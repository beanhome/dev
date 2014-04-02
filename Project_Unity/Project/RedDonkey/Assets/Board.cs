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
				 || m_aBlock[i,j] && !Ignore.AtPos(i,j))
					return false;
			}
		}
		
		return true;
	}

	public void ClearPiece(int x, int y, int w, int h)
	{
		for (int i=x ; i<x+w ; ++i)
		{
			for (int j=y ; j<y+h ; ++j)
			{
				if (i >= 0 && j >= 0 && i < m_iBlockCountX && j < m_iBlockCountY)
					m_aBlock[i,j] = false;
			}
		}
	}
	
	public void SetPiece(int x, int y, int w, int h)
	{
		if (!IsFree(x, y, w, h))
		    return;

		for (int i=x ; i<x+w ; ++i)
		{
			for (int j=y ; j<y+h ; ++j)
			{
				if (i >= 0 && j >= 0 && i < m_iBlockCountX && j < m_iBlockCountY)
					m_aBlock[i,j] = true;
			}
		}
	}

	public Vector2 GetWorldPosition(int x, int y, int w, int h)
	{
		Vector2 vOrigin = (Vector2)transform.position - m_vInnerSize * 0.5f;
		return vOrigin + ((new Vector2(x, y) + new Vector2(w, h)*0.5f) * M_fBlockSize);
	}

	public void GetBlockPosition(float x, float y, int w, int h, out int i, out int j)
	{
		Vector2 vOrigin = (Vector2)transform.position - m_vInnerSize * 0.5f;
		
		x -= m_fBlockSize * (w-1);
		y -= m_fBlockSize * (h-1);
		
		i = (int)((x - vOrigin.x) / m_fBlockSize);
		j = (int)((y - vOrigin.y) / m_fBlockSize);
	}
	
	public void GetBlockPosition(float x, float y, out int i, out int j)
	{
		GetBlockPosition (x, y, 1, 1, out i, out j);
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
		for (int i=0 ; i<m_iBlockCountX ; ++i)
		{
			for (int j=0 ; j<m_iBlockCountY ; ++j)
			{
				DrawSquare(GetWorldPosition(i, j, 1, 1), new Vector2(m_fBlockSize,m_fBlockSize)*0.9f, IsFree(i, j, 1, 1) ? Color.green : Color.red);
			}
		}
	}

	static public void DrawSquare(Vector2 pos, Vector2 size, Color col)
	{
		float xmin = pos.x - size.x *0.5f;
		float xmax = pos.x + size.x *0.5f;
		float ymin = pos.y - size.y *0.5f;
		float ymax = pos.y + size.y *0.5f;
		
		Debug.DrawLine(new Vector2(xmin, ymin), new Vector2(xmax, ymin), col, 0f, false);
		Debug.DrawLine(new Vector2(xmax, ymin), new Vector2(xmax, ymax), col, 0f, false);
		Debug.DrawLine(new Vector2(xmax, ymax), new Vector2(xmin, ymax), col, 0f, false);
		Debug.DrawLine(new Vector2(xmin, ymax), new Vector2(xmin, ymin), col, 0f, false);
	}
}
