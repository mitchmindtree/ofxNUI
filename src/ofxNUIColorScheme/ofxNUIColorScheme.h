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
