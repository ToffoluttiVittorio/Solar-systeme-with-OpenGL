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
//    string path = "/home/formation/Documents/TSI_Vitto/OpenGL";
    string path = "/home/vittorio/Documents/TSI/Open_gl/Solar-systeme-with-OpenGL";
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

    Shader shader("/home/vittorio/Documents/TSI/Open_gl/Solar-systeme-with-OpenGL/shaders/SimpleVertexShader.vertexshader", "/home/vittorio/Documents/TSI/Open_gl/Solar-systeme-with-OpenGL/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    cam.setFoV(90);
    cam.position = glm::vec3(-20,15,0);
    cam.horizontalAngle = 1.50;
    cam.verticalAngle = 12.2;
    NavigationControls controls(window, &cam);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////// Fichier obj //////////////////////////

    std::vector<Object*> planets;

    Object sun(path+"/planete.obj",path+"/ressources/textures/2k_sun.jpg");
    Object mercury(path+"/planete.obj",path+"/ressources/textures/2k_mercury.jpg");
    Object venus(path+"/planete.obj",path+"/ressources/textures/2k_venus_surface.jpg");
    Object earth(path+"/planete.obj",path+"/ressources/textures/2k_earth_daymap.jpg");
    Object mars(path+"/planete.obj",path+"/ressources/textures/2k_mars.jpg");
    Object jupiter(path+"/planete.obj",path+"/ressources/textures/2k_jupiter.jpg");
    Object saturn(path+"/planete.obj",path+"/ressources/textures/2k_saturn.jpg");
    Object uranus(path+"/planete.obj",path+"/ressources/textures/2k_uranus.jpg");
    Object neptune(path+"/planete.obj",path+"/ressources/textures/2k_neptune.jpg");
    Object stars(path+"/planete.obj",path+"/ressources/textures/2k_stars.jpg");

    planets.push_back(&sun);
    planets.push_back(&mercury);
    planets.push_back(&venus);
    planets.push_back(&earth);
    planets.push_back(&mars);
    planets.push_back(&jupiter);
    planets.push_back(&saturn);
    planets.push_back(&uranus);
    planets.push_back(&neptune);
    planets.push_back(&stars);

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

    mercury.position.x = 10;
    mercury.position.y = 0;

    float mercuryda = 58.0f; //en millions de kilomètres
    float mercurye = 0.2f;
    float mercuryv = 48.0f; //en km/s

    venus.position.x = 15;
    venus.position.y = 0;

    float venusda = 108.0f; //en millions de kilomètres
    float venuse = 0.0007f;
    float venusv = 35.0f; //en km/s

    earth.position.x = 20;
    earth.position.y = 0;

    float earthda = 150.0f; //en millions de kilomètres
    float earthe = 0.02f;
    float earthv = 35.0f; //en km/s

    mars.position.x = 25;
    mars.position.y = 0;

    float marsda = 230.0f; //en millions de kilomètres
    float marse = 0.01f;
    float marsv = 24.0f; //en km/s

    jupiter.position.x = 40;
    jupiter.position.y = 0;

    float jupiterda = 778.0f; //en millions de kilomètres
    float jupitere = 0.05f;
    float jupiterv = 13.0f; //en km/s

    saturn.position.x = 50;
    saturn.position.y = 0;

    float saturnda = 1427.0f; //en millions de kilomètres
    float saturnee = 0.056f;
    float saturnv = 10.0f; //en km/s

    uranus.position.x = 60;
    uranus.position.y = 0;

    float uranusda = 2870.0f; //en millions de kilomètres
    float uranuse = 0.046f;
    float uranusv = 7.0f; //en km/s

    neptune.position.x = 70;
    neptune.position.y = 0;

    float neptuneda = 4500.0f; //en millions de kilomètres
    float neptunee = 0.01f;
    float neptunev = 5.43f; //en km/s

    stars.position.x = 0;
    stars.position.y = 0;


    sun.scale = glm::vec3(7.0f, 7.0f, 7.0f);

    mercury.scale = glm::vec3(0.8f,0.8f,0.8f);

    venus.scale = glm::vec3(1.5f, 1.5f,1.5f);

    earth.scale = glm::vec3(1.5f, 1.5f,1.5f);

    mars.scale = glm::vec3(1.0f, 1.0f, 1.0f);

    jupiter.scale = glm::vec3(5.0f, 5.0f, 20.0f);

    saturn.scale = glm::vec3(4.0f,4.0f,4.0f);

    uranus.scale = glm::vec3(2.5f, 2.5f, 2.5f);

    neptune.scale = glm::vec3(2.4f, 2.4f, 2.4f);

    stars.scale = glm::vec3(100.0f, 100.0f, 100.0f);






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
//        float ambientStrength = 0.5f;
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("lightColor", lightColor);
//        shader.setUniform1f("ambientStrength", ambientStrength);

        // Lumière diffuse
        float diffuseStrength = 10.0f;
        glm::vec3 diffuselightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("diffuselightColor", diffuselightColor);
        shader.setUniform1f("diffuseStrength", diffuseStrength);

        //Lumière spéculaire
        float specularStrength = 5.0f;
        glm::vec3 specularLightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("specularLightColor", specularLightColor);
        shader.setUniform1f("specularStrength",specularStrength);
        shader.setUniform1f("shininess",15.0f);


        for (auto &planet : planets) {
            // Envoyer les données spécifiques de la planète au shader
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),planet->scale);
            glm::mat4 modelMatrix = planet->getModelMatrix() * scaleMatrix;
            glm::mat4 mvp = p * v * modelMatrix;
            shader.setUniformMat4f("MVP", mvp);
            shader.setUniformMat4f("m", modelMatrix);
            if (planet == addressof(sun) or planet == addressof(stars)){
                shader.setUniform1f("ambientStrength", 3.0f);
            }else{
                 shader.setUniform1f("ambientStrength", 0.5f);
            }

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
