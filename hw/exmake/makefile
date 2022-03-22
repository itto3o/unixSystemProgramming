#makefile

CC = gcc

LDFLAGS = -L. -lmine
TARGET = expProg
OBJS = main.o libmine.a

.SUFFIXES : .c .o
	.c.o :
		$(CC) -c $<

#이걸로 최종파일이 만들어 질테니까?
$(TARGET) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

#여기서 libmine.a만 정의해주면 되지 않을까?
libmine.a : exp.c
	ar ruv libmine.a exp.c


#지난 시간 makefile
#expProg : main.o libmine.a
#	gcc -o expProg -L. main.o -lmine

#main.o : main.c
#	gcc -c main.c

#libmine.a : exp.o
#	ar ruv libmine.a exp.o

#exp.o : exp.c
#	gcc -c exp.c
