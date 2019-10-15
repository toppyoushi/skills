#include <iostream>
#include <vector>
using namespace std;
vector<vector<int> > array;
bool Find(int target, vector<vector<int> > array) {
        bool found = false;
        int row = 0;
        int column = array[0].size()-1;
        cout<<row<<""<<column<<endl;
        int i = column;
        int j = row;
        while(i>0 && j <=column)
        {
            cout<<array[i][j]<<endl;
            if(array[i][j] == target)
            {
                found = true;
                break;
            }
            else if(array[i][j] > target)
            {
                i--;
            }
            else
                j++;
        }
        return found;
    }
int main()
{
    array.push_back({1,2,3,4,5});
    array.push_back({3,4,6,6,2});
    Find(3,array);
}