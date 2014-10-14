#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <functional>
#include <fstream>
#include <string>
#include <deque>
#include <set>
#include <vector>
#include "Trie.hpp"

using namespace std;

char * * board;
unsigned int board_width;
Trie * dict;

deque<char> current_word;
set<string> found_words;

bool sortfunc(const string & a, const string & b)
{
    if(a.size() == b.size())
    {
        return a < b;
    }
    else
    {
        return a.size() > b.size();
    }
}

void search(int x, int y, Trie * pos)
{
    if(pos->isWord())
    {
        string word;
        word.resize(current_word.size());
        int i = 0;
        for(deque<char>::iterator iter = current_word.begin(); iter != current_word.end(); iter++)
        {
            word[i] = *iter;
            i++;
        }
        found_words.insert(word);
    }

    for(int xx = x-1; xx <= x+1; xx++)
    {
        for(int yy = y-1; yy <= y+1; yy++)
        {
            if(xx >= 0 && xx < board_width && yy >= 0 && yy < board_width && pos->hasChild(board[xx][yy]))
            {
                current_word.push_back(board[xx][yy]);
                board[xx][yy] = '.';
                search(xx, yy, pos->getChild(current_word.back()));
                board[xx][yy] = current_word.back();
                current_word.pop_back();
            }
        }
    }
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        cout << "Dictionary argument required!" << endl;
        return 1;
    }
    dict = new Trie();
    {
        ifstream fin;
        string line;

        fin.open(argv[1]);
        if(!fin.is_open())
        {
            cout << "Could not open file " << argv[1] << endl;
            return 1;
        }
        while(true)
        {
            fin >> line;
            if(fin.eof())
            {
                break;
            }
            dict->addWord(line);
        }
        fin.close();
    }
    cin >> board_width;
    if(board_width <= 0)
    {
        cout << "Invalid board width" << endl;
        return 1;
    }
    board = new char * [board_width];
    for(int y = 0; y < board_width; y++)
    {
        board[y] = new char[board_width];
    }
    for(int y = 0; y < board_width; y++)
    {
        for(int x = 0; x < board_width; x++)
        {
            cin >> board[x][y];
            board[x][y] = tolower(board[x][y]);
            if(!(board[x][y] >= 'a' && board[x][y] <= 'z'))
            {
                cout << "Incorrect board format!" << endl;
                return 0;
            }
        }
    }
    for(int y = 0; y < board_width; y++)
    {
        for(int x = 0; x < board_width; x++)
        {
            search(x, y, dict);
        }
    }
    vector<string> words;
    words.resize(found_words.size());
    int i = 0;
    for(set<string>::iterator iter = found_words.begin(); iter != found_words.end(); iter++)
    {
        words[i++] = (*iter);
    }
    sort(words.begin(), words.end(), sortfunc);
    cout << "Found " << words.size() << " words" << endl;
    for(vector<string>::iterator iter = words.begin(); iter != words.end(); iter++)
    {
        if((*iter).size() != 1)
        {
            cout << (*iter) << endl;
        }
    }
    delete dict;
    return 0;
}
