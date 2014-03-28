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


#include "ofxNUINode.h"

//------------------------------

ofxNUINode::ofxNUINode()
: nodeLabel("")
, siblingPerc(0.f)
, parentNode(NULL)
, colorScheme(NULL)
, depth(0)
, depthFromActive(0)
, depthFromHighlighted(-1)
, nodeLayout(OFXNUINODE::LAYOUT_RADIAL)
, positionDepth(OFXNUINODE::LAYOUT_DEPTH)
, positionRadius(OFXNUINODE::LAYOUT_RADIUS)
, nodeRadius(OFXNUINODE::NODE_RADIUS)
, posTweenDurMs(OFXNUINODE::DEFAULT_POS_TWEEN_DURATION)
, posTweenDelMs(OFXNUINODE::DEFAULT_POS_TWEEN_DELAY)
, shapeType(OFXNUINODE::SHAPE_SPHERE)
, uniqueID(0)
, cam(NULL)
, active(false)
, highlight(false)
{
    
}

//------------------------------

void ofxNUINode::refresh()
{
    updateChildren();
    setColorScheme(getColorScheme());
    setShapeType(getShapeType());
    setCamera(getCam());
}

//------------------------------

void ofxNUINode::addChild(ofxNUINode *child)
{
    if (child->getParentNode()) {
        cloneChildren.reserve(getChildren()->capacity());
        cloneChildren.push_back(ofxNUINode(*child));
        child = &cloneChildren.back();
    }
    children.push_back(child);
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        if (child->nodeLabel == "") child->setNodeLabel(child->getName());
        child->setNumOfSiblings(children.size());
        child->setSiblingPerc(i);
        child->setParentNode(this);
    }
}

//------------------------------

void ofxNUINode::addChild(ofxNUINode *_child, int num)
{
    _child->setNodeLabel(_child->getName() + " " + ofToString(num));
    addChild(_child);
}

//------------------------------

void ofxNUINode::addChild(ofxNUINode *_child, string _name)
{
    _child->setNodeLabel(_name);
    addChild(_child);
}

//------------------------------

void ofxNUINode::addChildList(vector<ofxNUINode *> childList, string _name, int _layout)
{
    listParents.reserve(20);
    listParents.push_back(ofxNUINode());
    ofxNUINode *child = &listParents.back();
    child->setNodeLabel(_name);
    child->setNodeLayout(_layout);
    addChild(child);
    child->getChildren()->reserve(childList.size());
    for (int i=0; i < childList.size(); i++)
        child->addChild(childList[i], i+1);
}

//------------------------------

void ofxNUINode::updateChildren()
{
    for (auto &child : children) {
        child->setNumOfSiblings(children.size());
        child->updateNode();
        child->updateChildren();
    }
}

//------------------------------

void ofxNUINode::updateNode()
{
    updateNodeDepth();
    updateNodePosition();
    updateNodeColors();
}

//------------------------------

void ofxNUINode::updateNodeDepth()
{
    if (isActive()) {
        depthFromActive = 0;
        if (getParentNode()) {
            getParentNode()->depthFromActive = -1;
            depth = getParentNode()->depth + 1;
        }
    }
    else if (!isActive() && getParentNode()) {
        depthFromActive = getParentNode()->depthFromActive >= 0 ? getParentNode()->depthFromActive+1 : getParentNode()->depthFromActive-1;
        depth = getParentNode()->depth + 1;
    }
    else if (!isActive() && !getParentNode()) {
        depth = 0;
        if (getChildren()->size()) depthFromActive = getChildren()->front()->depthFromActive -1;
    }
}

//------------------------------

void ofxNUINode::updateNodePosition()
{
    if (!getParentNode()) return;
    
    if (getParentNode()->isActive()) {
        positionDepth = 0;
        positionRadius = OFXNUINODE::LAYOUT_RADIUS * 3.0f / 4.0f;
    }
    else if (isActive()) {
        positionDepth = OFXNUINODE::LAYOUT_DEPTH * 4.0f;
        positionRadius = OFXNUINODE::LAYOUT_RADIUS;
    }
    else {
        positionDepth = OFXNUINODE::LAYOUT_DEPTH;
        positionRadius = OFXNUINODE::LAYOUT_RADIUS;
    }
    
    if (getParentNode()->getParentNode()) {
        if (getParentNode()->getParentNode()->isActive()) {
            positionDepth = OFXNUINODE::LAYOUT_DEPTH * 2.0f;
            positionRadius = OFXNUINODE::LAYOUT_RADIUS;
        }
    }
    
    /* Get Position */
    switch (getParentNode()->getNodeLayout()) {
        case OFXNUINODE::LAYOUT_RADIAL: updateNodePositionRadial(); break;
        case OFXNUINODE::LAYOUT_SPIRAL: updateNodePositionSpiral(); break;
        case OFXNUINODE::LAYOUT_LIST: updateNodePositionList(); break;
        case OFXNUINODE::LAYOUT_GRID: updateNodePositionGrid(); break;
        default: updateNodePositionRadial(); break;
    }
    
    /* Set node orientation and position */
    position += getParentNode()->getNodePosition();
    setOrientation(position);
    setNodePosition(position);
}

//------------------------------

void ofxNUINode::updateNodePositionRadial()
{
    float x = getSiblingPerc() + getParentNode()->getSiblingPerc() + 0.25f;
    position = ofVec3f(sin(TWO_PI * x) * positionRadius, cos(TWO_PI * x) * positionRadius, positionDepth);
}

//------------------------------

void ofxNUINode::updateNodePositionSpiral()
{
    if (getNumOfSiblings() >= OFXNUINODE::SPIRAL_DEPTH_THRESHHOLD) {
        float x = (getSiblingPerc()/(1.0f/(float)getNumOfSiblings())) * OFXNUINODE::SPIRAL_DEPTH_THRESHHOLD_PERC + getParentNode()->getSiblingPerc() + 0.75f;
        position = ofVec3f(sin(TWO_PI * x) * positionRadius, cos(TWO_PI * x) * positionRadius, positionDepth - (getSiblingPerc() / (1.0f/(float)getNumOfSiblings())) * 50.0f);
    }
    else updateNodePositionRadial();
}

//------------------------------

void ofxNUINode::updateNodePositionList()
{
    position = ofVec3f(positionRadius / 1.5f, -30 * getSiblingNum(), positionDepth);
}

//------------------------------

void ofxNUINode::updateNodePositionGrid()
{
    // Not yet implemented.
}

//------------------------------

void ofxNUINode::updateNodeColors()
{
    if (!colorScheme) return;
    updateShapeColor();
    updateLineColor();
    updateNameColor();
}

//------------------------------

void ofxNUINode::updateShapeColor()
{
    //if (!shape) return;
    if (colorScheme) colorScheme->getLineColor();
    /* Set shape size and position */
    sphere.setRadius(getNodeRadius()); //shape->setRadius(getNodeRadius());
    
    if (!getParentNode())
        shapeColor = isActive() ? colorScheme->getShapeColorActive() : colorScheme->getShapeColorActiveDepth(getDepthFromActive());
    
    /* If node is currently active */
    else if (isActive())
        shapeColor = colorScheme->getShapeColorActive();
    
    /* If node is currently highlighted */
    else if (isHighlighted())
        shapeColor = colorScheme->getShapeColorHighlighted();
    
    /* If parent of node is currently active */
    else if (getParentNode()->isActive())
        shapeColor = colorScheme->getShapeColorActiveParent();
    
    /* If is derived from highlighted node */
    else if (depthFromHighlighted > 0)
        shapeColor = colorScheme->getShapeColorHighlightDepth(getDepthFromHighlighted());
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0)
        shapeColor = colorScheme->getShapeColorActiveDepth(getDepthFromActive());
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0)
        shapeColor = colorScheme->getShapeColorActiveDepth(getDepthFromActive());
    
    //shapeColor = ofColor(red, grn, blu, alpha);
    //shape->setColor(shapeColor);
    sphere.setColor(shapeColor);
}

//------------------------------

void ofxNUINode::updateLineColor()
{
    if (!getParentNode()) return;
    
    /* If node is currently active */
    if (isActive())
        lineColor = colorScheme->getLineColorActive();
    
    /* If node is currently highlighted */
    else if (isHighlighted())
        lineColor = colorScheme->getLineColorHighlighted();
    
    /* If parent node is active */
    else if (getParentNode()->isActive())
        lineColor = colorScheme->getLineColorActiveParent();
    
    /* If is derived from highlighted node */
    else if (getDepthFromHighlighted() > 0)
        lineColor = colorScheme->getLineColorHighlightDepth(getDepthFromHighlighted());
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0)
        lineColor = colorScheme->getLineColorActiveDepth(getDepthFromActive());
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0)
        lineColor = colorScheme->getLineColorActiveDepth(getDepthFromActive());
    
    else lineColor = colorScheme->getLineColor();
}

//------------------------------

void ofxNUINode::updateNameColor()
{
    nameColor = (isHighlighted() || isActive()) ? colorScheme->getNameColorActive() : colorScheme->getNameColor();
}

//------------------------------

void ofxNUINode::setCamera(ofEasyCam *_cam)
{
    cam = _cam;
    for (auto &child : children) child->setCamera(cam);
}

//------------------------------

void ofxNUINode::setColorScheme(ofxNUIColorScheme *_colorScheme)
{
    colorScheme = _colorScheme;
    for (auto &child : children) child->setColorScheme(colorScheme);
}

//------------------------------

void ofxNUINode::setNodeLayout(int _layout)
{
    nodeLayout = _layout;
}

//------------------------------

void ofxNUINode::setNodeLabel(string _nodeLabel)
{
    nodeLabel = _nodeLabel;
}

//------------------------------

void ofxNUINode::setNodePosition(ofVec3f _position)
{
    positionJN = _position;
    setPositionTween(_position);
}

//------------------------------

void ofxNUINode::setNodeRadius(int _nodeRadius)
{
    nodeRadius = _nodeRadius;
}

//------------------------------

void ofxNUINode::setNumOfSiblings(int _numOfSiblings)
{
    numOfSiblings = _numOfSiblings;
}

//------------------------------

void ofxNUINode::setParentNode(ofxNUINode *_parent)
{
    parentNode = _parent;
    ofNode::setParent(*parentNode);
}

//------------------------------

void ofxNUINode::setPositionTween(ofVec3f _position)
{
    tweenNodePos.setParameters(1, easingExpo, ofxTween::easeOut, getPosition().x, _position.x, posTweenDurMs, posTweenDelMs);
    tweenNodePos.addValue(getPosition().y, _position.y);
    tweenNodePos.addValue(getPosition().z, _position.z);
    tweenNodePos.start();
}

//------------------------------

void ofxNUINode::setShapeType(int _shapeType)
{
    shapeType = _shapeType;
    if (shapeType == OFXNUINODE::SHAPE_SPHERE) {
        // Not yet implemented.
    }
}

//------------------------------

void ofxNUINode::setSiblingPerc(int _siblingNum)
{
    siblingNum = _siblingNum;
    siblingPerc = (float)siblingNum / (float)numOfSiblings;
}

//------------------------------

void ofxNUINode::setUniqueID(int _uniqueID)
{
    uniqueID = _uniqueID;
}

//------------------------------

ofEasyCam* ofxNUINode::getCam()
{
    return cam;
}

vector<ofxNUINode*>* ofxNUINode::getChildren()
{
    return &children;
}

ofxNUIColorScheme* ofxNUINode::getColorScheme()
{
    return colorScheme;
}

vector<ofxNUINode>* ofxNUINode::getListParents()
{
    return &listParents;
}

int ofxNUINode::getDepth()
{
    return depth;
}

int ofxNUINode::getDepthFromActive()
{
    return depthFromActive;
}

int ofxNUINode::getDepthFromHighlighted()
{
    return depthFromHighlighted;
}

int ofxNUINode::getNodeLayout()
{
    return nodeLayout;
}

string ofxNUINode::getNodeLabel()
{
    return nodeLabel;
}

ofVec3f ofxNUINode::getNodePosition()
{
    return positionJN;
}

int ofxNUINode::getNodeRadius()
{
    return nodeRadius;
}

int ofxNUINode::getNumOfSiblings()
{
    return numOfSiblings;
}

ofxNUINode* ofxNUINode::getParentNode()
{
    return parentNode;
}

int ofxNUINode::getShapeType()
{
    return shapeType;
}

int ofxNUINode::getSiblingNum()
{
    return siblingNum;
}

float ofxNUINode::getSiblingPerc()
{
    return siblingPerc;
}

int ofxNUINode::getUniqueID()
{
    return uniqueID;
}

//------------------------------

void ofxNUINode::update()
{
    if (depthFromActive > 4) return;
    for (auto &child : children) child->update();
    if (depthFromActive < 0) return;
    else if (depthFromActive > 3)
        if (depthFromHighlighted > 3 || depthFromHighlighted < 0) return;
    if (isActive() || isHighlighted()) sphere.update(); //shape->update();
    if (tweenNodePos.isRunning() && getParentNode()) updateTween();
}

//------------------------------

void ofxNUINode::updateTween()
{
    ofVec3f tempTweenNodePos(tweenNodePos.update(), tweenNodePos.getTarget(1), tweenNodePos.getTarget(2));
    setPosition(tempTweenNodePos); // Update Node Position
    //shape->setPosition(tempTweenNodePos);
    sphere.setPosition(tempTweenNodePos);
    /* Setup line */
    line.clear();
    line.addVertex(tempTweenNodePos);
    line.addVertex(getParentNode()->getPosition());
}

//------------------------------

void ofxNUINode::customDraw()
{
    if (depthFromActive > 4) return;
    for (auto &child : children) child->customDraw();
    if (depthFromActive < 0) return;
    else if (depthFromActive > 3)
        if (depthFromHighlighted > 3 || depthFromHighlighted < 0) return;
    ofEnableAlphaBlending();
    drawShape();
    drawLine();
    drawName();
    ofDisableAlphaBlending();
}

//------------------------------

void ofxNUINode::customDraw2D()
{
    for (auto &child : children) child->customDraw2D();
}

//------------------------------

void ofxNUINode::drawLine()
{
    if (!getParentNode()) return;
    ofSetColor(lineColor);
    line.draw();
}

//------------------------------

void ofxNUINode::drawName()
{
    
    /* Only draw if depthFromActive < 1 or parent is highlighted */
    if (getParentNode() == NULL && depthFromActive > 1) return;
    else if (depthFromActive < 0) return;
    else if (getParentNode() && depthFromActive > 1)
        if (getParentNode()->isHighlighted() == false) return;
    
    ofSetColor(nameColor);
    ofDrawBitmapString(nodeLabel, getPosition().x + getNodeRadius() + 5, getPosition().y, getPosition().z);
    
}

//------------------------------

void ofxNUINode::drawShape()
{
    //shape->draw();
    sphere.draw();
}

//------------------------------

bool ofxNUINode::isActive()
{
    return active;
}

//------------------------------

void ofxNUINode::setActive(bool _isActive)
{
    active = _isActive;
    if (isActive()) {
        depthFromActive = 0;
        setHighlight(false);
        if (getParentNode())
            getParentNode()->depthFromActive = -1;
    }
    else if (getParentNode())
        if (!getParentNode()->isActive())
            depthFromActive = -1;
}

//------------------------------

void ofxNUINode::setChildAsActive(ofxNUINode *_child)
{
    setActive(false);
    _child->setActive(true);
    _child->updateNode();
    updateNode();
    updateChildren();
}

//------------------------------

void ofxNUINode::setParentAsActive()
{
    setActive(false);
    getParentNode()->setActive(true);
    getParentNode()->updateNode();
    getParentNode()->updateChildren();
}

//------------------------------

void ofxNUINode::toggleActive()
{
    active = abs(active-1);
    if (isActive()) {
        depthFromActive = 0;
        setHighlight(false);
    }
    else if (getParentNode())
        if (!getParentNode()->isActive())
            depthFromActive = -1;
}

//------------------------------

bool ofxNUINode::isHighlighted()
{
    return highlight;
}

//------------------------------

void ofxNUINode::setHighlight(bool _isHighlighted)
{
    highlight = _isHighlighted;
    if (isHighlighted()) {
        depthFromHighlighted = 0;
        setHighlightDepth();
    }
    else resetHighlightDepth();
}

//------------------------------

void ofxNUINode::setHighlightDepth()
{
    if (!isHighlighted())
        depthFromHighlighted = getParentNode()->depthFromHighlighted + 1;
    updateNodeColors();
    for (auto &child : children) child->setHighlightDepth();
}

//------------------------------

void ofxNUINode::resetHighlightDepth()
{
    if (getParentNode())
        depthFromHighlighted = getParentNode()->isActive() ? -1 : getParentNode()->getDepthFromHighlighted() - 1;
    updateNodeColors();
    for (auto &child : children) child->resetHighlightDepth();
}

//------------------------------

void ofxNUINode::toggleHighlight()
{
    highlight = abs(highlight-1);
    if (isHighlighted() == true) {
        depthFromHighlighted = 0;
        setHighlightDepth();
    }
    else resetHighlightDepth();
}

//------------------------------



//------------------------------



//------------------------------



//------------------------------



//------------------------------



