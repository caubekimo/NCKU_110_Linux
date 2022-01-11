// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define _GNU_SOURCE
#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

    FILE * fp; //讀進來的檔案
    char * line = NULL; //讀進來的某一行
    size_t len = 0; //prefix 的長度
	
    usleep(500000);

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}

	//讀取 in 檔
	fp = fopen("./in", "r");

	//如果沒有這個檔案, 就離開 with error
    if (fp == NULL)
	{
		printf("\nIn file not exists \n");
		return -1;
	}

    while(getline(&line, &len, fp) != -1){
		printf("line length: %zd\n", strlen(line));

		if (str(line) == "")
		{
			// print("kill");
		}
		// 呼叫 server
		else
		{
		// 		// if (strncmp("add", read, strlen("add")) == 0)
		// 		// {

		// 		// }
		// 		// else if(strncmp("abs", read, strlen("abs")) == 0)
		// 		// {

		// 		// }
		// 		// else if (strncmp("mul", read, strlen("mul")) == 0)
		// 		// {

		// 		// }
		// 		// else if (strncmp("kill", read, strlen("kill")) == 0)
		// 		// {

		// 		// }
		// 		// else
		// 		// {
		// 		// 	print()
		// 		// }
		}
    }

	fclose(fp);
	free(line)

	return 0;
}

// https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--
// https://www.geeksforgeeks.org/socket-programming-cc/
// http://zake7749.github.io/2015/03/17/SocketProgramming/