#include "Allocate.h"
struct memChunk{
    size_t size;
    void *address;

    memChunk(size_t size, void *address):size(size), address(address){}

    const bool operator==(const struct memChunk& other) const
    {
        bool isEqual = false;
         if (other.size == size && other.address == address) {
             isEqual = true;
         }

         return isEqual;
    }
    void print() {
        std::cout << "Size of Chunk: " << size << std::endl;
        std::cout << "Address of Chunk: " << address << std::endl;
    }
};

std::list <memChunk> allocatedChunks;
std::list <memChunk> freeChunks;

void *alloc(size_t chunk_size){
    void *startChunkAddress = nullptr;
    if (freeChunks.size() == 0){
        startChunkAddress = sbrk(0);
        sbrk(chunk_size);
        allocatedChunks.push_back(memChunk(chunk_size, startChunkAddress));
    }
    else if (allocationStrategy == "firstfit"){
        char *freeChunkAddress = nullptr;
        size_t freeSize = 0;
        for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
            if (it->size >= chunk_size){
                allocatedChunks.push_back(memChunk(chunk_size, it->address));
                startChunkAddress = it->address;
                freeChunkAddress = ((char *)it->address) + chunk_size;
                freeSize = it->size - chunk_size;
                it = freeChunks.erase(it);
            }
        }
        if (freeSize > 0){
            freeChunks.push_back(memChunk(freeSize, freeChunkAddress));
        }
    }

    else if (allocationStrategy == "bestfit"){
        char *closestAddress = nullptr;
        size_t closestSize = 0;
        /* Set the closest Size to the biggest possible free chunk size */
        for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
            if (it->size > closestSize){
                closestSize = it->size;
            }
        }
        /* Get the closest chunk size */
        for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
            long diff = it->size - chunk_size;
            if (diff >=0){
                if ((size_t)diff < closestSize){
                    closestSize = (size_t)diff;
                    closestAddress = (char *)it->address;
                }
            }
        }
        freeChunks.remove(memChunk(closestSize,closestAddress));
        allocatedChunks.push_back(memChunk(chunk_size, closestAddress));
        size_t freeSize = closestSize - chunk_size;
        char *freeChunkAddress = closestAddress + chunk_size;
        if (freeSize > 0){
            freeChunks.push_back(memChunk(freeSize, freeChunkAddress));
        }
        startChunkAddress = closestAddress;
    }

    else if (allocationStrategy == "worstfit"){
        char *biggestAddress = nullptr;
        size_t biggestSize = 0;
        for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
            if (it->size > biggestSize){
                biggestSize = it->size;
            }
            if (it->address > biggestAddress){
                biggestAddress = (char *)it->address;
            }
        }
        freeChunks.remove(memChunk(biggestSize,biggestAddress));
        allocatedChunks.push_back(memChunk(chunk_size, biggestAddress));
        size_t freeSize = biggestSize - chunk_size;
        char *freeChunkAddress = biggestAddress + chunk_size;
        if (freeSize > 0){
            freeChunks.push_back(memChunk(freeSize, freeChunkAddress));
        }
        startChunkAddress = biggestAddress;

    }

    std::cout << "---AllocatedChunks-----: " << std::endl;
    for (std::list<memChunk>::iterator it = allocatedChunks.begin(); it != allocatedChunks.end(); ++it){
        it->print();
    }  
    std::cout << "---FreeChunks-----: " << std::endl;
    for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
        it->print();
    }  
    return startChunkAddress;
}

void dealloc(void *chunk){
    /* Set the deallocated pointer value to NUL 
    size_t *chunkVal = (size_t*)chunk;
    *chunkVal = '\0'; 
    */
    size_t freeSize;
    for (std::list<memChunk>::iterator it = allocatedChunks.begin(); it != allocatedChunks.end(); ++it){
        if (chunk == it->address){
            freeSize = it->size;
            it = allocatedChunks.erase(it);
        }
    }
    freeChunks.push_back(memChunk(freeSize, chunk));
    std::cout << "---AllocatedChunks-----: " << std::endl;
    for (std::list<memChunk>::iterator it = allocatedChunks.begin(); it != allocatedChunks.end(); ++it){
        it->print();
    }  
    std::cout << "---FreeChunks-----: " << std::endl;
    for (std::list<memChunk>::iterator it = freeChunks.begin(); it != freeChunks.end(); ++it){
        it->print();
    }  
}