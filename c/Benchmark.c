#include <stdio.h>// print results
#include <time.h>// measure execution time
#include "table.h"// access to initTable() and tableSet()
#include "value.h"// used to create number keys
void insertKeys(int testInput);//function declaration
void searchKeys(int testInput);
void DeleteKeys(int testInput);


int main(){
    printf(" insert keys results");
    printf("\n");
    insertKeys(10);
    insertKeys(100);
    insertKeys(1000);
    insertKeys(10000);
    insertKeys(100000);// call fuction
        printf("\n");
    printf("\n");



     printf(" deleted keys results");
            printf("\n");
            DeleteKeys(10);
            DeleteKeys(100);
            DeleteKeys(1000);
            DeleteKeys(10000);
            DeleteKeys(100000);
    printf("\n");


    printf(" search keys results");
    printf("\n");
    searchKeys(10);
    searchKeys(100);
    searchKeys(1000);
    searchKeys(10000);
    searchKeys(100000);

    return 0;


}
void insertKeys(int testInput){// user input to test inserted keys value
    Table Hashtable;// hash table variable
    initTable(&Hashtable);// & - address of operator

    clock_t startTime = clock();// start time to calculate total time
    for(int test = 1; test <= testInput; test++){// counter for number of keys inputted
        Value key = NUMBER_VAL(test);//key
        Value val = NUMBER_VAL(test);// value of key

        tableSet(&Hashtable, key, val);//inserting key and value into hash table
    }

    clock_t endTime = clock();// end time
    printf("Time for %d keys: %ld clock ticks\n", testInput  , (long)(endTime - startTime));// prints results

    freeTable(&Hashtable);

}
void searchKeys(int testInput){// user input to test time it takes to find keys
    Table Hashtable;// hash table variable
    initTable(&Hashtable);// & - address of operator
    // first for loop fills hash table with inserted keys
    for(int test = 1; test <= testInput; test++){// counter for number of keys inputted
        Value key = NUMBER_VAL(test);//key
        Value val = NUMBER_VAL(test);// value of key

        tableSet(&Hashtable, key, val);//inserting key and value into hash table
    }
    clock_t startTime = clock();// start time to calculate search

    //second for loop - searches for inserted keys and gets value
        for(int test = 1; test <= testInput; test++){// search for keys
            Value key = NUMBER_VAL(test);// creation of key to serach
            Value val;
            // uses the get - searches for key and gets value
            tableGet(&Hashtable, key, &val);// searches hash table for key and stores in val
        }

    clock_t endTime = clock();// end time
    printf("Time for searching the %d keys: %ld clock ticks\n", testInput  , (long)(endTime - startTime));// prints results

    freeTable(&Hashtable);
}

void DeleteKeys(int testInput){// user input to test time it takes to delete keys
    Table Hashtable;// hash table variable
    initTable(&Hashtable);// & - address of operator
    // first for loop fills hash table with inserted keys
    for(int test = 1; test <= testInput; test++){// counter for number of keys inputted
        Value key = NUMBER_VAL(test);//key
        Value val = NUMBER_VAL(test);// value of key

        tableSet(&Hashtable, key, val);//inserting key and value into hash table
    }
    clock_t startTime = clock();// start time to calculate deleting of keys

    //second for loop - searches for inserted keys and deletes key and value
        for(int test = 1; test <= testInput; test++){// loops through keys to delete them
            tableDelete(&Hashtable,NUMBER_VAL(test));// searches hash table for key and deletes key
        }

    clock_t endTime = clock();// end time
    printf("Time for deleting the %d keys: %ld clock ticks\n", testInput  , (long)(endTime - startTime));// prints results

    freeTable(&Hashtable);
}






