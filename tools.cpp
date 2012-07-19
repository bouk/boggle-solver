#include "tools.hpp"

int cti(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        return c - 'a';
    }
    else if(c >= 'A' && c <= 'Z')
    {
        return c - 'A';
    }
    else
    {
        return 0;
    }
}
