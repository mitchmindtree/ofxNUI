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

//--------------------------------------------------------------------------------//
// INITIALISE
//--------------------------------------------------------------------------------//

void ofxNUINode::init()
{
    nodeLabel = "";
    siblingPerc = 0.0f;
    parentNode = NULL;
    colorScheme = NULL;
    
    depth = 0;
    depthFromActive = 0;
    depthFromHighlighted = -1;
    //shape = NULL;
    
    nodeLayout = OFXNUINODE_LAYOUT_RADIAL;
    positionDepth = OFXNUINODE_LAYOUT_DEPTH;
    positionRadius = OFXNUINODE_LAYOUT_RADIUS;
    
    nodeRadius = OFXNUINODE_NODE_RADIUS;
    
    posTweenDurMs = OFXNUINODE_DEFAULT_POS_TWEEN_DURATION;
    posTweenDelMs = OFXNUINODE_DEFAULT_POS_TWEEN_DELAY;
    
    setShapeType(OFXNUINODE_SHAPE_SPHERE);
    
    setGlobalPosition(0.0f, 0.0f, 0.0f);
    
    baseRed = 135;
    baseGrn = 135;
    baseBlu = 160;
    baseAlpha = 180;
    
    baseLineColor = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseShapeColor = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseNameColor = ofColor(baseRed+25,baseGrn+25,baseBlu, 250);
    
    lineColor = baseLineColor;
    shapeColor = baseShapeColor;
    nameColor = baseNameColor;
    
    //active = false;
    //highlight = false;
    
    setActive(false);
    setHighlight(false);
    
}

//--------------------------------------------------------------------------------//
// ADD CHILD
//--------------------------------------------------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child)
{
    
    children.push_back(_child);
    
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        if (child->nodeLabel == "") {
            child->setNodeLabel(child->getNodeName());
        }
        child->setNumOfSiblings(children.size());
        child->setSiblingPerc(i);
        child->setParentNode(this);
    }
    
    /* Set new positions for children */
    updateChildren();
    
}

//----------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child, int num)
{
    _child->setNodeLabel(_child->getNodeName() + " " + ofToString(num));
    addChild(_child);
}

//----------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child, string _name)
{
    _child->setNodeLabel(_name);
    addChild(_child);
}

//--------------------------------------------------------------------------------//
// ADD CHILD LIST
//--------------------------------------------------------------------------------//

void ofxNUINode::addChildList(vector<ofxNUINode *> childList, string _name)
{
    
    ofxNUINode *listParent = new ofxNUINode;
    listParent->setNodeLabel(_name);
    addChild(listParent);
    
    listParent->getChildren()->reserve(childList.size());
    for (int i=0; i < childList.size(); i++) {
        listParent->addChild(childList.at(i), i+1);
    }
    
}

//--------------------------------------------------------------------------------//
// SET CHILDREN POSITIONS
//--------------------------------------------------------------------------------//

void ofxNUINode::updateChildren()
{
    
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        child->setNumOfSiblings(children.size());
        child->updateNode();
        child->updateChildren();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE JEN NODE (WITH SIBLING RATIO)
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNode()
{
    updateNodeDepth();
    updateNodePosition();
    updateNodeColors();
}

//--------------------------------------------------------------------------------//
// UPDATE NODE DEPTH
//--------------------------------------------------------------------------------//

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
        if (getParentNode()->depthFromActive >= 0) {
            depthFromActive = getParentNode()->depthFromActive + 1;
        }
        else if (getParentNode()->depthFromActive < 0) {
            depthFromActive = getParentNode()->depthFromActive -1;
        }
        depth = getParentNode()->depth + 1;
    }
    
    else if (!isActive() && !getParentNode()) {
        depth = 0;
        if (getChildren()->size()) {
            depthFromActive = getChildren()->at(0)->depthFromActive -1;
        }
    }
    
    /* cout << ofToString(getNodeLabel()) + " | depth = " + ofToString(depth) + " | depthFromActive = " + ofToString(depthFromActive) + " | depthFromHighlighted = " + ofToString(depthFromHighlighted) << endl; */
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePosition()
{
    
    if (!getParentNode()) { return; }
    
    if (getParentNode()->isActive()) {
        positionDepth = 0;
        positionRadius = OFXNUINODE_LAYOUT_RADIUS * 3.0f / 4.0f;
    }
    else if (isActive()) {
        positionDepth = OFXNUINODE_LAYOUT_DEPTH * 4.0f;
        positionRadius = OFXNUINODE_LAYOUT_RADIUS;
    }
    else {
        positionDepth = OFXNUINODE_LAYOUT_DEPTH;
        positionRadius = OFXNUINODE_LAYOUT_RADIUS;
    }
    
    if (getParentNode()->getParentNode()) {
        if (getParentNode()->getParentNode()->isActive()) {
            positionDepth = OFXNUINODE_LAYOUT_DEPTH * 2.0f;
            positionRadius = OFXNUINODE_LAYOUT_RADIUS;
        }
    }
    
    /* Get Position */
    switch (getParentNode()->getNodeLayout()) {
        case OFXNUINODE_LAYOUT_RADIAL: updateNodePositionRadial(); break;
        case OFXNUINODE_LAYOUT_SPIRAL: updateNodePositionSpiral(); break;
        case OFXNUINODE_LAYOUT_LIST: updateNodePositionList(); break;
        case OFXNUINODE_LAYOUT_GRID: updateNodePositionGrid(); break;
        default: updateNodePositionRadial(); break;
    }
    
    /* Set node orientation and position */
    position += getParentNode()->getNodePosition();
    setOrientation(position);
    setNodePosition(position);
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION RADIAL
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionRadial()
{
    //algebraic.setup();
    float x = getSiblingPerc() + getParentNode()->getSiblingPerc() + 0.25f;
    position = ofVec3f(sin(TWO_PI * x) * positionRadius,
                       cos(TWO_PI * x) * positionRadius,
                       positionDepth);
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION SPIRAL
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionSpiral()
{
    if (getNumOfSiblings() >= OFXNUINODE_SPIRAL_DEPTH_THRESHHOLD) {
        float x = (getSiblingPerc()/(1.0f/(float)getNumOfSiblings()))
                    * OFXNUINODE_SPIRAL_DEPTH_THRESHHOLD_PERC
                    + getParentNode()->getSiblingPerc() + 0.75f;
        position = ofVec3f(sin(TWO_PI * x) * positionRadius,
                           cos(TWO_PI * x) * positionRadius,
                           positionDepth
                           - (getSiblingPerc() / (1.0f/(float)getNumOfSiblings()))
                           * 50.0f);
    }
    else {
        updateNodePositionRadial();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION LIST
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionList()
{
    position = ofVec3f(positionRadius / 1.5f, -30 * getSiblingNum(), positionDepth);
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION GRID
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionGrid()
{
    
}

//--------------------------------------------------------------------------------//
// UPDATE COLOURS
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodeColors()
{
    if (!colorScheme) { return; }
    updateShapeColor();
    updateLineColor();
    updateNameColor();
}

//--------------------------------------------------------------------------------//
// UPDATE AND SET SHAPE COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::updateShapeColor()
{
    
    //if (!shape) { return; }
    if (colorScheme) {
        colorScheme->getLineColor();
    }
    /* Set shape size and position */
    //shape->setRadius(getNodeRadius());
    sphere.setRadius(getNodeRadius());
    
    if (!getParentNode()) {
        if (isActive()) {
            shapeColor = colorScheme->getShapeColorActive();
        }
        else {
            shapeColor =colorScheme->getShapeColorActiveDepth(getDepthFromActive());
        }
    }
    
    /* If node is currently active */
    else if (isActive()) {
        shapeColor = colorScheme->getShapeColorActive();
    }
    
    /* If node is currently highlighted */
    else if (isHighlighted()) {
        shapeColor = colorScheme->getShapeColorHighlighted();
    }
    
    /* If parent of node is currently active */
    else if (getParentNode()->isActive()) {
        shapeColor = colorScheme->getShapeColorActiveParent();
    }
    
    /* If is derived from highlighted node */
    else if (depthFromHighlighted > 0) {
        shapeColor =
            colorScheme->getShapeColorHighlightDepth(getDepthFromHighlighted());
    }
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0) {
        shapeColor = colorScheme->getShapeColorActiveDepth(getDepthFromActive());
    }
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0) {
        shapeColor = colorScheme->getShapeColorActiveDepth(getDepthFromActive());
    }
    
    //shapeColor = ofColor(red, grn, blu, alpha);
    //shape->setColor(shapeColor);
    sphere.setColor(shapeColor);
    
}

//--------------------------------------------------------------------------------//
// UPDATE AND SET LINE COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::updateLineColor()
{
    
    if (!getParentNode()) { return; }
    
    /* If node is currently active */
    if (isActive()) {
        lineColor = colorScheme->getLineColorActive();
    }
    
    /* If node is currently highlighted */
    else if (isHighlighted()) {
        lineColor = colorScheme->getLineColorHighlighted();
    }
    
    /* If parent node is active */
    else if (getParentNode()->isActive()) {
        lineColor = colorScheme->getLineColorActiveParent();
    }
    
    /* If is derived from highlighted node */
    else if (getDepthFromHighlighted() > 0) {
        lineColor =
        colorScheme->getLineColorHighlightDepth(getDepthFromHighlighted());
    }
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0) {
        lineColor = colorScheme->getLineColorActiveDepth(getDepthFromActive());
    }
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0) {
        lineColor = colorScheme->getLineColorActiveDepth(getDepthFromActive());
    }
    
    else {
        lineColor = colorScheme->getLineColor();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE AND SET NAME COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNameColor()
{
    
    if (isHighlighted() || isActive()) {
        nameColor = colorScheme->getNameColorActive();
    }
    else {
        nameColor = colorScheme->getNameColor();
    }
    
}

//--------------------------------------------------------------------------------//
// SET COLOR SCHEME
//--------------------------------------------------------------------------------//

void ofxNUINode::setColorScheme(ofxNUIColorScheme *_colorScheme)
{
    colorScheme = _colorScheme;
    for (int i=0; i < getChildren()->size(); i++) {
        getChildren()->at(i)->setColorScheme(colorScheme);
    }
}

//--------------------------------------------------------------------------------//
// SET NODE LAYOUT
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodeLayout(int _layout)
{
    nodeLayout = _layout;
}

//--------------------------------------------------------------------------------//
// SET NODE NAME
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodeLabel(string _nodeLabel)
{
    nodeLabel = _nodeLabel;
}

//--------------------------------------------------------------------------------//
// SET POSITION OF ofxNUINode
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodePosition(ofVec3f _position)
{
    positionJN = _position;
    setPositionTween(_position);
}

//--------------------------------------------------------------------------------//
// SET NODE RADIUS
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodeRadius(int _nodeRadius)
{
    nodeRadius = _nodeRadius;
}

//--------------------------------------------------------------------------------//
// SET NUMBER OF SIBLINGS
//--------------------------------------------------------------------------------//

void ofxNUINode::setNumOfSiblings(int _numOfSiblings)
{
    numOfSiblings = _numOfSiblings;
}

//--------------------------------------------------------------------------------//
// SET PARENT NODE
//--------------------------------------------------------------------------------//

void ofxNUINode::setParentNode(ofxNUINode *_parent)
{
    parentNode = _parent;
    ofNode::setParent(*parentNode);
}

//--------------------------------------------------------------------------------//
// SET POSITION VIA TWEEN
//--------------------------------------------------------------------------------//

void ofxNUINode::setPositionTween(ofVec3f _position)
{
    tweenNodePos.setParameters(1, easingExpo, ofxTween::easeOut,
                               getPosition().x, _position.x,
                               posTweenDurMs, posTweenDelMs);
    tweenNodePos.addValue(getPosition().y, _position.y);
    tweenNodePos.addValue(getPosition().z, _position.z);
    tweenNodePos.start();
}

//--------------------------------------------------------------------------------//
// SET SHAPE TYPE
//--------------------------------------------------------------------------------//

void ofxNUINode::setShapeType(int _shapeType)
{
    shapeType = _shapeType;
    if (shapeType == OFXNUINODE_SHAPE_SPHERE) {
        //shape = &sphere;
    }
}

//--------------------------------------------------------------------------------//
// SET SIBLING PERCENTAGE
//--------------------------------------------------------------------------------//

void ofxNUINode::setSiblingPerc(int _siblingNum)
{
    siblingNum = _siblingNum;
    siblingPerc = (float)siblingNum / (float)numOfSiblings;
}

//--------------------------------------------------------------------------------//
// GET CHILDREN
//--------------------------------------------------------------------------------//

vector<ofxNUINode*>* ofxNUINode::getChildren()
{
    return &children;
}

//--------------------------------------------------------------------------------//
// GET DEPTH
//--------------------------------------------------------------------------------//

int ofxNUINode::getDepth()
{
    return depth;
}

//--------------------------------------------------------------------------------//
// GET ACTIVE DEPTH
//--------------------------------------------------------------------------------//

int ofxNUINode::getDepthFromActive()
{
    return depthFromActive;
}

//--------------------------------------------------------------------------------//
// GET HIGHLIHGT DEPTH
//--------------------------------------------------------------------------------//

int ofxNUINode::getDepthFromHighlighted()
{
    return depthFromHighlighted;
}

//--------------------------------------------------------------------------------//
// GET NODE LAYOUT
//--------------------------------------------------------------------------------//

int ofxNUINode::getNodeLayout()
{
    return nodeLayout;
}

//--------------------------------------------------------------------------------//
// RETURN NODE NAME
//--------------------------------------------------------------------------------//

string ofxNUINode::getNodeLabel()
{
    return nodeLabel;
}

//--------------------------------------------------------------------------------//
// GET POSITION OF ofxNUINode
//--------------------------------------------------------------------------------//

ofVec3f ofxNUINode::getNodePosition()
{
    return positionJN;
}

//--------------------------------------------------------------------------------//
// GET NODE RADIUS
//--------------------------------------------------------------------------------//

int ofxNUINode::getNodeRadius()
{
    return nodeRadius;
}

//--------------------------------------------------------------------------------//
// GET NUMBER OF SIBLINGS
//--------------------------------------------------------------------------------//

int ofxNUINode::getNumOfSiblings()
{
    return numOfSiblings;
}

//--------------------------------------------------------------------------------//
// GET PARENT
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUINode::getParentNode()
{
    return parentNode;
}

//--------------------------------------------------------------------------------//
// GET SHAPE TYPE
//--------------------------------------------------------------------------------//

int ofxNUINode::getShapeType()
{
    return shapeType;
}

//--------------------------------------------------------------------------------//
// GET SIBLING NUMBER (ID)
//--------------------------------------------------------------------------------//

int ofxNUINode::getSiblingNum()
{
    return siblingNum;
}

//--------------------------------------------------------------------------------//
// GET SIBLING PERCENTAGE
//--------------------------------------------------------------------------------//

float ofxNUINode::getSiblingPerc()
{
    return siblingPerc;
}

//--------------------------------------------------------------------------------//
// UPDATE
//--------------------------------------------------------------------------------//

void ofxNUINode::update()
{
    
    for (int i=0; i < children.size(); i++) {
        children.at(i)->update();
    }
    
    if (depthFromHighlighted > 2 && depthFromActive > 3) { return; }
    
    //shape->update();
    sphere.update();
    
    if (tweenNodePos.isRunning()) {
        updateTween();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE TWEEN
//--------------------------------------------------------------------------------//

void ofxNUINode::updateTween()
{
    ofVec3f tempTweenNodePos = ofVec3f(tweenNodePos.update(),
                                       tweenNodePos.getTarget(1),
                                       tweenNodePos.getTarget(2));
    
    /* Update Node Position */
    setPosition(tempTweenNodePos);
    //shape->setPosition(tempTweenNodePos);
    sphere.setPosition(tempTweenNodePos);
    /* Setup line */
    line.clear();
    line.addVertex(tempTweenNodePos);
    line.addVertex(getParentNode()->getPosition());
}

//--------------------------------------------------------------------------------//
// CUSTOM DRAW NODE
//--------------------------------------------------------------------------------//

void ofxNUINode::customDraw()
{
    
    /* If there are children... */
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        child->customDraw();
    }
    
    /* if (depthFromHighlighted > 2 && depthFromActive > 3) { return; }
    else if (depthFromActive < 0) { return; } */
    
    if (depthFromActive < 0) { return; }
    else if (depthFromActive > 3) {
        if (depthFromHighlighted > 3 || depthFromHighlighted < 0) { return; }
    }
    
    ofEnableAlphaBlending();
    drawShape();
    drawLine();
    drawName();
    ofDisableAlphaBlending();
    
}

//--------------------------------------------------------------------------------//
// DRAW LINE
//--------------------------------------------------------------------------------//

void ofxNUINode::drawLine()
{
    
    /* If there is parent... */
    if (getParentNode()) {
        ofSetColor(lineColor);
        line.draw();
    }
    
}

//--------------------------------------------------------------------------------//
// DRAW NAME
//--------------------------------------------------------------------------------//

void ofxNUINode::drawName()
{
    
    /* Only draw if depthFromActive < 1 or parent is highlighted */
    if (getParentNode() == NULL && depthFromActive > 1) { return; }
    else if (depthFromActive < 0) { return; }
    else if (getParentNode() && depthFromActive > 1) {
        if (getParentNode()->isHighlighted() == false) { return; }
    }
    
    ofSetColor(nameColor);
    ofDrawBitmapString(nodeLabel,   getPosition().x + getNodeRadius() + 5,
                                    getPosition().y,
                                    getPosition().z);
    
}

//--------------------------------------------------------------------------------//
// DRAW SHAPE
//--------------------------------------------------------------------------------//

void ofxNUINode::drawShape()
{
    //shape->draw();
    sphere.draw();
}

//--------------------------------------------------------------------------------//
// GET IS ACTIVE
//--------------------------------------------------------------------------------//

bool ofxNUINode::isActive()
{
    return active;
}

//--------------------------------------------------------------------------------//
// SET ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUINode::setActive(bool _isActive)
{
    
    active = _isActive;
    
    if (isActive()) {
        depthFromActive = 0;
        setHighlight(false);
        if (getParentNode()) {
            getParentNode()->depthFromActive = -1;
        }
    }
    else if (getParentNode()) {
        if (!getParentNode()->isActive()) {
            depthFromActive = -1;
        }
    }
    
}

//--------------------------------------------------------------------------------//
// SET CHILD NODE AS ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUINode::setChildAsActive(ofxNUINode *_child)
{
    setActive(false);
    _child->setActive(true);
    _child->updateNode();
    updateNode();
    updateChildren();
}

//--------------------------------------------------------------------------------//
// SET PARENT NODE AS ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUINode::setParentAsActive()
{
    setActive(false);
    getParentNode()->setActive(true);
    getParentNode()->updateNode();
    getParentNode()->updateChildren();
}

//--------------------------------------------------------------------------------//
// TOGGLE ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUINode::toggleActive()
{
    
    active = abs(active-1);
    
    if (isActive()) {
        depthFromActive = 0;
        setHighlight(false);
    }
    else if (getParentNode()) {
        if (!getParentNode()->isActive()) {
            depthFromActive = -1;
        }
    }
    
}

//--------------------------------------------------------------------------------//
// GET IS HIGHLIGHTED
//--------------------------------------------------------------------------------//

bool ofxNUINode::isHighlighted()
{
    return highlight;
}

//--------------------------------------------------------------------------------//
// SET HIGHLIHGTED
//--------------------------------------------------------------------------------//

void ofxNUINode::setHighlight(bool _isHighlighted)
{
    
    highlight = _isHighlighted;
    
    if (isHighlighted()) {
        depthFromHighlighted = 0;
        setHighlightDepth();
    }
    else {
        resetHighlightDepth();
    }
    
}

//--------------------------------------------------------------------------------//
// SET HIGHLIGHT DEPTH
//--------------------------------------------------------------------------------//

void ofxNUINode::setHighlightDepth()
{
    
    if (!isHighlighted()) {
        depthFromHighlighted = getParentNode()->depthFromHighlighted + 1;
    }
    
    updateNodeColors();
    
    for (int i=0; i < children.size(); i++) {
        children.at(i)->setHighlightDepth();
    }
    
}

//--------------------------------------------------------------------------------//
// RESET HIGHLIGHT DEPTH
//--------------------------------------------------------------------------------//

void ofxNUINode::resetHighlightDepth()
{
    
    if (getParentNode()) {
        if (getParentNode()->isActive()) {
            depthFromHighlighted = -1;
        }
        else {
            depthFromHighlighted = getParentNode()->getDepthFromHighlighted() - 1;
        }
    }
    
    updateNodeColors();
    
    for (int i=0; i < children.size(); i++) {
        children.at(i)->resetHighlightDepth();
    }
    
}

//--------------------------------------------------------------------------------//
// TOGGLE HIGHLIGHT
//--------------------------------------------------------------------------------//

void ofxNUINode::toggleHighlight()
{
    
    highlight = abs(highlight-1);
    
    if (isHighlighted() == true) {
        depthFromHighlighted = 0;
        setHighlightDepth();
    }
    else {
        resetHighlightDepth();
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



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//