//
//  ofxNUINode.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 10/12/2013.
//
//

#include "ofxNUINode.h"

//--------------------------------------------------------------------------------//
// SET NODE NAME
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodeName(string _nodeName)
{
    nodeName = _nodeName;
}

//--------------------------------------------------------------------------------//
// INITIALISE
//--------------------------------------------------------------------------------//

void ofxNUINode::init()
{
    nodeName = "";
    siblingPerc = 0.0f;
    parentNode = NULL;
    
    depth = 0;
    depthFromActive = 0;
    depthFromHighlighted = -1;
    
    setActive(false);
    setHighlight(false);
    hidden = false;
    
    nodeLayout = JEN_NODE_LAYOUT_RADIAL;
    positionDepth = JEN_NODE_DEPTH;
    positionRadius = JEN_NODE_RADIUS;
    
    posTweenDurMs = DEFAULT_POS_TWEEN_DURATION;
    posTweenDelMs = DEFAULT_POS_TWEEN_DELAY;
    
    setGlobalPosition(0.0f, 0.0f, 300.0f);
    
    baseRed = 135;
    baseGrn = 135;
    baseBlu = 160;
    baseAlpha = 180;
    
    baseLineColour = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseSphereColour = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseNameColour = ofColor(baseRed+25,baseGrn+25,baseBlu, 250);
    
    lineColour = baseLineColour;
    sphereColour = baseSphereColour;
    nameColour = baseNameColour;
    
    //getChildren()->reserve(JEN_MAX_NUM_OF_CHILDREN);
}

//--------------------------------------------------------------------------------//
// ADD CHILD
//--------------------------------------------------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child)
{
    
    children.push_back(_child);
    
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        if (child->nodeName == "") {
            child->setNodeName(child->getName());
        }
        child->setNumOfSiblings(children.size());
        child->setSiblingPerc(i);
        child->setParentJN(this);
    }
    
    /* Set new positions for children */
    updateChildren();
    
}

//----------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child, int num)
{
    _child->setNodeName(_child->getName() + " " + ofToString(num));
    addChild(_child);
}

//----------------------------------------//

void ofxNUINode::addChild(ofxNUINode *_child, string _name)
{
    _child->setNodeName(_name);
    addChild(_child);
}

//--------------------------------------------------------------------------------//
// ADD CHILD LIST
//--------------------------------------------------------------------------------//

void ofxNUINode::addChildList(vector<ofxNUINode *> childList, string _name)
{
    
    ofxNUINode *listParent = new ofxNUINode;
    listParent->setNodeName(_name);
    addChild(listParent);
    
    listParent->getChildren()->reserve(childList.size());
    for (int i=0; i < childList.size(); i++) {
        listParent->addChild(childList.at(i), i+1);
    }
    
}

//--------------------------------------------------------------------------------//
// SET PARENT NODE
//--------------------------------------------------------------------------------//

void ofxNUINode::setParentJN(ofxNUINode *_parent)
{
    parentNode = _parent;
    ofNode::setParent(*parentNode);
}

//--------------------------------------------------------------------------------//
// SET NUMBER OF SIBLINGS
//--------------------------------------------------------------------------------//

void ofxNUINode::setNumOfSiblings(int _numOfSiblings)
{
    numOfSiblings = _numOfSiblings;
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
// SET NODE LAYOUT
//--------------------------------------------------------------------------------//

void ofxNUINode::setNodeLayout(int _layout)
{
    nodeLayout = _layout;
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
// SET POSITION OF ofxNUINode
//--------------------------------------------------------------------------------//

void ofxNUINode::setPositionJN(ofVec3f _position)
{
    positionJN = _position;
    setPositionTween(_position);
}

//--------------------------------------------------------------------------------//
// SET CHILDREN POSITIONS
//--------------------------------------------------------------------------------//

void ofxNUINode::updateChildren()
{
    
    for (int i=0; i < children.size(); i++) {
        child = children.at(i);
        child->setNumOfSiblings(children.size());
        child->updateofxNUINode();
        child->updateChildren();
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE JEN NODE (WITH SIBLING RATIO)
//--------------------------------------------------------------------------------//

void ofxNUINode::updateofxNUINode()
{
    
    updateNodeDepth();
    updateNodePosition();
    updateNodeColours();
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE DEPTH
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodeDepth()
{
    
    if (isActive()) {
        depthFromActive = 0;
        if (getParent()) {
            getParent()->depthFromActive = -1;
            depth = getParent()->depth + 1;
        }
    }
    
    else if (!isActive() && getParent()) {
        if (getParent()->depthFromActive >= 0) {
            depthFromActive = getParent()->depthFromActive + 1;
        }
        else if (getParent()->depthFromActive < 0) {
            depthFromActive = getParent()->depthFromActive -1;
        }
        depth = getParent()->depth + 1;
    }
    
    else if (!isActive() && !getParent()) {
        depth = 0;
        if (getChildren()->size()) {
            depthFromActive = getChildren()->at(0)->depthFromActive -1;
        }
    }
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePosition()
{
    
    if (!getParent()) { return; }
    
    if (getParent()->isActive()) {
        positionDepth = 0;
        positionRadius = JEN_NODE_RADIUS * 3.0f / 4.0f;
    }
    else if (isActive()) {
        positionDepth = JEN_NODE_DEPTH * 4.0f;
        positionRadius = JEN_NODE_RADIUS;
    }
    else {
        positionDepth = JEN_NODE_DEPTH;
        positionRadius = JEN_NODE_RADIUS;
    }
    
    if (getParent()->getParent()) {
        if (getParent()->getParent()->isActive()) {
            positionDepth = JEN_NODE_DEPTH * 2.0f;
            positionRadius = JEN_NODE_RADIUS;
        }
    }
    
    /* Get Position */
    switch (getParent()->getNodeLayout()) {
        case JEN_NODE_LAYOUT_RADIAL: updateNodePositionRadial(); break;
        case JEN_NODE_LAYOUT_SPIRAL: updateNodePositionSpiral(); break;
        case JEN_NODE_LAYOUT_LIST: updateNodePositionList(); break;
        case JEN_NODE_LAYOUT_GRID: updateNodePositionGrid(); break;
        default: updateNodePositionRadial(); break;
    }
    
    /* Set node orientation and position */
    position += getParent()->getPositionJN();
    setOrientation(position);
    //setPosition(position);
    //setPositionTween(position);
    setPositionJN(position);
    
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION RADIAL
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionRadial()
{
    algebraic.setup(getSiblingPerc() + getParent()->getSiblingPerc() + 0.25f);
    position = ofVec3f(algebraic.getSine() * positionRadius,
                       algebraic.getCosine() * positionRadius,
                       positionDepth);
}

//--------------------------------------------------------------------------------//
// UPDATE NODE POSITION SPIRAL
//--------------------------------------------------------------------------------//

void ofxNUINode::updateNodePositionSpiral()
{
    if (getNumOfSiblings() >= JEN_SPIRAL_DEPTH_THRESHHOLD) {
        algebraic.setup((getSiblingPerc()/(1.0f/(float)getNumOfSiblings()))
                        * JEN_SPIRAL_DEPTH_THRESHHOLD_PERC
                        + getParent()->getSiblingPerc() + 0.75f);
        position = ofVec3f(algebraic.getSine() * positionRadius,
                           algebraic.getCosine() * positionRadius,
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

void ofxNUINode::updateNodeColours()
{
    
    setSphereColour();
    setLineColour();
    setNameColour();
    
}

//--------------------------------------------------------------------------------//
// RETURN NODE NAME
//--------------------------------------------------------------------------------//

string ofxNUINode::getNodeName()
{
    return nodeName;
}

//--------------------------------------------------------------------------------//
// GET CHILDREN
//--------------------------------------------------------------------------------//

vector<ofxNUINode*>* ofxNUINode::getChildren()
{
    return &children;
}

//--------------------------------------------------------------------------------//
// GET PARENT
//--------------------------------------------------------------------------------//

ofxNUINode* ofxNUINode::getParent()
{
    return parentNode;
}

//--------------------------------------------------------------------------------//
// GET SIBLING PERCENTAGE
//--------------------------------------------------------------------------------//

float ofxNUINode::getSiblingPerc()
{
    return siblingPerc;
}

//--------------------------------------------------------------------------------//
// GET NODE LAYOUT
//--------------------------------------------------------------------------------//

int ofxNUINode::getNodeLayout()
{
    return nodeLayout;
}

//--------------------------------------------------------------------------------//
// GET NUMBER OF SIBLINGS
//--------------------------------------------------------------------------------//

int ofxNUINode::getNumOfSiblings()
{
    return numOfSiblings;
}

//--------------------------------------------------------------------------------//
// GET POSITION OF ofxNUINode
//--------------------------------------------------------------------------------//

ofVec3f ofxNUINode::getPositionJN()
{
    return positionJN;
}

//--------------------------------------------------------------------------------//
// GET SIBLING NUMBER (ID)
//--------------------------------------------------------------------------------//

int ofxNUINode::getSiblingNum()
{
    return siblingNum;
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
    
    /* SET CONDITIONS */
    
    sphere.updateAngle();
    
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
    sphere.setPosition(tempTweenNodePos);
    /* Setup line */
    line.clear();
    line.addVertex(tempTweenNodePos);
    line.addVertex(getParent()->getPosition());
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
    drawSphere();
    drawLine();
    drawName();
    ofDisableAlphaBlending();
    
}

//--------------------------------------------------------------------------------//
// DRAW SPHERE
//--------------------------------------------------------------------------------//

void ofxNUINode::drawSphere()
{
    sphere.draw();
}

//--------------------------------------------------------------------------------//
// DRAW LINE
//--------------------------------------------------------------------------------//

void ofxNUINode::drawLine()
{
    
    /* If there is parent... */
    if (getParent()) {
        ofSetColor(lineColour);
        line.draw();
    }
    
}

//--------------------------------------------------------------------------------//
// DRAW NAME
//--------------------------------------------------------------------------------//

void ofxNUINode::drawName()
{
    
    /* Only draw if depthFromActive < 1 or parent is highlighted */
    if (getParent() == NULL && depthFromActive > 1) { return; }
    else if (depthFromActive < 0) { return; }
    else if (getParent() && depthFromActive > 1) {
        if (getParent()->isHighlighted() == false) { return; }
    }
    
    ofSetColor(nameColour);
    ofDrawBitmapString(nodeName,    getPosition().x + getSphereRadius() + 5,
                                    getPosition().y,
                                    getPosition().z);
    
}

//--------------------------------------------------------------------------------//
// SET SPHERE COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::setSphereColour()
{
    
    /* Set sphere size and position */
    genAndSetSphereRadius();
    sphere.setup(getSphereRadius());
    
    /* If node is currently active */
    if (isActive()) {
        red = baseRed - 30;
        grn = baseGrn + 40;
        blu = baseBlu - 30;
        alpha = baseAlpha;
    }
    
    /* If node is currently highlighted */
    else if (isHighlighted()) {
        red = baseRed + 40;
        grn = baseGrn * 0.5f;
        blu = baseBlu * 0.5f;
        alpha = baseAlpha;
    }
    
    /* If parent of node is currently active */
    else if (getParent()) {
        if (getParent()->isActive()) {
            red = baseRed * 0.5f;
            grn = baseGrn - 20;
            blu = baseBlu;
            alpha = ofClamp(baseAlpha * 1.5f, 0, 254);
        }
    }
    
    /* If is derived from highlighted node */
    else if (depthFromHighlighted > 0) {
        luminanceReduction = 30 * depthFromHighlighted;
        red = ofClamp(baseRed - luminanceReduction, 0, 254) * 1.5f;
        grn = ofClamp(baseGrn - luminanceReduction, 0, 254) * 0.3f;
        blu = ofClamp(baseBlu - luminanceReduction, 0, 254) * 0.3f;
        alpha = baseAlpha;
    }
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0) {
        luminanceReduction = 43 * depthFromActive;
        red = ofClamp(baseRed - luminanceReduction, 0, 254);
        grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
        blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
        alpha = ofClamp(baseAlpha - luminanceReduction * 0.2f, 0, 254);
    }
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0) {
        luminanceReduction = 120;
        red = ofClamp(baseRed - luminanceReduction, 0, 254);
        grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
        blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
        alpha = ofClamp(baseAlpha - luminanceReduction * 0.2f, 0, 254);
    }
    
    sphereColour = ofColor(red, grn, blu, alpha);
    sphere.setColour(sphereColour);
    
}

//--------------------------------------------------------------------------------//
// SET LINE COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::setLineColour()
{
    
    if (!getParent()) { return; }
    
    /* If node is currently active */
    if (isActive()) {
        red = baseRed;
        grn = baseGrn * 1.5f;
        blu = baseBlu;
        alpha = baseAlpha;
        lineColour = ofColor(red, grn, blu, alpha);
        return;
    }
    
    /* If node is currently highlighted */
    else if (isHighlighted()) {
        luminanceReduction = 30 * depthFromActive;
        red = baseRed - luminanceReduction;
        grn = baseGrn - luminanceReduction;
        blu = baseBlu - luminanceReduction;
        red += (255 - red) * 0.75f;
        lineColour = ofColor(red, grn, blu, 200);
        return;
    }
    
    /* If parent node is active */
    else if (getParent()->isActive()) {
        red = baseRed * 0.5f;
        grn = baseGrn * 0.8f;
        blu = baseBlu;
        alpha = baseAlpha;
        lineColour = ofColor(red, grn, blu, baseAlpha);
        return;
    }
    
    /* If is derived from highlighted node */
    else if (depthFromHighlighted > 0) {
        luminanceReduction = 30 * depthFromHighlighted;
        red = ofClamp(baseRed - luminanceReduction, 0, 254);
        grn = ofClamp(baseGrn - luminanceReduction*1.3f, 0, 254);
        blu = ofClamp(baseBlu - luminanceReduction*1.3f, 0, 254);
        red += (255 - red) * 0.25f;
        lineColour = ofColor(red, grn, blu,ofClamp(200-luminanceReduction,0,254));
        return;
    }
    
    /* If is any other type of node derived from active */
    else if (depthFromActive > 0) {
        luminanceReduction = 43 * depthFromActive;
    }
    
    /* If is any other type of node not derived from active */
    else if (depthFromActive < 0) {
        luminanceReduction = 120;
    }
    
    red = ofClamp(baseRed - luminanceReduction, 0, 254);
    grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
    blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
    alpha = baseAlpha * 0.75f * (float)luminanceReduction / (float)255;
    lineColour = ofColor(red, grn, blu, alpha);
    
}

//--------------------------------------------------------------------------------//
// SET NAME COLOUR
//--------------------------------------------------------------------------------//

void ofxNUINode::setNameColour()
{
    
    if (isHighlighted() || isActive()) {
        nameColour = baseNameColour + ofColor(40, -20, -20, 4);
    }
    else {
        nameColour = baseNameColour;
    }
    
}

//--------------------------------------------------------------------------------//
// GET IS ACTIVE
//--------------------------------------------------------------------------------//

bool ofxNUINode::isActive()
{
    return active;
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
    else if (getParent()) {
        if (!getParent()->isActive()) {
            depthFromActive = -1;
        }
    }
    
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
        if (getParent()) {
            getParent()->depthFromActive = -1;
        }
    }
    else if (getParent()) {
        if (!getParent()->isActive()) {
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
    _child->updateofxNUINode();
    updateofxNUINode();
    updateChildren();
}

//--------------------------------------------------------------------------------//
// SET PARENT NODE AS ACTIVE
//--------------------------------------------------------------------------------//

void ofxNUINode::setParentAsActive()
{
    setActive(false);
    getParent()->setActive(true);
    getParent()->updateofxNUINode();
    getParent()->updateChildren();
}

//--------------------------------------------------------------------------------//
// GET DEPTH FROM ACTIVE NODE
//--------------------------------------------------------------------------------//

int ofxNUINode::getDepthFromActive()
{
    return depthFromActive;
}

//--------------------------------------------------------------------------------//
// GET IS HIGHLIGHTED
//--------------------------------------------------------------------------------//

bool ofxNUINode::isHighlighted()
{
    return highlight;
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
// SET HIGHLIHGTED
//--------------------------------------------------------------------------------//

void ofxNUINode::setHighlight(bool _isHighlighted)
{
    
    highlight = _isHighlighted;
    
    if (isHighlighted() == true) {
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
    
    depthFromHighlighted = getParent()->depthFromHighlighted + 1;
    
    setLineColour();
    setSphereColour();
    setNameColour();
    
    for (int i=0; i < children.size(); i++) {
        children.at(i)->setHighlightDepth();
    }
    
}

//--------------------------------------------------------------------------------//
// RESET HIGHLIGHT DEPTH
//--------------------------------------------------------------------------------//

void ofxNUINode::resetHighlightDepth()
{
    
    depthFromHighlighted = -1;
    
    setLineColour();
    setSphereColour();
    setNameColour();
    
    for (int i=0; i < children.size(); i++) {
        children.at(i)->setHighlight(false);
    }
    
}

//--------------------------------------------------------------------------------//
// GENERATE AND SET SPHERE RADIUS
//--------------------------------------------------------------------------------//

void ofxNUINode::genAndSetSphereRadius()
{
    
    if (numOfSiblings == 0) { setSphereRadius(10); }
    else { setSphereRadius( 10.0f + (10.0f / (float)numOfSiblings) ); }
    
}

//--------------------------------------------------------------------------------//
// SET SPHERE RADIUS
//--------------------------------------------------------------------------------//

void ofxNUINode::setSphereRadius(int _sphereRadius)
{
    sphereRadius = _sphereRadius;
}

//--------------------------------------------------------------------------------//
// GET SPHERE RADIUS
//--------------------------------------------------------------------------------//

int ofxNUINode::getSphereRadius()
{
    return sphereRadius;
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