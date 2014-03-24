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

	// Use this for initialization
	void Start ()
	{
		m_eState = EState.ES_Fix;
		m_Board = GameObject.Find ("Board").GetComponent<Board>();

		transform.position = m_Board.GetWorldPosition (m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);

		m_Board.SetPiece(m_iPosX, m_iPosY, m_iSizeX, m_iSizeY);

		Debug.Log("Piece " + ToString() + " at " + transform.position);
	}

	// Update is called once per frame
	void Update ()
	{
		Vector2 vMove;
		Vector2 vMin, vMax;

		//vMin = m_vPosition + m_vSize * 0.5f;
		//vMax = vMin;
		vMin = Vector2.zero;
		vMax = Vector2.zero;

		if (m_Board.IsFree(m_iPosX + 1, m_iPosY, m_iSizeX, m_iSizeY, this))
			vMax.x += 1f;
		if (m_Board.IsFree(m_iPosX - 1, m_iPosY, m_iSizeX, m_iSizeY, this))
			vMin.x -= 1f;
		if (m_Board.IsFree(m_iPosX, m_iPosY + 1, m_iSizeX, m_iSizeY, this))
			vMax.y += 1f;
		if (m_Board.IsFree(m_iPosX, m_iPosY - 1, m_iSizeX, m_iSizeY, this))
			vMin.y -= 1f;

		DrawSquare(m_Board.GetWorldPosition(m_iPosX, m_iPosY, m_iSizeX, m_iSizeY)+(vMin+vMax)*0.5f, (vMax-vMin), Color.blue);

		vMin *= m_Board.M_fBlockSize;
		vMax *= m_Board.M_fBlockSize;

		vMove = (Vector2)Camera.main.ScreenToWorldPoint(Input.mousePosition) + m_vDragOffset - (Vector2)transform.position;

		vMove.x = Mathf.Clamp(vMove.x, vMin.x, vMax.x);
		vMove.y = Mathf.Clamp(vMove.y, vMin.y, vMax.y);

		/*
		if (Mathf.Abs(vMove.x) > Mathf.Abs(vMove.y))
			vMove.y = 0f;
		else
			vMove.x = 0f;

		vMove.x = Mathf.Clamp(transform.position.x + vMove.x, vMin.x, vMax.x);
		vMove.y = Mathf.Clamp(transform.position.y + vMove.y, vMin.y, vMax.y);
		transform.position = vMove;
		*/

		switch (m_eState)
		{
			case EState.ES_Fix:
				vMove = Vector2.zero;
				break;

			case EState.ES_Stand:
				if (Mathf.Abs(vMove.x) > Mathf.Abs(vMove.y))
			    {
					vMove.y = 0f;
					m_eState = EState.ES_MoveHoriz;
				}
				else
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

		transform.position += (Vector3)vMove;
	}

	void OnMouseOver ()
	{
		DrawSquare(transform.position, collider.bounds.size, Color.green);
	}

	void DrawSquare(Vector2 pos, Vector2 size, Color col)
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
		Vector3 pos = transform.position;
		pos.y = -pos.y;
		pos = Camera.main.WorldToScreenPoint(pos);
		GUI.Label(new Rect(pos.x-30,pos.y-10,60,20), name.ToString());
	}
}
