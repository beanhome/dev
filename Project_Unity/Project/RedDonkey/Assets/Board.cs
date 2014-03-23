using UnityEngine;
using System.Collections;

public class Board : MonoBehaviour
{
	public	Vector2	m_vInnerSize;
	public	Vector2	m_vBlockCount;
	private	float	m_fBlockSize;

	private bool[,] m_aBlock;

	public float M_fBlockSize { get { return m_fBlockSize; } }

	public bool IsFree(Vector2 pos, Vector2 size)
	{
		for (int i=0 ; i<(int)size.x ; ++i)
		{
			for (int j=0 ; j<(int)size.y ; ++j)
			{
				int x = (int)pos.x + i;
				int y = (int)pos.y + j;
				if (x < 0 || y < 0 || x >= (int)m_vBlockCount.x || y >= (int)m_vBlockCount.y
				 || m_aBlock[x,y])
					return false;
			}
		}
		
		return true;
	}
	
	public bool IsFree(Vector2 pos, Vector2 size, Piece Ignore)
	{
		for (int i=0 ; i<(int)size.x ; ++i)
		{
			for (int j=0 ; j<(int)size.y ; ++j)
			{
				int x = (int)pos.x + i;
				int y = (int)pos.y + j;
				if (x < 0 || y < 0 || x >= (int)m_vBlockCount.x || y >= (int)m_vBlockCount.y
				 || m_aBlock[x,y] && !Ignore.AtPos(pos + new Vector2(i,j)))
					return false;
			}
		}
		
		return true;
	}
	
	public void SetPiece(Vector2 pos, Vector2 size)
	{
		if (!IsFree(pos, size))
		    return;

		for (int i=0 ; i<(int)size.x ; ++i)
		{
			for (int j=0 ; j<(int)size.y ; ++j)
			{
				int x = (int)pos.x + i;
				int y = (int)pos.y + j;
				m_aBlock[x,y] = true;
			}
		}
	}
	
	void Awake()
	{
		m_fBlockSize = m_vInnerSize.x / m_vBlockCount.x;
		m_aBlock = new bool[(int)m_vBlockCount.x, (int)m_vBlockCount.y];
		Debug.Log("Board " + m_fBlockSize);
	}
	
	// Use this for initialization
	void Start ()
	{

	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}
}
