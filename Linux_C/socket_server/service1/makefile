CC:=gcc
exe1:=service1_server
exe2:=service1_client
obj1:=service1_server.c
obj2:=service1_client.c

all: $(obj1) $(obj2)
	$(CC) -o $(exe1) $(obj1)
	$(CC) -o $(exe2) $(obj2)

.PHONY: clean
clean:
	rm -rf $(exe1) $(exe2)