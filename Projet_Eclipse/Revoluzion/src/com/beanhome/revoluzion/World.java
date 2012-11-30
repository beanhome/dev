package com.beanhome.revoluzion;

import org.andengine.entity.scene.Scene;
import org.andengine.extension.physics.box2d.PhysicsWorld;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.vbo.VertexBufferObjectManager;

public class World
{
	private Brick m_aBrick[][];
	private Wall m_aWall[];
	
	public World(ITextureRegion[] brick, ITextureRegion wall, VertexBufferObjectManager vertexBufferObjectManager, Scene scene, PhysicsWorld physicsWorld)
	{
		m_aBrick = new Brick[32][5];
		m_aWall = new Wall[32];
		
		for (int i=0 ; i<m_aBrick.length ; ++i)
		{
			for (int j=0 ; j<m_aBrick[i].length ; ++j)
			{
				m_aBrick[i][j] = new Brick(i, j, brick[j], vertexBufferObjectManager, scene, physicsWorld);
			}
		}
		
		for (int i=0 ; i<m_aWall.length ; ++i)
		{
			m_aWall[i] = new Wall(i, wall, vertexBufferObjectManager, scene, physicsWorld);
		}
	}

}
