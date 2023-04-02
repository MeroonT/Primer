// Computer Programming 
// "Collatz"
// 
#include <iostream>
using namespace std;

int main() 
{
  int number;
  
  cout << "Enter the first number of the sequence: ";
  cin >> number;
  cout << number;
  
  while (number > 1) 
  {
    if (number % 2 == 0) {
      number = (number / 2);
    }
    else {
      number = ((3 * number) + 1);
    }
  cout << " " << number;
  }
  
  return 0;
}