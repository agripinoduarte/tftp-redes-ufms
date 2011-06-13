#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFFER 1024

int main(int argc, char *argv[])
{
	
	int iSock, iFileDescriptor, iNumBytes;
	struct sockaddr_in server_addr;
	struct hostent *he;
	
	char sBuffer[BUFFER], cmd[12];

	
	while(strcmp(cmd, "exit") != 0)
	{
		gets(cmd);
		
		if(strcmp(cmd, "get") == 0)
		{
		
		}
	}
	
	/*if(argc < 3)
	{
		printf("TFTP Client\n");
		exit(1);
	}
	
	//convertendo o endereco passado para uma estrutura que eu entendo
	if((he=gethostbyname(argv[1])) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
	
	if((iSock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}
	
	//abrir o arquivo passado
	iFileDescriptor = open(argv[2], O_RDONLY);
	if(iFileDescriptor < 0)
	{
		perror("open");
		exit(1);
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(2424);
	
	server_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(server_addr.sin_zero), 8);
	
	//inicio do envio
	iNumBytes = sendto(iSock, "01INICIO", 8, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if(iNumBytes < 0)
	{
		perror("sendto");
		exit(1);
	}	
	
	//primeiro eh enviado o nome do arquivo
	iNumBytes = sendto(iSock, argv[2], strlen(argv[2]), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if(iNumBytes < 0)
	{
		perror("sendto");
		exit(1);
	}
	
	iNumBytes = read(iFileDescriptor, &sBuffer, BUFFER);
	while(iNumBytes < 0)
	{
		//enviando o buffer
		iNumBytes = sendto(iSock, sBuffer, iNumBytes, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
		if(iNumBytes < 0)
		{
			perror("sendto (2)");
			exit(1);
		}
		fprintf(stderr, "\nEnviando ......... %d OK", iNumBytes);
		iNumBytes = read(iFileDescriptor, &sBuffer, BUFFER);
	}
	
	if(iNumBytes < 0)
	{
		perror("read");
		exit(1);
	}
	
	// fim do envio
	iNumBytes = sendto(iSock, "01FIM", 5, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
	if(iNumBytes < 0)
	{
		perror("sendto");
		exit(1);
	}

	close(iSock);
	close(iFileDescriptor);*/
	return 0;

}
