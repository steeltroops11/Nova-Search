/*
==================================================================
================= MEMORY TRAINER GAME - C++ PROJECT ==============
==================================================================
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// ============================ UTILITY FUNCTIONS =============================

void drawBorder() {
    cout << "=============================================================\n";
}

string getPlayerName() {
    string name;
    cout << "Enter your name: ";
    getline(cin, name);

    while (name.empty()) {
        cout << "Name cannot be empty. Enter again: ";
        getline(cin, name);
    }
    return name;
}

void showInstructions() {
    drawBorder();
    cout << "MEMORY TRAINER GAME INSTRUCTIONS\n";
    cout << "1. A sequence of numbers will be displayed.\n";
    cout << "2. Memorize the sequence carefully.\n";
    cout << "3. Enter the sequence in the same order.\n";
    cout << "4. Game ends on the first wrong input.\n";
    cout << "5. Score increases with each level.\n";
    drawBorder();
}

bool askReplay() {
    char choice;
    cout << "Play again? (y/n): ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return (choice == 'y' || choice == 'Y');
}

void clearScreen() {
    for (int i = 0; i < 40; i++)
        cout << endl;
}

// ============================ GAME LOGIC =============================

vector<int> generateSequence(int length, int minNum = 1, int maxNum = 9) {
    vector<int> seq;
    for (int i = 0; i < length; i++) {
        seq.push_back(rand() % (maxNum - minNum + 1) + minNum);
    }
    return seq;
}

void showSequence(const vector<int>& seq) {
    cout << "MEMORIZE THIS SEQUENCE:\n>> ";
    for (int num : seq)
        cout << num << " ";
    cout << "\nPress ENTER when ready...";
    cin.get();
}

vector<int> getPlayerSequence(int length) {
    vector<int> input(length);
    cout << "Enter the sequence:\n>> ";
    for (int i = 0; i < length; i++) {
        while (!(cin >> input[i])) {
            cout << "Invalid input. Enter again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

bool checkSequence(const vector<int>& original, const vector<int>& user) {
    for (size_t i = 0; i < original.size(); i++) {
        if (original[i] != user[i])
            return false;
    }
    return true;
}

string getEncouragement(int level) {
    if (level <= 3) return "Good start!";
    if (level <= 7) return "Great concentration!";
    if (level <= 12) return "Excellent memory!";
    return "Memory Master!";
}

void showStats(const string& name, int level, int score, int bestLevel, int bestScore) {
    drawBorder();
    cout << "GAME OVER, " << name << "\n";
    cout << "Level Reached : " << level << "\n";
    cout << "Score         : " << score << "\n";
    cout << "Best Level    : " << bestLevel << "\n";
    cout << "Best Score    : " << bestScore << "\n";
    cout << getEncouragement(level) << "\n";
    drawBorder();
}

// ============================ MAIN FUNCTION =============================

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int bestLevel = 0;
    int bestScore = 0;
    bool playAgain = true;

    while (playAgain) {
        showInstructions();
        string playerName = getPlayerName();

        int level = 1;
        int score = 0;
        int sequenceLength = 3;
        bool playing = true;

        clearScreen();
        cout << "Welcome " << playerName << "! Press ENTER to start...";
        cin.get();

        while (playing) {
            clearScreen();
            cout << "LEVEL " << level << " | Sequence Length: " << sequenceLength << "\n\n";

            vector<int> sequence = generateSequence(sequenceLength);
            showSequence(sequence);
            clearScreen();

            vector<int> userInput = getPlayerSequence(sequenceLength);

            if (checkSequence(sequence, userInput)) {
                score += sequenceLength * 10;
                level++;
                sequenceLength++;
                cout << "Correct! Score: " << score << "\nPress ENTER...";
                cin.get();
            } else {
                playing = false;
            }
        }

        if (level - 1 > bestLevel) bestLevel = level - 1;
        if (score > bestScore) bestScore = score;

        showStats(playerName, level - 1, score, bestLevel, bestScore);
        playAgain = askReplay();
        clearScreen();
    }

    cout << "Thank you for playing the Memory Trainer Game.\n";
    return 0;
}
