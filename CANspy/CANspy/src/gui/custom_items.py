from PyQt5.QtWidgets import QTableWidgetItem

class HexIDItem(QTableWidgetItem):
    def __init__(self, hex_id_str):
        # Ensure consistent lowercase 'x' format
        if hex_id_str.startswith('0X'):
            hex_id_str = '0x' + hex_id_str[2:]
        super().__init__(hex_id_str)
        
    def __lt__(self, other):
        # Convert hex strings to integers for proper numerical comparison
        try:
            # Remove '0x' prefix if present and convert to integer
            self_val = int(self.text().replace('0x', '').replace('0X', ''), 16)
            other_val = int(other.text().replace('0x', '').replace('0X', ''), 16)
            return self_val < other_val
        except:
            # Fall back to string comparison if conversion fails
            return self.text() < other.text()