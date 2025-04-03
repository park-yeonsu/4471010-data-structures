#include <stdio.h>
#include <stdlib.h>

void Merge(int arr[], int left, int mid, int right, int temp[]) {
  int i = left;
  int j = mid + 1;
  int k = left;

  while (i <= mid && j <= right) {
    if (arr[i] <= arr[j]) {
      temp[k++] = arr[i++];
    } else {
      temp[k++] = arr[j++];
    }
  }

  while (i <= mid) {
    temp[k++] = arr[i++];
  }

  while (j <= right) {
    temp[k++] = arr[j++];
  }

  for (i = left; i <= right; i++) {
    arr[i] = temp[i];
  }
}

void MergeSortRecursive(int arr[], int left, int right, int temp[]) {
  if (left < right) {
    int mid = (left + right) / 2;

    MergeSortRecursive(arr, left, mid, temp);
    MergeSortRecursive(arr, mid + 1, right, temp);

    Merge(arr, left, mid, right, temp);
  }
}

void MergeSort(int arr[], int n) {
  int* temp = (int*)malloc(n * sizeof(int));
  if (temp == NULL) {
    printf("Memory allocation failed\n");
    return;
  }

  MergeSortRecursive(arr, 0, n - 1, temp);

  free(temp);
}

int main() {
  int n;
  scanf("%d", &n);

  int* arr = (int*)malloc(n * sizeof(int));
  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  for (int i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  MergeSort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d\n", arr[i]);
  }

  free(arr);
  return 0;
}
