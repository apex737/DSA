#include <iostream>
#include <vector>

using namespace std;

// items: 전체 데이터, selected: 현재 선택된 데이터, start: 탐색 시작 인덱스, r: 뽑을 개수
void combination(const vector<int>& items, vector<int>& selected, int start, int r) {
    // 1. Base Case: r개를 모두 뽑았을 때
    if (selected.size() == r) {
        for (int val : selected) {
            cout << val << " ";
        }
        cout << endl;
        return;
    }

    // 2. Recursive Step: start 인덱스부터 끝까지 탐색
    for (int i = start; i < items.size(); ++i) {
        // 현재 요소 선택
        selected.push_back(items[i]);
        
        // 다음 요소를 뽑기 위해 재귀 호출 (현재 인덱스 i + 1 전달)
        combination(items, selected, i + 1, r);
        
        // 백트래킹: 선택 해제 (상태 복구)
        selected.pop_back();
    }
}

int main() {
    vector<int> items = {1, 2, 3, 4};
    vector<int> selected;
    int r = 2;

    cout << "4개 중 2개를 선택하는 조합:" << endl;
    combination(items, selected, 0, r);

    return 0;
}