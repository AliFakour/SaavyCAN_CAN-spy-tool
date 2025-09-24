import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, QMenuBar, QStatusBar
from PyQt5.QtGui import QIcon, QColor
from PyQt5.QtCore import Qt

# List required modules
required_modules = ["PyQt5", "can"]

missing_modules = []
for module in required_modules:
    try:
        __import__(module)
    except ImportError:
        missing_modules.append(module)

if missing_modules:
    print(f"Missing modules detected: {', '.join(missing_modules)}")
    response = input(f"Do you want to install them automatically? (y/n): ")
    if response.lower() == "y":
        import subprocess
        for module in missing_modules:
            subprocess.check_call([sys.executable, "-m", "pip", "install", module])
        print("Modules installed. Please restart the application.")
        sys.exit(0)
    else:
        print("Please install the missing modules and restart the application.")
        sys.exit(1)

from gui.config_window import ConfigWindow
from gui.connection_dialog import ConnectionDialog

class MainApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("CANspy Application")
        self.setGeometry(100, 100, 800, 600)
        self.config_window = ConfigWindow(self)
        self.setCentralWidget(self.config_window)
        
        # Create status bar
        self.status_bar = QStatusBar()
        self.setStatusBar(self.status_bar)
        self.update_status_bar("Disconnected", connected=False)
        
        self.create_menu()

    def create_menu(self):
        menubar = self.menuBar()

        # Connect/Disconnect action
        self.connect_action = QAction(QIcon(), "Connect", self)
        self.connect_action.setCheckable(True)
        self.connect_action.setChecked(False)
        self.connect_action.triggered.connect(self.toggle_connection)
        menubar.addAction(self.connect_action)

        # Clear table action
        clear_action = QAction(QIcon(), "Clear", self)
        clear_action.triggered.connect(self.clear_table)
        menubar.addAction(clear_action)

        # Exit action
        exit_action = QAction(QIcon(), "Exit", self)
        exit_action.triggered.connect(self.exit_app)
        menubar.addAction(exit_action)

    def update_status_bar(self, message, connected=False):
        """Update status bar with connection status"""
        if connected:
            # Green text for connected
            self.status_bar.setStyleSheet("color: green; font-weight: bold;")
        else:
            # Red text for disconnected
            self.status_bar.setStyleSheet("color: red; font-weight: bold;")
        self.status_bar.showMessage(message)

    def toggle_connection(self):
        if not self.connect_action.isChecked():
            self.config_window.stop_receiving()
            self.connect_action.setText("Connect")
            self.update_status_bar("Disconnected", connected=False)
        else:
            try:
                # Show connection dialog
                dialog = ConnectionDialog(self)
                if dialog.exec_():
                    # User clicked OK
                    try:
                        config = dialog.get_configuration()
                        self.config_window.configure_can(config)
                        
                        # Try to start receiving - this is where it's likely failing
                        success = self.config_window.start_receiving()
                        
                        if success:
                            self.connect_action.setText("Disconnect")
                            
                            # Update status bar with connection info
                            bitrate = config.get('bitrate', 500000) / 1000
                            channel = config.get('channel', 'UNKNOWN')
                            fd_status = "FD Enabled" if config.get('fd', False) else "FD Disabled"
                            data_bitrate = ""
                            if config.get('fd', False) and 'data_bitrate' in config:
                                data_bitrate = f", Data: {config['data_bitrate']/1000} kbps"
                            
                            status_text = f"Connected: {channel} at {bitrate} kbps{data_bitrate} ({fd_status})"
                            self.update_status_bar(status_text, connected=True)
                        else:
                            # Connection failed
                            self.connect_action.setChecked(False)
                            self.update_status_bar("Connection failed", connected=False)
                    except Exception as e:
                        # Handle errors in connection setup
                        import traceback
                        traceback.print_exc()
                        self.connect_action.setChecked(False)
                        self.update_status_bar(f"Error: {str(e)}", connected=False)
                else:
                    # User cancelled
                    self.connect_action.setChecked(False)
                    self.update_status_bar("Disconnected", connected=False)
            except Exception as e:
                # Catch any other errors
                import traceback
                traceback.print_exc()
                self.connect_action.setChecked(False)
                self.update_status_bar(f"Error: {str(e)}", connected=False)

    def clear_table(self):
        self.config_window.clear_table()

    def exit_app(self):
        self.config_window.stop_receiving()
        QApplication.quit()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_app = MainApp()
    main_app.show()
    sys.exit(app.exec_())