#ifndef MESHDISPLAY_H
#define MESHDISPLAY_H
#include <Fl/Fl_Gl_Window.H>
#include <Fl/Gl.H>
#include <GL/glu.h>
#include <Fl/Fl.H>
#include <iostream>
#include "camera.h"
#include <vector>
#include "algebra3.h"
#include "Edge.h"
#include "Face.h"
#include "Vertex.h"

class MeshDisplay : public Fl_Gl_Window
{
private:
	float snowcapHeight;
	bool wireframe;
	int defaultRows;
	int defaultCols;
	float defaultUWidth;
	float defaultUHeight;
	Camera* c;	// a pointer to the camera	
	Vertex* selectedVertex;
	int selectedIndex;
	vec3 color;
	std::vector<Edge*> edges;
	std::vector<Vertex*> verticies;
	std::vector<Face*> faces;

	void init();
	void draw();
	int handle(int event);		// handle keyboard events
	
public:
	MeshDisplay(int x, int y, int w, int h);
	virtual ~MeshDisplay();
	void topView();
	void sideView();
	void newMesh(float uwidth, float uHeight, int rows, int cols);
	void setColor(double r, double g, double b);
	void setRed(double r);
	void setGreen(double g);
	void setBlue(double b);
	void fractalize();
	void setVertexHeight(float h);
	void addVertex(Vertex* v);
	void addEdge(Edge* e);
	void addFace(Face* f);
	void meshReset();
	void selectNext();
	void selectPrev();


	void toggleWireframe(){ wireframe = !wireframe; }
	Vertex* getSelectedVertex(){ return selectedVertex; }
	void setSelectedVertex(Vertex* v){ selectedVertex = v; }
	void setSnowcapHeight(float f){ snowcapHeight = f; }
	std::vector<Edge*> getEdges(){ return edges; }
	std::vector<Vertex*> getVerticies(){ return verticies; }
	std::vector<Face*> getFaces(){ return faces; }
};

#endif