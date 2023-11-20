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
    string path = "/home/vittorio/Documents/TSI/OpenGL/Solar-systeme-with-OpenGL";

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

    Shader shader(path+"/shaders/SimpleVertexShader.vertexshader", path+"/shaders/SimpleFragmentShader.fragmentshader");
    shader.Bind();

/////////////////////////On crée un vertex array/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    VertexArray va;
    va.Bind();

/////////////////////////On crée la camera et les contrôles/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Camera cam(width, height);
    cam.setFoV(90);
    cam.position = glm::vec3(-1,2,0);
    cam.horizontalAngle = 1.50;
    cam.verticalAngle = 12.0;
    NavigationControls controls(window, &cam);

/////////////////////////Création des formes à afficher/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    ////////////////////////////// Fichier obj //////////////////////////


    std::vector<double> semiMajorAxis_   = {0.00, 0.0, 0.390, 0.720, 1.0000, 1.520, 5.200, 9.580, 19.22, 30.05};
    std::vector<double> eccentricity_    = {0.00, 0.0, 0.206, 0.007, 0.0170, 0.093, 0.049, 0.057, 0.046, 0.010};
    std::vector<double> angularVelocity_ = {0.00, 0.0, 1.240, 1.170, 1.0000, 0.520, 0.080, 0.034, 0.010, 0.006};

    std::vector<Object*> planets;

    Object stars(path+"/planete.obj",path+"/ressources/textures/2k_stars.jpg",semiMajorAxis_[0], eccentricity_[0], angularVelocity_[0]);
    Object sun(path+"/planete.obj",path+"/ressources/textures/2k_sun.jpg", semiMajorAxis_[1], eccentricity_[1], angularVelocity_[1]);
    Object mercury(path+"/planete.obj",path+"/ressources/textures/2k_mercury.jpg", semiMajorAxis_[2], eccentricity_[2], angularVelocity_[2]);
    Object venus(path+"/planete.obj",path+"/ressources/textures/2k_venus_surface.jpg", semiMajorAxis_[3], eccentricity_[3], angularVelocity_[3]);
    Object earth(path+"/planete.obj",path+"/ressources/textures/2k_earth_daymap.jpg", semiMajorAxis_[4], eccentricity_[4], angularVelocity_[4]);
    Object mars(path+"/planete.obj",path+"/ressources/textures/2k_mars.jpg", semiMajorAxis_[5], eccentricity_[5], angularVelocity_[5]);
    Object jupiter(path+"/planete.obj",path+"/ressources/textures/2k_jupiter.jpg", semiMajorAxis_[6], eccentricity_[6], angularVelocity_[6]);
    Object saturn(path+"/planete.obj",path+"/ressources/textures/2k_saturn.jpg", semiMajorAxis_[7], eccentricity_[7], angularVelocity_[7]);
    Object uranus(path+"/planete.obj",path+"/ressources/textures/2k_uranus.jpg", semiMajorAxis_[8], eccentricity_[8], angularVelocity_[8]);
    Object neptune(path+"/planete.obj",path+"/ressources/textures/2k_neptune.jpg", semiMajorAxis_[9], eccentricity_[9], angularVelocity_[9]);


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


/////////////////////////////// Position des planètes


    sun.scale = glm::vec3(0.3f, 0.3f, 0.3f);

    mercury.scale = glm::vec3(0.04f,0.04f,0.04f);

    venus.scale = glm::vec3(0.09f, 0.09f,0.09f);

    earth.scale = glm::vec3(0.1f, 0.1f,0.1f);

    mars.scale = glm::vec3(0.05f, 0.05f, 0.05f);

    jupiter.scale = glm::vec3(0.5f, 0.5f, 0.5f);

    saturn.scale = glm::vec3(0.4f,0.4f,0.4f);

    uranus.scale = glm::vec3(0.2f, 0.2f, 0.2f);

    neptune.scale = glm::vec3(0.2f, 0.2f, 0.2f);

    stars.scale = glm::vec3(70.0f, 70.0f, 70.0f);






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

        mercury.rotationAngles.y=currentTime;
        venus.rotationAngles.y=currentTime;
        earth.rotationAngles.y=currentTime;
        mars.rotationAngles.y=currentTime;
        jupiter.rotationAngles.y=currentTime;
        saturn.rotationAngles.y=currentTime;
        uranus.rotationAngles.y=currentTime;
        neptune.rotationAngles.y=currentTime;



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
        float diffuseStrength = 3.0f;
        glm::vec3 diffuselightColor(1.0f, 1.0f, 1.0f);
        shader.setUniform3fv("diffuselightColor", diffuselightColor);
        shader.setUniform1f("diffuseStrength", diffuseStrength);

        //Lumière spéculaire
        float specularStrength = 1.0f;
        glm::vec3 specularLightColor(0.0f, 5.0f, 0.0f);
        shader.setUniform3fv("specularLightColor", specularLightColor);
        shader.setUniform1f("specularStrength",specularStrength);
        shader.setUniform1f("shininess",25.0f);


        for (auto &planet : planets) {
            // Envoyer les données spécifiques de la planète au shader
            glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f),planet->scale);
            glm::mat4 modelMatrix = planet->getModelMatrix() * scaleMatrix;
            glm::mat4 mvp = p * v * modelMatrix;
            shader.setUniformMat4f("MVP", mvp);
            shader.setUniformMat4f("m", modelMatrix);
            if (planet == addressof(sun) or planet == addressof(stars)){
                shader.setUniform1f("ambientStrength", 2.0f);
            }else{
                 shader.setUniform1f("ambientStrength", 0.5f);
                 double theta = planet->angularVelocity * currentTime;
                 double r = planet->semiMajorAxis * (1 - planet->eccentricity * planet->eccentricity) / (1 + planet->eccentricity * cos(theta));
                 planet->position.x = r * cos(theta);
                 planet->position.z = r * sin(theta);

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
