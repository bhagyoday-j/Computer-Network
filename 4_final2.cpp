#include <iostream>
#include <string>

using namespace std;

// Convert integer to IP string
string intToIP(unsigned int ip)
{
    return to_string((ip >> 24) & 255) + "." +
           to_string((ip >> 16) & 255) + "." +
           to_string((ip >> 8) & 255) + "." +
           to_string(ip & 255);
}

// Print 32-bit binary 
void printBinary32(unsigned int num)
{
    for (int i = 31; i >= 0; i--)
    {
        cout << ((num >> i) & 1);

        if (i % 8 == 0 && i != 0)
            cout << " ";
    }
}

// Count only continuous 1s from left
int countSubnetBits(unsigned int mask)
{
    int count = 0;
    bool stop = false;

    for (int i = 31; i >= 0; i--)
    {
        if ((mask >> i) & 1)
        {
            if (!stop)
                count++;
        }
        else
        {
            stop = true;
        }
    }

    return count;
}

int main()
{
    unsigned int a, b, c, d;
    unsigned int m1, m2, m3, m4;

    cout << "Enter IP Address (4 numbers): ";

    cin >> a >> b >> c >> d;

    cout << "Enter Subnet Mask (4 numbers): ";

    cin >> m1 >> m2 >> m3 >> m4;

    // Create 32-bit IP and Mask
    unsigned int ip = (a << 24) | (b << 16) | (c << 8) | d;

    unsigned int mask = (m1 << 24) | (m2 << 16) | (m3 << 8) | m4;

    // Count subnet bits
    int subnetBits = countSubnetBits(mask);

    int hostBits = 32 - subnetBits;

    // Create prefix mask from subnet bits
    unsigned int prefixMask = 0;

    for (int i = 0; i < subnetBits; i++)
    {
        prefixMask |= (1U << (31 - i));
    }

    // Subnet Address
    unsigned int network = ip & prefixMask;

    // Total Addresses
    unsigned long long totalAddresses = 1;

    for (int i = 0; i < hostBits; i++)
    {
        totalAddresses *= 2;
    }

    // Broadcast Address
    unsigned long long broadcastNumber = (unsigned long long)network + totalAddresses - 1;

    unsigned int broadcast = (unsigned int)broadcastNumber;

    // First Host
    unsigned int firstHost = 0;

    if (hostBits >= 2)
    {
        firstHost = network + 1;
    }

    // Last Host
    unsigned int lastHost = 0;

    if (hostBits >= 2)
    {
        lastHost = broadcast - 1;
    }

    // Usable Hosts
    unsigned long long usableHosts;

    if (hostBits >= 2)
    {
        usableHosts = totalAddresses - 2;
    }
    else
    {
        usableHosts = 0;
    }

    // Output
    cout << "\n========== 32-BIT ==========\n";

    cout << "IP (32-bit)     : ";
    printBinary32(ip);
    cout << endl;

    cout << "Mask (32-bit)   : ";
    printBinary32(mask);
    cout << endl;

    cout << "AND Result      : ";
    printBinary32(network);
    cout << endl;

    cout << "Subnet Address  : "
         << intToIP(network)
         << endl;

    cout << "First Host      : "
         << intToIP(firstHost)
         << endl;

    cout << "Last Host       : "
         << intToIP(lastHost)
         << endl;

    cout << "Broadcast       : "
         << intToIP(broadcast)
         << endl;

    cout << "Subnet Bits     : "
         << subnetBits
         << endl;

    cout << "Host Bits       : "
         << hostBits
         << endl;

    cout << "Total Addresses : "
         << totalAddresses
         << endl;

    cout << "Usable Hosts    : "
         << usableHosts
         << endl;

    return 0;
}