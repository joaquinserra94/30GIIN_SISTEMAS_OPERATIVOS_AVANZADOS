#include <sys/types.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>
int main(int argc, char** argv) { 
pid_t pid;
pid = fork();
switch (pid) {
case -1: /* error */
exit(-1);
case 0: /* proceso hijo */
if (execvp(argv[1], &argv[1]
)<0) {
perror("error");
}
break; 
default:
printf("Proceso padre");
}
return 0;
}

/**/