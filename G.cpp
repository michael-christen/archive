//Calculate max open on board
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int MAX_SIZE = 40000;
//sel == 1 0r 0, 0 is row, 1 is col
int maxOpen(bool arr[MAX_SIZE][2],int n, int sel)
{
	int maxO = 0;
	int count=0;
	bool counting = false;
	for(int i = 0; i < n; i++)
	{
		if(arr[i][sel] == true)
		{
			if(count > maxO)
			{
				maxO = count;
			}
			count = 0;
			counting = false;
		}
		else if(i == n-1)
		{
			count ++;
			if(count > maxO)
				maxO = count;
		}
		else count ++;

		
	}
	return maxO;
}

int main()
{
	bool board[MAX_SIZE][2] = {false};
	int width,height,n;
	int maxR,maxCol;
	int tempx,tempy;
	bool first = true;
	while( cin >> width >> height >> n && (width!= 0 || height != 0 || n != 0))
	{
		//clear board cols
		for(int i = 0; i < width; i ++)
		{
			board[i][1] = false;
		}
		for(int i = 0; i< height; i++)
		{
			board[i][0] = false;
		}
		for(int i = 0; i < n; i++)
		{
			cin >> tempx >> tempy;
			board[tempx-1][1] = true;
			board[tempy-1][0] = true;
		}

		maxR = maxOpen(board,height,0);
		maxCol = maxOpen(board,width,1);
		if(!first)
			cout << endl;
		first = false;
		cout << maxCol*maxR;
	}
	return 0;
}

