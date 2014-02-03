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


#ifndef __GenMax__ofxNUIDirectorNode__
#define __GenMax__ofxNUIDirectorNode__

/* Header Includes */

#include "ofMain.h"
#include "ofxNUIWidgetNode.h"

/* Class */

class ofxNUIDirectorNode : public ofxNUINode {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIDirectorNode(){
        nodeInit();
    }
    
    /* Functions */
    
    virtual string getName() { return "ofxNUIDirectorNode"; }
    virtual string getNodeType() { return "ofxNUIDirectorNode"; }
    
    void nodeInit();
    virtual void setup(vector<ofxNUINode*> _nodes);
    void setupGL();
    void setupCam();
    void setupLight();
    
    void setActiveNode(ofxNUINode *_activeNode);
    void setPrevActiveNode(ofxNUINode  *_prevActiveNode);
    void setClosestChild(ofxNUINode *_closestChild);
    void setPrevClosestChild(ofxNUINode *_prevClosestChild);
    
    ofxNUINode* getActiveNode();
    ofxNUINode* getPrevActiveNode();
    ofxNUINode* getClosestChild();
    ofxNUINode* getPrevClosestChild();
    
    void moveCamToActive();
    void updateCamTween();
    void stopCamTween();
    
    bool isMouseOnASuperCanvas();
    void findClosestChild();
    
    void selectNode();
    void selectParent();
    void selectClosestChild();
    
    /* BaseApp Stuff */
    virtual void update();
    virtual void draw();
    virtual void keyPressed(int key);
    virtual void mouseMoved(int x, int y);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    
    /* Variable Declaration */
    
    bool positionIsTweening;
    bool targetIsTweening;
    
    int distance;
    int smallestDistance;
    
    unsigned int positionDurationMS;
    unsigned int targetDurationMS;
    unsigned int delayMS;
    
    bool mouseIsOnASuperCanvas;
    
    ofxNUIColorScheme coreColorScheme;
    
    ofEasyCam cam;
    ofLight ambientLight;
    
    ofxTween tweenCamPosition;
    ofxTween tweenCamTarget;
    ofxEasingExpo easingExpo;
    ofxEasingQuad easingQuad;
    
    /* Class Instances */
    
    ofxNUINode *activeNode;
    ofxNUINode *prevActiveNode;
    ofxNUINode *closestChild;
    ofxNUINode *prevClosestChild;
    ofxNUINode *child;
    ofxNUIWidgetNode *widgetNode;
    
};

#endif /* defined(__GenMax__ofxNUIDirectorNode__) */
