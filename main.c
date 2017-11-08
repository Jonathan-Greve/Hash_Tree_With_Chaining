#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct bin{
    int key;
    int val;
    struct bin* successor;
};

void create_ht(struct bin*** hashtable, size_t size){
    *hashtable = (struct bin**)malloc(size * sizeof(struct bin*));
    for (int i = 0; i < size; i++){
        (*hashtable)[i] = NULL;
    }
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
    //MISSING: Search chained bins
    struct bin* tmp_item;
    struct bin* item = (*hashtable)[hash_ht(size, key)];
    if(item){
        while(item){
            tmp_item = item;
            printf("val_in_chain: %d", tmp_item->val);
            item = item->successor;
            puts("test");
        }
        puts("found!");
        return tmp_item->val;
    }
    return -2;
}

int main(int argc, char* argv[argc+1]){
    size_t size = 10;
    struct bin** hashtable = NULL;
    create_ht(&hashtable, size);

    int nums[3] = {3, -1, -2};
    int target = 2;
    for(int i = 0; i < 3; i++){
        insert_ht(&hashtable, nums[i], i, size);
    }
    for(int i = 0; i < 3; i++){
        printf("val: %d\n", search_ht(&hashtable, nums[i], size));
    }

    for(int i = 0; i < 3; i++){
        int remain_num = target - nums[i];
        if(hashtable[hash_ht(size, remain_num)] && hashtable[hash_ht(size, remain_num)]->val != i){
            printf("[%d, %d]\n", i, hashtable[hash_ht(size, remain_num)]->val);
            break; //otherwise it will find all combinations
        }
    }

    puts("Done");
}