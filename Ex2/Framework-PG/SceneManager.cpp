#include "SceneManager.h"

//static controllers for mouse and keyboard
static bool keys[1024];
static bool resized;
static GLuint width, height;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::initialize(GLuint w, GLuint h)
{
	stickerAtual = 0;
	width = w;
	height = h;

	X[0] = 550;
	Y[0] = 500;


	X[1] = 650;
	Y[1] = 500;
	
	X[2] = 650;
	Y[2] = 400;
	
	X[3] = 550;
	Y[3] = 400;
	
	X[4] = 650;
	Y[4] = 300;

	X[5] = 550;
	Y[5] = 300;

	X[6] = 650;
	Y[6] = 200;

	X[7] = 550;
	Y[7] = 200;

	for (int i = 0; i < 8; i++)
	{
		Xtam[i] = 100;
		Ytam[i] = 75;
	}
	
	// GLFW - GLEW - OPENGL general setup -- TODO: config file
	initializeGraphics();

}

void SceneManager::initializeGraphics()
{
	// Init GLFW
	glfwInit();

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(width, height, "Hello Sprites", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);

	//Setando a callback de redimensionamento da janela
	glfwSetWindowSizeCallback(window, resize);
	
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Build and compile our shader program

	addShader("../shaders/transformations.vs", "../shaders/transformations.frag");
	addShader("../shaders/Grayscale.vs", "../shaders/Grayscale.frag");
	addShader("../shaders/Colorizacao.vs", "../shaders/Colorizacao.frag");
	addShader("../shaders/Inversao.vs", "../shaders/Inversao.frag");
	addShader("../shaders/Binarizacao.vs", "../shaders/Binarizacao.frag");
	addShader("../shaders/Louco.vs", "../shaders/Louco.frag");
	addShader("../shaders/Vignete.vs", "../shaders/Vignete.frag");


	//setup the scene -- LEMBRANDO QUE A DESCRI??O DE UMA CENA PODE VIR DE ARQUIVO(S) DE 
	// CONFIGURA??O
	setupScene();

	resized = true; //para entrar no setup da c?mera na 1a vez

}

void SceneManager::addShader(string vFilename, string fFilename)
{
        Shader *shader = new Shader (vFilename.c_str(), fFilename.c_str());
		shaders.push_back(shader);
}


void SceneManager::key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}
}

void SceneManager::resize(GLFWwindow * window, int w, int h)
{
	width = w;
	height = h;
	resized = true;

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
}


void SceneManager::update()
{
	if (keys[GLFW_KEY_ESCAPE])
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	if (keys[GLFW_KEY_0])
	{
		ShaderAtual = 0;
        trocaDeShader();
	}
	if (keys[GLFW_KEY_1])
	{
		ShaderAtual = 1;
		trocaDeShader();
	}
	if (keys[GLFW_KEY_2])
	{
		
		ShaderAtual = 2;
	    trocaDeShader();
	}
	if (keys[GLFW_KEY_3])
	{
		ShaderAtual = 3;
		trocaDeShader();
	}
	if (keys[GLFW_KEY_4])
	{
		ShaderAtual = 4;
		trocaDeShader();
	}
	if (keys[GLFW_KEY_5])
	{
		ShaderAtual = 5;
		trocaDeShader();
	}
	if (keys[GLFW_KEY_6])
	{
		ShaderAtual = 6;
		trocaDeShader();
	}

	//glm::vec3  a(X[0], Y[0], 0);
	//if(GetCursorPosX ==  a))
	if (keys[GLFW_KEY_T])
	{
		stickerAtual = stickerAtual + 1;
		if (stickerAtual == 8)
		{
			stickerAtual = 0;
		}
	}
	if (keys[GLFW_KEY_W])
	{
		Y[stickerAtual]++;
	}
	if (keys[GLFW_KEY_S])
	{
		Y[stickerAtual]--;
	}
	if (keys[GLFW_KEY_A])
	{
		X[stickerAtual]--;
	}
	if (keys[GLFW_KEY_D])
	{
		X[stickerAtual]++;
	}
	if (keys[GLFW_KEY_Q])
	{
		Xtam[stickerAtual]++;
		Ytam[stickerAtual]++;
	}
	if (keys[GLFW_KEY_E])
	{
		Xtam[stickerAtual]--;
		Ytam[stickerAtual]--;
	}
	objects[stickerAtual + 8]->setPosition(glm :: vec3 (X[stickerAtual], Y[stickerAtual], 0));
	objects[stickerAtual + 8]->setDimension(glm::vec3(Xtam[stickerAtual], Ytam[stickerAtual], 1.0f));
	
	
	//AQUI aplicaremos as transforma??es nos sprites
	
	//altera o angulo do segundo objeto
	/*objects[1]->setAngle((float)glfwGetTime());*/
}

void SceneManager::render()
{
	// Clear the colorbuffer
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	if (resized) //se houve redimensionamento na janela, redefine a projection matrix
	{
		setupCamera2D();
		resized = false;
	}

	//atualiza e desenha os Sprites

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->update();
		if (i == 16|| i==6)
		{
			glActiveTexture(GL_TEXTURE1);
			glUniform1i(glGetUniformLocation(shaders[6]->ID, "ourTexture2"), 1);
			glBindTexture(GL_TEXTURE_2D, textureMaskID);
		}
		objects[i]->draw();
	}
	

}

void SceneManager::trocaDeShader()
{
	
	switch (ShaderAtual)
	{
	case 0:
		objects[6]->setShader(shaders[ShaderAtual]);
		shaders[ShaderAtual]->setInt("code", 2);
		break;
	case 1:
		objects[6]->setShader(shaders[ShaderAtual]);
		
		break;
	case 2:
		objects[6]->setShader(shaders[ShaderAtual]);
		shaders[ShaderAtual]->setVec3("corColorizadora", 1.0, 0.0, 0.0);
		break;
	case 3:
		objects[6]->setShader(shaders[ShaderAtual]);
		break;
	case 4:
		objects[6]->setShader(shaders[ShaderAtual]);
		shaders[ShaderAtual]->setInt("limiar", 124);
		break;
	case 5:
		objects[6]->setShader(shaders[ShaderAtual]);
		shaders[ShaderAtual]->setInt("limiar", 124);
		break;

	case 6:
		objects[6]->setShader(shaders[ShaderAtual]);
		break;
	default:
		break;
	}

	

}

void SceneManager::run()
{
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Update method(s)
		update();

		//Render scene
		render();
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
}

void SceneManager::finish()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}


void SceneManager::setupScene()
{
	//Cria??o dos Sprites iniciais -- pode-se fazer m?todos de cria??o posteriormente
	Sprite* obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 300.0f, 0.0));
	obj->setDimension(glm::vec3(800.0f, 600.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[0]);
	objects.push_back(obj); //adiciona o primeiro obj
	shaders[0]->setInt("code", 0);
	
	//M?nimo: posicao e escala e ponteiro para o shader
	obj = new Sprite;
	obj->setPosition(glm::vec3(500.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[5]);
	objects.push_back(obj); //adiciona o primeiro obj
	shaders[5]->setInt("limiar", 124);

	//Adicionando mais um
	obj = new Sprite;
	obj->setPosition(glm::vec3(300.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[3]);
	objects.push_back(obj); //adiciona o segundo obj
	
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(400.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[4]);
	objects.push_back(obj);
	shaders[4]->setInt("limiar", 124);

	obj = new Sprite;
	obj->setPosition(glm::vec3(200.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[2]);
	objects.push_back(obj);
	shaders[2]->setVec3("corColorizadora", 1.0, 0.0, 0.0);


	obj = new Sprite;
	obj->setPosition(glm::vec3(100.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[1]);
	objects.push_back(obj);
	

	obj = new Sprite;
	obj->setPosition(glm::vec3(240.0f,350.0f, 0.0));
	obj->setDimension(glm::vec3(375.0f, 375.0f, 1.0f));
	obj->setShader(shaders[ShaderAtual]);
	objects.push_back(obj);
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(600.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
    shaders[0]->setInt("code", 2);
	
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(X[0], Y[0], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(X[1], Y[1], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);
	
	obj = new Sprite;
	obj->setPosition(glm::vec3(X[2], Y[2], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);

	obj = new Sprite;
	obj->setPosition(glm::vec3(X[3], Y[3], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);

	obj = new Sprite;
	obj->setPosition(glm::vec3(X[4], Y[4], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);

	obj = new Sprite;
	obj->setPosition(glm::vec3(X[5], Y[5], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);

	obj = new Sprite;
	obj->setPosition(glm::vec3(X[6], Y[6], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);

	obj = new Sprite;
	obj->setPosition(glm::vec3(X[7], Y[7], 0.0));
	obj->setDimension(glm::vec3(100.0f, 75.0f, 1.0f));
	obj->setShader(shaders[0]);
	objects.push_back(obj);
	shaders[0]->setInt("code", 0);
	 

	obj = new Sprite;
	obj->setPosition(glm::vec3(700.0f, 75.0f, 0.0));
	obj->setDimension(glm::vec3(100.0f, 100.0f, 1.0f)); //note que depois podemos reescalar conforme tamanho da sprite
	obj->setShader(shaders[6]);
	objects.push_back(obj); //adiciona o primeiro obj
	

	








	//Carregamento das texturas (pode ser feito intercalado na cria??o)
	//Futuramente, utilizar classe de materiais e armazenar dimensoes, etc
	unsigned int texID = loadTexture("../textures/Fundo.png");
	objects[0]->setTexture(texID);
	texID = loadTexture("../textures/Atual.jpg");
	
	objects[1]->setTexture(texID);
	objects[2]->setTexture(texID);
	objects[3]->setTexture(texID);
	objects[4]->setTexture(texID);
	objects[5]->setTexture(texID);
	objects[6]->setTexture(texID);
	objects[7]->setTexture(texID);
	objects[16]->setTexture(texID);

	texID = loadTexture("../textures/Crush.png");
	objects[8]->setTexture(texID);
	texID = loadTexture("../textures/Daora.png");
	objects[9]->setTexture(texID);
	texID = loadTexture("../textures/Eita.png");
	objects[10]->setTexture(texID);
	texID = loadTexture("../textures/Top.png");
	objects[11]->setTexture(texID);
	texID = loadTexture("../textures/SeLiga.png");
	objects[12]->setTexture(texID);
	texID = loadTexture("../textures/Sinistro.png");
	objects[13]->setTexture(texID);
	texID = loadTexture("../textures/StayHome.png");
	objects[14]->setTexture(texID);
	texID = loadTexture("../textures/Tenso.png");
	objects[15]->setTexture(texID);


	textureMaskID = loadTexture("../textures/flores.png");

	//Definindo a janela do mundo (ortho2D)
	ortho2D[0] = 0.0f; //xMin
	ortho2D[1] = 800.0f; //xMax
	ortho2D[2] = 0.0f; //yMin
	ortho2D[3] = 600.0f; //yMax

	//Habilita transpar?ncia
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void SceneManager::setupCamera2D() //TO DO: parametrizar aqui
{
	float zNear = -1.0, zFar = 1.0; //est?o fixos porque n?o precisamos mudar

	projection = glm::ortho(ortho2D[0], ortho2D[1], ortho2D[2], ortho2D[3], zNear, zFar);

	for (int i = 0; i < shaders.size(); i++)
	{
		shaders[i]->Use();
		//Obtendo o identificador da matriz de proje??o para enviar para o shader
		GLint projLoc = glGetUniformLocation(shaders[i]->ID, "projection");
		//Enviando a matriz de proje??o para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	}
}

unsigned int SceneManager::loadTexture(string filename)
{
	unsigned int texture;

	// load and create a texture 
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);
	
	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.

	glActiveTexture(GL_TEXTURE0);

	return texture;
}
