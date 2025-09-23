package peak.canlight;

/**
 * This interface is implemented by classes which need to process the CAN Receive-Event.
 */
public interface IRcvEventProcessor
{
    /**
     * This method is called by the RcvEventDispatcher to process the CAN Receive-Event
     * by the current implementor
     */
    public void processRcvEvent();
}