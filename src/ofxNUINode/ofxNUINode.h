//
//  ofxNUINode.h
//  GenMax
//
//  Created by Mitchell Nordine on 10/12/2013.
//
//

#ifndef __GenMax__ofxNUINode__
#define __GenMax__ofxNUINode__

/* Header Includes */

#include "ofMain.h"
#include "Algebraic.h"
#include "ofxNUISphere.h"
#include "ofxTween.h"
#include "ofxNUIColorScheme.h"

#define JEN_NODE_RADIUS 300.0f
#define JEN_NODE_DEPTH -200.0f

#define JEN_NODE_LAYOUT_RADIAL 0
#define JEN_NODE_LAYOUT_SPIRAL 1
#define JEN_NODE_LAYOUT_LIST 2
#define JEN_NODE_LAYOUT_GRID 3

#define JEN_SPIRAL_DEPTH_THRESHHOLD 32
#define JEN_SPIRAL_DEPTH_THRESHHOLD_PERC 0.03125f

#define DEFAULT_POS_TWEEN_DURATION 1000
#define DEFAULT_POS_TWEEN_DELAY 0

#define JEN_MAX_NUM_OF_CHILDREN 300

/* Class */

class ofxNUINode : public ofNode {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUINode(){
        init();
    }
    
    ~ofxNUINode(){
        
    }
    
    /* Functions */
    
    /* Name */
    virtual string getName() { return "ofxNUINode"; }
    virtual string getNodeType() { return "ofxNUINode"; }
    
    void init();
    void setNodeName(string _name);
    
    
    /* Add Children */
    void addChild(ofxNUINode *_child);
    void addChild(ofxNUINode *_child, int num);
    void addChild(ofxNUINode *_child, string _name);
    void addChildList(vector<ofxNUINode*> childList, string _name);
    
    /* Update When Activated */
    void updateChildren();
    virtual void updateofxNUINode();
    void updateNodeDepth();
    virtual void updateNodePosition();
    void updateNodePositionRadial();
    void updateNodePositionSpiral();
    void updateNodePositionList();
    void updateNodePositionGrid();
    void updateNodeColours();
    void genAndSetSphereRadius();
    
    void setSphereRadius(int _sphereRadius);
    void setParentJN(ofxNUINode *_parent);
    void setLineColour();
    void setSphereColour();
    void setNameColour();
    void setNumOfSiblings(int _numOfSiblings);
    void setSiblingPerc(int _siblingNum);
    void setNodeLayout(int _layout);
    void setPositionTween(ofVec3f _position);
    void setPositionJN(ofVec3f _position);
    
    /* Return Node Stuff */
    string getNodeName();
    vector<ofxNUINode*>* getChildren();
    ofxNUINode* getParent();
    int getSphereRadius();
    int getDepthFromActive();
    float getSiblingPerc();
    int getNumOfSiblings();
    int getNodeLayout();
    ofVec3f getPositionJN();
    int getSiblingNum();
    
    /* Update */
    virtual void update();
    void updateTween();
    
    /* Draw */
    virtual void customDraw();
    void drawSphere();
    void drawLine();
    void drawName();
    
    /* Conditions */
    bool isActive();
    void toggleActive();
    void setActive(bool _isActive);
    void setChildAsActive(ofxNUINode *_child);
    void setParentAsActive();
    
    bool isHighlighted();
    void toggleHighlight();
    virtual void setHighlight(bool _isHighlighted);
    void setHighlightDepth();
    void resetHighlightDepth();

    
    /* Variable Declaration */
private:
    string nodeName;
    int siblingNum;
    int numOfSiblings;
    int depth;
    int depthFromActive;
    int depthFromHighlighted;
    float depthRatio;
    float siblingPerc;
    Algebraic algebraic;
    bool active;
    bool highlight;
    int sphereRadius;
    bool hidden;
    int nodeLayout;
    float positionDepth;
    float positionRadius;
    int posTweenDurMs;
    int posTweenDelMs;
    
    ofVec3f position;
    ofVec3f positionJN;
    
    ofxTween tweenNodePos;
    ofxEasingExpo easingExpo;
    
    ofxNUISphere sphere;
    ofPolyline line;
    
    int luminanceReduction;
    ofColor lineColour;
    ofColor sphereColour;
    ofColor nameColour;
    
    ofColor baseLineColour;
    ofColor baseSphereColour;
    ofColor baseNameColour;
    
    int red;
    int grn;
    int blu;
    int alpha;
    
    int baseRed;
    int baseGrn;
    int baseBlu;
    int baseAlpha;
    
    /* Class Instances */
    
    ofxNUIColorScheme *colorScheme;
    ofxNUINode *parentNode;
    ofxNUINode *child;
    vector<ofxNUINode*> children;
    
};

#endif /* defined(__GenMax__ofxNUINode__) */
