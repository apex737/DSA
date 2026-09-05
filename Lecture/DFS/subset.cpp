#include <iostream>
using namespace std;

bool isused[4];

void func(int k) {
    if (k == 4) {
        cout << "{";
        for (int i = 0; i < 4; i++) {
            if (isused[i])
                cout << i;
        }
        cout << "}\n";
        return;
    }

    // k를 선택하지 않는 경우
    func(k + 1);

    // k를 선택하는 경우
    isused[k] = true;
    func(k + 1);
    isused[k] = false;
}

int main() {
    func(0);
    return 0;
}