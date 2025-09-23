# CANspy Application

## Overview
CANspy is a Python application designed to configure and interact with the USB2CAN module. It provides a graphical user interface (GUI) for setting parameters such as baud rate and enabling CAN FD (Flexible Data-rate) functionality. The application also allows users to start receiving messages over the CAN bus.

## Project Structure
```
CANspy/
├── src/
│   ├── main.py               # Entry point of the application
│   ├── gui/
│   │   └── config_window.py   # GUI for configuring the USB2CAN module
│   ├── can/
│   │   └── receiver.py        # Logic for receiving CAN messages
│   ├── utils/
│   │   └── usb2can.py         # Utility functions for USB2CAN interaction
│   └── types/
│       └── index.py           # Data types and constants
├── requirements.txt           # Project dependencies
├── README.md                  # Project documentation
└── setup.py                   # Packaging configuration
```

## Installation
To set up the project, follow these steps:

1. Clone the repository:
   ```
   git clone <repository-url>
   cd CANspy
   ```

2. Install the required dependencies:
   ```
   pip install -r requirements.txt
   ```

## Usage
To run the application, execute the following command:
```
python src/main.py
```

Once the application is running, you can configure the USB2CAN module through the GUI. Set the desired baud rate, enable CAN FD if needed, and start receiving messages from the CAN bus.

## Contributing
Contributions are welcome! Please feel free to submit a pull request or open an issue for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for details.