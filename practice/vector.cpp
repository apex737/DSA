#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
void printAll(const vector<int>& v)
{
    for(int i: v) cout << i << " ";
    cout << "\n\n";
}
int main()
{
    vector<int> v{1,2,3,4,5};
    v.push_back(6);
    v.emplace(v.begin(), 7);
    printAll(v); 
    vector<int>::iterator it = v.end();  // 7 1 2 3 4 5 6 ()
    it = v.erase(prev(it, 2), v.end());  
    advance(it, -1);
    printAll(v); // 7 1 2 3 (4) 
    sort(v.begin(), prev(it, 1));
    printAll(v); // 1 2 7 3 4
    cout << *it << "\n\n"; // 4; But... Invalid
    it = v.begin(); // init iterator 
    reverse(v.begin(), next(it, 3));
    printAll(v); // 7 2 1 3 4 
}