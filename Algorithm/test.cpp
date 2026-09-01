#include <iostream>
#include <string>
using namespace std;
string s = "Hello, my favorite color is blue";
int main(void)
{
    string t1 = "favorite";
    string t2 = "blue";
    cout << s.substr(s.find(t1), t1.length()) << ": " << s.substr(s.find(t2), t2.length());
    return 0;
}
