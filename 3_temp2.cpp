#include <iostream>
#include <vector>
using namespace std;

void goBackN(vector<int>& sender) {
    int n = sender.size();
    int framesz, err;

    cout << "\nEnter the Window/Frame Size : ";
    cin >> framesz;

    cout << "Enter the Error Frame Number : ";
    cin >> err;

    cout << "\n========== GO-BACK-N ==========\n";

    int start = 0;

    while (start < n) {
        int end = min(start + framesz, n);

        cout << "\nFrames Sent:\n";

        bool errorFound = false;

        // Sending current window
        for (int i = start; i < end; i++) {
            cout << "Frame " << i + 1 << " sent\n";
        }

        cout << "\nFrames Received:\n";

        // Receiving current window
        for (int i = start; i < end; i++) {

            if (i + 1 == err && !errorFound) {
                cout << "Frame " << i + 1 << " : ERROR\n";
                errorFound = true;
            }
            else if (errorFound) {
                cout << "Frame " << i + 1 << " : Discarded\n";
            }
            else {
                cout << "Frame " << i + 1 << " : Received\n";
                cout << "ACK " << i + 1 << " : Success\n";
            }
        }

        // Error occurred
        if (errorFound) {
            cout << "\nError detected at Frame " << err;
            cout << "\nRetransmitting from Frame " << err << "...\n";

            start = err - 1;

            // Error should happen only once
            err = -1;
        }
        else {
            start = end;
        }
    }

    cout << "\nAll frames transmitted successfully!\n";
}


void selectiveRepeat(vector<int>& sender) {
    int n = sender.size();
    int framesz, err;

    cout << "\nEnter the Window/Frame Size : ";
    cin >> framesz;

    cout << "Enter the Error Frame Number : ";
    cin >> err;

    cout << "\n========== SELECTIVE REPEAT ==========\n";

    int start = 0;
    bool errorHandled = false;

    while (start < n) {

        int end = min(start + framesz, n);

        cout << "\nFrames Sent:\n";

        // Send current window
        for (int i = start; i < end; i++) {
            cout << "Frame " << i + 1 << " sent\n";
        }

        cout << "\nFrames Received:\n";

        // Receive current window
        for (int i = start; i < end; i++) {

            if (i + 1 == err && !errorHandled) {
                cout << "Frame " << i + 1 << " : ERROR\n";
                cout << "NACK " << i + 1 << " : Failure\n";
            }
            else {
                cout << "Frame " << i + 1 << " : Received\n";
                cout << "ACK " << i + 1 << " : Success\n";
            }
        }

        // Retransmit only erroneous frame
        if (!errorHandled && err >= start + 1 && err <= end) {

            cout << "\nError detected at Frame " << err;
            cout << "\nSelective Repeat: Retransmitting only Frame "
                 << err << "...\n";

            cout << "Frame " << err << " sent\n";
            cout << "Frame " << err << " : Received\n";
            cout << "ACK " << err << " : Success\n";

            errorHandled = true;
        }

        start = end;
    }

    cout << "\nAll frames transmitted successfully!\n";
}


int main() {

    int n;

    cout << "\nEnter the total number of frames : ";
    cin >> n;

    vector<int> temp(n);

    for (int i = 0; i < n; i++) {
        temp[i] = i + 1;
    }

    bool run = true;
    int ch;

    while (run) {

        cout << "\n\n========== MENU ==========\n";
        cout << "1. Go-Back-N\n";
        cout << "2. Selective Repeat\n";
        cout << "3. Exit\n";

        cout << "Enter your choice : ";
        cin >> ch;

        switch (ch) {

            case 1:
                goBackN(temp);
                break;

            case 2:
                selectiveRepeat(temp);
                break;

            case 3:
                run = false;
                cout << "\nProgram exited.\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }
    }

    return 0;
}