package com.beanhome.revoluzion;

import org.andengine.entity.scene.Scene;
import org.andengine.entity.sprite.Sprite;
import org.andengine.extension.physics.box2d.PhysicsConnector;
import org.andengine.extension.physics.box2d.PhysicsFactory;
import org.andengine.extension.physics.box2d.PhysicsWorld;
import org.andengine.extension.physics.box2d.util.constants.PhysicsConstants;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.vbo.VertexBufferObjectManager;

import android.util.FloatMath;

import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.FixtureDef;

public class Brick
{
	private Scene					m_Scene;
	private PhysicsWorld			m_PhysicsWorld;

	private Sprite					m_Sprite;
	private Body					m_Body;

	private int						i, j;
	private float					m_fAngle;
	private float					x			= 0, y = 0;

	public Brick(int _i, int _j, ITextureRegion texture,
			VertexBufferObjectManager manager, Scene scene,
			PhysicsWorld physworld)
	{
		m_Scene = scene;
		m_PhysicsWorld = physworld;

		i = _i;
		j = _j;

		m_Sprite = new Sprite(0, 0, texture, manager);
		scene.attachChild(m_Sprite);

		m_Body = PhysicsFactory.createBoxBody(physworld, m_Sprite,
				BodyType.StaticBody, Revoluzion.FIXT_BRICK_DEF);
		m_Body.setUserData(this);
		physworld.registerPhysicsConnector(new PhysicsConnector(m_Sprite,
				m_Body, true, true));

		ComputePosition();
		m_Body.setTransform(x / PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT,
				y / PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT, m_fAngle);
	}

	public void ComputePosition()
	{
		m_fAngle = (float) (i * Math.PI / 16.f);
		float size[] = { 16, 17, 20, 25, 32 };
		for (int k = 1 ; k < size.length ; ++k)
			size[k] += size[k - 1];

		float dist = 200.f - size[j] + m_Sprite.getHeight() * 0.5f;

		x = FloatMath.cos(m_fAngle) * dist;
		y = FloatMath.sin(m_fAngle) * dist;

		x += 400.f;
		y += 400.f;

		m_fAngle -= Math.PI / 2;
	}

	public void Destroy()
	{
		final PhysicsConnector pPhysicsConnector = m_PhysicsWorld.getPhysicsConnectorManager().findPhysicsConnectorByShape(m_Sprite);
		m_PhysicsWorld.unregisterPhysicsConnector(pPhysicsConnector);
		m_PhysicsWorld.destroyBody(m_Body);
		m_Scene.detachChild(m_Sprite);
	}
}
