/* Sorts a given set of integer values using Quicksort algorithm */

#include <stdio.h>
#define N 10

void quicksort(int a[], int low, int high);

int main(void)
{
	int a[N];

	printf("Enter %d numbers to be sorted: ", N);
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);

	quicksort(a, 0, N - 1);

	printf("In sorted order: ");
	for (int i = 0; i < N - 1; i++)
		printf("%d ", a[i]);
	
	printf("\n");

	return 0;
}

void quicksort(int a[], int low, int high)
{

}