#include <iostream>
using namespace std;

void goBackN(int totalFrames, int windowSize, int errorFrame, int errorType) {
    cout << "\n=== GO-BACK-N SIMULATION ===\n";
    int i = 1;

    while (i <= totalFrames) {
        cout << "\n--- Sending Window ---" << endl;
        int sentCount = 0;

        // Send a batch up to window size
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            cout << "Sender: Sent Frame " << j << endl;
            sentCount++;
        }

        // Check if error happens in this window
        bool hasError = false;
        int failedAt = -1;

        for (int j = i; j < i + sentCount; j++) {
            if (j == errorFrame && errorType != 0) {
                hasError = true;
                failedAt = j;
                // Apply error once
                errorType = 0; 
                break;
            }
            cout << "Receiver: ACK " << j << " received by Sender." << endl;
        }

        if (hasError) {
            cout << "\n[!] ERROR DETECTED at Frame " << failedAt << "!" << endl;
            cout << "Receiver: Discarding all subsequent frames." << endl;
            cout << "Sender: Timeout! Retransmitting ALL frames from Frame " << failedAt << " onwards...\n";
            i = failedAt; // Go Back to N
        } else {
            i += sentCount; // Move window forward
        }
    }
    cout << "\n>>> All frames transmitted successfully using Go-Back-N! <<<\n";
}

void selectiveRepeat(int totalFrames, int windowSize, int errorFrame, int errorType) {
    cout << "\n=== SELECTIVE REPEAT SIMULATION ===\n";
    int ackStatus[100] = {0}; // 0 = Not ACKed, 1 = ACKed
    int i = 1;

    while (i <= totalFrames) {
        cout << "\n--- Sending Window ---" << endl;
        
        // Send window frames that aren't ACKed yet
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            if (ackStatus[j] == 0) {
                cout << "Sender: Sent Frame " << j << endl;
            }
        }

        // Process Receiver Responses
        for (int j = i; j < i + windowSize && j <= totalFrames; j++) {
            if (ackStatus[j] == 1) continue;

            if (j == errorFrame && errorType != 0) {
                cout << "\n[!] ERROR DETECTED at Frame " << j << "!" << endl;
                cout << "Receiver: Frame " << j << " lost/corrupted. Sending NAK " << j << "." << endl;
                cout << "Sender: Resending ONLY Frame " << j << "...\n";
                errorType = 0; // Apply error once
                
                // Immediately retransmit and ACK only this frame
                cout << "Sender: Sent Frame " << j << " (Retransmission)" << endl;
                cout << "Receiver: ACK " << j << " received by Sender." << endl;
                ackStatus[j] = 1;
            } else {
                cout << "Receiver: ACK " << j << " received by Sender." << endl;
                ackStatus[j] = 1;
            }
        }

        // Slide window forward past all ACKed frames
        while (i <= totalFrames && ackStatus[i] == 1) {
            i++;
        }
    }
    cout << "\n>>> All frames transmitted successfully using Selective Repeat! <<<\n";
}

int main() {
    int totalFrames, windowSize, mode, errorFrame, errorType;

    cout << "Enter total number of frames to send: ";
    cin >> totalFrames;

    cout << "Enter Window Size: ";
    cin >> windowSize;

    cout << "\nSelect Protocol Mode:\n";
    cout << "1. Go-Back-N\n";
    cout << "2. Selective Repeat\n";
    cout << "Enter Choice (1 or 2): ";
    cin >> mode;

    cout << "\nSelect Error Scenario to Simulate:\n";
    cout << "0. No Error\n";
    cout << "1. Frame Lost\n";
    cout << "2. ACK Lost\n";
    cout << "3. Frame Contains Error\n";
    cout << "Enter Choice (0-3): ";
    cin >> errorType;

    if (errorType != 0) {
        cout << "Enter the Frame Number where error occurs (1 to " << totalFrames << "): ";
        cin >> errorFrame;
    } else {
        errorFrame = -1;
    }

    if (mode == 1) {
        goBackN(totalFrames, windowSize, errorFrame, errorType);
    } else if (mode == 2) {
        selectiveRepeat(totalFrames, windowSize, errorFrame, errorType);
    } else {
        cout << "Invalid protocol choice!" << endl;
    }

    return 0;
}