package peak.demo;

import java.util.HashMap;
import javax.swing.JTable;

import javax.swing.table.DefaultTableModel;
import peak.canlight.CANMessage;

/*
 * Created on 22.05.2004
 */
public class TableMessageThread extends Thread
{

    public TableMessageThread()
    {
        try
        {
            jbInit();
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
    }
    private JTable table;
    private HashMap data;

    public TableMessageThread(JTable table, HashMap data)
    {
        this.table = table;
        this.data = data;
    }

    public void run()
    {
        //Variables
        TableDataRow dataRow = null;
        CANMessage msg = null;
        String msgIDStr = "";
        String msgLength = "";
        String msgType = "";
        String msgData = "";
        String blockData = "";
        String msgCount = "";
        String msgRcvTime = "";
        Object[] msgTableObect = null;

        //Retrieve JTable Model
        DefaultTableModel model = (DefaultTableModel) table.getModel();
        int msgIndex = -1;
        while (true)
        {
            for (Object item : data.values())
            {
                //Reset Variables Values
                msg = null;
                msgIDStr = "";
                msgLength = "";
                msgType = "";
                msgData = "";
                msgCount = "";
                msgRcvTime = "";
                msgTableObect = null;
                msgIndex = -1;

                //Cast item in TableDataRow
                dataRow = (TableDataRow) item;
                //Get CanMessage
                msg = dataRow.getMessage();

                //Get Type
                if (msg.getType() == 0)
                    msgType = "Standard";
                else
                    msgType = "Extended";
                //Message Length
                msgLength = String.valueOf(msg.getLength());
                //Message ID
                msgIDStr = Integer.toHexString(msg.getID()) + "h";
                //Message Data
                byte[] d = msg.getData();
                for (int dataIndex = 0; dataIndex < msg.getLength(); dataIndex++)
                {
                    blockData = Integer.toHexString(d[dataIndex] & 0xff);
                    if (blockData.length() == 1)
                        blockData = "0" + blockData;
                    msgData = msgData + blockData + " ";
                }
                //Message Count
                msgCount = String.valueOf(dataRow.getCounter());
                //Add Rcv Time If Need Be
                if (dataRow.getRcvTime() != null)
                    msgRcvTime = String.valueOf(dataRow.getRcvTime().getMillis()) + "." + String.valueOf(dataRow.getRcvTime().getMicros());
                //Construct JTable Object
                msgTableObect = new Object[]{ msgType, msgIDStr, msgLength, msgData, msgCount, msgRcvTime};

                synchronized(Application.token)
                {
                    //Search Existing DataRow In Model
                    for (int i = 0; i < model.getRowCount(); i++)
                    {
                        if (model.getValueAt(i, 1).toString().equals(msgIDStr))
                        {
                            msgIndex = i;
                            break;
                        }
                    }
                    //Index not found
                    if (msgIndex == -1)
                        model.addRow(msgTableObect);
                    //Index was found
                    else
                    {
                        for(int i=0;i<6;i++)
                            model.setValueAt(msgTableObect[i], msgIndex, i);
                    }
                }
            }

            //Update UI
            table.repaint(table.getVisibleRect());

            try
            {
                Thread.sleep(100);
            }
            catch (InterruptedException e)
            {
                System.out.println(e.getMessage());
                System.exit(0);
            }
        }
    }

    private void jbInit() throws Exception
    {
    }
}
