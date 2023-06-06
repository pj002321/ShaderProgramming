#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include <assert.h>
Renderer::Renderer(int windowSizeX, int windowSizeY)
{
	Initialize(windowSizeX, windowSizeY);
	Class0310();
}


Renderer::~Renderer()
{
}

void Renderer::Initialize(int windowSizeX, int windowSizeY)
{
	//Set window size
	m_WindowSizeX = windowSizeX;
	m_WindowSizeY = windowSizeY;

	//Load shaders
	m_SolidRectShader = CompileShaders("./Shaders/SolidRect.vs", 
										"./Shaders/SolidRect.fs");
	m_ParticleShader = CompileShaders("./Shaders/Particle.vs", 
										"./Shaders/Particle.fs");
	m_FragmentSandboxShader = CompileShaders("./Shaders/FragmentSandbox.vs",
											"./Shaders/FragmentSandbox.fs");
	m_AlphaClearShader = CompileShaders("./Shaders/AlphaClear.vs",
										"./Shaders/AlphaClear.fs");
	m_VertexSandboxShader = CompileShaders("./Shaders/VertexSandbox.vs",
										"./Shaders/VertexSandbox.fs");
	
	m_TextureSandboxShader= CompileShaders("./Shaders/TextureSandBox.vs",
		"./Shaders/TextureSandBox.fs");

	/*m_VertexSandboxShader = CompileShaders("./Shaders/line.vs",
		"./Shaders/line.fs");*/

	m_MergedTexture = CompileShaders("./Shaders/TextureSandbox.vs", "./Shaders/TextureSandbox.fs");
	m_GridMeshShader = CompileShaders("./Shaders/GridMesh.vs","./Shaders/GridMesh.fs");

	//Create VBOs
	CreateVertexBufferObjects();
	
	//CreateTexture
	CreateTextures();
	
	//LoadTexture

	CreateParticleVBO(10000);
	CreateGridMesh();

	//CreateTextures
	m_RGBTexture=CreatePngTexture("RGB.png",GL_NEAREST);
	m_0Texture = CreatePngTexture("./tex0.png", GL_NEAREST);
	m_1Texture = CreatePngTexture("./tex1.png", GL_NEAREST);
	m_2Texture = CreatePngTexture("./tex2.png", GL_NEAREST);
	m_3Texture = CreatePngTexture("./tex3.png", GL_NEAREST);
	m_4Texture = CreatePngTexture("./tex4.png", GL_NEAREST);
	m_5Texture = CreatePngTexture("./tex5.png", GL_NEAREST);

	m_ParticleTexture = CreatePngTexture("./particle.png", GL_NEAREST);
	m_ExplosiveTexture = CreatePngTexture("./explosion.png", GL_NEAREST);

	m_TUKtexture = CreatePngTexture("./TUKorea.png", GL_NEAREST);

	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{

	float textureRect[]
		=
	{
		-0.5, 0.5f, 0.f,		0.f, 0.f, //x,y,z,u,v
		-0.5f, -0.5f, 0.f,		0.f, 1.f,
		0.5f, 0.5f, 0.f,		1.f, 0.f, //Triangle1
		0.5f, 0.5f, 0.f,		1.f, 0.f,
		-0.5f, -0.5f, 0.f,		0.f, 1.f,
		0.5f, -0.5f, 0.f,		1.f, 1.f //Triangle2
	};
	glGenBuffers(1, &m_TextureSandboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(textureRect), textureRect, GL_STATIC_DRAW);

	float rect[]
		=
	{
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, -1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, //Triangle1
		-1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f,  1.f / m_WindowSizeX, 1.f / m_WindowSizeY, 0.f, 1.f / m_WindowSizeX, -1.f / m_WindowSizeY, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_VBORect);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect), rect, GL_STATIC_DRAW);

	float rect1[]
		=
	{
		-1.f, -1.f, 0.f, 0.f, 1.f, //x,y,z,u,v
		-1.f, 1.f, 0.f, 0.f, 0.f,
		1.f, 1.f, 0.f, 1.f, 0.f, //Triangle1
		-1.f, -1.f, 0.f,  0.f, 1.f,
		1.f, 1.f, 0.f, 1.f, 0.f,
		1.f, -1.f, 0.f, 1.f, 1.f //Triangle2
	};

	glGenBuffers(1, &m_FragmentSandboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FragmentSandboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect1), rect1, GL_STATIC_DRAW);

	float rect2[]
		=
	{
		-1.f, -1.f, 0.f, //x,y,z
		-1.f, 1.f, 0.f, 
		1.f, 1.f, 0.f,  //Triangle1
		-1.f, -1.f, 0.f,  
		1.f, 1.f, 0.f, 
		1.f, -1.f, 0.f //Triangle2
	};

	glGenBuffers(1, &m_AlphaClearVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_AlphaClearVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect2), rect2, GL_STATIC_DRAW);

	m_HorizontalLineVertexCount = 8;
	float* verticesLine = new float[m_HorizontalLineVertexCount * 3];
	float gap = 2.f / ((float)m_HorizontalLineVertexCount - 1.f);
	int index = 0;
	for (int i = 0; i < m_HorizontalLineVertexCount; i++)
	{
		verticesLine[index] = (float)i*gap - 1.f;
		index++;
		verticesLine[index] = 0.f;
		index++;
		verticesLine[index] = 0.f;
		index++;
	}
	glGenBuffers(1, &m_HorizontalLineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_HorizontalLineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*m_HorizontalLineVertexCount*3,
						verticesLine, GL_STATIC_DRAW);
	delete[] verticesLine;
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//���̴� ������Ʈ ����
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//���̴� �ڵ带 ���̴� ������Ʈ�� �Ҵ�
	glShaderSource(ShaderObj, 1, p, Lengths);

	//�Ҵ�� ���̴� �ڵ带 ������
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj �� ���������� ������ �Ǿ����� Ȯ��
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL �� shader log �����͸� ������
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram �� attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string *target)
{
	std::ifstream file(filename);
	if (file.fail())
	{
		std::cout << filename << " file loading failed.. \n";
		file.close();
		return false;
	}
	std::string line;
	while (getline(file, line)) {
		target->append(line.c_str());
		target->append("\n");
	}
	return true;
}

GLuint Renderer::CompileShaders(char* filenameVS, char* filenameFS)
{
	GLuint ShaderProgram = glCreateProgram(); //�� ���̴� ���α׷� ����

	if (ShaderProgram == 0) { //���̴� ���α׷��� ����������� Ȯ��
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs �� vs ������ �ε���
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs �� fs ������ �ε���
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram �� vs.c_str() ���ؽ� ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram �� fs.c_str() �����׸�Ʈ ���̴��� �������� ����� attach��
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach �Ϸ�� shaderProgram �� ��ŷ��
	glLinkProgram(ShaderProgram);

	//��ũ�� �����ߴ��� Ȯ��
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program �α׸� �޾ƿ�
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error linking shader program\n" << ErrorLog;
		return -1;
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(ShaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		std::cout << filenameVS << ", " << filenameFS << " Error validating shader program\n" << ErrorLog;
		return -1;
	}

	glUseProgram(ShaderProgram);
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done.";

	return ShaderProgram;
}

void Renderer::DrawSolidRect(float x, float y, float z, float size, float r, float g, float b, float a)
{
	float newX, newY;

	GetGLPosition(x, y, &newX, &newY);

	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), newX, newY, 0, size);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), r, g, b, a);

	int attribPosition = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBORect);
	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(attribPosition);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

float g_time = 0.f;

void Renderer::Class0310_Rendering()
{	//Program select
	glUseProgram(m_SolidRectShader);

	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), 0, 0, 0, 1);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), 1, 1, 1, 1);

	int attribLocation_Position = -1;
	attribLocation_Position = glGetAttribLocation(m_SolidRectShader,
		"a_Position");
	glEnableVertexAttribArray(attribLocation_Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO);
	glVertexAttribPointer(attribLocation_Position, 3, GL_FLOAT, 
		GL_FALSE, 0, 0);

	int attribLocation_Position1 = glGetAttribLocation(m_SolidRectShader, 
		"a_Position1");
	glEnableVertexAttribArray(attribLocation_Position1);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1);
	glVertexAttribPointer(attribLocation_Position1, 3, GL_FLOAT, GL_FALSE,
		sizeof(float) * 3, 0);

	int uniformScale = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(uniformScale, g_time);
	g_time += 0.016;
	if (g_time > 1.f)
		g_time = 0.f;

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Renderer::DrawParticle()
{
	GLuint program = m_ParticleShader;
	glUseProgram(program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*
	int posLoc = glGetAttribLocation(program, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE,
							0, 0);

	int colorLoc = glGetAttribLocation(program, "a_Color");
	glEnableVertexAttribArray(colorLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleColorVBO);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE,
		0, 0);
	*/
	int posLoc = glGetAttribLocation(program, "a_Position");
	glEnableVertexAttribArray(posLoc);
	int colorLoc = glGetAttribLocation(program, "a_Color");
	glEnableVertexAttribArray(colorLoc);
	int uvLoc = glGetAttribLocation(program, "a_UV");
	glEnableVertexAttribArray(uvLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePosColUVVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT,
		GL_FALSE,
		sizeof(float)*9, 0);
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 
		GL_FALSE,
		sizeof(float) * 9, (GLvoid*)(sizeof(float)*3));
	glVertexAttribPointer(uvLoc, 2, GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 9, (GLvoid*)(sizeof(float) * 7));

	int velLoc = glGetAttribLocation(program, "a_Vel");
	glEnableVertexAttribArray(velLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	glVertexAttribPointer(velLoc, 3, GL_FLOAT, GL_FALSE,
		0, 0);

	int emitTimeLoc = glGetAttribLocation(program, "a_EmitTime");
	glEnableVertexAttribArray(emitTimeLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	glVertexAttribPointer(emitTimeLoc, 1, GL_FLOAT, GL_FALSE,
		0, 0);

	int lifeTimeLoc = glGetAttribLocation(program, "a_LifeTime");
	glEnableVertexAttribArray(lifeTimeLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	glVertexAttribPointer(lifeTimeLoc, 1, GL_FLOAT, GL_FALSE,
		0, 0);

	int periodLoc = glGetAttribLocation(program, "a_Period");
	glEnableVertexAttribArray(periodLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePeriodVBO);
	glVertexAttribPointer(periodLoc, 1, GL_FLOAT, GL_FALSE,
		0, 0);

	int ampLoc = glGetAttribLocation(program, "a_Amp");
	glEnableVertexAttribArray(ampLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleAmpVBO);
	glVertexAttribPointer(ampLoc, 1, GL_FLOAT, GL_FALSE,
		0, 0);

	int valueLoc = glGetAttribLocation(program, "a_Value");
	glEnableVertexAttribArray(valueLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValueVBO);
	glVertexAttribPointer(valueLoc, 1, GL_FLOAT, GL_FALSE,
		0, 0);


	int timeLoc = glGetUniformLocation(program, "u_Time");
	glUniform1f(timeLoc, g_time);
	g_time += 0.01;
	int accelLoc = glGetUniformLocation(program, "u_Accel");
	glUniform3f(accelLoc, 0.f, -2.8f, 0.f);

	int texULoc = glGetUniformLocation(program,"u_Texture");
	glUniform1i(texULoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_ParticleTexture);

	glDrawArrays(GL_TRIANGLES, 0, m_ParticleVertexCount);

	glDisable(GL_BLEND);
}

void Renderer::DrawAlphaClear()
{
	GLuint shader = m_AlphaClearShader;
	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_AlphaClearVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawVertexSandbox()
{
	GLuint shader = m_VertexSandboxShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_HorizontalLineVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int timeULoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeULoc, g_time);
	g_time += 0.016;

	for (int i = 0; i < 5; i++)
	{
		glUniform1f(timeULoc, g_time+(float)i*0.2);
		glDrawArrays(GL_LINE_STRIP, 0, m_HorizontalLineVertexCount);
	}

	glDisable(GL_BLEND);
}

void Renderer::DrawTextureSandbox()
{
	GLuint shader = m_TextureSandboxShader;
	glUseProgram(shader);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	int posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	int texLoc = glGetAttribLocation(shader, "a_Texcoord");
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float)*3));
	
	GLuint samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, 0);
	glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE20, m_CheckerBoardTexture);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);
	
	GLuint repeateULoc = glGetUniformLocation(shader,"u_XYRepeat");
	glUniform2f(repeateULoc, (float)((int)g_time*4), 4.f);
	g_time += 0.008f;
	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::DrawGridMesh()
{
	glUseProgram(m_GridMeshShader);

	int attrribPosition = glGetAttribLocation(m_GridMeshShader, "a_Position");

	glEnableVertexAttribArray(attrribPosition);

	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glVertexAttribPointer(attrribPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int timeLoc = glGetUniformLocation(m_GridMeshShader, "u_Time");
	glUniform1f(timeLoc, g_time);
	g_time += 0.01;


	int uniformLoc_Texture = -1;
	uniformLoc_Texture = glGetUniformLocation(m_GridMeshShader, "u_Texture");
	glUniform1i(uniformLoc_Texture, 0);


	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_TUKtexture);


	glDrawArrays(GL_LINE_STRIP, 0, m_GridMeshVertexCount);
}

void Renderer::DrawSpriteAnimation()
{
	GLuint shader = m_TextureSandboxShader;
	glUseProgram(shader);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);

	int texLoc = glGetAttribLocation(shader, "a_Texcoord");
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	GLuint samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, (int)g_time % 6);

	//glBindTexture(GL_TEXTURE_2D, m_CheckerBoardTexture);
	//glBindTexture(GL_TEXTURE_2D, m_RGBTexture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_0Texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_1Texture);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_2Texture);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_3Texture);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, m_4Texture);


	////merged
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_5Texture);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, m_MergedTexture);

	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, m_ExplosiveTexture);

	int texID[] = { 0,1 };

	samplerULoc = glGetUniformLocation(shader, "u_MultiTexSampler");
	glUniform1iv(samplerULoc, 2, texID);
	samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, 7);

	int stepULoc = glGetUniformLocation(shader, "u_Step");

	glUniform1i(stepULoc, (int)g_time % 6);

	int seqNumLoc = glGetUniformLocation(shader, "u_seqNum");
	glUniform1f(seqNumLoc, g_time * 10);

	GLuint repeatULoc = glGetUniformLocation(shader, "u_XYRepeat");
	glUniform2f(repeatULoc, 2.f, 2.f);
	g_time += 0.08;

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::CreateTextures()
{
	static const GLulong checkerboard[] =
	{
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
	0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000,
	0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF
	};

	// glGenTexture
	glGenTextures(1, &m_CheckerBoardTexture);
	glBindTexture(GL_TEXTURE_2D, m_CheckerBoardTexture);
	// checkerboard : CPU -> GPU�� Data�� �̵��Ѵ�.
	// RGBA ������ 8X8 , Color�� ������ ���������ʱ⿡ GL_UNSIGNED_BYTE
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerboard);
	// Texture Sampling
	// GL_LINEAR - GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

}

GLuint Renderer::CreatePngTexture(char* filePath, GLuint samplingMethod)
{
	//Load Png
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, filePath);
	if (error != 0)
	{
		std::cout << "PNG image loading failed : " << filePath << std::endl;
		assert(0);
	}
	GLuint temp;
	glGenTextures(1, &temp);
	glBindTexture(GL_TEXTURE_2D, temp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingMethod);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingMethod);

	return temp;
}

void Renderer::CreateGridMesh()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 70;
	int pointCountY = 70;

	float width = targetPosX - basePosX;
	float height = targetPosY - basePosY;

	float* point = new float[pointCountX * pointCountY * 2];
	float* vertices = new float[(pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3];
	m_GridMeshVertexCount = (pointCountX - 1) * (pointCountY - 1) * 2 * 3;

	//Prepare points
	for (int x = 0; x < pointCountX; x++)
	{
		for (int y = 0; y < pointCountY; y++)
		{
			point[(y * pointCountX + x) * 2 + 0] = basePosX + width * (x / (float)(pointCountX - 1));
			point[(y * pointCountX + x) * 2 + 1] = basePosY + height * (y / (float)(pointCountY - 1));
		}
	}

	//Make triangles
	int vertIndex = 0;
	for (int x = 0; x < pointCountX - 1; x++)
	{
		for (int y = 0; y < pointCountY - 1; y++)
		{
			//Triangle part 1
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;

			//Triangle part 2
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + x) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[(y * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 0];
			vertIndex++;
			vertices[vertIndex] = point[((y + 1) * pointCountX + (x + 1)) * 2 + 1];
			vertIndex++;
			vertices[vertIndex] = 0.f;
			vertIndex++;
		}
	}

	glGenBuffers(1, &m_GridMeshVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (pointCountX - 1) * (pointCountY - 1) * 2 * 3 * 3, vertices, GL_STATIC_DRAW);
}

void Renderer::CreateFBOs()
{
	GLuint m_AFBOTexture = 0;
	GLuint m_BFBOTexture = 0;
	GLuint m_CFBOTexture = 0;

	//Color Buffer

	glGenTextures(1, &m_AFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenTextures(1, &m_BFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_BFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenTextures(1, &m_CFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_CFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	//Depth Buffer


	glGenRenderbuffers(1, &m_DepthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_A_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_AFBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);
}

void Renderer::DrawFragmentSandbox()
{
	GLuint shader = m_FragmentSandboxShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int posLoc = glGetAttribLocation(shader, "a_Position");
	int texLoc = glGetAttribLocation(shader, "a_Texcoord");
	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_FragmentSandboxVBO);

	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 
						sizeof(float)*5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE,
		sizeof(float)*5, (GLvoid*)(sizeof(float)*3));

	int pointUloc = glGetUniformLocation(shader, "u_Point");
	glUniform2f(pointUloc, 0.3, 0.3);
	int pointsUloc = glGetUniformLocation(shader, "u_Points");
	float points[] = { 0.1, 0.1, 0.5, 0.5, 0.8, 0.8 };
	glUniform2fv(pointsUloc, 3, points);
	int timeUloc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeUloc, g_time);
	g_time += 0.008;

	glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Renderer::GetGLPosition(float x, float y, float *newX, float *newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::Class0310()
{
	float vertices[] = { 0, 0, 0, 1, 0, 0, 1, 1, 0 };

	glGenBuffers(1, &m_testVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, 
		GL_STATIC_DRAW);

	float vertices1[] = { -1, -1, 0, 
						0, -1, 0, 
						0, 0, 0 };

	glGenBuffers(1, &m_testVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1,
		GL_STATIC_DRAW);

	float color[] = {  1, 0, 0, 1,
					   0, 1, 0, 1,
					   0, 0, 1, 1 };

	glGenBuffers(1, &m_ColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color,
		GL_STATIC_DRAW);

	/*int size = 40000000000000;
	float* testTemp = new float[size];
	memset(testTemp, 1, sizeof(float)*size);

	GLuint testVBO1 = 0;
	glGenBuffers(1, &testVBO1);
	glBindBuffer(GL_ARRAY_BUFFER, testVBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size,
		testTemp,
		GL_STATIC_DRAW);*/

}

void Renderer::CreateParticleVBO(int numParticleCount)
{
	int vertexCount = 6;
	int particleCount = numParticleCount;
	int floatCount = 3;
	int totalFloatCount = particleCount
		* vertexCount
		* floatCount;
	int totalFloatCountSingle = particleCount
		* vertexCount
		* 1;
	int totalFloatCountFour = particleCount
		* vertexCount
		* 4;

	m_ParticleVertexCount = particleCount * vertexCount;

	float* vertices = NULL;
	vertices = new float[totalFloatCount];

	float particleSize = 0.05f;

	int index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float particelCenterX = 0.f; // 2.f*(((float)rand() / (float)RAND_MAX) - 0.5f);
		float particelCenterY = 0.f; // 2.f*(((float)rand() / (float)RAND_MAX) - 0.5f);
		vertices[index] = particelCenterX - particleSize; index++;
		vertices[index] = particelCenterY + particleSize; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = particelCenterX - particleSize; index++;
		vertices[index] = particelCenterY - particleSize; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = particelCenterX + particleSize; index++;
		vertices[index] = particelCenterY + particleSize; index++;
		vertices[index] = 0.f; index++;

		vertices[index] = particelCenterX + particleSize; index++;
		vertices[index] = particelCenterY + particleSize; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = particelCenterX - particleSize; index++;
		vertices[index] = particelCenterY - particleSize; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = particelCenterX + particleSize; index++;
		vertices[index] = particelCenterY - particleSize; index++;
		vertices[index] = 0.f; index++;
	}

	glGenBuffers(1, &m_ParticleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCount,
		vertices, GL_STATIC_DRAW);
	delete[] vertices;

	float* verticesVel = NULL;
	verticesVel = new float[totalFloatCount];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float velX = 2.f*(((float)rand() / (float)RAND_MAX) - 0.5f);
		float velY = 4.f*(((float)rand() / (float)RAND_MAX));
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;;
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;
		
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;;
		verticesVel[index] = velX; index++;
		verticesVel[index] = velY; index++;
		verticesVel[index] = 0.f; index++;
	}

	glGenBuffers(1, &m_ParticleVelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCount,
		verticesVel, GL_STATIC_DRAW);
	delete[] verticesVel;
	
	//EmitTime
	float* verticesEmitTime = NULL;
	verticesEmitTime = new float[totalFloatCountSingle];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float emitTime = 10.f*(((float)rand() / (float)RAND_MAX));
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;;
	}

	glGenBuffers(1, &m_ParticleEmitTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCountSingle,
		verticesEmitTime, GL_STATIC_DRAW);
	delete[] verticesEmitTime;

	//LifeTime
	float* verticesLifeTime = NULL;
	verticesLifeTime = new float[totalFloatCountSingle];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float lifeTime = 1.f*(((float)rand() / (float)RAND_MAX));
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;;
	}

	glGenBuffers(1, &m_ParticleLifeTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCountSingle,
		verticesLifeTime, GL_STATIC_DRAW);
	delete[] verticesLifeTime;

	//period
	float* verticesPeriodTime = NULL;
	verticesPeriodTime = new float[totalFloatCountSingle];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float period = 1.f*(((float)rand() / (float)RAND_MAX));
		verticesPeriodTime[index] = period; index++;
		verticesPeriodTime[index] = period; index++;
		verticesPeriodTime[index] = period; index++;
		verticesPeriodTime[index] = period; index++;
		verticesPeriodTime[index] = period; index++;
		verticesPeriodTime[index] = period; index++;;
	}

	glGenBuffers(1, &m_ParticlePeriodVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePeriodVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCountSingle,
		verticesPeriodTime, GL_STATIC_DRAW);
	delete[] verticesPeriodTime;

	//amp
	float* verticesAmpTime = NULL;
	verticesAmpTime = new float[totalFloatCountSingle];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float amp = 1.f*(2.f*(((float)rand() / (float)RAND_MAX))-1.f);
		verticesAmpTime[index] = amp; index++;
		verticesAmpTime[index] = amp; index++;
		verticesAmpTime[index] = amp; index++;
		verticesAmpTime[index] = amp; index++;
		verticesAmpTime[index] = amp; index++;
		verticesAmpTime[index] = amp; index++;;
	}

	glGenBuffers(1, &m_ParticleAmpVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleAmpVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCountSingle,
		verticesAmpTime, GL_STATIC_DRAW);
	delete[] verticesAmpTime;

	//value
	float* verticesValue = NULL;
	verticesValue = new float[totalFloatCountSingle];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float value = 1.f*((float)rand() / (float)RAND_MAX);
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;;
	}

	glGenBuffers(1, &m_ParticleValueVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValueVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*totalFloatCountSingle,
		verticesValue, GL_STATIC_DRAW);
	delete[] verticesValue;	

	//color
	float* verticesColor = NULL;
	verticesColor = new float[totalFloatCountFour];

	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float r = 1.f*((float)rand() / (float)RAND_MAX);
		float g = 1.f*((float)rand() / (float)RAND_MAX);
		float b = 1.f*((float)rand() / (float)RAND_MAX);
		float a = 1.f*((float)rand() / (float)RAND_MAX);

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v1

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v2

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v3

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v4

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v5

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;//v6
	}

	glGenBuffers(1, &m_ParticleColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleColorVBO);
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(float)*totalFloatCountFour,
		verticesColor, GL_STATIC_DRAW);
	delete[] verticesColor;
	   	  
	//pos+color+UV vbo
	int totalFloatCountPosColUV = numParticleCount * 6 *
		(3 + 4 + 2);
	float* verticesPosColorUV = NULL;
	verticesPosColorUV = new float[totalFloatCountPosColUV];
	
	index = 0;
	for (int i = 0; i < numParticleCount; i++)
	{
		float particelCenterX = 0.f; // 2.f*(((float)rand() / (float)RAND_MAX) - 0.5f);
		float particelCenterY = 0.f; // 2.f*(((float)rand() / (float)RAND_MAX) - 0.5f);
		float r = 1.f*((float)rand() / (float)RAND_MAX);
		float g = 1.f*((float)rand() / (float)RAND_MAX);
		float b = 1.f*((float)rand() / (float)RAND_MAX);
		float a = 1.f*((float)rand() / (float)RAND_MAX);

		verticesPosColorUV[index] = particelCenterX - particleSize; index++;
		verticesPosColorUV[index] = particelCenterY + particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++; //xyz
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++; //rgba
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = 0.f; index++; //UV //v1

		verticesPosColorUV[index] = particelCenterX - particleSize; index++;
		verticesPosColorUV[index] = particelCenterY - particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = 1.f; index++; //UV //v2

		verticesPosColorUV[index] = particelCenterX + particleSize; index++;
		verticesPosColorUV[index] = particelCenterY + particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++;
		verticesPosColorUV[index] = 1.f; index++;
		verticesPosColorUV[index] = 0.f; index++; //UV //v3

		verticesPosColorUV[index] = particelCenterX + particleSize; index++;
		verticesPosColorUV[index] = particelCenterY + particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++;
		verticesPosColorUV[index] = 1.f; index++;
		verticesPosColorUV[index] = 0.f; index++; //UV //v4

		verticesPosColorUV[index] = particelCenterX - particleSize; index++;
		verticesPosColorUV[index] = particelCenterY - particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = 1.f; index++; //UV //v5

		verticesPosColorUV[index] = particelCenterX + particleSize; index++;
		verticesPosColorUV[index] = particelCenterY - particleSize; index++;
		verticesPosColorUV[index] = 0.f; index++;
		verticesPosColorUV[index] = r; index++;
		verticesPosColorUV[index] = g; index++;
		verticesPosColorUV[index] = b; index++;
		verticesPosColorUV[index] = a; index++;
		verticesPosColorUV[index] = 1.f; index++;
		verticesPosColorUV[index] = 1.f; index++; //UV //v6
	}

	glGenBuffers(1, &m_ParticlePosColUVVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePosColUVVBO);
	glBufferData(GL_ARRAY_BUFFER, 
		sizeof(float)*totalFloatCountPosColUV,
		verticesPosColorUV, GL_STATIC_DRAW);
	delete[] verticesPosColorUV;
}
