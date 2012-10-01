/*
 *  ofxArtNetInterface.h
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/29/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxArtNetInterface {
public:
	string name;
	string ip;
	string broadcast;
	string mac;
	
	static void getInterfaces(vector<ofxArtNetInterface>& interfaces);
};
