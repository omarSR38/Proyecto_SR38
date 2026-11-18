////////////////////////////////////////////////////////////////////////////////
// Filename: openglclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "OpenGLClass.h"
#include <iostream>
//CONTRSTRUCTORES:
OpenGLClass::OpenGLClass() : m_window(nullptr), m_screenWidth(0), m_screenHeight(0) {
	m_input = 0;
}
//OpenGLClass::OpenGLClass(const OpenGLClass& other)
//{
//}
OpenGLClass::~OpenGLClass()
{
	OpenGLClass::Shutdown();
}

//SET Y GET:
GLFWwindow* OpenGLClass::GetWindow() const {
	return m_window;
}
void OpenGLClass::SetInput(InputClass* input_) {
	m_input = input_;
}

//METODODS:
bool OpenGLClass::InitializeGLFW(int width, int height, const char* title, bool vsync) {
	m_screenWidth = width;
	m_screenHeight = height;
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW." << std::endl;
		return false; 
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_window) {
		std::cerr << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return false;
	}

	// Obtener tamaño de la pantalla (monitor primario)
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	// Calcular posición centrada
	int xpos = (mode->width - m_screenWidth) / 2;
	int ypos = (mode->height - m_screenHeight) / 2;

	// Mover la ventana a esa posición
	glfwSetWindowPos(m_window, xpos, ypos); 
	// Configurar VSync
	glfwSwapInterval(vsync ? 1 : 0);

	//glfwSetWindowUserPointer(m_window, input);  // Vincula InputClass con la ventana
	//glfwSetKeyCallback(m_window, OpenGLClass::tecladoCallback);  // Configura el callback

	// Carga las direcciones de todas las funciones de OpenGL
	if (!InitializeExtensions()) {
		std::cerr << "Failed to load OpenGL extensions\n";
		return false;
	}

	// Imprimir la versión de OpenGL para verificar que todo está funcionando
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;



	//glViewport(0, 0, m_screenWidth, m_screenHeight);




	//// Inicializar extensiones de OpenGL (GLAD)
	//if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
	//	std::cerr << "Error: No se pudo inicializar las extensiones de OpenGL (GLAD)." << std::endl;
	//	return false;
	//}

	// Configuraciones de OpenGL por defecto

	//GetWindowSize(m_screenWidth, m_screenHeight);
	glViewport(0, 0, m_screenWidth, m_screenHeight);
	glClearDepth(1.0f);
	//glEnable(GL_DEPTH_TEST); // Habilitar pruebas de profundidad
	//glDisable(GL_DEPTH_TEST);

	glCullFace(GL_BACK);     // Renderizar solo las caras traseras
	glFrontFace(GL_CW);      // Especificar que las caras en el sentido horario son frontales

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);





	// Initialize the world/model matrix to the identity matrix.
	//BuildIdentityMatrix(m_worldMatrix);

	//float fieldOfView = 3.14159265358979323846f / 4.0f;
	//float screenAspect = (float)m_screenWidth / (float)m_screenHeight;
	//BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, 0.1f, 1000.0f);

	//LoadExtensionListGLFW();


	return true;
}
bool OpenGLClass::InitializeExtensions() {

	// Establecer el contexto de ventana actual
	glfwMakeContextCurrent(m_window);
	// Cargar las extensiones de OpenGL utilizando GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "Error: No se pudieron cargar las extensiones de OpenGL con GLAD." << std::endl;
		return false;
	}

	// Ahora copia…
	glUseProgram = ::glUseProgram;
	glBindAttribLocation = ::glBindAttribLocation;
	glGetUniformLocation = ::glGetUniformLocation;
	glUniform1i = ::glUniform1i;
	glUniformMatrix4fv = ::glUniformMatrix4fv;
	// …y así para todas las funciones GL que vayas a usar a través del wrapper.

	// Imprimir la versión de OpenGL para verificar que todo está funcionando
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;


	return true;
}
void OpenGLClass::Shutdown() {
	if (m_window) {
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
	delete m_input;
}
void OpenGLClass::ConfigureOpenGL() {
	// Configuración del buffer de profundidad
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	// Configuración de la culling de caras traseras
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Configuración adicional, como matrices de proyección, si es necesario...
}
bool OpenGLClass::WindowShouldClose() const {
	return glfwWindowShouldClose(m_window);
}

//GETTERS DE MATRICES
void OpenGLClass::GetWorldMatrix(float* matrix)
{
	matrix[0] = m_worldMatrix[0];
	matrix[1] = m_worldMatrix[1];
	matrix[2] = m_worldMatrix[2];
	matrix[3] = m_worldMatrix[3];

	matrix[4] = m_worldMatrix[4];
	matrix[5] = m_worldMatrix[5];
	matrix[6] = m_worldMatrix[6];
	matrix[7] = m_worldMatrix[7];

	matrix[8] = m_worldMatrix[8];
	matrix[9] = m_worldMatrix[9];
	matrix[10] = m_worldMatrix[10];
	matrix[11] = m_worldMatrix[11];

	matrix[12] = m_worldMatrix[12];
	matrix[13] = m_worldMatrix[13];
	matrix[14] = m_worldMatrix[14];
	matrix[15] = m_worldMatrix[15];

	return;
}
void OpenGLClass::GetProjectionMatrix(float* matrix)
{
	matrix[0] = m_projectionMatrix[0];
	matrix[1] = m_projectionMatrix[1];
	matrix[2] = m_projectionMatrix[2];
	matrix[3] = m_projectionMatrix[3];

	matrix[4] = m_projectionMatrix[4];
	matrix[5] = m_projectionMatrix[5];
	matrix[6] = m_projectionMatrix[6];
	matrix[7] = m_projectionMatrix[7];

	matrix[8] = m_projectionMatrix[8];
	matrix[9] = m_projectionMatrix[9];
	matrix[10] = m_projectionMatrix[10];
	matrix[11] = m_projectionMatrix[11];

	matrix[12] = m_projectionMatrix[12];
	matrix[13] = m_projectionMatrix[13];
	matrix[14] = m_projectionMatrix[14];
	matrix[15] = m_projectionMatrix[15];

	return;
}
void OpenGLClass::GetVideoCardInfo(char* cardName)
{
	//strcpy_s(cardName, 128, m_videoCardDescription);
	return;
}

/////////////////////////////////TRANSFORMACIONES MATRICES///////////////////////////////////
void OpenGLClass::BuildIdentityMatrix(float* matrix)
{
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return;
}
void OpenGLClass::BuildPerspectiveFovLHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth)
{
	matrix[0] = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f / tan(fieldOfView * 0.5f);
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = screenDepth / (screenDepth - screenNear);
	matrix[11] = 1.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
	matrix[15] = 0.0f;

	return;
}
void OpenGLClass::MatrixRotationY(float* matrix, float angle)
{
	matrix[0] = cosf(angle);
	matrix[1] = 0.0f;
	matrix[2] = -sinf(angle);
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = sinf(angle);
	matrix[9] = 0.0f;
	matrix[10] = cosf(angle);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return;
}
void OpenGLClass::MatrixTranslation(float* matrix, float x, float y, float z)
{
	matrix[0] = 1.0f;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = 1.0f;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;
	matrix[15] = 1.0f;

	return;
}
void OpenGLClass::MatrixMultiply(float* result, float* matrix1, float* matrix2)
{
	result[0] = (matrix1[0] * matrix2[0]) + (matrix1[1] * matrix2[4]) + (matrix1[2] * matrix2[8]) + (matrix1[3] * matrix2[12]);
	result[1] = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[5]) + (matrix1[2] * matrix2[9]) + (matrix1[3] * matrix2[13]);
	result[2] = (matrix1[0] * matrix2[2]) + (matrix1[1] * matrix2[6]) + (matrix1[2] * matrix2[10]) + (matrix1[3] * matrix2[14]);
	result[3] = (matrix1[0] * matrix2[3]) + (matrix1[1] * matrix2[7]) + (matrix1[2] * matrix2[11]) + (matrix1[3] * matrix2[15]);

	result[4] = (matrix1[4] * matrix2[0]) + (matrix1[5] * matrix2[4]) + (matrix1[6] * matrix2[8]) + (matrix1[7] * matrix2[12]);
	result[5] = (matrix1[4] * matrix2[1]) + (matrix1[5] * matrix2[5]) + (matrix1[6] * matrix2[9]) + (matrix1[7] * matrix2[13]);
	result[6] = (matrix1[4] * matrix2[2]) + (matrix1[5] * matrix2[6]) + (matrix1[6] * matrix2[10]) + (matrix1[7] * matrix2[14]);
	result[7] = (matrix1[4] * matrix2[3]) + (matrix1[5] * matrix2[7]) + (matrix1[6] * matrix2[11]) + (matrix1[7] * matrix2[15]);

	result[8] = (matrix1[8] * matrix2[0]) + (matrix1[9] * matrix2[4]) + (matrix1[10] * matrix2[8]) + (matrix1[11] * matrix2[12]);
	result[9] = (matrix1[8] * matrix2[1]) + (matrix1[9] * matrix2[5]) + (matrix1[10] * matrix2[9]) + (matrix1[11] * matrix2[13]);
	result[10] = (matrix1[8] * matrix2[2]) + (matrix1[9] * matrix2[6]) + (matrix1[10] * matrix2[10]) + (matrix1[11] * matrix2[14]);
	result[11] = (matrix1[8] * matrix2[3]) + (matrix1[9] * matrix2[7]) + (matrix1[10] * matrix2[11]) + (matrix1[11] * matrix2[15]);

	result[12] = (matrix1[12] * matrix2[0]) + (matrix1[13] * matrix2[4]) + (matrix1[14] * matrix2[8]) + (matrix1[15] * matrix2[12]);
	result[13] = (matrix1[12] * matrix2[1]) + (matrix1[13] * matrix2[5]) + (matrix1[14] * matrix2[9]) + (matrix1[15] * matrix2[13]);
	result[14] = (matrix1[12] * matrix2[2]) + (matrix1[13] * matrix2[6]) + (matrix1[14] * matrix2[10]) + (matrix1[15] * matrix2[14]);
	result[15] = (matrix1[12] * matrix2[3]) + (matrix1[13] * matrix2[7]) + (matrix1[14] * matrix2[11]) + (matrix1[15] * matrix2[15]);

	return;
}
void OpenGLClass::MatrixScale(float* matrix, float sx, float sy, float sz) {
	matrix[0] = sx;
	matrix[1] = 0.0f;
	matrix[2] = 0.0f;
	matrix[3] = 0.0f;

	matrix[4] = 0.0f;
	matrix[5] = sy;
	matrix[6] = 0.0f;
	matrix[7] = 0.0f;

	matrix[8] = 0.0f;
	matrix[9] = 0.0f;
	matrix[10] = sz;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;
}


//SIN USAR (PARA REGISTRO):
//void OpenGLClass::BeginScene(float red, float green, float blue, float alpha)
//{
//	// Set the color to clear the screen to.
//	glClearColor(red, green, blue, alpha);
//
//	// Clear the screen and depth buffer.
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	return;
//}
//void OpenGLClass::EndScene()
//{
//	// Present the back buffer to the screen since rendering is complete.
//	glfwSwapBuffers(m_window);
//	glfwPollEvents();
//
//	return;
//}
//bool OpenGLClass::InitializeOpenGL(int screenWidth, int screenHeight, float screenDepth, float screenNear, bool vsync)
//{
//	//int attributeListInt[19];
//	//int pixelFormat[1];
//	//unsigned int formatCount;
//	//int result;
//	////PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
//	//int attributeList[5];
//	//float fieldOfView, screenAspect;
//	//char* vendorString, * rendererString;
//
//
//	////// Get the device context for this window.
//	////m_deviceContext = GetDC(hwnd);
//	////if (!m_deviceContext)
//	////{
//	////	return false;
//	////}
//
//	//// Support for OpenGL rendering.
//	//attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
//	//attributeListInt[1] = TRUE;
//
//	//// Support for rendering to a window.
//	//attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
//	//attributeListInt[3] = TRUE;
//
//	//// Support for hardware acceleration.
//	//attributeListInt[4] = WGL_ACCELERATION_ARB;
//	//attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;
//
//	//// Support for 24bit color.
//	//attributeListInt[6] = WGL_COLOR_BITS_ARB;
//	//attributeListInt[7] = 24;
//
//	//// Support for 24 bit depth buffer.
//	//attributeListInt[8] = WGL_DEPTH_BITS_ARB;
//	//attributeListInt[9] = 24;
//
//	//// Support for double buffer.
//	//attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
//	//attributeListInt[11] = TRUE;
//
//	//// Support for swapping front and back buffer.
//	//attributeListInt[12] = WGL_SWAP_METHOD_ARB;
//	//attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;
//
//	//// Support for the RGBA pixel type.
//	//attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
//	//attributeListInt[15] = WGL_TYPE_RGBA_ARB;
//
//	//// Support for a 8 bit stencil buffer.
//	//attributeListInt[16] = WGL_STENCIL_BITS_ARB;
//	//attributeListInt[17] = 8;
//
//	//// Null terminate the attribute list.
//	//attributeListInt[18] = 0;
//
//
//
//	////// Query for a pixel format that fits the attributes we want.
//	////result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
//	////if (result != 1)
//	////{
//	////	return false;
//	////}
//
//	////// If the video card/display can handle our desired pixel format then we set it as the current one.
//	////result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
//	////if (result != 1)
//	////{
//	////	return false;
//	////}
//
//	//// Set the 4.0 version of OpenGL in the attribute list.
//	//attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
//	//attributeList[1] = 3;
//	//attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
//	//attributeList[3] = 3;
//
//	//// Null terminate the attribute list.
//	//attributeList[4] = 0;
//
//	//// Create a OpenGL 4.0 rendering context.
//	//m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);
//	//if (m_renderingContext == NULL)
//	//{
//	//	return false;
//	//}
//
//	//// Set the rendering context to active.
//	//result = wglMakeCurrent(m_deviceContext, m_renderingContext);
//	//if (result != 1)
//	//{
//	//	return false;
//	//}
//
//	//// Set the depth buffer to be entirely cleared to 1.0 values.
//	//glClearDepth(1.0f);
//
//	//// Enable depth testing.
//	//glEnable(GL_DEPTH_TEST);
//
//	//// Set the polygon winding to front facing for the left handed system.
//	//glFrontFace(GL_CW);
//
//	//// Enable back face culling.
//	//glEnable(GL_CULL_FACE);
//	//glCullFace(GL_BACK);
//
//	//// Initialize the world/model matrix to the identity matrix.
//	//BuildIdentityMatrix(m_worldMatrix);
//
//	//// Set the field of view and screen aspect ratio.
//	//fieldOfView = 3.14159265358979323846f / 4.0f;
//	//screenAspect = (float)screenWidth / (float)screenHeight;
//
//	//// Build the perspective projection matrix.
//	//BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);
//
//	//// Get the name of the video card.
//	//vendorString = (char*)glGetString(GL_VENDOR);
//	//rendererString = (char*)glGetString(GL_RENDERER);
//	//char* glVersion = (char*)glGetString(GL_VERSION);
//
//	//// Store the video card name in a class member variable so it can be retrieved later.
//	////strcpy_s(m_videoCardDescription, vendorString);
//	////strcat_s(m_videoCardDescription, " - ");
//	////strcat_s(m_videoCardDescription, rendererString);
//	////MessageBoxA(hwnd, m_videoCardDescription, "Tarjeta grafica", MB_OK);
//	////MessageBoxA(hwnd, glVersion,"Open GL Version",MB_OK);
//
//	//// Turn on or off the vertical sync depending on the input bool value.
//	//if (vsync)
//	//{
//	//	result = wglSwapIntervalEXT(1);
//	//}
//	//else
//	//{
//	//	result = wglSwapIntervalEXT(0);
//	//}
//
//	//// Check if vsync was set correctly.
//	//if (result != 1)
//	//{
//	//	return false;
//	//}
//
//	return true;
//}
//bool OpenGLClass::LoadExtensionListGLFW()
//{
//	ConfigureOpenGL();
//
//
//
//
//	glAttachShader = (PFNGLATTACHSHADERPROC)glfwGetProcAddress("glAttachShader");
//	if (!glAttachShader)
//	{
//		return false;
//	}
//
//	glBindBuffer = (PFNGLBINDBUFFERPROC)glfwGetProcAddress("glBindBuffer");
//	if (!glBindBuffer)
//	{
//		return false;
//	}
//
//	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glfwGetProcAddress("glBindVertexArray");
//	if (!glBindVertexArray)
//	{
//		return false;
//	}
//
//	glBufferData = (PFNGLBUFFERDATAPROC)glfwGetProcAddress("glBufferData");
//	if (!glBufferData)
//	{
//		return false;
//	}
//
//	glCompileShader = (PFNGLCOMPILESHADERPROC)glfwGetProcAddress("glCompileShader");
//	if (!glCompileShader)
//	{
//		return false;
//	}
//
//	glCreateProgram = (PFNGLCREATEPROGRAMPROC)glfwGetProcAddress("glCreateProgram");
//	if (!glCreateProgram)
//	{
//		return false;
//	}
//
//	glCreateShader = (PFNGLCREATESHADERPROC)glfwGetProcAddress("glCreateShader");
//	if (!glCreateShader)
//	{
//		return false;
//	}
//
//	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glfwGetProcAddress("glDeleteBuffers");
//	if (!glDeleteBuffers)
//	{
//		return false;
//	}
//
//	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
//	if (!glDeleteProgram)
//	{
//		return false;
//	}
//
//	glDeleteShader = (PFNGLDELETESHADERPROC)glfwGetProcAddress("glDeleteShader");
//	if (!glDeleteShader)
//	{
//		return false;
//	}
//
//	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glfwGetProcAddress("glDeleteVertexArrays");
//	if (!glDeleteVertexArrays)
//	{
//		return false;
//	}
//
//	glDetachShader = (PFNGLDETACHSHADERPROC)glfwGetProcAddress("glDetachShader");
//	if (!glDetachShader)
//	{
//		return false;
//	}
//
//	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glEnableVertexAttribArray");
//	if (!glEnableVertexAttribArray)
//	{
//		return false;
//	}
//
//	glGenBuffers = (PFNGLGENBUFFERSPROC)glfwGetProcAddress("glGenBuffers");
//	if (!glGenBuffers)
//	{
//		return false;
//	}
//
//	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glfwGetProcAddress("glGenVertexArrays");
//	if (!glGenVertexArrays)
//	{
//		return false;
//	}
//
//	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glfwGetProcAddress("glGetAttribLocation");
//	if (!glGetAttribLocation)
//	{
//		return false;
//	}
//
//	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glfwGetProcAddress("glGetProgramInfoLog");
//	if (!glGetProgramInfoLog)
//	{
//		return false;
//	}
//
//	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glfwGetProcAddress("glGetProgramiv");
//	if (!glGetProgramiv)
//	{
//		return false;
//	}
//
//	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glfwGetProcAddress("glGetShaderInfoLog");
//	if (!glGetShaderInfoLog)
//	{
//		return false;
//	}
//
//	glGetShaderiv = (PFNGLGETSHADERIVPROC)glfwGetProcAddress("glGetShaderiv");
//	if (!glGetShaderiv)
//	{
//		return false;
//	}
//
//	glLinkProgram = (PFNGLLINKPROGRAMPROC)glfwGetProcAddress("glLinkProgram");
//	if (!glLinkProgram)
//	{
//		return false;
//	}
//
//	glShaderSource = (PFNGLSHADERSOURCEPROC)glfwGetProcAddress("glShaderSource");
//	if (!glShaderSource)
//	{
//		return false;
//	}
//
//	glUseProgram = (PFNGLUSEPROGRAMPROC)glfwGetProcAddress("glUseProgram");
//	if (!glUseProgram)
//	{
//		return false;
//	}
//
//	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glfwGetProcAddress("glVertexAttribPointer");
//	if (!glVertexAttribPointer)
//	{
//		return false;
//	}
//
//	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glfwGetProcAddress("glBindAttribLocation");
//	if (!glBindAttribLocation)
//	{
//		return false;
//	}
//
//	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glfwGetProcAddress("glGetUniformLocation");
//	if (!glGetUniformLocation)
//	{
//		return false;
//	}
//
//	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glfwGetProcAddress("glUniformMatrix4fv");
//	if (!glUniformMatrix4fv)
//	{
//		return false;
//	}
//
//	glActiveTexture = (PFNGLACTIVETEXTUREPROC)glfwGetProcAddress("glActiveTexture");
//	if (!glActiveTexture)
//	{
//		return false;
//	}
//
//	glUniform1i = (PFNGLUNIFORM1IPROC)glfwGetProcAddress("glUniform1i");
//	if (!glUniform1i)
//	{
//		return false;
//	}
//
//	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)glfwGetProcAddress("glGenerateMipmap");
//	if (!glGenerateMipmap)
//	{
//		return false;
//	}
//
//	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glfwGetProcAddress("glDisableVertexAttribArray");
//	if (!glDisableVertexAttribArray)
//	{
//		return false;
//	}
//
//	glUniform3fv = (PFNGLUNIFORM3FVPROC)glfwGetProcAddress("glUniform3fv");
//	if (!glUniform3fv)
//	{
//		return false;
//	}
//
//	glUniform4fv = (PFNGLUNIFORM4FVPROC)glfwGetProcAddress("glUniform4fv");
//	if (!glUniform4fv)
//	{
//		return false;
//	}
//
//	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glfwGetProcAddress("glDeleteProgram");
//	if (!glDeleteProgram)
//	{
//		return false;
//	}
//
//	// Verificar que todas las funciones estén cargadas
//	if (!glAttachShader || !glCreateShader || !glShaderSource || !glCompileShader ||
//		!glCreateProgram || !glLinkProgram || !glUseProgram || !glGetShaderiv || !glGetShaderInfoLog) {
//		return false;
//	}
//
//
//	//// Load the OpenGL extensions that this application will be using.
//	//wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
//	//if (!wglChoosePixelFormatARB)
//	//{
//	//	return false;
//	//}
//
//	//wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
//	//if (!wglCreateContextAttribsARB)
//	//{
//	//	return false;
//	//}
//
//	//wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
//	//if (!wglSwapIntervalEXT)
//	//{
//	//	return false;
//	//}
//
//	//glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
//	//if (!glAttachShader)
//	//{
//	//	return false;
//	//}
//
//	//glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
//	//if (!glBindBuffer)
//	//{
//	//	return false;
//	//}
//
//	//glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
//	//if (!glBindVertexArray)
//	//{
//	//	return false;
//	//}
//
//	//glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
//	//if (!glBufferData)
//	//{
//	//	return false;
//	//}
//
//	//glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
//	//if (!glCompileShader)
//	//{
//	//	return false;
//	//}
//
//	//glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
//	//if (!glCreateProgram)
//	//{
//	//	return false;
//	//}
//
//	//glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
//	//if (!glCreateShader)
//	//{
//	//	return false;
//	//}
//
//	//glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
//	//if (!glDeleteBuffers)
//	//{
//	//	return false;
//	//}
//
//	//glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
//	//if (!glDeleteProgram)
//	//{
//	//	return false;
//	//}
//
//	//glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
//	//if (!glDeleteShader)
//	//{
//	//	return false;
//	//}
//
//	//glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
//	//if (!glDeleteVertexArrays)
//	//{
//	//	return false;
//	//}
//
//	//glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
//	//if (!glDetachShader)
//	//{
//	//	return false;
//	//}
//
//	//glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
//	//if (!glEnableVertexAttribArray)
//	//{
//	//	return false;
//	//}
//
//	//glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
//	//if (!glGenBuffers)
//	//{
//	//	return false;
//	//}
//
//	//glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
//	//if (!glGenVertexArrays)
//	//{
//	//	return false;
//	//}
//
//	//glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
//	//if (!glGetAttribLocation)
//	//{
//	//	return false;
//	//}
//
//	//glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
//	//if (!glGetProgramInfoLog)
//	//{
//	//	return false;
//	//}
//
//	//glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
//	//if (!glGetProgramiv)
//	//{
//	//	return false;
//	//}
//
//	//glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
//	//if (!glGetShaderInfoLog)
//	//{
//	//	return false;
//	//}
//
//	//glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
//	//if (!glGetShaderiv)
//	//{
//	//	return false;
//	//}
//
//	//glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
//	//if (!glLinkProgram)
//	//{
//	//	return false;
//	//}
//
//	//glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
//	//if (!glShaderSource)
//	//{
//	//	return false;
//	//}
//
//	//glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
//	//if (!glUseProgram)
//	//{
//	//	return false;
//	//}
//
//	//glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
//	//if (!glVertexAttribPointer)
//	//{
//	//	return false;
//	//}
//
//	//glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
//	//if (!glBindAttribLocation)
//	//{
//	//	return false;
//	//}
//
//	//glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
//	//if (!glGetUniformLocation)
//	//{
//	//	return false;
//	//}
//
//	//glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
//	//if (!glUniformMatrix4fv)
//	//{
//	//	return false;
//	//}
//
//	//glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
//	//if (!glActiveTexture)
//	//{
//	//	return false;
//	//}
//
//	//glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
//	//if (!glUniform1i)
//	//{
//	//	return false;
//	//}
//
//	//glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
//	//if (!glGenerateMipmap)
//	//{
//	//	return false;
//	//}
//
//	//glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
//	//if (!glDisableVertexAttribArray)
//	//{
//	//	return false;
//	//}
//
//	//glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
//	//if (!glUniform3fv)
//	//{
//	//	return false;
//	//}
//
//	//glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
//	//if (!glUniform4fv)
//	//{
//	//	return false;
//	//}
//
//	//return true;
//	//glewExperimental = GL_TRUE; // Recomendado para algunos drivers
//	//GLenum result = glewInit();
//	//if (result != GLEW_OK) {
//	//	return false;
//	//}
//	return true;
//
//
//}
////bool OpenGLClass::InitializeExtensions() {
////	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
////		return false;
////	}
////	return true;
////}
//bool OpenGLClass::Initialize(int screenWidth, int screenHeight, const char* windowTitle, bool vsync) {
//	this->m_screenWidth = screenWidth;
//	this->m_screenHeight = screenHeight;
//
//	// Inicializar GLFW
//	if (!glfwInit()) {
//		std::cerr << "Error: No se pudo inicializar GLFW." << std::endl;
//		return false;
//	}
//
//	// Configuración del contexto de OpenGL (3.3 Core)
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	// Crear ventana
//	m_window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, nullptr, nullptr);
//	if (!m_window) {
//		std::cerr << "Error: No se pudo crear la ventana GLFW." << std::endl;
//		glfwTerminate();
//		return false;
//	}
//
//	// Hacer que el contexto de OpenGL sea actual
//	glfwMakeContextCurrent(m_window);
//
//	// Configurar VSync
//	glfwSwapInterval(vsync ? 1 : 0);
//
//	// Inicializar extensiones de OpenGL (GLAD/GLLoader puede ser requerido)
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cerr << "Error: No se pudo inicializar las extensiones de OpenGL." << std::endl;
//		return false;
//	}
//
//	// Configuraciones de OpenGL por defecto
//	glViewport(0, 0, screenWidth, screenHeight);
//	glEnable(GL_DEPTH_TEST);
//	glCullFace(GL_BACK);
//	glFrontFace(GL_CW);
//
//	return true;
//}
//void OpenGLClass::GetWindowSize(int& width, int& height) const {
//	glfwGetFramebufferSize(m_window, &width, &height);
//}
//void OpenGLClass::GetVideoCardInfo(std::string& cardInfo) const {
//	const GLubyte* vendor = glGetString(GL_VENDOR);
//	const GLubyte* renderer = glGetString(GL_RENDERER);
//	cardInfo = std::string(reinterpret_cast<const char*>(vendor)) + " - " +
//		std::string(reinterpret_cast<const char*>(renderer));
//}
////NO USAR