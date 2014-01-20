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


#include "ofxNUIWidgetNode.h"

//--------------------------------------------------------------------------------//
// INITIALISE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::init()
{
    superCanvasName = getNodeName();
    slider = NULL;
    numberDialer = NULL;
    labelButton = NULL;
    widget = NULL;
    canvas = NULL;
    numOfWidgets = 0;
}

//--------------------------------------------------------------------------------//
// SET CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setupCanvasAndCamera(ofxUICanvas *_canvas, ofEasyCam *_cam)
{
    
    canvas = _canvas;
    cam = _cam;
    
    
    ofxUISuperCanvas::setPosition(ofxNUINode::getPosition().x,
                                  ofxNUINode::getPosition().y);
    ofxUISuperCanvas::setDimensions(10, 10);
    ofxUISuperCanvas::setFontSize(OFX_UI_FONT_SMALL, OFX_UI_FONT_SMALL_SIZE);
    
    
    /* superCanvas = new ofxUISuperCanvas(getNodeLabel(), ofxNUINode::getPosition().x,
                                       ofxNUINode::getPosition().y, 10, 10,
                                       OFX_UI_FONT_SMALL); */
    
    canvas->addWidgetDown(this);
    
    ofxUISuperCanvas::setAutoDraw(false);
    ofxUISuperCanvas::setMinified(true);
    ofxUISuperCanvas::setVisible(false);
    ofxUISuperCanvas::setTheme(0);
    ofxUISuperCanvas::getCanvasTitle()->setAutoSize(true);

    hideSuperCanvasTitle();
    
    /* superCanvas->setAutoDraw(false);
    superCanvas->setMinified(true);
    superCanvas->setVisible(false);
    superCanvas->setTheme(0); */
    
    addWidgetsToSuperCanvas();
    
    ofAddListener(ofxUISuperCanvas::newGUIEvent, this, &ofxNUIWidgetNode::widgetEventListener);
    
}

//--------------------------------------------------------------------------------//
// HIDE SUPERCANVAS TITLE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::hideSuperCanvasTitle()
{
    ofxUISuperCanvas::getCanvasTitle()->setVisible(false);
    ofxUISuperCanvas::autoSizeToFitWidgets();
}

//--------------------------------------------------------------------------------//
// ADD WIDGETS TO CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetsToSuperCanvas()
{
    
    for (int i=0; i < widgets.size(); i++) {
        widget = widgets.at(i);
        //superCanvas->addWidgetDown(widget);
        ofxUISuperCanvas::addWidgetDown(widget);
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE ofxNUINode (OVERLOAD OF ofxNUINode)
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateNode()
{
    
    ofxNUINode::updateNode();
    
    if (!ofxUISuperCanvas::isVisible()) { return; }
    
    if (isActive()) {
        ofxUISuperCanvas::setVisible(true);
        ofxUISuperCanvas::setMinified(false);
        ofxUISuperCanvas::autoSizeToFitWidgets();
        /* superCanvas->setVisible(true);
        superCanvas->setMinified(false);
        superCanvas->autoSizeToFitWidgets(); */
    }
    else if (isHighlighted()) {
        ofxUISuperCanvas::setVisible(true);
        ofxUISuperCanvas::setMinified(false);
        /* superCanvas->setVisible(true);
        superCanvas->setMinified(false); */
    }
    else if (getParentNode()){
        if (getParentNode()->isActive()) {
            ofxUISuperCanvas::setVisible(true);
            ofxUISuperCanvas::setMinified(true);
            /* superCanvas->setVisible(true);
            superCanvas->setMinified(true); */
        }
    }
    else {
        ofxUISuperCanvas::setVisible(false);
        ofxUISuperCanvas::setMinified(true);
        //superCanvas->setVisible(false);
    }
    
    hideSuperCanvasTitle();
    
    updateSuperCanvas();
    
}

//--------------------------------------------------------------------------------//
// SET HIGHLIGHT (OVERLOAD OF ofxNUINode)
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setHighlight(bool _isHighlighted)
{
    
    ofxNUINode::setHighlight(_isHighlighted);
    
    if (!isHighlighted()) {
        ofxUISuperCanvas::setMinified(true);
        ofxUISuperCanvas::setVisible(false);
    }
    
    else if (isHighlighted()) {
        ofxUISuperCanvas::setMinified(false);
        ofxUISuperCanvas::setVisible(true);
        ofxUISuperCanvas::autoSizeToFitWidgets();

        /* superCanvas->setMinified(false);
        superCanvas->autoSizeToFitWidgets(); */
        updateSuperCanvas();
    }
    
    hideSuperCanvasTitle();
    
}

//--------------------------------------------------------------------------------//
// UPDATE SUPERCANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvas()
{

    if (!ofxUISuperCanvas::isVisible()) { return; }
    
    numOfWidgets = widgets.size();
    circumference = PI * getNodeRadius() * 2;
    highlightWidth = circumference * getSiblingPerc();
    
    //updateSuperCanvasWidgetDimensions();
    //updateSuperCanvasDimensions();
    updateSuperCanvasPosition();
    
}

//--------------------------------------------------------------------------------//
// UPDATE SUPERCANVAS WIDGET SIZES
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvasWidgetDimensions()
{
    
    /* If node is active */
    if (isActive()) {
        
        for (int i=0; i < widgets.size(); i++) {
            widget = widgets[i];
            ofxUIRectangle *rect = widget->getRect();
            
            if (widget->getKind() == OFX_UI_WIDGET_SLIDER_H) {
                rect->setWidth(SLIDER_WIDTH);
                rect->setHeight(SLIDER_HEIGHT);
            }
            else if (widget->getKind() == OFX_UI_WIDGET_LABELBUTTON) {
                rect->setWidth(BUTTON_WIDTH);
                rect->setHeight(BUTTON_HEIGHT);
            }
            else if (widget->getKind() == OFX_UI_WIDGET_2DPAD) {
                rect->setWidth(ENVELOPE_EDITOR_WIDTH);
                rect->setHeight(ENVELOPE_EDITOR_HEIGHT);
            }
            
            /* Set new widget position */
            if (i == 0) {
                /* rect->setX(0);
                rect->setY(0); */
            }
            else {
                /* rect->setX(widgets[i-1]->getRect()->getX());
                rect->setY(widgets[i-1]->getRect()->getHeight()
                           + widgets[i-1]->getRect()->getY()); */
            }
            
        }
        
    }
    
    /* If node is highlighted */
    else if (isHighlighted()) {
        
        highlightHeightMax = highlightWidth / (float)numOfWidgets;
        
        for (int i=0; i < numOfWidgets; i++) {
            widget = widgets[i];
            ofxUIRectangle *rect = widget->getRect();
            
            if (widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER) { }
            
            else {
                rect->setWidth(highlightWidth);
                if (rect->getHeight() > highlightHeightMax) {
                    highlightHeight = highlightHeightMax;
                }
                else {
                    highlightHeight = rect->getHeight();
                }
                rect->setHeight(highlightHeight);
            }
            
            /* Set new widget position */
            if (i == 0) {
                /* rect->setX(0);
                rect->setY(0); */
            }
            else {
                /* rect->setX(widgets[i-1]->getRect()->getX());
                rect->setY(widgets[i-1]->getRect()->getHeight()
                           + widgets[i-1]->getRect()->getY()); */
            }
            
        }
        
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE SUPERCANVAS DIMENSIONS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvasDimensions()
{
    
    if (isActive() || isHighlighted()) {
        ofxUISuperCanvas::autoSizeToFitWidgets();
        //superCanvas->autoSizeToFitWidgets();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE WIDGET POSITIONS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvasPosition()
{
    
    if (!canvas || !cam) { return; }
    
    ofVec2f current = cam->worldToScreen(
                                getPosition()+ofVec3f(getNodeRadius(),0,0) );
    
    //superCanvas->setPosition(current.x, current.y);
    ofxUISuperCanvas::setPosition(current.x, current.y);
    
    /* if (isActive() || isHighlighted()) {
        
        for (int i=0; i < widgets.size(); i++) {
            widget = widgets[i];
            ofxUIRectangle *rect = widget->getRect();
            
            if (i == 0) {
                rect->setX(0);
                rect->setY(0);
            }
            else {
                rect->setX(widgets[i-1]->getRect()->getX());
                rect->setY(widgets[i-1]->getRect()->getHeight()
                           + widgets[i-1]->getRect()->getY());
            }
            
        }
        
    } */
    
}

//--------------------------------------------------------------------------------//
// DRAW SUPER CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::drawSuperCanvas()
{
    
    if (!canvas) { return; }
    
    //superCanvas->draw();
    ofxUISuperCanvas::draw();
    
}

//--------------------------------------------------------------------------------//
// ADD WIDGET SLIDER
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetSlider(string _name, float *_floatPtr,
                                 float _min, float _max)
{
    
    widget = new ofxUISlider(SLIDER_WIDTH, SLIDER_HEIGHT, _min, _max, _floatPtr,
                             _name);
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD WIDGET INT SLIDER
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetIntSlider(string _name, int *_intPtr, int _min, int _max)
{
    
    widget = new ofxUIIntSlider(_name, _min, _max, _intPtr, SLIDER_WIDTH, SLIDER_HEIGHT);
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD NUMBER DIALER
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetNumberDialer(string _name, float *_floatPtr,
                                       float _min, float _max, int _precision)
{
    
    /* First, add label 'header' with dialer name */
    widget = new ofxUILabel(_name, OFX_UI_FONT_SMALL);
    widgets.push_back(widget);
    
    /* Then add number dialer... */
    numberDialer = new ofxUINumberDialer(_min, _max, _floatPtr, _precision, _name,
                                         OFX_UI_FONT_SMALL);
    
    widget = numberDialer;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD WIDGET LABEL BUTTON
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetLabelButton(string _name)
{
    
    bool tempBool = false;
    
    labelButton = new ofxUILabelButton(_name, tempBool, BUTTON_WIDTH, BUTTON_HEIGHT, OFX_UI_FONT_SMALL, false);
    labelButton->setLabelVisible(true);
    
    widget = labelButton;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD DROP DOWN LIST
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetDropDownList(string _name, vector<string> _items, string _activeItem)
{
    
    dropDownList = new ofxUIDropDownList(DDL_WIDTH,_name,_items, OFX_UI_FONT_SMALL);
    dropDownList->setShowCurrentSelected(true);
    dropDownList->setAllowMultiple(false);
    dropDownList->setAutoClose(true);
    dropDownList->activateToggle(_activeItem);
    
    widget = dropDownList;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD TEXT INPUT
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetTextInput(string _name, string _textstring)
{
    
    textInput = new ofxUITextInput(_name, _textstring, TEXT_INPUT_WIDTH);
    textInput->setTriggerOnClick(false);
    
    widget = textInput;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD TOGGLE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetToggle(string _name, bool *_toggle)
{
    
    toggle = new ofxUIToggle(_name, _toggle, TOGGLE_DIMENSION, TOGGLE_DIMENSION);
    
    widget = toggle;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
// ADD ENVELOPE EDITOR
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::addWidgetEnvelopeEditor(string _name, ofxUIEnvelope *_envelope,
                                         bool _isFreq)
{
    
    envelopeEditor = new ofxUIEnvelopeEditor(_name, _envelope,ENVELOPE_EDITOR_WIDTH,
                                  ENVELOPE_EDITOR_HEIGHT, 0.0f, 0.0f);
    envelopeEditor->isFrequency = _isFreq;
    
    widget = envelopeEditor;
    
    widgets.push_back(widget);
    
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
// WIDGET EVENT LISTENER
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::widgetEventListener(ofxUIEventArgs &e)
{
    
    for (int i=0; i < widgets.size(); i++) {
        widget = widgets.at(i);
        
        if(e.widget->getName() == widget->getName()){
            
            /* Slider */
            if (widget->getKind() == OFX_UI_WIDGET_SLIDER_H
                || widget->getKind() == OFX_UI_WIDGET_SLIDER_V) {
                slider = dynamic_cast<ofxUISlider*>(widget);
                widgetFunctions(slider->getName());
            }
            
            /* Int Slider */
            else if (widget->getKind() == OFX_UI_WIDGET_INTSLIDER_H
                     || widget->getKind() == OFX_UI_WIDGET_INTSLIDER_V) {
                intSlider = dynamic_cast<ofxUIIntSlider*>(widget);
                widgetFunctions(intSlider->getName());
            }
            
            /* Number Dialer */
            else if (widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER) {
                numberDialer = dynamic_cast<ofxUINumberDialer*>(widget);
                widgetFunctions(numberDialer->getName());
            }
            
            /* Drop Down List */
            else if (widget->getKind() == OFX_UI_WIDGET_DROPDOWNLIST) {
                dropDownList = dynamic_cast<ofxUIDropDownList*>(widget);
                if (ofGetMousePressed() == false
                    && dropDownList->getSelected().size()) {
                    ofxUIWidget *selected = dropDownList->getSelected().at(0);
                    widgetFunctions(selected->getName());
                }
            }
            
            /* Label Button */
            else if (widget->getKind() == OFX_UI_WIDGET_LABELBUTTON) {
                labelButton = dynamic_cast<ofxUILabelButton*>(widget);
                if(ofGetMousePressed() == false){
                    widgetFunctions(labelButton->getName());
                    labelButton->setValue(false);
                }
            }
            
            /* Text Input */
            else if (widget->getKind() == OFX_UI_WIDGET_TEXTINPUT) {
                textInput = dynamic_cast<ofxUITextInput*>(widget);
                widgetFunctions(textInput->getName());
            }
            
            break;
            
        }
        
    }
    
    return;
    
}

//--------------------------------------------------------------------------------//
// GET WIDGETS
//--------------------------------------------------------------------------------//

ofxUISuperCanvas* ofxNUIWidgetNode::getSuperCanvas()
{
    return superCanvas;
}

ofxUIWidget* ofxNUIWidgetNode::getWidget()
{
    return widget;
}

ofxUISlider* ofxNUIWidgetNode::getSlider()
{
    return slider;
}

ofxUINumberDialer* ofxNUIWidgetNode::getNumberDialer()
{
    return numberDialer;
}

ofxUILabelButton* ofxNUIWidgetNode::getLabelButton()
{
    return labelButton;
}

ofxUILabelToggle* ofxNUIWidgetNode::getLabelToggle()
{
    return labelToggle;
}

ofxUIEnvelopeEditor* ofxNUIWidgetNode::getEnvelopeEditor()
{
    return envelopeEditor;
}

ofxUIDropDownList* ofxNUIWidgetNode::getDropDownList()
{
    return dropDownList;
}

ofxUITextInput* ofxNUIWidgetNode::getTextInput()
{
    return textInput;
}

ofxUIToggle* ofxNUIWidgetNode::getToggle()
{
    return toggle;
}

//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//