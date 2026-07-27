/*
Algorithm:
1. Enter the 4 data bit.
2. Generate three parity bit (even parity) as P1,P2,and P4.

P1=d[3] d[5] d[7]
P2= d[3] d[6] d[7]
P4= d[5] d[6] d[7]

3. Form the 7-bit hamming code and send it to receiver.
4. Receive the 7-bit hamming code .
5. Generate the even parity bit to check the error position as

E1= P[1]d[3] d[5] d[7]
E2= P[2]d[3] d[6] d[7]
E3=P[4] d[5] d[6] d[7]

6. Convert binary value(E3,E2,E1) into decimal to get the error position and print it.
7. Take the ones complement of the bit at that position.
8. Print the 7- bit hamming code as error corrected code.
*/

#include <iostream>
using namespace std;

int main()
{
    int h[8]; // Index 1 to 7

    cout << "Enter 4 data bits (d7 d6 d5 d3): ";
    cin >> h[7];
    cin >> h[6];
    cin >> h[5];
    cin >> h[3];

    int r1 = h[3] ^ h[5] ^ h[7];
    int r2 = h[3] ^ h[6] ^ h[7];
    int r4 = h[5] ^ h[6] ^ h[7];

    h[1] = r1;
    h[2] = r2;
    h[4] = r4;

    cout << "\nGenerated 7-bit Hamming Code: ";
    for(int i = 7; i >  0; i--)
        cout << h[i];

    int r[8];

    cout << "\n\nEnter received 7-bit Hamming Code: ";
    for(int i = 7; i > 0; i--)
        cin >> r[i];

    int c1 = r[1] ^ r[3] ^ r[5] ^ r[7];
    int c2 = r[2] ^ r[3] ^ r[6] ^ r[7];
    int c3 = r[4] ^ r[5] ^ r[6] ^ r[7];

    int errorPos = c3 * 4 + c2 * 2 + c1;

    if(errorPos == 0) {
        cout << "\nNo Error Detected.";
    } else {
        cout << "\nError Detected at Position: " << errorPos;

        // Correct the error
        r[errorPos] = !r[errorPos];

        cout << "\nCorrected Hamming Code: ";
        for(int i = 7; i > 0; i--)
            cout << r[i];
    }

    cout << endl;
    return 0;
}

