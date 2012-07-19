#include "Trie.hpp"
#include <ctype.h>

Trie::Trie()
{
    for(int i = 0; i < 26; i++)
    {
        this->children[i] = 0;
    }
    this->isword = false;
}

Trie::~Trie()
{
    for(int i = 0; i < 26; i++)
    {
        if(this->children[i])
        {
            delete this->children[i];
        }
    }
}

void Trie::addWord(const std::string & word, int index)
{
    if(index == word.size())
    {
        this->isword = true;
    }
    else
    {
        int i = tolower(word[index]) - 'a';
        if(i < 0 || i > 25)
        {
            return;
        }
        if(!this->children[i])
        {
            this->children[i] = new Trie();
        }
        this->children[i]->addWord(word, index + 1);
    }
}

bool Trie::contains(const std::string & word, int index)
{
    if(index == word.size())
    {
        return this->isword;
    }
    else
    {
        int i = tolower(word[index]) - 'a';
        if(i < 0 || i > 25)
        {
            return false;
        }
        if(!this->children[i])
        {
            return false;
        }
        return this->children[i]->contains(word, index + 1);
    }
}
