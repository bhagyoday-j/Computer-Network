#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int n, window;

    cout << "Enter total number of frames: ";
    cin >> n;

    cout << "Enter window size: ";
    cin >> window;

    int base = 0;

    while (base < n)
    {
        int end = min(base + window, n);

        cout << "\n====================================";
        cout << "\nCurrent Window: ";

        for (int i = base; i < end; i++)
            cout << i << " ";

        // ---------------- SENDER ----------------
        cout << "\n\n--- Sender ---\n";

        for (int i = base; i < end; i++)
            cout << "Sending Frame " << i << endl;


        // ---------------- RECEIVER ----------------
        cout << "\n--- Receiver ---\n";

        vector<int> received;

        cout << "Enter received frames in arrival order:\n";

        for (int i = base; i < end; i++)
        {
            int frame;

            cout << "Received frame: ";
            cin >> frame;

            received.push_back(frame);
        }


        // ---------------- GBN RECEIVER ----------------

        int expected = base;
        int errorFrame = -1;

        cout << "\n--- Receiver Processing ---\n";

        for (int frame : received)
        {
            if (frame == expected)
            {
                cout << "Frame " << frame
                     << " received correctly." << endl;

                cout << "ACK " << frame
                     << " sent." << endl;

                expected++;
            }
            else
            {
                cout << "Frame " << frame
                     << " received out of order." << endl;

                cout << "Frame " << frame
                     << " discarded." << endl;

                if (errorFrame == -1)
                    errorFrame = expected;
            }
        }


        // ---------------- NO ERROR ----------------

        if (errorFrame == -1)
        {
            cout << "\nAll frames in window received correctly."
                 << endl;

            base = end;
        }


        // ---------------- ERROR ----------------

        else
        {
            cout << "\nError detected at Frame "
                 << errorFrame << endl;

            cout << "\n--- Go-Back-N Retransmission ---\n";

            // Retransmit from error frame
            for (int i = errorFrame; i < end; i++)
            {
                cout << "Retransmitting Frame "
                     << i << endl;

                cout << "Frame " << i
                     << " received correctly." << endl;

                cout << "ACK " << i
                     << " sent." << endl;
            }

            // After successful retransmission,
            // whole window is acknowledged
            base = end;
        }
    }

    cout << "\n====================================";
    cout << "\nAll frames transmitted successfully.";
    cout << "\nTransmission completed.";
    cout << "\n====================================\n";

    return 0;
}