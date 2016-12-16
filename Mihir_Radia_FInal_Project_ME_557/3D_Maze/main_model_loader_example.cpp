//
//  main_spotlight.cpp
//  HCI 557 Spotlight example
//
//  Created by Rafael Radkowski on 5/28/15.
//  Copyright (c) 2015 -. All rights reserved.
// Final Project by Mihir Radia
// ME 557
// Title: 3D Maze

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
#include "Sphere3D.h"
#include "Texture.h"
#include "Plane3D.h"
#include "GLObjectObj.h"

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
	extern int forward_key;
	extern int back_key;
	extern int left_key;
	extern int right_key;
	extern int x_coord; 
	extern int y_coord;
	extern int cam_key;

    // Init the glew api
    initGlew();
    SetCameraManipulator(CameraTypes::CAMERA_MANIPULATOR);

    

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Create some models
    
    // coordinate system
    CoordSystem* cs = new CoordSystem(40.0);
    
    
    // create an apperance object.
    GLAppearance* apperance_0 = new GLAppearance("../../data/shaders/multi_vertex_lights.vs", "../../data/shaders/multi_vertex_lights.fs");
	GLAppearance* apperance_1 = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
	GLAppearance* apperance_2 = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
	GLAppearance* apperance_3 = new GLAppearance("../../data/shaders/single_texture.vs", "../../data/shaders/single_texture.fs");
	GLAppearance* apperance_4 = new GLAppearance("../../data/shaders/spherical_mapping.vs", "../../data/shaders/spherical_mapping.fs");

    GLDirectLightSource  light_source;
    light_source._lightPos = glm::vec4(100.0,100.0,100.0, 1.0);
    light_source._ambient_intensity = 100.0;
    light_source._specular_intensity = 1.5;
    light_source._diffuse_intensity = 1.0;
    light_source._attenuation_coeff = 0.0;

	GLDirectLightSource  light_source_1;
	light_source._lightPos = glm::vec4(20.0, 20.0, 0.0, 0.0);
	light_source._ambient_intensity = 0.2;
	light_source._specular_intensity = 2.5;
	light_source._diffuse_intensity = 2.0;
	light_source._attenuation_coeff = 0.0;
    
    // add the light to this apperance object
    apperance_4->addLightSource(light_source);
	apperance_1->addLightSource(light_source_1);
    
    // Create a material object
    GLMaterial material_0;
    material_0._diffuse_material = glm::vec3(1.0, 0.0, 0.0);
    material_0._ambient_material = glm::vec3(1.0, 0.0, 0.0);
    material_0._specular_material = glm::vec3(1.0, 0.0, 0.0);
    material_0._shininess = 400.0;
    material_0._transparency = 0.0;

	GLMaterial material_1;
	material_1._diffuse_material = glm::vec3(1.0, 0.64, 0.3);
	material_1._ambient_material = glm::vec3(1.0, 0.0, 0.5);
	material_1._specular_material = glm::vec3(1.0, 1.0, 1.0);
	material_1._shininess = 1.0;
	material_1._transparency = 0.0;
    
    // Add the material to the apperance object
    apperance_0->setMaterial(material_0);
    apperance_0->finalize();

	apperance_1->setMaterial(material_1);
	apperance_2->setMaterial(material_1);
	apperance_4->setMaterial(material_1);

    // If you want to change appearance parameters after you init the object, call the update function
    apperance_0->updateLightSources();
	apperance_1->updateLightSources();

    // textures
	GLTexture* texture1 = new GLTexture();
	GLTexture* texture2 = new GLTexture();
	GLTexture* texture3 = new GLTexture();
	GLTexture* texture4 = new GLTexture();

	texture1->loadAndCreateTexture("../../data/textures/texture_brick.bmp");
	texture2->loadAndCreateTexture("../../data/textures/grass.bmp");
	texture3->loadAndCreateTexture("../../data/textures/wood.bmp");
	texture4->loadAndCreateTexture("../../data/textures/environment.bmp");

	apperance_1->setTexture(texture1);
	apperance_2->setTex(texture2, 2);
	apperance_3->setTex(texture3, 3);
	apperance_4->setTex(texture4, 4);

	//objects
    GLObjectObj* loadedModel1 = new GLObjectObj("../../data/Mazeassembly.obj");
	GLObjectObj* loadedModel2 = new GLObjectObj("../../data/Assem2.obj");
    loadedModel1->setApperance(*apperance_1);
    loadedModel1->init();

	loadedModel2->setApperance(*apperance_3);
	loadedModel2->init();

	GLPlane3D* plane1 = new GLPlane3D(5.0, 0.0, 5.0, 60, 60);
	plane1->setApperance(*apperance_2);
	plane1->init();

	GLSphere3D* sphere = new GLSphere3D(0.0, 0.0, 0.0, 50.0, 90, 90);
	sphere->setApperance(*apperance_4);
	sphere->init();

	glm::mat4 rotate1 = glm::rotate(1.57f, glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 tranform_plane = glm::translate(glm::vec3(-2.0f, -7.0f, 7.0f));
	glm::mat4 tranform_multip = tranform_plane * rotate1;

	plane1->setMatrix(tranform_multip);
    glm::mat4 transform = glm::scale(glm::vec3(8.0f, 8.0f, 8.0f));
	glm::mat4 tranform1 = glm::translate(glm::vec3(-12.0f,-32.0f,-25.0f));
	glm::mat4 tranform_multi = tranform1 * transform;
    loadedModel1->setMatrix(tranform_multi);

	glm::mat4 transform2 = glm::translate(glm::vec3(-26.0f, -12.5f, 7.25f));

	glm::mat4 transform3 = glm::scale(glm::vec3(7.0f, 7.0f, 7.0f));
	
	glm::mat4 transform_multi = transform2 * transform3;

	loadedModel2->setMatrix(transform_multi);
	//glm::mat4 key_trans = glm::translate(glm::vec3(-6.0f, 11.0f, 17.5f));
	//glm::mat4 key_trans1 = glm::scale(glm::vec3(1.0f, 10.0f, 10.0f));
	//loadedModel2->setMatrix(key_trans1);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // Set up our green background color
    static const GLfloat clear_color[] = { 0.475f, 0.836f, 1.0f, 1.0f };
    static const GLfloat clear_depth[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    
    // This sets the camera to a new location
    // the first parameter is the eye position, the second the center location, and the third the up vector. 
    SetViewAsLookAt(glm::vec3(-35.0f, 30.0f, 12.0f), glm::vec3(-1.0f, -10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    
    // Enable depth test
    // ignore this line, it allows us to keep the distance value after we proejct each object to a 2d canvas.
    glEnable(GL_DEPTH_TEST);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Blending
    
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    

    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //// Main render loop
    
    // This is our render loop. As long as our window remains open (ESC is not pressed), we'll continue to render things.
    while(!glfwWindowShouldClose(window))
    {
        
        // Clear the entire buffer with our green color (sets the background to be green).
        glClearBufferfv(GL_COLOR , 0, clear_color);
        glClearBufferfv(GL_DEPTH , 0, clear_depth);
        
		if (cam_key == 4)
		{
			SetViewAsLookAt(glm::vec3(-35.0f, 30.0f, 12.0f), glm::vec3(-1.0f, -10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			cam_key = 0;
		}
		if(cam_key == 1)
			SetViewAsLookAt(glm::vec3(0.0f, 30.0f, 32.0f), glm::vec3(-1.0f, -10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		if(cam_key == 2)
			SetViewAsLookAt(glm::vec3(0.0f, 30.0f, -12.0f), glm::vec3(-1.0f, -10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		if(cam_key == 3)
			SetViewAsLookAt(glm::vec3(35.0f, 30.0f, 12.0f), glm::vec3(-1.0f, -10.0f, 10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //// This renders the objects
        
        // Set the trackball locatiom
        //SetTrackballLocation(GetCurrentCameraMatrix(), GetCurrentCameraTranslation());
		
		//set_camera(cam_key);
        
		// draw the objects
        cs->draw();
        
        loadedModel1->draw();
		loadedModel2->draw();
		plane1->draw();
		sphere->draw();
        //// This renders the objects
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		if (x_coord < 26 && (y_coord == 0))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if (x_coord > 26 && (y_coord == 0))
		{
			x_coord = 26;
		}
		if ((x_coord >= 18 && x_coord <= 26) && (y_coord == 4))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);

		}
		if ((x_coord >= 15 && x_coord <= 18) && (y_coord == 8))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);

		}
		if ((x_coord >= 18 && x_coord <= 26) && (y_coord >= 11 && y_coord <=15))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);

		}
		if ((x_coord >= 23 && x_coord <= 26) && (y_coord == 8 ))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);

		}
		if ((x_coord >= 15 && x_coord <= 19) && (y_coord == 19))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 16 && x_coord <= 19) && (y_coord == 24))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 7 && x_coord <= 40) && (y_coord == 29))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 24 && x_coord <= 28) && (y_coord == 22))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 40 && x_coord <= 45) && (y_coord == 32))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 2 && x_coord <= 40) && (y_coord == 34))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 2 && x_coord <= 13) && (y_coord == 4))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 5 && x_coord <= 10) && (y_coord == 22))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 36 && x_coord <= 40) && (y_coord == 19))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 30 && x_coord <=40) && (y_coord == 13))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 32 && x_coord <= 38) && (y_coord == 10))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 30 && x_coord <= 40) && (y_coord == 1))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}
		if ((x_coord >= 30 && x_coord <= 35) && (y_coord == 4))
		{
			loadedModel2->key_callback1(forward_key);
			loadedModel2->key_callback2(back_key);
		}


		// Y COORDINATE
		/////////////
		if (x_coord == 26 && (y_coord >= 0 && y_coord <= 4))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 18 && (y_coord >= 4 && y_coord <= 15))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 26 && (y_coord >= 8 && y_coord <= 11))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 15 && (y_coord >= 8 && y_coord <= 19))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 19 && (y_coord >= 19 && y_coord <= 24))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 16 && (y_coord >= 24 && y_coord <= 29))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 28 && (y_coord >= 22 && y_coord <= 29))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 40 && (y_coord >= 19 && y_coord <= 34))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 2 && (y_coord >= 4 && y_coord <= 34))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 10 && (y_coord >= 4 && y_coord <= 22))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 5 && (y_coord >= 8 && y_coord <= 22))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 36 && (y_coord >= 13 && y_coord <= 19))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 32 && (y_coord >= 10 && y_coord <= 13))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 40 && (y_coord >= 0 && y_coord <= 13))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}
		if (x_coord == 35 && (y_coord >= 0 && y_coord <= 4))
		{
			loadedModel2->key_callback3(left_key);
			loadedModel2->key_callback4(right_key);
		}

		// Swap the buffers so that what we drew will appear on the screen.
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    }
    
    
    delete cs;


}

