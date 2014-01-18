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


#include "ofxNUIDirectorNode.h"

//--------------------------------------------------------------------------------//
// INITIATE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::init()
{
    ofxNUINode::init();
}

//--------------------------------------------------------------------------------//
// SETUP CORE NODE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setup(vector<ofxNUINode *> _nodes)
{
    
    setNodeLabel(getName());
    setActiveNode(this);
    setActive(true);
    setHighlight(false);
    ofNode::setPosition(0.0f, 0.0f, 0.0f);
    setColorScheme(&coreColorScheme);
    setShapeType(OFXNUINODE_SHAPE_SPHERE);
    setupCanvas();
    setupGL();
    setupCam();
    setupLight();
    
    getChildren()->reserve(_nodes.size());
    for (int i=0; i < getChildren()->size(); i++) {
        addChild(_nodes.at(i));
    }
    
    updateChildren();
    
}

//--------------------------------------------------------------------------------//
// SETUP CANVAS
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setupCanvas()
{
    canvas = new ofxUICanvas(0, 0, ofGetWidth(), ofGetHeight());
    canvas->setName("CoreNodeCanvas");
    canvas->setVisible(true);
    setCanvasForWidgetNodes(this);
}

//--------------------------------------------------------------------------------//
// SET CANVAS FOR WIDGET NODES
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setCanvasForWidgetNodes(ofxNUINode *_node)
{
    if (_node->getNodeType() == "ofxNUIWidgetNode") {
        widgetNode = dynamic_cast<ofxNUIWidgetNode*>(_node);
        widgetNode->setupCanvasAndCamera(canvas, &cam);
    }
    for (int i=0; i < _node->getChildren()->size(); i++) {
        setCanvasForWidgetNodes(_node->getChildren()->at(i));
    }
}

//--------------------------------------------------------------------------------//
// SETUP GL
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setupGL()
{
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableSmoothing();
}

//--------------------------------------------------------------------------------//
// SETUP CAM
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setupCam()
{
    cam.setPosition(getPosition().x,
                    getPosition().y,
                    getPosition().z + (OFXNUINODE_LAYOUT_RADIUS * 1.8f));
    cam.setTarget(getPosition());
    cam.setDistance(OFXNUINODE_LAYOUT_RADIUS * 1.8f);
}

//--------------------------------------------------------------------------------//
// SETUP LIGHT
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setupLight()
{
    ofEnableLighting();
    ambientLight.setAmbientColor(ofColor(150, 190, 170, 255));
    ambientLight.setDiffuseColor(ofColor(150,150,150));
}

//--------------------------------------------------------------------------------//
// SET ACTIVE NODE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setActiveNode(ofxNUINode *_activeNode)
{
    activeNode = _activeNode;
}

//--------------------------------------------------------------------------------//
// SET PREVIOUS ACTIVE NODE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setPrevActiveNode(ofxNUINode *_prevActiveNode)
{
    prevActiveNode = _prevActiveNode;
}

//--------------------------------------------------------------------------------//
// SET CLOSEST CHILD NODE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setClosestChild(ofxNUINode *_closestChild)
{
    closestChild = _closestChild;
}

//--------------------------------------------------------------------------------//
// SET PREVIOUS CLOSEST CHILD
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::setPrevClosestChild(ofxNUINode *_prevClosestChild)
{
    prevClosestChild = _prevClosestChild;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE NODE
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUIDirectorNode::getActiveNode()
{
    return activeNode;
}

//--------------------------------------------------------------------------------//
// RETURN PREVIOUS ACTIVE NODE
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUIDirectorNode::getPrevActiveNode()
{
    return prevActiveNode;
}

//--------------------------------------------------------------------------------//
// RETURN CLOSEST CHILD
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUIDirectorNode::getClosestChild()
{
    return closestChild;
}

//--------------------------------------------------------------------------------//
// RETURN PREVIOUS CLOSEST CHILD
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUIDirectorNode::getPrevClosestChild()
{
    return prevClosestChild;
}

//--------------------------------------------------------------------------------//
// MOVE CAMERA TO ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::moveCamToActive()
{
    
    tweenCamPosition.setParameters(1, easingQuad, ofxTween::easeOut,
                                   cam.getPosition().x, activeNode->getNodePosition().x,
                                   positionDurationMS, delayMS);
    tweenCamPosition.addValue(cam.getPosition().y, activeNode->getNodePosition().y);
    tweenCamPosition.addValue(cam.getPosition().z, activeNode->getNodePosition().z
                              + (OFXNUINODE_LAYOUT_RADIUS * 1.8f));
    
    tweenCamTarget.setParameters(2, easingExpo, ofxTween::easeOut,
                                 prevActiveNode->getPosition().x, activeNode->getNodePosition().x,
                                 targetDurationMS, delayMS);
    tweenCamTarget.addValue(prevActiveNode->getPosition().y,
                            activeNode->getNodePosition().y);
    tweenCamTarget.addValue(prevActiveNode->getPosition().z,
                            activeNode->getNodePosition().z);
    
    tweenCamPosition.start();
    tweenCamTarget.start();
    
    positionIsTweening = true;
    targetIsTweening = true;
    
}

//--------------------------------------------------------------------------------//
// UPDATE CAM TWEEN
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::updateCamTween()
{
    if (positionIsTweening) {
        ofVec3f camPosition = ofVec3f(tweenCamPosition.update(),
                                      tweenCamPosition.getTarget(1),
                                      tweenCamPosition.getTarget(2));
        cam.setPosition(camPosition);
    }
    if (targetIsTweening) {
        ofVec3f camTarget = ofVec3f(tweenCamTarget.update(),
                                    tweenCamTarget.getTarget(1),
                                    tweenCamTarget.getTarget(2));
        cam.setTarget(camTarget);
    }
}

//--------------------------------------------------------------------------------//
// STOP CAM TWEEN
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::stopCamTween()
{
    positionIsTweening = false;
    targetIsTweening = false;
}

//--------------------------------------------------------------------------------//
// CHECK MOUSE FOR SUPER CANVAS
//--------------------------------------------------------------------------------//

bool ofxNUIDirectorNode::isMouseOnASuperCanvas()
{
    if (!closestChild) {
        return false;
    }
    
    if (closestChild->getNodeType() == "ofxNUIWidgetNode") {
        widgetNode = dynamic_cast<ofxNUIWidgetNode*>(closestChild);
        if (widgetNode->superCanvas->isHit(ofGetMouseX(), ofGetMouseY())) {
            cam.disableMouseInput();
            return true;
        }
        else {
            cam.enableMouseInput();
            return false;
        }
    }
    else {
        cam.enableMouseInput();
        return false;
    }
}

//--------------------------------------------------------------------------------//
// FIND CLOSEST CHILD
//--------------------------------------------------------------------------------//

void ofxNUIDirectorNode::findClosestChild()
{
    ofVec2f mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());
    
    distance = 0;
    smallestDistance = 0;
    
    for (int i=0; i < activeNode->getChildren()->size(); i++) {
        child = dynamic_cast<ofxNUINode*>(activeNode->getChildren()->at(i));
        ofVec3f current = cam.worldToScreen(child->getPosition());
        distance = current.distance(mouse);
        if (i == 0 || distance < smallestDistance) {
            smallestDistance = distance;
            closestChild = child;
        }
    }
    
    if (!prevClosestChild) {
        closestChild->setHighlight(true);
        prevClosestChild = closestChild;
        return;
    }
    
    if (closestChild->getNodeLabel() != prevClosestChild->getNodeLabel()) {
        prevClosestChild->setHighlight(false);
        closestChild->setHighlight(true);
        prevClosestChild = closestChild;
    }
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