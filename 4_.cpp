#include <iostream>
#include <vector>
#include <string>
using namespace std;


string decToBin(int num) {

    string ans = "";

    for (int i = 7; i >= 0; i--) {

        if (num & (1 << i))
            ans += '1';
        else
            ans += '0';
    }

    return ans;
}


void displayIP(vector<int> ip) {

    for (int i = 0; i < 4; i++) {

        cout << ip[i];

        if (i != 3)
            cout << ".";
    }
}


void displayBinary(vector<int> ip) {

    for (int i = 0; i < 4; i++) {

        cout << decToBin(ip[i]);

        if (i != 3)
            cout << ".";
    }
}


vector<int> acceptIP() {

    vector<int> ip(4);

    cout << "Enter IP address (use spaces instead of dots): ";

    for (int i = 0; i < 4; i++) {
        cin >> ip[i];
    }

    return ip;
}


vector<int> acceptSubnetMask() {

    vector<int> mask(4);

    cout << "Enter Subnet Mask (use spaces instead of dots): ";

    for (int i = 0; i < 4; i++) {
        cin >> mask[i];
    }

    return mask;
}


int findPrefix(vector<int> mask) {

    int prefix = 0;

    for (int i = 0; i < 4; i++) {

        for (int j = 7; j >= 0; j--) {

            if (mask[i] & (1 << j))
                prefix++;
            else
                break;
        }
    }

    return prefix;
}


vector<int> findSubnet(vector<int> ip, vector<int> mask) {

    vector<int> subnet(4);

    for (int i = 0; i < 4; i++) {

        subnet[i] = ip[i] & mask[i];
    }

    return subnet;
}


vector<int> findBroadcast(vector<int> subnet,
                          vector<int> mask) {

    vector<int> broadcast(4);

    for (int i = 0; i < 4; i++) {

        broadcast[i] = subnet[i] | (255 - mask[i]);
    }

    return broadcast;
}


void netMasking() {


    vector<int> ip = acceptIP();

    vector<int> mask = acceptSubnetMask();



    int prefix = findPrefix(mask);



    int hostBits = 32 - prefix;



    long long totalAddresses = 1LL << hostBits;



    long long usableHosts = totalAddresses - 2;


    

    vector<int> subnet = findSubnet(ip, mask);



    vector<int> broadcast = findBroadcast(subnet, mask);



    vector<int> firstHost = subnet;

    firstHost[3]++;



    vector<int> lastHost = broadcast;

    lastHost[3]--;



    cout << "\n============================================\n";
    cout << "              SUBNETTING RESULT\n";
    cout << "============================================\n";


    cout << "\nIP Address          : ";
    displayIP(ip);


    cout << "\nIP Address (Binary) : ";
    displayBinary(ip);


    cout << "\n\nSubnet Mask         : ";
    displayIP(mask);


    cout << "\nSubnet Mask (Binary): ";
    displayBinary(mask);


    //cout << "\n\nCIDR Prefix         : /" << prefix;


    cout << "\nHost Bits           : " << hostBits;


    cout << "\nTotal Addresses     : " << totalAddresses;


    cout << "\nUsable Hosts        : " << usableHosts;


    cout << "\n\n--------------------------------------------";


    cout << "\nSubnet Address      : ";
    displayIP(subnet);


    cout << "\nSubnet Address Binary: ";
    displayBinary(subnet);


    cout << "\n\nFirst Host Address  : ";
    displayIP(firstHost);


    cout << "\nFirst Host Binary   : ";
    displayBinary(firstHost);


    cout << "\n\nLast Host Address   : ";
    displayIP(lastHost);


    cout << "\nLast Host Binary    : ";
    displayBinary(lastHost);


    cout << "\n\nBroadcast Address   : ";
    displayIP(broadcast);


    cout << "\nBroadcast Binary    : ";
    displayBinary(broadcast);


    cout << "\n============================================\n";
}


int main() {

    netMasking();

    return 0;
}