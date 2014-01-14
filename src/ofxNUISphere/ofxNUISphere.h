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


#ifndef __GenMax__ofxNUISphere__
#define __GenMax__ofxNUISphere__

/* Header Includes */

#include "ofMain.h"
#include "ofxNUIShape.h"

/* Class */

class ofxNUISphere : public ofxNUIShape {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUISphere(){
        
    }
    
    ~ofxNUISphere(){
        
    }
    
    /* Functions */
    
    void setup(float _radius, ofVec3f _position, ofColor _color);
    void setRadius(float _radius);
    void setPosition(ofVec3f _position);
    void setColor(ofColor _color);
    void draw();
    void update();
    void updateAngle();
    
    /* Variable Declaration */
    
    float ang;
    float wave1;
    ofSpherePrimitive spherePrimitive;
    ofMesh mesh;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__GenMax__ofxNUISphere__) */
