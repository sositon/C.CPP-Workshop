#include <stdlib.h>
#include <stdio.h>
#include "ex2.h"
//#include "test_ex2.c"

#define DOUBLE_2_FORMAT "%.2lf"
#define ARGC_ERROR_MSG "ERROR: Wrong number of arguments.\nUsage: main <path to file>\n"

/**
 * main to run functions from Ex2
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
        {
            fprintf(stderr, ARGC_ERROR_MSG);
            return EXIT_FAILURE;  // EXIT_FAILURE is a macro for 1. Only to be used as return value from main or
            // parameter to exit()! Don't use it to replace 1 in function return value etc.
        }
    LinkedList *list = parse_linked_list(argv[1]);
    size_t n = 0; // will contain the number of elements in the returned array after call to getAverage(list,&n)
    Node *node = calloc(1, sizeof(Node));
    add_to_start_linked_list(list, node);

    double *average_list = get_averages(list, &n);
    printf("Average:\n");
    for (size_t i = 0; i < n; ++i)
        {
            printf(DOUBLE_2_FORMAT, average_list[i]);
            if (i != n - 1)
                {
                    printf(", ");
                }
        }
    printf("\n");
    free(average_list);
    free_linked_list(list); // not setting to NULL as the program is terminated after the free
    list = NULL;
    return EXIT_SUCCESS; // macro for 0. Like EXIT_FAILURE, not to be used for function return values!!
}
