#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeSort (char array[], int, int, struct part *);
void merge(char array[], int low, int mid, int high, struct part *);

struct part
{
    int weight;
    int line;
    char batchCode[5];
    int targetEngineCode;
    int date;
};

void  generateRandomData(struct part *, struct part * , struct part * , struct part *);



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

    mergeSort(ids, 0, 11 , morningParts);

    for (int i = 0; i < 11; i++ ){
        printf("%d ", array[i]);
    }

    printf("\n");

    //printf("%d", count++);
    
    //printf("%d\n%d\n%s\n", morningParts[0].weight, morningParts[0].line, morningParts[0].batchCode);

}

void generateRandomData( 
                    struct part *morningParts, 
                    struct part *eveningParts, 
                    struct part *afternoonParts, 
                    struct part *nightParts
                )
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


// our function for merge sort will use id and do comparision based on weight
void mergeSort(char array[], int low, int high, struct part *parts)
{
    
    // comparison to check if we are at the single elements
    
    if (low < high){

        int mid = low + (high - low) / 2;

        // upper part breaking
        mergeSort(array,low, mid, parts);

        //lower part breaking
        mergeSort(array, mid + 1, high, parts);


        //merging them both together
        merge(array, low, mid, high,parts);
    };

}

void merge(char array[], int low, int mid, int high, struct part *parts){

    int i, j, k;
    int l = mid - low + 1;
    int r = high - mid;

    int left[l], right[r];

    // making two temp arrays of ids
    for (i = 0; i < l; i++)
    {
        left[i] = array[low + i];
    }
    for (j = 0 ; j < r ; j++)
    {
        right[j] = array[mid + 1 + j];
    }

    //main logic for merge

    i = 0;
    j = 0;
    k = low;


    // GOTTA WORK ON THIS PART
    
    // while(i < l && j < r)
    // {   
    //     // for loop to get the weight of the id
    //     for (int j = 0; j < 10; i++)
    //     {
    //         if (parts[j].batchCode == left[i]){
    //             int lWeight = parts[j].weight;
    //         }
    //         if (parts[j].batchCode == right[j]){}
    //     }
        
    //     if (left[i] <= right[j]){
    //         array[k] = left[i];
    //         i++;
    //     } else{
    //         array[k] = right[j];
    //         j++;
    //     }
    //     k++;
    // }

    //copying the leftovers
    while(i < l){
        array[k] = left[i];
        i++;
        k++;
    }

    // 
    while(i < r){
        array[k] = right[i];
        i++;
        k++;
    }

}
