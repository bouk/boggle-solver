#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>

class Trie
{
public:
    Trie();
    ~Trie();

    void addWord(const std::string & word)
    {
        this->addWord(word, 0);
    }

    bool contains(const std::string & word)
    {
        return this->contains(word, 0);
    }

    Trie * getChild(char c)
    {
        int i = c - 'a';
        if(i < 0 || i > 25)
        {
            return 0;
        }
        return this->children[i];
    }

    bool hasChild(char c)
    {
        int i = c - 'a';
        if(i < 0 || i > 25)
        {
            return false;
        }
        return !!this->children[i];
    }

    bool isWord()
    {
        return this->isword;
    }

protected:
    bool contains(const std::string & word, int index);
    void addWord(const std::string & word, int index);

private:
    bool isword;
    Trie * children[26];
};
#endif
