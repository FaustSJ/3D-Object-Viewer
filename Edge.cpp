#include "Edge.h"

/*
Face* neFace;
Face* swFace;
Vertex* neVertex;
Vertex* swVertex;
bool ready;
*/

//constructors
Edge::Edge(){
	ready = false;
	//and emptey edge to be filled in later
}
Edge::Edge(Face* neF, Face* swF, Vertex* neV, Vertex* swV){
	neFace = neF;
	swFace = swF;
	neVertex = neV;
	swVertex = swV;
	ready = false;
}

/*
Face* getNEFace(){ return neFace; }
Face* getSWFace(){ return swFace; }
Vertex* getNEVertex(){ return neVertex; }
Vertex* getSWVertex(){ return swVertex; }
void setNEFace(Face* f){ neFace = f; }
void setSWFace(Face* f){ swFace = f; }
void setNEVertex(Vertex* v){ neVertex = v; }
void setSWVertex(Vertex* v){ swVertex = v; }
void nowReady(){ ready = true;}
bool isReady(){ return ready; }
*/

