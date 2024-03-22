// Wordle.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "words.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int Word_Length = 5;
const int Number_of_Guesses = 5; // Define the number of guesses allowed

string getRandomWord();
bool isValidWord(string word);

int main()
{
    vector<string> guesses(Number_of_Guesses);
    vector<int> matches(Number_of_Guesses);
    string targetWord = getRandomWord();

    string input;
    string userWord;
    int currentGuessCount = 0;

    cout << R"(
 __        __   _______    ______    ______   __         _____
|\  \     |\  \|\   __  \|\   __  \|\   ___ \|\  \     |\  ___ \     
\ \  \    \ \  \ \  \|\  \ \  \|\  \ \  \_|\ \ \  \    \ \   __/|    
 \ \  \  __\ \  \ \  \\\  \ \   _  _\ \  \ \\ \ \  \    \ \  \_|/__  
  \ \  \|\__\_\  \ \  \\\  \ \  \\  \\ \  \_\\ \ \  \____\ \  \_|\ \ 
   \ \____________\ \_______\ \__\\ _\\ \_______\ \_______\ \_______\
    \|____________|\|_______|\|__|\|__|\|_______|\|_______|\|_______|

            )";

    cout << "\n\nWelcome to Wordle!\n\n";

    cout << "Press \"Q\" to quit the game." << endl;

    while (currentGuessCount < Number_of_Guesses)
    {
        cout << (Number_of_Guesses - currentGuessCount) << " Guess remaining" << endl;
        cout << "Enter your guess (" << Word_Length << " characters): ";
        cin >> input;

        // Check if user want to quit
        if (input == "Q") {
            cout << "Quitting the game. The word was: " << targetWord << endl;
            break;
        }

        if (!isValidWord(input)) {
            cout << "Invalid guess! Please enter a " << Word_Length << "-character word with uppercase letters only." << endl;
            continue;
        }

        // Reset userWord for each new guess
        string userWord(Word_Length, '_');

        // Check each character in the guessed word against the target word
        for (int i = 0; i < Word_Length; i++) {
            if (input[i] == targetWord[i]) {
                userWord[i] = input[i]; // Exact match
            }
            else 
            {
                // Check if the character exists in the target word (partial match)
                for (int j = 0; j < Word_Length; j++) 
                {
                    if (input[i] == targetWord[j]) 
                    {
                        userWord[i] = '*'; // Indicate a correct letter in the wrong position
                        break; // Exit inner loop once a match is found
                    }
                }
            }
        }

        cout << "Your progress: ";
        for (char c : userWord) {
            if (c == '_') {
                cout << "_ ";
            }
            else if (c == '*') {
                cout << "? ";
            }
            else {
                cout << c << " ";
            }
        }
        cout << endl;

        if (userWord == targetWord) 
        {
            cout << "Congratulations! You guessed the word: " << targetWord << endl;
            break;
        }

        
        currentGuessCount++;
        cout << endl;
        cout << "---------------------------------------\n"
                "---------------------------------------" << endl;
        
        if (currentGuessCount == Number_of_Guesses)
        {
            cout << "Sorry, you ran out of guesses!" << endl;
            cout << "The word is " << targetWord;
        }
        

    }

    return 0;
}

string getRandomWord()
{
    srand(time(NULL));

    int randomNum = rand() % words.size();
    
    string randomWord = words[randomNum];

    for (char& c : randomWord)
    {
        c = toupper(c);
    }

    return  randomWord;
}

bool isValidWord(string word)
{
    if (word.length() != Word_Length)
        return false;

    for (char c : word) {
        if (!isupper(c))
            return false;
    }

    return true;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
