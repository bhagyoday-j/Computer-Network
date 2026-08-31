#include <iostream>
#include <string>
#include <cmath>

using namespace std;

// Convert integer to IP string
string intToIP(unsigned int ip)
{
    return to_string((ip >> 24) & 255) + "." +
           to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." +
           to_string(ip & 255);
}

// Convert integer to binary
string toBinary(unsigned int num)
{
    string temp = "";

    for (int i = 31; i >= 0; i--)
    {
        temp += ((num >> i) & 1) ? '1' : '0';

        if (i % 8 == 0 && i != 0)
            temp += '.';
    }

    return temp;
}

int main()
{
    unsigned int a, b, c, d;
    unsigned int m1, m2, m3, m4;

    cout << "Enter IP Address (a b c d): ";
    cin >> a >> b >> c >> d;

    cout << "Enter Subnet Mask (m1 m2 m3 m4): ";
    cin >> m1 >> m2 >> m3 >> m4;

    // Create 32-bit IP and Mask
    unsigned int ip = (a << 24) | (b << 16) | (c << 8) | d;
    unsigned int mask = (m1 << 24) | (m2 << 16) | (m3 << 8) | m4;

    // Network Address
    unsigned int network = ip & mask;

    // Broadcast Address
    unsigned int broadcast = network | (~mask);

    // First and Last Host
    unsigned int firstHost = network + 1;
    unsigned int lastHost = broadcast - 1;

    // Custom host bit counting
    // Scan from right to left and stop at first 0

    int networkBits = 0;
    bool foundFirstZero = false;

    for (int i = 0; i < 32; i++)
    {
        int bit = (mask >> i) & 1;

        if (!foundFirstZero)
        {
            if (bit == 1)
            {
                networkBits++;
            }
            else
            {
                foundFirstZero = true;
            }
        }
    }

    int hostBits = 32 - networkBits;

    long long totalAddresses = pow(2, hostBits);
    long long usableHost = pow(2, hostBits) - 2;

    //Number of networks
    long long numberOfNetworks = pow(2, 32-hostBits);

    cout << "\n========== RESULT ==========\n";

    cout << "\nIP Address (Binary):\n";
    cout << toBinary(ip) << endl;

    cout << "\nSubnet Mask (Binary):\n";
    cout << toBinary(mask) << endl;

    cout << "\nNetwork Address or Subnet Address or Network ID : " << intToIP(network) << endl;

    cout << "Broadcast Address : " << intToIP(broadcast) << endl;

    cout << "First Host : " << intToIP(firstHost) << endl;

    cout << "Last Host : " << intToIP(lastHost) << endl;

    cout << "Total Addresses(Host + Broadcast + Network) : " << totalAddresses << endl;

    cout << "Total Usable Host Addresses : " << usableHost << endl;

    cout << "Total Number of Networks : " << numberOfNetworks << endl;

    return 0;
}

/*
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

// Convert IP string to integer
unsigned int ipToInt(string ip)
{
    stringstream ss(ip);
    string part;
    unsigned int result = 0;

    for (int i = 0; i < 4; i++)
    {
        getline(ss, part, '.');
        result = (result << 8) | stoi(part);
    }

    return result;
}

// Convert integer to IP string
string intToIP(unsigned int ip)
{
    return to_string((ip >> 24) & 255) + "." +
           to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." +
           to_string(ip & 255);
}

// Convert integer to binary
string toBinary(unsigned int num)
{
    string bin = "";

    for (int i = 31; i >= 0; i--)
    {
        bin += ((num >> i) & 1) ? '1' : '0';

        if (i % 8 == 0 && i != 0)
            bin += '.';
    }

    return bin;
}

int main()
{
    string ipStr, maskStr;

    cout << "Enter IP Address : ";
    cin >> ipStr;

    cout << "Enter Subnet Mask : ";
    cin >> maskStr;

    unsigned int ip = ipToInt(ipStr);
    unsigned int mask = ipToInt(maskStr);

    // Network Address
    unsigned int network = ip & mask;

    // Broadcast Address
    unsigned int broadcast = network | (~mask);

    // First and Last Host
    unsigned int firstHost = network + 1;
    unsigned int lastHost = broadcast - 1;

    // Count host bits
    int hostBits = 0;
    unsigned int tempMask = mask;

    while ((tempMask & 1) == 0)
    {
        hostBits++;
        tempMask >>= 1;
    }

    long long totalHosts = pow(2, hostBits) - 2;

    cout << "\n========== RESULT ==========\n";

    cout << "\nIP Address (Binary):\n";
    cout << toBinary(ip) << endl;

    cout << "\nSubnet Mask (Binary):\n";
    cout << toBinary(mask) << endl;

    cout << "\nNetwork Address : "
         << intToIP(network) << endl;

    cout << "Broadcast Address : "
         << intToIP(broadcast) << endl;

    cout << "First Host : "
         << intToIP(firstHost) << endl;

    cout << "Last Host : "
         << intToIP(lastHost) << endl;

    cout << "Total Hosts per Subnet : "
         << totalHosts << endl;

    return 0;
}
*/