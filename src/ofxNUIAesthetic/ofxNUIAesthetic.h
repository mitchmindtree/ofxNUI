//
//  ofxNUIAesthetic.h
//  GenMax
//
//  Created by Mitchell Nordine on 12/01/2014.
//
//

#ifndef __GenMax__ofxNUIAesthetic__
#define __GenMax__ofxNUIAesthetic__

/* Header Includes */

#include "ofMain.h"
#include "ofxTween.h"
#include "ofxNUIColorScheme.h"
#include "ofxNUISphere.h"

#define OFXNUI_NODE_SHAPE_SPHERE 0
#define OFXNUI_NODE_SHAPE_CIRCLE 1
#define OFXNUI_NODE_SHAPE_TRIANGLE 2

/* Class */

class ofxNUIAesthetic {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIAesthetic(){
        init();
    }
    
    ~ofxNUIAesthetic(){
        
    }
    
    /* Functions */
    
    void setup(ofxNUIColorScheme *_colorScheme, int _shapeType = 0);
    void init();
    void updateAesthetic();
    void setShapeType(int _shapeType);
    
    void genAndSetShapeRadius();
    void setShapeRadius(int _shapeRadius);
    int getShapeRadius();
    
    void customDraw();
    void drawShape();
    void drawLine();
    void drawName();
    
    virtual void update();
    void updateTween();
    void updateShape();
    
    /* Variable Declaration */
    
    int shapeType;
    
    ofxTween tweenNodePos;
    ofxEasingExpo easingExpo;
    
    ofxNUISphere sphere;
    ofPolyline line;
    
    /* Class Instances */
    
    ofxNUIColorScheme *colorScheme;
    
};

#endif /* defined(__GenMax__ofxNUIAesthetic__) */
