// mafiaLite.cpp
// Game logic for mafiaLite
// Shaiyon Hariri

#include <iostream>
#include <thread>
#include <chrono>
#include "functions.cpp"
using namespace std;

#define ROUNDS 5

int main() {

    // Get number of players
    cout << "Welcome to mafiaLite" << endl << endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Number of players: (5-8) ";
    int numPlayers;
    while (numPlayers < 5 || numPlayers > 8) {
        cin >> numPlayers;
        if (cin.fail() || numPlayers < 5 || numPlayers > 8) {
            cin.clear();
            cin.ignore();
            cout << "Enter a valid number! ";
        }
    }
    
    // Get screen size for hiding role reveals and turns
    string answer = "";
    string hideScreen = "";
    cout << "How big is your terminal window? (s/m/l) ";
    while (answer != "s" && answer != "m" && answer != "l") {
        cin >> answer;
        if (answer != "s" && answer != "m" && answer != "l")
            cout << "Enter a valid answer! ";
    }
    if (answer == "s")
        hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    else if (answer == "m")
        hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    else
        hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    // Explain rules if necessary
    answer = "";
    cout << "Shall the rules be explained? (y/n) ";
    while (answer != "y" && answer != "n") {
        cin >> answer;
    }
    if (answer == "y") {
        cout << endl;
        explainRules();
    }
    cout << endl;

    // Get names from user
    string names[numPlayers];
    Player players[numPlayers];
    for (int i = 1; i <= numPlayers; i++) {
        cout << "Player " << i << " name: ";
        answer = "";
        // If name is already used or not only alphabetical, prompt user again
        do {
            cin >> answer;
            if (strInArray(names, answer, i))
                cout << "Enter a name not already used! ";
            else if (!isValid(answer))
                cout << "Enter a valid name! ";
        } while (strInArray(names, answer, i) || !isValid(answer));
        names[i-1] = answer;
        players[i-1].name = answer;
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl;

    // Set number of mafia and players chosen to secure each round (varies by numPlayers)
    int numMafia;
    int numSecure[ROUNDS];
    setupNumSecure(numSecure, numMafia, numPlayers, ROUNDS);

    // Assign random roles to players
    int roleNums[numPlayers];
    for (int i = 0; i < numPlayers; i++) {
        roleNums[i] = i;
    }
    srand(time(NULL));
    shuffleArray(roleNums, numPlayers);
    string mafiaNames;
    for (int i = 0; i < numMafia; i++) {
        players[roleNums[i]].role = MAFIA;
        mafiaNames += players[roleNums[i]].name;
        if (i != numMafia-1)
            mafiaNames += ", ";
    }
    for (int i = numMafia; i < numPlayers; i++) {
        players[roleNums[i]].role = TOWN;
    }

    // Keep track of game score
    int numKilled = 0;
    int numSecured = 0;
    cout << "Role reveals: make sure nobody sees anyone else's role!" << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));
    // Show players their roles discreetly
    for (int i = 0; i < numPlayers; i++) {
        if (i)
            cout << hideScreen;
        cout << players[i].name << ", are you ready to see your role? (y) ";
        answer = "";
        while (answer != "y") {
            cin >> answer;
        }
        if (players[i].role == MAFIA) {
            cout.flush();
            cout << "You are mafia...\n";
            this_thread::sleep_for(chrono::seconds(1));
            cout << "Mafia members: " << mafiaNames << endl;
        }
        else
            cout << "You are town." << endl;
        cout.flush();
        this_thread::sleep_for(chrono::seconds(3));
    }
    cout << hideScreen;
    cout << "So it begins..";
    cout.flush();
    this_thread::sleep_for(chrono::seconds(2));
    cout << " trust no one." << endl << endl;
    this_thread::sleep_for(chrono::seconds(2));

    // Game rounds
    for (int i = 0; i < ROUNDS; i++) {
        bool killed = false;
        int numKilledThisRound = 0;
        cout.flush();
        cout << "Round " << i + 1 << endl << endl;
        this_thread::sleep_for(chrono::seconds(2));
        // Talking Phase
        cout << "Pick " << numSecure[i] << " players to secure the town. Discuss and reach a consensus." << endl;
        this_thread::sleep_for(chrono::seconds(5));
        cout << "Who will it be?" << endl;
        for (int j = 0; j < numPlayers; j++) {
            cout << players[j].name << " ";
        }
        cout << endl;
        
        string playerSecuring[numSecure[i]];
        for (int j = 0; j < numSecure[i]; j++) {
            // If given name is not in names or already picked, prompt user again
            answer = "";
            do {
            cin >> answer;
            } while (!strInArray(names, answer, numPlayers) || strInArray(playerSecuring, answer, j+1));
            playerSecuring[j] = answer;
        }
        // Mission Phase
        this_thread::sleep_for(chrono::seconds(2));
        // Each player's turn
        for (int j = 0; j < numPlayers; j++) {
            bool isSecuring = false;
            for (int k = 0; k < numSecure[i]; k++) {
                if (playerSecuring[k] == players[j].name)
                    isSecuring = true;
            }
            cout << players[j].name << "'s turn. Ready? (y) ";
            answer = "";
            while (answer != "y") {
                cin >> answer;
            }
            // Different caes for if player is Mafia, town or town and securing
            if (players[j].role == MAFIA && isSecuring) {
                cout << "Kill somebody (y), or secure the town? (n) ";
                answer = "";
                while (answer != "y" && answer != "n") {
                    cin >> answer;
                }
                if (answer == "y")
                    numKilledThisRound++;
            }
            else if (players[j].role == TOWN && isSecuring) {
                cout << "Securing the town! (y to continue) ";
                answer = "";
                while (answer != "y") {
                    cin >> answer;
                }
            }
            else {
                cout << "You can't do anything this turn. (y to continue) ";
                answer = "";
                while (answer != "y") {
                    cin >> answer;
                }
            }
            cout << hideScreen;
        }
        // Need two killers to increase numKilled in round 4 for 7 and 8 player games
        if (numKilledThisRound == 1 && numPlayers > 6 && i == 3)
            killed = false;
        else if (numKilledThisRound)
            killed = true;

        // End of round logic
        // Murder committed
        if (killed) {
            numKilled++;
            if (numKilledThisRound >= 2) {
                cout << "There were " << numKilledThisRound << " killers this round." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                cout << "These mafioso should show a little more restraint..." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
            else {
                cout << "A murder, the horror!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                if (numKilled == 2) {
                    cout << "How much more can the village take?" << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
            }
        }
        // Round secured
        else {
            numSecured++;
            if (numKilledThisRound) {
                cout << "There was an atnumPlayersted murder last night.." << endl;
                this_thread::sleep_for(chrono::seconds(2));
                cout << "But there was too much security." << endl;
                this_thread::sleep_for(chrono::seconds(2));
            }
            else {
                cout << "The town has been secured!" << endl;
                this_thread::sleep_for(chrono::seconds(2));
                if (numSecured == 2) {
                    cout << "It appears the sheep may defeat the wolves after all." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                    cout << "But maybe it's just a trick.." << endl;
                    this_thread::sleep_for(chrono::seconds(2));
                }
            }
        }
        cout << "Secures: " << numSecured << "  Deaths: " << numKilled << endl << endl;
        this_thread::sleep_for(chrono::seconds(2));
        // Check for win condition at end of each round
        if (numKilled == 3) {
            cout << "The rampage has gone too far!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Triumphant the mafia stands." << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "A dark day for citizens everywhere.";
            this_thread::sleep_for(chrono::seconds(15));
            exit(0);
        }
        else if (numSecured == 3) {
            cout << "Order has been enforced in the village!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "The scourge has been driven out," << endl;
            this_thread::sleep_for(chrono::seconds(2));
            cout << "Thus, victory for the plebeians.";
            this_thread::sleep_for(chrono::seconds(15));
            exit(0);
        }
    }
    return 1;
}