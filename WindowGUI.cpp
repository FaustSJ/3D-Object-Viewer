#include "WindowGUI.h"

/*
Fl_Button* createMeshButton;
Fl_Button* toggleWireframeButton;
Fl_Button* topViewButton;
Fl_Button* sideViewButton;
Fl_Button* nextVertexButton;
Fl_Button* prevVertexButton;
//	Fl_Button* selectVertexButton;
Fl_Button* fractalizeButton;
Fl_Slider* snowcapSlider;
Fl_Slider* vertexHeightSlider;
Fl_Slider* red;
Fl_Slider* blue;
Fl_Slider* green;
MeshDisplay* mView;
//	Fl_Float_Input* xVal;
//	Fl_Float_Input* yVal;
//	Fl_Float_Input* zVal;
Fl_Float_Input* numRows;
Fl_Float_Input* numCols;
Fl_Float_Input* unitWidth;
Fl_Float_Input* unitHeight;
Fl_Float_Input* subdivisionsInput;
Fl_Text_Display* snowcapHeightLabel;
Fl_Text_Display* meshColorLabel;
Fl_Text_Display* viewsLabel;
Fl_Text_Display* vertexHeightLabel;
Fl_Text_Display* numOfSubdivisionsLabel;
Fl_Text_Display* selectVertexLabel;
*/

WindowGUI::WindowGUI(int x, int y, int w, int h, char* c) : Fl_Window(x, y, w, h, c){
	//the buttons
	createMeshButton = new Fl_Button(585, 84, 100, 30, "Create Mesh");
	createMeshButton->callback(this->createMeshButtonCB, this);
	toggleWireframeButton = new Fl_Button(620, 255, 125, 30, "Toggle Wireframe");
	toggleWireframeButton->callback(this->toggleWireframeButtonCB, this);
	topViewButton = new Fl_Button(525, 290, 60, 30, "Top");
	topViewButton->callback(this->topViewButtonCB, this);
	sideViewButton = new Fl_Button(525, 255, 60, 30, "Side");
	sideViewButton->callback(this->sideViewButtonCB, this);
//	selectVertexButton = new Fl_Button(519, 366, 100, 30, "Select Vertex");
//	selectVertexButton->callback(this->selectVertexButtonCB, this);
//	fractalizeButton = new Fl_Button(629, 280, 80, 25, "Fractalize!");
//	fractalizeButton->callback(this->fractalizeButtonCB, this);
	nextVertexButton = new Fl_Button(565, 355, 40, 30, "->");
	nextVertexButton->callback(this->nextVertexButtonCB, this);
	prevVertexButton = new Fl_Button(525, 355, 40, 30, "<-");
	prevVertexButton->callback(this->prevVertexButtonCB, this);

	//the sliders
	snowcapSlider = new Fl_Slider(520, 476, 230, 24);
	snowcapSlider->type(1);
	snowcapSlider->range(0, 20);
	snowcapSlider->step(0.2);
	snowcapSlider->value(20);
	snowcapSlider->callback(this->snowcapSliderCB, this);
	vertexHeightSlider = new Fl_Slider(520, 426, 230, 24);
	vertexHeightSlider->type(1);
	vertexHeightSlider->range(-20, 20);
	vertexHeightSlider->step(0.2);
	vertexHeightSlider->value(0);
	vertexHeightSlider->callback(this->vertexHeightSliderCB, this);
	red = new Fl_Slider(546, 153, 189, 20);
	red->type(1);
	red->range(0, 1);
	red->step(0.1);
	red->value(1);
	red->color(FL_RED);
	red->callback(this->redCB, this);
	green = new Fl_Slider(546, 173, 189, 20);
	green->type(1);
	green->range(0, 1);
	green->step(0.1);
	green->value(1);
	green->color((Fl_Color)62);
	green->callback(this->greenCB, this);
	blue = new Fl_Slider(546, 193, 189, 20);
	blue->type(1);
	blue->range(0, 1);
	blue->step(0.1);
	blue->value(1);
	blue->color((Fl_Color)186);
	blue->callback(this->blueCB, this);

	//the input boxes
//	xVal = new Fl_Float_Input(522, 341, 30, 24);
//	yVal = new Fl_Float_Input(552, 341, 30, 24);
//	zVal = new Fl_Float_Input(582, 341, 30, 24);
	numRows = new Fl_Float_Input(575, 16, 35, 28, "Rows");
	numCols = new Fl_Float_Input(575, 44, 35, 28, "Cols");
	unitWidth = new Fl_Float_Input(687, 15, 35, 28, "Unit Width");
	unitHeight = new Fl_Float_Input(687, 43, 35, 28, "Unit Height");
	subdivisionsInput = new Fl_Float_Input(670, 336, 35, 28);

	//the labels
	snowcapHeightLabel = new Fl_Text_Display(510, 472, 260, 1, "Snowcap Height");
	meshColorLabel = new Fl_Text_Display(545, 151, 190, 1, "Mesh Color");
	viewsLabel = new Fl_Text_Display(505, 250, 95, 1, "Views");
	vertexHeightLabel = new Fl_Text_Display(510, 422, 260, 1, "Vertex Height");
	numOfSubdivisionsLabel = new Fl_Text_Display(625, 331, 125, 1, "No. of Subdivisions");
	selectVertexLabel = new Fl_Text_Display(500, 351, 130, 1, "Select Vertex");

	//the display window
	mView = new MeshDisplay(10, 9, 500, 500);
	mView->setColor(1, 0, 1);
		//adjust the sliders
	green->value(0);
}

WindowGUI::~WindowGUI(){
	delete(createMeshButton);
	delete(toggleWireframeButton);
	delete(topViewButton);
	delete(sideViewButton);
	delete(nextVertexButton);
	delete(prevVertexButton);
//	delete(fractalizeButton);
//	delete(selectVertexButton);
	delete(snowcapSlider);
	delete(vertexHeightSlider);
	delete(red);
	delete(blue);
	delete(green);
	delete(mView);
//	delete(xVal);
//	delete(yVal);
//	delete(zVal);
	delete(numRows);
	delete(numCols);
	delete(unitWidth);
	delete(unitHeight);
	delete(subdivisionsInput);
	delete(snowcapHeightLabel);
	delete(meshColorLabel);
	delete(viewsLabel);
	delete(vertexHeightLabel);
	delete(numOfSubdivisionsLabel);
	delete(selectVertexLabel);

	createMeshButton = NULL;
	toggleWireframeButton = NULL;
	topViewButton = NULL;
	sideViewButton = NULL;
//	selectVertexButton = NULL;

//	fractalizeButton = NULL;
	nextVertexButton = NULL;
	prevVertexButton = NULL;
	snowcapSlider = NULL;
	vertexHeightSlider = NULL;
	red = NULL;
	blue = NULL;
	green = NULL;
	mView = NULL;
//	xVal = NULL;
//	yVal = NULL;
//	zVal = NULL;
	numRows = NULL;
	numCols = NULL;
	unitWidth = NULL;
	unitHeight = NULL;
	subdivisionsInput = NULL;
	snowcapHeightLabel = NULL;
	meshColorLabel = NULL;
	viewsLabel = NULL;
	vertexHeightLabel = NULL;
	numOfSubdivisionsLabel = NULL;
	selectVertexLabel = NULL;
}

void WindowGUI::createMeshButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	//first grabs the values from user input
	int r = (int)*(win->numRows->value()) - 48;
	int c = (int)*(win->numCols->value()) - 48;
	float uWidth = (float)*(win->unitWidth->value()) - 48;
	float uHeight = (float)*(win->unitHeight->value()) - 48;

	if (((r*uWidth)<30) && ((c*uHeight)<30)){
		//then make the mesh then redraw
		win->mView->newMesh(uWidth, uHeight, r, c);
		win->mView->redraw();
	}
	else{
		std::cout << "Please make sure the overall width and height of the mesh you are trying to make is less than 30!" << std::endl;
	}
	
}
void WindowGUI::toggleWireframeButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->toggleWireframe();
	win->mView->redraw();
}
void WindowGUI::topViewButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->topView();
	win->mView->redraw();
}
void WindowGUI::sideViewButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->sideView();
	win->mView->redraw();
}

void WindowGUI::nextVertexButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->selectNext();
	win->mView->redraw();
}
void WindowGUI::prevVertexButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->selectPrev();
	win->mView->redraw();
}

void WindowGUI::fractalizeButtonCB(Fl_Widget *w, void *parm){
	WindowGUI* win = (WindowGUI*)parm;
	
	//make sure the number of subdivisions is 2 or greater.
	int n = (int)win->subdivisionsInput->value();
	if (n > 2){ 
		//reset the mesh so that the fractals start fresh
		win->mView->meshReset();
		//then subdivide however many times the user wanted!
		for (int i = n; i < 0; i--){
			win->mView->fractalize();
		}
		Vertex* v = win->mView->getSelectedVertex();
	}
	else{
		std::cout << "No fractalization was done." << std::endl;
	}
}

void WindowGUI::snowcapSliderCB(Fl_Widget *w, void *parm){
	Fl_Slider* snowLevel = (Fl_Slider*)w;
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->setSnowcapHeight((float)(snowLevel->value()));
	win->mView->redraw();
}
void WindowGUI::vertexHeightSliderCB(Fl_Widget *w, void *parm){
	Fl_Slider* vertHeight = (Fl_Slider*)w;
	WindowGUI* win = (WindowGUI*)parm;
	win->mView->setVertexHeight((float)(vertHeight->value()));
	win->mView->redraw();
}
void WindowGUI::redCB(Fl_Widget *w, void *param){
	Fl_Slider* red = (Fl_Slider*)w;
	WindowGUI* win = (WindowGUI*)param;
	win->mView->setRed((double)red->value());
	win->mView->redraw();
}
void WindowGUI::blueCB(Fl_Widget *w, void *param){
	Fl_Slider* blue = (Fl_Slider*)w;
	WindowGUI* win = (WindowGUI*)param;
	win->mView->setBlue((double)blue->value());
	win->mView->redraw();
}
void WindowGUI::greenCB(Fl_Widget *w, void *param){
	Fl_Slider* green = (Fl_Slider*)w;
	WindowGUI* win = (WindowGUI*)param;
	win->mView->setGreen((double)green->value());
	win->mView->redraw();
}

/*
void WindowGUI::selectVertexButtonCB(Fl_Widget *w, void *parm){
WindowGUI* win = (WindowGUI*)parm;
//get the values
float x = (float)*(win->xVal->value()) - 48;
float y = (float)*(win->yVal->value()) - 48;
float z = (float)*(win->zVal->value()) - 48;
//make a coordinate set
vec4 coor = vec4(x, y, z, 1);
//go through each vertex and find the closest one/////////////////
for (Vertex* v : win->mView->getVerticies()){
if (v->getCoords() == coor){
win->mView->setSelectedVertex(v);
}
}
//set height slider

}
*/
