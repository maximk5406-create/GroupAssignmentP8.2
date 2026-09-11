/**
 * Course: Computer Science / C++ Programming
 * Exercise: Big C++: Late Objects, Enhanced (3rd ed.) - Project P8.2
 * File Name: P8_2_SpellChecker.cpp
 * Description: Reads a dictionary file into a vector and checks a document file 
 *              for words not present in the dictionary list.
 * 
 * Team Members:
 *  - Member 1 (Team Lead): Dictionary loading and file streaming
 *  - Member 2: Word sanitization and search implementation
 *  - Member 3: Program driver, loop processing, and console output
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

// ============================================================================
// Author: Member 1 (Team Lead)
// Purpose: Opens the dictionary file and loads words into a vector.
// ============================================================================
vector<string> loadDictionary(const string& dictPath)
{
    vector<string> words;
    ifstream dictFile(dictPath);

    if (!dictFile.is_open())
    {
        cerr << "Error: Could not open dictionary file at " << dictPath << endl;
        return words;
    }

    string word;
    while (dictFile >> word)
    {
        // Convert dictionary word to lowercase for consistent comparison
        transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
    }

    dictFile.close();
    return words;
}

// ============================================================================
// Author: Maximn Keene
// Purpose: Strips punctuation and converts a raw document token to lowercase.
// ============================================================================
string cleanWord(const string& rawWord)
{
    int start = 0;
    int end = rawWord.length() - 1;

    // Remove leading non-alphanumeric characters
    while (start <= end && !isalnum(rawWord[start]))
    {
        start++;
    }

    // Remove trailing non-alphanumeric characters
    while (end >= start && !isalnum(rawWord[end]))
    {
        end--;
    }

    if (start > end) return "";

    string cleaned = rawWord.substr(start, end - start + 1);
    for (char& ch : cleaned)
    {
        ch = tolower(ch);
    }
    return cleaned;
}

// ============================================================================
// Author: Maxim Keene
// Purpose: Performs a search to verify if a word exists in the dictionary vector.
// ============================================================================
bool isWordInDictionary(const string& word, const vector<string>& dictionary)
{
    for (const string& dictWord : dictionary)
    {
        if (dictWord == word)
        {
            return true;
        }
    }
    return false;
}

// ============================================================================
// Author: Member 3
// Purpose: Program main entry point. Coordinates dictionary loading and document parsing.
// ============================================================================
int main()
{
    cout << "==========================================" << endl;
    cout << "         C++ File Spell Checker           " << endl;
    cout << "==========================================" << endl << endl;

    // Path to dictionary file (Use words.txt in local directory or system path)
    string dictPath = "words.txt"; 
    string documentPath = "input_document.txt";

    cout << "Loading dictionary from: " << dictPath << "..." << endl;
    vector<string> dictionary = loadDictionary(dictPath);

    if (dictionary.empty())
    {
        cerr << "Spell checking aborted due to missing dictionary." << endl;
        return 1;
    }

    cout << "Dictionary loaded successfully (" << dictionary.size() << " words)." << endl << endl;

    ifstream docFile(documentPath);
    if (!docFile.is_open())
    {
        cerr << "Error: Could not open document file: " << documentPath << endl;
        return 1;
    }

    cout << "Unrecognized / Misspelled Words Found:" << endl;
    cout << "------------------------------------------" << endl;

    string rawWord;
    int misspelledCount = 0;

    while (docFile >> rawWord)
    {
        string cleaned = cleanWord(rawWord);
        if (!cleaned.empty())
        {
            if (!isWordInDictionary(cleaned, dictionary))
            {
                cout << " -> " << cleaned << endl;
                misspelledCount++;
            }
        }
    }

    docFile.close();

    cout << "------------------------------------------" << endl;
    cout << "Spell check complete. Total unknown words: " << misspelledCount << endl;

    return 0;
}
