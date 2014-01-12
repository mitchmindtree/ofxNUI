//
//  ofxNUISphere.h
//  GenMax
//
//  Created by Mitchell Nordine on 11/12/2013.
//
//

#ifndef __GenMax__ofxNUISphere__
#define __GenMax__ofxNUISphere__

/* Header Includes */

#include "ofMain.h"

/* Class */

class ofxNUISphere {
    
public:
    
    /* Constructors & Destructors */
    
    ofxNUISphere(){
        position = ofVec3f(0,0,0);
    }
    
    ~ofxNUISphere(){
        
    }
    
    /* Functions */
    
    void setup(float radius);
    void setPosition(ofVec3f _position);
    void setColour(ofColor color);
    void draw();
    void updateAngle();
    
    /* Variable Declaration */
    
    float ang;
    float wave1;
    ofVec3f position;
    ofSpherePrimitive spherePrimitive;
    ofMesh mesh;
    
    /* Class Instances */
    
    
    
};

#endif /* defined(__GenMax__ofxNUISphere__) */
