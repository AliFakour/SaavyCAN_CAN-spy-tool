from PyQt5.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLabel, QComboBox, 
                             QTabWidget, QWidget, QLineEdit, QTreeWidget, QTreeWidgetItem,
                             QPushButton, QGroupBox, QFormLayout, QCheckBox, QSpinBox,
                             QDoubleSpinBox, QRadioButton, QButtonGroup, QFrame)
from PyQt5.QtGui import QIcon, QFont, QBrush, QColor
from PyQt5.QtCore import Qt, QTimer
import can
import re

class ConnectionDialog(QDialog):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.setWindowTitle("Connect")
        self.setFixedSize(700, 500)
        
        self.main_layout = QVBoxLayout(self)
        
        # Hardware selection on left, settings on right
        self.content_layout = QHBoxLayout()
        
        # Hardware list (left side)
        self.hardware_group = QGroupBox("Available PCAN Hardware:")
        self.hardware_layout = QVBoxLayout(self.hardware_group)
        
        self.hardware_tree = QTreeWidget()
        self.hardware_tree.setHeaderHidden(True)
        self.hardware_layout.addWidget(self.hardware_tree)
        
        # Scan button for manual refresh
        self.scan_button = QPushButton("Scan for Hardware")
        self.scan_button.clicked.connect(self.load_hardware)
        self.hardware_layout.addWidget(self.scan_button)
        
        # Settings tabs (right side)
        self.tabs = QTabWidget()
        self.can_setup_tab = QWidget()
        self.acceptance_filter_tab = QWidget()
        self.options_tab = QWidget()
        
        self.tabs.addTab(self.can_setup_tab, "CAN Setup")
        self.tabs.addTab(self.acceptance_filter_tab, "Acceptance Filter")
        self.tabs.addTab(self.options_tab, "Options")
        
        # Setup CAN configuration tab
        self.setup_can_tab()
        
        # Button layout
        self.button_layout = QHBoxLayout()
        self.ok_button = QPushButton("OK")
        self.cancel_button = QPushButton("Cancel")
        self.help_button = QPushButton("Help")
        
        self.button_layout.addStretch()
        self.button_layout.addWidget(self.ok_button)
        self.button_layout.addWidget(self.cancel_button)
        self.button_layout.addWidget(self.help_button)
        
        # Add components to main layout
        self.content_layout.addWidget(self.hardware_group, 1)
        self.content_layout.addWidget(self.tabs, 2)
        
        self.main_layout.addLayout(self.content_layout)
        self.main_layout.addLayout(self.button_layout)
        
        # Connect signals
        self.ok_button.clicked.connect(self.accept)
        self.cancel_button.clicked.connect(self.reject)
        self.help_button.clicked.connect(self.show_help)
        self.hardware_tree.itemSelectionChanged.connect(self.on_hardware_selection_changed)
        
        # Initialize default selection
        self.set_default_values()
        
        # Load hardware initially
        self.load_hardware()
        
        # Set up timer for real-time hardware detection
        self.refresh_timer = QTimer(self)
        self.refresh_timer.timeout.connect(self.load_hardware)
        self.refresh_timer.start(5000)  # Check every 5 seconds

    def load_hardware(self):
        """Detect and display actual PCAN hardware devices"""
        previously_selected = None
        if self.hardware_tree.selectedItems():
            previously_selected = self.hardware_tree.selectedItems()[0].text(0)
            
        self.hardware_tree.clear()
        
        try:
            # Check for available PCAN hardware using the PCAN-Basic API
            import can.interfaces.pcan as pcan
            
            # Common PCAN channels to check
            channels = [
                'PCAN_USBBUS1', 'PCAN_USBBUS2', 'PCAN_USBBUS3', 'PCAN_USBBUS4',
                'PCAN_USBBUS5', 'PCAN_USBBUS6', 'PCAN_USBBUS7', 'PCAN_USBBUS8'
            ]
            
            found_devices = False
            
            for channel in channels:
                try:
                    # Try to initialize the channel (will fail if not available)
                    bus = can.Bus(interface='pcan', channel=channel, bitrate=500000)
                    
                    # Get hardware info if possible
                    hw_name = "PCAN-USB"
                    if hasattr(bus, 'get_hardware_name'):
                        try:
                            hw_name = bus.get_hardware_name()
                        except:
                            pass
                    
                    # If it's an FD capable device
                    is_fd = False
                    try:
                        # Check if FD is available
                        bus.shutdown()
                        bus = can.Bus(interface='pcan', channel=channel, bitrate=500000, fd=True)
                        is_fd = True
                        bus.shutdown()
                    except:
                        pass
                    
                    device_text = f"{hw_name}{' FD' if is_fd else ''}: {channel}"
                    
                    # Add to tree with green text
                    device_item = QTreeWidgetItem(self.hardware_tree)
                    device_item.setText(0, device_text)
                    
                    # Set green color and bold font
                    green_brush = QBrush(QColor(0, 128, 0))  # Dark green
                    bold_font = QFont()
                    bold_font.setBold(True)
                    device_item.setForeground(0, green_brush)
                    device_item.setFont(0, bold_font)
                    
                    # Store channel name in item data for later retrieval
                    device_item.setData(0, Qt.UserRole, channel)
                    
                    found_devices = True
                    
                    # Re-select previously selected item if it exists
                    if previously_selected and previously_selected == device_text:
                        device_item.setSelected(True)
                    
                except Exception as e:
                    # This channel is not available
                    continue
                finally:
                    if 'bus' in locals() and bus:
                        bus.shutdown()
            
            if not found_devices:
                # No devices found - red text and disable tabs
                item = QTreeWidgetItem(self.hardware_tree)
                item.setText(0, "No PCAN hardware detected")
                
                # Set red color and bold font
                red_brush = QBrush(QColor(255, 0, 0))  # Red
                bold_font = QFont()
                bold_font.setBold(True)
                item.setForeground(0, red_brush)
                item.setFont(0, bold_font)
                
                # Disable tabs
                self.tabs.setEnabled(False)
            else:
                # Hardware found - enable tabs
                self.tabs.setEnabled(True)
                
        except Exception as e:
            print(f"Error loading hardware: {e}")
            # Add error message if hardware detection fails
            item = QTreeWidgetItem(self.hardware_tree)
            error_text = f"Error detecting hardware: {str(e)}"
            item.setText(0, error_text)
            
            # Set red color and bold font
            red_brush = QBrush(QColor(255, 0, 0))
            bold_font = QFont()
            bold_font.setBold(True)
            item.setForeground(0, red_brush)
            item.setFont(0, bold_font)
            
            # Disable tabs
            self.tabs.setEnabled(False)
        
        # Select first item if any and none was previously selected
        if not self.hardware_tree.selectedItems() and self.hardware_tree.topLevelItemCount() > 0:
            self.hardware_tree.topLevelItem(0).setSelected(True)
        
        # Update OK button state based on selection
        self.on_hardware_selection_changed()

    def on_hardware_selection_changed(self):
        """Enable/disable OK button based on hardware selection"""
        selected = self.hardware_tree.selectedItems()
        valid_selection = False
        
        if selected:
            # Check if it's a valid device (not an error message)
            text = selected[0].text(0)
            valid_selection = "No PCAN hardware detected" not in text and "Error detecting" not in text
        
        self.ok_button.setEnabled(valid_selection)

    def setup_can_tab(self):
        layout = QFormLayout(self.can_setup_tab)
        
        # Mode selection
        self.mode_combo = QComboBox()
        self.mode_combo.addItems(["CAN", "CAN FD"])
        layout.addRow(QLabel("Mode:"), self.mode_combo)
        
        # Clock Frequency
        self.clock_combo = QComboBox()
        self.clock_combo.addItems(["20 MHz", "24 MHz", "30 MHz", "40 MHz", "60 MHz", "80 MHz"])
        self.clock_combo.setCurrentText("80 MHz")
        layout.addRow(QLabel("Clock Frequency:"), self.clock_combo)
        
        # Add a separator line
        line = QFrame()
        line.setFrameShape(QFrame.HLine)
        line.setFrameShadow(QFrame.Sunken)
        layout.addRow(line)
        
        # Database Entry / Bit Rate
        self.bitrate_combo = QComboBox()
        self.bitrate_combo.addItems(["1 MBit/s", "800 kBit/s", "500 kBit/s", "250 kBit/s", "125 kBit/s", "100 kBit/s", "Custom"])
        self.bitrate_combo.setCurrentText("500 kBit/s")
        self.bitrate_combo.currentTextChanged.connect(self.on_bitrate_changed)
        layout.addRow(QLabel("Database Entry:"), self.bitrate_combo)
        
        # Manual Bit Rate input
        self.bitrate_edit = QLineEdit("500")
        layout.addRow(QLabel("Bit Rate [kbit/s]:"), self.bitrate_edit)
        
        # Sample Point
        self.sample_point_layout = QHBoxLayout()
        self.sample_point_spin = QDoubleSpinBox()
        self.sample_point_spin.setRange(0, 100)
        self.sample_point_spin.setValue(81.3)
        self.sample_point_spin.setSingleStep(0.1)
        self.sample_point_button = QPushButton("...")
        self.sample_point_layout.addWidget(self.sample_point_spin)
        self.sample_point_layout.addWidget(self.sample_point_button)
        layout.addRow(QLabel("Sample Point [%]:"), self.sample_point_layout)
        
        # Prescaler
        self.prescaler_spin = QSpinBox()
        self.prescaler_spin.setRange(1, 1024)
        self.prescaler_spin.setValue(10)
        layout.addRow(QLabel("Prescaler:"), self.prescaler_spin)
        
        # CAN FD specific settings (shown/hidden based on mode)
        self.fd_group = QGroupBox("CAN FD Settings")
        fd_layout = QFormLayout(self.fd_group)
        
        self.data_bitrate_combo = QComboBox()
        self.data_bitrate_combo.addItems(["8 MBit/s", "5 MBit/s", "4 MBit/s", "2 MBit/s", "1 MBit/s", "Same as Nominal"])
        self.data_bitrate_combo.setCurrentText("2 MBit/s")
        fd_layout.addRow(QLabel("Data Bit Rate:"), self.data_bitrate_combo)
        
        self.fd_sample_point_layout = QHBoxLayout()
        self.fd_sample_point_spin = QDoubleSpinBox()
        self.fd_sample_point_spin.setRange(0, 100)
        self.fd_sample_point_spin.setValue(80.0)
        self.fd_sample_point_spin.setSingleStep(0.1)
        self.fd_sample_point_button = QPushButton("...")
        self.fd_sample_point_layout.addWidget(self.fd_sample_point_spin)
        self.fd_sample_point_layout.addWidget(self.fd_sample_point_button)
        fd_layout.addRow(QLabel("Data Sample Point [%]:"), self.fd_sample_point_layout)
        
        self.iso_checkbox = QCheckBox("ISO CAN FD standard")
        self.iso_checkbox.setChecked(True)
        fd_layout.addRow("", self.iso_checkbox)
        
        layout.addRow(self.fd_group)
        
        # Connect mode change to show/hide FD settings
        self.mode_combo.currentTextChanged.connect(self.on_mode_changed)
        self.on_mode_changed("CAN")  # Initialize visibility

    def on_mode_changed(self, mode):
        self.fd_group.setVisible(mode == "CAN FD")
        
    def on_bitrate_changed(self, text):
        # Extract number from text like "500 kBit/s"
        if text != "Custom":
            match = re.search(r"(\d+)", text)
            if match:
                self.bitrate_edit.setText(match.group(1))
        self.bitrate_edit.setEnabled(text == "Custom")

    def show_help(self):
        # Show help information
        pass
        
    def set_default_values(self):
        # Set default values
        self.mode_combo.setCurrentText("CAN")
        self.clock_combo.setCurrentText("80 MHz")
        self.bitrate_combo.setCurrentText("500 kBit/s")
        self.bitrate_edit.setText("500")
        self.sample_point_spin.setValue(81.3)
        self.prescaler_spin.setValue(10)
        
    def get_configuration(self):
        """Return the selected configuration as a dictionary"""
        is_fd = self.mode_combo.currentText() == "CAN FD"
        
        # Extract bitrate in numeric form
        bitrate_text = self.bitrate_edit.text()
        try:
            bitrate = int(bitrate_text) * 1000  # Convert kbit/s to bit/s
        except ValueError:
            bitrate = 500000  # Default to 500 kbit/s
            
        # Extract data bitrate if using FD
        data_bitrate = None
        if is_fd:
            data_rate_text = self.data_bitrate_combo.currentText()
            if data_rate_text == "Same as Nominal":
                data_bitrate = bitrate
            else:
                match = re.search(r"(\d+)", data_rate_text)
                if match:
                    value = int(match.group(1))
                    if "MBit" in data_rate_text:
                        data_bitrate = value * 1000000
                    else:
                        data_bitrate = value * 1000
        
        # Get selected hardware
        selected_items = self.hardware_tree.selectedItems()
        channel = 'PCAN_USBBUS1'  # Default
        if selected_items:
            # Get channel from item data if available
            stored_channel = selected_items[0].data(0, Qt.UserRole)
            if stored_channel:
                channel = stored_channel
            else:
                # Extract from text as fallback
                item_text = selected_items[0].text(0)
                # Try to extract channel name from the end (after colon)
                if ":" in item_text:
                    channel_part = item_text.split(":")[-1].strip()
                    if channel_part:
                        channel = channel_part
        
        config = {
            'interface': 'pcan',
            'channel': channel,
            'bitrate': bitrate,
            'fd': is_fd
        }
        
        if is_fd and data_bitrate:
            config['data_bitrate'] = data_bitrate
            
        return config

    def closeEvent(self, event):
        """Stop the timer when dialog is closed"""
        self.refresh_timer.stop()
        super().closeEvent(event)