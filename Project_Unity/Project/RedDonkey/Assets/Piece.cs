using UnityEngine;
using System.Collections;

public class Piece : MonoBehaviour
{
	public Vector2 m_vSize;
	public Vector2 m_vPosition;

	private Board m_Board;

	// Use this for initialization
	void Start ()
	{
		m_Board = GameObject.Find ("Board").GetComponent<Board>();

		transform.position = (m_vPosition * m_Board.M_fBlockSize);

		Debug.Log("Piece " + ToString() + " at " + transform.position);
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}
}
