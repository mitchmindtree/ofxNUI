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


#include "ofxNUIColorScheme.h"

//--------------------------------------------------------------------------------//
// INITIALISE
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::init()
{
    
    baseRed = 135;
    baseGrn = 135;
    baseBlu = 160;
    baseAlpha = 180;
    
    baseLineColor = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseShapeColor = ofColor(baseRed,baseGrn,baseBlu, 150);
    baseNameColor = ofColor(baseRed+25,baseGrn+25,baseBlu, 250);
    
    genAndSetColors();
    
}

//--------------------------------------------------------------------------------//
// GENERATE AND SET ALL COLORS
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetColors()
{
    
    genAndSetLineColorActive();
    genAndSetLineColorActiveParent();
    genAndSetLineColorHighlighted();
    genAndSetShapeColorActive();
    genAndSetShapeColorActiveParent();
    genAndSetShapeColorHighlighted();
    genAndSetNameColorActive();
    genAndSetNameColorHighlighted();
    
}

//--------------------------------------------------------------------------------//
// SET LINE COLOR (ACTIVE)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetLineColorActive()
{
    red = ofClamp(baseRed, 0.0f, 254.0f);
    grn = ofClamp(baseGrn*1.5f, 0.0f, 254.0f);
    blu = ofClamp(baseBlu, 0.0f, 254.0f);
    alpha = ofClamp(baseAlpha, 0.0f, 254.0f);
    
    lineColorActive = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET LINE COLOR (ACTIVE PARENT)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetLineColorActiveParent()
{
    red = ofClamp(baseRed*0.5f, 0.0f, 254.0f);
    grn = ofClamp(baseGrn*0.8f, 0.0f, 254.0f);
    blu = ofClamp(baseBlu, 0.0f, 254.0f);
    alpha = ofClamp(baseAlpha, 0.0f, 254.0f);
    lineColorActiveParent = ofColor(red, grn, blu, baseAlpha);
}

//--------------------------------------------------------------------------------//
// SET LINE COLOR (HIGHLIGHTED)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetLineColorHighlighted()
{
    red = ofClamp(baseRed-30.0f, 0.0f, 254.0f);
    red += ofClamp((255 - red) * 0.75f, 0.0f, 254.0f);
    grn = ofClamp(baseGrn-30.0f, 0.0f, 254.0f);
    blu = ofClamp(baseBlu-30.0f, 0.0f, 254.0f);
    lineColorHighlighted = ofColor(red, grn, blu, 200);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (ACTIVE)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorActive()
{
    red = ofClamp(baseRed - 30, 0.0f, 254.0f);
    grn = ofClamp(baseGrn + 40, 0.0f, 254.0f);
    blu = ofClamp(baseBlu - 30, 0.0f, 254.0f);
    alpha = ofClamp(baseAlpha, 0.0f, 254.0f);
    shapeColorActive = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (ACTIVE PARENT)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorActiveParent()
{
    red = ofClamp(baseRed * 0.5f, 0.0f, 254.0f);
    grn = ofClamp(baseGrn - 20, 0.0f, 254.0f);
    blu = ofClamp(baseBlu, 0.0f, 254.0f);
    alpha = ofClamp(baseAlpha * 1.5f, 0, 254);
    shapeColorActiveParent = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (HIGHLIGHTED
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorHighlighted()
{
    red = ofClamp(baseRed + 40, 0.0f, 254.0f);
    grn = ofClamp(baseGrn * 0.5f, 0.0f, 254.0f);
    blu = ofClamp(baseBlu * 0.5f, 0.0f, 254.0f);
    alpha = ofClamp(baseAlpha, 0.0f, 254.0f);
    shapeColorHighlighted = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET NAME COLOR (ACTIVE)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetNameColorActive()
{
    nameColorActive = baseNameColor + ofColor(40, -20, -20, 4);
}

//--------------------------------------------------------------------------------//
// SET NAME COLOR (HIGHLIGHTED)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetNameColorHighlighted()
{
    nameColorHighlighted = baseNameColor + ofColor(40, -20, -20, 4);
}

//--------------------------------------------------------------------------------//
// RETURN BASE LINE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColor()
{
    return baseLineColor;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE LINE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColorActive()
{
    return lineColorActive;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE PARENT LINE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColorActiveParent()
{
    return lineColorActiveParent;
}

//--------------------------------------------------------------------------------//
// RETURN LINE COLOR FROM ACTIVE DEPTH
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColorActiveDepth(int depthFromActive)
{
    if (depthFromActive >= 0) {
        luminanceReduction = 43 * depthFromActive;
    }
    else if (depthFromActive < 0) {
        luminanceReduction = -120 * depthFromActive;
    }
    red = ofClamp(baseRed - luminanceReduction, 0, 254);
    grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
    blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
    alpha = ofClamp(baseAlpha*0.75f*(float)luminanceReduction/(float)255, 0, 254);
    return ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// RETURN HIGHLIGHTED LINE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColorHighlighted()
{
    return lineColorHighlighted;
}

//--------------------------------------------------------------------------------//
// RETURN LINE COLOR FROM HIGHLIGHT DEPTH
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getLineColorHighlightDepth(int depthFromHighlight)
{
    luminanceReduction = 30 * depthFromHighlight;
    red = ofClamp(baseRed - luminanceReduction, 0, 254);
    grn = ofClamp(baseGrn - luminanceReduction*1.3f, 0, 254);
    blu = ofClamp(baseBlu - luminanceReduction*1.3f, 0, 254);
    red += (255 - red) * 0.25f;
    alpha = ofClamp(200-luminanceReduction,0,254);
    return ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// RETURN BASE SHAPE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColor()
{
    return baseShapeColor;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE SHAPE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColorActive()
{
    return shapeColorActive;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE PARENT SHAPE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColorActiveParent()
{
    return shapeColorActiveParent;
}

//--------------------------------------------------------------------------------//
// RETURN SHAPE COLOR FROM ACTIVE DEPTH
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColorActiveDepth(int depthFromActive)
{
    luminanceReduction = 100 * depthFromActive;
    red = ofClamp(baseRed - luminanceReduction, 0, 254);
    grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
    blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
    alpha = ofClamp(baseAlpha - luminanceReduction * 0.2f, 0, 254);
    return ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// RETURN HIGHLIGHTED SHAPE COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColorHighlighted()
{
    return shapeColorHighlighted;
}

//--------------------------------------------------------------------------------//
// RETURN SHAPE COLOR FROM HIGHLIGHT DEPTH
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getShapeColorHighlightDepth(int depthFromHighlight)
{
    luminanceReduction = 30 * depthFromHighlight;
    red = ofClamp(baseRed - luminanceReduction, 0, 254) * 1.5f;
    grn = ofClamp(baseGrn - luminanceReduction, 0, 254) * 0.3f;
    blu = ofClamp(baseBlu - luminanceReduction, 0, 254) * 0.3f;
    alpha = baseAlpha;
    return ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// RETURN BASE NAME COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getNameColor()
{
    return baseNameColor;
}

//--------------------------------------------------------------------------------//
// RETURN ACTIVE NAME COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getNameColorActive()
{
    return nameColorActive;
}

//--------------------------------------------------------------------------------//
// RETURN HIGHLIGHTED NAME COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIColorScheme::getNameColorHighlighted()
{
    return nameColorHighlighted;
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



//--------------------------------------------------------------------------------//
//
//--------------------------------------------------------------------------------//