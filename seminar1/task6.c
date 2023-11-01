/* Создать программу для запуска на двух терминалах для обмена сообщениями между ними через файл - один 
передаёт(записывает файл) второй получает, можно чтобы он ещё и рассчитывал чего либо (например возводил строку, 
если это число, в квадрат). Что будет, если запустить более двух териналов на запись и на чтение?*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdbool.h>

#define WRITE(fd, buf, nbyte)   if (write(fd, buf, nbyte) < 0)                                  \
                                {                                                               \
                                    printf ("Can\'t write to file \"seminar1/message.txt\"\n"); \
                                    return false;                                               \
                                }

const char PATH_FILE[] = "seminar1/message.txt";

bool from_terminal_to_txt (const char *user_name)
{
    int message_file = open(PATH_FILE, O_WRONLY|O_CREAT);
    if(message_file < 0)
    {
        printf("Can\'t open file \"seminar1/message.txt\"\n");
        return false;
    }

    printf ("The program is ready to work\n");
    printf ("Write your message:\t");

    char str_[] = ":\t";
    WRITE(message_file, user_name, strlen(user_name));
    WRITE(message_file, str_,      strlen(str_)     );
    
    char c[1] = {0};
    while (c[0] != '\n')
    {
        c[0] = getchar();

        WRITE(message_file, c, 1);
    }

    if(close(message_file) < 0)
    {
        printf("Can\'t close file \"seminar1/message.txt\"\n");
        return false;
    }

    return true;
}

void from_txt_to_terminal ()
{

}

//argv[1] - имя пользователя
int main (int argc, char *argv[], char *envp[])
{
    if (argc < 2)
    {
        printf("You did not enter your name on the command line\n");
        return 1;
    }

    if (from_terminal_to_txt(argv[1]) == false)
    {
        return 1;
    }

    return 0;
}
