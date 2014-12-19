/*************************************************************************
  > File Name: memory_pool.cpp
  > Author:Haoson 
  > Created Time: Thu 18 Dec 2014 07:26:08 PM PST
  > Description: 
 ************************************************************************/

#include<iostream>
#include<assert.h>
#include"memory_pool.h"
MemoryPool* MemoryPool::create(MemoryPool*& head,size_t alloc_size,size_t block_size){
    assert(alloc_size>0 && block_size>0);
    MemoryPool* p = reinterpret_cast<MemoryPool*>(new char[sizeof(MemoryPool)+alloc_size*block_size]);
    p->next = head;
    head = p;
    return p;
}

void MemoryPool::freeDataChain(){
    MemoryPool* p = this;
    MemoryPool* temp;
    while(p){
        temp = p->next;
        char* cptr = reinterpret_cast<char*>(p);
        delete[] cptr;
        p = temp;
    }
}
