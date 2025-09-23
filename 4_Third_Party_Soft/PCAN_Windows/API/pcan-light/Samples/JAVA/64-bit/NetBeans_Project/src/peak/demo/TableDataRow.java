package peak.demo;


import peak.canlight.CANMessage;
import peak.canlight.CANTimestamp;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author jonathan
 */
public class TableDataRow
{

    private CANMessage message;

    public int getCounter()
    {
        return counter;
    }

    public void setCounter(int counter)
    {
        this.counter = counter;
    }

    public CANMessage getMessage()
    {
        return message;
    }

    public void setMessage(CANMessage message)
    {
        this.message = message;
    }

    public CANTimestamp getRcvTime()
    {
        return rcvTime;
    }

    public void setRcvTime(CANTimestamp rcvTime)
    {
        this.rcvTime = rcvTime;
    }
    private CANTimestamp rcvTime;
    private int counter;
}
