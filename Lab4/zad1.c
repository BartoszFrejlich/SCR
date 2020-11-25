#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 64

int main(int argc, char *argv[]) {

    pid_t pid;
    int fd[2];
    char buf[BUF_SIZE];
    char fname[32];
    if(pipe(fd) < 0) {
        fprintf(stderr, "nie utworzono pipa\n");
        return 1;
    }
    pid = fork();
    if(pid > 0){//parent
        close(fd[0]);
	FILE *file;
	
        if((file = fopen(argv[1], "r")) == NULL) {
	  fprintf(stderr, "nie otwarto pliku\n");
	  return 2;
	}
       while((fgets(buf, BUF_SIZE, file)) != NULL) {    
	 write(fd[1], buf, BUF_SIZE);
	 }
       fclose(file);
       close(fd[1]);
    }
 else if(pid == 0) {//child
        close(fd[1]);
        FILE *reading_stream;
	reading_stream = fdopen(fd[1], "r");
	printf("\n");
	while(read(fd[0], buf, BUF_SIZE) != 0){
	  printf("#%s#\n", buf);
	}
	printf("koniec odczytu\n");
	close(fd[0]);
	return 0;
    }
}
