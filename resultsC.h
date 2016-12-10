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
   vector<int> arpSizes;
   
   int totalIP4Packets;
   vector<int> ip4sizes;
   
   int totalIP6Packets;
   vector<int> ip6sizes;
   
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
   void addArpSize (int arpSize) { arpSizes.push_back(arpSize); };

   
   void incrementTotalIP4Packets() { totalIP4Packets++; };
   
   void incrementTotalIP6Packets() { totalIP6Packets++; };
   
   void incrementTotalOtherNetworkPackets() { totalOtherNetworkPackets++; };
   
   void displayResults();

   // for finding averages and mins and maxes
   int findAverageSize(vector<int> sizeVector) {
      int average = 0;
      for (int i = 0; i < sizeVector.size(); i++) {
         average = average + sizeVector.at(i);
      }

      return average/sizeVector.size();
   };

   int findMinSize(vector<int> sizeVector) {
      int min = 0;
      bool isSet = false;

      for (int i = 0; i < sizeVector.size(); i++) {
         if (sizeVector[i] < min || isSet == false) {
            min = sizeVector[i];
            isSet = true;
         }
      }

      return min;
   };

   int findMaxSize(vector<int> sizeVector) {
      int max = 0;
      bool isSet = false;

      for (int i = 0; i < sizeVector.size(); i++) {
         if (sizeVector[i] > max || isSet == false) {
            max = sizeVector[i];
            isSet = true;
         }
      }

      return max;
   };
   
   
   //PART 2 
   vector<int> getDestinationMacs() { return destinationMacs; };
   
   void addDestinationMac(int macAddress) { destinationMacs.push_back(macAddress); };
};

#endif
