//
//  ofxNUIWidgetNode.h
//  GenMax
//
//  Created by Mitchell Nordine on 15/12/2013.
//
//

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

/* Class */

class ofxNUIWidgetNode : public ofxNUINode {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIWidgetNode(){
        slider = NULL;
        numberDialer = NULL;
        labelButton = NULL;
        canvas = NULL;
        widget = NULL;
        canvas = NULL;
        numOfWidgets = 0;
    }
    
    ~ofxNUIWidgetNode(){
        
    }
    
    /* Functions */
    
    virtual string getName() { return "ofxNUIWidgetNode"; }
    virtual string getNodeType() { return "ofxNUIWidgetNode"; }
    
    void setupCanvasAndCamera(ofxUICanvas *_canvas, ofEasyCam *_cam);
    void addWidgetsToSuperCanvas();
    void updateofxNUINode();
    void updateSuperCanvas();
    void updateSuperCanvasWidgetDimensions();
    void updateSuperCanvasDimensions();
    void updateSuperCanvasPosition();
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
