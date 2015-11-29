package gui;

import parser.Grid;
import parser.State;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;

/**
 * Created by emil on 2015-11-28.
 */
public class GridPanel extends JPanel {
    private Grid grid;
    private State state;
    private int w = 32;

    public GridPanel(Grid grid, State state) {
        this.grid = grid;
        this.state = state;
    }

    public void zoomIn() {
        if(w < 512) w *= 2;
        setPreferredSize(new Dimension(grid.getC()*w, grid.getR()*w));
        revalidate();
        repaint();
    }

    public void zoomOut() {
        if(w > 2) w /= 2;
        setPreferredSize(new Dimension(grid.getC()*w, grid.getR()*w));
        revalidate();
        repaint();
    }

    public void setGrid(Grid grid) {
        this.grid = grid;
        revalidate();
        repaint();
    }

    public void setState(State state) {
        this.state = state;
        revalidate();
        repaint();
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, w*grid.getC(), w*grid.getR());
        g.setColor(Color.BLACK);
        g.drawRect(0,0,w*grid.getC(),w*grid.getR());
        for (int r = 0; r < grid.getR(); r++) {
            for (int c = 0; c < grid.getC(); c++) {
                if (grid.getGrid()[r][c] == Grid.SquareType.BLOCKED) {
                    g.fillRect(c * w, r * w, w, w);
                }
            }
        }
        g.setColor(Color.RED);
        Polygon robot = new Polygon(new int[]{0,w/2,w},new int[]{w,0,w},3);
        g.translate(state.getCol()*w,state.getRow()*w);
        ((Graphics2D)g).fill(AffineTransform.getRotateInstance(state.getAngle(),w/2,w/2).createTransformedShape(robot));

    }
}
