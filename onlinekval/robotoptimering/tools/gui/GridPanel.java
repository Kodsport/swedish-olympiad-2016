package gui;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;

import parser.Grid;
import parser.State;

/**
 * Created by emil on 2015-11-28.
 */
public class GridPanel extends JPanel {
    private Grid grid;
    private State state;

    public GridPanel(Grid grid, State state) {
        this.grid = grid;
        this.state = state;
    }

    @Override
    public void paint(Graphics g) {
        super.paint(g);
        int w = Math.min(getWidth() / grid.getC(),getHeight()/grid.getR());
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, w*grid.getC(), w*grid.getR());
        g.setColor(Color.BLACK);
        g.drawRect(0,0,w*grid.getC(),w*grid.getR());
        for (int r = 0; r < grid.getR(); r++) {
            for (int c = 0; c < grid.getC(); c++) {
                if (grid.getGrid()[r][c] == Grid.SquareType.BLOCKED) {
                    g.fillRect(r * w, c * w, w, w);
                }
            }
        }
        g.setColor(Color.RED);
        Polygon robot = new Polygon(new int[]{0,w/2,w},new int[]{w,0,w},3);
        g.translate(state.getX()*w,state.getY()*w);
        ((Graphics2D)g).fill(AffineTransform.getRotateInstance(state.getAngle(),w/2,w/2).createTransformedShape(robot));

    }
}
