/* Программа, иллюстрирующая использование системных вызовов open(), read() и close() для чтения информации из файла */

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

/* Должно быть два аргумента командной строки:
   1) Имя исходного файла
   2) Имя файла в который копируется текст 
*/
int main(int argc, char *argv[], char *envp[])
{
    /* Попытаемся открыть файл с именем в первом параметре вызова только
    для операций чтения */
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0)
    {
        /* Если файл открыть не удалось, печатаем об этом сообщение и прекращаем работу */
        printf("Can\'t open file\n");
        exit(-1);
    }

    /* Читаем файл пока не кончится и печатаем */
    size_t size = 0;
    char string[60] = {0};

    while ((size = read(fd, string, 60)))
    {
        printf("%s\n", string); /* Печатаем прочитанное*/
        for (int i = 0; i < 60; i++) 
        {
            string[i++] = '\0'; // очищаем строку
        } 
    }

    /*  Записываем файл под новым именем */
    int result = execle("/bin/cp", "/bin/cp", argv[1], argv[2], 0, envp);
    if (result < 0)
    {
      /* Если возникла ошибка, то попадаем сюда*/
      printf("Error on copying file\n");
      exit(-1);
    }

    /* Закрываем файл */
    if(close(fd) < 0)
    {
        printf("Can\'t close file\n");
    }

    /*  Открываем файл в редакторе */
    result = execle("/bin/cat", "/bin/cat", argv[2], 0, envp);
    if (result < 0)
    {
        /* Если возникла ошибка, то попадаем сюда*/
        printf("Error on opening file");
        exit(-1);
    }

    return 0;
}