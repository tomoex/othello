#include <stdlib.h>
#include <string.h>

#ifndef ARRAY_H_
#define ARRAY_H_

typedef struct {
    unsigned int length;
    unsigned int capacity;
    size_t size;
    void* data;
}Array;

void Array_new(Array* array, unsigned int length, size_t size){
    array->data = (void*)malloc(length * size);
    array->capacity = length;
    array->size = size;
    array->length = 0;
}

void Array_delete(Array* array){
    free(array->data);
    array->data = NULL;
    array->length = 0;
    array->size = 0;
    array->capacity = 0;
}

unsigned int Array_length(const Array* array){
    return array->length;
}

unsigned int Array_capacity(const Array* array){
    return array->capacity;
}


void* Array_get(Array* array, unsigned int index){
    return array->data + index * array->size;
}

void Array_append(Array* array, const void* value){
    // 追加後のlengthがcapacity以下のときだけ追加を行う
    if(array->length + 1 <= array->capacity){
        memcpy(array->data + array->length * array->size, value, array->size);
        array->length++;
    }
}

#endif
