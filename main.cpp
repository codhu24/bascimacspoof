#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;
void spoof(const string &interface,const string &new_mac) {
    string down_cmd="ifconfig "+interface + " down";
    if(system(down_cmd.c_str())!=0) 
    {
        cerr<<"[-] Failed to bring the interface down."<<endl;
        return;
    }
    string mac_cmd="ifconfig "+interface+" hw ether "+new_mac;
    if(system(mac_cmd.c_str())!=0) 
    {
        cerr<<"[-] Failed to set the new MAC address." << endl;
        return;
    }
    string up_cmd="ifconfig " +interface+ " up";
    if(system(up_cmd.c_str()) != 0) 
    {
        cerr<<"[-] Failed to bring the interface up."<<endl;
        return;
    }
    cout<<"[+] MAC address successfully changed to "<<new_mac<<" on interface "<<interface << endl;
}
int main(int argc, char* argv[]) 
{
    if(argc!=3) 
    {
        cerr<<"Usage: " << argv[0] << " <interface> <new_mac>" << endl;
        cerr<<"Example: " <<argv[0] <<" eth0 00:11:22:33:44:55" << endl;
        return 1;
    }
    string interface=argv[1];
    string new_mac=argv[2];
    if(new_mac.length()!=17||count(new_mac.begin(),new_mac.end(), ':')!=5) 
    {
        cerr<<"[-] Invalid MAC format. Please use the format: 00:11:22:33:44:55" << endl;
        return 1;
    }
    if(interface.empty()) 
    {
        cerr << "[-] Invalid interface. Please provide a valid network interface." << endl;
        return 1;
    }
    spoof(interface, new_mac);

    return 0;
}
