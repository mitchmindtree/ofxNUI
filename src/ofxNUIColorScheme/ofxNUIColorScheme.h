//
//  ofxNUIColorScheme.h
//  GenMax
//
//  Created by Mitchell Nordine on 10/01/2014.
//
//

#ifndef __GenMax__ofxNUIColorScheme__
#define __GenMax__ofxNUIColorScheme__

/* Header Includes */

#include "ofMain.h"

/* Class */

class ofxNUIColorScheme {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIColorScheme(){
        init();
    }
    
    ~ofxNUIColorScheme(){
        
    }
    
    /* Functions */
    
    void init();
    void genAndSetColors();
    
    void genAndSetLineColorActive();
    void genAndSetLineColorActiveParent();
    void genAndSetLineColorHighlighted();
    
    void genAndSetShapeColorActive();
    void genAndSetShapeColorActiveParent();
    void genAndSetShapeColorHighlighted();
    
    void genAndSetNameColorActive();
    void genAndSetNameColorHighlighted();
    
    ofColor getLineColor();
    ofColor getLineColorActive();
    ofColor getLineColorActiveParent();
    ofColor getLineColorActiveDepth(int depthFromActive);
    ofColor getLineColorHighlighted();
    ofColor getLineColorHighlightDepth(int depthFromHighlight);
    
    ofColor getShapeColor();
    ofColor getShapeColorActive();
    ofColor getShapeColorActiveParent();
    ofColor getShapeColorActiveDepth(int depthFromActive);
    ofColor getShapeColorHighlighted();
    ofColor getShapeColorHighlightDepth(int depthFromHighlight);
    
    ofColor getNameColor();
    ofColor getNameColorActive();
    ofColor getNameColorHighlighted();
    
    /* Variable Declaration */

private:
    
    int luminanceReduction;
    
    ofColor lineColorActive;
    ofColor lineColorActiveParent;
    ofColor lineColorHighlighted;
    
    ofColor shapeColorActive;
    ofColor shapeColorActiveParent;
    ofColor shapeColorHighlighted;
    
    ofColor nameColorActive;
    ofColor nameColorHighlighted;
    
    ofColor baseLineColor;
    ofColor baseShapeColor;
    ofColor baseNameColor;
    
    int red;
    int grn;
    int blu;
    int alpha;
    
    int baseRed;
    int baseGrn;
    int baseBlu;
    int baseAlpha;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__GenMax__ofxNUIColorScheme__) */
