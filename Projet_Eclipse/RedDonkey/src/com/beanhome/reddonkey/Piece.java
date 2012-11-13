package com.beanhome.reddonkey;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;


public class Piece
{
	private int m_iWidth = 1;
	private int m_iHeight = 1;
	
	private int m_iI = 0;
	private int m_iJ = 0;
	
	private float m_fPosX;
	private float m_fPosY;
	private float m_fPreviousX;
	private float m_fPreviousY;
	
	private float m_fSpeedX;
	private float m_fSpeedY;
	
	private float m_fOffsetX;
	private float m_fOffsetY;
	
	private Bitmap m_Image;
	
	private Box m_Box;
	
	private float m_iFreeMinX;
	private float m_iFreeMinY;
	private float m_iFreeMaxX;
	private float m_iFreeMaxY;

	enum State
	{
		IDLE,
		DRAG,
		AUTO,
		FINISH
	}
	
	private State m_eState;
	
	enum DragDir
	{
		NoDir,
		Horiz,
		Verti,
	}
	
	private DragDir m_eDragDir;
	
	public Piece(Context context, int i, int j, int w, int h, int id, Box box)
	{
		m_iI = i;
		m_iJ = j;		
		m_iWidth = w;
		m_iHeight = h;
		m_Image = BitmapFactory.decodeResource(context.getResources(), id);
		m_eState = State.IDLE;
		m_Box = box;
		
		m_fPosX = m_Box.GridToScreenX(m_iI);
		m_fPosY = m_Box.GridToScreenY(m_iJ);

		m_Box.AddPiece(this);
	}
	
	public void SetPlace(int x, int y)
	{
		//m_Box.RemovePiece(this);
		
		m_iI = x;
		m_iJ = y;
		m_fPosX = m_Box.GridToScreenX(m_iI);
		m_fPosY = m_Box.GridToScreenY(m_iJ);
		
		m_Box.AddPiece(this);
	}
	
	public int getPosI() { return m_iI; }
	public int getPosJ() { return m_iJ; }
	public int getWidth() { return m_iWidth; }
	public int getHeight() { return m_iHeight; }
	
	public boolean IsFinish() { return m_eState == State.FINISH; }
	
	public void Move(float x, float y)
	{
		float newx = x - m_fOffsetX;
		float newy = y - m_fOffsetY;
		
		newx = Math.max(newx, m_iFreeMinX);
		newx = Math.min(newx, m_iFreeMaxX - m_Box.GetPieceSize()*m_iWidth);
		
		newy = Math.max(newy, m_iFreeMinY);
		newy = Math.min(newy, m_iFreeMaxY - m_Box.GetPieceSize()*m_iHeight);
		
		if (newx != m_fPosX || newy != m_fPosY)
		{
			if (m_eDragDir == DragDir.NoDir)
			{
				if (Math.abs(newx-m_fPosX) < Math.abs(newy-m_fPosY))
					m_eDragDir = DragDir.Verti;
				else
					m_eDragDir = DragDir.Horiz;
			}
			
			if (m_eDragDir == DragDir.Horiz)
				m_fPosX = newx;
			else
				m_fPosY = newy;
		}
	}
	
	public void SetState(State state)
	{
		m_eState = state;
		
		switch (state)
		{
			case IDLE:
				m_fSpeedX = 0.f;
				m_fSpeedY = 0.f;
				break;

			case AUTO:
				int newi = m_iI;
				int newj = m_iJ;
				
				//Log.d("bh", "Last coord : " + m_iI + " " + m_iJ);
				//Log.d("bh", "Speed : " + m_fSpeedX + " " + m_fSpeedY);
				
				if (Math.abs(m_fSpeedX) < 1.f && Math.abs(m_fSpeedY) < 1.f)
				{
					newi = m_Box.ScreenToGridX(m_fPosX+m_Box.GetPieceSize()/2);
					newj = m_Box.ScreenToGridY(m_fPosY+m_Box.GetPieceSize()/2);
				}
				else
				{
					if (Math.abs(m_fSpeedX) >= 1.f)
						newi = (m_fSpeedX > 0.f ? Math.min(m_iI + 1, m_Box.GetSizeX()) : Math.max(0, m_iI-1));
					else
						newj = (m_fSpeedY > 0.f ? Math.min(m_iJ + 1, m_Box.GetSizeY()) : Math.max(0, m_iJ-1));
				}
				
				//Log.d("bh", "New coord : " + newi + " " + newj);
				
				if (newi != m_iI || newj != m_iJ)
				{
					m_Box.RemovePiece(this);
					m_iI = newi;
					m_iJ = newj;
					m_Box.AddPiece(this);
				}
				break;
				
			case DRAG:
				m_fPreviousX = m_fPosX;
				m_fPreviousY = m_fPosY;
				
				// Compute free zone
				m_iFreeMinX = m_fPosX;
				m_iFreeMinY = m_fPosY;
				m_iFreeMaxX = m_fPosX + m_iWidth * m_Box.GetPieceSize();
				m_iFreeMaxY = m_fPosY + m_iHeight* m_Box.GetPieceSize();
				
				m_eDragDir = DragDir.NoDir;
				
				int i, j;
				boolean bBloc = false;
				boolean bHorizFree = false;
				boolean bVertiFree = false;
				
				j = m_iJ - 1;
				if (j >= 0)
				{
					bBloc = false;
					for (i=m_iI ; i<m_iI+m_iWidth ; ++i)
					{
						if (m_Box.getPiece(i, j) != null)
						{
							bBloc = true;
							break;
						}
					}
					if (bBloc == false)
					{
						m_iFreeMinY -= m_Box.GetPieceSize();
						bVertiFree = true;
					}
				}
				
				j = m_iJ + m_iHeight;
				if (j < m_Box.GetSizeY())
				{
					bBloc = false;
					for (i=m_iI ; i<m_iI+m_iWidth ; ++i)
					{
						if (m_Box.getPiece(i, j) != null)
						{
							bBloc = true;
							break;
						}
					}
					if (bBloc == false)
					{
						m_iFreeMaxY += m_Box.GetPieceSize();
						bVertiFree = true;
					}
				}
				
				i = m_iI - 1;
				if (i >= 0)
				{
					bBloc = false;
					for (j=m_iJ ; j<m_iJ+m_iHeight ; ++j)
					{
						if (m_Box.getPiece(i, j) != null)
						{
							bBloc = true;
							break;
						}
					}
					if (bBloc == false)
					{
						m_iFreeMinX -= m_Box.GetPieceSize();
						bHorizFree = true;
					}
				}
				
				i = m_iI + m_iWidth;
				if (i < m_Box.GetSizeX())
				{
					bBloc = false;
					for (j=m_iJ ; j<m_iJ+m_iHeight ; ++j)
					{
						if (m_Box.getPiece(i, j) != null)
						{
							bBloc = true;
							break;
						}
					}
					if (bBloc == false)
					{
						m_iFreeMaxX += m_Box.GetPieceSize();
						bHorizFree = true;
					}
				}
				
				if (bHorizFree != bVertiFree)
				{
					m_eDragDir = (bHorizFree ? DragDir.Horiz : DragDir.Verti);
				}
				
				break;
				
			case FINISH:
				break;
		}
	}
	
	public void SetState(State state, int cx, int cy)
	{
		SetState(state);

		if (state == State.DRAG)
		{
			m_fOffsetX = cx - m_fPosX;
			m_fOffsetY = cy - m_fPosY;
		}
	}
	
	public boolean Contains(int x, int y)
	{
		float minx = m_fPosX;
		float miny = m_fPosY;
		float maxx = minx + m_Box.GetPieceSize() * m_iWidth;
		float maxy = miny + m_Box.GetPieceSize() * m_iHeight;

		return (x >= minx && x < maxx && y >= miny && y < maxy);
	}
	
	public void Update(double dt)
	{
		switch (m_eState)
		{
			case IDLE:
				if (m_iWidth == 2 && m_iHeight == 2 // Big
					&& m_iI == 1 && m_iJ == 3) // End Pos
				{
					SetState(State.FINISH);
				}
				break;
				
			case DRAG:
				m_fSpeedX = (m_fPosX - m_fPreviousX) / (float)dt;
				m_fSpeedY = (m_fPosY - m_fPreviousY) / (float)dt;
				break;
			
			case AUTO:
				float x = m_Box.GridToScreenX(m_iI);
				float y = m_Box.GridToScreenY(m_iJ);
				
				if (Math.abs(m_fPosX-x) < 1.f && Math.abs(m_fPosY-y) < 1.f)
				{
					SetState(State.IDLE);
				}
				else
				{
					float fSpeed = 500.f;
				
					float fStepX = Math.signum(x-m_fPosX) * fSpeed * (float)dt; 
					float fStepY = Math.signum(y-m_fPosY) * fSpeed * (float)dt;
					m_fPosX = (fStepX > 0.f ? Math.min(m_fPosX+fStepX, x) : Math.max(m_fPosX+fStepX, x));
					m_fPosY = (fStepY > 0.f ? Math.min(m_fPosY+fStepY, y) : Math.max(m_fPosY+fStepY, y));
				}
				break;
				
			case FINISH:
				float fSpeed = 500.f;
				if (m_fPosY < m_Box.GetImageHeight() + m_iWidth * m_Box.GetPieceSize())
					m_fPosY += fSpeed * dt;
				break;
		}
	}
	
	public void Draw(Canvas canvas)
	{
		Paint paint = new Paint();
		
		switch (m_eState)
		{
			case IDLE:
				m_fPosX = m_Box.GridToScreenX(m_iI);
				m_fPosY = m_Box.GridToScreenY(m_iJ);
				canvas.drawBitmap(m_Image, m_fPosX, m_fPosY, paint);
				break;

			case AUTO:
				canvas.drawBitmap(m_Image, m_fPosX, m_fPosY, paint);
				break;
				
			case DRAG:
				canvas.drawBitmap(m_Image, m_fPosX, m_fPosY, paint);
				paint.setColor(Color.GREEN);
				paint.setStyle(Paint.Style.STROKE);
				paint.setStrokeWidth(3);
				canvas.drawRect(m_fPosX, m_fPosY, m_fPosX+m_Image.getWidth(), m_fPosY+m_Image.getHeight(), paint);
				
				/*
				paint.setColor(Color.RED);
				paint.setStyle(Paint.Style.STROKE);
				paint.setStrokeWidth(1);
				canvas.drawRect(m_iFreeMinX, m_iFreeMinY, m_iFreeMaxX, m_iFreeMaxY, paint);
				*/
				
			case FINISH:
				canvas.drawBitmap(m_Image, m_fPosX, m_fPosY, paint);
				break;
		}
		
		// test
		/*
		paint.setColor(Color.WHITE);
		paint.setTextSize(20);
		paint.setStrokeWidth(1);
		canvas.drawText("speed x: " + m_fSpeedX, 10, 20, paint);
		canvas.drawText("speed y: " + m_fSpeedY, 10, 40, paint);
		*/

	}
	
}

