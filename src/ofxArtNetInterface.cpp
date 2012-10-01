/*
 *  ofxArtNetInterface.cpp
 *  artnetExample
 *
 *  Created by Tobias Ebsen on 9/29/12.
 *  Copyright 2012 Tobias Ebsen. All rights reserved.
 *
 */


#include <errno.h>

#ifndef WIN32
#include <sys/socket.h> // socket before net/if.h for mac
#include <net/if.h>
#include <sys/ioctl.h>
#else
typedef int socklen_t;
#include <winsock2.h>
#include <Lm.h>
#include <iphlpapi.h>
#endif

#include <unistd.h>

#include "private.h"

#ifdef HAVE_GETIFADDRS
#ifdef HAVE_LINUX_IF_PACKET_H
#define USE_GETIFADDRS
#endif
#endif

#ifdef USE_GETIFADDRS
#include <ifaddrs.h>
#include <linux/types.h> // required by if_packet
#include <linux/if_packet.h>
#endif


enum { INITIAL_IFACE_COUNT = 10 };
enum { IFACE_COUNT_INC = 5 };
enum { IFNAME_SIZE = 32 }; // 32 sounds a reasonable size

typedef struct iface_s {
	struct sockaddr_in ip_addr;
	struct sockaddr_in bcast_addr;
	int8_t hw_addr[ARTNET_MAC_SIZE];
	char   if_name[IFNAME_SIZE];
	struct iface_s *next;
} iface_t;

//////////////////////////////////////////////////////////////////////

extern "C" int get_ifaces(iface_t **if_head);

#include "ofxArtNetInterface.h"

void ofxArtNetInterface::getInterfaces(vector<ofxArtNetInterface>& interfaces) {
	
	iface_t *ift_head = NULL;
	int r = get_ifaces(&ift_head);
	if(r != ARTNET_EOK)
		return;
	
	iface_t *ift;
	for (ift = ift_head; ift != NULL; ift = ift->next) {
		
		ofxArtNetInterface interface;
		
		interface.name = ift->if_name;
		interface.ip = inet_ntoa(ift->ip_addr.sin_addr);
		interface.broadcast = inet_ntoa(ift->bcast_addr.sin_addr);
		
		stringstream ss;
		ss << setfill('0');
		for (int i=0; i<ARTNET_MAC_SIZE; i++) {
			if(i) ss << ":";
			ss << setw(2) << hex << (int)ift->hw_addr[i];
		}
		interface.mac = ss.str();
		
		interfaces.push_back(interface);
	}
}