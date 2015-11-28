package gui;

import javax.swing.*;
import java.awt.*;

/**
 * Created by emil on 2015-11-28.
 */
public class GuiMain extends JFrame {
    private JTextArea textArea = new JTextArea();
    private JButton parseButton = new JButton("Parse");

    public GuiMain() {
        super("Robot optimization");
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1;
        c.weighty = 0.8;
        c.insets = new Insets(2,2,2,2);
        JScrollPane textAreaPanel = new JScrollPane(textArea);
        add(textAreaPanel,c);
        c.gridy = 1;
        c.weighty = 0.2;
        add(parseButton,c);
        pack();
        setVisible(true);
    }

    public static void main(String[] args) {
        GuiMain main = new GuiMain();
    }
}
