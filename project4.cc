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
	
	if(ethType <= 1500) {
		results->increment802Frames();
	}
	else if(ethType >= 1536) {
		results->incrementEthernetIIFrames();
		
		if(ethType == 2048) {
			results->incrementTotalIP4Packets();
		}
		else if(ethType == 34525) {
			results->incrementTotalIP6Packets();
		}
		else if(ethType == 2054) {
			results->incrementTotalArpPackets();
		}
		else {
			results->incrementTotalOtherNetworkPackets();
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


