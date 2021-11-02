#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>

void tratarSenyal(int cod_senyal); //declaracion

int main(int argc, char const *argv[])
{
    pid_t pidHijo1, pidHijo2;
    printf("[PADRE]: %d\n", getpid());

    if((pidHijo1 = fork()) == -1) { //error
        exit(-1);
    }

    if(pidHijo1 == 0) { //hijo 1
        signal(SIGUSR1, tratarSenyal);
        printf("[HIJO 1]: Pid: %d\n", getpid());
        pause(); //Espero una señal (no puede discriminar)

    } else { //padre
        printf("[PADRE]: He creado un hijo con pid %d\n", pidHijo1);
        if((pidHijo2 = fork()) == -1) { //error
            exit(-1);
        }

        if(pidHijo2 == 0) { //hijo 2
            printf("[HIJO 2]: Pid: %d\n", getpid());
            sleep(2);
            kill(pidHijo1, SIGUSR1); //señal a hijo 1

        } else { //padre
            printf("[PADRE]: He creado un hijo con pid %d\n", pidHijo2);
            printf("[PADRE]: Esperando a un hijo...\n");
            printf("[PADRE]: El hijo con pid %d finalizó\n", wait(NULL));
            printf("[PADRE]: Esperando a otro hijo...\n");
            printf("[PADRE]: El hijo con pid %d finalizó\n", wait(NULL));
        }
    }

    return 0;
}

void tratarSenyal(int cod_senyal) {
    printf("[PROCESO %d]: He recibido una señal\n", getpid());
}
