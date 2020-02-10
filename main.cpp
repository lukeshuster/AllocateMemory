#include "Allocate.h"
#define EXIT_SUCCESS    0

std::string allocationStrategy;
int main(int argc, char *argv[]) {
    /* ./allocate -s <firstfit, bestfit or worstfit> */
    if(argc == 3){
        if (strcmp( argv[1], "-s") == 0){
            if((strcmp( argv[2], "firstfit") == 0) || (strcmp( argv[2], "bestfit") == 0) || (strcmp( argv[2], "worstfit") == 0)){
                /* firstfit code */
                if (strcmp( argv[2], "firstfit") == 0){
                    allocationStrategy = "firstfit";
                }

                /* bestfit code */
                else if (strcmp( argv[2], "bestfit") == 0){
                    allocationStrategy = "bestfit";
                }

                /* worstfit code */
                else{
                    allocationStrategy = "worstfit";
                }

                // RUN TESTS
                // allocator->allocate()
                int *ptr = (int*)alloc(sizeof(int));
                *ptr = 7;
                std::cout << "-------------"<< std::endl;
                int *ptr2 = (int*)alloc(sizeof(int));
                *ptr2 = 500;
                std::cout << "-------------"<< std::endl;
                char *ptr3 = (char*)alloc(sizeof(char));
                *ptr3 = 'f';
                std::cout << "-------------"<< std::endl;
                int *ptr4 = (int*)alloc(sizeof(int));
                *ptr4 = 29;
                std::cout << "Allocated Val: " << *ptr << std::endl;
                std::cout << "Allocated Val: " << *ptr2 << std::endl;
                std::cout << "Allocated Val: " << *ptr3 << std::endl;
                std::cout << "Allocated Val: " << *ptr4 << std::endl;
                std::cout << "------Dealloc 2-------"<< std::endl;    
                dealloc(ptr2);
                std::cout << "------ New Alloc-------"<< std::endl;
                char *ptr5 = (char*)alloc(sizeof(char));
                *ptr5 = 'D';
                std::cout << "Allocated Val: " << *ptr << std::endl;
                std::cout << "Allocated Val: " << *ptr5 << std::endl;
                std::cout << "Allocated Val: " << *ptr3 << std::endl;
                std::cout << "Allocated Val: " << *ptr4 << std::endl;         

            }
            else{
                std::cerr << "Invalid memory strategy - try <firstfit, bestfit or worstfit>" << std::endl;
            }
        }
        else{
            std::cerr << "Invalid command, try <-s>" << std::endl;
        }
    }

    else{
        std::cerr << "Invalid arguments, try <-s> <firstfit, bestfit or worstfit>" << std::endl;
    }

    return EXIT_SUCCESS;
}
