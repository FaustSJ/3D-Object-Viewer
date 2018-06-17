#pragma once
//#ifndef EDGE_H
//#define EDGE_H
#include <vector>
#include "Face.h"
#include "Vertex.h"

class Edge{
private:
	Face* neFace;
	Face* swFace;
	Vertex* neVertex;
	Vertex* swVertex;
	bool ready;
public:
	//constructors
	Edge();
	Edge(Face* neF, Face* swF, Vertex* neV, Vertex* swV);

	//getters and setters
	Face* getNEFace(){ return neFace; }
	Face* getSWFace(){ return swFace; }
	Vertex* getNEVertex(){ return neVertex; }
	Vertex* getSWVertex(){ return swVertex; }
	void setNEFace(Face* f){ neFace = f; }
	void setSWFace(Face* f){ swFace = f; }
	void setNEVertex(Vertex* v){ neVertex = v; }
	void setSWVertex(Vertex* v){ swVertex = v; }
	void nowReady(){ ready = true; }
	bool isReady(){ return ready; }

};
//#endif