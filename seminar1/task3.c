/* Пример создания нового процесса с разной работой процессов ребенка и родителя */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        //Ошибка 
        printf("Ошибка\n");
    } 
    else if (child_pid == 0)
    { 
        //Порожденный процесс
        pid_t pid = getpid();
        pid_t ppid = getppid();

        printf("pid = %d, ppid = %d, child_pid = %d\n", (int)pid, (int)ppid, (int)child_pid); 
    }
    else 
    {
        //Родительский процесс
        pid_t pid = getpid();
        pid_t ppid = getppid();

        printf("My pid = %d, my ppid = %d, child_pid = %d\n", (int)pid, (int)ppid, (int)child_pid); 
    }

    return 0;
}