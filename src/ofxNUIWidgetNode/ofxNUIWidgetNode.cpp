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
// CONSTRUCTORS / DESTRUCTORS
//--------------------------------------------------------------------------------//

ofxNUIWidgetNode::ofxNUIWidgetNode(string _label, int _size) : ofxNUINode(), superCanvas(getName(), OFX_UI_FONT_MEDIUM)
{
    nodeInit();
}

//--------------------------------------------------------------------------------//
// INITIALISE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::nodeInit()
{
    slider = NULL;
    numberDialer = NULL;
    labelButton = NULL;
    widget = NULL;
    numOfWidgets = 0;
    getSuperCanvas()->setAutoDraw(false);
    getSuperCanvas()->setAutoUpdate(false);
    getSuperCanvas()->setUseHeader(false);
    getSuperCanvas()->setTheme(0);
    getSuperCanvas()->setMinified(true);
    getSuperCanvas()->setVisible(false);
    getSuperCanvas()->setGlobalSliderHeight(SLIDER_HEIGHT);
    getSuperCanvas()->setFontSize(OFX_UI_FONT_SMALL, OFX_UI_FONT_SMALL_SIZE);
    ofAddListener(getSuperCanvas()->newGUIEvent, this,
                  &ofxNUIWidgetNode::widgetEventListener);
}

//--------------------------------------------------------------------------------//
// SET CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setCamera(ofEasyCam *_cam)
{
    ofxNUINode::setCamera(_cam);
    updateSuperCanvasPosition();
}

//--------------------------------------------------------------------------------//
// UPDATE ofxNUINode (OVERLOAD OF ofxNUINode)
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateNode()
{
    
    ofxNUINode::updateNode();
    
    if (isActive()) {
        getSuperCanvas()->setVisible(true);
        getSuperCanvas()->setMinified(false);
        getSuperCanvas()->autoSizeToFitWidgets();
    }
    else if (isHighlighted()) {
        getSuperCanvas()->setVisible(true);
        getSuperCanvas()->setMinified(false);
        getSuperCanvas()->autoSizeToFitWidgets();
    }
    else {
        getSuperCanvas()->setVisible(false);
        getSuperCanvas()->setMinified(true);
    }
    
    updateSuperCanvas();
    
}

//--------------------------------------------------------------------------------//
// SET HIGHLIGHT (OVERLOAD OF ofxNUINode)
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setHighlight(bool _isHighlighted)
{
    
    ofxNUINode::setHighlight(_isHighlighted);
    
    if (!isHighlighted() && !isActive()) {
        getSuperCanvas()->setMinified(true);
        getSuperCanvas()->setVisible(false);
    }
    
    else if (isHighlighted()) {
        getSuperCanvas()->setVisible(true);
        getSuperCanvas()->setMinified(false);
        updateSuperCanvas();
        getSuperCanvas()->autoSizeToFitWidgets();
    }
    
}

//--------------------------------------------------------------------------------//
// SET CHILD AS ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setChildAsActive(ofxNUINode *_child)
{
    ofxNUINode::setChildAsActive(_child);
    getSuperCanvas()->setVisible(false);
    getSuperCanvas()->setMinified(true);
}

//--------------------------------------------------------------------------------//
// SET PARENT AS ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::setParentAsActive()
{
    ofxNUINode::setParentAsActive();
    getSuperCanvas()->setVisible(false);
    getSuperCanvas()->setMinified(true);
}

//--------------------------------------------------------------------------------//
// UPDATE
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::update()
{
    ofxNUINode::update();
    if (getSuperCanvas()->isVisible()) {
        updateSuperCanvas();
        getSuperCanvas()->update();
    }
}

//--------------------------------------------------------------------------------//
// UPDATE SUPERCANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvas()
{
    numOfWidgets = widgets.size();
    circumference = PI * getNodeRadius() * 2;
    highlightWidth = circumference * getSiblingPerc();
    
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
// UPDATE WIDGET POSITIONS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::updateSuperCanvasPosition()
{
    if (!getCam()) { return; }
    ofVec2f current = getCam()->worldToScreen(
                getPosition()+ofVec3f(getNodeRadius(),-getNodeRadius()/2.0f,0) );
    getSuperCanvas()->setPosition(current.x, current.y);
}

//--------------------------------------------------------------------------------//
// DRAW SUPER CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIWidgetNode::customDraw2D()
{
    ofxNUINode::customDraw2D();
    if (getSuperCanvas()->isVisible()) {
        getSuperCanvas()->draw();
    }
}

//--------------------------------------------------------------------------------//
// ADD WIDGET SLIDER
//--------------------------------------------------------------------------------//

ofxUISlider* ofxNUIWidgetNode::addWidgetSlider(string _name, float *_value,
                                 float _min, float _max)
{
    return getSuperCanvas()->addSlider(_name, _min, _max, _value, SLIDER_WIDTH,
                                       SLIDER_HEIGHT);
}

ofxUIIntSlider* ofxNUIWidgetNode::addWidgetIntSlider(string _name, int *_value, int _min, int _max)
{
    getSuperCanvas()->addWidgetDown(intSlider = new ofxUIIntSlider
                        (_name, _min, _max, _value, SLIDER_WIDTH, SLIDER_HEIGHT));
    return intSlider;
}

//--------------------------------------------------------------------------------//
// ADD NUMBER DIALER
//--------------------------------------------------------------------------------//

ofxUINumberDialer* ofxNUIWidgetNode::addWidgetNumberDialer(string _name, float *_floatPtr,
                                       float _min, float _max, int _precision)
{
    getSuperCanvas()->addWidgetDown(new ofxUILabel(_name,OFX_UI_FONT_SMALL));
    return getSuperCanvas()->addNumberDialer(_name, _min, _max, _floatPtr,
                                             _precision);
}

//--------------------------------------------------------------------------------//
// ADD WIDGET LABEL BUTTON
//--------------------------------------------------------------------------------//

ofxUILabelButton* ofxNUIWidgetNode::addWidgetLabelButton(string _name)
{
    bool tempBool = false;
    labelButton = getSuperCanvas()->addLabelButton(_name, tempBool, BUTTON_WIDTH, BUTTON_HEIGHT, OFX_UI_FONT_SMALL, false);
    labelButton->setLabelVisible(true);
    return labelButton;
}

//--------------------------------------------------------------------------------//
// ADD DROP DOWN LIST
//--------------------------------------------------------------------------------//

ofxUIDropDownList* ofxNUIWidgetNode::addWidgetDropDownList(string _name, vector<string> _items,
                                             string _activeItem)
{
    getSuperCanvas()->addWidgetDown(dropDownList = new ofxUIDropDownList(DDL_WIDTH,_name,_items, OFX_UI_FONT_SMALL));
    dropDownList->setAllowMultiple(false);
    dropDownList->setAutoClose(true);
    dropDownList->activateToggle(_activeItem);
    return dropDownList;
}

//--------------------------------------------------------------------------------//
// ADD TEXT INPUT
//--------------------------------------------------------------------------------//

ofxUITextInput* ofxNUIWidgetNode::addWidgetTextInput(string _name, string _textstring)
{
    getSuperCanvas()->addWidgetDown(textInput = new ofxUITextInput(_name, _textstring, TEXT_INPUT_WIDTH));
    textInput->setTriggerOnClick(false);
    textInput->setAutoClear(false);
    return textInput;
}

//--------------------------------------------------------------------------------//
// ADD TOGGLE
//--------------------------------------------------------------------------------//

ofxUIToggle* ofxNUIWidgetNode::addWidgetToggle(string _name, bool *_toggle)
{
    return getSuperCanvas()->addToggle(_name, _toggle, TOGGLE_DIMENSION,
                                       TOGGLE_DIMENSION);
}

//--------------------------------------------------------------------------------//
// ADD ENVELOPE EDITOR
//--------------------------------------------------------------------------------//

ofxUIEnvelopeEditor* ofxNUIWidgetNode::addWidgetEnvelopeEditor(string _name,ofxUIEnvelope*_envelope, bool _isFreq)
{
    getSuperCanvas()->addWidgetDown(envelopeEditor = new ofxUIEnvelopeEditor
    (_name, _envelope,ENVELOPE_EDITOR_WIDTH, ENVELOPE_EDITOR_HEIGHT, 0.0f, 0.0f));
    envelopeEditor->isFrequency = _isFreq;
    return envelopeEditor;
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
    
    for (int i=0; i < getSuperCanvas()->getWidgets().size(); i++) {
        widget = getSuperCanvas()->getWidgets().at(i);
        
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
    
}

//--------------------------------------------------------------------------------//
// GET WIDGETS
//--------------------------------------------------------------------------------//

ofxUISuperCanvas* ofxNUIWidgetNode::getSuperCanvas()
{
    return &superCanvas;
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