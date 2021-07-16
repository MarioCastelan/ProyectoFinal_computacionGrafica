//Proyecto Final
//Castelan Hernandez Mario 
//Grupo:04
//Laboratorio de computacion grafica e interaccion humano computadora

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"

// Sky Box
#include "SkyBox.h"


// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//
float rotar1 = 0.0;
float rotar2 = 0.0;


//


int main()
{
    // Init GLFW
    glfwInit();
    // Set all the required options for GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 9", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    // Set the required callback functions
    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    // GLFW Options
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    // Define the viewport dimensions
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    // OpenGL options
    glEnable(GL_DEPTH_TEST);

    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
    // Carga de modelos     
    //    
    //Habitacion
    Model habitacion((char*)"Models/habitacion/habitacion.obj");
    //juguete de medusas
    Model jugueteAnclaje((char*)"Models/jugueteMedusas/jugueteAnclaje.obj");
    Model juguete1((char*)"Models/jugueteMedusas/juguete1.obj");
    Model juguete2((char*)"Models/jugueteMedusas/juguete2.obj");
    //
    Model trampolin((char*)"Models/trampolin/trampolin.obj");
    Model cama((char*)"Models/cama/cama.obj");
    Model pelota((char*)"Models/pelota/pelota.obj");
    Model reloj((char*)"Models/relojBarril/reloj.obj");
    Model barril((char*)"Models/relojBarril/barril.obj");
    Model plato((char*)"Models/platoGary/plato.obj");
    Model ventanaCuarto((char*)"Models/ventanas/ventanaCuarto.obj");
    //Puertas cuarto
    Model marcoPuertaCuarto1((char*)"Models/puertas/marcoPuertaCuarto1.obj");
    Model puertaCuarto1((char*)"Models/puertas/puertaCuarto1.obj");
    Model marcoPuertaCuarto2((char*)"Models/puertas/marcoPuertaCuarto2.obj");
    Model puertaCuarto2((char*)"Models/puertas/puertaCuarto2.obj");
    //Fachada
    //
    Model casa((char*)"Models/casa/casaFachada.obj");
    //Medusa 1
    Model medusa1((char*)"Models/medusas/medusa1.obj");
    Model pata1_1((char*)"Models/medusas/pata1_1.obj");
    Model pata1_2((char*)"Models/medusas/pata1_2.obj");
    Model pata1_3((char*)"Models/medusas/pata1_3.obj");
    Model pata1_4((char*)"Models/medusas/pata1_4.obj");
    //Medusa 1
    Model medusa2((char*)"Models/medusas/medusa2.obj");
    Model pata2_1((char*)"Models/medusas/pata2_1.obj");
    Model pata2_2((char*)"Models/medusas/pata2_2.obj");
    Model pata2_3((char*)"Models/medusas/pata2_3.obj");
    Model pata2_4((char*)"Models/medusas/pata2_4.obj");
    //Flores
    Model flor1((char*)"Models/flores/flor1.obj");
    Model flor2((char*)"Models/flores/flor2.obj");
    Model flor3((char*)"Models/flores/flor3.obj");
    Model flor4((char*)"Models/flores/flor4.obj");
    //Burbujas
    Model burbuja1((char*)"Models/burbujas/burbuja.obj");
    Model burbuja2((char*)"Models/burbujas/burbuja.obj");
    Model burbuja3((char*)"Models/burbujas/burbuja.obj");
    Model burbuja4((char*)"Models/burbujas/burbuja.obj");
    Model burbuja5((char*)"Models/burbujas/burbuja.obj");

    Model puertaCasa((char*)"Models/puertas/puertaCasa.obj"); //El marco de la puerta ya se encuentra en el modelo de la casa
    //Ventanas de la casa, Los marcos de las ventanas ya se encuentran en el modelo de la casa
    Model ventanaCasa1((char*)"Models/ventanas/ventanaCasa1.obj");
    Model ventanaCasa2((char*)"Models/ventanas/ventanaCasa2.obj");
    //Bob Esponja
    Model cuerpoEsponja((char*)"Models/bobEsponja/cuerpo.obj");
    Model brazoIzquierdo((char*)"Models/bobEsponja/brazoIzquierdo.obj");
    Model brazoDerecho((char*)"Models/bobEsponja/brazoDerecho.obj");
    Model pieIzquierdo((char*)"Models/bobEsponja/pieIzquierdo.obj");
    Model pieDerecho((char*)"Models/bobEsponja/pieDerecho.obj");
    //Gary
    Model cuerpoGary((char*)"Models/gary/cuerpo.obj");
    Model ojoIzquierdo((char*)"Models/gary/ojoIzquierdo.obj");
    Model ojoDerecho((char*)"Models/gary/ojoDerecho.obj");

    //SKYBOx
    SkyBox fondo((char*)"Models/SkyBox/right.tga", (char*)"Models/SkyBox/left.tga", (char*)"Models/SkyBox/top.tga",
        (char*)"Models/SkyBox/bottom.tga", (char*)"Models/SkyBox/back.tga", (char*)"Models/SkyBox/front.tga",
        skyboxVertices_1, sizeof(skyboxVertices_1));

    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view;
        /*_______________________________SkyBox_______________________________*/
        SkyBoxshader.Use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix()));	// Remove any translation component of the view matrix
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(SkyBoxshader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        fondo.Draw();


        shader.Use();

        view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat4 model(1);

        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        /*_______________________________Objetos Estaticos_______________________________*/
        // Los objetos estaticos ya se encuentran posicionados en la escena, estos fueron
        // posicionados desde el software Maya 

        /*_____________________Habitacion_____________________*/
        habitacion.Draw(shader);
        ventanaCuarto.Draw(shader);
        trampolin.Draw(shader);
        cama.Draw(shader);
        barril.Draw(shader);
        plato.Draw(shader);
        marcoPuertaCuarto1.Draw(shader);
        marcoPuertaCuarto2.Draw(shader);
        
        /*_____________________Fachada_____________________*/
        casa.Draw(shader);


        /*_______________________________Objetos animados_______________________________*/
        // Los objetos animados se tienen que posicionar manualmente, ya que cuando se 
        // exporta  un objeto este no guarda el pivote fuera del origen, solo la posicion 
        // se guarda pero el pivote se mantiene en el origen, por lo tanto se posicionan 
        // manualmente para mantener el pivote en donde se requiera. 
        /*_____________________Habitacion_____________________*/
        //PuertaCuarto1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.7254f, 1.7624f, -6.3046));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCuarto1.Draw(shader);
        //PuertaCuarto2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.6489f, 1.7615f, 10.9612));
        //model = glm::rotate(model, glm::radians(rotar1), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCuarto2.Draw(shader);
        
        //Reloj
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-5.4632f, 1.6206f, -1.7841));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        reloj.Draw(shader);

        //Juguete de medusas
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.8922f, 9.4165f, -2.3752f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        jugueteAnclaje.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.2576f, 6.8221f, -3.1715f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        juguete1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.4182f, 6.8540f, -1.6971f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        juguete2.Draw(shader);


        //Bob Esponja
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.4835f, 1.1726f, -3.6138f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuerpoEsponja.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(3.0852f, 1.4154f, -3.6936f));
        model = glm::rotate(model, glm::radians(rotar1), glm::vec3(1.0f, 0.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        brazoIzquierdo.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.8817f, 1.4106f, -3.6926f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        brazoDerecho.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.7592f, 0.7526f, -3.6952f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pieIzquierdo.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.2086f, 0.7526f, -3.6952f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pieDerecho.Draw(shader);

        //Pelota
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.2543f, 0.2781f, -2.8870f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pelota.Draw(shader);

        //Gary
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.245f, 0.66f, 0.921f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuerpoGary.Draw(shader); 

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.861f, 0.168f, 1.267f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ojoIzquierdo.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.921f, 0.132f, 1.303f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ojoDerecho.Draw(shader);

        /*_____________________Fachada_____________________*/
        //Medusa1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.2221f, 12.5750f, 33.5387f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        medusa1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.8847, 11.2060f, 33.3054f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.8699f, 11.1621f, 34.3139f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.5612f, 11.1536f, 34.1109f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.7413f, 11.2340f, 33.2980f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_4.Draw(shader);
        //Medusa2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.3627f, 18.4902f, 35.5109f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        medusa2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(20.8863f, 17.1430f, 35.4862f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.3452f, 17.0906f, 36.3839f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.8585f, 17.0477f, 35.8799f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.6391f, 17.1261f, 35.0766f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_4.Draw(shader);
        
        //Bubujas
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(17.1803f, 37.9356f, 11.6796f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        burbuja1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(23.5857f, 38.1910f, 2.1946f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        burbuja2.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(19.7220f, 42.6049f, 11.0467f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        burbuja3.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(25.1314f, 48.2882f, -0.3447f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        burbuja4.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(22.2975f, 55.0345f, 2.0671f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        burbuja5.Draw(shader);

        //Puerta casa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.6333f, 6.4050f, 18.0085f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCasa.Draw(shader);

        //Ventanas casa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.6756f, 19.9024f, 15.4704f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ventanaCasa1.Draw(shader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(8.4491f, 9.6981f, 14.8688f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ventanaCasa2.Draw(shader);

        // Flores 
        // No necesitan posicionarse ya que su pivote ya se encuentra en donde lo queremos (el origen), para
        // que las flores se muevan alrededor de la casa cuando cambie la luz ambiental 

        flor1.Draw(shader);

        flor2.Draw(shader);

        flor3.Draw(shader);

        flor4.Draw(shader);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
    // Camera controls
    if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
    {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }

    if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
    {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }

    if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
    {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }

    if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (keys[GLFW_KEY_U])
    {
        rotar1 += 0.1;
    }

    if (keys[GLFW_KEY_I])
    {
        rotar1 -= 0.1;
    }
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            keys[key] = false;
        }
    }

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse)
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(xOffset, yOffset);
}

