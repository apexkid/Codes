#include <iostream>

using namespace std;

int main()
{
	int n;
	int arr[100];
	int x;
	int temp;
	
	cout << "Enter num of elements" << endl;
	cin >> n;
	
	for(int i = 0; i < n; i++)
	{
		cin >> x;
		arr[i] = x;
	}
	
	for(int i = 1; i < n; i++ )
	{
		int key = arr[i];
		int j = i-1;
		
		while( j >= 0 && arr[j] > key)
		{
			arr[j +1] = arr[j];
			j--;
		}
		arr[j+1] = key;
	}

	for(int i = 0; i < n; i++)
		cout << endl << arr[i];
	
	return 0;
}
