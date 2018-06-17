#include <iostream>
#include "algebra3.h"
#include "camera.h"
#include "Edge.h"
#include "Face.h"
#include "MeshDisplay.h"
#include "Vertex.h"
#include "WindowGUI.h"

class Edge;
class Face;
class Vertex;

int main(int argc, char * const argv[]){
	//	TheWindow *g = new TheWindow(10, 10, 702, 378, "Polygon Tree GUI"); // create a window
	WindowGUI *g = new WindowGUI(10, 10, 769, 519, "Mini Maya"); // create a window
	g->color((Fl_Color)14);
	g->show();  // show the window

	return Fl::run(); // tell FLTK to go
	return 0;
}