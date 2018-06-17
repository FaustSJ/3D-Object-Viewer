#include "camera.h"

/*
mat4 rot;			// Current rotation matrix
vec3 up;				// Current up vector (the vertical direction)
vec3 eye;			// Current eye/camera position
vec3 angles;		//store current (r, phi, theta)
*/

//phi is the angle off of the Z axis (up/down)
//theta is the angle off of the X axis (left/right)
//r is the distance from the origin
Camera::Camera(float r, float phi, float theta){
	up = vec3(0.0, 1.0, 0.0);
	eye = vec3(0, 0, 20);
	rot = rotation3D(vec3(1, 0, 0), phi) * rotation3D(vec3(0, 1, 0), theta);
	angles = vec3(r, phi, theta);
}

// increase the phi angle. Note a negative value will decrease it. 
void Camera::increasePhi(float inc){
	rot = rot*rotation3D(vec3(0, 1, 0), inc);
}

// increase the theta angle
void Camera::increaseTheta(float inc){
	rot = rot*rotation3D(vec3(1, 0, 0), inc);
}

// increase the radius
void Camera::increaseRad(float inc){
	eye[2] = eye[2] + inc;
}

//move the camera to a top view
void Camera::hawkeye(){
	rot = rotation3D(vec3(1, 0, 0), 90);
}
//move the camera to a side view
void Camera::profile(){
	rot = rotation3D(vec3(0, 1, 0), 90);
}

// get the current eye position
const vec3 Camera::getEye(){
	return eye*rot;
}

// get the current up vector
const vec3 Camera::getUp(){
	return up;// *rot;  commenting this because we need up to be constant
}