/* разобраться как работает, написать комментарии,
   в том числе ко всем параметрам. */
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv)
{
	int shm_id = -1; // Дескриптор System V IPC для сегмента разделяемой памяти.
	char* shm_buf = -1; // Адрес сегмента разделяемой памяти в адресном пространстве процесса.
	
    /*Проверяем количество аргументов командной строки.*/
	if (argc < 2) 
	{
		fprintf(stderr, "Too few arguments\n");
		return 1;
	}

	shm_id = strtol(argv[1], NULL, 10); //Первым аргументом командной строки должен быть дескриптор ранее используемого сегмента разделяемой памяти.
	shm_buf = (char*) shmat (shm_id, NULL, 0); //Включим память в адресное пространство процесса.
	if (shm_buf == -1)
	{
		//fprintf(stderr, "shmat() error\n");
        perror ("shmat() error");
		return 1;
	}

	printf ("Message: %s\n", shm_buf);

	/*Функция shmdt отстыковывает сегмент разделяемой памяти, 
    находящийся по адресу shmaddr, от адресного пространства вызвающего процесса.*/
	shmdt(shm_buf); 
	shmctl(shm_id, IPC_RMID, NULL); //Удаляем из системы ранее использованный сегмент разделяемой памяти.
    
	return 0;
}