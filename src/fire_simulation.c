#include "fire_simulation.h"

// Definição da intensidade do fogo, onde cada valor representa uma cor correspondente à intensidade do fogo
int fireIntensity[FIREINTENSITY_SIZE] = {
    0x070707, 0x1f0707, 0x2f0f07,
    0x470f07, 0x571707, 0x671f07,
    0x771f07, 0x8f2707, 0x9f2f07,
    0xaf3f07, 0xbf4707, 0xc74707,
    0xDF4F07, 0xDF5707, 0xDF5707,
    0xD75F07, 0xD7670F, 0xcf6f0f,
    0xcf770f, 0xcf7f0f, 0xCF8717,
    0xC78717, 0xC78F17, 0xC7971F,
    0xBF9F1F, 0xBF9F1F, 0xBFA727,
    0xBFA727, 0xBFAF2F, 0xB7AF2F,
    0xB7B72F, 0xB7B737, 0xCFCF6F,
    0xDFDF9F, 0xEFEFC7, 0xFFFFFF};

// Matriz de textura que armazena os valores de cor RGB para cada pixel
unsigned char textureData[ROW][COLUMN][3];

// Matriz de tabela que armazena a intensidade do fogo para cada pixel
unsigned int table[ROW][COLUMN];

// Função para definir a cor de um pixel com base na intensidade do fogo
void setColor(int i, int j, int fI)
{
    int R = (fI & 0xff0000) >> 16;
    int G = (fI & 0x00ff00) >> 8;
    int B = (fI & 0x0000ff);

    textureData[i][j][0] = R;
    textureData[i][j][1] = G;
    textureData[i][j][2] = B;
}

// Função para atualizar a intensidade do fogo em cada pixel
void fireLoop()
{
    int i, j;
    for (i = ROW - 1; i > 0; i--)
    {
        for (j = 0; j < COLUMN; j++)
        {
            if (i != 0)
            {
                int fireIntensity = (table[i - 1][j] - (int)rand() % 3);
                if (fireIntensity >= 0)
                    table[i][j] = fireIntensity;
                else
                    table[i][j] = 0;
            }
        }
    }
}

// Função para renderizar a cena, chamando a função fireLoop para atualizar a intensidade do fogo e desenhando a textura na tela
void renderScene()
{
    glClear(GL_COLOR_BUFFER_BIT);
    int i, j;
    fireLoop();

    for (i = 0; i < ROW; i++) for (j = 0; j < COLUMN; j++) setColor(i, j, fireIntensity[(int)table[i][j]]);

    // Atualiza a textura com os novos valores de cor
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, COLUMN, ROW, GL_RGB, GL_UNSIGNED_BYTE, (void *)textureData);

    // Desenha um quadrado com a textura do fogo
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(-1.0, -1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(1.0, -1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(-1.0, 1.0);
    glEnd();

    glutSwapBuffers();
}

// Função de callback chamada sempre que o tamanho do framebuffer é alterado
void framebuffer_size_callback(int w, int h)
{
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
}

// Função para configurar o ambiente OpenGL, incluindo a cor de fundo, a semente do gerador de números aleatórios, a inicialização da tabela de intensidade do fogo e a configuração da textura
void setup()
{
    glClearColor(0.1, 0.1, 0.2, 1.0);

    srand(time(NULL));

    int i, j;

    // Inicializa a tabela de intensidade do fogo com o valor máximo
    for (i = 0; i < ROW; i++) for (j = 0; j < COLUMN; j++) table[i][j] = FIREINTENSITY_SIZE - 1;

    // Limpa a textura com valores de cor zero
    for (i = 0; i < ROW; i++) for (j = 0; j < COLUMN; j++) textureData[i][j][0] = textureData[i][j][1] = textureData[i][j][2] = 0;

    // Cria a textura com os dados da matriz textureData
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, COLUMN, ROW, GL_FALSE, GL_RGB, GL_UNSIGNED_BYTE, (void *)textureData);

    // Configura as propriedades de filtragem e envolvimento da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // Habilita a textura
    glEnable(GL_TEXTURE_2D);
}

// Função de callback chamada a cada 33 milissegundos para atualizar a cena
void timerFunction(int val)
{
    glutPostRedisplay();

    glutTimerFunc(33, timerFunction, 1);
}