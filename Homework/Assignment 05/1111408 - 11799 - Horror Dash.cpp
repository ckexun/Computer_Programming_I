#include <iostream>
#include <algorithm>
using namespace std;

int recMaxSpeed( int numRemaining );

int main()
{
	int T; //�X������
	cin >> T;
	for( int i = 1; i <= T; i++ )
	{
		int N; //�ǥͼ�
		cin >> N;
		cout << "Case " << i << ": " << recMaxSpeed( N ) << endl;
	}

	system( "pause" );
}

int recMaxSpeed( int numRemaining )
{
	int speed;
	cin >> speed;
	if (numRemaining == 1) { //���j�̩��h�W��
		return speed;
	}
	else{  
		int last = recMaxSpeed(numRemaining - 1); 
		if (speed > last) {
			return speed;
		}
		else {
			return last;
		}
	}
}