#include <iostream>
using namespace std;

// Convert decimal to 8-bit binary
void binary(int n)
{
    for (int i = 7; i >= 0; i--)
    {
        if (n & (1 << i))
            cout << "1";
        else
            cout << "0";
    }
}

// Convert IP to 32-bit number
unsigned long long toNumber(int ip[])
{
    unsigned long long n = 0;

    for (int i = 0; i < 4; i++)
        n = n * 256 + ip[i];

    return n;
}

// Convert 32-bit number to IP
void toIP(unsigned long long n, int ip[])
{
    ip[0] = (n >> 24) & 255;
    ip[1] = (n >> 16) & 255;
    ip[2] = (n >> 8) & 255;
    ip[3] = n & 255;
}

// Count only CONTINUOUS 1s from left
int countSubnetBits(int mask[])
{
    int count = 0;
    bool stop = false;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            if (mask[i] & (1 << j))
            {
                if (!stop)
                    count++;
            }
            else
            {
                stop = true;
            }
        }
    }

    return count;
}

int main()
{
    int ip[4], mask[4], subnet[4];

    // ---------------- INPUT ----------------

    cout << "Enter IP Address (4 numbers): ";

    for (int i = 0; i < 4; i++)
        cin >> ip[i];

    cout << "Enter Subnet Mask (4 numbers): ";

    for (int i = 0; i < 4; i++)
        cin >> mask[i];

    // ---------------- SUBNET BITS ----------------

    int subnetBits = countSubnetBits(mask);

    int hostBits = 32 - subnetBits;

    // ---------------- CREATE PREFIX MASK ----------------
    // This uses only the continuous 1s.
    

    int prefixMask[4] = {0, 0, 0, 0};

    for (int i = 0; i < subnetBits; i++)
    {
        int byte = i / 8;
        int bit = 7 - (i % 8);

        prefixMask[byte] |= (1 << bit);
    }

    // ---------------- SUBNET ADDRESS ----------------

    for (int i = 0; i < 4; i++)
        subnet[i] = ip[i] & prefixMask[i];

    // ---------------- TOTAL ADDRESSES ----------------

    unsigned long long totalAddresses = 1;

    for (int i = 0; i < hostBits; i++)
        totalAddresses *= 2;

    // ---------------- SUBNET NUMBER ----------------

    unsigned long long subnetNumber = toNumber(subnet);

    // ---------------- BROADCAST ----------------

    unsigned long long broadcastNumber =
        subnetNumber + totalAddresses - 1;

    int broadcast[4];

    toIP(broadcastNumber, broadcast);

    // ---------------- FIRST HOST ----------------

    int firstHost[4];

    if (hostBits >= 2)
    {
        toIP(subnetNumber + 1, firstHost);
    }

    // ---------------- LAST HOST ----------------

    int lastHost[4];

    if (hostBits >= 2)
    {
        toIP(broadcastNumber - 1, lastHost);
    }

    // ---------------- USABLE HOSTS ----------------

    unsigned long long usableHosts;

    if (hostBits >= 2)
        usableHosts = totalAddresses - 2;
    else
        usableHosts = 0;

    // ---------------- OUTPUT ----------------

    cout << "\n========== 32-BIT ==========\n";

    cout << "IP (32-bit)     : ";

    for (int i = 0; i < 4; i++)
    {
        binary(ip[i]);

        if (i != 3)
            cout << " ";
    }

    cout << endl;

    cout << "Mask (32-bit)   : ";

    for (int i = 0; i < 4; i++)
    {
        binary(mask[i]);

        if (i != 3)
            cout << " ";
    }

    cout << endl;

    cout << "AND Result      : ";

    for (int i = 0; i < 4; i++)
    {
        binary(subnet[i]);

        if (i != 3)
            cout << " ";
    }

    cout << endl;

    cout << "Subnet Address  : "
         << subnet[0] << "."
         << subnet[1] << "."
         << subnet[2] << "."
         << subnet[3] << endl;

    cout << "First Host      : "
         << firstHost[0] << "."
         << firstHost[1] << "."
         << firstHost[2] << "."
         << firstHost[3] << endl;

    cout << "Last Host       : "
         << lastHost[0] << "."
         << lastHost[1] << "."
         << lastHost[2] << "."
         << lastHost[3] << endl;

    cout << "Broadcast       : "
         << broadcast[0] << "."
         << broadcast[1] << "."
         << broadcast[2] << "."
         << broadcast[3] << endl;

    cout << "Subnet Bits     : " << subnetBits << endl;
    cout << "Host Bits       : " << hostBits << endl;
    cout << "Total Addresses : " << totalAddresses << endl;
    cout << "Usable Hosts    : " << usableHosts << endl;

    return 0;
}