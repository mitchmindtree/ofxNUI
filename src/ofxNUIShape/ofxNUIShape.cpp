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


#include "ofxNUIShape.h"

//--------------------------------------------------------------------------------//
// INITIATE
//--------------------------------------------------------------------------------//

void ofxNUIShape::init()
{
    position = ofVec3f(0,0,0);
    radius = 0;
    color = ofColor(150,150,150,150);
}

//--------------------------------------------------------------------------------//
// SETUP
//--------------------------------------------------------------------------------//

void ofxNUIShape::setup(float _radius, ofVec3f _position, ofColor _color)
{
    setRadius(_radius);
    setPosition(_position);
    setColor(_color);
}

//--------------------------------------------------------------------------------//
// SET POSITION
//--------------------------------------------------------------------------------//

void ofxNUIShape::setPosition(ofVec3f _position)
{
    position = _position;
}

//--------------------------------------------------------------------------------//
// RETURN POSITION
//--------------------------------------------------------------------------------//

ofVec3f ofxNUIShape::getPosition()
{
    return position;
}

//--------------------------------------------------------------------------------//
// SET RADIUS
//--------------------------------------------------------------------------------//

void ofxNUIShape::setRadius(float _radius)
{
    radius = _radius;
}

//--------------------------------------------------------------------------------//
// RETURN RADIUS
//--------------------------------------------------------------------------------//

float ofxNUIShape::getRadius()
{
    return radius;
}

//--------------------------------------------------------------------------------//
// SET COLOR
//--------------------------------------------------------------------------------//

void ofxNUIShape::setColor(ofColor _color)
{
    color = _color;
}

//--------------------------------------------------------------------------------//
// GET COLOR
//--------------------------------------------------------------------------------//

ofColor ofxNUIShape::getColor()
{
    return color;
}

//--------------------------------------------------------------------------------//
// DRAW SHAPE
//--------------------------------------------------------------------------------//

void ofxNUIShape::draw()
{
    
}

//--------------------------------------------------------------------------------//
// UPDATE SHAPE
//--------------------------------------------------------------------------------//

void ofxNUIShape::update()
{
    
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