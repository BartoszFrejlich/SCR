#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 256

int main() {

    pid_t pid;
    int fd[2], str;
    char buf[BUF_SIZE];
    char fname[32];
    if(pipe(fd) < 0) {
        fprintf(stderr, "nie utworzono pipa\n");
        return 1;
    }
    pid = fork();
    if(pid > 0){//parent
        close(fd[0]);
        printf("Sciezka pliku:\n");
        scanf("%s", fname);
	FILE *file;
	
        if((file = fopen(fname, "r")) == NULL) {
            fprintf(stderr, "nie otwarto pliku\n");
            return 2;
	}
       while((fgets(buf, BUF_SIZE, file)) != NULL) {    
	 write(fd[1], buf, BUF_SIZE);
	 }
       fclose(file);
       wait(NULL);
       close(fd[1]);
    }
 else if(pid == 0) {//child
        close(fd[1]);
        FILE *reading_stream;
	reading_stream = fdopen(fd[1], "r");
	while(read(fd[0], buf, BUF_SIZE) != 0){
	  printf("#$s#", buf);
	  printf("reading from pipe\n");
	}
	printf("koniec odczytu\n");
	close(fd[0]);
    } 
}
