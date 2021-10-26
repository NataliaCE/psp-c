#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {

    pid_t pid_padre = getpid();
    pid_t pid_hijo;
    int estado_proceso;
    //Duplico el proceso
    pid_t pid_proceso = fork();
    if(pid_proceso != 0) {
        //Si lo ejecuta el padre
        pid_hijo = pid_proceso;
    } else {
        //Si lo ejecuta el padre
        pid_hijo = getpid();
    }
    //Duplico el proceso. Se duplican tanto padre como hijo.
    fork();
    printf("[Proceso %d]: Hola, soy el hijo de %d \n", getpid(), getppid());

    if (getpid() == pid_padre) {
        wait(&estado_proceso);
        wait(&estado_proceso);
    }
    if (getpid() == pid_hijo) {
        wait(&estado_proceso);
    }
    return 0;
}
//Ctrl + ` --> terminal