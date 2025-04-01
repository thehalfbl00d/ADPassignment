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

#define Morning 10
#define Afternoon 10
#define Evening 10
#define Night 10

void generateRandomData(struct part *, int);
void merge(char *array[], int low, int mid, int high, struct part *parts, int) ;
void mergeSort(char *array[], int low, int high, struct part *parts, int);
int findWeight(char *id, struct part *parts, int );


int main()
{   
    // seeding time
    srand(time(NULL));
    
    // declaring different time parts
    struct part morningParts[Morning], eveningParts[Evening], afternoonParts[Afternoon], nightParts[Night];
    struct part all[Morning + Afternoon + Evening + Night];

    //generating random data
    generateRandomData(morningParts, Morning);
    generateRandomData(afternoonParts, Afternoon);
    generateRandomData(eveningParts, Evening);
    generateRandomData(nightParts, Night);

    // making one big id of everything ( works till here) + making a new big struct of all data
    char *allids[Morning + Afternoon + Evening + Night];
    for(int i = 0; i < Morning + Afternoon + Evening + Night; i++)
    {
        if (i < Morning)
        {
            allids[i] = morningParts[i].batchCode;
            strcpy(all[i].batchCode,morningParts[i].batchCode);
            all[i].weight = morningParts[i].weight;
            all[i].line = morningParts[i].line;
            all[i].targetEngineCode =  morningParts[i].targetEngineCode;
        } 
        else if (Morning <= i && i < (Afternoon + Morning))
        {
            allids[i] = afternoonParts[i - Morning].batchCode;
            strcpy(all[i].batchCode,afternoonParts[i - Morning].batchCode);
            all[i].weight = afternoonParts[i - Morning].weight;
            all[i].line = afternoonParts[i - Morning].line;
            all[i].targetEngineCode =  afternoonParts[i - Morning].targetEngineCode;
        }
        else if ((Afternoon + Morning) <= i && i < (Evening + Afternoon + Morning))
        {
            allids[i] = eveningParts[i - (Morning + Afternoon)].batchCode;
            strcpy(all[i].batchCode,eveningParts[i - (Morning + Afternoon)].batchCode);
            all[i].weight = eveningParts[i - (Morning + Afternoon)].weight;
            all[i].line = eveningParts[i - (Morning + Afternoon)].line;
            all[i].targetEngineCode =  eveningParts[i - (Morning + Afternoon)].targetEngineCode;
        }
        else if ((Evening + Afternoon + Morning) <= i && i < (Night + Morning+ Afternoon + Evening))
        {
            allids[i] = nightParts[i - (Morning + Afternoon + Evening)].batchCode;
            strcpy(all[i].batchCode,nightParts[i - (Morning + Afternoon + Evening)].batchCode);
            all[i].weight = nightParts[i - (Morning + Afternoon + Evening)].weight;
            all[i].line = nightParts[i - (Morning + Afternoon + Evening)].line;
            all[i].targetEngineCode =  nightParts[i - (Morning + Afternoon + Evening)].targetEngineCode;
        }
    }

    

    printf("All ids:  ");

    for(int i = 0; i < Morning + Afternoon + Evening + Night; i++)
    {
        printf("%s ",all[i].batchCode);
    }

    printf("\nAll weight:  ");

    for(int i = 0; i < Morning + Afternoon + Evening + Night; i++)
    {
        printf("%d ",all[i].weight);
    }

    printf("\nSorted Batch Code: ");
    mergeSort(allids,0,Morning + Afternoon + Evening + Night - 1,all, Morning + Afternoon + Evening + Night);
    for(int i = 0; i < Morning + Afternoon + Evening + Night; i++)
    {
        printf("%s ",allids[i]);
    }

    printf("\nSorted weight:  ");

    for(int i = 0; i < Morning + Afternoon + Evening + Night; i++)
    {
        printf("%d ",findWeight(allids[i], all, Morning + Afternoon + Evening + Night));
    }
};

void generateRandomData( struct part *Parts, int len)
{
    

    for (int i = 0; i < len; i++)
    {   
        // generating numbers

        int m = rand();
        int e = rand();
        int n = rand();
        int a = rand();
        
        //generating random weight
        Parts[i].weight = m % 10;

        //generatingrandomline
        Parts[i].line = m % 4 + 1;
        

        //generating random batchCode
         
        // generating character for ex, AB, FD
        for ( int j = 0; j < 2; j++ ){
            int w1 = rand();
            Parts[i].batchCode[j] = 'A' + (w1) % 25;
        }

        //num elements of batchCode ex 11, 12, 41
        for (int k = 2; k < 4 ; k++){
            int w2 = rand();
            Parts[i].batchCode[k] = '0' + w2 % 10;
            Parts[i].batchCode[4] = '\0';
        }


        // generating target engineCode
        for (int t = 0; t < 4; t++)
        {
            Parts[t].targetEngineCode = m * n;
        }

        
        
    } 
}

void merge(char *array[], int low, int mid, int high, struct part *parts, int len) 
{
    int i, j, k;
    int leftSize = mid - low + 1;
    int rightSize = high - mid;

    char *left[leftSize], *right[rightSize];

    for (i = 0; i < leftSize; i++) 
    {
        left[i] = array[low + i];
    }
    for (j = 0; j < rightSize; j++) {
        right[j] = array[mid + 1 + j];
    }


    i = 0;
    j = 0;
    k = low;

    
   while (i < leftSize && j < rightSize){
    if (findWeight(left[i],parts,len) <= findWeight(right[j], parts,len)){
        array[k] = left[i];
        i++;
    } else{
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

void mergeSort(char *array[], int low, int high, struct part *parts, int len) 
{
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(array, low, mid, parts, len);
        mergeSort(array, mid + 1, high, parts, len);
        merge(array, low, mid, high, parts, len);
    }
}



int findWeight(char *id, struct part *parts, int len )
{
    for (int i = 0; i < len; i++)
    {
        if((strcmp(parts[i].batchCode, id) == 0))
        {   
            return parts[i].weight;
        }
    }

    return 0;
}

