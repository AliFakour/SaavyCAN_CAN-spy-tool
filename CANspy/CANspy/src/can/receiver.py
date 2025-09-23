class CANReceiver:
    def __init__(self):
        self.is_receiving = False

    def start_receiving(self):
        if not self.is_receiving:
            self.is_receiving = True
            # Logic to start receiving messages from the CAN bus
            print("Started receiving messages.")

    def stop_receiving(self):
        if self.is_receiving:
            self.is_receiving = False
            # Logic to stop receiving messages from the CAN bus
            print("Stopped receiving messages.")

    def receive_message(self):
        if self.is_receiving:
            # Logic to receive a message from the CAN bus
            message = "Sample CAN message"  # Placeholder for actual message
            return message
        return None