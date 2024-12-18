#include <GL/glew.h>    // inclui lib auxiliar GLEW e a versão mais recente da OpenGL
#include <GLFW/glfw3.h> // GLFW biblioteca para interface com SO (janela, mouse, teclado, ...)
#include <stdio.h>      // biblioteca padrão C para I/O
#include <Windows.h>
#include <time.h>
#include <math.h>

#include "Retangulo.h"
#include "ControladorRetangulo.h"
#include "GameController.h"

int linhas = 15;
int colunas = 9;

float topPad = 0.1f;
float leftPad = 0.1f;
float rightPad = 0.1f;
float intraXPad = 0.01f;
float intraYPad = 0.01f;

float lenght = (2.0f - leftPad - rightPad - (intraXPad * (colunas - 1))) / (float)colunas;

bool jogou = false;
int chuteX = -1;
int chuteY = -1;

//Quanto mais perto de 1 mais facil
float tolerancia = 0.3f;


GLfloat matTrans[] = {
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0,

};


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    double xPrint, yPrint;
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS) {
        glfwGetCursorPos(window, &xpos, &ypos);




        xPrint = (xpos / 480) - 1;
        yPrint = (-ypos / 360) + 1;

        int colunaP = floor((1 - rightPad + xPrint) / (lenght + intraXPad));
        int linhaP =  -1 - floor( (2* (topPad + yPrint - 1)) / (lenght + (2 * intraYPad)));

        
        //printf("\nClicando na coluna %d\n", colunaP);
        //printf("Clicando na linha %d\n", linhaP);

        //printf("Posição X: %f \n", xPrint);
        //printf("Posição Y: %f \n", yPrint);

        chuteX = colunaP;
        chuteY = linhaP;
        jogou = true;
    }
}



int main() {
    //printf("lenght no main: %f\n", lenght);
    srand(time(NULL));
    FILE *arquiv;

    Retangulo retanguloBase =  Retangulo(0.0f,0.0f,lenght);
    GameController gameController = GameController(linhas, colunas,topPad,leftPad,rightPad,intraXPad,intraYPad, tolerancia);
    gameController.comecarJogo();
    

    fopen_s(&arquiv,"output.txt", "w");
   

    // 1 - Inicialização da GLFW
    if (!glfwInit()) {
        fprintf(arquiv, "ERROR: could not start GLFW3\n");
        fclose(arquiv);
        return 1;
    }
    // 1.1 - Necessário para Apple OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // 2 - Criação do contexto gráfico (window)
    GLFWwindow* window = glfwCreateWindow(960, 720, "Jogo da cores - Por Bruno P. Berti e Pedro Tubino", NULL, NULL);
    if (!window) {
        fprintf(arquiv, "*** ERRO: não foi possível abrir janela com a GLFW\n");
        // 2.0 - Se não foi possível iniciar GLFW, então termina / remove lib GLFW da memória.
        glfwTerminate();
        fclose(arquiv);
        return 1;
    }
    // 2.1 - Torna janela atual como o contexto gráfico atual para desenho
    glfwMakeContextCurrent(window);

    // 3 - Inicia manipulador da extensão GLEW 
    glewExperimental = GL_TRUE;
    glewInit();

    // 4 - Objetivo do exemplo: detectar a versão atual do OpenGL e motor de renderização.
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    printf("\n** Verificação da OpenGL ************\n");
    printf("\tRenderer: %s\n", renderer);
    printf("\tVersão suportada da OpenGL %s\n\n", version);

    /**************
     * 5 - AQUI VEM TODO O CÓDIGO DA APP GRÁFICA, PRINCIPALMENTE, O MAIN LOOP
     **************/

    
     // 5.1 - Geometria da cena
    /*
    GLfloat vertices[] = {
      -0.6,  0.6, 0.0, // primeiro triângulo // +-----+
       0.6,  0.6, 0.0,                       // | \ 1 |
       0.6, -0.6, 0.0,                       // |  \  |
       0.6, -0.6, 0.0, // segundo triângulo  // | 2 \ |
      -0.6, -0.6, 0.0,                       // +-----+
      -0.6,  0.6, 0.0,
    };
    */

   
    //GLfloat *vertices = retangulo.retornaCordenadas();
    GLfloat* vertices;
    vertices = retanguloBase.retornaCordenadas();
    
    



    GLuint vboVert; // identificador de vértices
    glGenBuffers(1, &vboVert);
    glBindBuffer(GL_ARRAY_BUFFER, vboVert);
    // 5.1.1 - Comando que passa dados de vértices da memória da CPU -> memória da GPU 
    glBufferData(GL_ARRAY_BUFFER, sizeof(*vertices) * 18, vertices, GL_STATIC_DRAW);

    /*

    GLfloat colors[] = { // cores como floats, valores entre [0..1]
       0.0,  0.0, 1.0, // primeiro triângulo // +-----+
       0.0,  1.0, 1.0,                       // | \ 1 |
       0.0,  1.0, 0.0,                       // |  \  |
       0.0,  1.0, 0.0, // segundo triângulo  // | 2 \ |
       1.0,  0.0, 0.0,                       // +-----+
       0.0,  0.0, 1.0,
    };

    */

    GLfloat colors[] = {
    0.0f, 0.0f, 0.0f,
    };
    //printf("\nValor vermelho do triangulo = %f",colors[0]);

    /*
    GLuint vboCor; // identificador de vértices
    glGenBuffers(1, &vboCor);
    glBindBuffer(GL_ARRAY_BUFFER, vboCor);
    // 5.1.2 - Comando que passa dados de cores da memória da CPU -> memória da GPU 
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    */

    // 5.2 - Objeto de propriedades / layout
    // como variável foi criada dentro do método main, este é o seu escopo!
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // 5.2.1 - Vínculo entre áreas de dados e layout de leitura de memória na GPU
    // 5.2.1.1 - Vinculando layout de leitura dos vértices
    glBindBuffer(GL_ARRAY_BUFFER, vboVert); // identifica vbo atual
    //   habilitado primeiro atributo do vbo (bind atual)
    glEnableVertexAttribArray(0);
    //   associação do vbo atual com primeiro atributo
    //   0 (primeiro 0) identifica que o primeiro atributo está sendo definido
    //   3, GL_FLOAT identifica que dados são vec3 e estão a cada 3 float, 
    //   começando no primeiro byte (último 0).
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    /*
    // 5.2.1.2 - Vinculando layout de leitura das cores
    glBindBuffer(GL_ARRAY_BUFFER, vboCor); // identifica vbo atual
    glEnableVertexAttribArray(1);          // agora utilizamos o próx layout disponível, 1
    // 1 indica que estamos definindo o segundo atributo de layout de memória
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    */

    // 5.3 - Definição dos shaders para renderização
    /*
    // 5.3.1 - Vertex shader é o estagio de entrada, é ele quem recebe os dados da GPU:
    const char* vertex_shader =
        "#version 410\n"
        "layout(location=0) in vec3 vp;"    // layout 0 foi utilizado para receber vec3 do vértice
        "layout(location=1) in vec3 vc;"    // layout 1 foi utilizado para receber vec3 da cor
        "out vec3 color;"                   // todos os estágios tem: entra -> proc -> saída, color é a saída para ao FS
        "void main () {"
        "   color = vc;"                    // a cor vc associada ao respectivo vértice vp é propagada para o FS
        "	  gl_Position = vec4 (vp, 1.0);"  //objetivo do VS, posicionar o vértice vp no sistema de referência do universo
        "}";
        */
    const char* vertex_shader =
        "#version 410\n"
        "layout(location=0) in vec3 vp;"    // layout 0 foi utilizado para receber vec3 do vértice
        "uniform vec3 vc;"    
        "uniform mat4 matTrans;"
        "out vec3 color;"                   // todos os estágios tem: entra -> proc -> saída, color é a saída para ao FS
        "void main () {"
        "   color = vc;"                    // a cor vc associada ao respectivo vértice vp é propagada para o FS
        "	  gl_Position = matTrans *(vec4 (vp, 1.0));"  //objetivo do VS, posicionar o vértice vp no sistema de referência do universo
        "}";

    // 5.3.2 - é o estágio de saída do pipeline que podemos intervir
    /*

    const char* fragment_shader =
        "#version 410\n"
        "in vec3 color;"                    // recebe a cor saída do estágio anterior VS
        "out vec4 frag_color;"
        "void main () {"
        "	 frag_color = vec4 (color, 1.0);" // objetivo do FS, determinar a cor do fragmento
        "}";

    */

    const char* fragment_shader =
        "#version 410\n"
        "in vec3 color;"                    // recebe a cor saída do estágio anterior VS
        "out vec4 frag_color;"
        "void main () {"
        "	 frag_color = vec4 (color, 1.0);" // objetivo do FS, determinar a cor do fragmento
        "}";

    // 5.4 - Compilação e "linkagem" dos shaders num shader programm
    // identifica vs e o associa com vertex_shader
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);

    int params = -1;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(arquiv, "ERROR: GL shader index %i did not compile\n", vs);
        // print_shader_info_log(vs);
        glfwTerminate();
        fclose(arquiv);
        return 1; // or exit or something
    }

    // identifica fs e o associa com fragment_shader
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(arquiv, "ERROR: GL shader index %i did not compile\n", fs);
        // print_shader_info_log(fs);
        glfwTerminate();
        fclose(arquiv);
        return 1; // or exit or something
    }

    // identifica do programa, adiciona partes e faz "linkagem"
    GLuint shader_programm = glCreateProgram();
    glAttachShader(shader_programm, fs);
    glAttachShader(shader_programm, vs);
    glLinkProgram(shader_programm);

    glGetProgramiv(shader_programm, GL_LINK_STATUS, &params);
    if (GL_TRUE != params)
    {
        fprintf(arquiv, "ERROR: could not link shader programme GL index %i\n",
            shader_programm);
        // print_programme_info_log( shader_programm);
        glfwTerminate();
        fclose(arquiv);
        return 1;
    }


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int matrixLocation = glGetUniformLocation(shader_programm, "vc");
    glUniform3fv(matrixLocation,1,colors);

    int matrixLocation2 = glGetUniformLocation(shader_programm, "matTrans");
    glUniformMatrix4fv(matrixLocation2, 1, GL_FALSE, matTrans);

    //retangulo.imprimeCores();
    /*
    for (int i = 0; i < 18; i++) {
        printf("O %d elemento do array é %f\n", i, vertices[i]);
   }
   */

    glUseProgram(shader_programm);

    /*
    for (int i = 0; i < 40; i++) {
        printf("\nretangulo %d encontrado no X: %f  , Y %f  \n", i,listaDeRetangulos[i].posX, listaDeRetangulos[i].posY);
    }
    */


    


    
    gameController.imprimeRodada();
    // 5.4 - Finalmente, loop de desenho. Note que até o momento pipeline não foi utilizado!
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        
        

        for (int i = 0; i < linhas*colunas; i++) {
            if (gameController.ativos[i]) {
                colors[0] = ((float)gameController.listaDeRetangulos[i].red / 255);
                colors[1] = ((float)gameController.listaDeRetangulos[i].green / 255);
                colors[2] = ((float)gameController.listaDeRetangulos[i].blue / 255);
                glUniform3fv(matrixLocation, 1, colors);
                matTrans[12] = gameController.listaDeRetangulos[i].posX;
                matTrans[13] = gameController.listaDeRetangulos[i].posY;
                glUniformMatrix4fv(matrixLocation2, 1, GL_FALSE, matTrans);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }

        if (jogou) {
            printf("\n%d Retangulo removidos", gameController.fazerRodada(chuteY, chuteX));
            jogou = false;
            gameController.imprimePontos();
            if (gameController.acabou()) {
                glfwTerminate();
                Sleep(10000);
            }
            else {
                gameController.imprimeRodada();
            }
        }

        // Define shader_programme como o shader a ser utilizado
        

        // Define vao como verte array atual 
        //glBindVertexArray(vao);
        // 5.4.1 - Este comando dispara a execução do pipeline na GPU
        // desenha pontos a partir do vértice 0 até 6
        //glDrawArrays(GL_TRIANGLES, 0, 6);

        // 5.4.2 - Este comando faz controle double buffering, obtendo imagem do framebuffer 
        //         gerado pela OpenGL para renderização no contexto gráfico (window).
        glfwSwapBuffers(window);

        // Processa eventos da GLFW
        glfwPollEvents();
        Sleep(100);
    }

    // 6 - Ao final, terminar / remover GLFW da memória.
    glfwTerminate();
    fclose(arquiv);
    return 0;
}