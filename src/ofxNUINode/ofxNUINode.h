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


#ifndef __GenMax__ofxNUINode__
#define __GenMax__ofxNUINode__

/* Header Includes */

#include "ofMain.h"
#include "Algebraic.h"
#include "ofxNUISphere.h"
#include "ofxTween.h"
#include "ofxNUIColorScheme.h"

#define OFXNUINODE_LAYOUT_RADIUS 300.0f
#define OFXNUINODE_LAYOUT_DEPTH -200.0f

#define OFXNUINODE_LAYOUT_RADIAL 0
#define OFXNUINODE_LAYOUT_SPIRAL 1
#define OFXNUINODE_LAYOUT_LIST 2
#define OFXNUINODE_LAYOUT_GRID 3

#define OFXNUINODE_SPIRAL_DEPTH_THRESHHOLD 32
#define OFXNUINODE_SPIRAL_DEPTH_THRESHHOLD_PERC 0.03125f

#define OFXNUINODE_DEFAULT_POS_TWEEN_DURATION 1000
#define OFXNUINODE_DEFAULT_POS_TWEEN_DELAY 0

#define OFXNUINODE_NODE_RADIUS 10

#define OFXNUINODE_SHAPE_SPHERE 0
#define OFXNUINODE_SHAPE_CIRCLE 1
#define OFXNUINODE_SHAPE_TRIANGLE 2

/* Class */

class ofxNUINode : public ofNode {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUINode();
    
    /* Functions */
    
    /* Name */
    virtual string getName() { return "ofxNUINode"; }
    virtual string getNodeType() { return "ofxNUINode"; }
    
    void nodeInit();
    
    /* Add Children */
    void addChild(ofxNUINode *_child);
    void addChild(ofxNUINode *_child, int num);
    void addChild(ofxNUINode *_child, string _name);
    void addChildList(vector<ofxNUINode*> childList, string _name,
                      int _layout = OFXNUINODE_LAYOUT_RADIAL);
    
    /* Update When A New Node is Activated */
    void updateChildren();
    virtual void updateNode();
    void updateNodeDepth();
    virtual void updateNodePosition();
    void updateNodePositionRadial();
    void updateNodePositionSpiral();
    void updateNodePositionList();
    void updateNodePositionGrid();
    void updateNodeColors();
    void updateLineColor();
    void updateNameColor();
    void updateShapeColor();
    
    /* Set Stuff */
    virtual void setCamera(ofEasyCam *_cam);
    void setColorScheme(ofxNUIColorScheme *_colorScheme);
    void setNodeLayout(int _layout);
    void setNodeLabel(string _name);
    void setNodePosition(ofVec3f _position);
    void setNodeRadius(int _nodeRadius);
    void setNumOfSiblings(int _numOfSiblings);
    void setParentNode(ofxNUINode *_parent);
    void setPositionTween(ofVec3f _position);
    void setShapeType(int _nodeShape);
    void setSiblingPerc(int _siblingNum);
    void setUniqueID(int _uniqueID);
    
    /* Return Stuff */
    ofEasyCam* getCam();
    vector<ofxNUINode*>* getChildren();
    vector<ofxNUINode>* getListParents();
    int getDepth();
    int getDepthFromActive();
    int getDepthFromHighlighted();
    int getNodeLayout();
    string getNodeLabel();
    ofVec3f getNodePosition();
    int getNodeRadius();
    int getNumOfSiblings();
    ofxNUINode* getParentNode();
    int getShapeType();
    float getSiblingPerc();
    int getSiblingNum();
    int getUniqueID();
    
    /* Update */
    virtual void update();
    void updateTween();
    
    /* Draw */
    virtual void customDraw();      // Is called automatically by ofNode.
    virtual void customDraw2D();    // Is called by ofxNUIDirectorNode
    void drawLine();
    void drawName();
    void drawShape();
    
    /* Conditions (Active) */
    bool isActive();
    void setActive(bool _isActive);
    virtual void setChildAsActive(ofxNUINode *_child);
    virtual void setParentAsActive();
    void toggleActive();
    
    /* Conditions (Highlighted) */
    bool isHighlighted();
    virtual void setHighlight(bool _isHighlighted);
    void setHighlightDepth();
    void resetHighlightDepth();
    void toggleHighlight();
    
    
    /* Variable Declaration */
    
private:
    
    bool active;
    int depth;
    int depthFromActive;
    int depthFromHighlighted;
    float depthRatio;
    bool highlight;
    int nodeLayout;
    string nodeLabel;
    int nodeRadius;
    int numOfSiblings;
    float positionDepth;
    float positionRadius;
    int posTweenDurMs;
    int posTweenDelMs;
    int siblingNum;
    float siblingPerc;
    int shapeType;
    int uniqueID;
    
    ofVec3f position;
    ofVec3f positionJN;
    
    ofxTween tweenNodePos;
    ofxEasingExpo easingExpo;
    
    ofxNUISphere sphere;
    ofPolyline line;
    
    ofColor lineColor;
    ofColor shapeColor;
    ofColor nameColor;
    
    /* Class Pointers */
    
    ofEasyCam *cam;
    //ofxNUIShape *shape;
    ofxNUIColorScheme *colorScheme;
    ofxNUINode *parentNode;
    ofxNUINode *child;
    vector<ofxNUINode*> children;
    vector<ofxNUINode> listParents;
    vector<ofxNUINode> cloneChildren;
    
};

#endif /* defined(__GenMax__ofxNUINode__) */
