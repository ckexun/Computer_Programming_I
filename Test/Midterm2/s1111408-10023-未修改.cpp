// Compute the square root of a huge integer.
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setfill;

#include <cstring>
#include <cmath>

struct HugeInt
{
   size_t size = 0;
   int *integer = nullptr;
};

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( HugeInt &hugeInt, HugeInt &squareRoot );

// put the square of hugeInt into the array square
void compSquare( HugeInt &hugeInt, HugeInt &square );

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 );

// if hugeInt1 < hugeInt2, return true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 );

int main()
{
   int testCase;
   cin >> testCase;
   for( int i = 1; i <= testCase; i++ )
   {
      char str[ 1010 ] = {};
      cin >> str;

      size_t numDigits = strlen( str );
      if( numDigits < 10 )
         cout << sqrt( atoi( str ) ) << endl;
      else
      {
         int *digits = new int[ numDigits + 2 ]();
         for( size_t j = 0; j < numDigits; ++j )
            digits[ j ] = str[ numDigits - 1 - j ] - '0';

         size_t last = ( numDigits - 1 ) / 3;
         HugeInt hugeInt;
         hugeInt.size = last + 1;
         hugeInt.integer = new int[ hugeInt.size ]();
         for( size_t j = 0; j <= last; j++ )
            hugeInt.integer[ j ] = digits[ 3 * j ] + digits[ 3 * j + 1 ] * 10 + digits[ 3 * j + 2 ] * 100;

         HugeInt squareRoot; // the square root of hugeInt
         squareRoot.size = ( hugeInt.size + 1 ) / 2; // the number of digits of squareRoot
         squareRoot.integer = new int[ squareRoot.size ](); // the square root of hugeInt

         // put the square root of hugeInt into the array squareRoot
         compSquareRoot( hugeInt, squareRoot );

         cout << squareRoot.integer[ squareRoot.size - 1 ];
         for( int j = squareRoot.size - 2; j >= 0; j-- )
            cout << setw( 3 ) << setfill( '0' ) << squareRoot.integer[ j ];
         cout << endl;

         delete[] squareRoot.integer;
         delete[] hugeInt.integer;
         delete[] digits;
      }

      if( i < testCase )
         cout << endl;
   }

//   system( "pause" );
}

// put the square root of hugeInt into the array squareRoot
void compSquareRoot( HugeInt &hugeInt, HugeInt &squareRoot )
{
    squareRoot.size = (hugeInt.size + 1) / 2; 
    delete[] squareRoot.integer;
    squareRoot.integer = new int[squareRoot.size]();
    
    HugeInt square; //create square
    square.size = hugeInt.size;
    delete[] square.integer;
    square.integer = new int[square.size]();

    for (int i = squareRoot.size - 1; i >= 0; i--) { //squareRoot 2.1.0
        int low = 1;
        int high = 999;
        int middle;
        while (low <= high) {
            middle = (low + high) / 2;
            squareRoot.integer[i] = middle;
            compSquare(squareRoot, square); //square = squareRoot * squareRoot
            if (equal(hugeInt, square))
                break;
            if (less(hugeInt, square))
                high = middle - 1;
            else
                low = middle + 1;
        }
        if (less(hugeInt, square))
            middle--;
        squareRoot.integer[i] = middle;
    }
    delete[] square.integer;
}

// put the square of hugeInt into the array square
void compSquare( HugeInt &hugeInt, HugeInt &square )
{
    square.size = hugeInt.size * 2; //maxsize
    delete[] square.integer;
    square.integer = new int[square.size]();

    for (int i = 0; i < hugeInt.size; i++) //square = hugeInt * hugeInt
        for (int j = 0; j < hugeInt.size; j++)
            square.integer[i + j] += hugeInt.integer[i] * hugeInt.integer[j];

    for (int i = 0; i < square.size - 1; i++) { //¶i¦ì
        if (square.integer[i] >= 1000) {
            square.integer[i + 1] += square.integer[i] / 1000;
            square.integer[i] %= 1000;
        }
    }

    if (square.size > 1 && square.integer[square.size - 1] == 0) //check head 0
        square.size--;

}

// if hugeInt1 == hugeInt2, return true; otherwise, return false
bool equal( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
   if( hugeInt1.size != hugeInt2.size )
      return false;

   for( int i = hugeInt1.size - 1; i >= 0; i-- )
      if( hugeInt1.integer[ i ] != hugeInt2.integer[ i ] )
         return false;

   return true;
}

// if hugeInt1 < hugeInt2, retuen true; otherwise, return false
bool less( HugeInt &hugeInt1, HugeInt &hugeInt2 )
{
    if (hugeInt1.size < hugeInt2.size)
        return true;
    else if (hugeInt1.size > hugeInt2.size)
        return false;
    else {
        for (int i = hugeInt1.size - 1; i >= 0; i--) {
            if (hugeInt1.integer[i] > hugeInt2.integer[i])
                return false;
            else if (hugeInt1.integer[i] < hugeInt2.integer[i])
                return true;
        }
        return false;
    }
}