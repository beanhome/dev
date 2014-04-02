using UnityEngine;
using System.Collections;

public class Piece : MonoBehaviour
{
	public int m_iSizeX;
	public int m_iSizeY;
	public int m_iPosX;
	public int m_iPosY;

	private Board m_Board;

	private Vector2 m_vDragOffset;

	enum EState
	{
		ES_Fix,
		ES_Stand,
		ES_MoveVerti,
		ES_MoveHoriz,
	};

	private EState m_eState;

	public bool AtPos(int i, int j)
	{
		return i >= m_iPosX && i < m_iPosX + m_iSizeX && j >= m_iPosY && j < m_iPosY + m_iSizeY;
	}

	public bool IsFree()
	{
		return m_Board.IsFree(m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);
	}

	public Vector2 GetWorldPosition()
	{
		return m_Board.GetWorldPosition (m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);
	}

	public void GetBlockPosition()
	{
		m_Board.GetBlockPosition (transform.position.x + (1f-(float)m_iSizeX)*m_Board.M_fBlockSize*0.5f, transform.position.y + (1f-(float)m_iSizeY)*m_Board.M_fBlockSize*0.5f, 1, 1, out m_iPosX, out m_iPosY);
	}

	// Use this for initialization
	void Start ()
	{
		m_eState = EState.ES_Fix;
		m_Board = GameObject.Find ("Board").GetComponent<Board>();

		transform.position = GetWorldPosition();

		m_Board.SetPiece(m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);

		Debug.Log("Piece " + ToString() + " at " + transform.position);
	}

	// Update is called once per frame
	void Update ()
	{
		Vector2 vCenter, vMove;
		Vector2 vMin, vMax;

		vMin = Vector2.zero;
		vMax = Vector2.zero;

		for (int i=1 ; m_Board.IsFree(m_iPosX + i, m_iPosY, m_iSizeX, m_iSizeY, this) ; ++i)
			vMax.x += 1f;

		for (int i=1 ; m_Board.IsFree(m_iPosX - i, m_iPosY, m_iSizeX, m_iSizeY, this) ; ++i)
			vMin.x -= 1f;

		for (int i=1 ; m_Board.IsFree(m_iPosX, m_iPosY + i, m_iSizeX, m_iSizeY, this) ; ++i)
			vMax.y += 1f;

		for (int i=1 ; m_Board.IsFree(m_iPosX, m_iPosY - i, m_iSizeX, m_iSizeY, this) ; ++i)
			vMin.y -= 1f;

		vMin *= m_Board.M_fBlockSize;
		vMax *= m_Board.M_fBlockSize;

		vCenter = GetWorldPosition();

		Board.DrawSquare(vCenter+(vMin+vMax)*0.5f, (vMax-vMin), Color.blue);

		vMove = (Vector2)Camera.main.ScreenToWorldPoint(Input.mousePosition) + m_vDragOffset - (Vector2)transform.position;

		switch (m_eState)
		{
			case EState.ES_Fix:
				vMove = Vector2.zero;
				Vector2 vDestination = m_Board.GetWorldPosition(m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);
				float fDist = ((Vector2)transform.position - vDestination).magnitude;
				if (fDist > 0f)
				{
					float fSpeed = 10f;
					float fAlpha = Time.deltaTime / (fDist / fSpeed);
					transform.position = Vector3.Lerp(transform.position, vDestination, fAlpha);
				}
				break;

			case EState.ES_Stand:
				if (Mathf.Abs(vMove.x) > Mathf.Abs(vMove.y))
			    {
					vMove.y = 0f;
					m_eState = EState.ES_MoveHoriz;
				}
				else if (Mathf.Abs(vMove.x) < Mathf.Abs(vMove.y))
				{
					vMove.x = 0f;
					m_eState = EState.ES_MoveVerti;
				}
				break;

			case EState.ES_MoveHoriz:
				vMove.y = 0f;
				break;

			case EState.ES_MoveVerti:
				vMove.x = 0f;
			break;
		}

		vMove.x = Mathf.Clamp(transform.position.x + vMove.x, vCenter.x + vMin.x, vCenter.x + vMax.x);
		vMove.y = Mathf.Clamp(transform.position.y + vMove.y, vCenter.y + vMin.y, vCenter.y + vMax.y);
		transform.position = vMove;

		m_Board.ClearPiece (m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);
		GetBlockPosition ();
		//m_Board.GetBlockPosition (transform.position.x, transform.position.y, m_iSizeX, m_iSizeY, out m_iPosX, out m_iPosY);
		m_Board.SetPiece (m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);
	}

	void OnMouseOver ()
	{
		Board.DrawSquare(transform.position, collider.bounds.size, IsFree() ? Color.green : Color.red);
	}

	void OnMouseDown()
	{
		m_eState = EState.ES_Stand;
		m_vDragOffset = transform.position - Camera.main.ScreenToWorldPoint(Input.mousePosition);
	}

	void OnMouseUp()
	{
		m_eState = EState.ES_Fix;
	}

	void OnGUI()
	{
		/*
		Vector3 pos = transform.position;
		pos.y = -pos.y;
		pos = Camera.main.WorldToScreenPoint(pos);
		GUI.Label(new Rect(pos.x-30,pos.y-10,60,20), name.ToString());
		*/
	}
}
