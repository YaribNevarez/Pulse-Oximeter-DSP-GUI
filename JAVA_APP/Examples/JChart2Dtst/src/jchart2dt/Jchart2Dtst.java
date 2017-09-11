package jchart2dt;

import java.awt.Color;
import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.BorderLayout;

import javax.swing.JButton;
import javax.swing.border.BevelBorder;
import javax.swing.border.EtchedBorder;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import info.monitorenter.gui.chart.Chart2D;
import info.monitorenter.gui.chart.traces.Trace2DSimple;

public class Jchart2Dtst {

	private JFrame frame;
	private JPanel chart_panel;
    private Chart2D chart;
    static final int NTRACES = 2;
    private Trace2DSimple trace_0;
    private Trace2DSimple trace_1;
    private JButton btnNewButton_1;


	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Jchart2Dtst window = new Jchart2Dtst();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public Jchart2Dtst() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(400, 100, 800, 800);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		chart_panel = new JPanel();
		chart_panel.setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
		frame.getContentPane().add(chart_panel, BorderLayout.CENTER);
		
		JPanel btn_panel = new JPanel();
		btn_panel.setBorder(new BevelBorder(BevelBorder.LOWERED, null, null, null, null));
		frame.getContentPane().add(btn_panel, BorderLayout.SOUTH);
		
		JButton btnNewButton = new JButton("Clear");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.out.println("Clear");
				trace_0.removeAllPoints();
				trace_1.removeAllPoints();
			}
		});
		btn_panel.add(btnNewButton);
		
		btnNewButton_1 = new JButton("Plot");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				System.out.println("Plot");
				/////////////////////////////
				plotSinCos();
			}
		});
		btn_panel.add(btnNewButton_1);
		CreateChart();
	}


	private void CreateChart()
	{
		chart = new Chart2D();
        trace_0 = new Trace2DSimple();
        chart.addTrace(trace_0);
        trace_1 = new Trace2DSimple();
        chart.addTrace(trace_1);
        trace_0.setColor(Color.blue);  trace_0.setName("Sine");
        trace_1.setColor(Color.red);  trace_1.setName("Cosine");
        chart_panel.setLayout(new BorderLayout(0, 0));
        
        chart_panel.add(chart);
        // chart_panel.setSize(100,200);
        chart.setVisible(true);
        chart_panel.setVisible(true);
        chart_panel.repaint();	
	}
	
	private void plotSinCos()
	{
		final int NPOINTS = 50;
		final double DELTAX = 10;
		final double BAR = 1;
		int k;
		double x=0, y0, y1;
		
		//trace_0.addPoint(1.1, 2.3);
		
		for (k = 0; k < NPOINTS; k ++)
		{
			y0 = Math.cos(2.0 * Math.PI * x/((BAR+DELTAX)*NPOINTS)); 
			y1 = Math.sin(2.0 * Math.PI * x/((BAR+DELTAX)*NPOINTS));
			
			trace_1.addPoint(x, y0);
			trace_0.addPoint(x, y1);
			
			x += BAR;
			trace_1.addPoint(x, y0);
			trace_0.addPoint(x, y1);
			
			trace_1.addPoint(x, 0);
			trace_0.addPoint(x, 0);
			
			x += DELTAX;
			trace_1.addPoint(x, 0);
			trace_0.addPoint(x, 0);
		}
	}
	

}
