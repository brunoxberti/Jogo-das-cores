#pragma once
#include <time.h>
#include "Retangulo.h"
class ControladorRetangulo
{
public:

	//Linhas e colunas trocados
	Retangulo* retornaRetangulos(int linhas, int colunas) {

		float lenght = 2 / (float)linhas;

		if ((lenght / 2) * colunas > 2) {
			throw ("Muito Alto");
		}

		Retangulo* retangulos = new Retangulo[linhas * colunas];

		for (int i = 0; i < colunas; i++) {
			for (int j = 0; j < linhas; j++) {
				retangulos[j + (i * linhas)] = Retangulo(-(lenght * (float)j) + 1, -(lenght * 0.5 * (float)i) + 1, lenght);
			}
		}


		return retangulos;
	}

	//Linhas e colunas trocados
	Retangulo* retornaRetangulosComPad(int linhas, int colunas, float topPad, float leftPad, float rightPad) {


		printf("\nleftPad: %f \nrightPad: %f\n", leftPad, rightPad);

		float lenght = (2.0f - leftPad - rightPad) / (float)linhas;

		float x;
		float y;

		if ((lenght / 2) * colunas > 2 - topPad) {
			printf("%f", (lenght / 2) * colunas);
			throw ("Muito Alto");
		}

		Retangulo* retangulos = new Retangulo[linhas * colunas];

		for (int i = 0; i < colunas; i++) {
			for (int j = 0; j < linhas; j++) {
				x = -(lenght * (float)j) + 1 - rightPad;
				y = -(lenght * 0.5 * (float)i) + 1 - topPad;
				retangulos[j + (i * linhas)] = Retangulo(x, y, lenght);
			}
		}


		return retangulos;

	}


	
	Retangulo* retornaRetangulosComMaisPad(int linhas, int colunas, float topPad, float leftPad, float rightPad, float IntraXPad, float IntraYPad) {


		//printf("\nleftPad: %f \nrightPad: %f\n", leftPad, rightPad);

		float lenght = (2.0f - leftPad - rightPad - (IntraXPad*(colunas-1))) / (float)colunas;
		//printf("lenght no funcao: %f\n", lenght);

		float x;
		float y;

		if ((lenght / 2) * linhas > 2 - topPad) {
			printf("%f", (lenght / 2) * linhas);
			throw ("Muito Alto");
		}

		Retangulo* retangulos = new Retangulo[linhas * colunas];

		for (int i = 0; i < linhas; i++) {
			for (int j = 0; j < colunas; j++) {
				x = -1 + (lenght * (float)j)  + rightPad + (IntraXPad * j);
				y = -(lenght * 0.5 * (float)i) + 1 - topPad - (IntraYPad*i);
				retangulos[j + (i * colunas)] = Retangulo(x, y, lenght);
			}
		}


		return retangulos;
	}



};

