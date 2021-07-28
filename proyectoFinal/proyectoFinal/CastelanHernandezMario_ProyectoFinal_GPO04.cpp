//Proyecto Final
//Castelan Hernandez Mario 
//Grupo:04
//Laboratorio de computacion grafica e interaccion humano computadora

// Std. Includes
#include <string>
#include <cmath>
#include <random>
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
void animarPuerta(glm::mat4* model, bool* puerta, float* rotacionPuerta);
void animar();
void animarJugueteMedusas(glm::mat4* model, int parte);
void animarVentana(glm::mat4* model);
void animarReloj(glm::mat4* model);
void animarBurbujaReloj(glm::mat4* model, int burbuja);
void animarBurbujaChimenea(glm::mat4* model, int burbuja);
void animarMedusa(glm::mat4* model, float* traslacionMedusa, float* rotacionPataMedusa, int parte, bool* estadoPataMedusa);
void keyFrameAnimacion();
void resetElements(void);
void interpolation(void);
void animarPelota(glm::mat4* model);
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
const float RANGO_DISTANCIA = 7.0f;
const float VELOCIDAD = 0.2f;
const int FRAMES_BOBESPONJA = 19;
const int FRAMES_GARY = 98;
// Variables de control de animaciones
bool abrir_puerta1 = false;
bool abrir_puerta2 = false;
bool abrir_puertaCasa = false;
bool abrir_ventanasCasa = false;
bool activar_jugueteMedusas = false;
bool activar_relojAlarma = false;
bool activar_burbujasAlarma = false;
bool activar_burbujasChimenea = false;
bool activar_medusas = false;
bool activar_pelota = false;
bool estadoPataMedusa1 = false;
bool estadoPataMedusa2 = false;
bool rebotePelota = false;
float rotacionPatasMedusa1 = 0.0f;
float rotacionPatasMedusa2 = 0.0f;
float rotacionPuerta1 = 0.0f;
float rotacionPuerta2 = 0.0f;
float rotacionPuertaCasa = 0.0f;
float rotacionVentanasCasa = 0.0f;
float jugueteRotacion1 = 0.0f;
float jugueteRotacion2 = 0.0f;
float jugueteRotacion3 = 0.0f;
float relojRotacion = 0.0f;
float relojTraslacion = 0.0f;
float traslacionMedusa1 = 0.0f;
float traslacionMedusa2 = 0.0f;
float burbujasRelojContador = 0.0f;
int relojAnimacionEstado = 1;

float rotacionjugueteAnclaje = 0.0f;
float rotacionJuguete1 = 0.0f;
float rotacionJuguete2 = 0.0f;
float posicionPelota = 0.0f;
float rotacionPelota = 0.0f;


//Posiciones de burbujas del reloj
glm::vec3 burbujasRelojPosiciones[] = {
    glm::vec3(-2.6370f,  2.3964f,  -1.2950f),
    glm::vec3(-2.6370f,  3.1390f,  -1.2950f),
    glm::vec3(-2.6370f,  3.8972f,  -1.2950f),
    glm::vec3(-2.6370f,  4.5717f,  -1.2950f),
    glm::vec3(-1.8141f,  2.3964f,  -1.5846f),
    glm::vec3(-2.3112f,  3.1390f,  -1.5846f),
    glm::vec3(-2.6370f,  3.8972f,  -1.5846f),
    glm::vec3(-2.6370f,  4.5717f,  -1.5846f),
    glm::vec3(-2.3112f,  4.2426f,  -1.7423f),
    glm::vec3(-2.6370f,  2.3964f,  -1.5846f),
    glm::vec3(-1.8141f,  3.1390f,  -2.0904f),
    glm::vec3(-1.8141f,  3.8972f,  -2.0904f),
    glm::vec3(-2.6370f,  4.5717f,  -2.0904f),
    glm::vec3(-2.3112f,  4.2426f,  -2.0904f)
};

float burbujasRelojTraslacion[] = {
    0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
};

//Posiciones de burbujas de chimenea
glm::vec3 burbujasChimeneaPosiciones[] = {
    glm::vec3(17.1803f, 37.9356f, 11.6796f),
    glm::vec3(23.5857f, 38.1910f, 2.1946f),
    glm::vec3(19.7220f, 42.6049f, 11.0467f),
    glm::vec3(25.1314f, 48.2882f, -0.3447f),
    glm::vec3(22.2975f, 55.0345f, 2.0671f)
};

float burbujasChimeneaTraslacion[] = {
    0.0, 0.0, 0.0, 0.0, 0.0
};

// Variables y estructura para animacion de keyframes 
float   posZ = 0,
rotCuerpo = 0,
rotCuerpoY = 0,
rotPieIzq = 0,
rotPieDer = 0,
rotBraIzq = 0,
rotBraDer = 0,
garyPosX = 0,
garyPosY = 0,
garyPosZ = 0,
garyRotY = 0,
garyRotX = 0,
garyOjoIzq = 0,
garyOjoDer = 0;

int i_max_steps = 85;
int i_curr_steps = 0;


typedef struct _frame
{
    float posZ;
    float incZ;
    float rotCuerpo;
    float rotIncCuerpo;
    float garyPosX;
    float garyPosY;
    float garyPosZ;
    float garyPosXInc;
    float garyPosYInc;
    float garyPosZInc;
    float garyRotY;
    float garyRotYInc;
    float garyRotX;
    float garyRotXInc;
    float garyOjoIzq;
    float garyOjoIzqInc;
    float garyOjoDer;
    float garyOjoDerInc;
    float rotPieIzq;
    float rotPieIzqInc;
    float rotPieDer;
    float rotPieDerInc;
    float rotBraIzq;
    float rotBraIzqInc;
    float rotBraDer;
    float rotBraDerInc;
    _frame(float _cuerpoRot, float _brazoIzqRot, float _brazoDerRot, float _pieIzqRot, float _pieDerRot, float _cuerpoTra, float _garyPosX, float _garyPosY, float _garyPosZ, float _garyRotY, float _garyRotX, float _garyOjoIzq, float _garyOjoDer) {
        posZ = _cuerpoTra;
        rotBraIzq = _brazoIzqRot;
        rotBraDer = _brazoDerRot;
        rotPieIzq = _pieIzqRot;
        rotPieDer = _pieDerRot;
        rotCuerpo = _cuerpoRot;
        garyPosX = _garyPosX;
        garyPosY = _garyPosY;
        garyPosZ = _garyPosZ;
        garyRotY = _garyRotY;
        garyRotX = _garyRotX;
        garyOjoIzq = _garyOjoIzq;
        garyOjoDer = _garyOjoDer;
    }

}FRAME;

vector<FRAME> KeyFrame = vector<FRAME>();
int FrameIndex = 0;
bool playAnimacionKeyFrames = false;
int playIndex = 0;
int maxFrames = 0;

// Posiciones de las pointLights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.0,0.0,101.8575),
    glm::vec3(0.0,0.0,-30.1029),
    glm::vec3(63.2484,0,1.1916),
    glm::vec3(-63.2484,0,1.1916)
};
//Posicion de la spotlight
glm::vec3 SpotLight(0.0);

int main()
{
    std::srand(glfwGetTime()); //Se inicialza generador random de numeros
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    std::cout << "Cargando Recursos" << endl;
    // Setup and compile our shaders
    Shader shader("Shaders/modelLoading.vs", "Shaders/modelLoading.frag");
    Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
    Shader SkyBoxshader("Shaders/SkyBox.vs", "Shaders/SkyBox.frag");
    std::cout << '\r' << "Recursos Cargados...15%" << std::flush;
    // Carga de modelos     
    //    
    //Habitacion
    Model habitacion((char*)"Models/habitacion/habitacion.obj");
    //juguete de medusas
    // Model juguete((char*)"Models/jugueteMedusas/juguete.obj");
        //juguete de medusas
    Model jugueteAnclaje((char*)"Models/jugueteMedusas/jugueteAnclaje.obj");
    Model juguete1((char*)"Models/jugueteMedusas/juguete1.obj");
    Model juguete2((char*)"Models/jugueteMedusas/juguete2.obj");
    //
    std::cout << '\r' << "Recursos Cargados...30%" << std::flush;
    Model trampolin((char*)"Models/trampolin/trampolin.obj");
    Model cama((char*)"Models/cama/cama.obj");
    Model pelota((char*)"Models/pelota/pelota.obj");
    Model reloj((char*)"Models/relojBarril/reloj.obj");
    Model barril((char*)"Models/relojBarril/barril.obj");
    Model plato((char*)"Models/platoGary/plato.obj");
    Model ventanaCuarto((char*)"Models/ventanas/ventanaCuarto.obj");
    std::cout << '\r' << "Recursos Cargados...40%" << std::flush;
    //Puertas cuarto
    Model marcoPuertaCuarto1((char*)"Models/puertas/marcoPuertaCuarto1.obj");
    Model puertaCuarto1((char*)"Models/puertas/puertaCuarto1.obj");
    Model marcoPuertaCuarto2((char*)"Models/puertas/marcoPuertaCuarto2.obj");
    Model puertaCuarto2((char*)"Models/puertas/puertaCuarto2.obj");
    //Burbuja de la alarma
    Model burbujaAlarma((char*)"Models/burbujas/burbujaAlarma.obj");
    //Fachada
    //
    Model casa((char*)"Models/casa/casaFachada.obj");
    std::cout << '\r' << "Recursos Cargados...45%" << std::flush;
    //Medusa 1
    Model medusa1((char*)"Models/medusas/medusa1.obj");
    Model pata1_1((char*)"Models/medusas/pata1_1.obj");
    Model pata1_2((char*)"Models/medusas/pata1_2.obj");
    Model pata1_3((char*)"Models/medusas/pata1_3.obj");
    Model pata1_4((char*)"Models/medusas/pata1_4.obj");
    std::cout << '\r' << "Recursos Cargados...50%" << std::flush;
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
    Model burbujaChimenea((char*)"Models/burbujas/burbuja.obj");
    std::cout << '\r' << "Recursos Cargados...60%" << std::flush;
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
    std::cout << '\r' << "Recursos Cargados...70%" << std::flush;
    //Gary
    Model cuerpoGary((char*)"Models/gary/cuerpo.obj");
    Model ojoIzquierdo((char*)"Models/gary/ojoIzquierdo.obj");
    Model ojoDerecho((char*)"Models/gary/ojoDerecho.obj");

    //SKYBOx
    SkyBox fondo((char*)"Models/SkyBox/right.tga", (char*)"Models/SkyBox/left.tga", (char*)"Models/SkyBox/top.tga",
        (char*)"Models/SkyBox/bottom.tga", (char*)"Models/SkyBox/back.tga", (char*)"Models/SkyBox/front.tga",
        skyboxVertices_1, sizeof(skyboxVertices_1));

    std::cout << '\r' << "Recursos Cargados...80%" << std::flush;

    // Draw in wireframe
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 200.0f);

    /*_______________________________Carga de datos para las animaciones con keyframes_______________________________*/
    //Bob Esponja
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 0, -55, 0, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 55, -55, 110, 0.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 110, -55, 1, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 55, -55, 110, 1.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 110, -55, 2, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 0, -55, 110, 2.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 110, -55, 3, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 55, -55, 110, 3.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 110, -55, 4, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 55, -55, 110, 4.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 55, -110, 110, -55, 5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, -110, 0, -55, 110, 5.5, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(20, -125.298, 80.7993, 0, 79.6991, 6, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(-20, 43.1002, -138.999, 6.80024, -32.4003, 6, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(-20, 43.1002, -138.999, 6.80024, -32.4003, 6, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(-20, 43.1002, -138.999, 6.80024, -32.4003, 6, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0));
    std::cout << '\r' << "Recursos Cargados...85%" << std::flush;
    //Gary
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 0.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 1.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 2.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 3.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 4.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 5.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 6.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 7.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 8.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 9.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 9.5, 0, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 9.5, 45, 0, 0, 0));// rota a izquierda
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 0.5, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 0.5, 9.5, 90, 90, 0, 0)); //rota hacia arrbia
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 1, 9.5, 90, 90, 0, 0)); //
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 1.136, 9.5, 90, 90, 0, 0));//
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 1.5, 9.5, 90, 90, 0, 0)); //regresa a normal la rotacion anterior, plano
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 2, 9.5, 90, 90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 3, 9.5, 90, 90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 3.5, 9.5, 90, 90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 1.5, 3.5, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 2, 3.5, 9.5, 90, 0, 0, 0)); //
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 2.5, 3.5, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 3, 3.5, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 3.5, 3.5, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4, 3.5, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 3.5, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 2.5, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 2, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 1.5, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 1, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 0.5, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.2, 0, 9.5, 90, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5, 0, 9.5, 90, 0, 0, 0)); //
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.5, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 9.5, 90, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 9.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 9.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 9, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 8.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 8, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 7.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 7, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 6.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 6, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 5.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 4.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 4, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 3.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 3, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 2.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 2, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 1.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 1, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 0.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, 0, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -0.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -1, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -1.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -2, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -2.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -3, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -3.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -4, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -4.5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 6, 0, -5, 180, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.5, 0, -5, 270, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 0, -5, 270, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 0.5, -5, 270, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 1, -5, 270, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 1.5, -5, 270, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 2, -5, 270, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 2.171, -5, 270, -90, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5.3, 2.171, -5, 270, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 5, 2.171, -5, 270, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -5, 270, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -5, 360, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 10, -10));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 10, -10));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 0, 0));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 10, -10));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 10, -10));
    KeyFrame.push_back(FRAME(0, 0, 0, 0, 0, 0, 4.5, 2.171, -4.5, 360, 0, 0, 0));
    /*_______________________________________________________________________________________________________________*/
    std::cout << '\r' << "Recursos Cargados...100%" << endl;
    std::cout << "Se cargaron todos los recursos" << endl;
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
        keyFrameAnimacion();
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

        lightingShader.Use();
        GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
        glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
        // Set material properties
        glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

        // Directional light
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.0f, -1.0f, -1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.0f, 0.0f, 0.0f);

        // Point light 1
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.1f, 0.1f, 0.1f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), 0.0f, 0.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.0014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.000007f);

        // Point light 2
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.0014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 0.000007f);

        // Point light 3
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.0014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 0.000007f);


        // Point light 4
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), 0.5f, 0.5f, 0.5f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), 0.0f, 0.0f, 0.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.0014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.000007f);


        // SpotLight
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), 1.8952f, 9.7498f, -2.3689f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), 0.0f, -1.0f, 0.0f);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), SpotLight.x, SpotLight.y, SpotLight.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), SpotLight.x, SpotLight.y, SpotLight.z);
        glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), SpotLight.x, SpotLight.y, SpotLight.z);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.0014f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.000007f);
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(8.5f)));
        glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(9.0f)));
        // Transformaciones de la camara
        view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));


        glm::mat4 model(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));

        /*_______________________________Objetos Estaticos_______________________________*/
        // Los objetos estaticos ya se encuentran posicionados en la escena, estos fueron
        // posicionados desde el software Maya 

        /*_____________________Habitacion_____________________*/
        habitacion.Draw(lightingShader);
        ventanaCuarto.Draw(lightingShader);
        trampolin.Draw(lightingShader);
        cama.Draw(lightingShader);
        barril.Draw(lightingShader);
        plato.Draw(lightingShader);
        marcoPuertaCuarto1.Draw(lightingShader);
        marcoPuertaCuarto2.Draw(lightingShader);

        /*_____________________Fachada_____________________*/
        casa.Draw(lightingShader);


        /*_______________________________Objetos animados_______________________________*/
        // Los objetos animados se tienen que posicionar manualmente, ya que cuando se 
        // exporta  un objeto este no guarda el pivote fuera del origen, solo la posicion 
        // se guarda pero el pivote se mantiene en el origen, por lo tanto se posicionan 
        // manualmente para mantener el pivote en donde se requiera. 
        /*_____________________Habitacion_____________________*/
        //PuertaCuarto1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.7254f, 1.7624f, -6.3046));
        animarPuerta(&model, &abrir_puerta1, &rotacionPuerta1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCuarto1.Draw(lightingShader);
        //PuertaCuarto2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.6489f, 1.7615f, 10.9612));
        animarPuerta(&model, &abrir_puerta2, &rotacionPuerta2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCuarto2.Draw(lightingShader);

        //Reloj
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-5.4632f, 1.6206f, -1.7841));
        animarReloj(&model);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        reloj.Draw(lightingShader);
        //Burbujas del reloj
        if (activar_burbujasAlarma) {
            for (int burbuja = 0; burbuja < 14; burbuja++) {
                model = glm::mat4(1);
                model = glm::translate(model, burbujasRelojPosiciones[burbuja]);
                animarBurbujaReloj(&model, burbuja);
                glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
                burbujaAlarma.Draw(lightingShader);
            }
        }
        //Juguete de medusas
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.8922f, 9.6141f, -2.3854f));
        animarJugueteMedusas(&model, 1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        jugueteAnclaje.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.8944f, 6.9405f, -3.4219f));
        animarJugueteMedusas(&model, 2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        juguete1.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(1.8922f, 6.9466f, -1.3860f));
        animarJugueteMedusas(&model, 3);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        juguete2.Draw(lightingShader);



        //Bob Esponja
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.4835f, 1.1726f, -3.6138f));
        model = glm::translate(model, glm::vec3(0, 0, posZ));
        model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(1.0f, 0.0f, 0.0));
        model = glm::rotate(model, glm::radians(rotCuerpoY), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuerpoEsponja.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(rotCuerpoY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::translate(model, glm::vec3(3.0852f, 1.4154f, -3.6936f));
        model = glm::translate(model, glm::vec3(0, 0, posZ));
        //model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(1.0f, 0.0f, 0.0));
        model = glm::rotate(model, glm::radians(rotBraIzq), glm::vec3(1.0f, 0.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        brazoIzquierdo.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(rotCuerpoY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::translate(model, glm::vec3(1.8817f, 1.4106f, -3.6926f));
        model = glm::translate(model, glm::vec3(0, 0, posZ));
        //model = glm::rotate(model, glm::radians(rotCuerpo), glm::vec3(1.0f, 0.0f, 0.0));
        model = glm::rotate(model, glm::radians(rotBraDer), glm::vec3(1.0f, 0.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        brazoDerecho.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(rotCuerpoY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::translate(model, glm::vec3(2.7592f, 0.7526f, -3.6952f));
        model = glm::translate(model, glm::vec3(0, 0, posZ));
        model = glm::rotate(model, glm::radians(rotPieIzq), glm::vec3(1.0f, 0.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pieIzquierdo.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::rotate(model, glm::radians(rotCuerpoY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::translate(model, glm::vec3(2.2086f, 0.7526f, -3.6952f));
        model = glm::translate(model, glm::vec3(0, 0, posZ));
        model = glm::rotate(model, glm::radians(rotPieDer), glm::vec3(1.0f, 0.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pieDerecho.Draw(lightingShader);

        //Pelota
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.2543f, 0.2781f, 3.1130f));
        animarPelota(&model);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pelota.Draw(lightingShader);

        //Gary
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.1049f, 0.1230f, 1.2290f));
        model = glm::translate(model, glm::vec3(garyPosX, garyPosY, garyPosZ));
        model = glm::rotate(model, glm::radians(garyRotX), glm::vec3(0.0f, 0.0f, 1.0));
        model = glm::rotate(model, glm::radians(garyRotY), glm::vec3(0.0f, 1.0f, 0.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        cuerpoGary.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.1049f, 0.1230f, 1.2290f));
        model = glm::translate(model, glm::vec3(garyPosX, garyPosY, garyPosZ));
        model = glm::rotate(model, glm::radians(garyRotX), glm::vec3(0.0f, 0.0f, 1.0));
        model = glm::rotate(model, glm::radians(garyRotY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(garyOjoIzq), glm::vec3(0.0f, 0.0f, 1.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ojoIzquierdo.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-2.1049f, 0.1230f, 1.2290f));
        model = glm::translate(model, glm::vec3(garyPosX, garyPosY, garyPosZ));
        model = glm::rotate(model, glm::radians(garyRotX), glm::vec3(0.0f, 0.0f, 1.0));
        model = glm::rotate(model, glm::radians(garyRotY), glm::vec3(0.0f, 1.0f, 0.0));
        model = glm::rotate(model, glm::radians(garyOjoDer), glm::vec3(0.0f, 0.0f, 1.0));
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ojoDerecho.Draw(lightingShader);

        /*_____________________Fachada_____________________*/
        //Medusa1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.2221f, 12.5750f, 33.5387f));
        animarMedusa(&model, &traslacionMedusa1, &rotacionPatasMedusa1, 1, &estadoPataMedusa1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        medusa1.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.8847, 11.2060f, 33.3054f));
        animarMedusa(&model, &traslacionMedusa1, &rotacionPatasMedusa1, 3, &estadoPataMedusa1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_1.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(15.8699f, 11.1621f, 34.3139f));
        animarMedusa(&model, &traslacionMedusa1, &rotacionPatasMedusa1, 3, &estadoPataMedusa1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_2.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.5612f, 11.1536f, 34.1109f));
        animarMedusa(&model, &traslacionMedusa1, &rotacionPatasMedusa1, 2, &estadoPataMedusa1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_3.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(16.7413f, 11.2340f, 33.2980f));
        animarMedusa(&model, &traslacionMedusa1, &rotacionPatasMedusa1, 2, &estadoPataMedusa1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata1_4.Draw(lightingShader);
        //Medusa2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.3627f, 18.4902f, 35.5109f));
        animarMedusa(&model, &traslacionMedusa2, &rotacionPatasMedusa2, 1, &estadoPataMedusa2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        medusa2.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(20.8863f, 17.1430f, 35.4862f));
        animarMedusa(&model, &traslacionMedusa2, &rotacionPatasMedusa2, 3, &estadoPataMedusa2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_1.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.3452f, 17.0906f, 36.3839f));
        animarMedusa(&model, &traslacionMedusa2, &rotacionPatasMedusa2, 3, &estadoPataMedusa2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_2.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.8585f, 17.0477f, 35.8799f));
        animarMedusa(&model, &traslacionMedusa2, &rotacionPatasMedusa2, 2, &estadoPataMedusa2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_3.Draw(lightingShader);

        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(21.6391f, 17.1261f, 35.0766f));
        animarMedusa(&model, &traslacionMedusa2, &rotacionPatasMedusa2, 2, &estadoPataMedusa2);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pata2_4.Draw(lightingShader);

        //Bubujas chimenea
        for (int burbuja = 0; burbuja < 5; burbuja++) {
            model = glm::mat4(1);
            model = glm::translate(model, burbujasChimeneaPosiciones[burbuja]);
            animarBurbujaChimenea(&model, burbuja);
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            burbujaChimenea.Draw(lightingShader);
        }


        //Puerta casa
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-4.6333, 0.0000, 18.0085));
        animarPuerta(&model, &abrir_puertaCasa, &rotacionPuertaCasa);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        puertaCasa.Draw(lightingShader);

        //Ventana casa 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-8.6756f, 19.9024f, 15.4704f));
        animarVentana(&model);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ventanaCasa1.Draw(lightingShader);
        //Ventana casa 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(8.4491f, 9.6981f, 14.8688f));
        animarVentana(&model);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        ventanaCasa2.Draw(lightingShader);

        // Flores 
        // No necesitan posicionarse ya que su pivote ya se encuentra en donde lo queremos (el origen), para
        // que las flores se muevan alrededor de la casa cuando cambie la luz ambiental 
        model = glm::mat4(1);
        glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        flor1.Draw(lightingShader);

        flor2.Draw(lightingShader);

        flor3.Draw(lightingShader);

        flor4.Draw(lightingShader);

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

    if (keys[GLFW_KEY_E])
    {
        //Animaciones de las puertas en base a la posicion de la camara
        animar();
    }
    if (keys[GLFW_KEY_V])
    {
        abrir_ventanasCasa = !abrir_ventanasCasa;
    }
    if (keys[GLFW_KEY_B]) {
        activar_burbujasChimenea = !activar_burbujasChimenea;
    }
    if (keys[GLFW_KEY_M]) {
        activar_medusas = !activar_medusas;
    }

    if (keys[GLFW_KEY_R]) {
        activar_relojAlarma = !activar_relojAlarma;
    }


    if (keys[GLFW_KEY_K])
    {
        //Animar Bob Esponja
        playAnimacionKeyFrames = !playAnimacionKeyFrames;
        if (playAnimacionKeyFrames) {
            maxFrames = FRAMES_BOBESPONJA;
            playIndex = 0;
            resetElements();
            //First Interpolation
            interpolation();
            i_curr_steps = 0;
        }
        else {
            resetElements();
        }
    }
    if (keys[GLFW_KEY_L])
    {
        //Animar Gary
        playAnimacionKeyFrames = !playAnimacionKeyFrames;
        if (playAnimacionKeyFrames) {
            maxFrames = FRAMES_BOBESPONJA + FRAMES_GARY;
            playIndex = FRAMES_BOBESPONJA;
            resetElements();
            //First Interpolation
            interpolation();
            i_curr_steps = 0;
        }
        else {
            resetElements();
        }
    }

    if (keys[GLFW_KEY_J]) {
        activar_jugueteMedusas = !activar_jugueteMedusas;
        if (activar_jugueteMedusas)
            SpotLight = glm::vec3(0.760f, 0.0f, 0.756f);
        else
            SpotLight = glm::vec3(0.0f);
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


void animarPuerta(glm::mat4* model, bool* puerta, float* rotacionPuerta) {
    if (*puerta) {
        if (*rotacionPuerta > -90.0f) {
            *rotacionPuerta -= 10 * VELOCIDAD;
        }
    }
    else if (*rotacionPuerta < 0) {
        *rotacionPuerta += 10 * VELOCIDAD;
    }
    *model = glm::rotate(*model, glm::radians(*rotacionPuerta), glm::vec3(0.0f, 1.0f, 0.0f));
}

void animarVentana(glm::mat4* model) {
    if (abrir_ventanasCasa) {
        if (rotacionVentanasCasa > -100.0f) {
            rotacionVentanasCasa -= 10 * VELOCIDAD;
        }
    }
    else if (rotacionVentanasCasa < 0) {
        rotacionVentanasCasa += 10 * VELOCIDAD;
    }
    *model = glm::rotate(*model, glm::radians(rotacionVentanasCasa), glm::vec3(0.0f, 1.0f, 0.0f));
}


void animarJugueteMedusas(glm::mat4* model, int parte) {
    float posX, posZ;
    if (activar_jugueteMedusas) {
        switch (parte) {
        case 1:
            rotacionjugueteAnclaje += 1.0 * VELOCIDAD;
            // Rotacion del anclaje del juguete
            *model = glm::rotate(*model, glm::radians(rotacionjugueteAnclaje), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case 2:
            rotacionJuguete1 -= 2.0 * VELOCIDAD;
            // Calculo de la la traslacion en base a la rotacion del anclaje
            posX = cos(glm::radians(-rotacionjugueteAnclaje)) * (1.8944f - 1.8922f) - sin(glm::radians(-rotacionjugueteAnclaje)) * (-3.4219f + 2.3854f) + 1.8922f; //+1.8922f;
            posZ = sin(glm::radians(-rotacionjugueteAnclaje)) * (1.8944f - 1.8922f) + cos(glm::radians(-rotacionjugueteAnclaje)) * (-3.4219f + 2.3854f) - 2.3854f;// -2.3752f;
            *model = glm::translate(glm::mat4(1.0f), glm::vec3(posX, 6.9405f, posZ));
            // Rotacion de los juguetes
            *model = glm::rotate(*model, glm::radians(rotacionJuguete1), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        case 3:
            rotacionJuguete2 -= 2.0 * VELOCIDAD;
            // Calculo de la la traslacion en base a la rotacion del anclaje
            posX = cos(glm::radians(-rotacionjugueteAnclaje)) * (1.8922f - 1.8922f) - sin(glm::radians(-rotacionjugueteAnclaje)) * (-1.3860f + 2.3854f) + 1.8922f; //+1.8922f;
            posZ = sin(glm::radians(-rotacionjugueteAnclaje)) * (1.8922f - 1.8922f) + cos(glm::radians(-rotacionjugueteAnclaje)) * (-1.3860f + 2.3854f) - 2.3854f;// -2.3752f;
            *model = glm::translate(glm::mat4(1.0f), glm::vec3(posX, 6.9466f, posZ));
            // Rotacion de los juguetes
            *model = glm::rotate(*model, glm::radians(rotacionJuguete2), glm::vec3(0.0f, 1.0f, 0.0f));
            break;
        default:
            break;
        }
    }

}


void animarReloj(glm::mat4* model) {
    if (activar_relojAlarma) {
        switch (relojAnimacionEstado) {
        case 1:
            if (relojTraslacion >= 1.0f) {
                relojAnimacionEstado = 2;
            }
            relojTraslacion += 0.1 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            break;
        case 2:
            if (relojTraslacion <= 0.0f) {
                relojAnimacionEstado = 3;
            }
            relojTraslacion -= 0.1 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            break;
        case 3:
            if (relojTraslacion >= 1.0f and relojRotacion <= -45.0f) {
                relojAnimacionEstado = 4;
            }
            relojTraslacion += 0.1 * VELOCIDAD;
            relojRotacion -= 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 4:
            if (relojTraslacion <= 0.0f and relojRotacion >= 0) {
                relojAnimacionEstado = 5;
            }
            relojTraslacion -= 0.1 * VELOCIDAD;
            relojRotacion += 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 5:
            if (relojTraslacion >= 1.0f and relojRotacion >= 45.0f) {
                relojAnimacionEstado = 6;
            }
            relojTraslacion += 0.1 * VELOCIDAD;
            relojRotacion += 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 6:
            if (relojTraslacion <= 0.0f and relojRotacion <= 0.0f) {
                relojAnimacionEstado = 7;
            }
            relojTraslacion -= 0.1 * VELOCIDAD;
            relojRotacion -= 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(1.0f, 0.0f, 0.0f));
            break;
        case 7:
            if (relojTraslacion >= 1.0f and relojRotacion >= 45.0f) {
                relojAnimacionEstado = 8;
            }
            relojTraslacion += 0.1 * VELOCIDAD;
            relojRotacion += 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        case 8:// TERMINIA Y EMPIZA BURBUJAS Y SONIDO FUERTE
            if (relojRotacion <= -45.0f) {
                relojAnimacionEstado = 9;
            }
            relojRotacion -= 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(0.0f, 0.0f, 1.0f));
            activar_burbujasAlarma = true;
            break;
        case 9:// Empiezan burbujas
            if (burbujasRelojContador >= 2) {
                relojAnimacionEstado = 10;
                burbujasRelojContador = 0;
                activar_burbujasAlarma = false;
            }

            burbujasRelojContador += 0.1 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        case 10:
            if (relojTraslacion <= 0.0f and relojRotacion >= 0.0f) {
                relojAnimacionEstado = 1;
                activar_relojAlarma = !activar_relojAlarma;
            }
            relojTraslacion -= 0.1 * VELOCIDAD;
            relojRotacion += 4.5 * VELOCIDAD;
            *model = glm::translate(*model, glm::vec3(0, relojTraslacion, 0));
            *model = glm::rotate(*model, glm::radians(relojRotacion), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        default:
            break;
        }
    }
}

void animarBurbujaReloj(glm::mat4* model, int burbuja) {

    float randomNumero = (float)std::rand() / (float)(RAND_MAX + 1);
    if (activar_burbujasAlarma && burbujasRelojContador <= 2) {
        if (burbujasRelojTraslacion[burbuja] <= 10) {
            burbujasRelojTraslacion[burbuja] += 0.1 * randomNumero;
            *model = glm::translate(*model, glm::vec3(burbujasRelojTraslacion[burbuja], 0, 0));
            // std::cout << "tralacion = " << ((double)std::rand() / (RAND_MAX)) + 1 << endl;
        }
        //Reinicia la traslacion de la burbuja
        else {
            burbujasRelojTraslacion[burbuja] = 0.0;
        }
    }
}

void animarBurbujaChimenea(glm::mat4* model, int burbuja) {


    if (activar_burbujasChimenea) {
        float randomNumero = (float)std::rand() / (float)(RAND_MAX + 1);
        if (burbujasChimeneaTraslacion[burbuja] <= 10) {
            burbujasChimeneaTraslacion[burbuja] += 0.1 * randomNumero;
            *model = glm::translate(*model, glm::vec3(0, burbujasChimeneaTraslacion[burbuja], 0));
        }
        //Reinicia la traslacion de la burbuja
        else {
            burbujasChimeneaTraslacion[burbuja] = 0.0;
        }
    }
}



void animarMedusa(glm::mat4* model, float* traslacionMedusa, float* rotacionPataMedusa, int parte, bool* estadoPataMedusa) {
    if (activar_medusas) {
        switch (parte) {
        case 1:
            if (*traslacionMedusa >= 50) {
                *traslacionMedusa = 0.0f;
            }
            else {
                *traslacionMedusa += 0.1 * VELOCIDAD;
            }
            if (*rotacionPataMedusa >= 70.0) {
                *estadoPataMedusa = true;
            }
            else if (*rotacionPataMedusa <= -20.0) {
                *estadoPataMedusa = false;
            }
            if (*estadoPataMedusa) {
                *rotacionPataMedusa -= 3 * VELOCIDAD;
            }
            else {
                *rotacionPataMedusa += 3 * VELOCIDAD;

            }
            *model = glm::translate(*model, glm::vec3(*traslacionMedusa, *traslacionMedusa, 0));
            break;
        case 2:
            *model = glm::translate(*model, glm::vec3(*traslacionMedusa, *traslacionMedusa, 0));
            *model = glm::rotate(*model, glm::radians(*rotacionPataMedusa), glm::vec3(0.0f, 0.0f, 1.0f));
            break;
        case 3:
            *model = glm::translate(*model, glm::vec3(*traslacionMedusa, *traslacionMedusa, 0));
            *model = glm::rotate(*model, glm::radians(-*rotacionPataMedusa), glm::vec3(0.0f, 0.0f, 1.0f));
        default:
            break;
        }
    }
}

// Activa la animacion correspondiente de acuerdo a la distancia de la posicion de la camara
void animar() {
    // Puerta cuarto 1
    if (glm::distance(camera.GetPosition(), glm::vec3(1.7254f, 1.7624f, -6.3046)) <= RANGO_DISTANCIA) {
        abrir_puerta1 = !abrir_puerta1;
    }
    // Puerta cuarto 2
    if (glm::distance(camera.GetPosition(), glm::vec3(1.6489f, 1.7615f, 10.9612)) <= RANGO_DISTANCIA) {
        abrir_puerta2 = !abrir_puerta2;
    }
    // Puerta casa
    if (glm::distance(camera.GetPosition(), glm::vec3(-4.6333, 0.0000, 18.0085)) <= RANGO_DISTANCIA + 10) {
        abrir_puertaCasa = !abrir_puertaCasa;
    }
}

// Funciones para animaciones con Key frames y animaciones combinadas
void keyFrameAnimacion()
{

    //Movimiento del personaje

    if (playAnimacionKeyFrames)
    {
        if (i_curr_steps >= i_max_steps) //end of animation between frames?
        {
            playIndex++;
            if (playIndex == 15)
                activar_pelota = true;

            if (playIndex > maxFrames - 2)	//end of total animation?
            {
                printf("termina anim\n");
                //playIndex = 0;
                playAnimacionKeyFrames = false;
            }
            else //Next frame interpolations
            {
                i_curr_steps = 0; //Reset counter
                                  //Interpolation
                interpolation();
            }
        }
        else
        {
            //Draw animation
            posZ += KeyFrame[playIndex].incZ;
            rotCuerpo += KeyFrame[playIndex].rotIncCuerpo;
            rotPieIzq += KeyFrame[playIndex].rotPieIzqInc;
            rotPieDer += KeyFrame[playIndex].rotPieDerInc;
            rotBraIzq += KeyFrame[playIndex].rotBraIzqInc;
            rotBraDer += KeyFrame[playIndex].rotBraDerInc;
            garyPosX += KeyFrame[playIndex].garyPosXInc;
            garyPosY += KeyFrame[playIndex].garyPosYInc;
            garyPosZ += KeyFrame[playIndex].garyPosZInc;
            garyRotX += KeyFrame[playIndex].garyRotXInc;
            garyRotY += KeyFrame[playIndex].garyRotYInc;
            garyOjoIzq += KeyFrame[playIndex].garyOjoIzqInc;
            garyOjoDer += KeyFrame[playIndex].garyOjoDerInc;
            i_curr_steps++;
        }

    }
}

void animarPelota(glm::mat4* model) {
    if (activar_pelota) {
        if (rebotePelota) {
            if (posicionPelota <= 3.1130) {
                //posicionPelota = 0;
                //rotacionPelota = 0;
                activar_pelota = false;
                rebotePelota = false;
            }
            else {
                posicionPelota -= 0.5 * VELOCIDAD;
                rotacionPelota -= 80 * VELOCIDAD;
            }
        }
        else {
            if (posicionPelota >= 8) {
                rebotePelota = true;
            }
            else {
                posicionPelota += 0.3 * VELOCIDAD;
                rotacionPelota += 80 * VELOCIDAD;
            }
        }
    }
    *model = glm::translate(*model, glm::vec3(0, 0, posicionPelota));
    *model = glm::rotate(*model, glm::radians(rotacionPelota), glm::vec3(1.0f, 0.0f, 0.0f));
}




void resetElements(void)
{
    posZ = KeyFrame[0].posZ;
    rotCuerpo = KeyFrame[0].rotCuerpo;
    rotPieIzq = KeyFrame[0].rotPieIzq;
    rotPieDer = KeyFrame[0].rotPieDer;
    rotBraIzq = KeyFrame[0].rotBraIzq;
    rotBraDer = KeyFrame[0].rotBraDer;
    garyPosX = KeyFrame[0].garyPosX;
    garyPosY = KeyFrame[0].garyPosY;
    garyPosZ = KeyFrame[0].garyPosZ;
    garyRotX = KeyFrame[0].garyRotX;
    garyRotY = KeyFrame[0].garyRotY;
    garyOjoIzq = KeyFrame[0].garyOjoIzq;
    garyOjoDer = KeyFrame[0].garyOjoDer;
}


void interpolation(void)
{

    KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

    KeyFrame[playIndex].rotPieIzqInc = (KeyFrame[playIndex + 1].rotPieIzq - KeyFrame[playIndex].rotPieIzq) / i_max_steps;
    KeyFrame[playIndex].rotPieDerInc = (KeyFrame[playIndex + 1].rotPieDer - KeyFrame[playIndex].rotPieDer) / i_max_steps;
    KeyFrame[playIndex].rotBraIzqInc = (KeyFrame[playIndex + 1].rotBraIzq - KeyFrame[playIndex].rotBraIzq) / i_max_steps;
    KeyFrame[playIndex].rotBraDerInc = (KeyFrame[playIndex + 1].rotBraDer - KeyFrame[playIndex].rotBraDer) / i_max_steps;

    KeyFrame[playIndex].rotIncCuerpo = (KeyFrame[playIndex + 1].rotCuerpo - KeyFrame[playIndex].rotCuerpo) / i_max_steps;
    KeyFrame[playIndex].garyPosXInc = (KeyFrame[playIndex + 1].garyPosX - KeyFrame[playIndex].garyPosX) / i_max_steps;
    KeyFrame[playIndex].garyPosYInc = (KeyFrame[playIndex + 1].garyPosY - KeyFrame[playIndex].garyPosY) / i_max_steps;
    KeyFrame[playIndex].garyPosZInc = (KeyFrame[playIndex + 1].garyPosZ - KeyFrame[playIndex].garyPosZ) / i_max_steps;
    KeyFrame[playIndex].garyRotXInc = (KeyFrame[playIndex + 1].garyRotX - KeyFrame[playIndex].garyRotX) / i_max_steps;
    KeyFrame[playIndex].garyRotYInc = (KeyFrame[playIndex + 1].garyRotY - KeyFrame[playIndex].garyRotY) / i_max_steps;

    KeyFrame[playIndex].garyOjoIzqInc = (KeyFrame[playIndex + 1].garyOjoIzq - KeyFrame[playIndex].garyOjoIzq) / i_max_steps;
    KeyFrame[playIndex].garyOjoDerInc = (KeyFrame[playIndex + 1].garyOjoDer - KeyFrame[playIndex].garyOjoDer) / i_max_steps;


}