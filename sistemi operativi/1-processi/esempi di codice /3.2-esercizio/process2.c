#include <stdio.h>
#include <unistd.h>

int main()
{
    fork(); // 2^1 = 2 processi (padre + figlio)

    fork(); // 2^2 = 4 processi
            // Entrambi i processi precedenti eseguono fork()

    fork(); // 2^3 = 8 processi
            // Tutti e 4 i processi precedenti eseguono fork()


    return 0;
}

