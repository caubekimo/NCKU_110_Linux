// Client side C/C++ program to demonstrate Socket programming
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define _GNU_SOURCE
// #define EXIT_FAILURE 1
// #define EXIT_SUCCESS 0
#define FILENAME "./in"

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char *hello = "Hello from client";
	char buffer[1024] = {0};

	/* Sleep 500ms */
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

	/* Open the file for reading */
	char *line_buf = NULL;
	size_t line_buf_size = 0;
	ssize_t line_size;
	int line_count = 0;
	FILE *fp = fopen(FILENAME, "r");

	/* Exit if file can't be opened */
	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", FILENAME);
		return EXIT_FAILURE;
	}

	/* Get the first line of the file */
	line_size = getline(&line_buf, &line_buf_size, fp);

	/* Loop through until we are done with the file */
	while (line_size > 1)
	{
		/* Increment our line count */
		line_count++;

		/* Show the line details */
    	// printf("line[%06d]: chars=%06zd, buf size=%06zu, contents: %s", line_count, line_size, line_buf_size, line_buf);

		/* Call server */
		send(sock, line_buf, strlen(line_buf), 0);
		valread = read(sock, buffer, 1024);
		printf("%s",buffer);
		memset(buffer, 0, sizeof buffer);
		/* Get the next line */
		line_size = getline(&line_buf, &line_buf_size, fp);
	}

	/* Free the allocated line buffer */
	free(line_buf);
	line_buf = NULL;

	/* Close the file */
	fclose(fp);

	return EXIT_SUCCESS;
}

// https://riptutorial.com/c/example/8274/get-lines-from-a-file-using-getline--
// https://www.geeksforgeeks.org/socket-programming-cc/
// http://zake7749.github.io/2015/03/17/SocketProgramming/
