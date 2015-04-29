//
//  ofApp.cpp
//  NoiseGrid3D
//
//  Code by Andreas Müller from NoiseWorkshopSketchpad
//
//  Commented and reformatted by Haley Van Camp on 4/28/15.
//

#include "ofApp.h"


// --------------------------------
void ofApp::setup()
{
    fontSmall.loadFont("Fonts/DIN.otf", 8 ); // loading font type
    
    camera.setAutoDistance( false );  // distance of camera from object
    camera.setPosition( ofVec3f(0,1,4) ); // setting position of camera
    camera.setNearClip( 0.001 ); // ??
}

// --------------------------------
void ofApp::draw()
{   // setting background color
    ofBackgroundGradient( ofColor(55), ofColor(0), OF_GRADIENT_CIRCULAR );
    
    
    t = ofGetElapsedTimef(); // initalizing t
    
    mx = ofNormalize( ofGetMouseX(), 0, ofGetWidth() ); // initalizing mx to mouse x position
    my = ofNormalize( ofGetMouseY(), 0, ofGetHeight() ); // initalizing my to mouse y position
    
    frequency = ofMap( mx, 0, 1, 0.1, 1.0 ); // initalizing frequency
    timeFrequency = ofMap( my, 0, 1, 0.1, 2.0 ); // initalizing timeFrequency
    
    tn = t * timeFrequency; // initalizing tn
    
    res = 20; // initalizing res to 20
    size = ofVec3f(3, 3, 3); // initalizing size
    
    ofMesh mesh; // declaring variable;
    mesh.setMode( OF_PRIMITIVE_LINES ); // setting mesh with lines(grid)
    
    // building a vector mesh
    for( int y = 0; y < res; y++ ) // from 0-19, y increases by one each loop
    {
        for( int x = 0; x < res; x++ ) // from 0-19, x increases by one each loop
        {
            for( int z = 0; z < res; z++ ) // from 0-19, z increases by one each loop
            {
                //ofVec3f p;
                //remapping input of x from 0, res to output size.x * -0.5, size.x * 0.5
                p.x = ofMap( x, 0, res, size.x * -0.5, size.x * 0.5 );
                //remapping input of y from 0, res to output size.y *  0.0, size.y * 1.0
                p.y = ofMap( y, 0, res, size.y *  0.0, size.y * 1.0 );
                //remapping input of z from 0, res to output size.z * -0.5, size.z * 0.5
                p.z = ofMap( z, 0, res, size.z * -0.5, size.z * 0.5 );
                
                noisePos = p * frequency; // initializing noisePos
                
                //ofVec3f noise;
                // calculates a four dimensional Perlin noise from -1 to 1 and assigns it to the x value of noise
                noise.x = ofSignedNoise( noisePos.x, noisePos.y, noisePos.z,	tn );
                 // calculates a four dimensional Perlin noise from -1 to 1 and assigns it to the y value of noise
                noise.y = ofSignedNoise( noisePos.y, noisePos.x, tn,			noisePos.z );
                 // calculates a four dimensional Perlin noise from -1 to 1 and assigns it to the z value of noise
                noise.z = ofSignedNoise( noisePos.z, tn,		 noisePos.x,	noisePos.y );
                noise.normalize(); // ??
                noise *= 0.2; // multiplies noise by .2 each loop
                
                mesh.addVertex( p ); // adding p to the mesh
                mesh.addVertex( p + noise ); // adding p + noise to the mesh
                
                // Color by direction
                // ??
                velAsCol = ofVec3f(noise.getNormalized() + ofVec3f(1)) * 0.5;
                tmpCol = ofFloatColor( velAsCol.x, velAsCol.y, velAsCol.z );
                mesh.addColor( tmpCol ); // adds tmpCol to mesh
                mesh.addColor( tmpCol ); // adds tmpCol to mesh again to complete vector
            }
        }
    }
    
    
    
    ofEnableDepthTest(); // enables depth test so rendering happens in z-depth
    
    camera.begin(); // camera begins
				// Grid
				ofSetColor( ofColor(60) ); // sets the color
				ofPushMatrix();
    ofRotate(90, 0, 0, -1); // rotates the grid
    ofDrawGridPlane( size.x, (int)size.x, false ); // draws grid
				ofPopMatrix();
    
				ofSetColor( ofColor::white ); // sets color
				mesh.draw(); // draws mesh
    
    camera.end(); // ends/closes camera
    
    ofDisableDepthTest(); // disable depth test
}

// --------------------------------
void ofApp::keyPressed( int _key )
{
    // does nothing
    if( _key == ' ' )
    {
    }
}


