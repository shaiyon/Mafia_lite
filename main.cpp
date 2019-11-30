    // mafiaLite
    // Text based multiplayer Mafia style game.
    // Shaiyon Hariri

    #include <iostream>
    #include <unistd.h>
    using namespace std;

    void shuffleArray(int arr[], int n);
    void explainRules();

    enum faction { MAFIA, TOWN };

    struct Player {
        string name;
        faction role;
    };    

    int main() {
        // Get number of players
        cout << "Welcome to maifaLite\n\nNumber of players: (5-8) ";
        int numPlayers = 0;
        while (numPlayers<5 || numPlayers>8) {
            cin >> numPlayers;
        }
        
        // Get screen size for hiding role reveals and turns
        string answer = "";
        string hideScreen = "";
        cout << "How big is your terminal window? (s/m/l) ";
        while (answer != "s" && answer != "m" && answer!= "l") {
            cin >> answer;
        }                
        if (answer == "s") 
            hideScreen = "\n\n\n\n\n\n\n\n";
        else if (answer == "m") 
            hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        else
            hideScreen = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        // Explain rules if necessary 
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
        Player players[numPlayers]; 
        for (int i = 0; i < numPlayers; i++) {
            cout << "Player " << i+1 << " name: ";
            answer = "";
            cin >> answer;
            players[i].name = answer;
        }
        cout << endl;

        int numRounds = 5;
        int numMafia;
        int numSecure[numRounds];
        // Number of players chosen to secure each round (varies by numPlayers)
        // And number of mafia / town 
        if (numPlayers == 5) {
            int a[] = {2, 3, 2, 3, 3};
            copy(a, a+numRounds, numSecure);
            numMafia = 2;
        }
        else if (numPlayers == 6) {
            int a[] = {2, 3, 4, 3, 4};
            copy(a, a+numRounds, numSecure);
            numMafia = 2;
        }
        else if (numPlayers == 7) {
            int a[] = {2, 3, 3, 4, 4};
            copy(a, a+numRounds, numSecure);
            numMafia = 3;
        }
        else {
            int a[] = {3, 4, 4, 5, 5};
            copy(a, a+numRounds, numSecure);
            numMafia = 3;
        }
        int numTown = numPlayers - numMafia;
        // Assign random roles to players
        int roleNums[numPlayers];
        for (int i = 0; i < numPlayers; i++) {
            roleNums[i] = i;
        }
        srand(time(NULL));
        shuffleArray(roleNums, numPlayers);
        for (int i = 0; i < numMafia; i++) {
            players[roleNums[i]].role = MAFIA;
        }
        for (int i = numMafia; i < numPlayers; i++) {
            players[roleNums[i]].role = TOWN;
        }

        // Keep track of game score
        int numKilled = 0;
        int numSecured = 0;
        cout << "Make sure nobody sees anyone elses role!" << endl << endl;
        // Show players their roles discreetly
        for (int i = 0; i < numPlayers; i++) {
            if (i)
                cout << hideScreen << endl;
            cout << players[i].name << ", are you ready to see your role? (y) ";
            answer = "";
            while (!(answer == "y")) {
                cin >> answer;
            }
            if (players[i].role == MAFIA)
                cout << "You are mafia..." << endl;
            else
                cout << "You are town.";
        }

        cout << "And now, the game begins. If you're town, try not to let 3 people die." << endl;
        cout << "Trust no one." << endl << endl;

        // Game rounds
        for (int i = 0; i < numRounds; i++) {
            bool killed = false;
            int numKilledThisRound = 0;
            cout << "Round " << i+1 << " of " << numRounds << endl << endl;
            sleep(2);
            // Talking Phase
            cout << "Voting Phase" << endl;
            sleep(1);
            cout << "Pick " << numSecure[i] << " players to secure the town. Discuss and reach a consensus." << endl;
            sleep(10);
            // Voting Phase
            cout << "Who will it be?" << endl;
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
                cout << "Input your turn after the wait period. Don't mess up, or you'll look suspicious!" << endl;
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
                    if (answer == "y") {
                        numKilledThisRound++;
                    }
                    sleep(1);
                }
                else if (players[j].role == TOWN && isSecuring) {
                    cout << "Securing the town! (y to continue) ";
                    answer = "";
                    while (answer != "y") {
                        cin >> answer;
                    }                
                    sleep(1);
                }
                else {
                    cout << "You can't do anything this turn. (y to continue) ";
                    answer = "";
                    while (answer != "y") {
                        cin >> answer;
                    }                
                    sleep(1);
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
                    cout << "There were " << numKilledThisRound << " killers this round. Total deaths: " << numKilled << endl;
                    cout << "These mafioso should show a little more restraint..." << endl;
                } 
                else {
                    cout << "A murder, the horror! Deaths: " << numKilled << endl;
                    if (numKilled == 2)
                        cout << "How much more can the village take?" << endl;
                }
            }
            // Round secured
            else {
                numSecured++;
                if (numKilledThisRound) {
                    cout << "There was an attempted murder last night.." << endl;
                    cout << "But there was too much security. Total secures: " << numSecured << endl;
                }
                else {
                    cout << "The town has been secured! Total secures: " << numSecured << endl;
                    if (numSecured == 2) {
                        cout << "It appears the sheep may defeat the wolves after all." << endl;
                        cout << "But maybe it's just a trick.." << endl;
                    }
                }
            }
            cout << endl;
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
        cout << "Each player is randomly chosen to be a member of one of two factions, town and mafia." << endl;
        sleep(5);
        cout << "Town is the majority and wants to secure the village." << endl;
        sleep(3);
        cout << "The village is secured when there are no killings that round. Keep suspected mafia off the patrol!" << endl;
        sleep(4);
        cout << "The mafia are the minority, with a lust for chaos and blood. They must undermine the people." << endl;
        sleep(5);
        cout << "Nobody knows anyone else's role. There are 2 mafiosos in 5-6 player matches, and 3 in 7-8 player ones." << endl;
        sleep(5);
        cout << "5 rounds are played, or until a faction achieves their goal in 3 rounds." << endl;
        sleep(4);
        cout << endl << "Each round has two phases: the talking phase, and the mission phase." << endl;
        sleep(5);
        cout << "Talking phase:" << endl;
        cout << "The players must discuss who they want to secure the town that round." << endl;
        sleep(5);
        cout << "Discussion occurs until a majority is reached and a decision is made." << endl;
        sleep(5);
        cout << "Mission phase:" << endl;
        cout << "Each player takes their turn. Town cannot do anything except continue and appear inconspicious!" << endl;
        sleep(5);
        cout << "When chosen to secure the town, the mafia can either kill, or decline to do so, going under the radar." << endl;
        sleep(5);
        cout << "Otherwise, the mafia cannot take an action either." << endl;
        sleep(3);
        cout << "It is extremely important for the town to figure out the truth." << endl;
        sleep(4);
        cout << "If public discourse is infiltrated, the interloper will cause mayhem without fail." << endl;
        sleep(4);
        cout << "Good luck...." << endl;
        sleep(3);
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