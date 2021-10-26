//Exec/exec_error.c
int main(int argc, char const *argv[])
{
    printf("Try to execute lss\n");
    if(execl("/bin/lls", "lls") == -1) {

    }
    return 0;
}
