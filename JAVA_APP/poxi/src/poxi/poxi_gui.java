package poxi;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.Iterator;
import java.util.Locale;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.BevelBorder;
import javax.swing.border.EtchedBorder;

import info.monitorenter.gui.chart.Chart2D;
import info.monitorenter.gui.chart.ITracePoint2D;
import info.monitorenter.gui.chart.pointpainters.PointPainterDisc;
import info.monitorenter.gui.chart.traces.Trace2DSimple;

import jssc.*;

public class poxi_gui {
	private JFrame frame;
	
	private final int        numOfTracesPerChart = 2;
	private final int        numOfCharts = 5;
	private JPanel []        chart_panel;
    private Chart2D []       chart;
    private Trace2DSimple [] trace;
    
    JLabel infoLabel;

    private JButton btnNewButton_1;
    
    private boolean plot_flag = false;

    private JButton btnConnect;
    private JButton btnDisconnect;
    private JButton btnSave;
    private String     portName;
    private SerialPort serialPort;
    
    private byte   serial_buffer[];
    private final byte serial_frameSignature = (byte) 0x5A;
    private int   serial_length;
    private byte   serial_crc;
    private int    serial_index;
    private boolean serial_frame_flag;
    
    private final int serial_DBSize = 16;
    private final int serial_CMDClearAll = 0;
    private final int serial_CMDBufferTrace = 1;
    private final int serial_CMDSetVisibleTrace = 2;
    private final int serial_CMDSetSTimeTrace = 3;
    private final int serial_CMDSetTimeTrace = 4;
    private final int serial_CMDTextMsg = 5;
    
    private double [] serial_STimeTrace;
    private double [] serial_TimeTrace;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) 
	{
		EventQueue.invokeLater
		(
			new Runnable()
				{
					public void run()
					{
						try {
								poxi_gui window = new poxi_gui();
								window.frame.setVisible(true);
							}
							catch (Exception e)
							{
								e.printStackTrace();
							}
					}
				}
		);
	}

	/**
	 * Create the application.
	 */
	public poxi_gui()
	{
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize()
	{
		frame = new JFrame();
		frame.setBounds(400, 100, 800, 800);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout((LayoutManager) new BoxLayout(frame.getContentPane(), BoxLayout.PAGE_AXIS));
		
		chart_panel = new JPanel [numOfCharts];

		for (int p = 0; p < numOfCharts; p ++)
		{
			chart_panel[p] = new JPanel();
			chart_panel[p].setBorder(new EtchedBorder(EtchedBorder.LOWERED, null, null));
			frame.getContentPane().add(chart_panel[p]);
		}
		
		//////////////////////////////////////
		JPanel info_panel = new JPanel();
		info_panel.setBorder(new BevelBorder(BevelBorder.LOWERED, null, null, null, null));
		frame.getContentPane().add(info_panel, BorderLayout.SOUTH);
		
		infoLabel = new JLabel("Information Panel");
		infoLabel.setFont(new Font ("Dialog", Font.PLAIN, 18));;
		info_panel.add(infoLabel);
		//////////////////////////////////////

		
		JPanel btn_panel = new JPanel();
		btn_panel.setBorder(new BevelBorder(BevelBorder.LOWERED, null, null, null, null));
		frame.getContentPane().add(btn_panel, BorderLayout.SOUTH);
		
		JButton btnNewButton = new JButton("Clear signal");
		btnNewButton.addActionListener
		(
			new ActionListener()
			{
				public void actionPerformed(ActionEvent arg0)
				{
					clearChart(0xff);
				}
			}
		);
		
		btn_panel.add(btnNewButton);
		
		btnNewButton_1 = new JButton("Sample signal");
		btnNewButton_1.addActionListener
		(
			new ActionListener()
			{
				public void actionPerformed(ActionEvent arg0)
				{
					System.out.println("Plot data");
					/////////////////////////////
					plot_flag = !plot_flag;
					
					if (plot_flag)
					{
						btnNewButton_1.setText("Stop sampling");
						btnNewButton_1.setForeground(Color.RED);
					}
					else
					{
						btnNewButton_1.setText("Start sampling");
						btnNewButton_1.setForeground(Color.BLUE);
					}
				}
			}
		);
		
		btn_panel.add(btnNewButton_1);
		
		//////////////////////////////////////
		
		String com_names [] = SerialPortList.getPortNames();
		
		for (int i = 0; i < com_names.length; i ++)
		{
			JButton btnCom = new JButton(com_names[i]);
			btnCom.addActionListener
			(
				new ActionListener()
				{
					public void actionPerformed(ActionEvent arg0)
					{
						System.out.println(arg0.getActionCommand().toString());
						portName=arg0.getActionCommand().toString();
						
						if (serialPort != null)
						{
							btnConnect.setEnabled(!serialPort.isOpened());
							btnDisconnect.setEnabled(serialPort.isOpened());
						}
						else
						{
							btnConnect.setEnabled(true);
						}
						
						btnConnect.setText("Connect " + portName);
					}
				}
			);
			
			btn_panel.add(btnCom);
		}
		
		//////////////////////////////////////
		btnConnect = new JButton("Connect");
		btnConnect.setEnabled(false);
		btnConnect.addActionListener
		(
			new ActionListener()
			{
				class PortReader implements SerialPortEventListener
				{
				    public void serialEvent(SerialPortEvent event) 
				    {
				    	System.out.println("Length: " + event.getEventValue());
				        if(event.isRXCHAR() && event.getEventValue() > 0)
				        {
				            try
				            {
				            	int data_index;
				            	int selTrace = 0;
				            	double value = 0;
				            	
				            	byte data[] = serialPort.readBytes(event.getEventValue());
				            	
				            	data_index = 0;
				            	while (data_index < data.length)
				            	{
					            	if (serial_index == 0)
					            	{
					            		while ((data_index < data.length) && (data[data_index] != serial_frameSignature)) data_index ++;
					            		
					            		if ((data_index < data.length) && (data[data_index] == serial_frameSignature)) {serial_index ++; data_index ++;}
					            	}
					            	
					            	if ((serial_index == 1) && (data_index < data.length) )
				            		{
				            			serial_length = 0xFF&((int)data[data_index++]);
				            			serial_buffer = new byte[serial_length + 3];
				            			serial_buffer[0] = serial_frameSignature;
				            			serial_buffer[1] = (byte)(0xFF & serial_length); 
	
					            		serial_index = 2;
				            		}
					            	
					            	if (serial_index >= 2)
					            	{
						            	while (((serial_index - 2) < serial_length) && (data_index < data.length))
						            		serial_buffer[serial_index++] = data[data_index++];
						            	
						            	if (serial_index - 2 == serial_length)
						            	{
						            		if (data_index < data.length)
						            		{
						            			serial_crc = data[data_index];
						            			byte crc = 0;
						            			for (int i = 0; i < serial_length; i ++) crc += serial_buffer[i + 2];
						            			
						            			serialPort.writeByte((byte) (serial_crc + serial_length));
						            			serial_frame_flag = serial_crc == crc;
						            			serial_index = 0;
						            			serial_length = 0;
						            		}
						            	}
					            	}
					            	
					            	if (serial_frame_flag && (4 <= serial_buffer.length))
					            	{
					            		serial_frame_flag = false;
					            		
					            		selTrace = 0xFF & serial_buffer[3];
					            		if (selTrace == 0xFF || selTrace < (numOfCharts * numOfTracesPerChart))
				            			switch (serial_buffer[2])
				            			{
				            			case serial_CMDClearAll:
				            				System.out.printf("SClear %d\n", serial_buffer[3]);
				            				if (plot_flag)
				            				clearChart(serial_buffer[3]);
				            				break;
				            			case serial_CMDBufferTrace:
				            				System.out.printf("SPlot %d\n", serial_buffer[3]);
				            				if (plot_flag)
				            				if (13 <= serial_buffer.length)
				            				{
				            					int k = 0;
							            		long data_long = 0;
							            		int array_length = serial_buffer[4];

							            		if (array_length <= serial_DBSize)
				            					while(k < array_length)
					            				{
						            				data_long = 0;
						            				for (int j = 0; j < 8; j++)
						            				{
						            					data_long |= (long)((0xFF&((long)serial_buffer[(5+j) + 8*k])) << (8*j));
						            				}
						            				value = Double.longBitsToDouble(data_long);
						            				
								                	if (selTrace == 0xFF)
								                	{
									                	for (int t = 0; t < (numOfCharts * numOfTracesPerChart); t ++)
									                	{
									                		trace[t].addPoint(serial_TimeTrace[t], value);
										                	serial_TimeTrace[t]+=serial_STimeTrace[t];
									                	}
								                	}
								                	else
								                	{
								                		trace[selTrace].addPoint(serial_TimeTrace[selTrace], value);
									                	serial_TimeTrace[selTrace]+=serial_STimeTrace[selTrace];
								                	}
									                k ++;
					            				}
				            				}
				            				break;
				            			case serial_CMDSetVisibleTrace:
				            				System.out.printf("SVisible %d = %d\n", serial_buffer[3], serial_buffer[4]);
				            				if (serial_buffer.length == 6)
				            				{
							                	if (selTrace == 0xFF)
							                	{
								                	for (int t = 0; t < (numOfCharts * numOfTracesPerChart); t ++)
								                	{
								                		trace[t].setVisible(serial_buffer[4]>0);
								                	}
							                	}
							                	else
							                	{
							                		trace[selTrace].setVisible(serial_buffer[4]>0);
							                	}
				            				}
				            				break;
				            			case serial_CMDSetSTimeTrace:
				            				System.out.printf("SSTime %d", serial_buffer[3]);
				            				if (serial_buffer.length == 13)
				            				{
					            				long data_long = 0;
					            				for (int j = 0; j < 8; j++)
					            				{
					            					data_long |= (long)((0xFF&((long)serial_buffer[4+j])) << (8*j));
					            				}
					            				value = Double.longBitsToDouble(data_long);
					            				
							                	if (selTrace == 0xFF)
							                	{
								                	for (int t = 0; t < (numOfCharts * numOfTracesPerChart); t ++)
								                	{
								                		serial_STimeTrace[t] = value;
								                	}
							                	}
							                	else
							                	{
							                		serial_STimeTrace[selTrace] = value;
							                	}

					            				System.out.printf(" %f\n",value);
				            				}
				            				break;
				            			case serial_CMDSetTimeTrace:
				            				System.out.printf("STime %d", serial_buffer[3]);
				            				if (serial_buffer.length == 13)
				            				{
					            				long data_long = 0;
					            				for (int j = 0; j < 8; j++)
					            				{
					            					data_long |= (long)((0xFF&((long)serial_buffer[4+j])) << (8*j));
					            				}
					            				value = Double.longBitsToDouble(data_long);
					            				
							                	if (selTrace == 0xFF)
							                	{
								                	for (int t = 0; t < (numOfCharts * numOfTracesPerChart); t ++)
								                	{
								                		serial_TimeTrace[t] = value;
								                	}
							                	}
							                	else
							                	{
							                		serial_TimeTrace[selTrace] = value;
							                	}

					            				System.out.printf(" %f\n",value);
				            				}
				            				break;
				            			case serial_CMDTextMsg:
				            				System.out.printf("STextMsg id = %d", serial_buffer[3]);
				            				if (serial_buffer[4] < serial_buffer.length)
				            				{
				            					char [] msg = new char [serial_buffer[4]];
				            					
				            					for (int i = 0; i < serial_buffer[4]; i ++)
				            						msg[i] =(char) serial_buffer[5+i];
				            					
				            					infoLabel.setText(String.copyValueOf(msg));

				            					System.out.printf("Msg = %s\n", msg);
				            				}
				            				break;
				            				default:
				            			}
					            	}
				            	}
				            }
				            catch (SerialPortException ex)
				            {
				                System.out.println("PortReader, Error: " + ex);
				            }
				        }
				    }
				}
				
				public void actionPerformed(ActionEvent arg0)
				{
					System.out.println("Connect " + portName);
					
					serialPort = new SerialPort(portName);
					
					try
					{
						serialPort.openPort();
						serialPort.setParams(SerialPort.BAUDRATE_115200,
											 SerialPort.DATABITS_8,
											 SerialPort.STOPBITS_1,
											 SerialPort.PARITY_NONE);
						serialPort.setFlowControlMode(SerialPort.FLOWCONTROL_RTSCTS_IN | SerialPort.FLOWCONTROL_RTSCTS_OUT);
						
						serialPort.addEventListener(new PortReader(), SerialPort.MASK_RXCHAR);
					}
					catch (SerialPortException ex)
					{
						System.out.println("Exception: " + ex.toString());
					}
					
					btnConnect.setEnabled(!serialPort.isOpened());
					btnDisconnect.setEnabled(serialPort.isOpened());
				}
			}
		);
		
		btn_panel.add(btnConnect);
		//////////////////////////////////////
		btnDisconnect = new JButton("Disconnect");
		btnDisconnect.setEnabled(false);
		btnDisconnect.addActionListener
		(
		new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				System.out.println("Disconnect");
				try
				{
					serialPort.closePort();
				}
				catch (SerialPortException e)
				{
					e.printStackTrace();
				}
				
				btnConnect.setEnabled(!serialPort.isOpened());
				btnDisconnect.setEnabled(serialPort.isOpened());
			}
		}
		);
		
		btn_panel.add(btnDisconnect);
		//////////////////////////////////////
		btnSave = new JButton("Save to file");
		//btnSave.setEnabled(false);
		btnSave.addActionListener
		(
		new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				System.out.println("Saving to file");
				
				btnSave.setEnabled(false);
				saveToFile();
				btnSave.setEnabled(true);
			}
		}
		);
		
		btn_panel.add(btnSave);
		//////////////////////////////////////
		CreateCharts();
	    serial_STimeTrace = new double [numOfCharts * numOfTracesPerChart];
	    serial_TimeTrace = new double [numOfCharts * numOfTracesPerChart];
	}
	
	private void clearChart(int selTrace)
	{
		System.out.println("Clear");
		selTrace &= 0xFF;
		
    	if (selTrace == 0xFF)
    	{
        	for (int t = 0; t < (numOfCharts * numOfTracesPerChart); t ++)
        	{
    			trace[t].removeAllPoints();
    			serial_TimeTrace[t] = 0.0;
        	}
    	}
    	else
    	{
    		trace[selTrace].removeAllPoints();
			serial_TimeTrace[selTrace] = 0.0;
    	}
  	}


	private void CreateCharts()
	{
		chart = new Chart2D [numOfCharts];
		trace = new Trace2DSimple [numOfCharts * numOfTracesPerChart];
		
    	for (int c = 0; c < numOfCharts; c ++)
    	{
			chart[c] = new Chart2D();

			for (int t = 0; t < numOfTracesPerChart; t ++)
			{
		        trace[numOfTracesPerChart*c + t] = new Trace2DSimple();
		        trace[numOfTracesPerChart*c + t].setPhysicalUnits("Magnitude", "Time (S)");
		        chart[c].addTrace(trace[numOfTracesPerChart*c + t]);
			}
	        
	        chart_panel[c].setLayout(new BorderLayout(0, 0));
	        chart_panel[c].add(chart[c]);
	        chart[c].setVisible(true);
	        chart_panel[c].setVisible(true);
	        chart_panel[c].repaint();
    	}
    	
        trace[0].setColor(Color.red);    trace[0].setName("Red light");
        trace[2].setColor(Color.red);    trace[2].setName("Red light Filtered");
        trace[4].setColor(Color.blue); trace[4].setName("Infrared light");
        trace[6].setColor(Color.blue); trace[6].setName("Infrared light Filtered");

        trace[8].setColor(Color.red);  trace[8].setName("Red light Filtered");
        trace[9].setColor(Color.blue); trace[9].setName("Infrared light Filtered");

	}
	
	private void saveToFile()
	{
		Iterator<ITracePoint2D> itPoints;
		ITracePoint2D point;
		
		Path logFile = Paths.get("poxi_adc.dat");

        try (BufferedWriter writer = Files.newBufferedWriter(logFile,
                StandardCharsets.UTF_8, StandardOpenOption.CREATE))
        {
        	itPoints = trace[0].iterator();
        	
            while (itPoints.hasNext())
            {
            	point = itPoints.next();
                writer.write(String.format(Locale.US,"%.3f, %.16f\n", point.getX(), point.getY()));
            }
        } catch (Exception e)
        {
            e.printStackTrace();
        }
	}
	
}
