package com.beanhome.reddonkey;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;

public class MainActivity extends Activity
{
	private GameView m_View = null;
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		m_View = new GameView(this);
		setContentView(m_View);
		
		GameData data = (GameData) getLastNonConfigurationInstance();
	    if(data != null)
	    {
	    	m_View.LoadGame(data);
	    }
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	@Override
	public Object onRetainNonConfigurationInstance()
	{
	    GameData data = m_View.SaveGame();
	    return data;
	}
}
