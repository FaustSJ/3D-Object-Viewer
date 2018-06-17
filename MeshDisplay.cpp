#include "MeshDisplay.h"

/*
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
*/

//////////////////////////////////////////////////////////////////////////////
//CONSTRUCTOR AND DESTRUCTOR
//////////////////////////////////////////////////////////////////////////////
MeshDisplay::MeshDisplay(int x, int y, int w, int h) :Fl_Gl_Window(x, y, w, h){
	c = new Camera(4, 0, 0);	// create a camera
	wireframe = true;
	color = vec3(1, 1, 1);
	snowcapHeight = 20;
	//makes a default mesh
	defaultRows = 5;
	defaultCols = 5;
	defaultUWidth = 3;
	defaultUHeight = 3;
	newMesh(3, 3, 5, 5); //sets up vectors and selectedVertex
}

MeshDisplay::~MeshDisplay(){
	delete(c);
	c = NULL;

	edges.clear();
	verticies.clear();
	faces.clear();
}

//////////////////////////////////////////////////////////////////////////////
//DRAWING AND HANDLING
//////////////////////////////////////////////////////////////////////////////
void MeshDisplay::init(){
	glViewport(0, 0, w(), h());
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//	glOrtho(-10, 10, -10, 10, -10, 10);
	gluPerspective(90, 1, 0.1, 40); //(angle off y, aspect ratio, zNear, zFar)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void MeshDisplay::draw(){
	//set up the window and drawing area
	if (!valid()){
		init();				// make sure the OpenGL settings are completed once before drawing
		valid(1);
	}
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
	vec3 eye = c->getEye();
	vec3 up = c->getUp();
	gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, up[0], up[1], up[2]); // camera control

	/////////////////////////////////
	//Draw the mesh and the wireframe
	/////////////////////////////////
	for(Face* f : faces){//for each face...
		//...draw the mesh...
		glBegin(GL_POLYGON);
		for (Vertex* v : f->getVerticies()){//connect the verticies.
			//get the current vertex's coordinates
			vec4 vCor = v->getCoords();
			//check how it should be colored
			if (vCor[1] >= snowcapHeight){glColor3f(0.5, 0.5, 1);}
			else{ glColor3d(color[0], color[1], color[2]); }
			//then draw the vertex
			glVertex3d(vCor[0], vCor[1], vCor[2]);
		}
		glEnd();
		//...and check if we need to draw the wireframe.
		if (wireframe){
			glColor3d(0.43, 0, 0);
			glBegin(GL_LINE_LOOP);
			for (Vertex* v : f->getVerticies()){//connect the verticies.
				//get the current vertex's coordinates
				vec4 vCor = v->getCoords();
				//then draw the vertex
				glVertex3d(vCor[0], vCor[1]+0.1, vCor[2]);
			}
			glEnd();
		}
	}

	/////////////////////////////////////////////
	//draw a box around the selected vertex
	////////////////////////////////////////////
	vec4 bOrigin = selectedVertex->getCoords();


	glColor3d(1, 0.23, 0.23);
	glBegin(GL_QUADS); //front
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
	glEnd();
	glBegin(GL_QUADS); //back
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
	glEnd();
	glBegin(GL_QUADS); //left
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
	glEnd();
	glBegin(GL_QUADS); //right
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
	glEnd();
	glBegin(GL_QUADS); //top
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] + 0.25), (bOrigin[2] - 0.25));
	glEnd();
	glBegin(GL_QUADS); //bottom
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
		glVertex3d((bOrigin[0] - 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] - 0.25), (bOrigin[2] + 0.25));
		glVertex3d((bOrigin[0] + 0.25), (bOrigin[1] - 0.25), (bOrigin[2] - 0.25));
	glEnd();
}

//to control the camera
int MeshDisplay::handle(int event){		// handle keyboard events
	if (event == FL_KEYUP){				// when the key is released, check for an event and handle it
		if (Fl::event_key() == 'a'){
			c->increasePhi(-7);
			redraw();
		}
		if (Fl::event_key() == 'd'){
			c->increasePhi(7);
			redraw();
		}
		if (Fl::event_key() == 'w'){
			c->increaseTheta(-7);
			redraw();
		}
		if (Fl::event_key() == 's'){
			c->increaseTheta(7);
			redraw();
		}
		if (Fl::event_key() == 'e'){
			c->increaseRad(-.5);
			redraw();
		}
		if (Fl::event_key() == 'f'){
			c->increaseRad(.5);
			redraw();
		}
	}
	return Fl_Gl_Window::handle(event);
}

//the public methods
//////////////////////////////////////////////////////////////////////////////
//ADDING ELEMENTS
//////////////////////////////////////////////////////////////////////////////
void MeshDisplay::addVertex(Vertex* v){ verticies.push_back(v); }
void MeshDisplay::addEdge(Edge* e){ edges.push_back(e); }
void MeshDisplay::addFace(Face* f){ faces.push_back(f); }
//////////////////////////////////////////////////////////////////////////////
//VIEWS
//////////////////////////////////////////////////////////////////////////////
void MeshDisplay::topView(){ c->hawkeye(); }
void MeshDisplay::sideView(){ c->profile(); }
/////////////////////////////////////////////////////////////////////////////
//SET COLOR
/////////////////////////////////////////////////////////////////////////////
void MeshDisplay::setColor(double r, double g, double b){ color = vec3(r, g, b); }
void MeshDisplay::setRed(double r){ color[0] = r; }
void MeshDisplay::setGreen(double g){ color[1] = g; }
void MeshDisplay::setBlue(double b){ color[2] = b; }

//////////////////////////////////////////////////////////////////////////////
//MESH MAKING
//////////////////////////////////////////////////////////////////////////////
//reverts the mesh to its original default shape
void MeshDisplay::meshReset(){ newMesh(defaultUWidth, defaultUHeight, defaultRows, defaultCols);}

void MeshDisplay::newMesh(float uWidth, float uHeight, int rows, int cols){
	//starting from scratch includes clearing the lists
	verticies.clear();
	edges.clear();
	faces.clear();
	//in case the given values differ from the default values, update the defaults
	defaultUWidth = uWidth;
	defaultUHeight = uHeight;
	defaultRows = rows;
	defaultCols = cols;	
/*
VERTEX:
	setCoords(vec4 v)
	Vertex::addEdge(Edge* e)
	Vertex::addFace(Face* f)
FACE:
	addVertex(Vertex* v)
	addEdge(Edge* e)
EDGE:
	setNEFace(Face* f)
	setSWFace(Face* f)
	setNEVertex(Vertex* v)
	setSWVertex(Vertex* v)

	nowReady()
	isReady()
*/
	float mx = (uWidth*cols) / 2;//represents how far the mesh extends from the origin along the z-axis
	float mz = (uHeight*rows) / 2;//represents how far the mesh extends from the origin along the y-axis
	//mem vectors store data to be passed between rows
	std::vector<Face*> memF;
	std::vector<Edge*> memE;
	std::vector<Vertex*> memV;

/* Example: how newMesh() makes a 2x2 mesh
	                        __           __    __
	first row ->   |  ->   |/  + |  ->  |/  + |/ |  -> end first row
                  __ __       __ __        __ __
	second row-> |/ |/ | ->  |/ |/_|  ->  |/_|/_| -> end second row, and done~
    	               |        |/_|      |/_|/_|
              __                    __
	building |/   in order of  /  ,    ,  |
	          __                          __
	building |/_  in order of  _  ,  /  ,    ,  |
*/
	
	///////////////////
	//the creation loop
	///////////////////
	for (int r = rows; r > 0; r--){
		/////////////////
		//begin a new row
		/////////////////
		std::cout << "" << std::endl;
		//draws +x-most edge
		memE.push_back(new Edge()); //the +x-most edge
		if (r == rows){ memV.push_back(new Vertex()); } //the far vertex
		memV.push_back(new Vertex()); //the near vertex
		//in memV: [far, near]

		//adding coordinates to the verticies
		if (r == rows){ 
			memV[memV.size() - 2]->setCoords(vec4(mx, 0, (mz - (uHeight*(rows - r))), 1)); 
		} //far
		memV[memV.size()-1]->setCoords(vec4(mx, 0, (mz-(uHeight*(rows-(r-1)))), 1)); //near

		//adding the verticies to the edge
		if (r == rows){ memE[memE.size() - 1]->setNEVertex(memV[memV.size() - 2]);}
		memE[memE.size()-1]->setSWVertex(memV[memV.size()-1]);

		//adding the edge to the verticies
		if (r == rows){ memV[memV.size() - 2]->addEdge(memE[memE.size() - 1]); }
		memV[memV.size()-1]->addEdge(memE[memE.size()-1]);

		//teathering the new edge to the prevnear +x vertex
		if (r != rows){
			memE[memE.size() - 1]->setNEVertex(memV[1]);
			memV[1]->addEdge(memE[memE.size() - 1]);
		}

		//an empty face marks the end of the mesh
		memE[memE.size() - 1]->setNEFace(new Face());

		//used to sort verticies in the mid-part of the mesh
		int shift = 0;

		//////////////
		//draw the row 
		//////////////
		for (int c = cols; c > 0; c--){
			//the r number determines what we make
			//the c number tells us which data will be ready to store (in the main vectors)
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
			if (r == rows){//if we are in the first row
				/*        __
				  make:  |/  , adding on to the previous loop-step's drawing
				*/
/*---------------------------------------------------------------------------------*/
				if (c != 1){//if we are in a first or middle column
				//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;

					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]

					memV.push_back(new Vertex()); //the far vertex - memV[memV.size()-2]
					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the NEface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 2]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - r))), 1)); //far
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near
					
				//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setSWVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 1]);//tilt<-NEface
					memE[memE.size() - 2]->setNEVertex(memV[memV.size() - 2]);//top<-far
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 1]);//top<-NEface
					memE[memE.size() - 1]->setNEVertex(memV[memV.size() - 2]);//side<-far
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 1]);//side<-NEface

					//adding to the verticies
					memV[memV.size() - 2]->addEdge(memE[memE.size() - 2]);//far<-top
					memV[memV.size() - 2]->addEdge(memE[memE.size() - 1]);//far<-side
					memV[memV.size() - 2]->addFace(memF[memF.size() - 1]);//far<-NEface
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 1]);//near<-NEface

					//adding to the face
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 2]);//NEface<-far
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 1]);//NEface<-near
		
				//swap information with previously made data///////////////////////////
					//in memV [..., prevFar, prevNear, far, near]
					//in memE [..., prevE, tilt, top, side]
					//in memF [..., NEface]
					//adding to the edges
					memE[memE.size() - 3]->setNEVertex(memV[memV.size() - 4]);//tilt<-prevfar
					memE[memE.size() - 2]->setSWVertex(memV[memV.size() - 4]);//top<-prevfar
	
					//adding to the verticies
					memV[memV.size() - 4]->addEdge(memE[memE.size() - 3]);//prevfar<-tilt
					memV[memV.size() - 4]->addEdge(memE[memE.size() - 2]);//prevfar<-top
					memV[memV.size() - 4]->addFace(memF[memF.size() - 1]);//prevfar<-NEface
				
					//adding to the face
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 4]);//NEface<-prevfar
			
				//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->setNEFace(new Face());//top<-EMPTY FACE, signaling mesh end
					memE[memE.size() - 2]->nowReady();//top is ready
					memF[memF.size() - 1]->nowReady();//NEface is ready
				}
/*---------------------------------------------------------------------------------------------*/
				else{//if we are in last column
				//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;
					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]

					memV.push_back(new Vertex()); //the far vertex - memV[memV.size()-2]
					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the NEface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 2]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - r))), 1)); //far
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near

				//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setSWVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 1]);//tilt<-NEface
					memE[memE.size() - 2]->setNEVertex(memV[memV.size() - 2]);//top<-far
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 1]);//top<-NEface
					memE[memE.size() - 1]->setNEVertex(memV[memV.size() - 2]);//side<-far
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 1]);//side<-NEface

					//adding to the verticies
					memV[memV.size() - 2]->addEdge(memE[memE.size() - 2]);//far<-top
					memV[memV.size() - 2]->addEdge(memE[memE.size() - 1]);//far<-side
					memV[memV.size() - 2]->addFace(memF[memF.size() - 1]);//far<-NEface
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 1]);//near<-NEface

					//adding to the face
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 2]);//NEface<-far
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 1]);//NEface<-near

				//swap information with previously made data///////////////////////////
					//in memV [..., prevFar, prevNear, far, near]
					//in memE [..., prevE, tilt, top, side]
					//in memF [..., NEface]
					//adding to the edges
					memE[memE.size() - 3]->setNEVertex(memV[memV.size() - 4]);//tilt<-prevfar
					memE[memE.size() - 2]->setSWVertex(memV[memV.size() - 4]);//top<-prevfar

					//adding to the verticies
					memV[memV.size() - 4]->addEdge(memE[memE.size() - 3]);//prevfar<-tilt
					memV[memV.size() - 4]->addEdge(memE[memE.size() - 2]);//prevfar<-top
					memV[memV.size() - 4]->addFace(memF[memF.size() - 1]);//prevfar<-NEface

					//adding to the face
					memF[memF.size() - 1]->addVertex(memV[memV.size() - 4]);//NEface<-prevfar

				//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->setNEFace(new Face());//top<-EMPTY FACE, signaling mesh end
					memE[memE.size() - 2]->nowReady();//top is ready
					memE[memE.size() - 1]->setSWFace(new Face());//side<-EMPTY FACE, signaling mesh end
					memE[memE.size() - 1]->nowReady();//side is now ready
					memV[memV.size() - 2]->nowReady();//far is now ready
					memF[memF.size() - 1]->nowReady();//NEface is ready
				}
			}
//////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
			else if (r == 1){//if we are in the last row
				//        __
				//  make:  |/_
				//
/*------------------------------------------------------------------------------*/
				if (c != 1){//if we are in a first or middle column
				//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;
					memE.push_back(new Edge());// bottom - memE[memE.size()-4]
					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]
		
					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the Bface - memF[memF.size()-3]
					memF.push_back(new Face()); //the NEface - memF[memF.size()-2]
					memF.push_back(new Face()); //the SWface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near
		
				//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setSWVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 2]);//tilt<-NEface
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 3]);//tilt<-Bface
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 2]);//top<-NEface
					memE[memE.size() - 2]->setNEFace(memF[memF.size() - 1]);//top<-SWface
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 2]);//side<-NEface
					memE[memE.size() - 4]->setNEFace(memF[memF.size() - 3]);//bottom<-Bface
					memE[memE.size() - 4]->setSWVertex(memV[memV.size() - 1]);//bottom<-near

					//adding to the vertex
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 2]);//near<-NEface
					memV[memV.size() - 1]->addFace(memF[memF.size() - 3]);//near<-Bface
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 4]);//near<-bottom

					//adding to the faces
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 2]->addVertex(memV[memV.size() - 1]);//NEface<-near
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//SWface<-top
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 3]);//Bface<-tilt
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 4]);//Bface<-bottom
					memF[memF.size() - 3]->addVertex(memV[memV.size() - 1]);//Bface<-near

				//swap information with previously made data///////////////////////////
					//in memV [(cols-c)farR, (+1)farL, ..., (+cols)nearR, (+cols+1)nearL,..., +x-immediate, near]
					//in memE [(2*(cols-c))pcsideR, (+1)pctilt, (+2)pcsideL,..., prevE, tilt, top, side]
					//in memF [NEface, SWface]

					//adding to the edges
					memE[2 * (cols - c)]->setSWFace(memF[memF.size() - 1]);//pcsideR<-SWface
					memE[(2 * (cols - c)) + 1]->setSWFace(memF[memF.size() - 1]);//pctilt<-SWface
					memE[memE.size() - 3]->setNEVertex(memV[(cols - c) + cols]);//tilt<-pcnearR
					memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + cols]);//top<-pcnearR
					memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + cols + 1]);//top<-pcnearL
					memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + cols + 1]);//side<-pcnearL
					memE[memE.size() - 5]->setSWFace(memF[memF.size() - 3]);//prevE<-Bface
					memE[memE.size() - 4]->setNEVertex(memV[memV.size()-2]);//bottom<-prevV

					//adding to the verticies
					memV[(cols - c) + cols]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
					memV[(cols - c) + cols]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 3]);//pcnearR<-Bface
					memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
					memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
					memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
					memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
					memV[(cols - c)]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					memV[memV.size() - 2]->addFace(memF[memF.size() - 3]);//prevV<-Bface

					//adding to the faces
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c))]);//SWface<-pcsideR
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c)) + 1]);//SWface<-pctilt
					memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols + 1]);//NEface<-pcnearL
					memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols]);//NEface<-pcnearR
					memF[memF.size() - 1]->addVertex(memV[(cols - c)]);//SWface<-pcfarR
					memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols]);//SWface<-pcnearR
					memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols + 1]);//SWface<-pcnearL
					memF[memF.size() - 3]->addVertex(memV[(cols - c) + cols]);//Bface<-pcnearR
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 5]);//Bface<-prevE
					memF[memF.size() - 3]->addVertex(memV[memV.size() - 2]);//Bface<-prevV

				//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->nowReady();//top is ready
					memE[(2 * (cols - c))]->nowReady();//pcsideR is ready
					memE[(2 * (cols - c)) + 1]->nowReady();//pctilt is ready
					memF[memF.size() - 1]->nowReady();//SWface is ready
					memF[memF.size() - 2]->nowReady();//NEface is ready
					memF[memF.size() - 3]->nowReady();//NEface is ready
					memV[(cols - c)]->nowReady();//pcfarR is ready
					memV[(cols - c) + cols]->nowReady();//pcnearR is ready
					memE[memE.size() - 3]->nowReady();//tilt is ready
					memE[memE.size() - 5]->nowReady();//prevE is ready
					memV[memV.size() - 2]->nowReady();//prevV is ready
					memE[memE.size() - 4]->nowReady();//bottom is ready
				}
/*-----------------------------------------------------------------------------------------------*/
				else{//if we are in last column
				//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;
					memE.push_back(new Edge());// bottom - memE[memE.size()-4]
					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]

					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the Bface - memF[memF.size()-3]
					memF.push_back(new Face()); //the NEface - memF[memF.size()-2]
					memF.push_back(new Face()); //the SWface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near

				//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setSWVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setSWFace(memF[memF.size() - 2]);//tilt<-NEface
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 3]);//tilt<-Bface
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 2]);//top<-NEface
					memE[memE.size() - 2]->setNEFace(memF[memF.size() - 1]);//top<-SWface
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 2]);//side<-NEface
					memE[memE.size() - 4]->setNEFace(memF[memF.size() - 3]);//bottom<-Bface
					memE[memE.size() - 4]->setSWVertex(memV[memV.size() - 1]);//bottom<-near

					//adding to the vertex
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 2]);//near<-NEface
					memV[memV.size() - 1]->addFace(memF[memF.size() - 3]);//near<-Bface
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 4]);//near<-bottom

					//adding to the faces
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 2]->addVertex(memV[memV.size() - 1]);//NEface<-near
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//SWface<-top
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 3]);//Bface<-tilt
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 4]);//Bface<-bottom
					memF[memF.size() - 3]->addVertex(memV[memV.size() - 1]);//Bface<-near

				//swap information with previously made data///////////////////////////
					//in memV [(cols-c)farR, (+1)farL, ..., (+cols)nearR, (+cols+1)nearL,..., +x-immediate, near]
					//in memE [(2*(cols-c))pcsideR, (+1)pctilt, (+2)pcsideL,..., prevE, tilt, top, side]
					//in memF [NEface, SWface]

					//adding to the edges
					memE[2 * (cols - c)]->setSWFace(memF[memF.size() - 1]);//pcsideR<-SWface
					memE[(2 * (cols - c)) + 1]->setSWFace(memF[memF.size() - 1]);//pctilt<-SWface
					memE[memE.size() - 3]->setNEVertex(memV[(cols - c) + cols]);//tilt<-pcnearR
					memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + cols]);//top<-pcnearR
					memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + cols + 1]);//top<-pcnearL
					memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + cols + 1]);//side<-pcnearL
					memE[memE.size() - 5]->setSWFace(memF[memF.size() - 3]);//prevE<-Bface
					memE[memE.size() - 4]->setNEVertex(memV[memV.size() - 2]);//bottom<-prevV

					//adding to the verticies
					memV[(cols - c) + cols]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
					memV[(cols - c) + cols]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
					memV[(cols - c) + cols]->addFace(memF[memF.size() - 3]);//pcnearR<-Bface
					memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
					memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
					memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
					memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
					memV[(cols - c)]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					memV[memV.size() - 2]->addFace(memF[memF.size() - 3]);//prevV<-Bface

					//adding to the faces
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c))]);//SWface<-pcsideR
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c)) + 1]);//SWface<-pctilt
					memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols + 1]);//NEface<-pcnearL
					memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols]);//NEface<-pcnearR
					memF[memF.size() - 1]->addVertex(memV[(cols - c)]);//SWface<-pcfarR
					memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols]);//SWface<-pcnearR
					memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols + 1]);//SWface<-pcnearL
					memF[memF.size() - 3]->addVertex(memV[(cols - c) + cols]);//Bface<-pcnearR
					memF[memF.size() - 3]->addEdge(memE[memE.size() - 5]);//Bface<-prevE
					memF[memF.size() - 3]->addVertex(memV[memV.size() - 2]);//Bface<-prevV

				//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->nowReady();//top is ready
					memE[(2 * (cols - c))]->nowReady();//pcsideR is ready
					memE[(2 * (cols - c)) + 1]->nowReady();//pctilt is ready
					memF[memF.size() - 1]->nowReady();//SWface is ready
					memF[memF.size() - 2]->nowReady();//NEface is ready
					memF[memF.size() - 3]->nowReady();//NEface is ready
					memV[(cols - c)]->nowReady();//pcfarR is ready
					memV[(cols - c) + cols]->nowReady();//pcnearR is ready
					memE[memE.size() - 3]->nowReady();//tilt is ready
					memE[memE.size() - 5]->nowReady();//prevE is ready
					memV[memV.size() - 2]->nowReady();//prevV is ready
					memE[memE.size() - 4]->nowReady();//bottom is ready
					memV[memV.size() - 1]->nowReady();//near is ready
					memE[memE.size() - 1]->nowReady();//side is ready
					memV[(cols - c) + cols + 1]->nowReady();//pcnearL is ready
				}
			}
///////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
			else {//if we are in one of the middle rows
				//         __
				// make:   |/  , adding on to the previous loop-step's drawing
				//
/*------------------------------------------------------------------------------------*/
				if (c != 1){//if we are in a first or middle column
					//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;
					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]

					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the NEface - memF[memF.size()-2]
					memF.push_back(new Face()); //the SWface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near

					//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setNEVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 2]);//tilt<-NEface
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 2]);//top<-NEface
					memE[memE.size() - 2]->setNEFace(memF[memF.size() - 1]);//top<-SWface
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 2]);//side<-NEface

					//adding to the vertex
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 2]);//near<-NEface

					//adding to the faces
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 2]->addVertex(memV[memV.size() - 1]);//NEface<-near
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//SWface<-top

					//swap information with previously made data///////////////////////////
					//in memE [(2*(cols-c))pcsideR, (+1)pctilt, (+2)pcsideL,..., prevE, tilt, top, side]
					//in memF [NEface, SWface]
					//adding to the edges
					memE[2 * (cols - c)]->setSWFace(memF[memF.size() - 1]);//pcsideR<-SWface
					memE[(2 * (cols - c)) + 1]->setSWFace(memF[memF.size() - 1]);//pctilt<-SWface
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memE[memE.size() - 3]->setSWVertex(memV[(cols - c) + 1 + shift]);//tilt<-pcnearR
						memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + 1 + shift]);//top<-pcnearR
						memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + 3 + shift]);//top<-pcnearL
						memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + 3 + shift]);//side<-pcnearL
					}
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memE[memE.size() - 3]->setSWVertex(memV[(cols - c) + cols]);//tilt<-pcnearR
						memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + cols]);//top<-pcnearR
						memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + cols + 1]);//top<-pcnearL
						memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + cols + 1]);//side<-pcnearL
					}


					//adding to the verticies
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memV[(cols - c) + 1 + shift]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
						memV[(cols - c) + 1 + shift]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
						memV[(cols - c) + 1 + shift]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
						memV[(cols - c) + 1 + shift]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
						memV[(cols - c) + 3 + shift]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
						memV[(cols - c) + 3 + shift]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
						memV[(cols - c) + 3 + shift]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
						memV[(cols - c) + 3 + shift]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
						memV[(cols - c) + shift]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					}
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memV[(cols - c) + cols]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
						memV[(cols - c) + cols]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
						memV[(cols - c) + cols]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
						memV[(cols - c) + cols]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
						memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
						memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
						memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
						memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
						memV[(cols - c)]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					}


					//adding to the faces
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c))]);//SWface<-pcsideR
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c)) + 1]);//SWface<-pctilt
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + 3 + shift]);//NEface<-pcnearL
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + 1 + shift]);//NEface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + shift]);//SWface<-pcfarR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + 1 + shift]);//SWface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + 3 + shift]);//SWface<-pcnearL
					}
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols + 1]);//NEface<-pcnearL
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols]);//NEface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c)]);//SWface<-pcfarR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols]);//SWface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols + 1]);//SWface<-pcnearL
					}

					//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->nowReady();//top is ready
					memE[(2 * (cols - c))]->nowReady();//pcsideR is ready
					memE[(2 * (cols - c)) + 1]->nowReady();//pctilt is ready
					memF[memF.size() - 1]->nowReady();//SWface is ready
					memF[memF.size() - 2]->nowReady();//NEface is ready
					if (r == (rows - 1)){ memV[(cols - c) + shift]->nowReady(); } //pcfarR is ready
					else{ memV[(cols - c)]->nowReady(); }//pcfarR ir ready
					shift++;
				}
/*-----------------------------------------------------------------------------------------------------*/
				else {//if we are in last column
				//make the new items/////////////////////////////////////////
					std::cout << "-----------------------------r and c " << r << " " << c << std::endl;
					memE.push_back(new Edge());// tilt - memE[memE.size()-3]
					memE.push_back(new Edge());// top - memE[memE.size()-2]
					memE.push_back(new Edge());// side - memE[memE.size()-1]

					memV.push_back(new Vertex()); //the near vertex - memV[memV.size()-1]

					memF.push_back(new Face()); //the NEface - memF[memF.size()-2]
					memF.push_back(new Face()); //the SWface - memF[memF.size()-1]

					//put coordinates in the verticies
					memV[memV.size() - 1]->setCoords(vec4((mx - (uWidth*(cols - (c - 1)))), 0, (mz - (uHeight*(rows - (r - 1)))), 1)); //near

				//store new data in each other//////////////////////////////////////////

					//adding to the edges
					memE[memE.size() - 3]->setNEVertex(memV[memV.size() - 1]);//tilt<-near
					memE[memE.size() - 3]->setNEFace(memF[memF.size() - 2]);//tilt<-NEface
					memE[memE.size() - 2]->setSWFace(memF[memF.size() - 2]);//top<-NEface
					memE[memE.size() - 2]->setNEFace(memF[memF.size() - 1]);//top<-SWface
					memE[memE.size() - 1]->setSWVertex(memV[memV.size() - 1]);//side<-near
					memE[memE.size() - 1]->setNEFace(memF[memF.size() - 2]);//side<-NEface

					//adding to the vertex
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 3]);//near<-tilt
					memV[memV.size() - 1]->addEdge(memE[memE.size() - 1]);//near<-side
					memV[memV.size() - 1]->addFace(memF[memF.size() - 2]);//near<-NEface

					//adding to the faces
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 3]);//NEface<-tilt 
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 2]);//NEface<-top
					memF[memF.size() - 2]->addEdge(memE[memE.size() - 1]);//NEface<-side
					memF[memF.size() - 2]->addVertex(memV[memV.size() - 1]);//NEface<-near
					memF[memF.size() - 1]->addEdge(memE[memE.size() - 2]);//SWface<-top

				//swap information with previously made data///////////////////////////
					//in memE [(2*(cols-c))pcsideR, (+1)pctilt, (+2)pcsideL,..., prevE, tilt, top, side]
					//in memF [NEface, SWface]
					//adding to the edges
					memE[2 * (cols - c)]->setSWFace(memF[memF.size() - 1]);//pcsideR<-SWface
					memE[(2 * (cols - c)) + 1]->setSWFace(memF[memF.size() - 1]);//pctilt<-SWface
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memE[memE.size() - 3]->setSWVertex(memV[(cols - c) + 1 + shift]);//tilt<-pcnearR
						memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + 1 + shift]);//top<-pcnearR
						memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + shift + 2]);//top<-pcnearL
						memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + shift + 2]);//side<-pcnearL
					}
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memE[memE.size() - 3]->setSWVertex(memV[(cols - c) + cols]);//tilt<-pcnearR
						memE[memE.size() - 2]->setNEVertex(memV[(cols - c) + cols]);//top<-pcnearR
						memE[memE.size() - 2]->setSWVertex(memV[(cols - c) + cols + 1]);//top<-pcnearL
						memE[memE.size() - 1]->setNEVertex(memV[(cols - c) + cols + 1]);//side<-pcnearL
					}


					//adding to the verticies
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memV[(cols - c) + 1 + shift]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
						memV[(cols - c) + 1 + shift]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
						memV[(cols - c) + 1 + shift]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
						memV[(cols - c) + 1 + shift]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
						memV[(cols - c) + shift + 2]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
						memV[(cols - c) + shift + 2]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
						memV[(cols - c) + shift + 2]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
						memV[(cols - c) + shift + 2]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
						memV[(cols - c) + shift]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					} 
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memV[(cols - c) + cols]->addEdge(memE[memE.size() - 3]);//pcnearR<-tilt
						memV[(cols - c) + cols]->addEdge(memE[memE.size() - 2]);//pcnearR<-top
						memV[(cols - c) + cols]->addFace(memF[memF.size() - 1]);//pcnearR<-SWface
						memV[(cols - c) + cols]->addFace(memF[memF.size() - 2]);//pcnearR<-NEface
						memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 2]);//pcnearL<-top
						memV[(cols - c) + cols + 1]->addEdge(memE[memE.size() - 1]);//pcnearL<-side
						memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 1]);//pcnearL<-SWface
						memV[(cols - c) + cols + 1]->addFace(memF[memF.size() - 2]);//pcnearL<-NEface
						memV[(cols - c)]->addFace(memF[memF.size() - 1]);//pcfarR<-SWface
					}


					//adding to the faces
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c))]);//SWface<-pcsideR
					memF[memF.size() - 1]->addEdge(memE[(2 * (cols - c)) + 1]);//SWface<-pctilt
					if (r == (rows - 1)){//the vertex labeling pattern shifts after the first row
						//in memV [(cols-c)farR, (+1)nearR, (+2)farL, (+3)nearL,..., +x-immediate, near]
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + shift + 2]);//NEface<-pcnearL
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + 1 + shift]);//NEface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + shift]);//SWface<-pcfarR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + 1 + shift]);//SWface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + shift + 2]);//SWface<-pcnearL
					}
					else{
						//in memV [(cols-c)farR, (+1)farL, ..., (+cols+1)nearR, (+cols+2)nearL,..., +x-immediate, near]
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols + 1]);//NEface<-pcnearL
						memF[memF.size() - 2]->addVertex(memV[(cols - c) + cols]);//NEface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c)]);//SWface<-pcfarR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols]);//SWface<-pcnearR
						memF[memF.size() - 1]->addVertex(memV[(cols - c) + cols + 1]);//SWface<-pcnearL
					}

				//signal which data are now ready to be stored/////////////////////////
					memE[memE.size() - 2]->nowReady();//top is ready
					memE[memE.size() - 1]->setSWFace(new Face());//side<-EMPTY FACE, signaling mesh end
					memE[memE.size() - 1]->nowReady();//side is now ready
					memE[(2 * (cols - c))]->nowReady();//pcsideR is ready
					memE[(2 * (cols - c)) + 1]->nowReady();//pctilt is ready
					memF[memF.size() - 1]->nowReady();//SWface is ready
					memF[memF.size() - 2]->nowReady();//NEface is ready
					if (r == (rows - 1)){ 
						memV[(cols - c) + shift]->nowReady();//pcfarR is ready
						memV[(cols - c) + shift + 2]->nowReady(); //pcnearL is ready
					} 
					else{ 
						memV[(cols - c)]->nowReady();//pcfarR is ready
						memV[(cols - c) + cols + 1]->nowReady(); //pcnearL is ready
					}
				}	
			}
		}
	////////////////////////////////////////////////////////////////
	//end the row
	///////////////////////////////////////////////////////////////
		//Pop and store any verticies who have all of their neighbors(edges and faces) saved
		for (int vNum = 0; vNum < (int)memV.size(); vNum++){
			if (memV[vNum]->isReady()){
				verticies.push_back(memV[vNum]);
				memV.erase(memV.begin()+vNum);
				vNum--;
			}
		}
		//Pop and store any edges who have all of their neighbors(verticies and faces) saved
		for (int eNum = 0; eNum < (int)memE.size(); eNum++){
			if (memE[eNum]->isReady()){
				edges.push_back(memE[eNum]);
				memE.erase(memE.begin() + eNum);
				eNum--;
			}
		}
		//Pop and store any faces who have all of their neighbors(edges and verticies) saved
		for (int fNum = 0; fNum < (int)memF.size(); fNum++){
			if (memF[fNum]->isReady()){
				faces.push_back(memF[fNum]);
				memF.erase(memF.begin() + fNum);
				fNum--;
			}
		}
	}
	//set the selected vertex as the first vertex
	selectedVertex = verticies[0];
}

void MeshDisplay::fractalize(){
	//maybe make it similar to newMesh? go by row instead of face
	//list of quads?
		//each quad contains a list of verticies, edges, and faces that make it.
	for (Face* f : faces){
		/*
		for(Edges* e : f->getEdges()){
			
		}
		average the values between the two vericies, the randomly change the y value between +-1 to +-5.
		*/
	}//RESET SELECTED VERTEX?
}

//////////////////////////////////////////////////////////////////////////////
//SELECTED VERTEX 
//////////////////////////////////////////////////////////////////////////////
void MeshDisplay::setVertexHeight(float h){
	vec4 coor = selectedVertex->getCoords();
	vec4 v = vec4(coor[0], h, coor[2], 1);
	selectedVertex->setCoords(v);
}
void MeshDisplay::selectNext(){
	//if the current vertex is the last vertex, it will wrap around to the first vertex
	if (selectedIndex == (verticies.size() - 1)){
		selectedIndex = 0;
		selectedVertex = verticies[0];
	}
	else{
		selectedIndex += 1;
		selectedVertex = verticies[selectedIndex];
	}
}
void MeshDisplay::selectPrev(){
	//if the current vertex is the first vertex, it will wrap around to the last vertex
	if (selectedIndex == 0){
		selectedIndex = 0;
		selectedVertex = verticies[(verticies.size() - 1)];
	}
	else{
		selectedIndex -= 1;
		selectedVertex = verticies[selectedIndex];
	}
}
/*
void toggleWireframe(){ wireframe = !wireframe; }
Vertex* getSelectedVertex(){ return selectedVertex; }
void setSelectedVertex(Vertex* v){ selectedVertex = v; }
void setSnowcapHeight(float f){ snowcapHeight = f; }
std::vector<Edge*> getEdges(){ return edges; }
std::vector<Vertex*> getVerticies(){ return verticies; }
std::vector<Face*> getFaces(){ return faces; }
};
*/