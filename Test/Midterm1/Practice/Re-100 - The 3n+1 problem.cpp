// UVa 100 - The 3n + 1 problem
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=36

#include <iostream>
using namespace std;

int recCycleLength( int numProcessing );

int main()
{
   int i;
   int j;
   
   while (cin >> i >> j)
   {
      int larger;  // i �M j ���j��
      int smaller; // i �M j ���p��
      int nowCycleLenth;
      int maxCycleLenth = 0;

      if (i > j)
      {
         larger = i;
         smaller = j;
      } 
      else
      {
         larger = j;
         smaller = i;
      }

      for (int k = smaller; k <= larger; k++) 
      {
         nowCycleLenth = recCycleLength(k);

         if (nowCycleLenth > maxCycleLenth)
            maxCycleLenth = nowCycleLenth;
      }

      cout << i << " " << j << " " << maxCycleLenth << endl;
   }

   system( "pause" );
}

int recCycleLength( int numProcessing )
{


   
}