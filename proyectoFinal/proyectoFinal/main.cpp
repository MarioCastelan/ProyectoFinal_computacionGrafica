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
    //
    Model burbujas((char*)"Models/burbujas/burbujas.obj");
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
        //SKYBOX
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

        habitacion.Draw(shader);
        ventanaCuarto.Draw(shader);
        trampolin.Draw(shader);
        cama.Draw(shader);
        pelota.Draw(shader);
        reloj.Draw(shader);
        barril.Draw(shader);
        plato.Draw(shader);
        //Modelado jerarquico
        jugueteAnclaje.Draw(shader);
        juguete1.Draw(shader);
        juguete2.Draw(shader);

        marcoPuertaCuarto1.Draw(shader);
        puertaCuarto1.Draw(shader);
        marcoPuertaCuarto2.Draw(shader);
        puertaCuarto2.Draw(shader);
        
        //Fachada
        casa.Draw(shader);
        //Medusa 1
        medusa1.Draw(shader);
        pata1_1.Draw(shader);
        pata1_2.Draw(shader);
        pata1_3.Draw(shader);
        pata1_4.Draw(shader);
        //Medusa 2
        medusa2.Draw(shader);
        pata2_1.Draw(shader);
        pata2_2.Draw(shader);
        pata2_3.Draw(shader);
        pata2_4.Draw(shader);
        //Flores
        flor1.Draw(shader);
        flor2.Draw(shader);
        flor3.Draw(shader);
        flor4.Draw(shader);
        //
        burbujas.Draw(shader);
        puertaCasa.Draw(shader);
        //Ventanas
        ventanaCasa1.Draw(shader);
        ventanaCasa2.Draw(shader);

        //Bob Esponja
        cuerpoEsponja.Draw(shader);
        brazoIzquierdo.Draw(shader);
        brazoDerecho.Draw(shader);
        pieIzquierdo.Draw(shader);
        pieDerecho.Draw(shader);
        //Gary
        cuerpoGary.Draw(shader);
        ojoIzquierdo.Draw(shader);
        ojoDerecho.Draw(shader);

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

