#pragma once
#include <math.h>
#include "algebra3.h"
#include <iostream>

// A class for storing camera transforms
class Camera{
	private:
		mat4 rot;			// Current rotation matrix 
		vec3 up;				// Current up vector
		vec3 eye;			// Current eye/camera position
		vec3 angles;		//store current (r, phi, theta)
	public:
		Camera(float r, float phi, float theta); 
		void increasePhi(float inc);		// increase the phi angle. Note a negative value will decrease it. 
		void increaseTheta(float inc);		// increase the theta angle
		void increaseRad(float inc);		// increase the radius
		void hawkeye();		//move the camera to a top view
		void profile();		//move the camera to a side view
		const vec3 getEye();		// get the current eye position
		const vec3 getUp();		// get the current up vector
};