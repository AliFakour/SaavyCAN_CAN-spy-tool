package peak.demo;

import java.awt.*;
import javax.swing.*;

/*
 * Created on 20.05.2004
 *
 */


public class SplashScreen
    extends JWindow {
  public SplashScreen() {
    try {
      jbInit();
    }
    catch (Exception ex) {
      ex.printStackTrace();
    }
  }

  public SplashScreen(String image, String text) {
    JPanel contentPane = new JPanel();
    contentPane.setBackground(new Color(255,255, 255));
    contentPane.setLayout(new BorderLayout());

    if (image != null) {
      ImageIcon icon = new ImageIcon(this.getClass().getResource(image));
      contentPane.add("Center", new JLabel(icon, JLabel.CENTER));
    }
    contentPane.add("South", new JLabel(text, JLabel.CENTER));
    setContentPane(contentPane);
  }

  public void showFor(int ms) {
    Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
    setLocation(dim.width / 3, dim.height / 3);
    setSize(360,360);
    setVisible(true);
    try {
      Thread.sleep(ms);
    }
    catch (InterruptedException e) {
    }
    setVisible(false);
  }

  private void jbInit() throws Exception {
  }
}
