#pragma once
//#ifndef FACE_H
//#define FACE_H
#include <vector>
//#include "Edge.h"
//#include "Vertex.h"

class Edge;
class Vertex;

class Face{
private:
	std::vector<Edge*> edges;
	std::vector<Vertex*> verticies;
	bool ready;
public:
	//constructors
	Face();
	Face(std::vector<Edge*> e, std::vector<Vertex*> v);

	void addVertex(Vertex* v);
	void addEdge(Edge* e);
	std::vector<Edge*> getEdges(){ return edges; }
	std::vector<Vertex*> getVerticies(){ return verticies; }
	void nowReady(){ ready = true;}
	bool isReady(){ return ready; }
};
//#endif