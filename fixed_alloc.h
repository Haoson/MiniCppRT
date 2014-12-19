/*************************************************************************
  > File Name: fixed_alloc.h
  > Author:Haoson 
  > Created Time: Thu 18 Dec 2014 05:30:39 AM PST
  > Description: 固定大小的内存分配器 
 ************************************************************************/

#ifndef FIXED_ALLOC_H_
#define FIXED_ALLOC_H_
#include<cstddef>
#include"memory_pool.h"
class FixedAlloc{
    public:
        FixedAlloc(size_t nAllocSize,size_t nBlockSize=32);
        size_t getAllocSize(){
            return allocSize;
        }
        void* allocate();//分配allocSize大小的块
        void deallocate(void* p);//回收alloc出去的内存
        void deallocateAll();//回收所有从这个alloc分配出去的内存
        ~FixedAlloc();

    protected:
        union Obj{
            union Obj* free_list_link;
        };
        size_t allocSize;//分配块的大小
        size_t blockSize;//每次申请的块的数目
        MemoryPool* blocks_head;//所有区块组成的自由链表头
        Obj* free_block_head;//未分配出去的区块头
};
#endif
