// Mafia_lite.cpp
// Implements methods in Mafia_lite.h
// Shaiyon Hariri

#include <iostream>
#include <bits/stdc++.h> 
#include "Mafia_lite.h"
using namespace std;

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
