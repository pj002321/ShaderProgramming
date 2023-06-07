#include "stdafx.h"
#include "Renderer.h"
#include "LoadPng.h"
#include "assert.h"

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
	m_TextureSandboxShader = CompileShaders("./Shaders/TextureSandbox.vs",
		"./Shaders/TextureSandbox.fs");
	m_MidTermVSShader = CompileShaders("./Shaders/MidTermVS.vs",
		"./Shaders/MidTermVS.fs");
	m_MidTermFSShader = CompileShaders("./Shaders/MidTermFS.vs",
		"./Shaders/MidTermFS.fs");
	m_GridMeshShader = CompileShaders("./Shaders/GridMesh.vs",
		"./Shaders/GridMesh.fs");
	m_DrawTextureShader = CompileShaders("./Shaders/DrawTexture.vs",
		"./Shaders/DrawTexture.fs");

	//Create VBOs
	CreateVertexBufferObjects();

	//Create Textures;
	CreateTexures();

	//Create grid mesh
	CreateGridMesh();

	//Create FBO
	CreateFBOs();

	//Load Textures
	m_RGBTexture = CreatePngTexture("./RGB.png", GL_NEAREST);
	m_0Texture = CreatePngTexture("./0.png", GL_NEAREST);
	m_1Texture = CreatePngTexture("./1.png", GL_NEAREST);
	m_2Texture = CreatePngTexture("./2.png", GL_NEAREST);
	m_3Texture = CreatePngTexture("./3.png", GL_NEAREST);
	m_4Texture = CreatePngTexture("./4.png", GL_NEAREST);
	m_5Texture = CreatePngTexture("./5.png", GL_NEAREST);
	m_MergedTexture = CreatePngTexture("./merged.png", GL_NEAREST);
	m_ExplosionTexture = CreatePngTexture("./explosion.png", GL_NEAREST);
	m_rabbitTexture = CreatePngTexture("./newj.png", GL_NEAREST);



	if (m_SolidRectShader > 0 && m_VBORect > 0)
	{
		m_Initialized = true;
	}
}

void Renderer::CreateFBOs()
{
	glGenTextures(1, &m_AFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glGenTextures(1, &m_AFBOAttach_1_Texture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOAttach_1_Texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glGenTextures(1, &m_AFBOAttach_2_Texture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOAttach_2_Texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glGenTextures(1, &m_AFBOAttach_3_Texture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOAttach_3_Texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glGenTextures(1, &m_AFBOAttach_4_Texture);
	glBindTexture(GL_TEXTURE_2D, m_AFBOAttach_4_Texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);


	glGenTextures(1, &m_BFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_BFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenTextures(1, &m_CFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_CFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenTextures(1, &m_DFBOTexture);
	glBindTexture(GL_TEXTURE_2D, m_DFBOTexture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glGenRenderbuffers(1, &m_DepthRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, m_DepthRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_A_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_A_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_AFBOTexture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_AFBOAttach_1_Texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_AFBOAttach_2_Texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_AFBOAttach_3_Texture, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_AFBOAttach_4_Texture, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "fbo creation failed" << std::endl;
	}

	glGenFramebuffers(1, &m_B_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_B_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_BFBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "fbo creation failed" << std::endl;
	}

	glGenFramebuffers(1, &m_C_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_C_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_CFBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "fbo creation failed" << std::endl;
	}

	glGenFramebuffers(1, &m_D_FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_D_FBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_DFBOTexture, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthRenderBuffer);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "fbo creation failed" << std::endl;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

bool Renderer::IsInitialized()
{
	return m_Initialized;
}

void Renderer::CreateVertexBufferObjects()
{
	float size = 0.05;
	float midTermVSRect[] =
	{
		-size,  size, 0.f,    0.f, 0.f, 1.f, //x, y, z, tx, ty, value
		-size, -size, 0.f,    0.f, 1.f, 1.f,
		 size,  size, 0.f,    1.f, 0.f, 1.f, //Triangle1
		 size,  size, 0.f,    1.f, 0.f, 1.f,
		-size, -size, 0.f,    0.f, 1.f, 1.f,
		 size, -size, 0.f,    1.f, 1.f, 1.f, //Triangle2 
		-size,  size, 0.f,    0.f, 0.f, 2.f,
		-size, -size, 0.f,    0.f, 1.f, 2.f,
		 size,  size, 0.f,    1.f, 0.f, 2.f, //Triangle3
		 size,  size, 0.f,    1.f, 0.f, 2.f,
		-size, -size, 0.f,    0.f, 1.f, 2.f,
		 size, -size, 0.f,    1.f, 1.f, 2.f, //Triangle4
	};

	glGenBuffers(1, &m_MidTermVSVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_MidTermVSVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(midTermVSRect), midTermVSRect, GL_STATIC_DRAW);

	size = 0.5f;
	float midTermFSRect[] =
	{
		-size,  size, 0.f,    0.f, 0.f, //x, y, z, tx, ty
		-size, -size, 0.f,    0.f, 1.f,
		 size,  size, 0.f,    1.f, 0.f, //Triangle1
		 size,  size, 0.f,    1.f, 0.f,
		-size, -size, 0.f,    0.f, 1.f,
		 size, -size, 0.f,    1.f, 1.f, //Triangle2 
	};

	glGenBuffers(1, &m_MidTermFSVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_MidTermFSVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(midTermFSRect), midTermFSRect, GL_STATIC_DRAW);

	float textureRect[] =
	{
		-0.5f, 0.5f, 0.f,     0.f, 0.f, //x, y, z, tx, ty
		-0.5f, -0.5f, 0.f,    0.f, 1.f,
		 0.5f, 0.5f, 0.f,     1.f, 0.f, //Triangle1
		 0.5f, 0.5f, 0.f,     1.f, 0.f,
		-0.5f, -0.5f, 0.f,    0.f, 1.f,
		 0.5f, -0.5f, 0.f,    1.f, 1.f //Triangle2 
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

	float vertices[] = { 0, 0, 0,
						 1, 0, 0,
						 1, 1, 0 }; //CPU memory

	glGenBuffers(1, &m_testVBO); //get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO); //bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //data transfer from CPU to GPU

	float vertices1[] = { -1, -1, 0,
						   0, -1, 0,
						   0, 0, 0 }; //CPU memory

	glGenBuffers(1, &m_testVBO1); //get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1); //bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW); //data transfer from CPU to GPU

	float verticesColor[] = { 1, 0, 0, 1,
							  0, 1, 0, 1,
							  0, 0, 1, 1 }; //CPU memory

	glGenBuffers(1, &m_testVBOColor); //get Buffer Object ID
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBOColor); //bind to array buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesColor), verticesColor, GL_STATIC_DRAW); //data transfer from CPU to GPU


	/*float* temp;
	int size = 400000000000000;
	temp = new float[size];
	memset(temp, 1, sizeof(float)*size);

	glBindBuffer(GL_ARRAY_BUFFER, testVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*size, temp, GL_STATIC_DRAW);

	std::cout << "asdf" << std::endl;*/

	float rect1[]
		=
	{
		-1.f, -1.f, 0.f,     0.f, 1.f, //x, y, z, tx, ty
		-1.f, 1.f, 0.f,      0.f, 0.f,
		1.f, 1.f, 0.f,       1.f, 0.f, //Triangle1
		-1.f, -1.f, 0.f,     0.f, 1.f,
		1.f, 1.f, 0.f,       1.f, 0.f,
		1.f, -1.f, 0.f,      1.f, 1.f //Triangle2
	};

	glGenBuffers(1, &m_FragmentSandboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_FragmentSandboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect1), rect1, GL_STATIC_DRAW);

	float rect2[]
		=
	{
		-1.f, -1.f, 0.f,  //x, y, z
		-1.f, 1.f, 0.f,
		1.f, 1.f, 0.f,  //Triangle1
		-1.f, -1.f, 0.f,
		1.f, 1.f, 0.f,
		1.f, -1.f, 0.f, //Triangle2
	};

	glGenBuffers(1, &m_AlphaClearVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_AlphaClearVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(rect2), rect2, GL_STATIC_DRAW);

	m_HoriLineVertexCount = 10;
	int floatCount = m_HoriLineVertexCount * 3;
	int index = 0;
	float gap = 2.f / ((float)m_HoriLineVertexCount - 1.f);
	float* lineVertices = new float[floatCount];
	for (int i = 0; i < m_HoriLineVertexCount; i++)
	{
		lineVertices[index] = -1.f + (float)i * gap; index++;
		lineVertices[index] = 0.f; index++;
		lineVertices[index] = 0.f; index++;
	}
	glGenBuffers(1, &m_HoriLineVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_HoriLineVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCount,
		lineVertices, GL_STATIC_DRAW);

	float sizeX = 1.f / m_WindowSizeX;
	float sizeY = 1.f / m_WindowSizeY;
	float drawTextureRect[] =
	{
		-sizeX, sizeY, 0.f,     0.f, 0.f, //x, y, z, tx, ty
		-sizeX, -sizeY, 0.f,    0.f, 1.f,
		sizeX, sizeY, 0.f,     1.f, 0.f, //Triangle1
		sizeX, sizeY, 0.f,     1.f, 0.f,
		-sizeX, -sizeY, 0.f,    0.f, 1.f,
		sizeX, -sizeY, 0.f,    1.f, 1.f //Triangle2 
	};

	glGenBuffers(1, &m_DrawTextureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_DrawTextureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(drawTextureRect), drawTextureRect, GL_STATIC_DRAW);

	CreateParticles(100000);
}

void Renderer::AddShader(GLuint ShaderProgram, const char* pShaderText, GLenum ShaderType)
{
	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(ShaderType);

	if (ShaderObj == 0) {
		fprintf(stderr, "Error creating shader type %d\n", ShaderType);
	}

	const GLchar* p[1];
	p[0] = pShaderText;
	GLint Lengths[1];
	Lengths[0] = strlen(pShaderText);
	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, p, Lengths);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint success;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", ShaderType, InfoLog);
		printf("%s \n", pShaderText);
	}

	// ShaderProgram 에 attach!!
	glAttachShader(ShaderProgram, ShaderObj);
}

bool Renderer::ReadFile(char* filename, std::string* target)
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
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		fprintf(stderr, "Error creating shader program\n");
	}

	std::string vs, fs;

	//shader.vs 가 vs 안으로 로딩됨
	if (!ReadFile(filenameVS, &vs)) {
		printf("Error compiling vertex shader\n");
		return -1;
	};

	//shader.fs 가 fs 안으로 로딩됨
	if (!ReadFile(filenameFS, &fs)) {
		printf("Error compiling fragment shader\n");
		return -1;
	};

	// ShaderProgram 에 vs.c_str() 버텍스 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, vs.c_str(), GL_VERTEX_SHADER);

	// ShaderProgram 에 fs.c_str() 프레그먼트 쉐이더를 컴파일한 결과를 attach함
	AddShader(ShaderProgram, fs.c_str(), GL_FRAGMENT_SHADER);

	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };

	//Attach 완료된 shaderProgram 을 링킹함
	glLinkProgram(ShaderProgram);

	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &Success);

	if (Success == 0) {
		// shader program 로그를 받아옴
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
	std::cout << filenameVS << ", " << filenameFS << " Shader compiling is done." << std::endl;

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

void Renderer::Class0310_Render()
{
	//Program select
	glUseProgram(m_SolidRectShader);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Trans"), 0, 0, 0, 1);
	glUniform4f(glGetUniformLocation(m_SolidRectShader, "u_Color"), 1, 0, 0, 1);

	int attribLoc_Position = -1;
	attribLoc_Position = glGetAttribLocation(m_SolidRectShader, "a_Position");
	glEnableVertexAttribArray(attribLoc_Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO);
	glVertexAttribPointer(attribLoc_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Position1 = -1;
	attribLoc_Position1 = glGetAttribLocation(m_SolidRectShader, "a_Position1");
	glEnableVertexAttribArray(attribLoc_Position1);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBO1);
	glVertexAttribPointer(attribLoc_Position1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Color = -1;
	attribLoc_Color = glGetAttribLocation(m_SolidRectShader, "a_Color");
	glEnableVertexAttribArray(attribLoc_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_testVBOColor);
	glVertexAttribPointer(attribLoc_Color, 4, GL_FLOAT, GL_FALSE, 0, 0);

	int unifromLoc_Scale = -1;
	unifromLoc_Scale = glGetUniformLocation(m_SolidRectShader, "u_Scale");
	glUniform1f(unifromLoc_Scale, g_time);
	//g_time += 0.016;
	//if (g_time > 1.f)
	//	g_time = 0.f;

	glDrawArrays(GL_TRIANGLES, 0, 3);

}

void Renderer::DrawParticleEffect()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_B_FBO);
	glViewport(0, 0, 512, 512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Program select
	int program = m_ParticleShader;
	glUseProgram(program);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/*int attribLoc_Position = -1;
	attribLoc_Position = glGetAttribLocation(program, "a_Position");
	glEnableVertexAttribArray(attribLoc_Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glVertexAttribPointer(attribLoc_Position, 3, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Color = -1;
	attribLoc_Color = glGetAttribLocation(program, "a_Color");
	glEnableVertexAttribArray(attribLoc_Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleColorVBO);
	glVertexAttribPointer(attribLoc_Color, 4, GL_FLOAT, GL_FALSE, 0, 0);
	*/
	int attribLoc_Position = -1;
	attribLoc_Position = glGetAttribLocation(program, "a_Position");
	int attribLoc_Color = -1;
	attribLoc_Color = glGetAttribLocation(program, "a_Color");
	int attribLoc_Vel = -1;
	attribLoc_Vel = glGetAttribLocation(program, "a_Vel");
	int attribLoc_UV = -1;
	attribLoc_UV = glGetAttribLocation(program, "a_UV");
	glEnableVertexAttribArray(attribLoc_Position);
	glEnableVertexAttribArray(attribLoc_Color);
	glEnableVertexAttribArray(attribLoc_Vel);
	glEnableVertexAttribArray(attribLoc_UV);

	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePositionColorVelUVVBO);
	glVertexAttribPointer(attribLoc_Position, 3, GL_FLOAT,
		GL_FALSE, sizeof(float) * 12, 0);
	glVertexAttribPointer(attribLoc_Color, 4, GL_FLOAT,
		GL_FALSE, sizeof(float) * 12,
		(GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(attribLoc_Vel, 3, GL_FLOAT,
		GL_FALSE, sizeof(float) * 12,
		(GLvoid*)(sizeof(float) * 7));
	glVertexAttribPointer(attribLoc_UV, 2, GL_FLOAT,
		GL_FALSE, sizeof(float) * 12,
		(GLvoid*)(sizeof(float) * 10));

	/*int attribLoc_Vel = -1;
	attribLoc_Vel = glGetAttribLocation(program, "a_Vel");
	glEnableVertexAttribArray(attribLoc_Vel);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	glVertexAttribPointer(attribLoc_Vel, 3, GL_FLOAT, GL_FALSE, 0, 0);
	*/
	int attribLoc_EmitTime = -1;
	attribLoc_EmitTime = glGetAttribLocation(program, "a_EmitTime");
	glEnableVertexAttribArray(attribLoc_EmitTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	glVertexAttribPointer(attribLoc_EmitTime, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_LifeTime = -1;
	attribLoc_LifeTime = glGetAttribLocation(program, "a_LifeTime");
	glEnableVertexAttribArray(attribLoc_LifeTime);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	glVertexAttribPointer(attribLoc_LifeTime, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Period = -1;
	attribLoc_Period = glGetAttribLocation(program, "a_Period");
	glEnableVertexAttribArray(attribLoc_Period);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePeriodVBO);
	glVertexAttribPointer(attribLoc_Period, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Amp = -1;
	attribLoc_Amp = glGetAttribLocation(program, "a_Amp");
	glEnableVertexAttribArray(attribLoc_Amp);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleAmpVBO);
	glVertexAttribPointer(attribLoc_Amp, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int attribLoc_Value = -1;
	attribLoc_Value = glGetAttribLocation(program, "a_Value");
	glEnableVertexAttribArray(attribLoc_Value);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValueVBO);
	glVertexAttribPointer(attribLoc_Value, 1, GL_FLOAT, GL_FALSE, 0, 0);

	int uniformLoc_Time = -1;
	uniformLoc_Time = glGetUniformLocation(program, "u_Time");
	glUniform1f(uniformLoc_Time, g_time);
	g_time += 0.008;

	glDrawArrays(GL_TRIANGLES, 0, m_ParticleVerticesCount);

	glDisable(GL_BLEND);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawVertexSandbox()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_C_FBO);
	glViewport(0, 0, 512, 512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint shader = m_VertexSandboxShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_HoriLineVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint timeULoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeULoc, g_time);
	g_time += 0.016;

	glDrawArrays(GL_LINE_STRIP, 0, m_HoriLineVertexCount);

	glUniform1f(timeULoc, g_time + 0.2);
	glDrawArrays(GL_LINE_STRIP, 0, m_HoriLineVertexCount);

	glUniform1f(timeULoc, g_time + 0.4);
	glDrawArrays(GL_LINE_STRIP, 0, m_HoriLineVertexCount);

	glUniform1f(timeULoc, g_time + 0.6);
	glDrawArrays(GL_LINE_STRIP, 0, m_HoriLineVertexCount);


	glDisable(GL_BLEND);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawAlphaClear()
{
	GLuint shader = m_AlphaClearShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_AlphaClearVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::DrawFragmentSandbox()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_A_FBO);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 512, 512);
	GLenum drawBuffer[5] = { GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 ,
	GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4 };
	glDrawBuffers(5, drawBuffer);

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
		sizeof(float) * 5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE,
		sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	int uniformLoc_Point = -1;
	uniformLoc_Point = glGetUniformLocation(shader, "u_Point");
	glUniform2f(uniformLoc_Point, 0.5f, 0.f);

	float points[] = { 0.4f, 0.4f,
					  0.2f, 0.2f,
					  0.f, 0.3f };
	int uniformLoc_Points = -1;
	uniformLoc_Points = glGetUniformLocation(shader, "u_Points");
	glUniform2fv(uniformLoc_Points, 3, points);

	int uniformLoc_Time = -1;
	uniformLoc_Time = glGetUniformLocation(shader, "u_Time");
	glUniform1f(uniformLoc_Time, g_time);
	g_time += 0.001;

	int uniformLoc_Tex = -1;
	uniformLoc_Tex = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(uniformLoc_Tex, 0);
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//Draw done.

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, 512, 512);

	//DrawTexture(0, 0, 256, 256, m_AFBOAttach_4_Texture);

}

void Renderer::DrawTextureSandbox()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_D_FBO);
	glViewport(0, 0, 512, 512);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint shader = m_TextureSandboxShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	GLuint texLoc = glGetAttribLocation(shader, "a_TexPos");
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_TextureSandboxVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5,
		(GLvoid*)(sizeof(float) * 3));

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
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, m_5Texture);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, m_MergedTexture);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, m_ExplosionTexture);


	int texID[] = { 0, 1 };
	GLuint samplerULoc = glGetUniformLocation(shader, "u_MultiTexSampler");
	glUniform1iv(samplerULoc, 2, texID);
	samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, 7);
	int stepULoc = glGetUniformLocation(shader, "u_Step");
	glUniform1f(stepULoc, (float)(((int)g_time) % 6));
	int seqNumULoc = glGetUniformLocation(shader, "u_SeqNum");
	glUniform1f(seqNumULoc, g_time * 10);

	GLuint repeatULoc = glGetUniformLocation(shader, "u_XYRepeat");
	glUniform2f(repeatULoc, 2.f, 2.f);
	g_time += 0.08;

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Renderer::DrawGridMesh()
{
	GLuint shader = m_GridMeshShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	glBindBuffer(GL_ARRAY_BUFFER, m_GridMeshVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);

	GLuint timeULoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeULoc, g_time);
	g_time += 0.016;

	GLuint texULoc = glGetUniformLocation(shader, "u_Texture");
	glUniform1i(texULoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_rabbitTexture);

	glDrawArrays(GL_TRIANGLES, 0, m_GridMeshVertexCount);

	DrawTexture(0, 0, 256, 256, m_rabbitTexture);
}

void Renderer::DrawResults()
{
	DrawTexture(-0.75, -0.75, 128, 128, m_AFBOTexture);
	DrawTexture(-0.25, -0.75, 128, 128, m_AFBOAttach_1_Texture);
	DrawTexture(0.25, -0.75, 128, 128, m_AFBOAttach_2_Texture);
	DrawTexture(0.75, -0.75, 128, 128, m_AFBOAttach_3_Texture);
	DrawTexture(-0.75, -0.25, 128, 128, m_BFBOTexture);
	DrawTexture(-0.25, -0.25, 128, 128, m_CFBOTexture);
	DrawTexture(0.25, -0.25, 128, 128, m_DFBOTexture);
}

void Renderer::DrawMidTermVS()
{
	GLuint shader = m_MidTermVSShader;
	glUseProgram(shader);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	GLuint texLoc = glGetAttribLocation(shader, "a_TexPos");
	glEnableVertexAttribArray(texLoc);
	GLuint valueLoc = glGetAttribLocation(shader, "a_Value");
	glEnableVertexAttribArray(valueLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_MidTermVSVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
		(GLvoid*)(sizeof(float) * 3));
	glVertexAttribPointer(valueLoc, 1, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
		(GLvoid*)(sizeof(float) * 5));

	GLuint timeULoc = glGetUniformLocation(shader, "u_Time");
	glUniform1f(timeULoc, g_time);	g_time += 0.008;

	glDrawArrays(GL_TRIANGLES, 0, 12);
}

void Renderer::DrawMidTermFS()
{
	GLuint shader = m_MidTermFSShader;
	glUseProgram(shader);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	GLuint texLoc = glGetAttribLocation(shader, "a_TexPos");
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_MidTermFSVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	GLuint samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_RGBTexture);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::GetGLPosition(float x, float y, float* newX, float* newY)
{
	*newX = x * 2.f / m_WindowSizeX;
	*newY = y * 2.f / m_WindowSizeY;
}

void Renderer::Class0310()
{
}

void Renderer::CreateTexures()
{
	GLulong checkerboard[] =
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

	glGenTextures(1, &m_CheckerBoardTexture);
	glBindTexture(GL_TEXTURE_2D, m_CheckerBoardTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		checkerboard);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
		std::cout << "PNG image loading failed:" << filePath << std::endl;
		assert(0);
	}

	GLuint temp;
	glGenTextures(1, &temp);
	glBindTexture(GL_TEXTURE_2D, temp);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
		GL_UNSIGNED_BYTE, &image[0]);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, samplingMethod);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, samplingMethod);

	return temp;
}

void Renderer::CreateGridMesh()
{
	float basePosX = -0.5f;
	float basePosY = -0.5f;
	float targetPosX = 0.5f;
	float targetPosY = 0.5f;

	int pointCountX = 64;
	int pointCountY = 64;

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

void Renderer::CreateParticles(int numParticles)
{
	float centerX, centerY;
	centerX = 0.f;
	centerY = 0.f;
	float size = 0.01f;
	int particleCount = numParticles;
	m_ParticleVerticesCount = particleCount * 6;
	int floatCount = particleCount * 6 * 3; //x, y, z per vertex
	int floatCountColor = particleCount * 6 * 4; //r,g,b,a per vertex
	int floatCountSingle = particleCount * 6; //value per vertex
	int floatCountPosColorVel = particleCount * 6 * (3 + 4 + 3);
	//x, y, z, r, g, b, a, vx, vy, vz
	int floatCountPosColorVelUV = particleCount * 6 * (3 + 4 + 3 + 2);
	//x, y, z, r, g, b, a, vx, vy, vz, u, v

	float* vertices = NULL;
	vertices = new float[floatCount];

	//position
	int index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		centerX = 0.f;// ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		centerY = 0.f;// ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		vertices[index] = centerX - size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = centerX - size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = centerX + size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;

		vertices[index] = centerX + size; index++;
		vertices[index] = centerY + size; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = centerX - size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;
		vertices[index] = centerX + size; index++;
		vertices[index] = centerY - size; index++;
		vertices[index] = 0.f; index++;
	}

	glGenBuffers(1, &m_ParticleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCount,
		vertices, GL_STATIC_DRAW);

	delete[] vertices;

	//color
	float* verticesColor = NULL;
	verticesColor = new float[floatCountColor];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float r = (float)rand() / (float)RAND_MAX;
		float g = (float)rand() / (float)RAND_MAX;
		float b = (float)rand() / (float)RAND_MAX;
		float a = (float)rand() / (float)RAND_MAX;
		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;
		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;
		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;

		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;
		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;
		verticesColor[index] = r; index++;
		verticesColor[index] = g; index++;
		verticesColor[index] = b; index++;
		verticesColor[index] = a; index++;
	}

	glGenBuffers(1, &m_ParticleColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountColor,
		verticesColor, GL_STATIC_DRAW);

	delete[] verticesColor;

	//pos_color_vel_UV
	float* verticesPosColorVelUV = NULL;
	verticesPosColorVelUV = new float[floatCountPosColorVelUV];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float centerX = 0.f;// ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		float centerY = 0.f;// ((float)rand() / (float)RAND_MAX)*2.f - 1.f;
		float r = (float)rand() / (float)RAND_MAX;
		float g = (float)rand() / (float)RAND_MAX;
		float b = (float)rand() / (float)RAND_MAX;
		float a = (float)rand() / (float)RAND_MAX;
		float vx = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		float vy = ((float)rand() / (float)RAND_MAX) * 2.f;// -1.f;

		verticesPosColorVelUV[index] = centerX - size; index++;
		verticesPosColorVelUV[index] = centerY + size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 0.f; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //u, v

		verticesPosColorVelUV[index] = centerX - size; index++;
		verticesPosColorVelUV[index] = centerY - size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 0.f; index++;
		verticesPosColorVelUV[index] = 1.f; index++; //u, v

		verticesPosColorVelUV[index] = centerX + size; index++;
		verticesPosColorVelUV[index] = centerY + size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 1.f; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //u, v

		verticesPosColorVelUV[index] = centerX + size; index++;
		verticesPosColorVelUV[index] = centerY + size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 1.f; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //u, v

		verticesPosColorVelUV[index] = centerX - size; index++;
		verticesPosColorVelUV[index] = centerY - size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 0.f; index++;
		verticesPosColorVelUV[index] = 1.f; index++; //u, v

		verticesPosColorVelUV[index] = centerX + size; index++;
		verticesPosColorVelUV[index] = centerY - size; index++;
		verticesPosColorVelUV[index] = 0.f; index++; //x,y,z
		verticesPosColorVelUV[index] = r; index++;
		verticesPosColorVelUV[index] = g; index++;
		verticesPosColorVelUV[index] = b; index++;
		verticesPosColorVelUV[index] = a; index++; //r,g,b,a
		verticesPosColorVelUV[index] = vx; index++;
		verticesPosColorVelUV[index] = vy; index++;
		verticesPosColorVelUV[index] = 0; index++; //vx, vy, vz
		verticesPosColorVelUV[index] = 1.f; index++;
		verticesPosColorVelUV[index] = 1.f; index++; //u, v
	}

	glGenBuffers(1, &m_ParticlePositionColorVelUVVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePositionColorVelUVVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)
		* floatCountPosColorVelUV,
		verticesPosColorVelUV, GL_STATIC_DRAW);

	delete[] verticesPosColorVelUV;

	//velocity
	float* verticesVel = NULL;
	verticesVel = new float[floatCount];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		centerX = ((float)rand() / (float)RAND_MAX) * 2.f - 1.f;
		centerY = ((float)rand() / (float)RAND_MAX) * 2.f;// -1.f;
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;

		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;
		verticesVel[index] = centerX; index++;
		verticesVel[index] = centerY; index++;
		verticesVel[index] = 0; index++;
	}

	glGenBuffers(1, &m_ParticleVelVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleVelVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCount,
		verticesVel, GL_STATIC_DRAW);

	delete[] verticesVel;

	//emit Time
	float* verticesEmitTime = NULL;
	verticesEmitTime = new float[floatCountSingle];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float emitTime = ((float)rand() / (float)RAND_MAX) * 10.f;

		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;

		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
		verticesEmitTime[index] = emitTime; index++;
	}

	glGenBuffers(1, &m_ParticleEmitTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleEmitTimeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle,
		verticesEmitTime, GL_STATIC_DRAW);

	delete[] verticesEmitTime;

	//life Time
	float* verticesLifeTime = NULL;
	verticesLifeTime = new float[floatCountSingle];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float lifeTime = ((float)rand() / (float)RAND_MAX) * 1.f;

		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;

		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
		verticesLifeTime[index] = lifeTime; index++;
	}

	glGenBuffers(1, &m_ParticleLifeTimeVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleLifeTimeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle,
		verticesLifeTime, GL_STATIC_DRAW);

	delete[] verticesLifeTime;

	//period
	float* verticesPeriod = NULL;
	verticesPeriod = new float[floatCountSingle];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float period = 1.f * ((float)rand() / (float)RAND_MAX);

		verticesPeriod[index] = period; index++;
		verticesPeriod[index] = period; index++;
		verticesPeriod[index] = period; index++;

		verticesPeriod[index] = period; index++;
		verticesPeriod[index] = period; index++;
		verticesPeriod[index] = period; index++;
	}

	glGenBuffers(1, &m_ParticlePeriodVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticlePeriodVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle,
		verticesPeriod, GL_STATIC_DRAW);

	delete[] verticesPeriod;

	//amp
	float* verticesAmp = NULL;
	verticesAmp = new float[floatCountSingle];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float amp = 2.f * ((float)rand() / (float)RAND_MAX) - 1.f;

		verticesAmp[index] = amp; index++;
		verticesAmp[index] = amp; index++;
		verticesAmp[index] = amp; index++;

		verticesAmp[index] = amp; index++;
		verticesAmp[index] = amp; index++;
		verticesAmp[index] = amp; index++;
	}

	glGenBuffers(1, &m_ParticleAmpVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleAmpVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle,
		verticesAmp, GL_STATIC_DRAW);

	delete[] verticesAmp;

	//parametric value
	float* verticesValue = NULL;
	verticesValue = new float[floatCountSingle];

	index = 0;
	for (int i = 0; i < particleCount; i++)
	{
		float value = 1.f * ((float)rand() / (float)RAND_MAX);

		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;

		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
		verticesValue[index] = value; index++;
	}

	glGenBuffers(1, &m_ParticleValueVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_ParticleValueVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * floatCountSingle,
		verticesValue, GL_STATIC_DRAW);

	delete[] verticesValue;

}

void Renderer::DrawTexture(float x, float y, float scaleX, float scaleY, GLuint texID)
{
	GLuint shader = m_DrawTextureShader;
	glUseProgram(shader);

	GLuint posLoc = glGetAttribLocation(shader, "a_Position");
	glEnableVertexAttribArray(posLoc);
	GLuint texLoc = glGetAttribLocation(shader, "a_TexPos");
	glEnableVertexAttribArray(texLoc);

	glBindBuffer(GL_ARRAY_BUFFER, m_DrawTextureVBO);
	glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (GLvoid*)(sizeof(float) * 3));

	GLuint samplerULoc = glGetUniformLocation(shader, "u_TexSampler");
	glUniform1i(samplerULoc, 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, texID);

	GLuint posScaleULoc = glGetUniformLocation(shader, "u_PosScale");
	glUniform4f(posScaleULoc, x, y, scaleX, scaleY);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
