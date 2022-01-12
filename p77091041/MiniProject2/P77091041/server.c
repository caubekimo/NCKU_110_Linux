// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#define PORT 8080
#define ADD 1
#define ABS 2
#define MUL 3
#define NOT 4

int get_next_space(char* str, int start){
    int i;
    for(i = start; str[i] != ' ' && i < strlen(str); i++);
    return i == strlen(str) ? -1 : i;
}

int get_int(char* str, int start){
    int i, res = 0;
    for(i = start; i < strlen(str) && str[i] >= '0' && str[i] <= '9'; i++){
        res *= 10;
        res += (str[i] - '0');
    }
	
    return res;
}

/* Split string */
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller knows where the list of returned strings ends */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int main(int argc, char const *argv[])
{
	int server_fd, new_socket, valread, a, b;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello\n";
    char *del, *returnValue;
	char** tokens;

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );

	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}

	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}

	while(1){
		valread = read(new_socket, buffer, 1024);
		
		if (valread >= 0)
		{
			printf("receive: %s\n", buffer);

			if (strlen(buffer) > 0)
			{
				if (strncmp("add", buffer, strlen("add")) == 0)
				{
					tokens = str_split(buffer, ' ');
					// printf("token1: %s\ntoken2: %s", *(tokens + 1), *(tokens + 2));
					// printf("token1: %06d\ntoken2: %06d", atoi(*(tokens + 1)), atoi(*(tokens + 2)));
					a = atoi(*(tokens + 1));
					b = atoi(*(tokens + 2));
					returnValue = ((a + b) + '0');
					printf(returnValue);
					send(new_socket, returnValue, strlen(returnValue), 0);
					printf("send: %s\n", returnValue);
					free(tokens);
				}
				else if (strncmp("abs", buffer, strlen("abs")) == 0)
				{
					send(new_socket, buffer, strlen(buffer), 0);
					printf("send: %s\n", buffer);
				}
				else if (strncmp("mul", buffer, strlen("mul")) == 0)
				{
					send(new_socket, buffer, strlen(buffer), 0);
					printf("send: %s\n", buffer);
				}
				else if (strncmp("kill", buffer, strlen("kill")) == 0)
				{
					send(new_socket, "\n", strlen("\n"), 0);
					printf("send: %s\n", "Bye");
					return EXIT_SUCCESS;
				}
				else if (strlen(buffer) > 1)
				{
					send(new_socket, "Hello\n", strlen("Hello\n"), 0);
					printf("send: %s\n", "Hello\n");
				}
				else
				{
					send(new_socket, NULL, 0, 0);
					printf("send: %s\n", NULL);
				}
			}
		}
    }

	return EXIT_SUCCESS;
}

// https://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c
