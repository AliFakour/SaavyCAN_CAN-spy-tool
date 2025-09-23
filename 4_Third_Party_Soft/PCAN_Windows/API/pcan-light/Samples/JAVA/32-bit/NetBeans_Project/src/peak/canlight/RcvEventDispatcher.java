package peak.canlight;

/**
 * This class is a gateway between the PCAN Light JNI and the application to dispatch the CAN Receive-Event.
 *<pre>
 *RcvEventDispatcher contains a public static method dispatchRcvEvent which is called from the JNI to notify the Java
 *application when the handle of the Receive-Event detects a state change.
 *</pre>
 */
public class RcvEventDispatcher
{
    static private IRcvEventProcessor listener;

    /**
     * Gets the Receive-Event processor
     * @return a IRcvEventProcessor
     */
    public static IRcvEventProcessor getListener()
    {
        return listener;
    }

    /**
     * Sets the Receive-Event processor
     * @param listener a IRcvEventProcessor implementor
     */
    public static void setListener(IRcvEventProcessor listener)
    {
        RcvEventDispatcher.listener = listener;
    }

    /**
     * This static public method will call from JNI to process the Receive-Event
     * by the listener
     */
    static public void dispatchRcvEvent()
    {
        if(listener != null)
            listener.processRcvEvent();
    }
}
