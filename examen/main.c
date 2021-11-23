#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void manejador(int senyal);
pid_t padre;

int main(int argc, char const *argv[])
{

    int fd[2];
    pipe(fd);
    padre = getpid();
    pid_t hijo = fork();

    if(hijo == 0) { //hijo
        
        close(fd[1]);
        sleep(1);
        printf("Hijo = %d\n", getpid());
        signal(SIGUSR1, manejador);
        pid_t abuelo;
        
        read(fd[0], &abuelo, sizeof(pid_t));
        printf("[Hijo]: Mi pid es %d, el pid de mi padre es %d y el pid de mi abuelo es %d\n",
         getpid(), getppid(), abuelo);

    } else {//padre
        pause();
        pid_t abuelo = getppid();
        printf("Abuelo = %d\n", abuelo);
        printf("Padre = %d\n", padre);
        close(fd[0]);
        write(fd[1], &abuelo, sizeof(pid_t));
        wait(NULL);
    }

    return 0;
}

void manejador(int senyal) {
    kill(padre, SIGUSR1);
    printf("manejador");
}

