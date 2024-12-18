#pragma once
#include <math.h>

#include "Retangulo.h"
#include "ControladorRetangulo.h"

#define distMax 441.67296
#define MAX(a,b) (((a)>(b))?(a):(b))

class GameController
{
public:

	int linhas;
	int colunas;

	float topPad;
	float leftPad;
	float rightPad;
	float intraXPad;
	float intraYPad;

	float tolerancia;
	Retangulo* listaDeRetangulos;
	bool* ativos;

	int pontos;
	int desativados;
	int rodada;
	


	GameController(int linhasParam, int colunasParam, float topPading, float leftPading, float rightPadding, float intraXPadding, float intraYPading, float toleranciaParam) {
		
		linhas = linhasParam;
		colunas = colunasParam;

		topPad = topPading;
		leftPad = leftPading;
		rightPad = rightPadding;
		intraXPad = intraXPadding;
		intraYPad = intraYPading;

		tolerancia = toleranciaParam;

		ControladorRetangulo controladorRetangulo = ControladorRetangulo();

		listaDeRetangulos = controladorRetangulo.retornaRetangulosComMaisPad(linhas,colunas,topPad,leftPad,rightPad,intraXPad,intraYPad);
		ativos = new bool[linhas * colunas];
		


		pontos, desativados, rodada = -1;
	}

	void comecarJogo() {
		pontos = 0;
		desativados = 0;
		rodada = 1;
		for (int i = 0; i < linhas * colunas; i++) {
			ativos[i] = true;
		}

	}

	int fazerRodada(int linh, int colum) {
		if (ativos[colum + (linh * colunas)]) {
			int red = listaDeRetangulos[colum + (linh * colunas)].red;
			int green = listaDeRetangulos[colum + (linh * colunas)].green;
			int blue = listaDeRetangulos[colum + (linh * colunas)].blue;

			int retirados = 1;
			ativos[colum + (linh * colunas)] = false;

			for (int i = 0; i < linhas * colunas; i++) {
				if (ativos[i]) {
					//printf("\n%f", sqrt(pow(red - listaDeRetangulos[i].red, 2) + pow(green - listaDeRetangulos[i].green, 2) + pow(blue - listaDeRetangulos[i].blue, 2)));
					if (distMax*tolerancia >= sqrt(pow(red - listaDeRetangulos[i].red, 2) + pow(green - listaDeRetangulos[i].green, 2) + pow(blue - listaDeRetangulos[i].blue, 2))) {
						retirados++;
						ativos[i] = false;
					}
				}
			}

			desativados += retirados;
			pontos += MAX((11 - rodada), 1) * retirados;
			rodada++;

			return retirados;

		}
		return 0;
	}

	void imprimePontos() {
		printf("\nPontos: %d\n", pontos);
	}

	void imprimeRodada() {
		printf("\nRodada: %d\n", rodada);
	}

	bool acabou() {
		if (desativados >= (linhas * colunas)) {

			printf("\nO Jogo Acabou\n");
			printf("Foram %d Rodadas e %d Pontos",(rodada-1),pontos );
			return true;
		}
		return false;
	}




};