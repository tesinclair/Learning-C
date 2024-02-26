#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

void sliceSort(int *arr, int ptr, int length, int *left, int *right);
int *arrJoin(int *array1, int lenArr1, int pivot, int *array2, int lenArr2);
int quickSort(int *arr, int arrSize, int *sortedArr);

int main(){
  int arr[] = {2, 4, 3, 7, 5, 19, 20, 32, 45, 12, 31, 1};

  int arrSize = sizeof(arr)/sizeof(arr[0]);

  int *sortedArr = malloc(sizeof(arr));
  quickSort(arr, arrSize, sortedArr);

  for(int i=0; i<arrSize; i++){
    printf("%d\n", sortedArr[i]);
  }

  free(sortedArr);
  return 0;
}

int quickSort(int *arr, int arrSize, int *sortedArr){
  // If the array only has one value, return the array
  if(arrSize == 1){
    sortedArr[0] = arr[0];
    return 1;
  }

  else if (arrSize <= 0){
    return 1;
  }
  // If the array only has two values
  else if(arrSize == 2){

    // If the first element is lager than the second, swap them
    if (arr[0] > arr[1]){
      sortedArr[0] = arr[1];
      sortedArr[1] = arr[0];
      return 1;
    }
    // If the second element is larger than the first, return the arr (as it is ordered already)
    else{
      sortedArr[0] = arr[0];
      sortedArr[1] = arr[1];
      return 1;
    }
  }
  // Set the pivot as the median val in arr
  int largestInArr = 0;
  for (int i = 0; i<arrSize-1; i++){
    // If the current element is larger than the next, and the value in largestIntArr. Or it is the last element in the array
    if ((arr[i] > arr[i+1] && arr[i] > largestInArr) || i+1 == arrSize){
      largestInArr = arr[i];
    }
  }
  // Make pivot the value closest to the middle of array
  int pivot = arr[0];

  // Mid value
  int mid = largestInArr / 2;

  for (int i = 1; i<arrSize; i++){
    // Check if the current value is closer to the mid value than the current pivot
    if (abs(arr[i] - mid) < abs(pivot - mid)){
      pivot = arr[i];
    }
  }

  // Get sizes of both arrays
  int lenLeft = 0;
  int lenRight = 0;
//  printf("%d\n", lenLeft);
  // Loop through array and increase the value of left and right size relaive to the size of value
  for (int i = 0; i<arrSize; i++){
    if (arr[i] < pivot){
      lenLeft++;
    }else if (arr[i] > pivot){
      lenRight++;
    }else{
      continue;
    }
  }
  int *left = malloc(lenLeft * sizeof(int));
  int *right = malloc(lenRight * sizeof(int));
  // Create the multidimentional array
  sliceSort(arr, pivot, arrSize, left, right);

  quickSort(left, lenLeft, left);
  quickSort(right, lenRight, right);
  
  // concat the three arrays
  int *result = arrJoin(left, lenLeft, pivot, right, lenRight);
  assert(result);
  for(int i=0; i<arrSize; i++){
    sortedArr[i] = result[i];
  }

  free(left);
  free(result);
  free(right);
  return 1;
}


// Function to slice arrays 
void sliceSort(int *arr, int ptr, int length, int *left, int *right){
  /*
  Args:
    Takes an array - To split
    a pivot - for the comparison
    an array length - for the looping
    a left array - reference to the array which should be joined on the left
    a right array - reference to the array whihh should be joined on the right
  
  Function:
    loops through the first array and stores all values smaller than the pivot inside the left array, and all values larger in the right array.
    NOTE: Does not return the pivot, that is, the pivot is not returned in either array
  */

  // Store the current index for each array
  int leftIndex = 0;
  int rightIndex = 0;

  // Loop through array
  for (int i=0; i<length; i++){
      // If value is smaller, add to the left array
      if (arr[i] < ptr){
        left[leftIndex] = arr[i];
        leftIndex++;
      // If value is larger add to the right array
      }else if(arr[i] > ptr){
        right[rightIndex] = arr[i];
        rightIndex++;
      }else{ //If the current is the pivot, move to the nect iteration
        continue;
      }
  }
}
//TODO: Fix implementation
// Function to join two given arrays by a pivot
int *arrJoin(int *array1, int lenArr1, int pivot, int *array2, int lenArr2){
  /*
  Args:
    Function takes two arrays, their relative lengths, and a pivot to join the arrays by.
  
  Return:
    Returns an int array of the joined arrays by the given pivot : input([1, 2], 3, [4, 5]) => [1, 2, 3, 4, 5]
  */

  // Create an index to keep track of where we are in the joined array
  int index = 0;

  // initialize an array with length of the sum of the arrays and 1 - so we include the pivot.
  int *joinedArr = malloc(lenArr1 + lenArr2 + 1); 

  // Loop through the first array and add then items to the joined array
  for (int i = 0; i < lenArr1; i++){
    joinedArr[index] = array1[i];
    index++;
  }

  // Add the pivot to the joined array
  joinedArr[lenArr1] = pivot;
  index++;

  // Loop through the second array and add each item to the joined array
  for (int i = 0; i < lenArr2; i++){
    joinedArr[index] = array2[i];
    index++;
  }

  return joinedArr; // return the joined array
}
