# File: /CANspy/CANspy/src/types/index.py

BAUD_RATE_125K = 125000
BAUD_RATE_250K = 250000
BAUD_RATE_500K = 500000
BAUD_RATE_1M = 1000000

FD_ENABLED = True
FD_DISABLED = False

MESSAGE_FORMAT_STANDARD = 0
MESSAGE_FORMAT_EXTENDED = 1

class CANMessage:
    def __init__(self, identifier, data, is_fd=False):
        self.identifier = identifier
        self.data = data
        self.is_fd = is_fd

    def __repr__(self):
        return f"CANMessage(identifier={self.identifier}, data={self.data}, is_fd={self.is_fd})"