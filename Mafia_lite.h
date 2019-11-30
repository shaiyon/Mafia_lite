// Mafia.h
// Header file for classes and methods used in Mafia
// Shaiyon Hariri

#ifndef MAFIA_LITE_H
#define MAFIA_LITE_H

#include <iostream>
using namespace std;

enum role { MAFIA, TOWN };

class Player {
    public:
        void setName(string n) { name = n; }
        string getName() const { return name; }
        role getRole() const { return r; }
        void setRole(role ro) { r = ro; }
    private: 
        // Player name
        string name;
        // Mafia or town
        role r;

};      

#endif