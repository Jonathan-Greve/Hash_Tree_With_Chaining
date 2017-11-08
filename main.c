#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct bin{
    int key;
    int val;
    struct bin* successor;
};

void create_ht(struct bin*** hashtable, size_t size){
    *hashtable = (struct bin**)calloc(size, sizeof(struct bin**));
}

int hash_ht(size_t size, int key){
    return abs(floor(size * fmod(key * 0.61803398987, 1)));
}

void insert_ht(struct bin*** hashtable, int key, int val, size_t size){
    //When the bin is empty
    if(!(*hashtable)[hash_ht(size, key)]){
        struct bin* item = (struct bin*)malloc(sizeof(struct bin));
        item->key = key;
        item->val = val;
        item->successor = NULL;
        (*hashtable)[hash_ht(size, key)] = item;
        return;
    }
    //Else find the correct position in the chain to insert
    struct bin* item = (*hashtable)[hash_ht(size, key)];
    struct bin* tmp_item;
    while(item && item->key != key){
        tmp_item = item;
        item = item->successor;
    }
    if(item->key != key){
        item = (struct bin*)malloc(sizeof(struct bin));
        tmp_item->successor = item;
        item->key = key;
        item->val = val;
        item->successor = NULL;
        return;
    }
    item->val = val;
}

int search_ht(struct bin*** hashtable, int key, size_t size){
    struct bin* tmp_item;
    struct bin* item = (*hashtable)[hash_ht(size, key)];
    if(item){
        while(item){
            tmp_item = item;
            printf("val_in_chain: %d\n", tmp_item->val);
            item = item->successor;
        }
        return tmp_item->val;
    }
    return 0;
}

int main(int argc, char* argv[argc+1]){
    size_t size = 100;
    struct bin** hashtable = NULL;
    create_ht(&hashtable, size);

    //Two sums problem on leetcode.com
    int numsSize = 4;
    int nums[4] = {0,4,3,0};
    int target = 0;
    for(int i = 0; i < numsSize; i+=2){
        if(hashtable[hash_ht(size, nums[i])]){
            printf("[%d, %d]\n", i, hashtable[hash_ht(size, nums[i])]->val);
            break;
        }
        insert_ht(&hashtable, target - nums[i], i, size);
        if(hashtable[hash_ht(size, nums[i+1])]){
            printf("[%d, %d]\n", i+1, hashtable[hash_ht(size, nums[i+1])]->val);
            break;
        }
        insert_ht(&hashtable, target - nums[i+1], i+1, size);
    }

    //Testing search
    // for(int i = 0; i < numsSize; i++){
    //     printf("val: %d\n", search_ht(&hashtable, nums[i], size));
    // }

    puts("Done");
}