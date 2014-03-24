using UnityEngine;
using System.Collections;

public class Board : MonoBehaviour
{
	public	Vector2	m_vInnerSize;
	public	int 	m_iBlockCountX;
	public	int 	m_iBlockCountY;
	private	float	m_fBlockSize;
	public	float M_fBlockSize { get { return m_fBlockSize; } }

	private bool[,] m_aBlock;

	public bool IsFree(int x, int y, int w, int h)
	{
		for (int i=x ; i<x+w ; ++i)
		{
			for (int j=y ; j<y+h ; ++j)
			{
				if (i < 0 || j < 0 || i >= m_iBlockCountX || j >= m_iBlockCountY || m_aBlock[i,j])
					return false;
			}
		}
		
		return true;
	}
	
	public bool IsFree(int x, int y, int w, int h, Piece Ignore)
	{
		for (int i=x ; i<x+w ; ++i)
		{
			for (int j=y ; j<y+h ; ++j)
			{
				if (i < 0 || j < 0 || i >= m_iBlockCountX || j >= m_iBlockCountY
				 || m_aBlock[x,y] && !Ignore.AtPos(i,j))
					return false;
			}
		}
		
		return true;
	}
	
	public void SetPiece(int x, int y, int w, int h)
	{
		if (!IsFree(x, y, w, h))
		    return;

		for (int i=x ; i<x+w ; ++i)
		{
			for (int j=y ; j<y+h ; ++j)
			{
				m_aBlock[i,j] = true;
			}
		}
	}

	public Vector2 GetWorldPosition(int x, int y, int w, int h)
	{
		Vector2 vOrigin = (Vector2)transform.position - m_vInnerSize * 0.5f;
		return vOrigin + ((new Vector2(x, y) + new Vector2(w, h)*0.5f) * M_fBlockSize);
	}
	
	void Awake()
	{
		m_fBlockSize = m_vInnerSize.x / m_iBlockCountX;
		m_aBlock = new bool[m_iBlockCountX, m_iBlockCountY];
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
