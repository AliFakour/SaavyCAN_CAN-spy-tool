package peak.canlight;

/**
 * This is the main class for using the pcanlight api
 * with your java applications.
 * Steps to use this api:<br><br>
 * <pre>
 * 1. Create a new CANLight object:<br>
 *    example: <br>
 *    can = new CANLight();<br>
 *    (or use an constructor which returns an initialized object)
 *
 * 2. Call the initializeAPI method passing the hardware parameter which you want use <br>
 *    example to initialize a USB hardware channel 1: <br>
 *    can.initializeAPI(CANLight.PCAN_USB_1CH);<br>
 *    (All hardwares are represented by a static constant prefixed by 'PCAN_')
 *
 * 3. If necessary call setFilter(), resetFilter() or resetClient()
 *	example:
 *	can.resetClient();
 *	can.resetFilter();
 *	can.setFilter(0x000,0x123,CANLight.TYPE_ST);
 *
 * 4. Call the read or write method <br>
 *    example:
 *	CANMessage msg;
 *	msg = can.read();
 *	can.write(msg);
 *    (do not forget to check if msg is null after calling the read method)<br>
 *
 * 5. At the end call the close method
 *    example:
 *    can.close();
 *</pre>
 *<br>
 *A minimalistic program that writes every can message that it receives (ping-pong)<br>
 *looks like this:<br>
 *<pre>
 *import peak.canlight.*;
 *
 *public class MinimalisticProgram
 *{
 *      public static void main(String[] args)
 *      {
 *          CANLight can;
 *          CANMessage msg;
 *          int res;
 *          can = new CANLight();
 *          if(!can.initializeAPI(CANLight.PCAN_USB_1CH))
 *          {
 *              System.out.println("Unable to initialize the API");
 *              System.exit(0);
 *          }
 *          res = canLight.init(CANLight.BAUD_1M, CANLight.MAX_EXTENDED_ID);
 *          msg = new CANMessage();
 *          while(true)
 *          {
 *              while(can.read(msg) == CANLight.ERR_OK)
 *              {
 *                  res = can.write(msg);
 *                  if(res != CANLight.ERR_OK)
 *                  {
 *                      System.out.println("Unable to write the CAN message");
 *                      System.exit(0);
 *                  }
 *              }
 *          }
 *      }
 *}
 *</pre>
 * @author Jonathan
 * @version 2.0
 */
public class CANLight {

    /**
     * A constant for 1 Megabaud
     */
    static public final int BAUD_1M = 0x0014;
    /**
     * A constant for 500 Kilobaud
     */
    static public final int BAUD_500K = 0x001c;
    /**
     * A constant for 250 Kilobaud
     */
    static public final int BAUD_250K = 0x011c;
    /**
     * A constant for 125 Kilobaud
     */
    static public final int BAUD_125K = 0x031c;
    /**
     * A constant for 100 Kilobaud
     */
    static public final int BAUD_100K = 0x432f;
    /**
     * A constant for 50 Kilobaud
     */
    static public final int BAUD_50K = 0x472f;
    /**
     * A constant for 20 Kilobaud
     */
    static public final int BAUD_20K = 0x532f;
    /**
     * A constant for 10 Kilobaud
     */
    static public final int BAUD_10K = 0x672f;
    /**
     * A constant for 5 Kilobaud
     */
    static public final int BAUD_5K = 0x7f7f;
    /**
     * A constant for the 11bit message type (standard)
     */
    static public final int TYPE_ST = 0x0000;
    /**
     * A constant for the 29bit message type (extended)
     */
    static public final int TYPE_EX = 0x0001;
    /**
     * 11bit message type (standard)
     */
    static public final byte MSGTYPE_STANDARD = 0x0;
    /**
     * Remote request
     */
    static public final byte MSGTYPE_RTR = 0x1;
    /**
     * 29bit message type (extended)
     */
    static public final byte MSGTYPE_EXTENDED = 0x2;
    /**
     * Status Message
     */
    static public final byte MSG_TYPE_STATUS = 0x3;
    /**
     * Maximal values for the standard ID of a CAN Message
     */
    static public final int MAX_STANDARD_ID = 0x7FF;
    /**
     * Maximal values for the extended ID of a CAN Message
     */
    static public final int MAX_EXTENDED_ID = 0x1FFFFFFF;


    /**
     * A constant for ISA hardware
     */
    static public final int HW_ISA = 1;
    /**
     * A constant for SJA Dongle hardware
     */
    static public final int HW_DONGLE_SJA = 5;
    /**
     * A constant for Dongle Pro hardware
     */
    static public final int HW_DONGLE_PRO = 7;
    /**
     * A constant for SJA ISA hardware
     */
    static public final int HW_ISA_SJA = 9;
    /**
     * A constant for PCI hardware
     */
    static public final int HW_PCI = 10;

    /**
     * A constant for ISA 1st channel
     */
    static public final int PCAN_ISA_1CH = 0;
    /**
     * A constant for ISA 2nd channel
     */
    static public final int PCAN_ISA_2CH = 1;
    /**
     * A constant for PCI 1st channel
     */
    static public final int PCAN_PCI_1CH = 2;
    /**
     * A constant for PCI 2nd channel
     */
    static public final int PCAN_PCI_2CH = 3;
    /**
     * A constant for PCC 1st channel
     */
    static public final int PCAN_PCC_1CH = 4;
    /**
     * A constant for PCC 2nd channel
     */
    static public final int PCAN_PCC_2CH = 5;
    /**
     * A constant for USB 1st channel
     */
    static public final int PCAN_USB_1CH = 6;
    /**
     * A constant for USB 2nd channel
     */
    static public final int PCAN_USB_2CH = 7;
    /**
     * A constant for DONGLE PRO
     */
    static public final int PCAN_DNP = 8;
    /**
     * A constant for DONGLE
     */
    static public final int PCAN_DNG = 9;

    /**
     * A constant for no error
     */
    static public final int ERR_OK = 0x0000;
    /**
     * A constant for send buffer of the Controller ist full
     */
    static public final int ERR_XMTFULL = 0x0001;
    /**
     * A constant for a constant for CAN-Controller was read to late
     */
    static public final int ERR_OVERRUN = 0x0002;
    /**
     * A constant for bus error: an Error count reached the limit
     */
    static public final int ERR_BUSLIGHT = 0x0004;
    /**
     * A constant for bus error: an Error count reached the limit
     */
    static public final int ERR_BUSHEAVY = 0x0008;
    /**
     * A constant for bus error: CAN_Controller went to 'Bus-Off'
     */
    static public final int ERR_BUSOFF = 0x0010;
    /**
     * A constant for rcvQueue is empty
     */
    static public final int ERR_QRCVEMPTY = 0x0020;
    /**
     * A constant for rcvQueue was read to late
     */
    static public final int ERR_QOVERRUN = 0x0040;
    /**
     * A constant for send queue is full
     */
    static public final int ERR_QXMTFULL = 0x0080;
    /**
     * A constant for registerTest of the 82C200/SJA1000 failed
     */
    static public final int ERR_REGTEST = 0x0100;
    /**
     *A constant for problem with Localization of the VxD
     */
    static public final int ERR_NOVXD = 0x0200;
    /**
     * A constant for ERR_HWINUSE
     */
    static public final int ERR_HWINUSE = 0x0400;
    /**
     * A constant for ERR_NETINUSE
     */
    static public final int ERR_NETINUSE = 0x0800;
    /**
     * A constant for invalid Hardware handle
     */
    static public final int ERR_ILLHW = 0x1400;
    /**
     * A constant for not generatably Resource (FIFO Client Timeout)
     */
    static public final int ERR_RESOURCE = 0x2000;
    /**
     * A constant for parameter not permitted
     */
    static public final int ERR_PARMTYP = 0x4000;
    /**
     * A constant for invalid Parameter value
     */
    static public final int ERR_PARMVAL = 0x8000;
    /**
     * A constant for mask for all Handle errors
     */
    static public final int ERR_MASK_ILLHANDLE = 0x1C00;
    /**
     * A constant for all others error status <> 0 please ask by PEAK ......intern Driver errors.....
     */
    static public final int ERR_ANYBUSERR = ERR_BUSLIGHT | ERR_BUSHEAVY | ERR_BUSOFF;
    /**
     * A constant for a Dll could not be loaded or a function was not found into the Dll
     */
    static public final int ERR_NO_DLL = 0xFFFFFFFF;

    /**
    * Standard Contructor
    *
    * If an object is created with this constructer use init() to initialize the object
    */
    public CANLight() {
    }

    /**
    * Initializes the PCANLight for a specific hardware
    *
    * @param hwType the hardware to be used
    */
    public native boolean initializeAPI(int hwType);

    /**
    * Activates the PNP hardware, initializes it and makes some tests
    * Use this method only with PNP hardware!
    *
    * @param baudRate the baudrate to be used
    * @param msgType the type of the message frame (standard or extended)
    * @return 0, if successful, otherwise the error code
    */
    public native int init(int baudRate, int msgType);

    /**
    * Activates the NON PNP hardware, initializes it and makes some tests.
    * Use this method only with NON PNP hardware!
    *
    * @param baudRate the baudrate to be used
    * @param msgType the type of the message frame (standard or extended)
    * @param ioPort the io port to use
    * @param interrupt the interrupt to use
    * @return 0, if successful, otherwise the error code
    */
    public native int init(int baudRate, int msgType, int ioPort,
            int interrupt);

    /**
    * Returns a String with version and copyright information
    *
    * @param strBuffer String buffer to return the hardware information (max. 255 characters)
    * @return 0, if successful, otherwise the error code.
    */
    public native int getVersionInfo(StringBuffer strBuffer);

    /**
    * Returns the version information of the used PCAN-Light DLL
    *
    * @param strBuffer String buffer to return the DLL information (max. 255 characters)
    * @return 0, if successful, otherwise the error code
    */
    public native int getDLLVersionInfo(StringBuffer strBuffer);

    /**
    * Returns the device number of a USB CAN Hardware
    *
    * @param deviceNumber number a single element array to pass an Integer by reference which represents the device number
    * @return 0, if successful, otherwise the error code.
    */
    public native int getUSBDeviceNr(int[] deviceNumber);

    /**
     * Write the new device number of a USB CAN Hardware
     *
     * @param deviceNumber device number
     * @return 0, if successful, otherwise the error code
     */
    public native int setUSBDeviceNr(int deviceNumber);

    /**
    * Deactivates the hardware and frees all used resources
    *
    * @return 0, if successful, otherwise the error code
    */
    public native int close();

    /**
     * Returns the status of the hardware
     *
     * @return Error/status of the hardware after execute the function
     */
    public native int getStatus();

    /**
     * Reads the next message.
     * With this method it is possible to reuse a previously created message object
     *
     * @param message An existing message object, that should be "filled" with data should not be null
     * @return 0, if successful, otherwise the error code
     * @see peak.canlight.CANMessage
     */
    public native int read(CANMessage message);

    /**
     * Reads the next message.
     * With this method it is possible to reuse a previously created message object.
     *
     * @param message An existing message object, that should be "filled" with data. Should not be null
     * @param rcvTime The TPCANTimestamp structure for the message's timestamp
     * @return 0, if successful, otherwise the error code.
     * @see peak.canlight.CANMessage
     * @see peak.canlight.CANTimestamp
     */
    public native int readEx(CANMessage message, CANTimestamp rcvTime);

    /**
    * Sets a hardware or software filter depending on the message type passed as third parameter
    *
    * @param from The smallest message ID, which should be received
    * @param to The largest message ID, which should be received
    * @param msgType The message type (use TYPE_ST or TYPE_EX)
    * @return 0, if successful, otherwise the error code
    */
    public native int setFilter(int from, int to, int msgType);

    /**
     * Closes the hardware filter such, that no more messages will be received
     *
     * @return 0, if successful, otherwise the error code
     */
    public native int resetFilter();

    /**
     * Writes a message.
     *
     * @param message The message that should be written to the can bus
     * @return 0, if successful, otherwise the error code
     * @see peak.canlight.CANMessage
     */
    public native int write(CANMessage message);

   
    /**
     * Clears the receive- and transmit-queues.
     *
     * @return 0, if successful, otherwise the error code
     */
    public native int resetClient();
    
    /**
     * Sets the handle of the Receive-Event.
     * static method peak.canlight.RcvEventDispatcher.dispatchRcvEvent is used
     * to notify each Receive-Event
     *
     * @return 0, if successful, otherwise the error code
     */
    public native int setRcvEvent();

    /**
     * Resets the handle of the Receive-Event.
     *
     * @return 0, if successful, otherwise the error code
     */
    public native int resetRcvEvent();

    /**
     * Calls C/C++ GetLastError Function
     *
     * @return 0, if successful, otherwise the system error code
     */
    public native long getLastError();

    static {
        System.loadLibrary("pcanlight_jni");
    }
}
