// functions.cpp
// Functions for mafiaLite
// Shaiyon Hariri

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Useful data structures
enum faction { TOWN, MAFIA };
struct Player {
    string name;
    faction role;
};

// Create seed in main before usage
void shuffleArray(int arr[], const int n) {
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

bool strInArray(string arr[], const string str, const int len) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == str) 
            return true;
    }
    return false;
}

bool isValid(const string str) {
    int len = str.size();
    if (len > 15)
        return false;
    for (int i = 0; i < len; i++) {
        if (!isalpha(str[i]))
            return false;
    }
    return true;
}

void setupNumSecure(int numSecure[], int &numMafia, const int numPlayers, const int ROUNDS) {
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
    cout << endl << "Town members are unaware of anyone else's role, but the mafia know everything.";
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