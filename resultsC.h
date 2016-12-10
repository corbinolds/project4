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
   vector<int> ipv4Sizes;
   
   int totalIP6Packets;
   vector<int> ipv6Sizes;
   
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

   int totalOtherTransportPackets;
   
   
   
   
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
   void addIpv4Size (int ipv4Size) { ipv4Sizes.push_back(ipv4Size); };

   void incrementTotalIP6Packets() { totalIP6Packets++; };
   void addIpv6Size (int ipv6Size) { ipv6Sizes.push_back(ipv6Size); };
   
   void incrementTotalOtherNetworkPackets() { totalOtherNetworkPackets++; };

   //transport layer


   void incrementTotalOtherTransportPackets() { totalOtherTransportPackets++; };
   
   void displayResults();


   // for finding averages and mins and maxes
   double findAverageSize(vector<int> sizeVector) {
      double average = 0.0;
      for (int i = 0; i < sizeVector.size(); i++) {
         average = average + sizeVector.at(i);
      }

      if(sizeVector.size() == 0) {
         return 0.0;
      }
      return average/sizeVector.size();
   };

   int findMinSize(vector<int> sizeVector) {
      int min = 0;
      bool isSet = false;

      for (int i = 0; i < sizeVector.size(); i++) {
         if (isSet == false || sizeVector[i] < min) {
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
         if (isSet == false || sizeVector[i] > max) {
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
