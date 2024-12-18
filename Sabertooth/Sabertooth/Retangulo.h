#pragma once
#include <cstdlib>
#include <GL/glew.h>
#include <stdio.h>
#include <time.h>

// Todos os retangulos são 2 vezes mais largos que altos
class Retangulo{

public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;

	float posX;
	float posY;

	float lenght;

	Retangulo() {
		red = rand() % 256;
		green = rand() % 256;
		blue = rand() % 256;

		posX = 0;
		posY = 0;

		lenght = 1;
	}

	Retangulo(float x, float y) {
		red = rand() % 256;
		green = rand() % 256;
		blue = rand() % 256;

		posX = x;
		posY = y;

		lenght = 1;
	}

	Retangulo(float x, float y, float size) {
		red = rand() % 256;
		green = rand() % 256;
		blue = rand() % 256;

		posX = x;
		posY = y;

		lenght = size;
	}

	void imprimeCores() {
		printf("Vermelho: %i\nVerde: %i\nAzul %i\n\n",red, green, blue);
	}

	GLfloat *retornaCordenadas() {
		GLfloat *vertices = new GLfloat[18];

		float zero = 0.0f;
		//printf("\nO Valor de zero é % f\n",zero);


		// Esse é o unico jeito que funciona. vertices[2], vertices[5],... = zero; da erro
		vertices[0] = posX;
		vertices[1] = posY;
		vertices[2] = zero;
		vertices[3] = posX + lenght;
		vertices[4] = posY;
		vertices[5] = zero;
		vertices[6] = posX;
		vertices[7] = posY - (lenght / 2);
		vertices[8] = zero;
		vertices[9] = posX;
		vertices[10] = posY - (lenght / 2);
		vertices[11] = zero;
		vertices[12] = posX + lenght;
		vertices[14] = zero;
		vertices[13] = posY - (lenght / 2);
		vertices[15] = posX + lenght;
		vertices[16] = posY;
		vertices[17] = zero;

	/*
		 GLfloat vertices[] = {
	  posX,  posY, 0.0f,
	   posX + lenght,  posY, 0.0f,                       
	   posX, posY + (lenght/2), 0.0f,                       
	   posX, posY + (lenght / 2), 0.0f,
	  posX + lenght,  posY + (lenght / 2), 0.0f,                       
	  posX,  posY, 0.0f,
		};
		*/
		 
		/*
		 printf("\nEnviando %llu Bytes\n", sizeof(*vertices));
		 for (int i = 0; i < 18; i++) {
			 printf("O %d elemento do array é %f\n", i, vertices[i]);
		 }
		 printf("\n\n");
		 */

		 return vertices;
	}



};

