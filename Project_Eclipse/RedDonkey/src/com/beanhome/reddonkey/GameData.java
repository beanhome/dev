package com.beanhome.reddonkey;

import java.util.Vector;

public class GameData
{
	public GameThread.State m_eState;
	
	public class Point
	{
		public int i;
		public int j;
		
		public Point(int _i, int _j) { i = _i; j = _j; }
	}
	
	public Vector<Point> m_aPos = new Vector<GameData.Point>(); 

	/*
	public GameData()
	{
		m_eState = game.GetState();
		
		for (int i=0 ; i<game.GetPieceCount() ; ++i)
		{
			m_aPos.add(new Point(game.GetPiece(i).getPosI(), game.GetPiece(i).getPosJ()));
		}
		
	}
	*/
}
