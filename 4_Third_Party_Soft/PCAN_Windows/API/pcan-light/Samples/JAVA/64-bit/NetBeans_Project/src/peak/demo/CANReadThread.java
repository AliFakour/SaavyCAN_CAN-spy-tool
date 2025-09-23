package peak.demo;

import java.util.HashMap;
import peak.canlight.CANLight;
import peak.canlight.CANMessage;
import peak.canlight.CANTimestamp;
import peak.canlight.IRcvEventProcessor;

/*
 * Created on 22.05.2004
 *
 */
public class CANReadThread extends Thread implements IRcvEventProcessor
{

    private CANLight canLight;
    private HashMap dataRowCollection;
    private Boolean readTimeStamp = false;

    // UseReadEx Getter
    public Boolean getUseReadEx()
    {
        return readTimeStamp;
    }

    // UseReadEx Setter
    public void setUseReadEx(Boolean useReadEx)
    {
        this.readTimeStamp = useReadEx;
    }

    // Constructor
    public CANReadThread(CANLight can, HashMap data)
    {
        this.canLight = can;
        this.dataRowCollection = data;
    }

    public void run()
    {
        while (true)
        {
            //Call Read/ReadEx
            callAPIFunctionRead();

            //Sleep
            try
            {
                Thread.sleep(10);
            }
            catch (InterruptedException e)
            {
                return;
            }
        }
    }

    //Call Read/ReadEx Can Function And Process Message
    public void callAPIFunctionRead()
    {
        //Variables
        CANMessage canMessage = null;
        CANTimestamp rcvTime = null;
        TableDataRow dataRow = null;
        int ret;
        int messageID = 0;

        try
        {
            //Select PCANLight Function
            do
            {
                //Create A New Message
                canMessage = new CANMessage();
                //Create A New Time Stamp
                rcvTime = new CANTimestamp();

                if (readTimeStamp)
                    ret = canLight.readEx(canMessage, rcvTime);
                else
                    ret = canLight.read(canMessage);

                //If No Error
                if (ret == 0)
                {
                    //Get Message ID
                    messageID = canMessage.getID();

                    //Check If Message Was Already Processed
                    if (dataRowCollection.containsKey(messageID))
                        dataRow = (TableDataRow) dataRowCollection.get(messageID);
                    else
                        dataRow = new TableDataRow();

                    //Set Readed Message
                    dataRow.setMessage(canMessage);

                    //Set Time Stamp If Need Be
                    if (readTimeStamp)
                        dataRow.setRcvTime(rcvTime);
                    else
                        dataRow.setRcvTime(null);

                    //Update Message COunter
                    dataRow.setCounter(dataRow.getCounter() + 1);

                    //Critical Area
                    synchronized (Application.token)
                    {
                        //Put Message In the dataRowCollection
                        dataRowCollection.put(messageID, dataRow);
                    }

                    canMessage = null;
                    rcvTime = null;
                }
            }
            while ((ret & CANLight.ERR_QRCVEMPTY) == 0);
        }
        catch (Exception e)
        {
            System.out.println("CANReadThread Exception:" + e.getMessage());
            e.printStackTrace();
            System.exit(0);
        }
    }

    public void processRcvEvent()
    {
        callAPIFunctionRead();
    }
}
