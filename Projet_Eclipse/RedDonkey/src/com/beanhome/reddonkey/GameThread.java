package com.beanhome.reddonkey;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.util.Log;
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
	private double m_fCircleRadius = 0.f;
	
	private Bitmap m_Base;
	private Bitmap m_Big;
	
	GameThread(SurfaceHolder holder, Context context)
	{
		super();
		m_Holder = holder;
		m_Context = context;
		
		m_Base = BitmapFactory.decodeResource(m_Context.getResources(), R.drawable.base);
		m_Big = BitmapFactory.decodeResource(m_Context.getResources(), R.drawable.big);
	}
	
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
	}

	private void draw(Canvas canvas, double dt)
	{
		Paint paint = new Paint();
		paint.setColor(Color.WHITE);
		paint.setStyle(Paint.Style.STROKE);
		paint.setStrokeWidth(1);
		
		int cx = canvas.getWidth()/2;
		int cy = canvas.getHeight()/2;
		
		canvas.drawColor(Color.BLACK);

		float bx = (canvas.getWidth() - m_Base.getWidth())/2.f;
		float by = 0.f;
		canvas.drawBitmap(m_Base, bx, by, paint);
		
		float ox = bx + 39.f;
		float oy = by + 37.f;
		float s = 96.f;
		float ow = s * 4.f;
		float oh = s * 5.f;

		canvas.drawRect(ox, oy, ox+ow, oy+oh, paint);
		for (int i=1 ; i<4 ; ++i)
			canvas.drawLine(ox+s*i, oy, ox+s*i, oy+oh, paint);			
		for (int i=1 ; i<5 ; ++i)
			canvas.drawLine(ox, oy+s*i, ox+ow, oy+s*i, paint);			

		
		//canvas.drawBitmap(m_Big, ox, oy, paint);
		//canvas.drawBitmap(m_Big, ox+m_Big.getWidth(), oy, paint);

		//canvas.drawRect(ox, oy, ox+256.f, oy+320.f, paint);
		
		/*
		canvas.drawBitmap(m_Big,
				new Rect(0, 0, m_Big.getWidth(), m_Big.getHeight()),
				new Rect((int)ox, (int)oy, m_Big.getWidth(), m_Big.getHeight()),
				paint);
		*/
		
		
		
		m_fCircleRadius = Math.abs(Math.sin(m_fCurrentTime) * 100.f);
		
		canvas.drawCircle(cx, cy, (float)m_fCircleRadius, paint);
		
	}

}

