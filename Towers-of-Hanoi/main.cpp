// Computer Programming
// "Towers of Hanoi"
//
#include <iostream>
#include <string>
using namespace std;

void Hanoi(int Num, char first, char second, char third){
  if(Num == 1){
    cout << "Move disk 1 from " << first << " to " << third << endl;
    return;
  }
  
  Hanoi(Num - 1, first, third, second);
  cout << "Move disk " << Num << " from " << first << " to " <<  third  << endl;
  Hanoi(Num - 1, second, first, third);
}

int main(){ 
char A = 'A';
char B = 'B';
char C = 'C';
int inputDisks;
  
  try{
   cout << "How many disks should the tower consist of?";
   cin >> inputDisks;
   if (cin.fail() || inputDisks <= 0){
    throw runtime_error("invalid input.");
   }
   Hanoi(inputDisks,A,B,C);
  }
  
  catch (runtime_error& excpt) {
  cout << excpt.what() << endl;
  }
  return 0;
}