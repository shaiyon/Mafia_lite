// mafiaLite
// Terminal based local multiplayer mafia style game.
// Shaiyon Hariri

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Useful data structures
enum faction { MAFIA, TOWN };
struct Player {
    string name;
    faction role;
};

void explainRules();
void shuffleArray(int arr[], int n);
bool stringInArray(string arr[], string str, int len);

int main() {
    // Get number of players
    cout << "Welcome to mafiaLite" << endl << endl; 
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Number of players: (5-8) ";
    int numPlayers = 0;
    while (numPlayers < 5 || numPlayers > 8) {
        cin >> numPlayers;
    }

    // Get screen size for hiding role reveals and turns
    string answer = "";
    string hideScreen = "";
    cout << "How big is your terminal window? (s/m/l) ";
    while (answer != "s" && answer != "m" && answer != "l") {
        cin >> answer;
    }
    if (answer == "s")
        hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
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
        // If name is already used, prompt user again
        do {
            cin >> answer;
        } while (stringInArray(names, answer, i));
        names[i-1] = answer;
        players[i-1].name = answer;
    }
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl;

    const int ROUNDS = 5;
    int numMafia;
    int numSecure[ROUNDS];
    // Number of players chosen to secure each round (varies by numPlayers)
    // And number of mafia / town
    if (numPlayers == 5) {
        int a[] = {2, 3, 2, 3, 3};
        copy(a, a + ROUNDS, numSecure);
        numMafia = 2;
    }
    else if (numPlayers == 6) {
        int a[] = {2, 3, 4, 3, 4};
        copy(a, a + ROUNDS, numSecure);
        numMafia = 2;
    }
    else if (numPlayers == 7) {
        int a[] = {2, 3, 3, 4, 4};
        copy(a, a + ROUNDS, numSecure);
        numMafia = 3;
    }
    else {
        int a[] = {3, 4, 4, 5, 5};
        copy(a, a + ROUNDS, numSecure);
        numMafia = 3;
    }
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
        while (!(answer == "y")) {
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
        // Voting Phase
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
            } while (!stringInArray(names, answer, numPlayers) || stringInArray(playerSecuring, answer, j+1));
            playerSecuring[j] = answer;
        }
        // Mission Phase
        cout << "May those chosen keep us safe." << endl;
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
                cout << "There was an attempted murder last night.." << endl;
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
            cout << "Triumphant the mafia stands." << endl;
            cout << "A dark day for citizens everywhere.";
            exit(0);
        }
        else if (numSecured == 3) {
            cout << "Order has been enforced in the village!" << endl;
            cout << "The scourge has been driven out," << endl;
            cout << "Thus, victory for the plebeians.";
            exit(0);
        }
    }
    return 1;
}

void explainRules() {
    this_thread::sleep_for(chrono::seconds(1));
    cout << "Each player is randomly chosen to be a member of one of two factions, town and mafia.";
    cout.flush();
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "Town is the majority and wants to secure the village.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "The village is secured when there are no killings that round. Keep suspected mafia off the patrol!";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << "The mafia are the minority, with a lust for chaos and blood. They must undermine the people.";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << "Town is unaware of anyone else's role, while the mafia know.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "There are 2 mafiosos in 5-6 player matches, and 3 in 7-8 player ones.";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << "5 rounds are played, or until a faction achieves their goal in 3 rounds.";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << endl << "Each round has two phases: the talking phase, and the mission phase.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "Talking phase:";
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl << "Players discuss who will be chosen secure the town that round.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "The town wants to keep suspected mafia off the patrol to avoid killings.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "Discussion occurs until a majority is reached and a decision is made.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "Mission phase:";
    this_thread::sleep_for(chrono::seconds(1));
    cout << endl << "Each player takes their turn. Town cannot do anything except continue and appear inconspicious!";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << "When chosen to secure the town, the mafia can either kill, or decline to do so, going under the radar.";
    this_thread::sleep_for(chrono::seconds(5));
    cout << endl << "Otherwise, the mafia cannot take an action either.";
    this_thread::sleep_for(chrono::seconds(2));
    cout << endl << "It is extremely important for the town to figure out the truth.";
    this_thread::sleep_for(chrono::seconds(3));
    cout << endl << "If public discourse is infiltrated, the interloper will wreak havoc without fail.";
    this_thread::sleep_for(chrono::seconds(4));
    cout << endl << "Good luck...." << endl; 
    this_thread::sleep_for(chrono::seconds(2));
}

// Create seed in main before usage
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

bool stringInArray(string arr[], string str, int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == str) 
            return true;
    }
    return false;
}
