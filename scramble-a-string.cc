/*
Jerry Vogel
Scramble A String v1.0
Started 9/29/2015
Wordlist from https://github.com/first20hours/google-10000-english
Have Fun!!!
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <limits.h>
#include <time.h>
#include <stdio.h>
#define DEBUG false

using namespace std;
    
//Shuffles the words
vector<string> Shuffle(vector<string>str)
{
    vector<string>shuffledWords;
    for(int num = 0; num < str.size(); num++)
    {
        string word = str[num];
        bool same = false;
        for(int i = 0; i < str[num].length(); i++)
        {
            int ranNum = rand() % str[num].length();
            char temp = str[num][i];
            str[num][i] = str[num][ranNum];
            str[num][ranNum] = temp;
        }
        if(str[num] == word)
        {
            same = true;
        }
        while(same)
        {
            for(int i = 0; i < str[num].length(); i++)
            {
                int ranNum = rand() % str[num].length();
                char temp = str[num][i];
                str[num][i] = str[num][ranNum];
                str[num][ranNum] = temp;
            }
            if(str[num] != word)
            {
                same = false;
            }
        }
        shuffledWords.push_back(str[num]);
    }
    return shuffledWords;
}

vector<string> insertionsort(vector<string> str, int size)  //Set size to 1 to make it a true insertion sort
{
    for(int i = 1; i < str.size(); i++)
    {
        string temp = str[i];
        int j = i;
        while( j > 0 && str[j - 1].length() > temp.length())
        {
            str[j] = str[j-1];
            j = j - 1;
        }
        str[j] = temp;
    }
    return str;
}
/*    Failed Shell Sort.  Will Debug later
void shellsort(vector<string> str)
{
    const int gapdiff = 3;  //How much the gap will be changed
    int gap = 1;
    while (gap < str.size())
    {
        if(isBeingDebugged)
        {
            cout << "shuffling" << endl << gap << endl;
        }
        gap = gap * gapdiff + 1;
        if(isBeingDebugged)
        {
            cout << gap << endl;
        }
        while(gap > 0)
        {
            if(isBeingDebugged)
            {
                cout << "shuffling pt. 2" << endl << gap << endl;
            }
            gap /= (gapdiff - 1);
            if(isBeingDebugged)
            {
                cout << "shuffling pt. 2" << endl << gap << endl;
            }
            for(int i = 1; i < gap; i++)
            {
                insertionsort(str, gap);
                if(gap == 1)
                {
                    break;
                }
            }
        }
        if(isBeingDebugged)
        {
            break;
        }
    }
    if(isBeingDebugged)
    {
        cout << gap << endl;
    }
}
*/
int main()
{
    vector<string> words;
    vector<string> selectedWords;
    vector<string> shuffledWords;
    vector<string> sortedWords;
    vector<string> sortedUnshuffled;
    vector<int> usedWords;
    ifstream myFile;
    string line;
    long seed;
    bool over;
    bool correct;
    int difficulty;
    int usedTries;
    int totalGuesses;
    int wordNum;
    int totalWords;
    double tries;
    
    myFile.open("words.txt");
    //Reading the file
    if(myFile.is_open())
    {
        while ( getline (myFile, line) )
        {
            words.push_back(line);
        }
    myFile.close();
    }
    
    //Remove words with length <= 4
    for(int i = words.size() - 1; i >= 0; i--)
    {
        if(words[i].length() <= 4)
        {
            words.erase (words.begin() + i);
        }
    }
    #if DEBUG
        cout << words[0] << endl;
    #endif
    srand(time(NULL));  //set the seed for the random number as the time
    //How many words will be in the game
    cout << "How many words would you like in the game?" << endl;
    cin >> totalWords;
    
    //Populates selectedWords with "totalWords" random words from "words"
    for(int i = 0; i < totalWords; i++)
    {
        int wordIndex;
        wordIndex = (rand() % (words.size() - 1));
        for(int j = 0; j < usedWords.size(); j++)
        {
            if(usedWords[j] == wordIndex)
            {
                wordIndex = (rand() % (words.size() - 1));
                j = 0;
            }
        }
        selectedWords.push_back(words[wordIndex]);
        usedWords.push_back(wordIndex);
    }
    
    #if DEBUG
        for(int i = 0; i < selectedWords.size(); i++)
        {
            cout << selectedWords[i] << endl;
        }
    #endif
    
    //Shuffle and Sort selectedWords
    shuffledWords = Shuffle(selectedWords);
    
    #if DEBUG
        cout << endl;
        for(int i = 0; i < shuffledWords.size(); i++)
        {
            cout <<shuffledWords[i] << endl;
        }
    #endif
    
    sortedWords = insertionsort(shuffledWords, 1);
    sortedUnshuffled = insertionsort(selectedWords, 1);
    
    //Debug
    #if DEBUG
        cout << "Sorted List" << endl;
        for(int i = 0; i < sortedWords.size(); i++)
        {
            cout << sortedWords[i] << endl;
        }
        cout << "Sorted unshuffled List" << endl;
        for(int i = 0; i < sortedUnshuffled.size(); i++)
        {
            cout << sortedUnshuffled[i] << endl;
        }
    #endif
        cout << "Which difficulty would you like?  Please enter a number 1 - 3.  1 is easiest, 3 is hardest" << endl;
    cin >> difficulty;
    difficulty = (difficulty % 3);  //If people enter numbers too high, this will fix it
    if(difficulty == 1)
    {
        tries = 2;
    }
    else if(difficulty == 2)
    {
        tries = 1.5;
    }
    else if(difficulty == 0) //The difficulty % 3 makes entering 3 = 0
    {
        tries = 1;
    }
    totalGuesses = (int) (tries * sortedWords.size()) + 2;  //You get 2 free guesses
    
    //Game Start
    over = false;
    usedTries = 1;
    wordNum = 0;
    while(!over)
    {
        correct = false;
        while(!(over || correct))
        {
            #if DEBUG
                for(int i = 0; i < sortedUnshuffled.size(); i++)
                {
                    cout << sortedUnshuffled[i] << endl;
                }
            #endif
            cout << "What is this word unscrambled?" << endl << sortedWords[wordNum] << endl;
            string guess;
            cin >> guess;
            if(guess == sortedUnshuffled[wordNum])
            {
                wordNum++;
                if(wordNum == sortedWords.size())
                {
                    over = true;
                    cout << "Conglaturation, this story is happy end!" << endl << "Play again!";  //"conglaturation" is intentional
                }
                else
                {
                    cout << "Correct.  Time for the next word.  You have " << (totalGuesses - usedTries) << " tries left." << endl;
                    correct = true;
                }
            }
            else if(guess != sortedUnshuffled[wordNum] && usedTries != totalGuesses)
            {
                usedTries++;
                cout << "Incorrect.  You have " << (totalGuesses - usedTries) << " guess(es) left.  Try Again" << endl;
            }
            else if(guess != sortedUnshuffled[wordNum] && usedTries == totalGuesses)
            {
                cout << "You have used up all of your tries.  Game over." << endl << "Here are all the words." << endl;
                for(int i = wordNum ; i < sortedUnshuffled.size(); i++)
                {
                    cout << sortedUnshuffled[i] << endl;
                }
                cout << "Play again!";
                over = true;
            }
        }
    }
    return 0;
}