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
		for(int j = 0; j < n; j++)
		{
			int temp;
			if(arr[i] < arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	cout << endl << "Sorted order";
	for(int i = 0; i < n; i++)
		cout << arr[i] << endl;
	
	return 0;
}
