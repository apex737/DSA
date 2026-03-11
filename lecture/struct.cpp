#include <bits/stdc++.h>

using namespace std;
class StudentRecord
{
  char   name[10];
  float   GPA;
  int  age; 
public:
// 생성자 정의
    StudentRecord(const char* n, float g, int a) {
        strncpy(name, n, 9); // char 배열에 문자열 복사
        name[9] = '\0';      // null 문자로 끝맺음
        GPA = g;
        age = a;
    }
    void print(){
      cout << "name: " << name << " | ";
      cout << "age: " << age << " | ";
      cout << "GPA: " << GPA << " | ";
      cout << "\n";
    }
} ;

int main()
{
  StudentRecord sr("Alice", 3.3, 10);
  printf("packed: %zd\n", sizeof(sr));
  sr.print();
}