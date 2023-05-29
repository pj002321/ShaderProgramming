#pragma once

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#include "Dependencies\glew.h"

class Renderer
{
public:
	Renderer(int windowSizeX, int windowSizeY);
	~Renderer();

	bool IsInitialized();
	void DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a);
	void Class0310_Rendering();

	void DrawParticle();
	void DrawFragmentSandbox();
	void DrawAlphaClear();
	void DrawVertexSandbox();
	void DrawTextureSandbox();
	void DrawGridMesh();
	void DrawSpriteAnimation();

private:
	void Initialize(int windowSizeX, int windowSizeY);
	bool ReadFile(char* filename, std::string *target);
	void AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType);
	GLuint CompileShaders(char* filenameVS, char* filenameFS);
	void CreateVertexBufferObjects();
	void GetGLPosition(float x, float y, float *newX, float *newY);
	void Class0310();
	void CreateParticleVBO(int numParticleCount);
	void CreateTextures();
	GLuint CreatePngTexture(char* filePath, GLuint samplingMethod);
	void CreateGridMesh();
	void CreateFBOs();

	GLuint m_ParticleShader = -1;
	GLuint m_ParticleVBO = -1;
	GLuint m_ParticleVelVBO = -1;
	GLuint m_ParticleEmitTimeVBO = -1;
	GLuint m_ParticleLifeTimeVBO = -1;
	GLuint m_ParticlePeriodVBO = -1;
	GLuint m_ParticleAmpVBO = -1;
	GLuint m_ParticleValueVBO = -1;
	GLuint m_ParticleColorVBO = -1;
	GLuint m_ParticlePosColUVVBO = -1;
	GLuint m_ParticleVertexCount = -1;

	bool m_Initialized = false;
	
	unsigned int m_WindowSizeX = 0;
	unsigned int m_WindowSizeY = 0;

	GLuint m_VBORect = 0;
	GLuint m_SolidRectShader = 0;

	GLuint m_testVBO = 0;
	GLuint m_testVBO1 = 0;
	GLuint m_ColorVBO = 0;

	//for fragment sandbox
	GLuint m_FragmentSandboxShader = 0;
	GLuint m_FragmentSandboxVBO = 0;

	//for trail
	GLuint m_AlphaClearShader = 0;
	GLuint m_AlphaClearVBO = 0;

	//for vertex anim
	GLuint m_VertexSandboxShader = 0;
	GLuint m_HorizontalLineVBO = 0;
	GLuint m_HorizontalLineVertexCount = 0;

	//for Texture
	GLuint m_TextureSandboxShader = 0;
	GLuint m_TextureSandboxVBO = 0;
	GLuint m_CheckerBoardTexture = 0;

	GLuint m_RGBTexture = 0;

	GLuint m_0Texture = 0;
	GLuint m_1Texture = 0;
	GLuint m_2Texture = 0;
	GLuint m_3Texture = 0;
	GLuint m_4Texture = 0;
	GLuint m_5Texture = 0;

	GLuint m_MergedTexture = 0;
	GLuint m_ParticleTexture = 0;
	GLuint m_ExplosiveTexture = 0;

	// Flag Vertex Shader 

	GLuint m_GridMeshShader = 0;
	GLuint m_GridMeshVBO = 0;

	float m_GridMeshVertexCount = 0;
	GLuint m_TUKtexture = 0;

	// FBO
	GLuint m_AFBOTexture = 0;
	GLuint m_BFBOTexture = 0;
	GLuint m_CFBOTexture = 0;

	GLuint m_DepthRenderBuffer = 0;

	GLuint m_A_FBO = 0;

};

