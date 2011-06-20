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

#define BUFFER 512

int main(int argc, char *argv[])
{
	
	int iSock, iFileDescriptor, iNumBytes;
	struct sockaddr_in server_addr;
	struct hostent *he;
	int i , j;
	
	char sBuffer[BUFFER], input[512], *cmd, *token, *filename;
	
	if(argc < 3)
	{
		printf("Uso: client <endereço> <porta>\n");
		exit(1);
	}
	
	
	//convertendo o endereco passado para uma estrutura que eu entendo
	if((he = gethostbyname(argv[1])) == NULL)
	{
		perror("gethostbyname");
		exit(1);
	}
	
	if((iSock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket");
		exit(1);
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons((int)argv[2]);
	server_addr.sin_addr = *((struct in_addr *)he->h_addr);
	bzero(&(server_addr.sin_zero), 8);
	
	
	printf("----------------------------TFTP - Trivial File Transfer Protocol------------------------------------");
	printf("\nComandos:\n\tget <arquivo>\n\tput <arquivo>\n\trexmt <tempo>\n\ttimeout <tempo>\n\ttrace\n\tquit\n");
	
	cmd = malloc(5);
	filename = malloc(255);
	
	while(strcmp(cmd, "quit") != 0 && strcmp(cmd, "q") != 0)
	{
		printf(">");
		gets(input);
		cmd = strtok (input, " ");
		
		if(strcmp(cmd, "get") == 0 || strcmp(cmd, "g") == 0 )
		{
			puts("Buscando arquivo remoto...");
			
			if((filename = strtok(NULL, " ")) != NULL)
			{
				sBuffer[0] = 0; sBuffer[1] = 1;  //Read Request (RRQ)
				
				for(j = 0,i = 2; j < strlen(filename); j++, i++)
				{
					sBuffer[i] = filename[j];
				}
				
				sBuffer[i] = 0;
				sBuffer[i+1] = 'R';
				sBuffer[i+2] = 0;
				
				printf("%d", sizeof(sBuffer));
				iNumBytes = sendto(iSock, sBuffer, strlen(sBuffer), 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
				
				if(iNumBytes < 0)
				{
					perror("sendto");
				}
				else
				{
					//recebe o ACK e enviar proximo pacote
				}
					
				
			}			
			
		}
		else if(strcmp(cmd, "put") == 0 || strcmp(cmd, "p") == 0 )
		{
			//abrir o arquivo passado
			/*iFileDescriptor = open(argv[2], O_RDONLY);
			if(iFileDescriptor < 0)
			{
				perror("open");
				exit(1);
			}*/	
		}
		else if(strcmp(cmd, "rexmt") == 0 || strcmp(cmd, "r") == 0 )
		{
		
		}
		else if(strcmp(cmd, "timeout") == 0 || strcmp(cmd, "t") == 0 )
		{
		
		}
		else if(strcmp(cmd, "trace") == 0 || strcmp(cmd, "c") == 0 )
		{
		
		}
		else if(strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0 )
		{
			puts("\nbye");
		}
		else
		{
			printf("\n\'%s\': comando inválido. Use get, put, rexmt, timeout, trace ou quit\n", cmd);
		}
	}
	
	
	
	
	//inicio do envio
	/*iNumBytes = sendto(iSock, "01INICIO", 8, 0, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
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
	}*/

	close(iSock);
	close(iFileDescriptor);
	return 0;

}
