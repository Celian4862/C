#include <stdio.h>

struct Triangle {
    float side1, side2, side3;
};

void merge(struct Triangle arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    struct Triangle L[n1], R[n2];

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i].side1 + L[i].side2 + L[i].side3 < R[j].side1 + R[j].side2 + R[j].side3) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct Triangle arr[], int left, int right) {
    if (left < right) {
        // Same as (left+right)/2, but avoids overflow for large left and right
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

int main() {
    int n;
    printf("Enter the number of triangles: ");
    scanf("%d", &n);

    struct Triangle triangles[n];

    // Input triangles
    for (int i = 0; i < n; i++) {
        printf("Enter sides of triangle %d (space-separated): ", i + 1);
        scanf("%f %f %f", &triangles[i].side1, &triangles[i].side2, &triangles[i].side3);
    }

    // Perform merge sort
    mergeSort(triangles, 0, n - 1);

    // Display sorted triangles
    printf("\nSorted Triangles:\n");
    for (int i = 0; i < n; i++) {
        printf("Triangle %d: %.2f %.2f %.2f\n", i + 1, triangles[i].side1, triangles[i].side2, triangles[i].side3);
    }

    return 0;
}
