#include <iostream>
using namespace std;
int binary_search(int arr[], int beg, int end, int val)
{
	while (beg <= end)
	{
    	int mid = (beg + end) / 2;
    	if (arr[mid] == val)
    	{
        	return mid;
    	}
    	else if (arr[mid] < val)
    	{
        	beg = mid + 1;
    	}
    	else
    	{
        	end = mid - 1;
    	}
	}
	return -1;
}
int linear_search(int arr[], int n, int x)
{
	for (int i = 0; i < n; i++)
    	if (arr[i] == x)
        	return i;
	return -1;
}
int main()
{
	int n, x;
	cout << "Enter number of elements : ";
	cin >> n;
	int a[n];
	cout << "Enter array elements : ";
	for (int i = 0; i < n; i++)
	{
    	cin >> a[i];
	}
 
	// linear search
	cout << "Using Linear search -" << endl;
	cout << "Enter element to be searched : ";
	cin >> x;
	int ans = linear_search(a, n, x);
	if (ans == -1)
    	cout << x << " not found." << endl;
	else
    	cout << x << " found at position " << ans + 1 << endl;
 
	// binary search
 
	cout << "Using Binary search -" << endl;
	for (int i = 0; i < n - 1; i++)
	{
    	for (int j = 0; j < n - i - 1; j++)
    	{
        	if (a[j] > a[j + 1])
        	{
            	int temp = a[j];
            	a[j] = a[j + 1];
            	a[j + 1] = temp;
        	}
    	}
	}
	cout << "sorted array is : " << endl;
	for (int i = 0; i < n; i++)
	{
    	cout << a[i] << " ";
	}
 
	cout << "\nEnter element to be searched : ";
	cin >> x;
	int res = binary_search(a, 0, n - 1, x);
	if (res == -1)
    	cout << x << " not found." << endl;
	else
    	cout << x << " found at position " << res + 1 << endl;
	return 0;
}
