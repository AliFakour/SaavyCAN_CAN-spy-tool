import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QAction, QMenuBar
from PyQt5.QtGui import QIcon

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

class MainApp(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("CANspy Application")
        self.setGeometry(100, 100, 800, 600)
        self.config_window = ConfigWindow(self)
        self.setCentralWidget(self.config_window)
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

    def toggle_connection(self):
        if self.connect_action.isChecked():
            self.config_window.start_receiving()
            self.connect_action.setText("Disconnect")
        else:
            self.config_window.stop_receiving()
            self.connect_action.setText("Connect")

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