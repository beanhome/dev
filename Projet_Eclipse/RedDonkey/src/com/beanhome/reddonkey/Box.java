package com.beanhome.reddonkey;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.view.MotionEvent;

public class Box
{
	private Bitmap m_Image;
	private int m_iImageX;
	private int m_iImageY;
	
	private int m_iGridSizeX;
	private int m_iGridSizeY;
	
	private int m_iGridOriginX;
	private int m_iGridOriginY;
	
	private int m_iPieceSize;
	
	private int m_iGridWidth;
	private int m_iGridHeight;
	
	private Piece m_Grid[][];
	
	public Box(Context context)
	{
		m_Image = BitmapFactory.decodeResource(context.getResources(), R.drawable.base);
		
		m_iGridSizeX = 4;
		m_iGridSizeY = 5;
		
		m_iPieceSize = 96;
		
		m_iGridOriginX = 39;
		m_iGridOriginY = 37;
		
		m_iGridWidth = m_iGridSizeX * m_iPieceSize;
		m_iGridHeight = m_iGridSizeY * m_iPieceSize;
		
		m_Grid = new Piece[m_iGridSizeX][m_iGridSizeY];
	}
	
	public int GetPieceSize()
	{
		return m_iPieceSize;
	}
	
	public int GetImageWidth()
	{
		return m_Image.getWidth();
	}
	
	public int GetImageHeight()
	{
		return m_Image.getHeight();
	}
	
	public void SetImageOrigin(int x, int y)
	{
		m_iImageX = x;
		m_iImageY = y;
	}
	
	public int GridToScreenX(int i)
	{
		return m_iImageX + m_iGridOriginX + (m_iPieceSize * i);
	}
	
	public int GridToScreenY(int i)
	{
		return m_iImageY + m_iGridOriginY + (m_iPieceSize * i);
	}
	
	public int ScreenToGridX(int x)
	{
		return (x - (m_iImageX + m_iGridOriginX))/m_iPieceSize;
	}

	public int ScreenToGridY(int y)
	{
		return (y - (m_iImageY + m_iGridOriginY))/m_iPieceSize;
	}
	
	public boolean IsInGrid(int x, int y)
	{
		return (x >= m_iImageX + m_iGridOriginX
				&& x < m_iImageX + m_iGridOriginX + m_iGridWidth
				&& y >= m_iImageY + m_iGridOriginY
				&& y < m_iImageY + m_iGridOriginY + m_iGridHeight);
	}
	
	public boolean AddPiece(Piece piece)
	{
		int i = piece.getPosI();
		int j = piece.getPosJ();
		int w = piece.getWidth();
		int h = piece.getHeight();
		
		for (int k=i ; k<i+w ; ++k)
		{
			for (int l=j ; l<j+h ; ++l)
			{
				if (m_Grid[k][l] != null)
					return false;				
			}
		}

		for (int k=i ; k<i+w ; ++k)
		{
			for (int l=j ; l<j+h ; ++l)
			{
				m_Grid[k][l] = piece;				
			}
		}

		return true;		
	}
	
	public void RemovePiece(Piece piece)
	{
		int i = piece.getPosI();
		int j = piece.getPosJ();
		int w = piece.getWidth();
		int h = piece.getHeight();
		
		for (int k=i ; k<i+w ; ++k)
		{
			for (int l=j ; l<j+h ; ++l)
			{
				assert(m_Grid[k][l] == piece);
				m_Grid[k][l] = null;			
			}
		}
	}
	
	public Piece getPiece(int i, int j)
	{
		assert(i>0 && i<m_iGridSizeX);
		assert(j>0 && j<m_iGridSizeY);
		return m_Grid[i][j];
	}
	
	public void Draw(Canvas canvas)
	{
		Paint paint = new Paint();
		canvas.drawBitmap(m_Image, m_iImageX, m_iImageY, paint);
	}
	
	public void DrawDebug(Canvas canvas)
	{
		Paint paint = new Paint();
		paint.setColor(Color.WHITE);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(1);

		int ox = m_iImageX + m_iGridOriginX;
		int oy = m_iImageY + m_iGridOriginY;

		canvas.drawRect(ox, oy, ox+m_iGridWidth, oy+m_iGridHeight, paint);
		for (int i=1 ; i<m_iGridSizeX ; ++i)
			canvas.drawLine(ox+m_iPieceSize*i, oy, ox+m_iPieceSize*i, oy+m_iGridHeight, paint);			
		for (int i=1 ; i<m_iGridSizeY ; ++i)
			canvas.drawLine(ox, oy+m_iPieceSize*i, ox+m_iGridWidth, oy+m_iPieceSize*i, paint);
		
		for (int i=0 ; i<m_iGridSizeX ; ++i)
		{
			for (int j=0 ; j<m_iGridSizeY ; ++j)
			{
				if (m_Grid[i][j] != null)
				{
					int x = ox + i*m_iPieceSize + m_iPieceSize/2;
					int y = oy + j*m_iPieceSize + m_iPieceSize/2;
					canvas.drawCircle(x, y, 20, paint);
				}
			}
		}

	}
	
	public boolean OnTouchEvent(MotionEvent event)
	{
		//int i = ScreenToGridX((int)event.getX());
		//int j = ScreenToGridY((int)event.getY());

		switch (event.getAction())
		{
			/*
			case MotionEvent.ACTION_DOWN:
				m_bTouch = true;
				break;
				
			case MotionEvent.ACTION_MOVE:
				m_fTouchX = event.getX();
				m_fTouchY = event.getY();
				break;
				
			case MotionEvent.ACTION_UP:
			case MotionEvent.ACTION_CANCEL:
				m_bTouch = false;
				break;
			*/
		}
	
		return true;
	}
	

}
