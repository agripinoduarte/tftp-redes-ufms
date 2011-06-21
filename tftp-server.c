#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <strings.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUFFER 576
#define SERVERPORT 2424

int iSock, iFileDescriptor;
struct sockaddr_in my_addr;
struct sockaddr_in client_addr;
socklen_t addr_len;
	
void rrq(char *buffer)
{
	char filename[255];
	strcpy(filename, &buffer[2]);
	char fBuffer[512];
	int iNumBytes;   
	puts(filename);
	
	FILE *pFile;
	pFile = fopen(filename, "r");
	int size;
	
	if (pFile != 0)
	{
		//fragmentar o arquivo em blocos de 512 bytes e envia-los sequencialmente para o cliente
		while(size = fread(fBuffer, 1, 512, pFile) > 0)
		{
			
			if(iNumBytes = sendto(iSock, fBuffer, BUFFER, 0, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)))
			{
			
			}
		
		}
	}
	else
	{
		//retornar pacote de erro
	}	
	

}

int main(void)
{
	int iNumBytes;
	char sBuffer[BUFFER], cmd[4];
	int new_fd;
	if((iSock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}
	
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(SERVERPORT);
	my_addr.sin_addr.s_addr = INADDR_ANY;
	bzero(&(my_addr.sin_zero), 8);
	
	if(bind(iSock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("bind");
		exit(1);
	}
	
	//loop infinito recebendo dados
	while(1)
	{
		puts("Esperando conexão...");
		addr_len = sizeof(struct sockaddr);
		
		if((iNumBytes = recvfrom(iSock, sBuffer, BUFFER, 0, (struct sockaddr *)&client_addr, &addr_len)) < 0)
		{
			perror("recvfroM");
			exit(1);
		}
		
		new_fd = accept(iFileDescriptor, (struct sockaddr *)&client_addr, &addr_len);
		puts("pedido recebido");
		
		switch(sBuffer[1])
		{
			case 1: //RRQ - Read Request
				rrq(sBuffer);
			break;
			
			case 2: //WRQ - Write Request
			
			break;
		
		}

		
		/*if(strcmp(sBuffer, "01INICIO") == 0)
		{
			if((iNumBytes = recvfrom(iSock, sBuffer, BUFFER, 0, (struct sockaddr *)&client_addr, &addr_len)) < 0)
			{
			
				perror("recvfrom");
				exit(1);
			}
			
			sBuffer[iNumBytes] = '\0';
			fprintf(stderr, "\nRecebendo o arquivo %s", sBuffer);
			iFileDescriptor = creat(sBuffer, 0644); //permissao -rw-r--r-- 
			
			if(iFileDescriptor < 0)
			{
				perror("creat");
				exit(1);
			}		
			
			//leitura ate o final do arquivo
			iNumBytes = recvfrom(iSock, sBuffer, BUFFER, 0, (struct sockaddr *)&client_addr, &addr_len);
			while(iNumBytes > 0)
			{
				sBuffer[iNumBytes] = '\0';
				if(strcmp(sBuffer, "01FIM") == 0) //fim de transmissao
				{
					break;
				}
				
				fprintf(stderr, "\nRecebendo ....... %d OK", iNumBytes);
				write(iFileDescriptor, sBuffer, iNumBytes);
				iNumBytes = recvfrom(iSock, sBuffer, BUFFER, 0, (struct sockaddr *)&client_addr, &addr_len);
			}
			
			if(iNumBytes < 0)
			{
				perror("recvfrom");
				exit(1);
			}
			
			close(iFileDescriptor);
			fprintf(stderr, "\nFim de transferencia");
		}*/
			
	}	
	
	close(iSock);
	
	return 0;
}

