package gui;

import parser.Grid;
import parser.State;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * Created by emil on 2015-11-28.
 */
public class GuiMain extends JFrame {
    private JTextArea textArea = new JTextArea();
    private JButton parseButton = new JButton("Parse");
    private JButton runButton = new JButton("Step");
    private GridPanel gridPanel;
    private JList<String> codeList = new JList<>();
    private JPanel codePanel = new JPanel(new CardLayout());

    public GuiMain(Grid grid, State state) {
        super("Robot optimization");
        gridPanel = new GridPanel(grid, state);
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1;
        c.weighty = 1;
        c.insets = new Insets(4,4,4,4);
        c.gridheight = 2;
        codePanel.add(new JScrollPane(textArea));
        codePanel.add(new JScrollPane(codeList));
        add(codePanel,c);
        c.gridheight = 1;
        c.gridwidth = 2;
        c.weighty = 0.9;
        c.gridy = 0;
        c.gridx = 1;
        add(gridPanel,c);
        c.gridheight = 1;
        c.gridwidth = 1;
        c.gridx = 1;
        c.gridy = 1;
        c.weighty = 0.1;
        c.fill = GridBagConstraints.HORIZONTAL;
        add(parseButton,c);
        c.gridx = 2;
        add(runButton,c);
        pack();
        setVisible(true);
        parseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                swapToList();
            }
        });
        runButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                codeList.setSelectedIndex(Math.min(codeList.getModel().getSize()-1,codeList.getSelectedIndex() + 1));
            }
        });
        codeList.setEnabled(false);
        runButton.setEnabled(false);
    }

    private void swapToList() {
        String code = textArea.getText();
        DefaultListModel<String> listModel = new DefaultListModel<>();
        for(String line : code.split("\n")) {
            listModel.addElement(line);
        }
        codeList.setModel(listModel);
        CardLayout cl = (CardLayout)(codePanel.getLayout());
        cl.next(codePanel);
        codeList.setSelectedIndex(0);
        parseButton.setEnabled(false);
        runButton.setEnabled(true);
    }

    private static Grid createDummyGrid() {
        Grid.SquareType[][] squareTypes = new Grid.SquareType[5][5];
        squareTypes[0][1] = Grid.SquareType.BLOCKED;
        squareTypes[2][0] = Grid.SquareType.BLOCKED;
        squareTypes[3][0] = Grid.SquareType.BLOCKED;
        squareTypes[4][0] = Grid.SquareType.BLOCKED;
        squareTypes[3][1] = Grid.SquareType.BLOCKED;
        return new Grid(5,5,squareTypes);
    }

    public static void main(String[] args) throws IOException {
        State state = new State(0,0,State.Direction.LEFT);
        Grid grid = createDummyGrid();
        GuiMain main = new GuiMain(grid,state);
    }
}
