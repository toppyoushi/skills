#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cmath>
#include <stdint.h>
#include <map>
#include <cstring>
using namespace std;
bool match(char *str, char *pattern)
{
    if (str == nullptr || pattern == nullptr)
        return false;
    int length1 = strlen(str);
    int length2 = strlen(pattern);
    int i = 0, j = 0;
    while (j < length2)
    {
        if (j < length2 - 1 && pattern[j + 1] == '*')
        {
            while (i < length1 && (pattern[j] == '.' || str[i] == pattern[j]))
                i++;
            j += 2;
        }
        else if (i < length1 && (pattern[j] == '.' || str[i] == pattern[j]))
        {
            i++;
            j++;
        }
        else
        {
            return false;
        }
    }
    if (i == length1 && j == length2)
        return true;
    return false;
}
int main()
{
    // char *s1 = new char[100], *s2 = new char[100];
    // cin >> s1 >> s2;
    char s1[] = "abababab";
    char s2[] = "ab.*b";
    cout << s1 << s2 << endl;
    cout << match(s1, s2) << endl;
    return 0;
}