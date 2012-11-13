package com.beanhome.reddonkey;

import java.util.Vector;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

class GameThread extends Thread
{
	private SurfaceHolder m_Holder = null;
	private Context m_Context = null;
	
	private int m_iWidth;
	private int m_iHeight;
	
	private boolean m_bIsRunning;
	
	private double m_fPreviousTime = 0.f;
	private double m_fCurrentTime = 0.f;
	
	private Box m_Box;
	private Vector<Piece> m_aPiece = new Vector<Piece>();
	
	/*
	private double m_fCircleRadius = 0.f;
	private boolean m_bTouch = false;
	private float m_fTouchX;
	private float m_fTouchY;
	*/
	
	enum State
	{
		IDLE,
		DRAG,
		WAIT,
		FINISH
	}
	
	private State m_eState;

	private Piece m_oDragPiece;
	
	GameThread(SurfaceHolder holder, Context context)
	{
		super();
		m_Holder = holder;
		m_Context = context;
		m_Box = new Box(context);
		m_eState = State.IDLE;
		
		m_aPiece.add(new Piece(context, 0, 0, 1, 2, R.drawable.long_01, m_Box));
		m_aPiece.add(new Piece(context, 3, 0, 1, 2, R.drawable.long_02, m_Box));
		m_aPiece.add(new Piece(context, 1, 0, 2, 2, R.drawable.big, m_Box));
		m_aPiece.add(new Piece(context, 0, 2, 1, 2, R.drawable.long_03, m_Box));
		m_aPiece.add(new Piece(context, 3, 2, 1, 2, R.drawable.long_04, m_Box));
		m_aPiece.add(new Piece(context, 1, 2, 2, 1, R.drawable.long_05, m_Box));
		m_aPiece.add(new Piece(context, 1, 3, 1, 1, R.drawable.small_01, m_Box));
		m_aPiece.add(new Piece(context, 2, 3, 1, 1, R.drawable.small_02, m_Box));
		m_aPiece.add(new Piece(context, 0, 4, 1, 1, R.drawable.small_03, m_Box));
		m_aPiece.add(new Piece(context, 3, 4, 1, 1, R.drawable.small_04, m_Box));
	}
	
	/*
	public GameThread.State GetState() { return m_eState; }
	public int GetPieceCount() { return m_aPiece.size(); }
	public Piece GetPiece(int i) { return m_aPiece.elementAt(i); }
	*/
	
	public Box GetBox() { return m_Box; }
	
	public void setSurfaceSize(int width, int height)
	{
		synchronized (m_Holder)
		{
			m_iWidth = width;
			m_iHeight = height;
		}
	}
	
	public void setRunning(boolean running)
	{
		m_bIsRunning = running;
	}
	
	@Override
	public void run()
	{
		Log.d("bh", "Game thread started");
		
		while (m_bIsRunning)
		{
			m_fPreviousTime = m_fCurrentTime;
			m_fCurrentTime = System.nanoTime() / 1000000000.0f;
			double dt = m_fCurrentTime - m_fPreviousTime;
			
			updateState(dt);
			
			Canvas canvas = null;
			try
			{
				canvas = m_Holder.lockCanvas(null);
				synchronized (m_Holder)
				{
					draw(canvas, dt);
				}
			}
			finally
			{
				if (canvas != null)
				{
					m_Holder.unlockCanvasAndPost(canvas);
				}
			}
		}

		Log.d("mg", "Game thread ended");
	}
	
	private void updateState(double dt)
	{
		for (int i=0 ; i<m_aPiece.size() ; ++i)
		{
			m_aPiece.elementAt(i).Update(dt);
			if (m_aPiece.elementAt(i).IsFinish())
				m_eState = State.FINISH;
		}
	}

	private void draw(Canvas canvas, double dt)
	{
		canvas.drawColor(Color.BLACK);
		
		int x = (canvas.getWidth() - m_Box.GetImageWidth())/2;
		int y = (canvas.getHeight() - m_Box.GetImageHeight())/2;
		
		m_Box.SetImageOrigin(x, y);
		m_Box.Draw(canvas);
		
		for (int i=0 ; i<m_aPiece.size() ; ++i)
		{
			if (m_aPiece.elementAt(i) != m_oDragPiece)
				m_aPiece.elementAt(i).Draw(canvas);	
		}
		if (m_oDragPiece != null)
			m_oDragPiece.Draw(canvas);

		//m_Box.DrawDebug(canvas);
	}

	public boolean OnTouchEvent(MotionEvent event)
	{
		if (m_eState == State.FINISH)
			return false;
		
		switch (event.getAction())
		{
			case MotionEvent.ACTION_DOWN:
				int i = m_Box.ScreenToGridX((int)event.getX());
				int j = m_Box.ScreenToGridY((int)event.getY());
				if (i<m_Box.GetSizeX() && j<m_Box.GetSizeY())
				{
					Piece piece = m_Box.getPiece(i, j);
					assert(m_eState != State.DRAG);
					assert(m_oDragPiece != null);
					if (piece != null && m_oDragPiece == null)
					{
						m_eState = State.DRAG;
						m_oDragPiece = piece;
						m_oDragPiece.SetState(Piece.State.DRAG, (int)event.getX(), (int)event.getY());
					}
				}
				break;
				
			case MotionEvent.ACTION_MOVE:
				assert(m_eState != State.IDLE);
				if (m_oDragPiece != null)
				{
					m_oDragPiece.Move((int)event.getX(), (int)event.getY());
				}
				break;
				
			case MotionEvent.ACTION_UP:
			case MotionEvent.ACTION_CANCEL:
				if (m_oDragPiece != null)
				{
					m_oDragPiece.SetState(Piece.State.AUTO);
					m_oDragPiece = null;
					m_eState = State.WAIT;
				}
				break;
		}
	
		return true;
	}
	
	public void Save(GameData data)
	{
		data.m_eState = m_eState;

		data.m_aPos.clear();
		for (int i=0 ; i<m_aPiece.size() ; ++i)
		{
			data.m_aPos.add(data.new Point(m_aPiece.elementAt(i).getPosI(), m_aPiece.elementAt(i).getPosJ()));
		}

	}

	public void Load(GameData data)
	{
		assert data.m_aPos.size() == m_aPiece.size();
		
		m_eState = data.m_eState;

		m_Box.Clear();
		for (int i=0 ; i<m_aPiece.size() ; ++i)
		{
			m_aPiece.elementAt(i).SetPlace(data.m_aPos.elementAt(i).i, data.m_aPos.elementAt(i).j);
		}
	}

}

