package com.beanhome.revoluzion;

import org.andengine.entity.scene.Scene;
import org.andengine.entity.sprite.Sprite;
import org.andengine.extension.physics.box2d.PhysicsConnector;
import org.andengine.extension.physics.box2d.PhysicsFactory;
import org.andengine.extension.physics.box2d.PhysicsWorld;
import org.andengine.extension.physics.box2d.util.constants.PhysicsConstants;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.vbo.VertexBufferObjectManager;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.FixtureDef;

public class Board
{
	private Sprite m_Sprite;
	private Body m_Body;
	private static final FixtureDef FIXTURE_DEF = PhysicsFactory.createFixtureDef(1, 0.5f, 0.5f);
	
	private float m_fAngle = 0.f;
	private float m_fTargetAngle = 0.f;
	private float m_fSpeed = 0.f;
	private Vector2 m_aGravity[];
	private int m_iGravId = 0;
	private Vector2 m_vGravity;


	public Board(ITextureRegion texture, VertexBufferObjectManager manager, Scene scene, PhysicsWorld physworld)
	{
		m_Sprite = new Sprite(0, 0, texture, manager);
		scene.attachChild(m_Sprite);
		
		m_Body = PhysicsFactory.createBoxBody(physworld, m_Sprite, BodyType.DynamicBody, FIXTURE_DEF);
		physworld.registerPhysicsConnector(new PhysicsConnector(m_Sprite, m_Body, true, true));

		float top = 400.f - 8.f;
		//float top = 0.f;
		
		SetPosition(400.f, 400.f + top);
		m_Sprite.setRotationCenter(m_Sprite.getWidth()*0.5f, m_Sprite.getHeight()*0.5f - top);
		
		SetAngle(0.f);
		
		m_aGravity = new Vector2[10];
		m_vGravity = new Vector2();
		for (int i=0 ; i<m_aGravity.length ; ++i)
			m_aGravity[i] = new Vector2();

		m_iGravId = 0;
	}
	
	//public Sprite GetSprite() { return m_Sprite; }
	
	public void SetPosition(float x, float y)
	{
		//m_Sprite.setPosition(x - m_Sprite.getWidth()*0.5f, y - m_Sprite.getHeight()*0.5f);
		m_Body.setTransform(x/PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT, y/PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT, 0);
	}

	public void SetAngle(float fAngle)
	{
		m_Sprite.setRotation(-fAngle);
	}
	
	public Vector2 ApplyGravity(Vector2 gravity)
	{
		m_vGravity.x *= m_aGravity.length;
		m_vGravity.y *= m_aGravity.length;

		m_vGravity.x -= m_aGravity[m_iGravId].x;
		m_vGravity.y -= m_aGravity[m_iGravId].y;
		m_vGravity.x += gravity.x;
		m_vGravity.y += gravity.y;

		m_vGravity.x /= m_aGravity.length;
		m_vGravity.y /= m_aGravity.length;

		m_aGravity[m_iGravId] = gravity;
		m_iGravId = (m_iGravId+1) % m_aGravity.length;
		
		m_fTargetAngle = (float)Math.atan2(m_vGravity.x, m_vGravity.y) * 180.f / (float)Math.PI;
		
		m_fSpeed = m_vGravity.len();
		
		return m_vGravity;
	}
	
	public void Update(float dt)
	{
		float fDelta = m_fTargetAngle - m_fAngle;
		
		if (fDelta > 180.f)
			fDelta -= 360.f;
		else if (fDelta < -180.f)
			fDelta += 360.f;
		
		float fStep = Math.signum(fDelta) * m_fSpeed * 100.f * dt;
		
		if (Math.abs(fStep) > Math.abs(fDelta))
			fStep = fDelta;
		
		m_fAngle += fStep;
		
		SetAngle(m_fAngle);
	}
	
}
