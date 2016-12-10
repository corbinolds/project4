//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

using namespace std;

// ***************************************************************************
// * resultsC::resultsC
// *  Constructor for the results container class.  
// ***************************************************************************
resultsC::resultsC() {
  totalPacketCount = 0;
  
  // link layer
  totalEthernetIIFrames = 0;
  number802frames = 0;
  
  // network layer
  totalArpPackets = 0;
  totalIP4Packets = 0;
  totalIP6Packets = 0;
  totalOtherNetworkPackets = 0;
  
  // transport layer
  totalICMPPackets = 0;
  totalTCPPackets = 0;
  totalUDPPackets = 0;
  totalOtherTransportPackets = 0;
}


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to pr all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {

  cout << "A total of " << totalPacketCount << " packets processed." << endl << endl;
  
  //link layer
  cout << "------ LINK LAYER ------" << endl;
  cout << "There are " << totalEthernetIIFrames << " total Ethernet II frames." << endl;
  cout << "There are " << number802frames << " total 802.3 frames." << endl << endl;
  
 	//network layer 
  cout << "------ NETWORK LAYER ------" << endl;
 	cout << "There are " << totalArpPackets << " total ARP packets." << endl;
  cout << "ARP min size: '" << findMinSize(arpSizes) << "'. ARP max size: '" << findMaxSize(arpSizes) << "'. ARP average size: '" << findAverageSize(arpSizes) << "'." << endl << endl;

  cout << "There are " << totalIP4Packets << " total IPv4 packets." << endl;
  cout << "IPv4 min size: '" << findMinSize(ipv4Sizes) << "'. IPv4 max size: '" << findMaxSize(ipv4Sizes) << "'. IPv4 average size: '" << findAverageSize(ipv4Sizes) << "'." << endl << endl;
  
  cout << "There are " << totalIP6Packets << " total IPv6 packets." << endl; 
  cout << "IPv6 min size: '" << findMinSize(ipv6Sizes) << "'. IPv6 max size: '" << findMaxSize(ipv6Sizes) << "'. IPv6 average size: '" << findAverageSize(ipv6Sizes) << "'." << endl << endl;
  
  cout << "There are " << totalOtherNetworkPackets << " total other network layer protocol packets." << endl << endl; 
  
  cout << "------ TRANSPORT LAYER ------" << endl;
  cout << "There are " << totalICMPPackets << " total ICMP packets." << endl; 
  cout << "ICMP min size: '" << findMinSize(icmpSizes) << "'. ICMP max size: '" << findMaxSize(icmpSizes) << "'. ICMP average size: '" << findAverageSize(icmpSizes) << "'." << endl << endl;

  cout << "There are " << totalTCPPackets << " total TCP packets." << endl; 
  // cout << "TCP min size: '" << findMinSize(tcpSizes) << "'. TCP max size: '" << findMaxSize(tcpSizes) << "'. TCP average size: '" << findAverageSize(tcpSizes) << "'." << endl << endl;
  
  cout << "There are " << totalUDPPackets << " total UDP packets." << endl; 
  // cout << "UDP min size: '" << findMinSize(udpSizes) << "'. UDP max size: '" << findMaxSize(udpSizes) << "'. UDP average size: '" << findAverageSize(udpSizes) << "'." << endl << endl;
  
  cout << "There are " << totalOtherTransportPackets << " total other transport layer protocol packets." << endl << endl; 

  
  // PART 2
  cout << "There are " << destinationMacs.size() << " unique destination mac addresses." << endl;
  cout << "There are " << sourceMacs.size() << " unique source mac addresses." << endl;

  
}
