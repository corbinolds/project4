//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include <vector>

using namespace std;

#ifndef resultsC_h
#define resultsC_h

class resultsC {
  protected:
   int totalPacketCount;
   // link layer
   int totalEthernetIIFrames;
   int number802frames;
   
   // network layer
   int totalArpPackets;
   //int averageSizeArp;
   //int minSizeArp;
   //int maxSizeArp;
   
   int totalIP4Packets;
   //int averageSizeIP4;
   //int minSizeIP4;
   //int maxSizeIP4;
   
   int totalIP6Packets;
   //int averageSizeIP6;
   //int minSizeIP6;
   //int maxSizeIP6;
   
   int totalOtherNetworkPackets;
   
   // transport layer
   //int totalICMPPakcets;
   //int averageSizeICMP;
   //int minSizeICMP;
   //int maxSizeICMP;
   
   //int totalTCPPackets;
   //int averageSizeTCP;
   //int minSizeTCP;
   //int maxSizeTCP;
   
   //int totalUPDPackets;
   //int averageSizeUDP;
   //int minSizeUDP;
   //int maxSizeUDP;
   
   
   
   
   //PART 2
   vector<int> destinationMacs;

  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   
   //link layer
   void incrementEthernetIIFrames() { totalEthernetIIFrames++; };
   void increment802Frames() { number802frames++; };
   
   //network layer
   void incrementTotalArpPackets() { totalArpPackets++; };
   
   void incrementTotalIP4Packets() { totalIP4Packets++; };
   
   void incrementTotalIP6Packets() { totalIP6Packets++; };
   
   void incrementTotalOtherNetworkPackets() { totalOtherNetworkPackets++; };
   
   void displayResults();
   
   
   //PART 2 
   vector<int> getDestinationMacs() { return destinationMacs; };
   
   void addDestinationMac(int macAddress) { destinationMacs.push_back(macAddress); };
};

#endif
