//
//  ofxNUIColorScheme.cpp
//  GenMax
//
//  Created by Mitchell Nordine on 10/01/2014.
//
//

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
    red = baseRed;
    grn = baseGrn * 1.5f;
    blu = baseBlu;
    alpha = baseAlpha;
    lineColorActive = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET LINE COLOR (ACTIVE PARENT)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetLineColorActiveParent()
{
    red = baseRed * 0.5f;
    grn = baseGrn * 0.8f;
    blu = baseBlu;
    alpha = baseAlpha;
    lineColorActiveParent = ofColor(red, grn, blu, baseAlpha);
}

//--------------------------------------------------------------------------------//
// SET LINE COLOR (HIGHLIGHTED)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetLineColorHighlighted()
{
    red = baseRed - 30;
    grn = baseGrn - 30;
    blu = baseBlu - 30;
    red += (255 - red) * 0.75f;
    lineColorHighlighted = ofColor(red, grn, blu, 200);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (ACTIVE)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorActive()
{
    red = baseRed - 30;
    grn = baseGrn + 40;
    blu = baseBlu - 30;
    alpha = baseAlpha;
    shapeColorActive = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (ACTIVE PARENT)
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorActiveParent()
{
    red = baseRed * 0.5f;
    grn = baseGrn - 20;
    blu = baseBlu;
    alpha = ofClamp(baseAlpha * 1.5f, 0, 254);
    shapeColorActiveParent = ofColor(red, grn, blu, alpha);
}

//--------------------------------------------------------------------------------//
// SET SHAPE COLOR (HIGHLIGHTED
//--------------------------------------------------------------------------------//

void ofxNUIColorScheme::genAndSetShapeColorHighlighted()
{
    red = baseRed + 40;
    grn = baseGrn * 0.5f;
    blu = baseBlu * 0.5f;
    alpha = baseAlpha;
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
    luminanceReduction = 43 * depthFromActive;
    red = ofClamp(baseRed - luminanceReduction, 0, 254);
    grn = ofClamp(baseGrn - luminanceReduction, 0, 254);
    blu = ofClamp(baseBlu - luminanceReduction, 0, 254);
    alpha = baseAlpha * 0.75f * (float)luminanceReduction / (float)255;
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
    luminanceReduction = 43 * depthFromActive;
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