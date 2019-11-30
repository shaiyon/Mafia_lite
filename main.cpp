#include "Mafia_lite.h"
#include <iostream>
#include <unistd.h>
using namespace std;

void shuffleArray(int arr[], int n);

int main() {
    // Initial prompt to user
    cout << "Welcome to Maifa lite!\nNumber of players (5-8): ";
    int numPlayers = 0;
    while (numPlayers<5 || numPlayers>8) {
        cin >> numPlayers;
    }

    // Get names from user
    Player players[numPlayers]; 
    for (int i = 0; i < numPlayers; i++) {
        cout << "Player " << i+1 << " name: ";
        string name;
        cin >> name;
        players[i].setName(name);
    }

    // Assign random roles to players
    int roleNums[numPlayers];
    srand(time(NULL));
    for (int i = 0; i < numPlayers; i++) {
        roleNums[i] = i;
    }
    int numMafia = numPlayers/2;
    int numTown = numPlayers - numMafia;
    shuffleArray(roleNums, numPlayers);
    for (int i = 0; i < numMafia; i++) {
        players[roleNums[i]].setRole(MAFIA);
    }
    for (int i = 0; i < numTown; i++) {
        players[roleNums[i]].setRole(TOWN);
    }

    // Show players their roles
    for (int i = 0; i < numPlayers; i++) {
        cout << players[i].getName() << ", ready to see your role (Y/N)?  ";
        string answer = "";
        while (!(answer == "Y")) {
            cin >> answer;
        }
        if (players[i].getRole() == MAFIA)
            cout << "You are MAFIA..." << endl;
        else
            cout << "You are TOWN.";
        sleep(5);   
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
    }

    cout << "And now, the game begins. If you're town, try not to let 3 people die." << endl;
    cout << "If you're mafia, trust no one." << endl << endl;
    // Game rounds
    int numRounds = 5;
    int numSave[numRounds]; 
    for (int i = 0; i < numRounds; i++) {
        numSave[i] = numRounds % i + numTown/2;
    }
    for (int i = 1; i <= numRounds; i++) {
        bool killed = false;
        cout << "Beginning: Round " << i << " of " << numRounds << endl << endl;
        sleep(2);
        // Talking Phase
        cout << "Talking Phase" << endl << endl;
        cout << "Who will secure the town (Pick 2)? You have 1:30 to decide";
        sleep(90);
        // Voting Phase
        cout << endl << "Voting Phase" << endl << endl;
        cout << "So, who will it be? Pick " << numSave[i] << " of the following players: " << endl;
        for (int j = 0; j < numPlayers; j++) {
            cout << players[j].getName() << " ";
        }
        cout << endl;
        string playerSecuring[numSave[i]];
        for (int j = 0; j < numSave[j]; i++) {
            cin >> playerSecuring[j];
        }
        // Mission Phase 
        cout << endl << "Mission Phase" << endl << endl;
        // Info about mission phase in first round of a game
        if (i = 1) {
            cout << "Input your turn after the 10 second wait period. Don't mess up, or you'll look suspicious!" << endl;
            sleep(1);
            cout << "Mafia can secure the town or commit a murder." << endl;
            sleep(1);
            cout << "Town just has to sit tight. But pretend you're thinking!" << endl;
            sleep(1);
            cout << endl;
        }
        // Each player's turn
        for (int j = 0; j < numPlayers; j++) {
            bool isSecuring = false;
            for (int k = 0; k < numSave[i]; k++) {
                if (playerSecuring[k] == players[j].getName())
                    isSecuring = true;
            }
            cout <<  players[j].getName() << "'s turn. Ready (Y/N)? ";
            string answer = "";
            while (answer != "Y") {
                cin >> answer;
            }
            cout << endl;
            // Different caes for if player is Mafia, town or town and securing
            if (players[j].getRole() == MAFIA && isSecuring) {
                cout << "Kill somebody, or secure the town (kill/secure)? ";
                sleep(10);
                answer = "";
                while (answer != "kill" || answer != "secure") {
                    cin >> answer;
                }
                if (answer == "kill")
                    killed = true;
            }
            else if (players[j].getRole() == TOWN && isSecuring) {
                cout << "Securing the town!";
                sleep(10);
            }
            else {
                cout << "You can't do anything this turn.";
            }
            cout << endl;
            cout << "Next players turn now.";
            sleep(4);
            cout << "\n\n\n\n\n\n\n\n\n\n";
        }
    }
    return 0;

}
 