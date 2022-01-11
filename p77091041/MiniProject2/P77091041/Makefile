all: client server

.PHONY = clean client server

client: client.c
	gcc $< -o $@
server: server.c
	gcc $< -o $@

clean:
	rm client server