CC:=gcc
exe1:=tcp_server
exe2:=tcp_client
obj1:=tcp_server.c
obj2:=tcp_client.c

all: $(obj1) $(obj2)
	$(CC) -o $(exe1) $(obj1)
	$(CC) -o $(exe2) $(obj2)

.PHONY:clean
clean:
	rm -rf $(exe1) $(exe2)