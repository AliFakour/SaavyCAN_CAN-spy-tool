from PyQt5 import QtWidgets, QtCore
from PyQt5.QtWidgets import QWidget, QTableWidget, QTableWidgetItem, QCheckBox, QLabel, QVBoxLayout, QHBoxLayout
from PyQt5.QtCore import pyqtSignal
import threading
import time
import can
from gui.custom_items import HexIDItem

class ConfigWindow(QWidget):
    message_received = pyqtSignal(dict)

    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("USB2CAN Configuration")
        self.setGeometry(100, 100, 800, 600)

        # Controls
        self.baud_rate_label = QtWidgets.QLabel("Baud Rate:")
        self.baud_rate_combo = QtWidgets.QComboBox()
        self.baud_rate_combo.addItems(["125 kbps", "250 kbps", "500 kbps", "1000 kbps"])
        self.fd_checkbox = QtWidgets.QCheckBox("Enable FD")
        self.overwrite_checkbox = QCheckBox("Overwrite")
        self.overwrite_checkbox.setChecked(True)
        self.status_label = QLabel("")

        # Layout for controls
        controls_layout = QHBoxLayout()
        controls_layout.addWidget(self.baud_rate_label)
        controls_layout.addWidget(self.baud_rate_combo)
        controls_layout.addWidget(self.fd_checkbox)
        controls_layout.addWidget(self.overwrite_checkbox)
        controls_layout.addWidget(self.status_label)
        controls_layout.addStretch()

        # Data table
        self.table = QTableWidget()
        self.table.setColumnCount(8)
        self.table.setHorizontalHeaderLabels([
            "#", "Timestamp", "CAN ID", "Type", "Length", "Data", "Cycle Time", "Count"
        ])
        self.table.verticalHeader().setVisible(False)
        self.table.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        self.table.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows)
        self.table.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.table.horizontalHeader().setSectionResizeMode(QtWidgets.QHeaderView.Interactive)
        self.table.setSortingEnabled(True)  # <-- Enable sorting

        # Main layout
        main_layout = QVBoxLayout(self)
        main_layout.addLayout(controls_layout)
        main_layout.addWidget(self.table)
        self.setLayout(main_layout)

        # Threading and message tracking
        self.receive_thread = None
        self.running = False
        self.msgs = {}  # {can_id: msg_data}
        self.last_timestamps = {}
        self.counts = {}

        self.message_received.connect(self.handle_message)
        self.overwrite_checkbox.stateChanged.connect(self.handle_overwrite_change)

    def start_receiving(self):
        baud_rate = self.baud_rate_combo.currentText()
        enable_fd = self.fd_checkbox.isChecked()
        self.status_label.setText(f"Receiving messages at {baud_rate} {'with FD' if enable_fd else 'without FD'}")
        if not self.running:
            self.running = True
            self.receive_thread = threading.Thread(target=self.receive_messages, daemon=True)
            self.receive_thread.start()

    def receive_messages(self):
        bus = None
        try:
            # Use stored configuration if available
            if hasattr(self, 'can_config'):
                bus = can.interface.Bus(**self.can_config)
            else:
                # Fallback to old configuration
                bus = can.interface.Bus(
                    interface='pcan',
                    channel='PCAN_USBBUS1',
                    bitrate=500000,
                    fd=self.fd_checkbox.isChecked()
                )
            while self.running:
                msg = bus.recv(1.0)
                if msg:
                    try:
                        timestamp = time.strftime('%H:%M:%S', time.localtime(float(msg.timestamp)))
                        timestamp += f".{int((float(msg.timestamp) % 1) * 1000):03d}"
                    except Exception:
                        timestamp = str(msg.timestamp)

                    can_id = hex(msg.arbitration_id)  # This naturally uses lowercase 'x'
                    msg_type = "FD" if getattr(msg, "is_fd", False) else "STD"
                    length = msg.dlc
                    data = ' '.join(f"{b:02X}" for b in msg.data)
                    cycle_time = ""
                    count = 1

                    try:
                        if can_id in self.last_timestamps:
                            prev = float(self.last_timestamps[can_id])
                            curr = float(msg.timestamp)
                            cycle = (curr - prev) * 1000
                            cycle_time = f"{cycle:.2f} ms"
                            self.last_timestamps[can_id] = curr
                            self.counts[can_id] += 1
                            count = self.counts[can_id]
                        else:
                            self.last_timestamps[can_id] = float(msg.timestamp)
                            self.counts[can_id] = 1
                    except Exception:
                        cycle_time = ""

                    overwrite = self.overwrite_checkbox.isChecked()
                    msg_data = {
                        'timestamp': timestamp,
                        'can_id': can_id,
                        'msg_type': msg_type,
                        'length': length,
                        'data': data,
                        'cycle_time': cycle_time,
                        'count': count,
                        'overwrite': overwrite
                    }
                    self.message_received.emit(msg_data)
        except Exception as e:
            QtCore.QMetaObject.invokeMethod(
                self.status_label,
                "setText",
                QtCore.Qt.QueuedConnection,
                QtCore.Q_ARG(str, f"Error: {e}")
            )
        finally:
            if bus is not None:
                bus.shutdown()

    def handle_message(self, msg_data):
        # Temporarily disable sorting
        was_sorting_enabled = self.table.isSortingEnabled()
        self.table.setSortingEnabled(False)
        
        timestamp = msg_data['timestamp']
        can_id = msg_data['can_id'].upper()
        msg_type = msg_data['msg_type']
        length = msg_data['length']
        data = msg_data['data']
        cycle_time = msg_data['cycle_time']
        count = msg_data['count']
        overwrite = msg_data['overwrite']

        if overwrite:
            row = self.find_row_by_can_id(can_id)
            if row is not None:
                self.update_row(row, timestamp, can_id, msg_type, length, data, cycle_time, count)
            else:
                row = self.table.rowCount()
                self.table.insertRow(row)
                self.set_row(row, timestamp, can_id, msg_type, length, data, cycle_time, count)
        else:
            row = self.table.rowCount()
            self.table.insertRow(row)
            self.set_row(row, timestamp, can_id, msg_type, length, data, cycle_time, count)
        
        self.update_row_numbers()
        
        # Re-enable sorting if it was enabled before
        self.table.setSortingEnabled(was_sorting_enabled)

    def handle_overwrite_change(self, state):
        # Temporarily disable sorting while modifying the table
        was_sorting_enabled = self.table.isSortingEnabled()
        self.table.setSortingEnabled(False)
    
        if state == QtCore.Qt.Checked:
            # Find all unique CAN IDs and their rows
            can_id_rows = {}
            for row in range(self.table.rowCount()):
                item = self.table.item(row, 2)
                if item:
                    can_id = item.text()
                    if can_id in can_id_rows:
                        can_id_rows[can_id].append(row)
                    else:
                        can_id_rows[can_id] = [row]
            
            # Remove all but the last row for each CAN ID with duplicates
            rows_to_remove = []
            for can_id, rows in can_id_rows.items():
                if len(rows) > 1:
                    # Keep the last row (most recent data)
                    rows_to_remove.extend(rows[:-1])
            
            # Remove rows in reverse order to keep indices valid
            for row in sorted(rows_to_remove, reverse=True):
                self.table.removeRow(row)
        
        # Update row numbers after removing rows
        self.update_row_numbers()
        
        # Re-enable sorting if it was enabled
        self.table.setSortingEnabled(was_sorting_enabled)

    def update_row_numbers(self):
        # Set row number column to be sequential from 1 to N
        for row in range(self.table.rowCount()):
            self.table.setItem(row, 0, QTableWidgetItem(str(row + 1)))

    def set_row(self, row, timestamp, can_id, msg_type, length, data, cycle_time, count):
        self.table.setItem(row, 0, QTableWidgetItem(str(row + 1)))
        self.table.setItem(row, 1, QTableWidgetItem(timestamp))
        self.table.setItem(row, 2, HexIDItem(can_id.upper()))  # Use custom item for CAN ID
        self.table.setItem(row, 3, QTableWidgetItem(msg_type))
        self.table.setItem(row, 4, QTableWidgetItem(str(length)))
        self.table.setItem(row, 5, QTableWidgetItem(data))
        self.table.setItem(row, 6, QTableWidgetItem(cycle_time))
        self.table.setItem(row, 7, QTableWidgetItem(str(count)))
        if row == 0:
            self.table.resizeColumnsToContents()

    def update_row(self, row, timestamp, can_id, msg_type, length, data, cycle_time, count):
        self.table.setItem(row, 1, QTableWidgetItem(timestamp))
        self.table.setItem(row, 3, QTableWidgetItem(msg_type))
        self.table.setItem(row, 4, QTableWidgetItem(str(length)))
        self.table.setItem(row, 5, QTableWidgetItem(data))
        self.table.setItem(row, 6, QTableWidgetItem(cycle_time))
        self.table.setItem(row, 7, QTableWidgetItem(str(count)))

    def stop_receiving(self):
        self.running = False
        if self.receive_thread and self.receive_thread.is_alive():
            self.receive_thread.join(timeout=2)
        self.status_label.setText("Disconnected.")

    def find_row_by_can_id(self, can_id):
        """Find row containing the given CAN ID, case insensitive"""
        can_id_lower = can_id.lower()
        for row in range(self.table.rowCount()):
            item = self.table.item(row, 2)  # CAN ID is in column 2
            if item and item.text().lower() == can_id_lower:
                return row
        return None

    def clear_table(self):
        # Temporarily disable sorting
        was_sorting_enabled = self.table.isSortingEnabled()
        self.table.setSortingEnabled(False)
        
        # Clear the table
        self.table.setRowCount(0)
        
        # Reset all data tracking
        self.last_timestamps = {}
        self.counts = {}
        
        # Re-enable sorting if it was enabled
        self.table.setSortingEnabled(was_sorting_enabled)
        
        self.status_label.setText("Table cleared.")

    def configure_can(self, config):
        """Configure CAN parameters based on dialog settings"""
        self.can_config = config
        
        # Update UI to reflect settings
        if 'bitrate' in config:
            bitrate_kbps = config['bitrate'] / 1000
            for i in range(self.baud_rate_combo.count()):
                if str(int(bitrate_kbps)) in self.baud_rate_combo.itemText(i):
                    self.baud_rate_combo.setCurrentIndex(i)
                    break
        
        self.fd_checkbox.setChecked(config.get('fd', False))
        
        # Update status label
        bitrate = config.get('bitrate', 500000) / 1000
        fd_text = ""
        if config.get('fd', False):
            data_bitrate = config.get('data_bitrate', bitrate * 1000) / 1000
            fd_text = f" (FD: {data_bitrate} kbps)"
        
        self.status_label.setText(f"Configured: {bitrate} kbps{fd_text}")