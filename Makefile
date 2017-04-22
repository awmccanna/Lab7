CC=gcc

lab7:	cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./changeDir/changeDir.o
	${CC} -g cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./changeDir/changeDir.o -o lab7

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	${CC} -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	${CC} -g -c ./utils/myUtils.c

process.o:	./process/process.c ./process/process.h
	${CC} -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	${CC} -g -c ./pipes/pipes.c

changeDir.o:	./changeDir/changeDir.c ./changeDir/changeDir.h
	${CC} -g -c ./changeDir/changeDir.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./changeDir/changeDir.o
	rm lab7

