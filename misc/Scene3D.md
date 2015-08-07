# Scene3D
A lightweight cross-platform 3d rendering library.

## Core Features
* High performance realtime 3D rendering using OpenGL-ES 2.0.
* Unified C++ code base to support Android and iOS.
* The binary file (Scene3D.so) is smaller than 2 MB.
* Static 3d model (.obj) and animated 3d models (.md2, .dae and .fbx).
* Supports common image formats (bmp, jpg, png and tga).
* Supports collision detection to enable 3d model picking from touch screen.

## Advanced Features
* Supports dynamic shadows.
* Present effects like snow, smoke and fire with particle system.
* Creates 3d scene from a flexible xml file.
* Supports desktop OS like Windows, Linux and OSX.

## 3rd-party Library Intergration
* Metaio
* Vuforia
* OpenCV
* Your library

## Android API
```Java
package com.scene3d;

import android.content.Context;
import android.content.res.AssetManager;

public class Scene3D {

	static {
		System.loadLibrary("Scene3D");
	}
	private final Context context;

	public Scene3D(Context context) {
		this.context = context;
		AssetManager amgr = context.getAssets();
		String internalDataPath = context.getFilesDir().getAbsolutePath();
		initializeFileSystem(internalDataPath, amgr);
	}

	// general
	public static native void clear();
	private native void initializeFileSystem(String jInternalDataPath, AssetManager amgr);
	public static native void resize(int width, int height);
	public static native void render();
	public static native void destroyScene();

	// node methods
	public static native long addMeshNode(String jMeshName);
	public static native long addCubeNode(float size);
	public static native long addPlaneNode(float width, float height);
	public static native long addSphereNode(float radius);
	public static native void removeNode(long nodePtr);
	public static native long getRootNode();

	public static native void setNodePosition(long nodePtr, float x, float y, float z);
	public static native void setNodeRotation(long nodePtr, float x, float y, float z);
	public static native void setNodeScale(long nodePtr, float x, float y, float z);
	public static native void setNodeVisible(long nodePtr, boolean visible);
	public static native void setNodeParent(long nodePtr, long parentPtr);

	public static void setRootNodeVisible(boolean visible)
	{
		setNodeVisible(getRootNode(), visible);
	}
	
	public static native void setNodeTextureAtLayer(long nodePtr, int textureLayer, long texturePtr);
	public static void setNodeTexture(long nodePtr, long texturePtr)
	{
		setNodeTextureAtLayer(nodePtr, 0, texturePtr);
	}
	
	public static native void setNodeAnimationFps(long nodePtr, float fps);
	public static native void setNodeAnimation(long nodePtr, String jAnimationName);
	public static native void setNodeAnimationIndex(long nodePtr, int index);
	public static native void setNodeAnimationStartEnd(long nodePtr, int start, int end);
	public static native void setNodeAnimationLoop(long nodePtr, boolean isLoop);
	// interaction methods
	public static long pickNodeFromScreen(float x, float y)
	{
		return pickNodeFromScreen((int)x, (int)y);
	}
	
	public static native long pickNodeFromScreen(int x, int y);
	
	// matrix methods
	public static native void setNodeModelMatrix(long nodePtr, float[] jMatrix);
	public static native void setViewMatrix(float[] jMatrix);
	public static native void setProjectionMatrix(float[] jMatrix);

	// light methods
	public static native void addPointLight(float lightRadius);
	
	// texture methods
	public static native long addTexture(int width, int height);
	public static native long getTexture(String jFileName);
	public static native long addFullScreenTextureNode(long texturePtr, int rotationType);
	public static native void updateTexture(long texturePtr, byte[] jImageData);
	public static native void drawFullScreenTexture(long texturePtr, int rotationType);
	public static native void writeTexture(long texturePtr, String jFilename);
}
```

## iOS API
```C++
#pragma once

namespace Scene3D
{
    void clear();
    void resize(int width, int height);
    void render();
    void destroyScene();

    // node methods
    long addMeshNode(const char* meshName);
    long addCubeNode(float size);
    long addPlaneNode(float width, float height);
    long addSphereNode(float radius);
    void removeNode(long nodePtr);
    long getRootNode();

    void setNodePosition(long nodePtr, float x, float y, float z);
    void setNodeRotation(long nodePtr, float x, float y, float z);
    void setNodeScale(long nodePtr, float x, float y, float z);
    void setNodeVisible(long nodePtr, bool visible);
    void setNodeParent(long nodePtr, long parentPtr);

    void setRootNodeVisible(bool visible);

    void setNodeTextureAtLayer(long nodePtr, int textureLayer, long texturePtr);
    void setNodeTexture(long nodePtr, long texturePtr);

    void setNodeAnimationFps(long nodePtr, float fps);
    void setNodeAnimation(long nodePtr, const char* animationName);
    void setNodeAnimationIndex(long nodePtr, int index);
    void setNodeAnimationStartEnd(long nodePtr, int start, int end);
    void setNodeAnimationLoop(long nodePtr, bool isLoop);

    // interaction methods
    long pickNodeFromScreen(int x, int y);

    // matrix methods
    void setNodeModelMatrix(long nodePtr, float* matrix);
    void setViewMatrix(float* matrix);
    void setProjectionMatrix(float* matrix);

    // light methods
    void addPointLight(float lightRadius);

    // texture methods
    long addTexture(int width, int height);
    long getTexture(const char* fileName);
    long addFullScreenTextureNode(long texturePtr, int rotationType);
    void updateTexture(long texturePtr, char* imageData);
    void drawFullScreenTexture(long texturePtr, int rotationType);
    void writeTexture(long texturePtr, const char* filename);
}
```

## Contact
vinjn@qq.com
