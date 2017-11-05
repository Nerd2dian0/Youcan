#
# Makefile for Menu Program
#

CC_PTHREAD_FLAG      = -lpthread
CC_FLAGS             = -c
CC_OUTPUT_FLAGS      = -o
CC                   = gcc
RM                   = -rm
RM_FLAGS             = -f

SRC     =  linktable.c menu.c test.c
TARGET  =  test
OBJS    =  linktable.o menu.o test.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FLAGS) $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) $<

clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGET) *.bak
