/* Дописать комментарии ко всем непонятным местам.
   1 Повысить надёжность при записи текста исходящего соообщения.
   3 Как формируется уникальный ключ для разделяемой памяти.
   2 Переделать на работу с несколькими терминалами,
    каждое сообщение начинать с номера терминала, 
    номер терминала передавать в параметре при запуске.*/
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHMEM_SIZE 4096
#define SHM_KEY_BASE 0xDEADBABE
#define SHM_MAXSIZE 1 << 20
#define DELAY (10*1000)
#define OFFSET 100

int main()
{
    // ttyname(int fd) возвращает указатель на полное имя устройства терминала, заканчивающееся на NULL, открытого на описателе файла fd.
    // fileno(FILE *stream) определяет дескриптор файла открытого потока данных по указателю на управляющую таблицу потока данных.
	printf( "--------------------\n"
		    "SHM-Chat 0.1\n"
		    "--------------------\n"
		    "To send message just type it and press Enter. Another instance of SHM-Chat receives and displays it.\n"
		    "--------------------\n"
		    "stdin: %s\n"
		    "stdout: %s\n"
		    "--------------------\n"
		    "Enter any number (chat is among instances with the same number):",
            ttyname(fileno(stdin)), ttyname(fileno(stdout)));

	int shm_key = 0; // Ключ для сегмента разделяемой памяти.
	scanf("%d", &shm_key); 
	shm_key += SHM_KEY_BASE;

	printf("--------------------\n\n");
	
	// Проверьте, работает ли уже более одного экземпляра.
	int shmid_test = shmget(shm_key, SHMEM_SIZE, 0777);		
	struct shmid_ds buf; // Информация о сегменте, которая находится в shmid, возвращается в эту структуру.
	shmctl(shmid_test, IPC_STAT, &buf); //shmctl() позволяет пользователю получать информацию о разделяемых сегментах памяти.

    // buf.shm_nattch - количество текущих подключений сегмента.
	if (buf.shm_nattch > 2 && buf.shm_nattch < 0xFF)
	{
		printf("Only tet-a-tet chat is supported! Now exiting...\n");
		exit(1);
	}

    /* Порождаем новый процесс и проверяем не возникло ли ошибки. */
	pid_t childpid = 0;
	if ((childpid = fork()) == -1)
	{
		perror("Fork error");
	}
	
	if(childpid == 0)
	{
		//Дочерний процесс: печатает входящие сообщения.
		usleep(DELAY); /*Функция usleep приостанавливает работу потока, в котором она была вызвана, 
                        на указанное в аргументе время в микросекундах или до поступления сигнала,
                        по которому вызывается функция обработки сигналов или программа завершает свою работу.*/
		int shmid = shmget(shm_key, SHMEM_SIZE, 0777);
		char* shmem = (char*)shmat(shmid, NULL, 0);
		shmem[0] = 0;

		for(;;)
		{
			if (shmem[0] != 0 && strcmp(shmem, ttyname(fileno(stdout))) != 0)
			{
				printf("--> %s\n", shmem + OFFSET);
				shmem[0] = 0;
			}
			usleep(DELAY);
		}
	} 
    else
	{
		// Родительский процесс: сканирует исходящие сообщения.
		int shmid = shmget(shm_key, SHMEM_SIZE, IPC_CREAT|0777);
		char* shmem = (char*)shmat(shmid, NULL, 0);
		usleep(20 * 1000);

		for(;;)
		{
			gets(shmem + OFFSET);
			ttyname_r(fileno(stdin), shmem, 20);
			usleep(DELAY);
		}
	}

    return 0;
}