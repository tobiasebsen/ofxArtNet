/*
 *  ofxArtNetNodeEntry.h
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/27/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"

class ofxArtNetNodeEntry {
public:
	ofxArtNetNodeEntry(void* node_entry);
	
	string	ip;
	int		subnet;
	string	shortName;
	string	longName;
	string	mac;
};