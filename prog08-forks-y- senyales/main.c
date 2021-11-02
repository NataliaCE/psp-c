#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

//Definimos manejador de señal
void manejadorHijo(int num_senyal);
void manejadorPadre(int num_senyal);

int main(int argc, char const *argv[])
{
    pid_t pid;
    pid = fork();
    if(pid == -1) {//Gestiona un posible error
        perror("Error en el fork");
        exit(1);
    }
    if(pid == 0) { //Soy el hijo
        signal(SIGUSR1, manejadorHijo);
        printf("[PROCESO: %d]: Manejador activado", getpid());
        pause();

    } else { //Soy el padre
        signal(SIGUSR1, manejadorPadre);
        printf("[PROCESO: %d]: Manejador activado", getpid());
        pause();
        pid_t pid_hijo = wait(NULL);
    }
    return 0;
}

//Implementamos los manejadores
void manejadorHijo(int num_senyal) {
    printf("Soy el manejador de la señal hijo.");
}

void manejadorPadre(int num_senyal) {
    printf("Soy el manejador de la señal padre.");
}

//En la terminal --> kill -SIGUSR1 'pid'