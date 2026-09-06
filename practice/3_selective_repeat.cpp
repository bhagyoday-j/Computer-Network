#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
  int totalFrames;
  int windowSize;
  int errorFrame = -1;
  int i = 1;
  vector<int> ackStatus(100, 0);


  cout << "Enter Total number of frames : ";
  cin >> totalFrames;

  cout << "Enter Window size : ";
  cin >> windowSize;

  cout << "\n---Chose your choice---" << endl;
  cout << "-1 \t: No error" << endl;
  cout << "1 to " << totalFrames << " : error Frame" << endl;
  cout << "Enter Your choice : ";
  cin >> errorFrame;


  cout << "\n=== SELECTIVE REPEAT SIMULATION ===\n";

  while(i <= totalFrames) {
    cout << "\n--- Sending Window ---" << endl;
    
    for(int j = i; j < i + windowSize && j <= totalFrames; j++) {
      if(ackStatus[j] == 0) {
        cout << "Sender: Sent Frame " << j << endl;
      }
    }

    vector<int> nakFrames;

    for(int j = i; j < i + windowSize && j <= totalFrames; j++) {
      if(ackStatus[j] == 1) 
        continue;
      
      if(j == errorFrame) {
        cout << "Receiver: Frame " << j << " lost/corrupted. Sending NAK " << j << "." << endl;
        nakFrames.push_back(j);
      } else {
        cout << "Receiver: Frame " << j << " received correctly. Sending ACK " << j << "." << endl;
        ackStatus[j] = 1;
      }
    }

    for(int j : nakFrames) {
      cout << "\nSender: Retransmitting Frame " << j << "..." << endl;
      cout << "Sender: Sent Frame " << j << " (Retransmission)" << endl;
      cout << "Receiver: Frame " << j << " received correctly. Sending ACK " << j << "." << endl;

      ackStatus[j] = 1;
    }

    while (i <= totalFrames && ackStatus[i] == 1) {
      i++;
    }
  }

  cout << "\n>>> All frames transmitted successfully using Selective Repeat! <<<\n";

  return 0;
}