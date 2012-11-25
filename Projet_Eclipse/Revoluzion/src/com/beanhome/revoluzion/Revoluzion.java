package com.beanhome.revoluzion;

import org.andengine.engine.camera.Camera;
import org.andengine.engine.handler.IUpdateHandler;
import org.andengine.engine.options.EngineOptions;
import org.andengine.engine.options.ScreenOrientation;
import org.andengine.engine.options.resolutionpolicy.RatioResolutionPolicy;
import org.andengine.entity.primitive.Line;
import org.andengine.entity.primitive.Rectangle;
import org.andengine.entity.scene.Scene;
import org.andengine.entity.scene.background.SpriteBackground;
import org.andengine.entity.sprite.Sprite;
import org.andengine.extension.physics.box2d.PhysicsFactory;
import org.andengine.extension.physics.box2d.PhysicsWorld;
import org.andengine.input.sensor.acceleration.AccelerationData;
import org.andengine.input.sensor.acceleration.IAccelerationListener;
import org.andengine.opengl.texture.TextureOptions;
import org.andengine.opengl.texture.atlas.bitmap.BitmapTextureAtlas;
import org.andengine.opengl.texture.atlas.bitmap.BitmapTextureAtlasTextureRegionFactory;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.vbo.VertexBufferObjectManager;
import org.andengine.ui.activity.SimpleBaseGameActivity;

import android.util.Log;

import com.badlogic.gdx.math.Vector2;
import com.badlogic.gdx.physics.box2d.BodyDef.BodyType;
import com.badlogic.gdx.physics.box2d.Contact;
import com.badlogic.gdx.physics.box2d.ContactImpulse;
import com.badlogic.gdx.physics.box2d.ContactListener;
import com.badlogic.gdx.physics.box2d.FixtureDef;
import com.badlogic.gdx.physics.box2d.Manifold;

public class Revoluzion extends SimpleBaseGameActivity implements IAccelerationListener
{
	private static final int CAMERA_WIDTH = 800;
	private static final int CAMERA_HEIGHT = 800;
	
	private ITextureRegion m_Background;
	private ITextureRegion m_BoardTexture;
	private ITextureRegion m_BallTexture;
	private ITextureRegion m_Brick;
	private BitmapTextureAtlas mBitmapTextureAtlas;
	
	private Board m_Board;
	private Ball m_Ball;
	
	
	private Line m_oLine;
	
	private PhysicsWorld mPhysicsWorld;
	
	@Override
	public EngineOptions onCreateEngineOptions()
	{
		final Camera camera = new Camera(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT);

		return new EngineOptions(true, ScreenOrientation.LANDSCAPE_FIXED, new RatioResolutionPolicy(CAMERA_WIDTH, CAMERA_HEIGHT), camera);
	}

	@Override
	protected void onCreateResources()
	{
		mBitmapTextureAtlas = new BitmapTextureAtlas(this.getTextureManager(), 1024, 1024, TextureOptions.BILINEAR);
        m_Background = BitmapTextureAtlasTextureRegionFactory.createFromAsset(mBitmapTextureAtlas, this, "gfx/back.png", 0, 0);
        m_BoardTexture = BitmapTextureAtlasTextureRegionFactory.createFromAsset(mBitmapTextureAtlas, this, "gfx/board.png", 812, 0);
        m_BallTexture = BitmapTextureAtlasTextureRegionFactory.createFromAsset(mBitmapTextureAtlas, this, "gfx/ball.png", 812, 32);
        m_Brick = BitmapTextureAtlasTextureRegionFactory.createFromAsset(mBitmapTextureAtlas, this, "gfx/brick_01.png", 812, 64);
        mBitmapTextureAtlas.load();
	}

	@Override
	protected Scene onCreateScene()
	{
		final Scene scene = new Scene();
		mPhysicsWorld = new PhysicsWorld(new Vector2(0, 0), false);
	
		final Sprite sprite = new Sprite(0, 0, m_Background, getVertexBufferObjectManager());
		scene.setBackground(new SpriteBackground(sprite));
	
		
		m_Board = new Board(m_BoardTexture, getVertexBufferObjectManager(), scene, mPhysicsWorld);
		m_Ball = new Ball(m_BallTexture, getVertexBufferObjectManager(), scene, mPhysicsWorld);

		m_oLine = new Line(0.f, 0.f, 0.f, 0.f, 3.f, getVertexBufferObjectManager());
		m_oLine.setColor(0.f, 0.f, 1.f);
		scene.attachChild(m_oLine);
		

		scene.registerUpdateHandler(new IUpdateHandler()
		{
			@Override
			public void onUpdate(float pSecondsElapsed)
			{
				Update(pSecondsElapsed);
			}

			@Override
			public void reset()
			{
			}
		});
		
		mPhysicsWorld.setContactListener(new ContactListener()
		{
			@Override
			public void beginContact(Contact contact)
			{
				Log.d("bh", "beginContact");
				if (contact.getFixtureA().getBody() == m_Ball.GetBody())
				{
					m_Ball.DetectContact(contact.getFixtureB(), contact);
				}
				else if (contact.getFixtureB().getBody() == m_Ball.GetBody())
				{
					m_Ball.DetectContact(contact.getFixtureA(), contact);
				}
			}

			@Override
			public void preSolve(Contact contact, Manifold oldManifold)
			{
				Log.d("bh", "preSolve");
			}
			
			@Override
			public void postSolve(Contact contact, ContactImpulse impulse)
			{
				Log.d("bh", "postSolve");
			}
			
			@Override
			public void endContact(Contact contact)
			{
				Log.d("bh", "endContact");
			}
		});
		
		final VertexBufferObjectManager vertexBufferObjectManager = this.getVertexBufferObjectManager();

		/*
		final Rectangle ground = new Rectangle(0, CAMERA_HEIGHT - 2, CAMERA_WIDTH, 2, vertexBufferObjectManager);
		final Rectangle roof = new Rectangle(0, 0, CAMERA_WIDTH, 2, vertexBufferObjectManager);
		final Rectangle left = new Rectangle(0, 0, 2, CAMERA_HEIGHT, vertexBufferObjectManager);
		final Rectangle right = new Rectangle(CAMERA_WIDTH - 2, 0, 2, CAMERA_HEIGHT, vertexBufferObjectManager);
		*/
		final Rectangle ground = new Rectangle(-32, CAMERA_HEIGHT+32, CAMERA_WIDTH+64, 2, vertexBufferObjectManager);
		final Rectangle roof = new Rectangle(-32, -32, CAMERA_WIDTH+64, 2, vertexBufferObjectManager);
		final Rectangle left = new Rectangle(-32, -32, 2, CAMERA_HEIGHT+64, vertexBufferObjectManager);
		final Rectangle right = new Rectangle(CAMERA_WIDTH+32, -32, 2, CAMERA_HEIGHT+64, vertexBufferObjectManager);


		final FixtureDef wallFixtureDef = PhysicsFactory.createFixtureDef(0, 0.5f, 0.5f);
		PhysicsFactory.createBoxBody(this.mPhysicsWorld, ground, BodyType.StaticBody, wallFixtureDef);
		PhysicsFactory.createBoxBody(this.mPhysicsWorld, roof, BodyType.StaticBody, wallFixtureDef);
		PhysicsFactory.createBoxBody(this.mPhysicsWorld, left, BodyType.StaticBody, wallFixtureDef);
		PhysicsFactory.createBoxBody(this.mPhysicsWorld, right, BodyType.StaticBody, wallFixtureDef);

		scene.attachChild(ground);
		scene.attachChild(roof);
		scene.attachChild(left);
		scene.attachChild(right);
	
		scene.registerUpdateHandler(this.mPhysicsWorld);
		
		//m_Board.ApplyForce(new Vector2(-1, 0));

		return scene;
	}
	
	@Override
	public void onResumeGame()
	{
		super.onResumeGame();

		this.enableAccelerationSensor(this);
	}

	@Override
	public void onPauseGame()
	{
		super.onPauseGame();

		this.disableAccelerationSensor();
	}



	private void Update(float fSecondsElapsed)
	{
		//m_Board.Update(fSecondsElapsed);

		/*
		m_fAngle += 100 * fSecondsElapsed;
		
		if (m_fAngle > 360.f)
			m_fAngle -= 360.f;
		
		m_Board.SetAngle(m_fAngle);
		*/
	}

	@Override
	public void onAccelerationAccuracyChanged(final AccelerationData pAccelerationData)
	{

	}

	@Override
	public void onAccelerationChanged(final AccelerationData pAccelerationData)
	{
		//Vector2 gravity = m_Board.ApplyGravity(new Vector2(pAccelerationData.getX(), pAccelerationData.getY()));
		Vector2 gravity = new Vector2(pAccelerationData.getX(), pAccelerationData.getY());
		
		m_Board.ApplyForce(new Vector2(pAccelerationData.getX()*10.f, pAccelerationData.getY()*10.f));
		
		m_oLine.setPosition(400.f,  400.f,  400.f+gravity.x*100.f, 400.f+gravity.y*100.f);
	}



}
