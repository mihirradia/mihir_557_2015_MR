//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
// By:Mihir Radia

// stl include
#include <iostream>
#include <string>

// GLEW include
#include <GL/glew.h>

// GLM include files
#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// glfw includes
#include <GLFW/glfw3.h>


// include local files
#include "controls.h"
#include "HCI557Common.h"
#include "CoordSystem.h"
//#include "GLSphere.h"
#include "Sphere3D.h"
#include "GLAppearance.h"
#include<algorithm>



using namespace std;


// The handle to the window object
GLFWwindow*         window;

// Define some of the global variables we're using for this sample
GLuint program;

/* A trackball to move and rotate the camera view */
extern Trackball trackball;



int main(int argc, const char * argv[])
{
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Init glfw, create a window, and init glew
    
    // Init the GLFW Window
    window = initWindow();
    
    
    // Init the glew api
    initGlew();
    
    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);

    
    // create an apperance object.
    GLAppearance* apperance1 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance2 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance3 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance4 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");

    
    // The spotlight object
    GLSpotLightSource  light_source1;
    light_source1._lightPos = glm::vec4(80,0.0,-10.0, 1.0);
    light_source1._ambient_intensity = 0.0;
    light_source1._specular_intensity = 1.0;
    light_source1._diffuse_intensity = 1.0;
    light_source1._attenuation_coeff = 0.02;
    light_source1._cone_angle = 0.0; // in degree
    light_source1._cone_direction = glm::vec3(20.0, 0.0, -17.0); // this must be aligned with the object and light position.
    
    
    GLDirectLightSource  light_source2;
    light_source2._lightPos = glm::vec4(20.0,0.0,-17.0, 0.0);
    light_source2._ambient_intensity = 0.0;
    light_source2._specular_intensity = 0.8;
    light_source2._diffuse_intensity = 1.0;
    light_source2._attenuation_coeff = 0.02;
    //light_source2._cone_angle = 12.0; // in degree
   // light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source3;
	light_source3._lightPos = glm::vec4(20.0, 0.0, -9.0, 0.0);
	light_source3._ambient_intensity = 1.0;
	light_source3._specular_intensity = 0.4;
	light_source3._diffuse_intensity = 1.0;
	light_source3._attenuation_coeff = 0.02;
	//light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source4;
	light_source4._lightPos = glm::vec4(20.0, 8.0, -8.0, 0.0);
	light_source4._ambient_intensity = 0.0;
	light_source4._specular_intensity = 2.0;
	light_source4._diffuse_intensity = 0.0;
	light_source4._attenuation_coeff = 0.02;
	//light_source4._cone_angle = 12.0; // in degree
	 //light_source4._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLSpotLightSource  light_source5;
	light_source5._lightPos = glm::vec4(11.0, 1.5, -6.0, 1.0);
	light_source5._ambient_intensity = 0.0;
	light_source5._specular_intensity = 0.0;
	light_source5._diffuse_intensity = 600.0;
	light_source5._attenuation_coeff = 0.02;
	light_source5._cone_angle = 30; // in degree
	light_source5._cone_direction = glm::vec3(-1.0, 0.25, 0.0); // this must be aligned with the object and light position.

	

	GLSpotLightSource  light_source7;
	light_source7._lightPos = glm::vec4(10.0, 14, -16.0, 1.0);
	light_source7._ambient_intensity = 0.1;
	light_source7._specular_intensity = 0.0;
	light_source7._diffuse_intensity = 4.0;
	light_source7._attenuation_coeff = 0.01;
	light_source7._cone_angle = 18; // in degree
	light_source7._cone_direction = glm::vec3(-0.3, -0.5, -0.1); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source8;
	light_source8._lightPos = glm::vec4(10.0, -10.0, 8.0, 0.0);
	light_source8._ambient_intensity = 0.0;
	light_source8._specular_intensity = 0.3;
	light_source8._diffuse_intensity = 0.01;
	light_source8._attenuation_coeff = 0.02;
	//light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source9;
	light_source9._lightPos = glm::vec4(20.0, 4.0, -4.0, 0.0);
	light_source9._ambient_intensity = 0.0;
	light_source9._specular_intensity = 0.3;
	light_source9._diffuse_intensity = 0.01;
	light_source9._attenuation_coeff = 0.02;
	//light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

	GLDirectLightSource  light_source10;
	light_source10._lightPos = glm::vec4(9.0, -14.0, -6.0, 1.0);
	light_source10._ambient_intensity = 0.1;
	light_source10._specular_intensity = 0.0;
	light_source10._diffuse_intensity = 1.5;
	light_source10._attenuation_coeff = 0.02;
	//light_source2._cone_angle = 12.0; // in degree
	// light_source2._cone_direction = glm::vec3(-1.0, 0.0, 0.0); // this must be aligned with the object and light position.

  
    
    // add the spot light to this apperance object
    apperance1->addLightSource(light_source1);
    apperance1->addLightSource(light_source2);

    apperance2->addLightSource(light_source3);

	apperance3->addLightSource(light_source4);
	apperance3->addLightSource(light_source5);

	apperance4->addLightSource(light_source7);
	apperance4->addLightSource(light_source8);
	apperance4->addLightSource(light_source9);
	apperance4->addLightSource(light_source10);

    // Create a material object
    GLMaterial material1;
    material1._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material1._ambient_material = glm::vec3(1.0, 0.0, 0.0);
	material1._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material1._shininess = 80.0;

	GLMaterial material2;
	material2._diffuse_material = glm::vec3(0.0, 0.0, 1.0);
	material2._ambient_material = glm::vec3(0.0, 0.0, 0.0);
	material2._specular_material = glm::vec3(0.0, 0.0, 0.7);
	material2._shininess = 0.8;

	GLMaterial material3;
	material3._diffuse_material = glm::vec3(0.0, 1.0, 0.0);
	material3._ambient_material = glm::vec3(1.0, 1.0, 1.0);
	material3._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material3._shininess = 100.0;

	GLMaterial material4;
	material4._diffuse_material = glm::vec3(0.9, 1.0, 0.2);
	material4._ambient_material = glm::vec3(0.94, 0.98, 0.27);
	material4._specular_material = glm::vec3(1.0, 1.0, 0.1);
	material4._shininess =100.0;

    // Add the material to the apperance object
    apperance1->setMaterial(material1);
    apperance1->finalize();
    
	apperance2->setMaterial(material2);
	apperance2->finalize();

	apperance3->setMaterial(material3);
	apperance3->finalize();

	apperance4->setMaterial(material4);
	apperance4->finalize();
    // create the sphere geometry
    GLSphere3D* sphere1 = new GLSphere3D(0.0, 0.0, 18.0, 4.0, 90, 50);
	GLSphere3D* sphere2= new GLSphere3D(0.0, 0.0, 6.0, 4.0, 90, 50);
	GLSphere3D* sphere3= new GLSphere3D(0.0, 0.0, -6.0, 4.0, 400, 400);
	GLSphere3D* sphere4= new GLSphere3D(0.0, 0.0, -18.0, 4.0, 200, 200);


    sphere1->setApperance(*apperance1);
	sphere2->setApperance(*apperance2);
	sphere3->setApperance(*apperance3);
	sphere4->setApperance(*apperance4);
    
	sphere1->init();
	sphere2->init();
	sphere3->init();
	sphere4->init();
    
    
    
    //material._diffuse_material = glm::vec3(1.0, 0.0, 0.2);
    //material._ambient_material = glm::vec3(1.0, 0.0, 0.2);
    //apperance->updateMaterial();
    //light_source1._diffuse_intensity = 1.0;
    //apperance->updateLightSources();
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(50.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
   // sphere->enableNormalVectorRenderer();
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
    
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        SetTrackballLocation(trackball.getRotationMatrix());
        
        // draw the objects
        cs->draw();
        
        sphere1->draw();
		sphere2->draw();
		sphere3->draw();
		sphere4->draw();
        
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
        // Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

