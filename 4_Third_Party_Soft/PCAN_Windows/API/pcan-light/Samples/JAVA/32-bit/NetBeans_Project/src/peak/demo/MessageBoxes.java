package peak.demo;

import javax.swing.*;

public class MessageBoxes {
  public MessageBoxes() {
  }

  public static void ShowMessage(String Text)
  {
    ShowMessage(Text,"MyApplication");
  }

  public static void ShowMessage(String Text,String Title)
  {
    ShowMessage(Text,Title,JOptionPane.NO_OPTION);
  }

  public static void ShowMessage(String Text,String Title,int messageType)
  {
    JOptionPane.showMessageDialog(null,Text,Title,messageType);
  }

  public static void ShowError(String Text,String Title)
  {
    ShowMessage(Text,Title,JOptionPane.ERROR_MESSAGE);
  }

  public static void ShowWarning(String Text,String Title)
  {
    ShowMessage(Text,Title,JOptionPane.WARNING_MESSAGE);
  }

  public static void ShowInfo(String Text,String Title)
  {
    ShowMessage(Text,Title,JOptionPane.INFORMATION_MESSAGE);
  }
}
