#include <stdio.h>
#include <stdbool.h>

// Function prototypes
bool isValid(const int arr[], int length, int pos);  // Check if position is valid in the array
void remove_element(int arr[], int length, int pos); // Remove element at a given position
void insert_element(int arr[], int length, int pos, int value); // Insert element at a given position
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]); // Reshape 1D array to 2D
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]); // Transpose a 2D matrix
bool found_duplicate(int arr[], int length);  // Check for duplicates in the array

// Main function
int main() {
    // Initialize a 1D array with some elements
    int arr[] = {15, 33, 30, 30, 55, 60};
    int length = sizeof(arr) / sizeof(arr[0]);  // Calculate the length of the array

    // Print the original array
    printf("Original array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Remove element at index 2
    remove_element(arr, length, 2);
    printf("After removing element at index 2: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Insert 90 at index 2
    insert_element(arr, length, 2, 90);
    printf("After inserting 80 at index 2: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // Reshape the array into a 2D array with 2 rows and 3 columns
    int nRows = 2, nCols = 3;
    int arr2d[nRows][nCols];
    reshape(arr, length, nRows, nCols, arr2d);
    printf("Reshaped array:\n");
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    // Transpose the 2D array
    int mat_transp[nCols][nRows];
    trans_matrix(nRows, nCols, arr2d, mat_transp);
    printf("Transposed matrix:\n");
    for (int i = 0; i < nCols; i++) {
        for (int j = 0; j < nRows; j++) {
            printf("%d ", mat_transp[i][j]);
        }
        printf("\n");
    }

    // Check if the array contains duplicates
    bool has_duplicate = found_duplicate(arr, length);
    printf("Array has duplicate: %s\n", has_duplicate ? "true" : "false");

    return 0;
}

// Function to check if a given position is valid in the array
bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);  // Return true if position is within valid bounds
}

// Function to remove an element from the array at the specified position
void remove_element(int arr[], int length, int pos) {
    // Validate the position
    if (!isValid(arr, length, pos)) {
        printf("Invalid position\n");
    } else {
        // Shift elements to the left to fill the gap created by removal
        for (int i = pos; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
    }
}

// Function to insert an element at the specified position in the array
void insert_element(int arr[], int length, int pos, int value) {
    // Validate the position
    if (!isValid(arr, length, pos)) {
        printf("Invalid position\n");
    } else {
        // Shift elements to the right to make space for the new element
        for (int i = length - 1; i > pos; i--) {
            arr[i] = arr[i - 1];
        }
        arr[pos] = value;  // Insert the new value at the specified position
    }
}

// Function to reshape a 1D array into a 2D array with specified rows and columns
void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    // Check if the total number of elements matches the required number of rows and columns
    if (length != nRows * nCols) {
        printf("Invalid dimensions\n");  // Error message if dimensions don't match
    } else {
        int i = 0;  // Index for the 1D array
        // Loop through rows and columns to fill the 2D array
        for (int j = 0; j < nRows; j++) {
            for (int k = 0; k < nCols; k++) {
                arr2d[j][k] = arr[i];  // Assign elements from 1D array to 2D array
                i++;  // Move to the next element in the 1D array
            }
        }
    }
}

// Function to transpose a matrix (swap rows with columns)
void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    // Loop through the rows and columns and swap them to transpose the matrix
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];  // Swap rows and columns
        }
    }
}

// Function to check if there are any duplicates in the array
bool found_duplicate(int arr[], int length) {
    // Compare each element with every other element to check for duplicates
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {  // Duplicate found
                return true;
            }
        }
    }
    return false;  // No duplicates found
}

