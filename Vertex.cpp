#include "Vertex.h"

/*
vec4 coords;
std::vector<Edge*> edges;
std::vector<Face*> faces;
bool ready;
*/

//constructors
Vertex::Vertex(){
	ready = false;
	//an empty vertex to be filed in later
}
Vertex::Vertex(std::vector<Edge*> e, std::vector<Face*> f, vec4 c){
	edges = e;
	faces = f;
	coords = c;
	ready = false;
}

void Vertex::addEdge(Edge* e){ edges.push_back(e); }
void Vertex::addFace(Face* f){ faces.push_back(f); }

/*
std::vector<Edge*> getEdges(){ return edges; }
std::vector<Face*> getFaces(){ return faces; }
vec4 getCoords(){ return coords; }
void setCoords(vec4 v){ coords = v; }
void nowReady(){ ready = true;}
bool isReady(){ return ready; }
*/