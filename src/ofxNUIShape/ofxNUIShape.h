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


#ifndef __GenMax__ofxNUIShape__
#define __GenMax__ofxNUIShape__

/* Header Includes */

#include "ofMain.h"

/* Class */

class ofxNUIShape {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUIShape(){
        init();
    }
    
    ~ofxNUIShape(){
        
    }
    
    /* Functions */
    
    string getNodeName() { return "ofxNUIShape"; }
    
    virtual void init();
    virtual void setup(float _radius, ofVec3f _position, ofColor _color);
    virtual void setPosition(ofVec3f _position);
    virtual ofVec3f getPosition();
    virtual void setRadius(float _radius);
    virtual float getRadius();
    virtual void setColor(ofColor _color);
    virtual ofColor getColor();
    virtual void draw();
    virtual void update();
    
    /* Variable Declaration */
    
private:
    
    ofVec3f position;
    float radius;
    ofColor color;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__GenMax__ofxNUIShape__) */
