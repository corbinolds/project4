//
//  project4.cpp
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"
#include <vector>

using namespace std;

// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************
void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
	resultsC* results = (resultsC*)user;
	
	int ethType1 = (int)packet[12];
	int ethType2 = (int)packet[13];
	
	int ethType = (ethType1 * 256) + ethType2;
	
	//link layer
	if(ethType <= 1500) {
		results->increment802Frames();

		// increment other network and transport packets since 802.3 is different than ethernet II
		results->incrementTotalOtherNetworkPackets();
		results->incrementTotalOtherTransportPackets();
	}
	else if(ethType >= 1536) {
		results->incrementEthernetIIFrames();
		
		//network layer
		//IPv4
		if(ethType == 2048) {
			results->incrementTotalIP4Packets();

			//get packet length
			// IN IPv4 THERE IS A TOTAL LENGTH FIELD IN THE HEADER, THIS IS THAT VALUE
			int packetLength = (int)packet[16]*256 + (int)packet[17];
			results->addIpv4Size(packetLength);


			//transport layer for ipv4
			int transportPacket = (int)packet[23];
			//ICMP
			if(transportPacket == 1) {
				results->incrementTotalICMPPackets();

				//since ICMP header length is 8 bytes, subtract 8 from the length found in the Network header
				results->addICMPSize(packetLength - 8);
			}
			
			//UDP
			else if(transportPacket == 17) {
				results->incrementTotalUDPPackets();
				results->addUDPSize(packetLength - 8.0);
			}

			//TCP
			else if(transportPacket == 6) {
				results->incrementTotalTCPPackets();

				int tcpPacket = (int)packet[14] % (16);
				int tcpLength = (int)(packet[tcpPacket + 12] - (packet[tcpPacket + 12] % 16)) / 4;
				
				results->addTCPSize(packetLength - tcpLength);

				//CHECK SYN AND FIN ONLY TCP HAS
				if((packet[67] & 2) == 2) {
					results->incrementSynPacket();
				} 
				if((packet[67] & 1) == 1) {
					results->incrementFinPacket();
				}
			}

			else {
				results->incrementTotalOtherTransportPackets();
			}

		}

		//IPv6
		else if(ethType == 34525) {
			results->incrementTotalIP6Packets();

			// IN IPv6 THERE IS A PAYLOAD LENGTH FIELD IN THE HEADER, THIS IS THAT VALUE
			int packetLength = (int)packet[18]*256 + (int)packet[19];
			results->addIpv6Size(packetLength);

			//transport layer for ipv6
			//NEXT HEADER FIELD IN THE HEADER
			int transportPacket = (int)packet[20];
			//ICMP
			//CHECKS FOR IPv6 ICMP BECAUSE WE ARE USING IPv6 
			if(transportPacket == 58) {
				results->incrementTotalICMPPackets();

				//since ICMP header length is 8 bytes, subtract 8 from the length found in the Network header
				results->addICMPSize(packetLength - 8);
			}
			
			//UDP
			else if(transportPacket == 17) {
				results->incrementTotalUDPPackets();
				results->addUDPSize(packetLength - 8.0);
			}

			//TCP
			else if(transportPacket == 6) {
				results->incrementTotalTCPPackets();

				int tcpLength = (int)(packet[66] - (packet[66] % 16)) / 4;

				results->addTCPSize(packetLength - tcpLength);

				//CHECK SYN AND FIN ONLY TCP HAS
				if((packet[67] & 2) == 2) {
					results->incrementSynPacket();
				} 
				if((packet[67] & 1) == 1) {
					results->incrementFinPacket();
				}

			}

			else {
				results->incrementTotalOtherTransportPackets();
			}
		}

		//ARP
		else if(ethType == 2054) {
			results->incrementTotalArpPackets();
			results->addArpSize(60);

			// ARP DOESN'T HAVE ANY TRANSPORT LAYER SO NO TRANSPORT LAYER INCREMENT NEEDED
		}

		else {
			results->incrementTotalOtherNetworkPackets();
			results->incrementTotalOtherTransportPackets();
		}
		
	}
	

	
	int destinationMac1 = (int)packet[0];
	int destinationMac2 = (int)packet[1];
	int destinationMac3 = (int)packet[2];
	int destinationMac4 = (int)packet[3];
	int destinationMac5 = (int)packet[4];
	int destinationMac6 = (int)packet[5];
	
	int destinationMac = (destinationMac1 * 1280) + (destinationMac2 * 1024) + (destinationMac3 * 768) + (destinationMac4 * 512) + (destinationMac5 * 256) + destinationMac6;
	bool isUniqueDest = true;

	for(int i = 0; i < results->getDestinationMacs().size(); i++) {
		if (results->getDestinationMacs().at(i) == destinationMac) {
			isUniqueDest = false;
			break;
		}
	}
	
	if(isUniqueDest) {
		results->addDestinationMac(destinationMac);
	}

	int sourceMac1 = (int)packet[6];
	int sourceMac2 = (int)packet[7];
	int sourceMac3 = (int)packet[8];
	int sourceMac4 = (int)packet[9];
	int sourceMac5 = (int)packet[10];
	int sourceMac6 = (int)packet[11];
	
	int sourceMac = (sourceMac1 * 1280) + (sourceMac2 * 1024) + (sourceMac3 * 768) + (sourceMac4 * 512) + (sourceMac5 * 256) + sourceMac6;
	bool isUniqueSource = true;

	for(int i = 0; i < results->getSourceMacs().size(); i++) {
		if (results->getSourceMacs().at(i) == sourceMac) {
			isUniqueSource = false;
			break;
		}
	}
	
	if(isUniqueSource) {
		results->addSourceMac(sourceMac);
	}

	//increment total packet count
  results->incrementPacketCount();

  return;
}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, const char * argv[])
{

  
  // **********************************************************************
  // * The program is called with a single argument, the name of the
  // * pcap save file to read.
  // **********************************************************************
  if (argc != 2) {
     std::cerr << "useage: project4 <filename>" << std::endl;
     exit(EXIT_FAILURE);
  }


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(argv[1],errbuf)) == NULL ) {
    std::cerr << "Unable to open pcap file: " << argv[1] << "\n"
         << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (strlen(errbuf) > 0)
    std::cerr << "Warning: pcap_open_offiline: " << pcap_geterr(PT) << std::endl;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    std::cerr << "Error calling dispatcher: " << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Dispatcher finished with " << pk_count << " packets left in the queue." << std::endl;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}


