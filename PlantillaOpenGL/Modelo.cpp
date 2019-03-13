#include "stdafx.h"
#include "Modelo.h"

Modelo::Modelo() {

}

void Modelo::inicializarVertexArray(GLuint posicionID, GLuint colorID) {

	// Crear un vertex array (triángulo)
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	// Crear un vertex buffer (triángulo)
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	// Llenado del buffer (triángulo)
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertice) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	// Habilitar atributos del Shader (cuadrado)
	glEnableVertexAttribArray(posicionID);
	glEnableVertexAttribArray(colorID);
	// Especificar a OpenGL cómo se va a comunicar (cuadrado)
	glVertexAttribPointer(posicionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertice), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertice), (void*)sizeof(vec3));

}

void Modelo::dibujar(GLenum mododibujo) {
	shader->enlazar();
	glBindVertexArray(vertexArrayID);
	glDrawArrays(mododibujo, 0, vertices.size());
	glBindVertexArray(0);
	shader->desenlazar();

}