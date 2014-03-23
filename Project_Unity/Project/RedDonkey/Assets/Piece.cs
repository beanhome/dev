using UnityEngine;
using System.Collections;

public class Piece : MonoBehaviour
{
	public Vector2 m_vSize;
	public Vector2 m_vPosition;

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

	public bool AtPos(Vector2 pos)
	{
		return (int)pos.x >= (int)m_vPosition.x && (int)pos.x < (int)m_vPosition.x + (int)m_vSize.x
			&& (int)pos.y >= (int)m_vPosition.y && (int)pos.y < (int)m_vPosition.y + (int)m_vSize.y;
	}

	// Use this for initialization
	void Start ()
	{
		m_eState = EState.ES_Fix;
		m_Board = GameObject.Find ("Board").GetComponent<Board>();

		Vector2 vOrigin = (Vector2)m_Board.transform.position - m_Board.m_vInnerSize * 0.5f;

		Vector2 vPos = vOrigin + ((m_vPosition + m_vSize*0.5f) * m_Board.M_fBlockSize);
		transform.position = vPos;

		m_Board.SetPiece(m_vPosition, m_vSize);

		Debug.Log("Piece " + ToString() + " at " + transform.position);
	}

	Vector2 GetWorldPosition()
	{
		Vector2 vOrigin = (Vector2)m_Board.transform.position - m_Board.m_vInnerSize * 0.5f;
		return vOrigin + ((m_vPosition + m_vSize*0.5f) * m_Board.M_fBlockSize);
	}

	Vector2 GetWorldPosition(Vector2 pos)
	{
		Vector2 vOrigin = (Vector2)m_Board.transform.position - m_Board.m_vInnerSize * 0.5f;
		return vOrigin + (pos * m_Board.M_fBlockSize);
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

		if (m_Board.IsFree(m_vPosition + new Vector2(1f,0f), m_vSize, this))
			vMax.x += 1f;
		if (m_Board.IsFree(m_vPosition + new Vector2(-1f,0f), m_vSize, this))
			vMin.x -= 1f;
		if (m_Board.IsFree(m_vPosition + new Vector2(0f,1f), m_vSize, this))
			vMax.y += 1f;
		if (m_Board.IsFree(m_vPosition + new Vector2(0f,-1f), m_vSize, this))
			vMin.y -= 1f;

		DrawSquare(GetWorldPosition((m_vPosition + m_vSize*0.5f)+(vMin+vMax)*0.5f), (vMax-vMin), Color.blue);

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
