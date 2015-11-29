package gui;

import parser.Context;
import parser.Grid;
import parser.State;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;

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
    private JButton zoomInButton = new JButton("Zoom in");
    private JButton zoomOutButton = new JButton("Zoom out");

    public GuiMain(Grid grid, State state) {
        super("Robot optimization");
        gridPanel = new GridPanel(grid, state);
        setLayout(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.fill = GridBagConstraints.BOTH;
        c.weightx = 1;
        c.weighty = 1;
        c.insets = new Insets(5, 5, 5, 5);
        c.gridheight = 3;
        codePanel.add(new JScrollPane(textArea));
        codePanel.add(new JScrollPane(codeList));
        add(codePanel, c);
        c.gridheight = 1;
        c.gridwidth = 2;
        c.weighty = 0.9;
        c.gridy = 0;
        c.gridx = 1;
        add(new JScrollPane(gridPanel), c);
        c.gridheight = 1;
        c.gridwidth = 1;
        c.gridx = 1;
        c.gridy = 1;
        c.weighty = 0.1;
        c.fill = GridBagConstraints.HORIZONTAL;
        add(zoomInButton, c);
        c.gridx = 2;
        add(zoomOutButton, c);
        c.gridx = 1;
        c.gridy = 2;
        add(parseButton, c);
        c.gridx = 2;
        add(runButton, c);
         parseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                swapToList();
            }
        });
        runButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                codeList.setSelectedIndex(Math.min(codeList.getModel().getSize() - 1, codeList.getSelectedIndex() + 1));
            }
        });
        zoomInButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gridPanel.zoomIn();
                invalidate();
            }
        });
        zoomOutButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                gridPanel.zoomOut();
                invalidate();
            }
        });
        codeList.setEnabled(false);
        runButton.setEnabled(false);
        JMenuBar menuBar = new JMenuBar();
        JMenu loadMenu = new JMenu("Load");
        JMenuItem loadMapButton = new JMenuItem("Map file");
        loadMapButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                try{
                    loadMap();
                }   catch (IOException e) {
                    JOptionPane.showMessageDialog(GuiMain.this, e.getMessage(), "Error loading map",JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        JMenuItem loadCodeButton = new JMenuItem("Code file");
        loadCodeButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent ev) {
                try{
                    loadCode();
                }   catch (IOException e) {
                    JOptionPane.showMessageDialog(GuiMain.this, e.getMessage(), "Error loading code",JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        loadMenu.add(loadMapButton);
        loadMenu.add(loadCodeButton);
        menuBar.add(loadMenu);
        setJMenuBar(menuBar);
        pack();
        setVisible(true);
    }

    private void loadMap() throws IOException {
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Robot maps", "in");
        fileChooser.setFileFilter(filter);
        int returnVal = fileChooser.showOpenDialog(GuiMain.this);
        if(returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            if(!file.exists()) throw new IOException("Could not find file " + file.getCanonicalPath());
            Context con = Context.readInitialConfig(new FileInputStream(file));
            gridPanel.setGrid(con.grid);
            gridPanel.setState(con.states.get(0));
        }
    }

    private void loadCode() throws IOException {
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Robot code files", "ans");
        fileChooser.setFileFilter(filter);
        int returnVal = fileChooser.showOpenDialog(GuiMain.this);
        if(returnVal == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            if(!file.exists()) throw new IOException("Could not find file " + file.getCanonicalPath());
            BufferedReader br = new BufferedReader(new FileReader(file));
            StringBuilder sb = new StringBuilder();
            while(true) {
                String line = br.readLine();
                if(line == null) break;
                sb.append(line);
                sb.append("\n");
            }
            textArea.setText(sb.toString());
            CardLayout cl = (CardLayout) (codePanel.getLayout());
            cl.first(codePanel);
            parseButton.setEnabled(true);
            runButton.setEnabled(false);
        }
    }

    private void swapToList() {
        String code = textArea.getText();
        DefaultListModel<String> listModel = new DefaultListModel<>();
        for (String line : code.split("\n")) {
            listModel.addElement(line);
        }
        codeList.setModel(listModel);
        CardLayout cl = (CardLayout) (codePanel.getLayout());
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
        return new Grid(5, 5, squareTypes);
    }

    public static void main(String[] args) throws IOException {
        State state = new State(0, 0, State.Direction.LEFT);
        Grid grid = createDummyGrid();
        GuiMain main = new GuiMain(grid, state);
    }
}
