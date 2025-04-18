#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
using namespace std;

void spoof(const string &interface, const string &new_mac) {
    // Add spaces between commands!
    string down_cmd = "ifconfig " + interface + " down";
    system(down_cmd.c_str());

    string mac_cmd = "ifconfig " + interface + " hw ether " + new_mac;
    system(mac_cmd.c_str());

    string up_cmd = "ifconfig " + interface + " up";
    system(up_cmd.c_str());

    cout << "[+] MAC address changed to " << new_mac << " on " << interface << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <interface> <new_mac>" << endl;
        cerr << "Example: " << argv[0] << " eth0 00:11:22:33:44:55" << endl;
        return 1;
    }

    string interface = argv[1];
    string new_mac = argv[2];

    if (new_mac.length() != 17 || count(new_mac.begin(), new_mac.end(), ':') != 5) {
        cerr << "[-] Invalid MAC format. Use 00:11:22:33:44:55" << endl;
        return 1;
    }

    spoof(interface, new_mac);
    return 0;
}