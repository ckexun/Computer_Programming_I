// UVa 10931 - Parity
// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1872

#include <iostream>
using namespace std;

int recFindParity( int numProcessing, int bin[], int &binSize );

int main()
{
   int I;
   cin >> I;
   while ( I ) 
   {
      int parity = 0;
      int binSize = 0;  // 二進制下的位數
      int bin[32] = {};  // 二進制下的表示（倒序儲存，例如 10 = 0101）

      parity = recFindParity(I, bin, binSize);

      cout << "The parity of ";
      for (int i = binSize - 1; i >= 0; i--)
         cout << bin[i];
      cout << " is " << parity << " (mod 2).\n";

      cin >> I;
   }

   system( "pause" );
}

int recFindParity( int numProcessing, int bin[], int &binSize )
{

   
   
}