#include <stdio.h>
#include <time.h>

int main(void)
{
    printf("O tamanho de time_t é %zu bytes\n", sizeof(time_t));
    printf("O tamanho de long int é %zu bytes\n", sizeof(long int));
    return 0;
}
