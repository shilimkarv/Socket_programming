TARGET	=	client	server
CC	=	gcc
CFLAGS	=		-g
normal	:	$(TARGET)

client	:	client.c
	$(CC)	$(CFLAGS)	client.c	-pthread -o	client

server	:	server.c
	$(CC)	$(CFLAGS)	server.c	-o	server

clean	:
	$(RM) $(TARGET)
#make -f makefile2.mk normal
