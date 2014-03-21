package com.beanhome.reddonkey;

import android.content.Context;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

public class GameView extends SurfaceView implements SurfaceHolder.Callback
{
	private SurfaceHolder m_Holder = null;
	private GameThread mThread = null;

	/**
	 * Utilisé pour construire la vue en Java
	 * @param context le contexte qui héberge la vue
	 */
	public GameView(Context context)
	{
		super(context);
		init(context);
	}

	/**
	 * Utilisé pour construire la vue depuis XML sans style
	 * @param context le contexte qui héberge la vue
	 * @param attrs les attributs définis en XML
	 */
	public GameView(Context context, AttributeSet attrs)
	{
		super(context, attrs);
		init(context);
	}

	/**
	 * Utilisé pour construire la vue depuis XML avec un style
	 * @param context le contexte qui héberge la vue
	 * @param attrs les attributs définis en XML
	 * @param defStyle référence au style associé
	 */
	public GameView(Context context, AttributeSet attrs, int defStyle)
	{
		super(context, attrs, defStyle);
		init(context);
	}
	
	public void init(Context context)
	{
		m_Holder = getHolder();
		mThread = new GameThread(m_Holder, context);
		m_Holder.addCallback(this);
		setFocusable(true);
	}
	
	public void surfaceCreated(SurfaceHolder holder)
	{
		Log.d("bh", "Surface created");
		
		mThread.setRunning(true);
		mThread.start();
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		Log.d("bh", "Surface changed, width = [" + width + "], height = [" + height + "]");
		mThread.setSurfaceSize(width, height);

	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		Log.d("bh", "Surface destroyed");
		
		mThread.setRunning(false);

		boolean alive = true;
		while (alive)
		{
			try
			{
				mThread.join();
				alive = false;
			}
			catch (InterruptedException e)
			{
			}
		}
	}
	
	@Override
	public void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
	{
	    setMeasuredDimension(mThread.GetBox().GetImageWidth(), mThread.GetBox().GetImageHeight());
	}

	
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		return mThread.OnTouchEvent(event);
	}
	
	public GameData SaveGame()
	{
		GameData game = new GameData();
		mThread.Save(game);
		return game;
	}

	public void LoadGame(GameData game)
	{
		mThread.Load(game);		
	}

}