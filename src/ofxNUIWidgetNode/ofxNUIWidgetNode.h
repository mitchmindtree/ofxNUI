/**********************************************************************************
 
 Copyright (C) 2014 Mitchell Nordine (www.mitchellnordine.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/


#ifndef __GenMax__ofxNUIWidgetNode__
#define __GenMax__ofxNUIWidgetNode__

/* Header Includes */

#include "ofMain.h"
#include "ofxNUINode.h"
#include "ofxUI.h"

#define WIDGET_SPACER 20
#define SLIDER_WIDTH 100
#define SLIDER_HEIGHT 20
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 30
#define ENVELOPE_EDITOR_WIDTH 600
#define ENVELOPE_EDITOR_HEIGHT 300
#define DDL_WIDTH 150
#define TEXT_INPUT_WIDTH 150
#define TOGGLE_DIMENSION 10

#define WIDGET_VERTICAL_PADDING_ACTIVE 20
#define WIDGET_VERTICAL_PADDING_HIGHLIGHTED 5

class ofxUISuperCanvasHelper: public ofxUISuperCanvas {
public:
    ofxUISuperCanvasHelper(string _label = "WidgetNode",
                           int _size = OFX_UI_FONT_MEDIUM)
    : ofxUISuperCanvas(_label, _size) {}
    virtual string& getSuperCanvasName() {}
    string superCanvasName;
    string& getName()
    {
        return getSuperCanvasName();
    }
};

/* Class */

class ofxNUIWidgetNode : public ofxNUINode, public ofxUISuperCanvasHelper {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIWidgetNode(string _label = "WidgetNode",
                     int _size = OFX_UI_FONT_MEDIUM)
    : ofxUISuperCanvasHelper(_label, _size), ofxNUINode() {
        init();
    }
    
    ~ofxNUIWidgetNode(){
        
    }
    
    /* Functions */
    
    virtual string getNodeName() { return "ofxNUIWidgetNode"; }
    virtual string& getSuperCanvasName() { return superCanvasName; }
    virtual string getNodeType() { return "ofxNUIWidgetNode"; }
    
    virtual void init();
    void setupCanvasAndCamera(ofxUICanvas *_canvas, ofEasyCam *_cam);
    void hideSuperCanvasTitle();
    void addWidgetsToSuperCanvas();
    void updateNode();
    void update();
    void updateSuperCanvas();
    void updateSuperCanvasWidgetDimensions();
    void updateSuperCanvasDimensions();
    void updateSuperCanvasPosition();
    virtual void customDraw();
    void drawSuperCanvas();
    void setHighlight(bool _isHighlighted);
    virtual void widgetFunctions(string _widgetName){}
    
    void widgetEventListener(ofxUIEventArgs &e);
    
    /* Add widgets */
    void addWidgetSlider(string _name, float *_floatPtr, float _min, float _max);
    void addWidgetIntSlider(string _name, int *_intPtr, int _min, int _max);
    void addWidgetNumberDialer(string _name, float *_floatPtr, float _min, float _max, int _precision);
    void addWidgetLabelButton(string _name);
    void addWidgetDropDownList(string _name, vector<string> _items, string _activeItem);
    void addWidgetTextInput(string _name, string _textstring);
    void addWidgetToggle(string _name, bool *_toggle);
    void addWidgetEnvelopeEditor(string _name, ofxUIEnvelope *_envelope,
                                 bool _isFreq);
    
    ofxUISuperCanvas *getSuperCanvas();
    ofxUIWidget* getWidget();
    ofxUISlider* getSlider();
    ofxUINumberDialer* getNumberDialer();
    ofxUILabelButton* getLabelButton();
    ofxUILabelToggle* getLabelToggle();
    ofxUIEnvelopeEditor* getEnvelopeEditor();
    ofxUIDropDownList* getDropDownList();
    ofxUITextInput* getTextInput();
    ofxUIToggle* getToggle();
    
    /* Variable Declaration */
    
    int numOfWidgets;
    float circumference;
    float highlightWidth;
    float highlightHeight;
    float highlightHeightMax;
    string ddlActiveItem;
    
    /* Variable Instances */
    
    int *intPtr;
    float *floatPtr;
    double *doublePtr;
    bool *boolPtr;
    
    /* Class Instances */
    
    vector<ofxUIWidget*> widgets;
    ofxUISlider *slider;
    ofxUIIntSlider *intSlider;
    ofxUINumberDialer *numberDialer;
    ofxUILabelButton *labelButton;
    ofxUILabelToggle *labelToggle;
    ofxUISuperCanvas *superCanvas;
    ofxUIWidget *widget;
    ofxUIEnvelopeEditor *envelopeEditor;
    ofxUIDropDownList *dropDownList;
    ofxUITextInput *textInput;
    ofxUIToggle *toggle;
    
    ofEasyCam *cam;
    ofxUICanvas *canvas;
    
};



#endif /* defined(__GenMax__ofxNUIWidgetNode__) */
