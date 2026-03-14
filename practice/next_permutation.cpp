#include <bits/stdc++.h>
using namespace std;

void testCombination()
{
  int a[]={0,0,0,0,1};
  do {
    for(int i=0;i<5;i++)
      if(a[i]==0) cout<<i+1;
    cout<<"\n";
  } while(next_permutation(a,a+5));
}

void testPermutation()
{
  int myints[] = {1,2,3};

  std::sort (myints,myints+3);

  std::cout << "The 3! possible permutations with 3 elements:\n";
  do {
    std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
  } while ( std::next_permutation(myints,myints+3) );

  std::cout << "After loop: " << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';

}


int main() 
{

  testCombination();
}