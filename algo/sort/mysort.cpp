#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
//o(nlogn) o(nlogn) o(n^2) o(logn)
void quicksort(vector<int> &a, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int low = l, high = r;
    int t = a[low];
    while (low < high)
    {
        while (low < high && a[high] > t)
        {
            high--;
        }
        if (low < high)
        {
            a[low] = a[high];
            low++;
        }
        while (low < high && a[low] <= t)
        {
            low++;
        }
        if (low < high)
        {
            a[high] = a[low];
            high--;
        }
    }
    a[low] = t;
    quicksort(a, l, low - 1);
    quicksort(a, low + 1, r);
}
//o(n^2) o(n) o(n^2) o(1)
void insertsort(vector<int> &a)
{
    for (int i = 1; i < a.size(); ++i)
    {
        int temp = a[i];
        int j = i - 1;
        while (j >= 0)
        {
            if (temp >= a[j])
                break;
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = temp;
    }
}
//o(n^2) o(nlogn) o(n^2) o(1)
void binsort(vector<int> &a)
{
    for (int i = 1; i < a.size(); ++i)
    {
        int temp = a[i];
        int l = 0;
        int r = i - 1;
        while (l <= r)
        {
            int m = (l + r) / 2;
            if (a[m] > temp)
            {
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }
        for (int j = i - 1; j >= l; --j)
        {
            a[j + 1] = a[j];
        }
        a[l] = temp;
    }
}
void shellinsert(vector<int> &a, int delta)
{
    for (int i = delta; i < a.size(); ++i)
    {
        int temp = a[i];
        int j = i - delta;
        while (j >= 0)
        {
            if (a[j] < temp)
                break;
            a[j + delta] = a[j];
            j -= delta;
        }
        a[j + delta] = temp;
    }
}
//o(n^(1.5))  -  -  o(1)
void shellsort(vector<int> &a)
{
    int delta = 5;
    while (delta > 1)
    {
        shellinsert(a, delta);
        delta /= 2;
    }
    shellinsert(a, 1);
}
//o(n^2) o(n) o(n^2) o(1)
void bubblesort(vector<int> &a)
{
    for (int i = 0; i < a.size() - 1; ++i)
    {
        for (int j = 1; j < a.size(); ++j)
        {
            if (a[j - 1] > a[j])
            {
                swap(a[j - 1], a[j]);
            }
        }
    }
}
//o(n^2) o(n^2) o(n^2) o(1)
void selectsort(vector<int> &a)
{
    for (int i = 0; i < a.size() - 1; ++i)
    {
        for (int j = i + 1; j < a.size(); ++j)
        {
            if (a[j] < a[i])
            {
                int temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
}
void shiftheap(vector<int> &a, int begin, int end)
{
    if (begin < 0 || end >= a.size())
        return;
    while (begin < end)
    {
        int left = begin * 2 + 1;
        int right = begin * 2 + 2;
        int max = begin;
        if (left <= end)
        {
            if (a[left] > a[max])
                max = left;
        }
        if (right <= end)
        {
            if (a[right] > a[max])
                max = right;
        }
        if (max == begin)
            break;
        swap(a[max], a[begin]);
        begin = max;
    }
}
void createheap(vector<int> &a)
{
    for (int i = a.size() / 2; i >= 0; i--)
    {
        shiftheap(a, i, a.size() - 1);
    }
}
//o(nlogn) o(nlogn) o(nlogn) o(1)
void heapsort(vector<int> &a)
{
    createheap(a);
    swap(a[0], a[a.size() - 1]);
    for (int i = a.size() - 2; i > 0; --i)
    {
        shiftheap(a, 0, i);
        swap(a[0], a[i]);
    }
}
void merge(vector<int> &a, int l, int mid, int r)
{
    vector<int> b;
    int i = l, j = mid + 1;
    while (i <= mid && j <= r)
    {
        if (a[i] < a[j])
        {
            b.push_back(a[i]);
            i++;
        }
        else
        {
            b.push_back(a[j]);
            j++;
        }
    }
    if (i > mid)
    {
        while (j <= r)
        {
            b.push_back(a[j]);
            j++;
        }
    }
    if (j > r)
    {
        while (i <= mid)
        {
            b.push_back(a[i]);
            i++;
        }
    }
    for (int i = 0; i < b.size(); ++i)
    {
        a[l+i] = b[i];
    }
}
//o(nlogn) o(nlogn) o(nlogn) o(n)
void mergesort(vector<int> &a, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    mergesort(a, l, mid);
    mergesort(a, mid + 1, r);
    merge(a, l, mid, r);
}
int main()
{
    vector<int> a;
    int temp, n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> temp;
        a.push_back(temp);
    }
    // insertsort(a);
    // binsort(a);
    // shellsort(a);
    // bubblesort(a);
    // quicksort(a, 0, a.size() - 1);
    // selectsort(a);
    // heapsort(a);
    mergesort(a, 0, a.size() - 1);
    for (int i = 0; i < n; ++i)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}