
#include <stdio.h>

int main() {
  int myArr[] = {5, 3, 4, 2, 7, 6, 9};
  
  printf(qSort(&myArr));
 
  return 0;
}

int quickSort(int* arr){
  int arrSize = sizeOf(arr)/sizeOf(arr[0]); // Get the size of the array
  
  if(arrSize == 1){ // If the array only has one value, return the array
    return arr;
  }
  
  int pointer = arr[arrSize / 2]; // Set the pointer at half the array size

  // Get pointer index
  int ptrIndex = NULL;
  for (int i=0; i<arrSize; i++){
    if (arr[i] == pointer){
      int ptrIndex = i;
      break;
    }
  }

  int left[ptrIndex - 1];
  int right[arrSize - ptrIndex];

  slice(&arr, &pointer, &arrSize, &ptrIndex, &left, &right); // Create the multidimentional array

  int sortedLeft[] = quicksort(left);
  int sortedRight[] = quicksort(right);
  
  int result[] = arrjoin(&sortedLeft, &pointer, &sortedRight, &arrSize); // concat the three arrays

  free(arr);
  return result;
}

// Function to slice arrays 
void slice(int* arr, int* ptr, int* length, int* ptrIndex, int* left, int* right){
  /*
  Args:
    Takes an array to split,
    a pointer, that is, the location the array should be split (the pointer is not included in the split arrays),
    a length, which is the length of the starting array,
    a ptrIndex, which is just the index in the array the pointer is,
    a reference to the left array split
    a reference to the right array split
  
  Function:
    Edits the two reference arrays such that left includes only left of the pointer, and right, only right
  */
  assert(left);
  assert(right);

  int passedPointer = 0;

  // Get the length of the array without the pointer
  length -= sizeOf(arr[0]);

  // Loop through array
  for (int i=0; i<*length; i++){
    // if location in array isn't pointer, and we haven't passed the pointer yet
    if (i != *ptrIndex && !passedPointer){
      left[i] = arr[i];
    }

    //  If we are at the pointer location
    else if (i == *ptrIndex){
      passedPointer = 1;
    }

    // if we have passed the pointer
    else if (i != *ptrIndex && passedPointer){
      right[i - *ptrIndex] = arr[i];
    }
    
    
  }
  // Free the memory pointers
  free(arr);
  free(ptr);
  free(length);
  free(ptrIndex);
  
}

// Function to join two given arrays by a pointer
int arrJoin(int* array1, int* lenArr1, int* pointer, int* array2, int* lenArr2){
  /*
  Args:
    Function takes two arrays, their relative lengths, and a pointer to join the arrays by.
  
  Return:
    Returns an int array of the joined arrays by the given pointer : input([1, 2], 3, [4, 5]) => [1, 2, 3, 4, 5]
  */

  // Create an index to keep track of where we are in the joined array
  int index = 0;

  // initialize an array with length of the sum of the arrays and 1 - so we include the pointer.
  int joinedArr[*lenArr1 + *lenArr2 + 1]; 

  // Loop through the first array and add then items to the joined array
  for (int i = 0; i < *lenArr1; i++){
    joinedArr[index] = array1[i];
    index++;
  }

  // Add the pointer to the 
  joinedArr[*lenArr1] = *pointer;
  index++;

  // Loop through the second array and add each item to the joined array
  for (int i = 0; i < *lenArr2; i++){
    joinedArr[index] = array2[i];
    index++;
  }
  
  //Free the memory pointers
  free(array1);
  free(pointer);
  free(array2);
  free(lenArr1);
  free(lenArr2);

  return joinedArr; // return the joined array
}
