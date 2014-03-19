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

//------------------------------

ofxNUIWidgetNode::ofxNUIWidgetNode(string _label, int _size)
: canvas(_label, _size)
{
    getCanvas()->disableAppDrawCallback();
    getCanvas()->disableAppUpdateCallback();
    getCanvas()->setTheme(0);
    getCanvas()->setVisible(false);
    getCanvas()->setGlobalSliderHeight(SLIDER_HEIGHT);
    getCanvas()->setFontSize(OFX_UI_FONT_SMALL, OFX_UI_FONT_SMALL_SIZE);
    getCanvas()->setUseHeader(false);
}

//------------------------------

void ofxNUIWidgetNode::nodeInit()
{
    
}

//------------------------------

void ofxNUIWidgetNode::setCamera(ofEasyCam *_cam)
{
    ofxNUINode::setCamera(_cam);
    ofAddListener(getCanvas()->newGUIEvent, this,
                  &ofxNUIWidgetNode::widgetEventListener);
    updateSuperCanvasPosition();
}

//------------------------------

void ofxNUIWidgetNode::updateNode()
{
    
    ofxNUINode::updateNode();
    
    if (isActive()) {
        getCanvas()->setVisible(true);
        getCanvas()->autoSizeToFitWidgets();
    }
    else if (isHighlighted()) {
        getCanvas()->setVisible(true);
        getCanvas()->autoSizeToFitWidgets();
    }
    else {
        getCanvas()->setVisible(false);
    }
    
    updateSuperCanvas();
    
}

//------------------------------

void ofxNUIWidgetNode::setHighlight(bool _isHighlighted)
{
    
    ofxNUINode::setHighlight(_isHighlighted);
    
    if (!isHighlighted() && !isActive()) {
        getCanvas()->setVisible(false);
    }
    
    else if (isHighlighted()) {
        getCanvas()->setVisible(true);
        updateSuperCanvas();
        getCanvas()->autoSizeToFitWidgets();
    }
    
}

//------------------------------

void ofxNUIWidgetNode::setChildAsActive(ofxNUINode *_child)
{
    ofxNUINode::setChildAsActive(_child);
    getCanvas()->setVisible(false);
}

//------------------------------

void ofxNUIWidgetNode::setParentAsActive()
{
    ofxNUINode::setParentAsActive();
    getCanvas()->setVisible(false);
}

//------------------------------

void ofxNUIWidgetNode::update()
{
    ofxNUINode::update();
    if (getCanvas()->isVisible()) {
        updateSuperCanvas();
        getCanvas()->update();
    }
}

//------------------------------

void ofxNUIWidgetNode::updateSuperCanvas()
{
    circumference = PI * getNodeRadius() * 2;
    highlightWidth = circumference * getSiblingPerc();
    
    updateSuperCanvasPosition();
}

//------------------------------

void ofxNUIWidgetNode::updateSuperCanvasWidgetDimensions()
{
    
    /* If node is active */
    if (isActive()) {
        
        for (int i=0; i < getCanvas()->getWidgets().size(); i++) {
            ofxUIWidget *widget = getCanvas()->getWidgets()[i];
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
        
        highlightHeightMax = highlightWidth / (float)getCanvas()->getWidgets().size();
        
        for (int i=0; i < getCanvas()->getWidgets().size(); i++) {
            ofxUIWidget *widget = getCanvas()->getWidgets()[i];
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

//------------------------------

void ofxNUIWidgetNode::updateSuperCanvasPosition()
{
    if (!getCam()) { return; }
    ofVec2f current = getCam()->worldToScreen(
                getPosition()+ofVec3f(getNodeRadius(),-getNodeRadius()/2.0f,0) );
    getCanvas()->setPosition(current.x, current.y);
}

//------------------------------

void ofxNUIWidgetNode::customDraw2D()
{
    ofxNUINode::customDraw2D();
    if (getCanvas()->isVisible()) {
        getCanvas()->draw();
    }
}

//------------------------------

ofxUISlider* ofxNUIWidgetNode::addWidgetSlider(string _name, float *_value,
                                 float _min, float _max)
{
    return getCanvas()->addSlider(_name, _min, _max, _value,
                                  SLIDER_WIDTH, SLIDER_HEIGHT);
}

ofxUIIntSlider* ofxNUIWidgetNode::addWidgetIntSlider(string _name, int *_value, int _min, int _max)
{
    ofxUIIntSlider *intSlider;
    getCanvas()->addWidgetDown(intSlider = new ofxUIIntSlider(_name, _min, _max, _value, SLIDER_WIDTH, SLIDER_HEIGHT));
    return intSlider;
}

//------------------------------

ofxUINumberDialer* ofxNUIWidgetNode::addWidgetNumberDialer(string _name, float *_floatPtr,
                                       float _min, float _max, int _precision)
{
    return getCanvas()->addNumberDialer(_name, _min, _max, _floatPtr, _precision);
}

//------------------------------

ofxUILabelButton* ofxNUIWidgetNode::addWidgetLabelButton(string _name)
{
    bool tempBool = false;
    ofxUILabelButton *labelButton = getCanvas()->addLabelButton(_name, tempBool, BUTTON_WIDTH, BUTTON_HEIGHT, OFX_UI_FONT_SMALL, false);
    labelButton->setLabelVisible(true);
    return labelButton;
}

//------------------------------

ofxUIDropDownList* ofxNUIWidgetNode::addWidgetDropDownList(string _name, vector<string> _items,
                                             string _activeItem)
{
    ofxUIDropDownList *dropDownList;
    getCanvas()->addWidgetDown(dropDownList = new ofxUIDropDownList(DDL_WIDTH,_name,_items, OFX_UI_FONT_SMALL));
    dropDownList->setAllowMultiple(false);
    dropDownList->setAutoClose(true);
    dropDownList->activateToggle(_activeItem);
    dropDownList->setLabelText(_activeItem);
    return dropDownList;
}

//------------------------------

ofxUITextInput* ofxNUIWidgetNode::addWidgetTextInput(string _name, string _textstring)
{
    ofxUITextInput *textInput;
    getCanvas()->addWidgetDown(textInput = new ofxUITextInput(_name, _textstring, TEXT_INPUT_WIDTH));
    textInput->setTriggerOnClick(false);
    textInput->setAutoClear(false);
    return textInput;
}

//------------------------------

ofxUIToggle* ofxNUIWidgetNode::addWidgetToggle(string _name, bool *_toggle)
{
    return getCanvas()->addToggle(_name, _toggle, TOGGLE_DIMENSION, TOGGLE_DIMENSION);
}

//------------------------------

ofxUIEnvelopeEditor* ofxNUIWidgetNode::addWidgetEnvelopeEditor(string _name, ofxUIEnvelope*_envelope, bool _isFreq)
{
    ofxUIEnvelopeEditor *envelopeEditor;
    getCanvas()->addWidgetDown(envelopeEditor = new ofxUIEnvelopeEditor(_name, _envelope,ENVELOPE_EDITOR_WIDTH, ENVELOPE_EDITOR_HEIGHT, 0.0f, 0.0f));
    envelopeEditor->isFrequency = _isFreq;
    return envelopeEditor;
}

//------------------------------

void ofxNUIWidgetNode::widgetEventListener(ofxUIEventArgs &e)
{
    
    for (int i=0; i < getCanvas()->getWidgets().size(); i++) {
        ofxUIWidget *widget = getCanvas()->getWidgets().at(i);
        
        if(e.widget->getName() == widget->getName()){
            
            /* Slider */
            if (widget->getKind() == OFX_UI_WIDGET_SLIDER_H
                || widget->getKind() == OFX_UI_WIDGET_SLIDER_V) {
                ofxUISlider *slider = dynamic_cast<ofxUISlider*>(widget);
                widgetFunctions(slider->getName());
            }
            
            /* Int Slider */
            else if (widget->getKind() == OFX_UI_WIDGET_INTSLIDER_H
                     || widget->getKind() == OFX_UI_WIDGET_INTSLIDER_V) {
                ofxUIIntSlider *intSlider = dynamic_cast<ofxUIIntSlider*>(widget);
                widgetFunctions(intSlider->getName());
            }
            
            /* Number Dialer */
            else if (widget->getKind() == OFX_UI_WIDGET_NUMBERDIALER) {
                ofxUINumberDialer *numberDialer = dynamic_cast<ofxUINumberDialer*>(widget);
                widgetFunctions(numberDialer->getName());
            }
            
            /* Drop Down List */
            else if (widget->getKind() == OFX_UI_WIDGET_DROPDOWNLIST) {
                ofxUIDropDownList *dropDownList = dynamic_cast<ofxUIDropDownList*>(widget);
                if (ofGetMousePressed() == false
                    && dropDownList->getSelected().size()) {
                    ofxUIWidget *selected = dropDownList->getSelected().at(0);
                    widgetFunctions(selected->getName());
                }
            }
            
            /* Label Button */
            else if (widget->getKind() == OFX_UI_WIDGET_LABELBUTTON) {
                ofxUILabelButton *labelButton = dynamic_cast<ofxUILabelButton*>(widget);
                if(ofGetMousePressed() == false){
                    widgetFunctions(labelButton->getName());
                    labelButton->setValue(false);
                }
            }
            
            /* Text Input */
            else if (widget->getKind() == OFX_UI_WIDGET_TEXTINPUT) {
                ofxUITextInput *textInput = dynamic_cast<ofxUITextInput*>(widget);
                widgetFunctions(textInput->getName());
            }
            
            break;
            
        }
        
    }
    
}

//------------------------------

ofxUISuperCanvas* ofxNUIWidgetNode::getCanvas()
{
    return &canvas;
}

//------------------------------



//------------------------------



//------------------------------



//------------------------------



//------------------------------