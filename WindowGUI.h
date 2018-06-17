#ifndef WINDOWGUI_H
#define WINDOWGUI_H
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Slider.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_TREE.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Color_Chooser.H>
#include <iostream>
#include "MeshDisplay.h"
#include "camera.h"

class WindowGUI : public Fl_Window
{
private:
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

	static void createMeshButtonCB(Fl_Widget *w, void *parm);
	static void toggleWireframeButtonCB(Fl_Widget *w, void *parm);
	static void topViewButtonCB(Fl_Widget *w, void *parm);
	static void sideViewButtonCB(Fl_Widget *w, void *parm);
	static void fractalizeButtonCB(Fl_Widget *w, void *parm);
	static void snowcapSliderCB(Fl_Widget *w, void *parm);
	static void vertexHeightSliderCB(Fl_Widget *w, void *parm);
	static void redCB(Fl_Widget *w, void *param);
	static void blueCB(Fl_Widget *w, void *param);
	static void greenCB(Fl_Widget *w, void *param);
	static void nextVertexButtonCB(Fl_Widget *w, void *parm);
	static void prevVertexButtonCB(Fl_Widget *w, void *parm);
//	static void selectVertexButtonCB(Fl_Widget *w, void *parm);

public:
	WindowGUI(int x, int y, int w, int h, char* c);
	virtual ~WindowGUI();
//	Fl_Float_Input* getxVal(){ return xVal; };
//	Fl_Float_Input* getyVal(){ return yVal; };
//	Fl_Float_Input* getzVal(){ return zVal; };
//	Fl_Float_Input* getNumRows(){ return numRows; };
//	Fl_Float_Input* getNumCols(){ return numCols; };
//	Fl_Float_Input* getUnitWidth(){ return unitWidth; };
//	Fl_Float_Input* getUnitHeight(){ return unitHeight; };
//	Fl_Float_Input* getSubdivisions(){ return subdivisionsInput; };
};
#endif