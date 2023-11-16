#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <vector>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "renderer.h"
#include "camera.h"
#include "navigationcontrols.h"
#include "pointlight.h"



using namespace std;

int main()
{
    string path = "/home/formation/Documents/TSI_Vitto/OpenGL";
/////////////////////////Initialisation de GLFW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }


    glfwWindowHint(GLFW_SAMPLES, 4); //antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //version core

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


/////////////////////////Ouverture de la fenêtre/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //définition de la taille de la fenêtre
    int width=600;
    int height=600;

    //On récupère les dimensions de l'écran pour créer la fenètre
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    glfwGetMonitorWorkarea(primary,nullptr,nullptr, &width, &height);

    //Enfin on crée la fenêtre
    GLFWwindow* window = glfwCreateWindow(width,height,"OpenGL_API",NULL,NULL);
    glfwSwapInterval(1);
    //On vérifie que l'initialisation a bien marché
    if (window==NULL){
        fprintf(stderr, "Erreur lors de la création de la fénêtre\n");
        glfwTerminate();
        return -1;
    }

    //Enfin on définit la fenêtre créée comme la fenêtre sur laquelle on va dessiner
    glfwMakeContextCurrent(window);



/////////////////////////Initialisation de GLEW/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //Initialisation de GLEW
    glewExperimental=true;
    if (glewInit() != GLEW_OK){
        fprintf(stderr, "Erreur lors de l'initialisation de GLEW\n");
        return -1;
    }


/////////////////////////On crée un Renderer/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Renderer renderer;

/////////////////////////On crée un Shader/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Shader shader(path+"/OGL_TP/shaders/SimpleVertexShader.vertexshader", path+"/OGL_TP/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    NavigationControls controls(window, &cam);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//    vector<glm::vec3> g_vertex_buffer_data = {
//        glm::vec3(-1.0f,-1.0f,-1.0f), // triangle 1 : begin
//        glm::vec3(-1.0f,-1.0f, 1.0f),
//        glm::vec3(-1.0f, 1.0f, 1.0f), // triangle 1 : end
//        glm::vec3(1.0f, 1.0f,-1.0f), // triangle 2 : begin
//        glm::vec3(-1.0f,-1.0f,-1.0f),
//        glm::vec3(-1.0f, 1.0f,-1.0f), // triangle 2 : end
//        glm::vec3(1.0f,-1.0f, 1.0f),
//        glm::vec3(-1.0f,-1.0f,-1.0f),
//        glm::vec3(1.0f,-1.0f,-1.0f),
//        glm::vec3(1.0f, 1.0f,-1.0f),
//        glm::vec3(1.0f,-1.0f,-1.0f),
//        glm::vec3(-1.0f,-1.0f,-1.0f),
//        glm::vec3(-1.0f,-1.0f,-1.0f),
//        glm::vec3(-1.0f, 1.0f, 1.0f),
//        glm::vec3(-1.0f, 1.0f,-1.0f),
//        glm::vec3(1.0f,-1.0f, 1.0f),
//        glm::vec3(-1.0f,-1.0f, 1.0f),
//        glm::vec3(-1.0f,-1.0f,-1.0f),
//        glm::vec3(-1.0f, 1.0f, 1.0f),
//        glm::vec3(-1.0f,-1.0f, 1.0f),
//        glm::vec3(1.0f,-1.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f,-1.0f,-1.0f),
//        glm::vec3(1.0f, 1.0f,-1.0f),
//        glm::vec3(1.0f,-1.0f,-1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f,-1.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f,-1.0f),
//        glm::vec3(-1.0f, 1.0f,-1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(-1.0f, 1.0f,-1.0f),
//        glm::vec3(-1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f, 1.0f, 1.0f),
//        glm::vec3(-1.0f, 1.0f, 1.0f),
//        glm::vec3(1.0f,-1.0f, 1.0f)
//    };

//    vector<glm::vec2> g_uv_buffer_data = {
//        glm::vec2(0.000059f, 1.0f-0.000004f),
//        glm::vec2(0.000103f, 1.0f-0.336048f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(1.000023f, 1.0f-0.000013f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.999958f, 1.0f-0.336064f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.336024f, 1.0f-0.671877f),
//        glm::vec2(0.667969f, 1.0f-0.671889f),
//        glm::vec2(1.000023f, 1.0f-0.000013f),
//        glm::vec2(0.668104f, 1.0f-0.000013f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.000059f, 1.0f-0.000004f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(0.336098f, 1.0f-0.000071f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(0.336024f, 1.0f-0.671877f),
//        glm::vec2(1.000004f, 1.0f-0.671847f),
//        glm::vec2(0.999958f, 1.0f-0.336064f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.668104f, 1.0f-0.000013f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(0.667979f, 1.0f-0.335851f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(0.668104f, 1.0f-0.000013f),
//        glm::vec2(0.336098f, 1.0f-0.000071f),
//        glm::vec2(0.000103f, 1.0f-0.336048f),
//        glm::vec2(0.000004f, 1.0f-0.671870f),
//        glm::vec2(0.336024f, 1.0f-0.671877f),
//        glm::vec2(0.000103f, 1.0f-0.336048f),
//        glm::vec2(0.336024f, 1.0f-0.671877f),
//        glm::vec2(0.335973f, 1.0f-0.335903f),
//        glm::vec2(0.667969f, 1.0f-0.671889f),
//        glm::vec2(1.000004f, 1.0f-0.671847f),
//        glm::vec2(0.667979f, 1.0f-0.335851f)
//    };

//    Object o(g_vertex_buffer_data, g_uv_buffer_data, path+"/OGL_TP/ressources/textures/roche.jpg");

    ////////////////////////////// Fichier obj //////////////////////////

    std::vector<Object*> planets;

    Object sun(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_sun.jpg");
    Object mercury(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_mercury.jpg");
    Object venus(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_venus_surface.jpg");
    Object earth(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_earth_daymap.jpg");
    Object mars(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_mars.jpg");
    Object jupiter(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_jupiter.jpg");
    Object saturn(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_saturn.jpg");
    Object uranus(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_uranus.jpg");
    Object neptune(path+"/OGL_TP/planete.obj",path+"/OGL_TP/ressources/textures/2k_neptune.jpg");

    planets.push_back(&sun);
    planets.push_back(&mercury);
    planets.push_back(&venus);
    planets.push_back(&earth);
    planets.push_back(&mars);
    planets.push_back(&jupiter);
    planets.push_back(&saturn);
    planets.push_back(&uranus);
    planets.push_back(&neptune);


/////////////////////////Création de la matrice MVP/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//    cam.computeMatrices(width, height);
//    glm::mat4 m = o.getModelMatrix();
//    glm::mat4 v = cam.getViewMatrix();
//    glm::mat4 p = cam.getProjectionMatrix();

//    glm::mat4 mvp = p*v*m;

//    shader.setUniformMat4f("MVP", mvp);
//    shader.setUniformMat4f("m", m);

    ///Light

//    // Position de la lumière
//    glm::vec3 lightPosition(2.0f, 2.0f, 2.0f);
//    // Couleur de la lumière
//    glm::vec3 lightColor(5.0f, 1.0f, 1.0f);
//    //Intensité de la lumière
//    float intensity(100.0f);

//    PointLight pointlight(lightPosition, lightColor, intensity);

//    shader.setUniform3fv("pointlight", lightColor);
//    shader.setUniform1f("pointlightpower", intensity);

    /////////////////////////////// Position des planètes


    sun.position.x = 0;
    sun.position.y = 0;

    mercury.position.x = 5;
    mercury.position.y = 0;

    venus.position.x = 10;
    venus.position.y = 0;

    earth.position.x = 15;
    earth.position.y = 0;

    mars.position.x = 20;
    mars.position.y = 0;

    jupiter.position.x = 25;
    jupiter.position.y = 0;

    saturn.position.x = 30;
    saturn.position.y = 0;

    uranus.position.x = 35;
    uranus.position.y = 0;

    neptune.position.x = 40;
    neptune.position.y = 0;



/////////////////////////Boucle de rendu/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    // Assure que l'on peut capturer les touche de clavier
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //On indique la couleur de fond
//    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    //On autorise les tests de profondeur

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float lastTime = glfwGetTime();
    float currentTime, deltaTime;

    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && !glfwWindowShouldClose(window)){


        currentTime = glfwGetTime();
        deltaTime = currentTime-lastTime;
        lastTime = currentTime;

        renderer.Clear();

        controls.update(deltaTime, &shader);
        cam.computeMatrices(width, height);



//        sun.rotationAngles.y=currentTime;

//        glm::mat4 modelMatrix = sun.getModelMatrix();
        glm::mat4 v = cam.getViewMatrix();
        glm::mat4 p = cam.getProjectionMatrix();
//        glm::mat4 mvp = p * v * modelMatrix;
//        shader.setUniformMat4f("MVP", mvp);
//        shader.setUniformMat4f("m", modelMatrix);

//        renderer.Draw(va, sun, shader);
//        renderer.Draw(va, earth, shader);

        // Lumière ambiante
        float ambientStrength = 0.5f;
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("lightColor", lightColor);
        shader.setUniform1f("ambientStrength", ambientStrength);

        // Lumière diffuse
        float diffuseStrength = 0.7f;
        glm::vec3 diffuselightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("diffuselightColor", diffuselightColor);
        shader.setUniform1f("diffuseStrength", diffuseStrength);

        //Lumière spéculaire
        float specularStrength = 0.5f;
        glm::vec3 specularLightColor(1.0f, 10.0f, 1.0f);
        shader.setUniform3fv("specularLightColor", specularLightColor);
        shader.setUniform1f("specularStrength",specularStrength);
        shader.setUniform1f("shininess",15.0f);


        for (auto &planet : planets) {
            // Envoyer les données spécifiques de la planète au shader
            glm::mat4 modelMatrix = planet->getModelMatrix();
            glm::mat4 mvp = p * v * modelMatrix;
            shader.setUniformMat4f("MVP", mvp);
            shader.setUniformMat4f("m", modelMatrix);


            renderer.Draw(va, *planet, shader);
        }

        cam.Bind(&shader);

        ////////////////Partie rafraichissement de l'image et des évènements///////////////
        //Swap buffers : frame refresh
        glfwSwapBuffers(window);
        //get the events
        glfwPollEvents();
    }
    glfwTerminate();




    return 0;
}
