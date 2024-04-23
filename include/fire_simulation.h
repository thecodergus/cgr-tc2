#ifndef FIRE_SIMULATION_H
#define FIRE_SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define ROW 300
#define COLUMN 300
#define FIREINTENSITY_SIZE 36

/**
 * @brief Definição da intensidade do fogo, onde cada valor representa uma cor correspondente à intensidade do fogo.
 */
extern int fireIntensity[FIREINTENSITY_SIZE];

/**
 * @brief Matriz de textura que armazena os valores de cor RGB para cada pixel.
 */
extern unsigned char textureData[ROW][COLUMN][3];

/**
 * @brief Matriz de tabela que armazena a intensidade do fogo para cada pixel.
 */
extern unsigned int table[ROW][COLUMN];

/**
 * @brief Função para definir a cor de um pixel com base na intensidade do fogo.
 *
 * @param i Coordenada x do pixel.
 * @param j Coordena da y do pixel.
 * @param fI Intensidade do fogo.
 */
void setColor(int i, int j, int fI);

/**
 * @brief Função para atualizar a intensidade do fogo em cada pixel.
 */
void fireLoop();

/**
 * @brief Função para renderizar a cena, chamando a função fireLoop para atualizar a intensidade do fogo e desenhando a textura na tela.
 */
void renderScene();

/**
 * @brief Função de callback chamada sempre que o tamanho do framebuffer é alterado.
 *
 * @param w Nova largura do framebuffer.
 * @param h Nova altura do framebuffer.
 */
void framebuffer_size_callback(int w, int h);

/**
 * @brief Função para configurar o ambiente OpenGL, incluindo a cor de fundo, a semente do gerador de números aleatórios, a inicialização da tabela de intensidade do fogo e a configuração da textura.
 */
void setup();

/**
 * @brief Função de callback chamada a cada 33 milissegundos para atualizar a cena.
 *
 * @param val Valor passado para a função de callback.
 */
void timerFunction(int val);

#endif