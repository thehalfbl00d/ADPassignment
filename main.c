#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct part
{
    int weight;
    int line;
    char batchCode[5];
    int targetEngineCode;
    int date;
};
void generateRandomData(struct part *, struct part *, struct part *, struct part *);
void merge(int array[], int low, int mid, int high);
void mergeSort(int array[], int low, int high);


int main()
{
    // declaring different time parts
    struct part morningParts[10], eveningParts[10], afternoonParts[10], nightParts[10];

    //passing array to function
    printf("\nGenerating Random Data...\n");

    int startTime = clock();
    generateRandomData(morningParts, eveningParts, afternoonParts, nightParts);
    int endTime = clock();

    printf("Random Data Generation Complete! time taken : %d Milliseconds\n\n" ,(endTime - startTime));

    
    //copying ids into an array
    char *ids[10]; 
    for (int i = 0; i < 10; i++)
    {
        ids[i] = morningParts[i].batchCode;
    }

    int array[] = {1,4,3,2,6,4,2,7,1,2,3}; 


    for (int i = 0; i < 11; i++ ){
        printf("%d ", array[i]);
    }

    printf("\n");
}


void generateRandomData( struct part *morningParts, struct part *eveningParts, struct part *afternoonParts, struct part *nightParts)
{
    // seeding time
    srand(time(NULL));

    for (int i = 0; i < 10; i++)
    {   
        // generating numbers

        int m = rand();
        int e = rand();
        int n = rand();
        int a = rand();
        
        //generating random weight
        morningParts[i].weight = m % 10;
        eveningParts[i].weight = e % 10;
        nightParts[i].weight = n % 10;
        afternoonParts[i].weight = a % 10;

        //generatingrandomline
        morningParts[i].line = m % 4 + 1;
        eveningParts[i].line = n % 4 + 1;
        afternoonParts[i].line = a % 4 + 1;
        nightParts[i].line = n % 4 + 1;

        //generating random batchCode
        for (int k = 0; k < 10; k++)
        {   
            // generating character for ex, AB, FD
            for ( int j = 0; j < 2; j++ ){
                int w1 = rand();
                morningParts[k].batchCode[j] = 'A' + (w1) % 25;

                int j1 = rand();
                nightParts[k].batchCode[j] = 'A' + (j1) % 25;

                int k1 = rand();
                eveningParts[k].batchCode[j] = 'A' + (k1) % 25;

                int l1 = rand();
                afternoonParts[k].batchCode[j] = 'A' + (l1) % 25;
            }

            //num elements of batchCode ex 11, 12, 41
            for (int k = 2; k < 4 ; k++){
                int w2 = rand();
                morningParts[i].batchCode[k] = '0' + w2 % 10;
                int i2 = rand();
                nightParts[i].batchCode[k] = '0' + i2 % 10;
                int k2 = rand();
                afternoonParts[i].batchCode[k] = '0' + k2 % 10;
                int l2 = rand();
                eveningParts[i].batchCode[k] = '0' + l2 % 10;
            }

            // generating target engineCode
            for (int t = 0; t < 4; t++)
            {
                morningParts[t].targetEngineCode = m * n;
                eveningParts[t].targetEngineCode = n * e;
                afternoonParts[t].targetEngineCode = m * e;
                nightParts[t].targetEngineCode = a * e;
            }

        }
    } 
}

void merge(int array[], int low, int mid, int high) {
    int i, j, k;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    int left[leftSize], right[rightSize];

    for (i = 0; i < leftSize; i++) {
        left[i] = array[low + i];
    }
    for (j = 0; j < rightSize; j++) {
        right[j] = array[mid + 1 + j];
    }

    i = 0;
    j = 0;
    k = low;

    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        } else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < leftSize) {
        array[k] = left[i];
        i++;
        k++;
    }

    while (j < rightSize) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int array[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(array, low, mid);
        mergeSort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}