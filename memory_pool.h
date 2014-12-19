/*************************************************************************
  > File Name: memory_pool.h
  > Author:Haoson 
  > Created Time: Thu 18 Dec 2014 07:13:49 PM PST
  > Description: 内存分配器辅助类 
 ************************************************************************/

#ifndef MEMORY_POOL_H_
#define MEMORY_POOL_H_
#include<cstddef>
struct MemoryPool{
    MemoryPool* next;
    void* data(){
        return this+1;
    }
    static MemoryPool* create(MemoryPool*& head,size_t alloc_size,size_t block_size);
    void freeDataChain();
};
#endif
