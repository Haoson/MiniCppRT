/*************************************************************************
  > File Name: pool_allocator.cpp
  > Author:Haoson 
  > Created Time: Thu 18 Dec 2014 05:33:51 AM PST
  > Description: 
 ************************************************************************/

#include<iostream>
#include<assert.h>
#include"fixed_alloc.h"

FixedAlloc::FixedAlloc(size_t nAllocSize,size_t nBlockSize){
    assert(nAllocSize>=sizeof(Obj));
    assert(nBlockSize>1);
//alloc的自由链表的设计思想是借用对象的前4个字节(32位系统上)来作为next指针链接block，如果对象本身大小比4个字节还小，那么必须向上调整对象大小
    if(nAllocSize<sizeof(Obj))
        nAllocSize = sizeof(Obj);
    if(nBlockSize<=1)
        nBlockSize = 32;
    allocSize = nAllocSize;
    blockSize = nBlockSize;
    blocks_head = nullptr;
    free_block_head = nullptr;
}
FixedAlloc::~FixedAlloc(){
    deallocateAll();
}
void FixedAlloc::deallocateAll(){
    blocks_head->freeDataChain();
    blocks_head = nullptr;
    free_block_head = nullptr;
}
void FixedAlloc::deallocate(void* p){
    if(p){//归还的block入链
        Obj* objptr = static_cast<Obj*>(p);
        objptr->free_list_link = free_block_head;
        free_block_head = objptr;
    }
}
void* FixedAlloc::allocate(){
    if(!free_block_head){//内存池中没有未分配的block
        MemoryPool* p = MemoryPool::create(blocks_head,blockSize,allocSize); 
        Obj* objptr = static_cast<Obj*>(p->data());
        free_block_head = objptr;
        Obj* temp;
        for(size_t i=0;i!=blockSize-1;++i){//将所有block链起来
            temp = reinterpret_cast<Obj*>(reinterpret_cast<char*>(objptr)+allocSize);
            objptr->free_list_link =temp;
            objptr = temp;
        }
        objptr->free_list_link = nullptr;//最后一个block的指针指向nullptr
    }
    void* p = free_block_head;
    free_block_head = free_block_head->free_list_link;
    return p;
}
