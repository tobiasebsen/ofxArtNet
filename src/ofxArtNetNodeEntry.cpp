/*
 *  ofxArtNetNodeEntry.cpp
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/27/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxArtNetNodeEntry.h"
#include "artnet.h"

ofxArtNetNodeEntry::ofxArtNetNodeEntry(void* node_entry) {
	artnet_node_entry ne = (artnet_node_entry)node_entry;
	
	stringstream ssip;
	ssip << ne->ip[0] << "." << ne->ip[1] << "." << ne->ip[2] << "." << ne->ip[3];
	ip = ssip.str();
	
	subnet = ne->sub;
	
	shortName.assign((char*)ne->shortname);
	longName.assign((char*)ne->longname);
	
	stringstream ssmac;
	for (int i=0; i<ARTNET_MAC_SIZE; i++) {
		if(i) ssmac << ":";
		ssmac << hex << setw(2) << ne->mac[i];
	}
	mac = ssmac.str();
}