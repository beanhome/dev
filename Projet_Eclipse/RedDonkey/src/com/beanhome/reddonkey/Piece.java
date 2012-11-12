package com.beanhome.reddonkey;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;


public class Piece
{
	private int m_iWidth = 1;
	private int m_iHeight = 1;
	
	private int m_iI = 0;
	private int m_iJ = 0;
	
	private int m_iPosX;
	private int m_iPosY;
	
	private int m_iOffsetX;
	private int m_iOffsetY;
	
	private Bitmap m_Image;
	
	private Box m_Box;
	
	enum State
	{
		IDLE,
		DRAG,
	}
	
	private State m_eState;
	
	public Piece(Context context, int i, int j, int w, int h, int id, Box box)
	{
		m_iI = i;
		m_iJ = j;		
		m_iWidth = w;
		m_iHeight = h;
		m_Image = BitmapFactory.decodeResource(context.getResources(), id);
		m_eState = State.IDLE;
		m_Box = box;
		
		m_iPosX = m_Box.GridToScreenX(m_iI);
		m_iPosY = m_Box.GridToScreenY(m_iJ);

		m_Box.AddPiece(this);
	}
	
	public void SetPlace(int x, int y)
	{
		m_Box.RemovePiece(this);
		
		m_iI = x;
		m_iJ = y;
		m_iPosX = m_Box.GridToScreenX(m_iI);
		m_iPosY = m_Box.GridToScreenY(m_iJ);
		
		m_Box.AddPiece(this);
	}
	
	public int getPosI() { return m_iI; }
	public int getPosJ() { return m_iJ; }
	public int getWidth() { return m_iWidth; }
	public int getHeight() { return m_iHeight; }
	
	public void Move(int x, int y)
	{
		m_iPosX = x - m_iOffsetX;
		m_iPosY = y - m_iOffsetY;
	}
	
	public void SetState(State state)
	{
		m_eState = state;
		
		if (state == State.IDLE)
		{
			m_iPosX = m_Box.GridToScreenX(m_iI);
			m_iPosY = m_Box.GridToScreenY(m_iJ);
		}
	}
	
	public void SetState(State state, int cx, int cy)
	{
		SetState(state);

		if (state == State.DRAG)
		{
			m_iOffsetX = cx - m_iPosX;
			m_iOffsetY = cy - m_iPosY;
		}
	}
	
	public boolean Contains(int x, int y)
	{
		int minx = m_iPosX;
		int miny = m_iPosY;
		int maxx = minx + m_Box.GetPieceSize() * m_iWidth;
		int maxy = miny + m_Box.GetPieceSize() * m_iHeight;

		return (x >= minx && x < maxx && y >= miny && y < maxy);
	}
	
	public void Draw(Canvas canvas)
	{
		Paint paint = new Paint();

		switch (m_eState)
		{
			case IDLE:
				m_iPosX = m_Box.GridToScreenX(m_iI);
				m_iPosY = m_Box.GridToScreenY(m_iJ);
				canvas.drawBitmap(m_Image, m_iPosX, m_iPosY, paint);
				break;
				
			case DRAG:
				canvas.drawBitmap(m_Image, m_iPosX, m_iPosY, paint);
				paint.setColor(Color.GREEN);
				paint.setStyle(Paint.Style.STROKE);
				paint.setStrokeWidth(3);
				canvas.drawRect(m_iPosX, m_iPosY, m_iPosX+m_Image.getWidth(), m_iPosY+m_Image.getHeight(), paint);
				break;
		}
	}
	
}

