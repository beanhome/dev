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
import com.badlogic.gdx.physics.box2d.Contact;
import com.badlogic.gdx.physics.box2d.Fixture;
import com.badlogic.gdx.physics.box2d.FixtureDef;

public class Ball
{
	private Sprite m_Sprite;
	private Body m_Body;
	private static final FixtureDef FIXTURE_DEF = PhysicsFactory.createFixtureDef(1, 0.5f, 0.5f);

	public Ball(ITextureRegion texture, VertexBufferObjectManager manager, Scene scene, PhysicsWorld physworld)
	{
		m_Sprite = new Sprite(200, 200, texture, manager);
		scene.attachChild(m_Sprite);
		
		m_Body = PhysicsFactory.createCircleBody(physworld, m_Sprite, BodyType.DynamicBody, FIXTURE_DEF);
		physworld.registerPhysicsConnector(new PhysicsConnector(m_Sprite, m_Body, true, true));

		m_Body.applyLinearImpulse(new Vector2(4.f,  1.5f), new Vector2(.5f, 0.5f));
	}
	
	public final Body GetBody() { return m_Body; }
	
	public void SetPosition(float x, float y)
	{
		//m_Sprite.setPosition(x - m_Sprite.getWidth()*0.5f, y - m_Sprite.getHeight()*0.5f);
		m_Body.setTransform(x/PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT, y/PhysicsConstants.PIXEL_TO_METER_RATIO_DEFAULT, 0);
	}
	
	public void DetectContact(Fixture other, Contact contact)
	{
		Vector2 v = m_Body.getLinearVelocity();
		Vector2 n = contact.getWorldManifold().getNormal();
		
		v = v.sub(n.mul(2.f * n.dot(v)));
		
		m_Body.setLinearVelocity(v);
	}


}
