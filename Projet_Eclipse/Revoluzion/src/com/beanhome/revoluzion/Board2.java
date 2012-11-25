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
import com.badlogic.gdx.physics.box2d.joints.RevoluteJointDef;

public class Board2
{
	private Sprite m_Sprite;
	private Body m_Body;
	//private static final FixtureDef FIXTURE_DEF = PhysicsFactory.createFixtureDef(1, 0.5f, 0.5f);
	private static final FixtureDef FIXTURE_DEF = PhysicsFactory.createFixtureDef(1, 0.5f, 0.5f);
	
	public Board2(ITextureRegion texture, VertexBufferObjectManager manager, Scene scene, PhysicsWorld physworld)
	{
		m_Sprite = new Sprite(400-texture.getWidth()*0.5f, 778, texture, manager);
		scene.attachChild(m_Sprite);
		
		m_Body = PhysicsFactory.createBoxBody(physworld, m_Sprite, BodyType.DynamicBody, FIXTURE_DEF);
		physworld.registerPhysicsConnector(new PhysicsConnector(m_Sprite, m_Body, true, true));
		
		Body Anchor = PhysicsFactory.createCircleBody(physworld, 400, 400, 10, BodyType.StaticBody, FIXTURE_DEF);
		
		final RevoluteJointDef revoluteJointDef = new RevoluteJointDef();
		revoluteJointDef.initialize(Anchor, m_Body, Anchor.getWorldCenter());

		/*
		revoluteJointDef.enableLimit = true;
		revoluteJointDef.upperAngle = (float)Math.PI;
		revoluteJointDef.lowerAngle = (float)-Math.PI;
		
		revoluteJointDef.enableMotor = false;
		revoluteJointDef.motorSpeed = 2;
		revoluteJointDef.maxMotorTorque = 200;
		*/

		physworld.createJoint(revoluteJointDef);
	}
	
	public void ApplyForce(Vector2 vForce)
	{
		//m_Body.applyForce(vForce, m_Body.getWorldCenter());
		m_Body.setLinearVelocity(vForce);
	}



	
}
