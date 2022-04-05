
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Label;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SocketClient {
	PrintWriter writer;
	static Socket sock;
	static InputStream reader;
	Scanner scan = new Scanner(System.in);
	String message = null;
	int readByteCount;

	JFrame frame;
	JFrame frame_2;
	JFrame startframe;
	JPanel panel;
	JPanel panel_2;
	// JPanel npanel;
	JPanel spanel;
	JButton select_1;
	JButton select_2;
	JButton stopButton;
	JButton mainButton;
	JButton stop2Button;
	JButton main2Button;
	JLabel a;
	JLabel b;
	JLabel c;
	JLabel d;
	JLabel e;
	JLabel f;
	JLabel g;
	JLabel h;
	JLabel a1,a11;
	JLabel b1,b11;
	JLabel c1,c11;
	JLabel d1,d11;
	JLabel e1,e11;
	JLabel f1,f11;
	JLabel g1,g11;
	JLabel h1,h11;
	JLabel sleep;
	int ax;
	int ay;
	int bx;
	int by;
	int cx;
	int cy;
	int dx;
	int dy;
	int ex;
	int ey;
	int fx;
	int fy;
	int gx;
	int gy;
	int hx;
	int hy;
	int ax1;
	int ay1;
	int bx1;
	int by1;
	int cx1;
	int cy1;
	int dx1;
	int dy1;
	int ex1;
	int ey1;
	int fx1;
	int fy1;
	int gx1;
	int gy1;
	int hx1;
	int hy1;
	int n;
	String sing;
	String[] sing2;
	private final String tree = "res/tree.png";
	private final String night = "res/night.jpg";
	private final String star = "res/star.png";
	private final String song = "res/song.png";

	public static void main(String[] args) {
		SocketClient client = new SocketClient();
		client.go();
	}

	private void go() {

		frame = new JFrame("frame");
		frame_2 = new JFrame("frame");
		startframe = new JFrame("start");

		stopButton = new JButton(new ImageIcon("res/exit.png"));
		stopButton.setBorderPainted(false);
		stopButton.setFocusPainted(false);
		stopButton.setContentAreaFilled(false);
		stopButton.setBounds(830, 550, 50, 50);
		stopButton.addActionListener(new StopListener());

		mainButton = new JButton(new ImageIcon("res/main.png"));
		mainButton.setBorderPainted(false);
		mainButton.setFocusPainted(false);
		mainButton.setContentAreaFilled(false);
		mainButton.setBounds(770, 550, 50, 50);
		mainButton.addActionListener(new MainListener());

		stop2Button = new JButton(new ImageIcon("res/exit.png"));
		stop2Button.setBorderPainted(false);
		stop2Button.setFocusPainted(false);
		stop2Button.setContentAreaFilled(false);
		stop2Button.setBounds(830, 550, 50, 50);
		stop2Button.addActionListener(new StopListener());

		main2Button = new JButton(new ImageIcon("res/main.png"));
		main2Button.setBorderPainted(false);
		main2Button.setFocusPainted(false);
		main2Button.setContentAreaFilled(false);
		main2Button.setBounds(770, 550, 50, 50);
		main2Button.addActionListener(new MainListener());

		// 선택 1

		select_1 = new JButton(new ImageIcon("res/star_1.png"));
		select_1.setBorderPainted(false);
		select_1.setFocusPainted(false);
		select_1.setContentAreaFilled(false);
		select_1.setBounds(200, 350, 130, 90);
		select_1.addActionListener(new S1Listener());

		// 선택 2
		select_2 = new JButton(new ImageIcon("res/star_2.png"));
		select_2.setBorderPainted(false);
		select_2.setFocusPainted(false);
		select_2.setContentAreaFilled(false);
		select_2.setBounds(450, 350, 130, 90);
		select_2.addActionListener(new S2Listener());

		a = new JLabel(new ImageIcon("res/a.png"));
		ax = (int) (Math.random() * 800) + 1;
		ay = (int) (Math.random() * 250) + 1;
		a.setBounds(ax, ay, 50, 50);
		a.setVisible(true);

		b = new JLabel(new ImageIcon("res/b.png"));
		bx = (int) (Math.random() * 800) + 1;
		by = (int) (Math.random() * 250) + 1;
		b.setBounds(bx, by, 50, 50);
		b.setVisible(true);

		c = new JLabel(new ImageIcon("res/c.png"));
		cx = (int) (Math.random() * 800) + 1;
		cy = (int) (Math.random() * 250) + 1;
		c.setBounds(cx, cy, 50, 50);
		c.setVisible(true);

		d = new JLabel(new ImageIcon("res/d.png"));
		dx = (int) (Math.random() * 800) + 1;
		dy = (int) (Math.random() * 250) + 1;
		d.setBounds(dx, dy, 50, 50);
		d.setVisible(true);

		e = new JLabel(new ImageIcon("res/e.png"));
		ex = (int) (Math.random() * 800) + 1;
		ey = (int) (Math.random() * 250) + 1;
		e.setBounds(ex, ey, 50, 50);
		e.setVisible(true);

		f = new JLabel(new ImageIcon("res/f.png"));
		fx = (int) (Math.random() * 800) + 1;
		fy = (int) (Math.random() * 250) + 1;
		f.setBounds(fx, fy, 50, 50);
		f.setVisible(true);

		g = new JLabel(new ImageIcon("res/g.png"));
		gx = (int) (Math.random() * 800) + 1;
		gy = (int) (Math.random() * 250) + 1;
		g.setBounds(gx, gy, 50, 50);
		g.setVisible(true);

		h = new JLabel(new ImageIcon("res/h.png"));
		hx = (int) (Math.random() * 800) + 1;
		hy = (int) (Math.random() * 250) + 1;
		h.setBounds(hx, hy, 50, 50);
		h.setVisible(true);

		a1 = new JLabel(new ImageIcon("res/h.png"));
		ax1 = (int) (Math.random() * 800) + 1;
		ay1 = (int) (Math.random() * 250) + 1;
		a1.setBounds(ax1, ay1, 50, 50);
		a1.setVisible(true);

		b1 = new JLabel(new ImageIcon("res/e.png"));
		bx1 = (int) (Math.random() * 800) + 1;
		by1 = (int) (Math.random() * 250) + 1;
		b1.setBounds(bx1, by1, 50, 50);
		b1.setVisible(true);

		c1 = new JLabel(new ImageIcon("res/g.png"));
		cx1 = (int) (Math.random() * 800) + 1;
		cy1 = (int) (Math.random() * 250) + 1;
		c1.setBounds(cx, cy, 50, 50);
		c1.setVisible(true);

		d1 = new JLabel(new ImageIcon("res/a.png"));
		dx1 = (int) (Math.random() * 800) + 1;
		dy1 = (int) (Math.random() * 250) + 1;
		d1.setBounds(dx1, dy1, 50, 50);
		d1.setVisible(true);

		e1 = new JLabel(new ImageIcon("res/c.png"));
		ex1 = (int) (Math.random() * 800) + 1;
		ey1 = (int) (Math.random() * 250) + 1;
		e1.setBounds(ex1, ey1, 50, 50);
		e1.setVisible(true);

		f1 = new JLabel(new ImageIcon("res/b.png"));
		fx1 = (int) (Math.random() * 800) + 1;
		fy1 = (int) (Math.random() * 250) + 1;
		f1.setBounds(fx1, fy1, 50, 50);
		f1.setVisible(true);

		g1 = new JLabel(new ImageIcon("res/f.png"));
		gx1 = (int) (Math.random() * 800) + 1;
		gy1 = (int) (Math.random() * 250) + 1;
		g.setBounds(gx1, gy1, 50, 50);
		g.setVisible(true);

		h1 = new JLabel(new ImageIcon("res/d.png"));
		hx1 = (int) (Math.random() * 800) + 1;
		hy1 = (int) (Math.random() * 250) + 1;
		h1.setBounds(hx1, hy1, 50, 50);
		h1.setVisible(true);

		a11 = new JLabel(new ImageIcon("res/a11.png"));
		a11.setBounds(50, 450, 100, 100);
		a11.setVisible(false);
		
		b11 = new JLabel(new ImageIcon("res/b11.png"));
		b11.setBounds(150, 450, 100, 100);
		b11.setVisible(false);

		c11 = new JLabel(new ImageIcon("res/c11.png"));
		c11.setBounds(250, 450, 100, 100);
		c11.setVisible(false);

		d11 = new JLabel(new ImageIcon("res/d11.png"));
		d11.setBounds(350, 450, 100, 100);
		d11.setVisible(false);

		e11 = new JLabel(new ImageIcon("res/e11.png"));
		e11.setBounds(450, 450, 100, 100);
		e11.setVisible(false);

		f11 = new JLabel(new ImageIcon("res/f11.png"));
		f11.setBounds(550, 450, 100, 100);
		f11.setVisible(false);

		g11 = new JLabel(new ImageIcon("res/g11.png"));
		g11.setBounds(650, 450, 100, 100);
		g11.setVisible(false);

		h11 = new JLabel(new ImageIcon("res/h11.png"));
		h11.setBounds(750, 450, 100, 100);
		h11.setVisible(true);

		sleep = new JLabel(new ImageIcon("res/sleep.png"));
		sleep.setBounds(280, 450, 350, 100);
		sleep.setVisible(false);
		
		spanel = new SBackPanel();
		spanel.add(select_1);
		spanel.add(select_2);
		spanel.setLayout(null);
		spanel.setVisible(true);

		panel = new BackPanel();
		panel.setLayout(null);
		panel.add(stopButton);
		panel.add(mainButton);

		panel_2 = new Back_2Panel();
		panel_2.setLayout(null);
		panel_2.add(stop2Button);
		panel_2.add(main2Button);
		panel_2.add(a);
		panel_2.add(b);
		panel_2.add(c);
		panel_2.add(d);
		panel_2.add(e);
		panel_2.add(f);
		panel_2.add(g);
		panel_2.add(h);
		panel_2.add(a1);
		panel_2.add(b1);
		panel_2.add(c1);
		panel_2.add(d1);
		panel_2.add(e1);
		panel_2.add(f1);
		panel_2.add(g1);
		panel_2.add(h1);
		panel_2.add(a11);
		panel_2.add(b11);
		panel_2.add(c11);
		panel_2.add(d11);
		panel_2.add(e11);
		panel_2.add(f11);
		panel_2.add(g11);
		panel_2.add(h11);
		panel_2.add(sleep);
		/*
		 * npanel = new NBackPanel(); npanel.setLayout(null); npanel.setVisible(false);
		 */

		startframe.add(spanel);
		startframe.setSize(800, 650);
		startframe.setBackground(Color.white);
		startframe.setVisible(true);

		frame_2.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// frame_2.add(npanel);
		frame_2.add(panel_2);
		frame_2.setSize(900, 650);
		frame_2.setVisible(false);
		frame_2.setBackground(Color.WHITE);

		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// frame.add(npanel);
		frame.add(panel);
		frame.setSize(900, 650);
		frame.setVisible(false);
		frame.setBackground(Color.WHITE);

		try {
			// sock = new Socket("220.69.203.19", 8081);
			sock = new Socket("127.0.0.1", 8081);
			reader = sock.getInputStream();
			writer = new PrintWriter(sock.getOutputStream(), true);
		} catch (Exception ex11) {
			ex11.printStackTrace();
		}
		//
		// writer.println("1");
		byte[] data = new byte[100];

		for (;;) {
			try {
				reader.read(data, 0, data.length); // 받은 데이터를 넣어주어 읽음, 0번째 위치부터 length까지

				for (int i = 0; i < 100000000; i++);

				writer.println("0");

				a.setVisible(false);
				b.setVisible(true);
				c.setVisible(false);
				d.setVisible(true);
				e.setVisible(false);
				f.setVisible(true);
				g.setVisible(false);
				h.setVisible(true);
				a1.setVisible(true);
				b1.setVisible(false);
				c1.setVisible(true);
				d1.setVisible(false);
				e1.setVisible(true);
				f1.setVisible(false);
				g1.setVisible(true);
				h1.setVisible(false);

				sing = new String(data);
				sing2 = sing.split("");
				n = (int) Double.parseDouble(sing2[0]);
				System.out.println(n);
				if (n == 0) {
					writer.println("0");
					continue;
				}
				if (n == 1) {
					sleep.setVisible(false);
					a11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					a11.setVisible(false);
				}
				if (n == 2) {
					sleep.setVisible(false);
					b11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					b11.setVisible(false);
				}
				if (n == 3) {
					sleep.setVisible(false);
					c11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					c11.setVisible(false);
				}
				if (n == 4) {
					sleep.setVisible(false);
					d11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					d11.setVisible(false);
				}
				if (n == 5) {
					sleep.setVisible(false);
					e11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					e11.setVisible(false);
				}
				if (n == 6) {
					sleep.setVisible(false);
					f11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					f11.setVisible(false);
				}
				if (n == 7) {
					sleep.setVisible(false);
					g11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					g11.setVisible(false);
				}
				if (n == 8) {
					sleep.setVisible(false);
					h11.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
					h11.setVisible(false);
				}
				if (n == 9) {
					sleep.setVisible(true);
					for (int i = 0; i < 100000000; i++);
					for (int i = 0; i < 100000000; i++);
				}
				
				
				
				System.out.println("re : " + new String(data));

				a.setVisible(true);
				b.setVisible(false);
				c.setVisible(true);
				d.setVisible(false);
				e.setVisible(true);
				f.setVisible(false);
				g.setVisible(true);
				h.setVisible(false);
				a1.setVisible(false);
				b1.setVisible(true);
				c1.setVisible(false);
				d1.setVisible(true);
				e1.setVisible(false);
				f1.setVisible(true);
				g1.setVisible(false);
				h1.setVisible(true);

			} catch (Exception e) {
				try {
					reader.close();
					writer.close();
					sock.close();
					break;
				} catch (IOException iex) {
					break;
				} // catch
			} // catch
		} // for
	}// go

	public class BackPanel extends JPanel {
		public void paintComponent(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;
			ImageIcon back = new ImageIcon(song);
			g2d.drawImage(back.getImage(), 0, 0, 870, 620, this);

			// ImageIcon end = new ImageIcon("/res/엔딩화면끝.png");
			// g2d.drawImage(end.getImage(),0,47,705,655,null);
		}
	}// BackPanel close

	public class Back_2Panel extends JPanel {
		public void paintComponent(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;
			ImageIcon back = new ImageIcon(night);
			g2d.drawImage(back.getImage(), 0, 0, 890, 620, this);

			// ImageIcon end = new ImageIcon("/res/엔딩화면끝.png");
			// g2d.drawImage(end.getImage(),0,47,705,655,null);
		}
	}// BackPanel close

	public class NBackPanel extends JPanel {
		public void paintComponent(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;
			ImageIcon back = new ImageIcon(night);
			g2d.drawImage(back.getImage(), 0, 0, 870, 620, this);

			// ImageIcon end = new ImageIcon("/res/엔딩화면끝.png");
			// g2d.drawImage(end.getImage(),0,47,705,655,null);
		}
	}// NBackPanel close

	public class SBackPanel extends JPanel {
		public void paintComponent(Graphics g) {
			Graphics2D g2d = (Graphics2D) g;
			ImageIcon back = new ImageIcon(star);
			g2d.drawImage(back.getImage(), 0, 0, 800, 620, this);
		}
	}// SBackPanel close

	private class S1Listener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			startframe.dispose();
			frame.setVisible(true);
		}
	}// S1Listener close

	private class S2Listener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			startframe.dispose();
			frame_2.setVisible(true);
		}
	}// S1Listener close

	private class StopListener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			System.exit(0);
		}
	}// StopListener close

	private class MainListener implements ActionListener {
		public void actionPerformed(ActionEvent ev) {
			frame.dispose();
			frame_2.dispose();
			startframe.setVisible(true);
		}
	}// StopListener close
}// SocketClient