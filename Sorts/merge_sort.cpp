#include <iostream>

using namespace std;

void merge(int arr[], int s, int mid, int e);
void mergesort(int arr[], int s, int e)
{
	if(s < e)
	{
		int mid = (s + e) /2;
		mergesort(arr, s, mid);
		mergesort(arr, mid + 1, e);
		merge(arr, s, mid, e);
	}
	return;
}

void merge(int arr[], int s, int mid,  int e)
{
	int a, b, j;
	int len1 = mid - s + 1;
	int len2 = e - mid;
	int x[len1 + 1];
	int y[len2 + 1];
	
	x[len1] = 10000;
	y[len2] = 10000;
	
	j = s;
	for(int i = 0; i < len1; i++)
		x[i] = arr[s + i];
	
	for(int i = 0; i < len2; i++)
		y[i] = arr[mid + i + 1];
	
	a = 0;
	b = 0;
	
	for(int i= s; i <= e; i++)
	{
		if(x[a] < y[b])
		{
			arr[i] = x[a];
			a++;
		}
		else
		{
			arr[i] = y[b];
			b++;
		}
	}
	return;
}


int main()
{
	int arr[] = {4, 31, 2, 1};
	

	cout << "Original array" << endl;
	for(int i = 0; i < 4; i++)
		cout << endl << arr[i];

	mergesort(arr, 0, 3);

	cout << "Sorted array" << endl;
	for(int i = 0; i < 4; i++)
		cout << endl << arr[i];

	return 0;
}
