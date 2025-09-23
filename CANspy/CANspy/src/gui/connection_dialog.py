from PyQt5.QtWidgets import (QDialog, QVBoxLayout, QHBoxLayout, QLabel, QComboBox, 
                             QTabWidget, QWidget, QLineEdit, QTreeWidget, QTreeWidgetItem,
                             QPushButton, QGroupBox, QFormLayout, QCheckBox, QSpinBox,
                             QDoubleSpinBox, QRadioButton, QButtonGroup, QFrame)
from PyQt5.QtGui import QIcon
from PyQt5.QtCore import Qt
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
        
        # Load available hardware
        self.load_hardware()
        
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
        
        # Initialize default selection
        self.set_default_values()

    def load_hardware(self):
        try:
            # Try to detect available PCAN hardware
            # This is a placeholder - actual hardware detection depends on the PCAN API
            pcan_usb = QTreeWidgetItem(self.hardware_tree)
            pcan_usb.setText(0, "PCAN-USB FD: Device ID 80000000h")
            pcan_usb.setIcon(0, QIcon("path/to/usb-icon.png"))  # Add an icon path if available
            pcan_usb.setSelected(True)
        except Exception as e:
            print(f"Error loading hardware: {e}")
            # Add dummy entry if hardware detection fails
            item = QTreeWidgetItem(self.hardware_tree)
            item.setText(0, "No PCAN hardware detected")

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
            # Extract device info from selected item
            item_text = selected_items[0].text(0)
            if "Device ID" in item_text:
                # This is just a placeholder - actual channel mapping would depend on your implementation
                channel = 'PCAN_USBBUS1'
        
        config = {
            'interface': 'pcan',
            'channel': channel,
            'bitrate': bitrate,
            'fd': is_fd
        }
        
        if is_fd and data_bitrate:
            config['data_bitrate'] = data_bitrate
            
        return config