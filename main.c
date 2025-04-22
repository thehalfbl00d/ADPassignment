/*
Description:    This code generated random data, throws it into struct, 
                then uses a modded version of mergesort to sort, 
                which does comparisons based on weights and arrange the ids in an array based on that,
                now we are finished sorting,
                to print weights, we use a function which basically goes to the struct and asks for the weight of the id,
                so now we are making a new array of weight based on this sorted ids array,
                then we use quick sort for finding weight in the whole meatball of all weights,
                then we break down all of the weights into 4 vans.
                I will try to use dma for structs but if you still see this comment, i failed.
Author: Akshat Pasbola (D24126231)
Date: idk
*/


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

#define Morning 15
#define Afternoon 12
#define Evening 30
#define Night 20

void generateRandomData(struct part *, int);
void merge(char *array[], int low, int mid, int high, struct part *parts, int);
void mergeSort(char *array[], int low, int high, struct part *parts, int);
int findWeight(char *id, struct part *parts, int );
int binarySearch(char *ids[], int find, int low, int high, struct part *all);


int main()
{   

    // seeding time
    srand(time(NULL));

    //variables
    int allIDCount = Morning + Afternoon + Evening + Night;
    
    // declaring different time parts
    struct part morningParts[Morning], eveningParts[Evening], afternoonParts[Afternoon], nightParts[Night];
    struct part all[allIDCount];

    //generating random data
    generateRandomData(morningParts, Morning);
    generateRandomData(afternoonParts, Afternoon);
    generateRandomData(eveningParts, Evening);
    generateRandomData(nightParts, Night);

    // making one big id of everything ( works till here) + making a new big struct of all data
    char *allids[allIDCount];
    for(int i = 0; i < allIDCount; i++)
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
        else if ((Evening + Afternoon + Morning) <= i && i < (allIDCount))
        {
            allids[i] = nightParts[i - (allIDCount - Night)].batchCode;
            strcpy(all[i].batchCode,nightParts[i - (allIDCount - Night)].batchCode);
            all[i].weight = nightParts[i - (allIDCount - Night)].weight;
            all[i].line = nightParts[i - (allIDCount - Night)].line;
            all[i].targetEngineCode =  nightParts[i - (allIDCount - Night)].targetEngineCode;
        }
    }
    
    
    // printing all ids
    printf("\n%19s",":   All IDS   :  \n\n");
    for(int i = 0; i < allIDCount; i++)
    {
        printf("%s ",all[i].batchCode);
    }
    printf("\n");

    //printing all weight
    printf("\n%20s",":   All Weights   :  \n\n");
    for(int i = 0; i < allIDCount; i++)
    {
        printf("%d ",all[i].weight);
    }
    printf("\n");

    
    
    //sorting weights
    //allids is an array of pointers, i.e. why we didnt pass it as address
    mergeSort(allids,0,allIDCount - 1,all, allIDCount);

    //TASK 2
    printf("\n\n:<------TASK 1------>:\n\n");
    for (int i = 0; i < allIDCount; i++)
    {
        if (i < Morning)
        {
            if (i == 0){
                printf("\nMorning IDS: \n");
            }
            printf("%s ", allids[i]);
        } 
        else if (Morning <= i && i < (Afternoon + Morning))
        {
            if (i == Morning){
                printf("\n\nAfternoon IDS: \n");
            }
            printf("%s ", allids[i]); 
        }
        else if ((Afternoon + Morning) <= i && i < (allIDCount - Night))
        {
            if (i == (Afternoon + Morning))
            {
                printf("\n\nEvening IDS: \n");
            }
            printf("%s ", allids[i]);
        }
        else if ((allIDCount - Night) <= i && i < (allIDCount))
        {
            if (i == (Evening + Afternoon + Morning)){
                printf("\n\nNight IDS: \n");
            }
            printf("%s ", allids[i]);
        }
    }


    // TASK 2 START //
    printf("\n\n:<------TASK 2------>:\n\n");
    //printing all sorted batch
    printf("\n:     Sorted Batch Code     : \n\n");
    for(int i = 0; i < allIDCount; i++)
    {
        printf("%s ",allids[i]);
    }
    printf("\n");

    //printing sorted weights
    printf("\n:     Sorted weight     :  \n\n");
    for(int i = 0; i <allIDCount; i++)
    {
        printf("%d ",findWeight(allids[i], all,allIDCount));
    }

    // TASK 2 END //
    // TASK 3 STARTS //
    printf("\n\n:<------TASK 3------>:");
    // making a menu for looking
    int inMenu = 1;
    while(inMenu)
    {   
        int option;
        printf("\n\nNumber looking for\nPress -1 to exit : ");
        scanf("%d", &option);

        if (option == -1)
        {
            inMenu = 0;
        } 
        else
        {
            binarySearch(allids,option,0,allIDCount, all);
        }
    }

    //printing vans allocation

    printf("\n\n<-----TASK 4----->");
    printf("\n\n<-----VAN ALLOCATION----->"); 
    int numberofvans = 4;
    int products_in_each_van = allIDCount / 4;
    int extras = allIDCount % 4;
    int van = 0;

    for (int i = 0 ; i < allIDCount; i++)
    {   
        if(i % (products_in_each_van + 1) == 0)
        {
            printf("\nVan %d: ", van+=1);
        }
        printf("%s ", allids[i]);

    }


    printf("\n\n");

    printf("\nThanks for using my Software\n");
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
        Parts[i].weight = m % 1000;

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

int binarySearch(char *ids[], int find, int low, int high, struct part *all)
{   
    if (low < high)
    {   
        int mid = low + (high - low)/2;
        int midWeight = findWeight(ids[mid], all, Afternoon + Morning + Evening + Night);

        if ( midWeight == find)
        {   
            int weight = findWeight(ids[mid], all, Afternoon + Morning + Evening + Night);
            int i = 0;
            while(weight == findWeight(ids[mid - i], all, Afternoon + Morning + Evening + Night) && ((mid - i) >=0 ))
            {   
                mid = mid - i;
                i++;
            }; 
            
            printf("%d found at id %s, at index: %d", midWeight, ids[mid], mid + 1);
            return mid;
        } 
        else if (midWeight > find)
        {   
            high = mid - 1;
            return binarySearch(ids,find,low, mid - 1 , all);
        }
        
        return binarySearch(ids, find, mid + 1, high, all);  // Search right
    } 
    else
    {
        printf("\nNumber not found!\n");
        return -1;
    }
}
