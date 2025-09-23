import can

try:
    bus = can.interface.Bus(
        interface='pcan',
        channel='PCAN_USBBUS1',
        bitrate=500000
    )
    print("PCAN-USB FD device opened successfully on channel: PCAN_USBBUS1")
finally:
    try:
        bus.shutdown()
    except Exception:
        pass