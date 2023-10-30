# Семинар 1

## Задание 1

Первое задание направление на изучение аргументов командной строки.

Рассмторим программу, написанную ниже:
```C++
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[], char *envp[])
{
    for (int i = 0; envp[i] != NULL; i++) 
    {
        printf("envp[%d]: %s\n", i, envp[i]);
    }
    for (int i = 0; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
} 
```