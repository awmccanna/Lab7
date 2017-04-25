CC=gcc
FLAGS= -g


lab7:	cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./changeDir/changeDir.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./history/history.o ./alias/alias.o ./utils/fileUtil.o
	${CC} ${FLAGS} cscd340Lab7.c ./tokenize/makeArgs.o ./utils/myUtils.o ./process/process.o ./pipes/pipes.o ./changeDir/changeDir.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./history/history.o ./alias/alias.o ./utils/fileUtil.o -o lab7

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	${CC} ${FLAGS} -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.c ./utils/myUtils.h
	${CC} ${FLAGS} -c ./utils/myUtils.c

fileUtil.o:	./utils/fileUtil.c ./utils/fileUtil.h
	${CC} ${FLAGS} -c ./utils/fileUtil.c

process.o:	./process/process.c ./process/process.h
	${CC} ${FLAGS} -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	${CC} ${FLAGS} -c ./pipes/pipes.c

changeDir.o:	./changeDir/changeDir.c ./changeDir/changeDir.h
	${CC} ${FLAGS} -c ./changeDir/changeDir.c

listUtils.o:	./linkedlist/listUtils.c listUtils.h
	${CC} ${FLAGS} -c ./linkedlist/listUtils.c

linkedList.o:	./linkedlist/linkedList.h ./linkedlist/linkedList.c ./linkedlist/requiredIncludes.h
	${CC} ${FLAGS} -c ./linkedlist/linkedList.c

history.o: 	./history/history.c ./history/history.h
	${CC} ${FLAGS} -c ./history/history.c

alias.o: 	./alias/alias.c ./alias/alias.h
	${CC} ${FLAGS} -c ./alias/alias.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./utils/fileUtil.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./changeDir/changeDir.o
	rm ./linkedlist/linkedList.o
	rm ./linkedlist/listUtils.o
	rm ./history/history.o
	rm ./alias/alias.o
	rm lab7

