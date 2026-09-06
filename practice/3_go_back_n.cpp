#include <iostream>
#include <vector>
using namespace std;

int main() {
    int totalFrames;
    int windowSize;
    int errorFrame;

    cout << "Enter Total number of frames : ";
    cin >> totalFrames;

    cout << "Enter Window size : ";
    cin >> windowSize;

    cout << "\n---Choose your choice---" << endl;
    cout << "-1 \t: No error" << endl;
    cout << "1 to " << totalFrames << " : Error Frame" << endl;
    cout << "Enter Your choice : ";
    cin >> errorFrame;

    cout << "\n=== GO-BACK-N SIMULATION ===\n";

    int i = 1;
    bool errorOccurred = false;

    while (i <= totalFrames) {

        cout << "\n--- Sending Window ---\n";

        int sentCount = 0;

        // Send current window
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            cout << "Sender: Sent Frame " << j << endl;
            sentCount++;
        }

        bool hasError = false;
        int failedFrame = -1;

        // Process ACKs
        for (int j = i; j < i + sentCount; j++) {

            if (j == errorFrame && !errorOccurred) {
                cout << "Receiver: Frame " << j
                     << " lost/corrupted." << endl;

                hasError = true;
                failedFrame = j;
                errorOccurred = true;
                break;
            }

            cout << "Receiver: ACK " << j
                 << " received by Sender." << endl;
        }

        if (hasError) {
            cout << "\nSender: Go Back and retransmit from Frame "
                 << failedFrame << endl;

            i = failedFrame;   // Go back to failed frame
        } else {
            i += sentCount;    // Slide window
        }
    }

    cout << "\n>>> All frames transmitted successfully using Go-Back-N! <<<\n";

    return 0;
}