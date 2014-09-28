Comunicacion-Pipes
==================

Paso de mensajes

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define ESCRITURA 1
#define LECTURA 0
main()
{
	pid_t pid;
	int fd1[2]; 
	int pid_hijo;
	int fd2[2]; 
	int msg_length; 
	char msje[100]; 
	char msje2[100]; 
	char p[100]; 

	
	if (pipe(fd1) == -1 || pipe(fd2) == -1) 
	{
		perror("No se pudo crear el pipe");
		exit(-1);
	}

	if ((pid = fork()) == -1) 
	{
		printf("No se pudo crear hijo\n");
		exit(-1);
	}

	if (pid == 0)
	{
		printf("Descriptores del hijo: fd1[0] = %d, fd1[1] = %d\n", fd1[0], fd1[1]); 
		close(fd1[1]); 
		msg_length = read(fd1[0], msje, sizeof(msje));
		printf("recibi pregunta: %s\n",msje);
		pid_hijo=getpid(); 
		write(fd2[ESCRITURA], &pid_hijo, sizeof(pid_hijo));
		exit(0);
	}

	else 
	{
		printf("Descriptores del padre: fd1[0] = %d, fd1[1] = %d\n", fd1[0], fd1[1]); 
		close(fd1[0]); 
		write(fd1[1],"cual es tu pid",15); 
		msg_length = read(fd2[LECTURA],&pid_hijo,sizeof(pid_hijo)); /
		printf("el pid es: %d\n",pid_hijo);
		exit(0); 
	}
	exit(0);
}
