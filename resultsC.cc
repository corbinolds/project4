//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

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
  //averageSizeArp = 0;
  //minSizeArp = 0;
  //maxSizeArp = 0;

  totalIP4Packets = 0;
  //averageSizeIP4 = 0;
  //minSizeIP4 = 0;
  //maxSizeIP4 = 0;
   
  totalIP6Packets = 0;
  //averageSizeIP6 = 0;
  //minSizeIP6 = 0;
  //maxSizeIP6 = 0;
  
  totalOtherNetworkPackets = 0;
  
  // transport layer
  //totalICMPPackets = 0;
  //averageSizeICMP = 0;
  //minSizeICMP = 0;
  //maxSizeICMP = 0;
   
  //totalTCPPackets = 0;
  //averageSizeTCP = 0;
  //minSizeTCP = 0;
  //maxSizeTCP = 0;
   
  //totalUPDPackets = 0;
  //averageSizeUDP = 0;
  //minSizeUDP = 0;
  //maxSizeUDP = 0;
  
  //totalOtherTransportPackets = 0;
}


// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to pr all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {

  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
  
  //link layer
  std::cout << "There are " << totalEthernetIIFrames << " total Ethernet II frames." << std::endl;
  std::cout << "There are " << number802frames << " total 802.3 frames." << std::endl;
  
 	//network layer 
 	std::cout << "There are " << totalArpPackets << " total ARP packets." << std::endl;
 	
  std::cout << "There are " << totalIP4Packets << " total IPv4 packets." << std::endl;
  
  std::cout << "There are " << totalIP6Packets << " total IPv6 packets." << std::endl; 
  
  std::cout << "There are " << totalOtherNetworkPackets << " total other network layer protocol packets." << std::endl; 
  
  
  
  // PART 2
  
  cout << "There are " << destinationMacs.size() << " unique destination mac addresses." << endl;
  
}
