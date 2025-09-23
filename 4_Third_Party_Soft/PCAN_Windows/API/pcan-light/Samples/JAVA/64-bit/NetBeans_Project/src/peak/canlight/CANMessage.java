package peak.canlight;

/**
 * Defines a CAN message.
 */
public class CANMessage implements Cloneable
{

    private int _id;
    private byte _type;
    private byte _length;
    private byte _data[];

    /**
     * Default constructor
     */
    public CANMessage()
    {
        _data = new byte[8];
    }

    /**
     * Constructs a new message object.
     * @param id the message id
     * @param type the message type
     * @param length the message length
     * @param data the message data
     */
    public CANMessage(int id, byte type, byte length, byte[] data)
    {
        _id = id;
        _type = type;
        _length = length;
        _data = new byte[length];
        for (int j = 0; j < length; j++)
        {
            _data[j] = data[j];
        }
    }

    /**
     * Sets the id of this message.
     * @param id the message id
     */
    public void setID(int id)
    {
        _id = id;
    }

    /**
     * Sets the data and length of this message.
     * @param data the message data
     * @param length the message length
     */
    public void setData(byte[] data, byte length)
    {
        _length = length;
        for (int j = 0; j < length; j++)
        {
            _data[j] = data[j];
        }
    }

    /**
     * Sets the length of this message.
     * @param length the length of the message
     */
    public void setLength(byte length)
    {
        _length = length;
    }

    /**
     * Sets the type of this message.
     * @param type the message type
     */
    public void setType(byte type)
    {
        _type = type;
    }

    /**
     * Gets the id of this message.
     * @return the message id
     */
    public int getID()
    {
        return _id;
    }

    /**
     * Gets the data of this message.
     * @return the message data
     */
    public byte[] getData()
    {
        return _data;
    }

    /**
     * Gets the length of this message.
     * @return the message length
     */
    public byte getLength()
    {
        return _length;
    }

    /**
     * Gets the type of this message.
     * @return the message type
     */
    public byte getType()
    {
        return _type;
    }

    /**
     * Clones this message object.
     * @return The cloned message object.
     */
    public Object clone()
    {
        CANMessage msg = null;
        try
        {
            msg = (CANMessage) super.clone();
            msg._data = (byte[]) _data.clone();
        }
        catch (CloneNotSupportedException e)
        {
            System.out.println(e.getMessage());
        }
        return msg;
    }
}
