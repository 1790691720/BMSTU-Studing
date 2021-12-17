#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

typedef void (*sighandler)(int);
void brake(int);
jmp_buf pos;
sigjmp_buf buf;
static char digit[3];
static char* who[] = { "Pl1: ", "Pl2: ", "Bye.\n" };
int j = 0;

int main(int argc, char** argv) {
    srand(getpid());

    char previous = '1' + getpid() % 6;
    digit[0] = previous;
    digit[1] = '\b';
    digit[2] = '\n';
    signal(SIGALRM, (sighandler) brake);
    signal(SIGQUIT, (sighandler) brake);
    if((j = setjmp(pos)) == 1)
        alarm(0);
    else
        alarm(0);

    if (!sigsetjmp(buf,1))
    {
        /* code */
    }
    
    write(1, who[j], 5);
    while(j < 2) {
        write(1, digit, 2);
        int rnd = rand() % 5;
        switch (previous) {
            case '1':
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            case '2':
                if (rnd == 4) rnd = 5;
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            case '3':
                if (rnd == 3) rnd = 5;
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            case '4':
                if (rnd == 2) rnd = 5;
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            case '5':
                if (rnd == 1) rnd = 5;
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            case '6':
                if (rnd == 0) rnd = 5;
                digit[0] = '1' + rnd;
                previous = digit[0];
                break;
            default:
                digit[0] = '1' + rnd + rand() % 2;
                previous = digit[0];
                break;
        }
        usleep(50000);
    } /* while-j */
    signal(SIGINT, SIG_DFL);
    exit(0);
}

void brake(int c) {
    j++;
    static int j = 0;
    write(1, digit, 3);
    siglongjmp(buf,1);
    longjmp(pos, ++j);
    return;
}
