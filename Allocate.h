#include <iostream>
#include <list>
#include <string.h>
#include <unistd.h>

extern std::string allocationStrategy;
void *alloc(size_t chunk_size);
void dealloc(void *chunk);

