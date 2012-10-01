/*
 *  ofxArtNetDmxData.cpp
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/29/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */

#include "ofxArtNetDmxData.h"
#include <stdlib.h>

//-----------------------------------------------------
ofxArtNetDmxData::ofxArtNetDmxData(int len) {
	allocate(len);
	port = 0;
}
//-----------------------------------------------------
ofxArtNetDmxData::ofxArtNetDmxData(uint8_t* data, int len) {
	this->data = data;
	this->len = len;
	this->port = 0;
}
//-----------------------------------------------------
ofxArtNetDmxData::~ofxArtNetDmxData() {
	//destroy();
}
//-----------------------------------------------------
void ofxArtNetDmxData::allocate(int len) {
	this->len = len;
	this->data = (uint8_t*)malloc(len);
}
//-----------------------------------------------------
void ofxArtNetDmxData::destroy() {
	free(this->data);
	this->data = NULL;
	this->len = 0;
}
//-----------------------------------------------------
void ofxArtNetDmxData::set(uint8_t val) {
	memset(data, val, len);
}