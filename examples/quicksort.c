/***********************************************************************
*
* FILENAME: parentheses_checker.c
*
* DESCRIPTION: Sort a given set of integer 
* values using Quicksort algorithm 
*
* AUTHOR: gfvante - 15 August 2019
*
***********************************************************************/

#include <stdio.h>
#define N 10

void quicksort(int a[], int low, int high);
int divide(int a[], int low, int high);

int main(void)
{
	int a[N];

	printf("Enter %d numbers to be sorted: ", N);
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);

	quicksort(a, 0, N - 1);

	printf("In sorted order: ");
	for (int i = 0; i < N; i++)
		printf("%d ", a[i]);
	
	printf("\n");

	return 0;
}

/* Quicksort - Recursive version */
void quicksort(int a[], int low, int high)
{
	int piv;

	if (low >= high) return;
	piv = divide(a, low, high);
	quicksort(a, low, piv - 1);
	quicksort(a, piv + 1, high);
}

int divide(int a[], int low, int high)
{
	int pElem = a[low];

	for (;;) {
		while (low < high && pElem <= a[high])
			high--;
		if (low >= high) break;
		a[low++] = a[high];

		while (low < high && a[low] <= pElem)
			low++;
		if (low >= high) break;
		a[high--] = a[low];
	}

	a[high] = pElem;
	return high;
}
