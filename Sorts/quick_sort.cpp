#include <iostream>
#include <algorithm>

using namespace std;

int partition(int arr[], int s, int e);
void quicksort(int arr[], int s, int e);

void quicksort(int arr[], int s, int e)
{
	if(s < e)
	{
		int pivot = partition(arr, s, e);
		cout << "partion value = " << pivot;
		quicksort(arr, s, pivot -1);
		quicksort(arr, pivot +1, e);
	}
	return;
}

int partition(int arr[], int s, int e)
{
	int key = arr[e];
	int i, j;
	i = s;
	
	for(j = s; j < e; j++ )
	{
		if(arr[j] >= key)
		{
			swap(arr[i], arr[j]);
			i++;
		}
	}
	swap(arr[i], arr[e]);
	return i;
}

int main()
{
	int arr[] = {1, 2, 32, 1, 4};
	quicksort(arr, 0, 4);

	cout << "Sorted array" << endl;
	for(int i = 0; i < 5; i++)
		cout << arr[i] << endl;
	return 0;
}

