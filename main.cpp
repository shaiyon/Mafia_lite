// Mafia_lite
// Text based multiplayer Mafia style game.
// Shaiyon Hariri

#include <iostream>
#include <unistd.h>
#include <vector>
using namespace std;

void shuffleArray(int arr[], int n);
void checkWin(int k, int s);

enum role { MAFIA, TOWN };

struct Player {
    string name;
    role r;
};    

int main() {
    // Initial prompt to user
    cout << "Welcome to maifa lite!\nNumber of players (5-8): ";
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
        players[i].name = name;
    }

    int numRounds = 5;
    int numMafia;
    int numTown;
    int numSecure[numRounds];
     // Number of players who secure each round (varies by numPlayers)
     // And number of mafia / town 
    if (numPlayers == 5) {
        int a[] = {2, 3, 2, 3, 3};
        copy(a, a+numRounds, numSecure);
        numMafia = 2;
        numTown = 3;
    }
    else if (numPlayers == 6) {
        int a[] = {2, 3, 4, 3, 4};
        copy(a, a+numRounds, numSecure);
        numMafia = 2;
        numTown = 3;
    }
    else if (numPlayers == 7) {
        int a[] = {2, 3, 3, 4, 4};
        copy(a, a+numRounds, numSecure);
        numMafia = 3;
        numTown = 4;
    }
    else {
        int a[] = {3, 4, 4, 5, 5};
        copy(a, a+numRounds, numSecure);
        numMafia = 3;
        numTown = 5;
    }
    // Assign random roles to players
    int roleNums[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        roleNums[i] = i;
    }
    srand(time(NULL));
    shuffleArray(roleNums, numPlayers);
    for (int i = 0; i < numMafia; i++) {
        players[roleNums[i]].r = MAFIA;
    }
    for (int i = numMafia; i < numPlayers; i++) {
        players[roleNums[i]].r = TOWN;
    }

    // Keep track of game score
    int numKilled = 0;
    int numSecured = 0;
    // Show players their roles discreetly
    for (int i = 0; i < numPlayers; i++) {
        cout << players[i].name << ", ready to see your role? (y) ";
        string answer = "";
        while (!(answer == "y")) {
            cin >> answer;
        }
        if (players[i].r == MAFIA)
            cout << "You are mafia..." << endl;
        else
            cout << "You are town.";
        sleep(1);   
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
    }

    cout << "And now, the game begins. If you're town, try not to let 3 people die." << endl;
    cout << "Trust no one." << endl << endl;

    // Game rounds
    for (int i = 0; i < numRounds; i++) {
        // Check if win conditions have been met
        checkWin(numKilled, numSecured);
        bool killed = false;
        int numKilledThisRound = 0;
        cout << "Beginning: Round " << i+1 << " of " << numRounds << endl << endl;
        sleep(2);
        // Talking Phase
        cout << "Voting Phase" << endl;
        cout << "Pick " << numSecure[i] << " players to secure the town. You have 1:30 to decide." << endl;
        sleep(1);
        // Voting Phase
        cout << "So, who will it be?" << endl;
        for (int j = 0; j < numPlayers; j++) {
            cout << players[j].name << " ";
        }
        cout << endl;
        string playerSecuring[numSecure[i]];
        for (int j = 0; j < numSecure[i]; j++) {
            cin >> playerSecuring[j];
        }
        // Mission Phase 
        cout << endl << "Mission Phase" << endl;
        // Info about mission phase in first round of a game
        if (i == 0) {
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
            for (int k = 0; k < numSecure[i]; k++) {
                if (playerSecuring[k] == players[j].name)
                    isSecuring = true;
            }
            cout <<  players[j].name << "'s turn. Ready? (y) ";
            string answer = "";
            while (answer != "y") {
                cin >> answer;
            }
            // Different caes for if player is Mafia, town or town and securing
            if (players[j].r == MAFIA && isSecuring) {
                cout << "Kill somebody, or secure the town? (k/s) ";
                sleep(1);
                answer = "";
                while (answer != "k" && answer != "s") {
                    cin >> answer;
                }                
                if (answer == "k") {
                    numKilledThisRound++;
                }
            }
            else if (players[j].r == TOWN && isSecuring) {
                cout << "Securing the town!";
                sleep(1);
            }
            else {
                cout << "You can't do anything this turn.";
                sleep(1);
            }
            cout << "\n\n\n\n\n\n\n\n\n\n";
        }
        // Need two hackers to hack round 4 in 7 and 8 player games
        if (numKilledThisRound == 1 && numPlayers > 6 && i == 3)
            killed = false;
        else if (numKilledThisRound)
            killed = true;

        if (killed) {
            numKilled++;
            cout << "A murder, the horror! Deaths: " << numKilled << endl;
            if (numKilled == 2)
                cout << "How much more can the village take!" << endl;
        }
        else {
            numSecured++;
            cout << "The town has been secured! Times secured: " << numSecured << endl;
            if (numSecured == 2)
                cout << "It appears the small might overpower the weak after all." << endl;
                cout << "Or maybe it's juts a trick.." << endl;
        }
        cout << endl;
    }
    checkWin(numKilled, numSecured);
    return 0;

}

void shuffleArray(int arr[], int n) {
    int temp = 0;
    int randomIndex = 0;
    // Start from last element and swap one by one
    for (int i = 0; i < n; i++) {
        randomIndex = rand() % n;
        temp = arr[i];
        arr[i] = arr[randomIndex];
        arr[randomIndex] = temp;
    }
}

void checkWin(int k, int s) {
    // Check if win conditions have been met
    if (k == 3) {
        cout << "The killing rampage has gone too far!" << endl << endl;
        cout << "The mafia are triumphant." << endl;
        cout << "A dark day for citizens everywhere.";
        exit(0);
    }
    else if (s == 3) {
        cout << "Order has been enforced in the village!" << endl;
        cout << "The mafia scourge has been driven out," << endl;
        cout << "Thus, victory for the plebeians.";
        exit(0);
    }
}