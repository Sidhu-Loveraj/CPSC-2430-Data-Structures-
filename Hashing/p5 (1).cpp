// Loveraj Sidhu                                                             
// p5.cpp                                                                       
// hashes the words in Metamorphosis by Franz Kafka. Then prints the hash 
// table's load factor and its number of collisions, unique words, and 
// total words. Then will search for words inputed by uses and print the
// number of times they occur                                                                        

#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

const string FILE_NAME = "tests.txt";
const int TABLE_SIZE = 320;
const char YES = 'y';

// Each unique word gets a node
struct Node {
    int count;
    string word;
    Node* next;
};


bool proscessWord(string& word);
// pre-proscesses word and returns true if it fits word criteria
// pre: none
// post: punctuation has been removed on outside and word is uppercase

void insert(Node* table[], int index, string word, int& uwords, int&cols);
// inserts word into table at index 
// pre: word has been pre-proscessed and meets criteria
// post: node with word in it has been added to table or count of node has
// been increased. uwords and cols have been increased if nescessary

unsigned int RSHash(const char* str, unsigned int length);
// hash function by Robert Sedgwicks taken from partow.net
// pre: length is the length of str
// post: returns hash of str

int main()
{
    string word;
    ifstream file;
    Node* table[TABLE_SIZE];
    int collisions = 0;
    int uniquewords = 0;
    int totalwords = 0;
    double loadfactor;
    string findWord;
    char again = YES;
    bool wordfound = false;

    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
    // open and read file
    file.open(FILE_NAME);
    while (file >> word) {
        // read in word, preproscess it and check if it is valid
        if (proscessWord(word)) {
            // insert word if it meets criteria
            insert(table, RSHash(&word[0], word.length()), word, 
            uniquewords, collisions);
            totalwords++;
        } 
    }
    file.close();

    loadfactor = (double) uniquewords / TABLE_SIZE;

    // print out hash table info
    cout << "Load factor: " << loadfactor << endl;
    cout << "Collisions: " << collisions << endl;
    cout << "Unique words: " << uniquewords << endl;
    cout << "Total words: " << totalwords << endl;

    // let the user search for a words number of occurences
    while (tolower(again) == YES) {
        cout << "Enter a word to see its number of occurences" << endl;
        cin >> findWord;
        if (proscessWord(findWord)) {
            Node* finder;
            finder = table[RSHash(&findWord[0], findWord.length())];
            while (finder != nullptr) {
                // traverse linked list of collisions searching for word
                if (finder->word == findWord && !wordfound) {
                    // word is found
                    cout << "Word found " << finder->count << " time";
                    if (finder->count > 1) {
                        cout << "s";
                    }
                    wordfound = true;
                }
                finder = finder->next;
            }
        }
        if (!wordfound) {
            // word isn't found
            cout << "Word found 0 times";
        }
        // let the user do this as many times as they'd like
        cout << "\nWould you like to search for another word? (y/n)\n";
        cin >> again;
        wordfound = false;
    }
    // dealocate memory from hash table 
    Node* nodeptr;
    Node* delptr;
    for (int i = 0; i < TABLE_SIZE; i++) {
        nodeptr = table[i];
        while (nodeptr != nullptr) {
            delptr = nodeptr;
            nodeptr = nodeptr->next;
            delete delptr;
        }
    }
    return 0;
}

bool proscessWord(string& word)
{
    bool found = true;
    int pos = 0;
    // check if word is long enough
    if (word.length() <= 4) {
        found = false;
    }
    // convert to upper and set return to false if word cointains a number
    for (int i = 0; i < word.length(); i++) {
        if (isdigit(word[i])) {
            found = false;
        }
        word [i] = toupper(word[i]);
    }
    // remove punctuation from front of word
    while (!isalpha(word[pos]) && word.length() > 4) {
        word = word.substr(1);
    }
    // remove puncuation from back of word
    pos = word.length() - 1;
    while (!isalpha(word[pos]) && word.length() > 4) {
        word = word.substr(0,pos);
        pos--;
    }
    // check for if word has shrunk
    if (word.length() <= 4) {
        found = false;
    }
    return found;
}

void insert(Node* table[], int index, string word, int& uwords, int& cols) 
{
    Node* nodeptr = table[index];
    bool alreadyhashed = false;
    // increase count if word has already been inserted
    while (nodeptr != nullptr && !alreadyhashed) {
        if (nodeptr->word == word) {
            nodeptr->count++;
            alreadyhashed = true;
        }
        nodeptr = nodeptr->next;
    }
    if (!alreadyhashed) {
        Node* newnode;
        newnode = new Node;
        newnode->count = 1;
        newnode->word = word;
        // if a collision increase cols
        if (table[index] != nullptr) {
            cols++;
        }
        newnode->next = table[index];
        table[index] = newnode;
        // a new unique word
        uwords++;
    }
}

unsigned int RSHash(const char* str, unsigned int length)
{
    // random keys for hash function
    unsigned int b    = 378551;
    unsigned int a    = 63689;

    unsigned int hash = 0;

    // loop through string hashing based off each letter
    for (int i = 0; i < length; ++str, ++i)
    {
        // turn char into int and add it to hash X a
        hash = hash * a + (*str);
        // multiply a by b
        a = a * b;
    }
    // make sure hash will fit into table
    hash = hash % TABLE_SIZE;
    return hash;
}