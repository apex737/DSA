#include <list>
#include <iostream>
using namespace std;
void printAll(const list<int>& li)
{
    for(int i: li) cout << i << " ";
    cout << "\n\n";
}
int main()
{
    list<int> li = {1,2,3};
    // next, prev, advance 등으로 갱신 및 이동(복사본)
    list<int>::iterator it = li.end(); 
    cout << *(li.begin()) << "\n";  // 1
    cout << *(--it) << "\n";    // 3
    printAll(li);   // 1 2 3 
    li.push_back(4);
    li.pop_front();
    printAll(li);      // 2 (3) 4 
    advance(it, -1);   // (2) 3 4 
    /* insert/emplace 위치는 노드의 왼쪽; end()를 고려함 */
    it = li.insert(it, 1);  // 1 (2) 3 4; 
    /* insert/emplace는 삽입 위치를 it로 반환 */
    cout << *it << "\n\n";  // (1) 2 3 4; 
    /* erase 후에는 반드시 it 갱신 */
    // 지운 바로 다음 칸을 가리킴 
    it = li.erase(it, next(it, 2)); 
    printAll(li);      // (3) 4
    li.insert(it, 2);  // it를 받지 않으면 위치 그대로
    printAll(li);      // 2 (3) 4
    return 0;
}