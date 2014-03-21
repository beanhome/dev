package com.test.beanhometest;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity
{
	//private TextView tvMain = null;
	private GameView m_View = null;
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		//setContentView(R.layout.activity_main);
		
		//tvMain = new TextView(this);
		//tvMain.setText(R.string.hello_world);
		//setContentView(tvMain);
		
		m_View = new GameView(this);
		setContentView(m_View);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu)
	{
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
}
