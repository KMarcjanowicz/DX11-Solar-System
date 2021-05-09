////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Position = 0;
	m_Camera = 0;

	sun = 0;
	mercury = 0;
	venus = 0;
	earth = 0;

	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	//Initialised, will be my iceland model. 28/11/2019
	m_Model4 = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -20.0f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.0f, 0.0f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);


	// Create the model object.
	sun = new ModelClass;
	if (!sun)
	{
		return false;
	}

	//Initialize the model object.
	result = sun->Initialize(m_D3D->GetDevice(), "../Engine/models/sphere.txt", L"../Engine/textures/2k_sun.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sun object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	mercury = new ModelClass;
	if (!mercury)
	{
		return false;
	}

	//Initialize the model object.
	result = mercury->Initialize(m_D3D->GetDevice(), "../Engine/models/sphere.txt", L"../Engine/textures/2k_mercury.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the mercury object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	venus = new ModelClass;
	if (!venus)
	{
		return false;
	}

	//Initialize the model object.
	result = venus->Initialize(m_D3D->GetDevice(), "../Engine/models/sphere.txt", L"../Engine/textures/2k_venus_surface.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the venus object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	earth = new BumpModelClass;
	if (!earth)
	{
		return false;
	}

	// Initialize the bump model object.
	result = earth->Initialize(m_D3D->GetDevice(), "../Engine/models/sphere.txt", L"../Engine/textures/2k_earth_daymap.dds",
		L"../Engine/textures/2k_earth_normal_map.dds");

	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the earth model object.", L"Error", MB_OK);
		return false;
	}

	/*
	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/marble.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}
	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone.dds", 
								  L"../Engine/data/normal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}
	*/

	// Create the 4th model object.
	m_Model4 = new ModelClass;
	if (!m_Model4)
	{
		return false;
	}

	
	// Initialize the 4th model object.
	result = m_Model4->Initialize(m_D3D->GetDevice(), "../Engine/data/iceland.txt", L"../Engine/data/dessert2.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the 4th model object.", L"Error", MB_OK);
		return false;
	}
	

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if (sun)
	{
		sun->Shutdown();
		delete sun;
		sun = 0;
	}

	if (mercury)
	{
		mercury->Shutdown();
		delete mercury;
		mercury = 0;
	}


	if(venus)
	{
		venus->Shutdown();
		delete venus;
		venus = 0;
	}

	if(earth)
	{
		earth->Shutdown();
		delete earth;
		earth = 0;
	}

	if (m_Model4)
	{
		m_Model4->Shutdown();
		delete m_Model4;
		m_Model4 = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Render the graphics.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = m_Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = m_Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = m_Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	//*Xu. 03/12/2019
	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	//*/
	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseXDelta(), m_Input->GetMouseYDelta());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);
	m_Input->ResetCursorPos();

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	return true;
}

bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;

	static float rotation = 0.0f;

	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.0005f * m_Timer->GetTime();

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// Setup the rotation and translation of the sun.
	XMMATRIX scaleSun;
	scaleSun = XMMatrixScaling(10.0f, 10.0f, 10.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, scaleSun);

	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation / 20));

	// Render sun using the texture shader.
	sun->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), sun->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		sun->GetTexture());

	//=================================================================================================================================================
	m_D3D->GetWorldMatrix(worldMatrix);

	XMMATRIX scaleMercury;
	scaleMercury = XMMatrixScaling(0.60f, 0.60f, 0.60f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleMercury);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.0f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(20.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	//worldMatrix = XMMatrixRotationY(rotation);
	XMVECTOR MyAxis;
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, rotation * 2));


	// Render the first model using the texture shader.
	mercury->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), mercury->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		mercury->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//=================================================================================================================================================
	m_D3D->GetWorldMatrix(worldMatrix);

	XMMATRIX scaleVenus;
	scaleVenus = XMMatrixScaling(1.2f, 1.2f, 1.2f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleVenus);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.05f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(25.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	//worldMatrix = XMMatrixRotationY(rotation);
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, rotation ));


	// Render the first model using the texture shader.
	venus->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), venus->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		venus->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

	if (!result)
	{
		return false;
	}

	//=================================================================================================================================================
	m_D3D->GetWorldMatrix(worldMatrix);

	XMMATRIX scaleEarth;
	scaleEarth = XMMatrixScaling(1.7f, 1.7f, 1.7f);

	worldMatrix = XMMatrixMultiply(worldMatrix, scaleEarth);

	//self-spinning
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation * 0.1f));

	//set up positioning factors
	translateMatrix = XMMatrixTranslation(35.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	//set up rotation factors
	//worldMatrix = XMMatrixRotationY(rotation);
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, rotation * 0.6f));


	// Render the first model using the texture shader.
	earth->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), earth->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		earth->GetColorTexture(), earth->GetNormalMapTexture(), m_Light->GetDirection(),
		m_Light->GetDiffuseColor());

	if (!result)
	{
		return false;
	}

	/*
	// Setup the rotation and translation of the first model.
	worldMatrix = XMMatrixRotationZ(rotation * 3.0f);
	translateMatrix = XMMatrixTranslation(-3.5f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the second model.
	m_D3D->GetWorldMatrix(worldMatrix);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixScaling(0.03f, 0.03f, 0.03f));
	
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationY(rotation));

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixTranslation(0.0f, 0.0f, 0.0f));

	// Render the second model using the light shader.
	m_Model2->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderLightShader(m_D3D->GetDeviceContext(), m_Model2->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
									   m_Model2->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
									   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// Setup the rotation and translation of the third model.
	m_D3D->GetWorldMatrix(worldMatrix);
	worldMatrix = XMMatrixRotationX(rotation / 3.0f);
	translateMatrix = XMMatrixTranslation(3.5f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the third model using the bump map shader.
	m_Model3->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), m_Model3->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model3->GetColorTexture(), m_Model3->GetNormalMapTexture(), m_Light->GetDirection(), 
												  m_Light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	*/
	// Setup the rotation and translation of the 4th model.
	worldMatrix = XMMatrixIdentity();
	worldMatrix = XMMatrixScaling(10.0f, 3.0f, 10.0f);
	translateMatrix = XMMatrixTranslation(0.0f, -50.0f, 200.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Render the fourth model using the texture shader.
	m_Model4->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model4->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model4->GetTexture());
	if (!result)
	{
		return false;
	}
	// Present the rendered scene to the screen.
	m_D3D->EndScene();


	return true;
}