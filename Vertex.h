#pragma once
//#ifndef VERTEX_H
//#define VERTEX_H
#include <vector>
#include "algebra3.h"
//#include "Edge.h"
#include "Face.h"

class Edge; 
class Face;

class Vertex{
private:
	vec4 coords;
	std::vector<Edge*> edges;
	std::vector<Face*> faces;
	bool ready;
public:	
	//constructors
	Vertex();
	Vertex(std::vector<Edge*> e, std::vector<Face*> f, vec4 c);

	void addEdge(Edge* e);
	void addFace(Face* f);
	std::vector<Edge*> getEdges(){ return edges; }
	std::vector<Face*> getFaces(){ return faces; }
	vec4 getCoords(){ return coords; }
	void setCoords(vec4 v){ coords = v; }
	void nowReady(){ ready = true; }
	bool isReady(){ return ready; }
};

//#endif