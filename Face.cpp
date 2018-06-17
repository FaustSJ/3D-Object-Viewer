#include "Face.h"

/*
std::vector<Edge*> edges;
std::vector<Vertex*> verticies;
bool ready;
*/

//constructors
Face::Face(){
	ready = false;
	//an empty face, to be filled later
}
Face::Face(std::vector<Edge*> e, std::vector<Vertex*> v){
	edges = e;
	verticies = v;
	ready = false;
}

void Face::addVertex(Vertex* v){ verticies.push_back(v); }
void Face::addEdge(Edge* e){ edges.push_back(e); }

/*
std::vector<Edge*> getEdges(){ return edges; }
std::vector<Vertex*> getVerticies(){ return verticies; }
void nowReady(){ ready = true;}
bool isReady(){ return ready; }
*/