//
//  GLObject.cpp
//  OpenGL_Transformations
//
//  Created by Rafael Radkowski on 9/12/15.
//
//

#include <glm/glm.hpp>
#include "GLObject.h"


glm::mat4 g_projectionMatrix; // Store the projection matrix
glm::mat4 g_viewMatrix; // Store the view matrix
glm::mat4 g_invViewMatrix;

glm::mat4 g_trackball; // the trackball
glm::mat4 g_rotated_view;
glm::mat4 g_inv_rotated_view;

int check_key_cam = 0;

void SetTrackballLocation(glm::mat4 trackball)
{
    g_trackball = trackball;
    g_rotated_view = g_viewMatrix * g_trackball;
    g_inv_rotated_view = glm::inverse(g_rotated_view);
    
   // cout << g_rotated_view[3][0] << "\t" << g_rotated_view[3][1] << "\t" << g_rotated_view[3][2] << endl;
}

void set_camera(int key_change)
{
	if ((key_change >= 1) && (key_change != check_key_cam))
	{
		glm::mat4 rotate_cam = glm::rotate(0.785f, glm::vec3(0.0f, 1.0f, 0.0f));
		g_viewMatrix = g_viewMatrix * rotate_cam;
		g_inv_rotated_view = glm::inverse(g_rotated_view);
		check_key_cam = key_change;
	}
}

/*!
 Global function to set the trackball data
 */
void SetTrackballLocation(glm::mat4 orientation, glm::vec3 translation)
{
    g_viewMatrix = glm::lookAt(translation, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    g_trackball = orientation;
    g_rotated_view = g_viewMatrix * g_trackball;
    g_inv_rotated_view = glm::inverse(g_rotated_view);
}



void SetViewAsLookAt(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
{
    g_viewMatrix = glm::lookAt(eye, center, up);
    g_invViewMatrix = glm::inverse(g_viewMatrix);
    
    g_rotated_view = g_viewMatrix * g_trackball;
    g_inv_rotated_view = glm::inverse(g_rotated_view);
}


void SetPerspectiveViewFrustum(float view_angle_y, float ratio, float near, float far)
{
    g_projectionMatrix = glm::perspective(view_angle_y, ratio, near, far);
  
}


/*!
 Set the camera view matrix.
 @param viewmatrix -  the view matrix;
 */
void SetViewAsMatrix(glm::mat4 viewmatrix)
{
    g_viewMatrix = viewmatrix;
    g_invViewMatrix = glm::inverse(g_viewMatrix);
    
    g_rotated_view =g_viewMatrix;
    g_inv_rotated_view = g_invViewMatrix;
}


GLObject::GLObject()
{

    g_projectionMatrix = glm::perspective(1.0f, (float)1280 / (float)720, 0.1f, 10000.f);
    g_viewMatrix = glm::lookAt(glm::vec3(5.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    g_invViewMatrix = glm::inverse(g_viewMatrix);
    
    g_trackball =  glm::mat4();
    g_rotated_view = glm::mat4();
    
}


GLObject::~GLObject()
{

}


/*!
 Add the model view matrix, especially the three shader program objects to
 the shader program "program"
 */
bool GLObject::addModelViewMatrixToProgram(GLuint program)
{
    
    _projectionMatrixLocation = glGetUniformLocation(program, "projectionMatrixBox"); // Get the location of our projection matrix in the shader
    _viewMatrixLocation = glGetUniformLocation(program, "viewMatrixBox"); // Get the location of our view matrix in the shader
    _modelMatrixLocation = glGetUniformLocation(program, "modelMatrixBox"); // Get the location of our model matrix in the shader
    _inverseViewMatrixLocation = glGetUniformLocation(program, "inverseViewMatrix");
    
    glUniformMatrix4fv(_projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix()[0][0] ); // Send our projection matrix to the shader
    glUniformMatrix4fv(_viewMatrixLocation, 1, GL_FALSE, &viewMatrix()[0][0]); // Send our view matrix to the shader
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]); // Send our model matrix to the shader
    glUniformMatrix4fv(_inverseViewMatrixLocation, 1, GL_FALSE, &g_invViewMatrix[0][0]);
    return true;
}

/*!
 Set the appearance of this object
 */
void GLObject::setApperance(GLAppearance& apperance)
{
    if(_apperance.exists())
    {
        cerr << "[GLObject] - Did not set apperrance. The appearance for this object has already been set and cannot be changed without re-initialization" << endl;
        return;
    }
    
    _apperance = apperance;
}


/*!
Returns the shader program of this object
@return, the shader program id > 0. If an appearance is not set,
            the value is also 0.
*/
int GLObject::getProgram(void)
{
    if(_apperance.exists())
    {
        return _apperance.getProgram();
    }
    else
        return 0;
}


/*!
 Set a model matrix to move the object around
 @param matrix - the model matrix for this object.
 */
void GLObject::setMatrix(glm::mat4& matrix)
{
    _modelMatrix = matrix;
    glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
}

bool GLObject::key_callback1(int _change_key)
{
	if ((_change_key >= 1)&&(_change_key!=check_key))
	{
		glm::mat4 key_trans = glm::translate(glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 key_trans1 = glm::scale(glm::vec3(10.0f, 10.0f, 10.0f));
		glm::mat4& current_loc = _modelMatrix;
		glm::mat4 key_fin = key_trans*current_loc;
		//_modelMatrix = key_fin;
		//glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
		setMatrix(key_fin);
		check_key = _change_key;
		return true;

	}
	else return false;
}
bool GLObject::key_callback2(int _change_key)
{
	if ((_change_key >= 1) && (_change_key != check_key2))
	{
		glm::mat4 key_trans = glm::translate(glm::vec3(-1.0f, 0.0f, 0.0f));
		glm::mat4 key_trans1 = glm::scale(glm::vec3(10.0f, 10.0f, 10.0f));
		glm::mat4& current_loc = _modelMatrix;
		glm::mat4 key_fin = key_trans*current_loc;
		//_modelMatrix = key_fin;
		//glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
		setMatrix(key_fin);
		check_key2 = _change_key;
		return true;

	}
}

bool GLObject::key_callback3(int _change_key)
{
		if ((_change_key >= 1) && (_change_key != check_key3))
		{
			glm::mat4 key_trans = glm::translate(glm::vec3(0.0f, 0.0f, -1.0f));
			glm::mat4 key_trans1 = glm::scale(glm::vec3(10.0f, 10.0f, 10.0f));
			glm::mat4& current_loc = _modelMatrix;
			glm::mat4 key_fin = key_trans*current_loc;
			//_modelMatrix = key_fin;
			//glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
			setMatrix(key_fin);
			check_key3 = _change_key;
			return true;

		}

}

bool GLObject::key_callback4(int _change_key)
{
	if ((_change_key >= 1) && (_change_key != check_key4))
	{
		glm::mat4 key_trans = glm::translate(glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 key_trans1 = glm::scale(glm::vec3(10.0f, 10.0f, 10.0f));
		glm::mat4& current_loc = _modelMatrix;
		glm::mat4 key_fin = key_trans*current_loc;
		//_modelMatrix = key_fin;
		//glUniformMatrix4fv(_modelMatrixLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
		setMatrix(key_fin);
		check_key4 = _change_key;
		return true;

	}

}

glm::mat4 GLObject::projectionMatrix(void)
{
    return g_projectionMatrix;
}


glm::mat4 GLObject::viewMatrix(void)
{
    return g_viewMatrix;
}

glm::mat4 GLObject::invViewMatrix(void)
{
    return g_invViewMatrix;
}


// returns the rotated view matrix, mulitplied with the trackball.
glm::mat4 GLObject::rotatedViewMatrix(void)
{
    return g_rotated_view;
}

glm::mat4 GLObject::invRotatedViewMatrix(void)
{
    return g_inv_rotated_view;
}








