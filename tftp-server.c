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

int main(void)
{

	int iSock, iFileDescriptor;
	struct sockaddr_in my_addr;
	struct sockaddr_in client_addr;
	socklen_t addr_len;
	int iNumBytes;
	char sBuffer[BUFFER];
	
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
		puts(".");
		addr_len = sizeof(struct sockaddr);
		if((iNumBytes = recvfrom(iSock, sBuffer, BUFFER, 0, (struct sockaddr *)&client_addr, &addr_len)) < 0)
		{
			perror("recvfroM");
			exit(1);
		}
		
		fprintf(stderr, "Recebendo pacotes de %s\n", inet_ntoa(client_addr.sin_addr));
		fprintf(stderr, "o pacote tem %d bytes\n", iNumBytes);
		sBuffer[iNumBytes] = '\0';
		
		if(strcmp(sBuffer, "01INICIO") == 0)
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
		}
			
	}	
	
	close(iSock);
	
	return 0;
}
