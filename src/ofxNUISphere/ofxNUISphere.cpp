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


#include "ofxNUISphere.h"

//--------------------------------------------------------------------------------//
// SETUP
//--------------------------------------------------------------------------------//

void ofxNUISphere::setup(float _radius, ofVec3f _position, ofColor _color)
{
    ofxNUIShape::setup(_radius, _position, _color);
    spherePrimitive.set(_radius, 5);
    spherePrimitive.setOrientation(getPosition());
    mesh = spherePrimitive.getMesh();
    setColor(_color);
}

//--------------------------------------------------------------------------------//
// SETUP SPHERE
//--------------------------------------------------------------------------------//

void ofxNUISphere::setRadius(float _radius)
{
    ofxNUIShape::setRadius(_radius);
    spherePrimitive.set(_radius, 5);
    spherePrimitive.setOrientation(getPosition());
    mesh = spherePrimitive.getMesh();
}

//--------------------------------------------------------------------------------//
// SET POSITION
//--------------------------------------------------------------------------------//

void ofxNUISphere::setPosition(ofVec3f _position)
{
    ofxNUIShape::setPosition(_position);
    spherePrimitive.setOrientation(getPosition());
}

//--------------------------------------------------------------------------------//
// SET COLOUR
//--------------------------------------------------------------------------------//

void ofxNUISphere::setColor(ofColor _color)
{
    ofxNUIShape::setColor(_color);
    for (int i=0; i < mesh.getVertices().size(); i++) {
        mesh.addColor(_color+i);
    }
}

//--------------------------------------------------------------------------------//
// DRAW SPHERE
//--------------------------------------------------------------------------------//

void ofxNUISphere::draw()
{
    ofxNUIShape::draw();
    ofPushMatrix();
    ofTranslate(getPosition());
    ofRotate(wave1, 0.0f, ang, 1.0f);
    //mesh.drawFaces();
    mesh.drawWireframe();
    ofPopMatrix();
}

//--------------------------------------------------------------------------------//
// UPDATE
//--------------------------------------------------------------------------------//

void ofxNUISphere::update()
{
    ofxNUIShape::update();
    updateAngle();
}

//--------------------------------------------------------------------------------//
// UPDATE ANGLE
//--------------------------------------------------------------------------------//

void ofxNUISphere::updateAngle()
{
    ang+=0.1f;
    wave1 = 100.0f * sin(ang*0.1f) + ang;
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