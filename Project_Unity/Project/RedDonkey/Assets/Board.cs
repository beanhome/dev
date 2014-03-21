using UnityEngine;
using System.Collections;

public class Board : MonoBehaviour
{
	public	Vector2	m_vInnerSize;
	public	Vector2	m_vBlockCount;
	private	float	m_fBlockSize;

	public float M_fBlockSize { get { return m_fBlockSize; } }

	// Use this for initialization
	void Start ()
	{
		m_fBlockSize = m_vInnerSize.x / m_vBlockCount.x;
	}
	
	// Update is called once per frame
	void Update ()
	{
	
	}
}
