#include <iostream>
#include <string>
using namespace std;
int getNext(int *next, string p);
int kmp(string s, string p);
int main()
{
    string s;
    cin >> s;
    string p;
    cin >> p;
    cout << kmp(s, p) << endl;
    return 0;
}
int getNext(int *next, string p)
{
    next[0] = -1;
    int k = -1;
    int i = 0;
    while (i < p.size())
    {
        if (k == -1 || p[i] == p[k])
        {
            next[++i] = ++k;
        }
        else
        {
            k = next[k];
        }
    }
}
int kmp(string s, string p)
{
    int *next = new int[p.size()];
    getNext(next, p);
    int i = 0, j = 0;
    int l1 = s.size();
    int l2 = p.size();
    while (i < l1 && j < l2)
    {
        if (j == -1 || s[i] == p[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == l2)
        return i - j;
    return -1;
}