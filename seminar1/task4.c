/* Пример программы для изменения пользовательского контекста (запуска новой программы) в порожденном процессе. */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[], char *envp[])
{
    pid_t child_pid = fork();
 
    if (child_pid < 0)
    { 
        // Ошибка
        printf("Can\'t fork a child process\n"); 
    } 
    else if (child_pid > 0)
    {
        // Родительский процесс
        pid_t pid = getpid();
        pid_t ppid = getppid();

        printf("pid = %d, ppid = %d, child_pid = %d\n\n", (int)pid, (int)ppid, (int)child_pid); 
    } 
    else 
    {
        /* Порожденный процесс */
 
        /* Мы будем запускать команду cat c аргументом командной строки без изменения параметров среды,
        т.е. фактически выполнять команду "cat имя файла", которая должна выдать содержимое данного файла на экран.
        Для функции execle в качестве имени программы мы указываем ее полное имя с путем от корневой директории.
        Первое слово в командной строке у нас должно совпадать с именем запускаемой программы. 
        Второе слово в командной строке - это имя файла, содержимое которого мы хотим распечатать.*/

        int result = execle("/bin/cat", "/bin/cat", "seminar1/task4.cpp", 0, envp);

        if (result < 0)
        {
            // Если возникла ошибка, то попадаем сюда
            printf("Error on program start\n");
            exit(-1);
        }
    }

    return 0;
}
