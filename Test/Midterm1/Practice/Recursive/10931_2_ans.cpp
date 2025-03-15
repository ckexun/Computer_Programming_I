// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1872
// 10931 - Parity
#include <iostream>
using namespace std;

// prints the binary representation of number,
// for example, if number is 10, then prints 1010
void displayBinary( int number );

// returns the sum of all bits of the binary representation of number,
// or equivalently the number of 1s in the binary representation of number,
// for example, if number is 10, then returns 2
int sumBits( int number );

int main()
{
   int number;
   cin >> number;
   while( number > 0 )
   {
      cout << "The parity of ";
      displayBinary( number );

      cout << " is " << sumBits( number ) << " (mod 2).\n";

      cin >> number;
   }

   system( "pause" );
}

void displayBinary( int number )
{
   if (number == 0)
      return;

   displayBinary(number / 2);
   cout << number % 2;
}

int sumBits( int number )
{
   if (number == 0)
      return 0;

   int nowDigit = number % 2;
   return nowDigit + sumBits(number / 2);
}