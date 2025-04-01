#include <stdio.h>
int binarySearch(int [], int, int, int);
int main(){
    int array[6] = {1,2,3,4,4,5};

    if ((binarySearch(array, 4, 0, 6)) != -1)
    {
        printf("%d", binarySearch(array, 4, 0, 5));
    } 
    else
    {
        printf("Not Found");
    }

}

int binarySearch(int array[], int find, int low, int high)
{   
    if (low > high){
        return -1;
    }

    int mid = low + (high - low)/2;
    if (array[mid] == find)
    {   
        return mid;
    } 
    if(array[mid] > find)
    {   
        high = mid - 1;
        return binarySearch(array,find,low, high);
    }
    
    return binarySearch(array, find, mid + 1, high);  // Search right
}