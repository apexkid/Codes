#include <iostream>

using namespace std;

int main()
{
	int n;
	int arr[100];
	int x;

	cout << "Enter number of elements";
	cin >> n;
	cout << endl << "Enter elements";
	
	for(int i = 0; i < n; i++)
	{
		cin >> x;
		arr[i] = x;
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n-1; j++)
		{
			int temp;
			if(arr[j] < arr[j+1])
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}

	cout << endl << "Sorted order";
	for(int i = 0; i < n; i++)
		cout << arr[i] << endl;
	
	return 0;
}
