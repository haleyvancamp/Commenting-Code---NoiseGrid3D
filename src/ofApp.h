//  Code by Andreas MŸller from NoiseWorkshopSketchpad
//
//  Commented and reformatted by Haley Van Camp on 4/28/15.

#pragma once

#include "ofMain.h"
#include "math/MathUtils.h"


class ofApp : public ofBaseApp {
	public:
    // declaring functions
    void setup();
    void draw();
   	void keyPressed(int key);

    // declaring variables
    float t, tn, mx, my, frequency, timeFrequency;
    int res;
    ofMesh mesh;
    ofVec3f noisePos, noise, velAsCol, p, size;
    ofEasyCam camera;
    ofTrueTypeFont fontSmall;
    ofFloatColor tmpCol;
	
		
};