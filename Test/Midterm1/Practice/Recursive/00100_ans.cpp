// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=36
// 100 - The 3n + 1 problem
#include <iostream>
using namespace std;

// returns the maximum cycle-length over all integers
// between and including first and last
int maxCycleLength( int first, int last );

int cycleLength( int n ); // returns the cycle-length of n

int main()
{
   int i, j;
   while( cin >> i >> j )
   {
      cout << i << ' ' << j << ' ';

      if( i > j )
      {
         int buf = i;
         i = j;
         j = buf;
      }

      cout << maxCycleLength( i, j ) << endl;
   }
}

int maxCycleLength( int first, int last )
{
   if (first == last)
      return cycleLength(first);

   int lastMax = maxCycleLength(first + 1, last);
   int now = cycleLength(first);
   return max(now, lastMax);
}

int cycleLength( int n )
{
   if (n == 1)
      return 1;

   if (n % 2 == 1)
      return 1 + cycleLength(3 * n + 1);
   else
      return 1 + cycleLength(n / 2);
}