#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

#include "Shader.h"
#include "Vertice.h"

using namespace std;

void dibujar();
void actualizar();
void inicializarTriangulo();
void inicializarCuadrado();
void inicializarChichenItza();

Shader *shader;
GLuint posicionID;
GLuint colorID;

Modelo *triangulo;
Modelo *cuadrado;

int main()
{
	// Creamos una ventana
	GLFWwindow *window;

	// Si no se puede inicializar glfw, finalizamos la ejecucion
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}

	// Si se pudo iniciar GLFW, entonces inicializamos la ventana
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	// Si no podemos iniciar la ventana, terminamos ejecucion
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//Establecemos el contexto
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto, activamos funciones modernas
	glewExperimental = true;
	GLenum errorGlew = glewInit();
	if (errorGlew != GLEW_OK) {
		cout << glewGetErrorString(errorGlew);
	}

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL << std::endl;

	//inicializarTriangulo();
	//inicializarCuadrado();
	inicializarChichenItza();

	const char *rutaVertex = "VertexShader.shader";
	const char *rutaFragment = "FragmentShader.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	// Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");

	// Desenlazar el shader
	shader->desenlazar();

	// Crear un vertex array (triángulo)
	glGenVertexArrays(1, &vertexArrayTrianguloID);
	glBindVertexArray(vertexArrayTrianguloID);
	// Crear un vertex buffer (triángulo)
	glGenBuffers(1, &bufferTrianguloID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferTrianguloID);
	// Llenado del buffer (triángulo)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * triangulo.size(), triangulo.data(), GL_STATIC_DRAW);
	// Memoria consumida * Número de elementos (vértices) que tiene el vector

	// Habilitar atributos del Shader (cuadrado)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (cuadrado)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Vertex Array + Búffer (cuadrado)
	glGenVertexArrays(1, &vertexArrayCuadradoID);
	glBindVertexArray(vertexArrayCuadradoID);
	glGenBuffers(1, &bufferCuadradoID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferCuadradoID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * cuadrado.size(), cuadrado.data(), GL_STATIC_DRAW);

	// Habilitar atributos del Shader (chichen itzá)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (chichen itzá)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Vertex Array + Búffer (chichen itzá)
	glGenVertexArrays(1, &vertexArrayChichenItzaID);
	glBindVertexArray(vertexArrayChichenItzaID);
	glGenBuffers(1, &bufferChichenItzaID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferChichenItzaID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * chichenItza.size(), cuadrado.data(), GL_STATIC_DRAW);

	// Habilitar atributos del Shader (Triangulo)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (Triangulo)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));
	// Soltar vertex array y buffer
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Ciclo de dibujo (Draw loop)
	while (!glfwWindowShouldClose(window)) {

		// Establecer region de dibujo
		glViewport(0, 0, 1024, 768);

		// Establece el color de borrado
		glClearColor(.23, 0.3, 0.3, 1);

		// Borramos
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo
		dibujar();
		actualizar();

		// Cambiar los buffers
		glfwSwapBuffers(window);

		// Reconocer si hay entradas
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void dibujar()
{
	// Elegir el Shader
	shader->enlazar();

	// Elegir un vertex array
	glBindVertexArray(vertexArrayTrianguloID);

	// Dibujar
	glDrawArrays(GL_TRIANGLES, 0, triangulo.size());

	// Dibujar Cuadrado
	glBindVertexArray(vertexArrayCuadradoID);
	glDrawArrays(GL_POLYGON, 0, cuadrado.size());

	// Dibujar Chichen Itzá
	glBindVertexArray(vertexArrayChichenItzaID);
	glDrawArrays(GL_POLYGON, 0, chichenItza.size());

	// Soltar el vertex array
	glBindVertexArray(0);

	// Soltar el Shader
	shader->desenlazar();
}

void actualizar()
{

}

void inicializarTriangulo()
{
	Vertice v1 =
	{
		vec3(0.0f, 0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(-0.3f, -0.3f, 0.0f),
		vec4(1.0f, 0.8f, 0.0f, 1.0f)
	};

	triangulo->vertices.push_back(v1);
	triangulo->vertices.push_back(v2);
	triangulo->vertices.push_back(v3);
}

void inicializarCuadrado()
{
	Vertice v1 =
	{
		vec3(1.0f, 0.0f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(0.5f, 0.0f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(0.5f, 0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v4 =
	{
		vec3(1.0f, 0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};

	cuadrado->vertices.push_back(v1);
	cuadrado->vertices.push_back(v2);
	cuadrado->vertices.push_back(v3);
	cuadrado->vertices.push_back(v4);
}

void inicializarChichenItza()
{
	// Primer Rectángulo
	Vertice v1 =
	{
		vec3(-0.95f, -0.95f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v2 =
	{
		vec3(-0.95f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v3 =
	{
		vec3(-0.87f, -0.8f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Segundo Rectángulo
	Vertice v4 =
	{
		vec3(-0.87f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v5 =
	{
		vec3(-0.79f, -0.65f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Tercer Rectángulo
	Vertice v6 =
	{
		vec3(-0.79f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v7 =
	{
		vec3(-0.71f, -0.5f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	// Cuarto Rectángulo
	Vertice v8 =
	{
		vec3(-0.71f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	Vertice v9 =
	{
		vec3(-0.63f, -0.35f, 0.0f),
		vec4(0.4f, 0.5f, 0.2f, 1.0f)
	};
	


	cuadrado.push_back(v1);
	cuadrado.push_back(v2);
	cuadrado.push_back(v3);
	cuadrado.push_back(v4);

}