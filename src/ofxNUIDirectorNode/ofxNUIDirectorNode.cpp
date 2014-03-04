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

//------------------------------

ofxNUIDirectorNode::ofxNUIDirectorNode()
{
    ofxNUIDirectorNode::nodeInit();
}

ofxNUIDirectorNode::ofxNUIDirectorNode(vector<ofxNUINode*> _nodes)
{
    ofxNUIDirectorNode::nodeInit();
    setup(_nodes);
}

//------------------------------

void ofxNUIDirectorNode::nodeInit()
{
    positionDurationMS = 750;
    targetDurationMS = 1000;
    delayMS = 0;
    mouseIsOnASuperCanvas = false;
    activeNode = NULL;
    prevActiveNode = NULL;
    closestChild = NULL;
    prevClosestChild = NULL;
    
    setActiveNode(this);
    setPrevActiveNode(getActiveNode());
    setActive(true);
    setHighlight(false);
    setNodePosition(ofVec3f(0.0f, 0.0f, 0.0f));
}

//------------------------------

void ofxNUIDirectorNode::setup(vector<ofxNUINode *> _nodes)
{
    getChildren()->reserve(_nodes.size());
    for (int i=0; i < _nodes.size(); i++) {
        addChild(_nodes.at(i));
    }
    setNodeLabel(getName());
    setColorScheme(&coreColorScheme);
    setShapeType(OFXNUINODE_SHAPE_SPHERE);
    setupGL();
    setupLight();
    setupCam();
    updateNode();
    updateChildren();
    setCamera(&cam);
}

//------------------------------

void ofxNUIDirectorNode::setupGL()
{
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableSmoothing();
}

//------------------------------

void ofxNUIDirectorNode::setupCam()
{
    cam.setPosition(getPosition().x,
                    getPosition().y,
                    getPosition().z + (OFXNUINODE_LAYOUT_RADIUS * 1.8f));
    cam.setTarget(getPosition());
    cam.setDistance(OFXNUINODE_LAYOUT_RADIUS * 1.8f);
}

//------------------------------

void ofxNUIDirectorNode::setupLight()
{
    ofEnableLighting();
    ambientLight.setAmbientColor(ofColor(150, 190, 170, 255));
    ambientLight.setDiffuseColor(ofColor(150,150,150));
}

//------------------------------

void ofxNUIDirectorNode::refresh()
{
    setColorScheme(&coreColorScheme);
    setShapeType(OFXNUINODE_SHAPE_SPHERE);
    setCamera(&cam);
    getActiveNode()->setActive(true);
}

//------------------------------

void ofxNUIDirectorNode::setActiveNode(ofxNUINode *_activeNode)
{
    activeNode = _activeNode;
}

//------------------------------

void ofxNUIDirectorNode::setPrevActiveNode(ofxNUINode *_prevActiveNode)
{
    prevActiveNode = _prevActiveNode;
}

//------------------------------

void ofxNUIDirectorNode::setClosestChild(ofxNUINode *_closestChild)
{
    closestChild = _closestChild;
}

//------------------------------

void ofxNUIDirectorNode::setPrevClosestChild(ofxNUINode *_prevClosestChild)
{
    prevClosestChild = _prevClosestChild;
}

//------------------------------

ofxNUINode* ofxNUIDirectorNode::getActiveNode()
{
    return activeNode;
}

//------------------------------

ofxNUINode* ofxNUIDirectorNode::getPrevActiveNode()
{
    return prevActiveNode;
}

//------------------------------

ofxNUINode* ofxNUIDirectorNode::getClosestChild()
{
    return closestChild;
}

//------------------------------

ofxNUINode* ofxNUIDirectorNode::getPrevClosestChild()
{
    return prevClosestChild;
}

//------------------------------

void ofxNUIDirectorNode::moveCamToActive()
{
    positionDurationMS = 1000;
    int posX, posY, posZ;
    int tarX, tarY, tarZ;
    
    if (activeNode->getNodeLayout() == OFXNUINODE_LAYOUT_LIST) {
        posX = activeNode->getNodePosition().x + OFXNUINODE_LAYOUT_RADIUS;
        posY = activeNode->getNodePosition().y - OFXNUINODE_LAYOUT_RADIUS * 0.5f;
        posZ = activeNode->getNodePosition().z + (OFXNUINODE_LAYOUT_RADIUS * 1.8f);
        tarX = posX;
        tarY = posY;
        tarZ = activeNode->getNodePosition().z;
    }
    
    else if (activeNode->getNodeType() == "ofxNUIWidgetNode") {
        widgetNode = dynamic_cast<ofxNUIWidgetNode*>(activeNode);
        posX = activeNode->getNodePosition().x
                + widgetNode->getCanvas()->getRect()->getHalfWidth() * 0.65f;
        posY = activeNode->getNodePosition().y
                - widgetNode->getCanvas()->getRect()->getHalfHeight() * 0.65f;
        posZ = activeNode->getNodePosition().z + (OFXNUINODE_LAYOUT_RADIUS * 1.8f);
        tarX = posX;
        tarY = posY;
        tarZ = activeNode->getNodePosition().z;
    }
    
    else if (getChildren()) {
        posX = activeNode->getNodePosition().x;
        posY = activeNode->getNodePosition().y;
        posZ = activeNode->getNodePosition().z + (OFXNUINODE_LAYOUT_RADIUS * 1.8f);
        tarX = activeNode->getNodePosition().x;
        tarY = activeNode->getNodePosition().y;
        tarZ = activeNode->getNodePosition().z;
    }
    
    tweenCamPosition.setParameters(1, easingQuad, ofxTween::easeOut,
                                   cam.getPosition().x, posX,
                                   positionDurationMS, delayMS);
    tweenCamPosition.addValue(cam.getPosition().y, posY);
    tweenCamPosition.addValue(cam.getPosition().z, posZ);
    
    tweenCamTarget.setParameters(2, easingExpo, ofxTween::easeOut,
                                 prevActiveNode->getPosition().x, tarX,
                                 targetDurationMS, delayMS);
    tweenCamTarget.addValue(prevActiveNode->getPosition().y, tarY);
    tweenCamTarget.addValue(prevActiveNode->getPosition().z, tarZ);
    
    tweenCamPosition.start();
    tweenCamTarget.start();
    
    positionIsTweening = true;
    targetIsTweening = true;
    
}

//------------------------------

void ofxNUIDirectorNode::updateCamTween()
{
    if (positionIsTweening) {
        cam.setPosition(ofVec3f(tweenCamPosition.update(),
                                tweenCamPosition.getTarget(1),
                                tweenCamPosition.getTarget(2)));
    }
    if (targetIsTweening) {
        cam.setTarget(ofVec3f(tweenCamTarget.update(),
                              tweenCamTarget.getTarget(1),
                              tweenCamTarget.getTarget(2)));
    }
}

//------------------------------

void ofxNUIDirectorNode::stopCamTween()
{
    positionIsTweening = false;
    targetIsTweening = false;
}

//------------------------------

bool ofxNUIDirectorNode::isMouseOnASuperCanvas()
{
    if (!closestChild) {
        return false;
    }
    
    if (closestChild->getNodeType() == "ofxNUIWidgetNode") {
        widgetNode = dynamic_cast<ofxNUIWidgetNode*>(closestChild);
        if (widgetNode->getCanvas()->isHit(ofGetMouseX(), ofGetMouseY())) {
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

//------------------------------

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
    
    if (closestChild != prevClosestChild) {
        prevClosestChild->setHighlight(false);
        closestChild->setHighlight(true);
        prevClosestChild = closestChild;
    }
}

//------------------------------

void ofxNUIDirectorNode::selectNode()
{
    
    ofVec2f mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());
    ofVec3f current = cam.worldToScreen(activeNode->ofNode::getPosition());
    int distance = current.distance(mouse);
    
    /* Select the parent as active node */
    if (distance < activeNode->getNodeRadius()*3.0f && activeNode->getParentNode()){
        selectParent();
        return;
    }
    
    current = cam.worldToScreen(closestChild->ofNode::getPosition());
    distance = current.distance(mouse);
    
    /* Select the child as active node */
    if (distance < closestChild->getNodeRadius() * 3.0f) {
        selectClosestChild();
        return;
    }
    
}

//------------------------------

void ofxNUIDirectorNode::selectParent()
{
    activeNode->setParentAsActive();
    setPrevActiveNode(getActiveNode());
    setActiveNode(getActiveNode()->getParentNode());
    
    moveCamToActive();
}

//------------------------------

void ofxNUIDirectorNode::selectClosestChild()
{
    activeNode->setChildAsActive(closestChild);
    setPrevActiveNode(getActiveNode());
    setActiveNode(getClosestChild());
    
    moveCamToActive();
}

//------------------------------

void ofxNUIDirectorNode::update()
{
    ofxNUINode::update();
    /* for (int i=0; i < getChildren()->size(); i++) {
        getChildren()->at(i)->update();
    } */
    
    updateCamTween();
}

//------------------------------

void ofxNUIDirectorNode::draw()
{
    
    ofBackground(10);
    
    /* 3D node system with cam and lighting. */
    ambientLight.enable();
    cam.begin();
    
    if (activeNode->getParentNode()) {
        activeNode->getParentNode()->customDraw();
    }
    else {
        activeNode->customDraw();
    }
    
    cam.end();
    ambientLight.disable();
    
    activeNode->customDraw2D();
    
}

//------------------------------

void ofxNUIDirectorNode::keyPressed(int key)
{
    
}

//------------------------------

void ofxNUIDirectorNode::mouseMoved(int x, int y )
{
    if (!isMouseOnASuperCanvas()) {
        findClosestChild();
    }
}

//------------------------------

void ofxNUIDirectorNode::mousePressed(int x, int y, int button)
{
    stopCamTween();
}

//------------------------------

void ofxNUIDirectorNode::mouseReleased(int x, int y, int button)
{
    if (!isMouseOnASuperCanvas() && button == 0) {
        selectNode();
    }
}

//------------------------------



//------------------------------



//------------------------------



//------------------------------



//------------------------------