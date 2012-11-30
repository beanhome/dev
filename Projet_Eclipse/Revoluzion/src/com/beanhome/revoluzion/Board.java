package com.beanhome.revoluzion;

import org.andengine.entity.scene.Scene;
import org.andengine.entity.sprite.Sprite;
import org.andengine.extension.physics.box2d.PhysicsConnector;
import org.andengine.extension.physics.box2d.PhysicsFactory;
import org.andengine.extension.physics.box2d.PhysicsWorld;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.vbo.VertexBufferObjectManager;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.Body;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.joints.RevoluteJointDef;

public class Board
{
	private Sprite m_Sprite;
	private Body m_Body;
	
	public Board(ITextureRegion texture, VertexBufferObjectManager manager, Scene scene, PhysicsWorld physworld)
	{
		m_Sprite = new Sprite(400-texture.getWidth()*0.5f, 760, texture, manager);
		scene.attachChild(m_Sprite);
		
		m_Body = PhysicsFactory.createBoxBody(physworld, m_Sprite, BodyType.DynamicBody, Revoluzion.FIXT_BOARD_DEF);
		physworld.registerPhysicsConnector(new PhysicsConnector(m_Sprite, m_Body, true, true));
		
		Body Anchor = PhysicsFactory.createCircleBody(physworld, 400, 400, 10, BodyType.StaticBody, Revoluzion.FIXT_BOARD_DEF);
		
		final RevoluteJointDef revoluteJointDef = new RevoluteJointDef();
		revoluteJointDef.initialize(Anchor, m_Body, Anchor.getWorldCenter());

		physworld.createJoint(revoluteJointDef);
	}
	
	public void ApplyForce(Vector2 vForce)
	{
		m_Body.setLinearVelocity(vForce);
	}



	
}
