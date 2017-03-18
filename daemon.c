#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void *sigchld_handler()
{
    int *status;

    status = NULL;
    while (wait3(status, WNOHANG, (struct rusage *) 0) > 0) {
        ;
    }
}

void make_daemon()
{
    int tty_fd;

    /* Close all open file descriptors */
    for (int i = 0; i < getdtablesize(); i++) {
        close(i);
    }

    chdir("/"); /* Change to root directory */
    umask(0); /* Reset file access creation mask */

    /* Fork a child process and kill the parent. This is done to run
       the daemon in background */
    if (fork() != 0) {
        exit(0);
    }

    setpgid(0, getpid()); /* Dissociate from process group and make itself the
                             process group leader */

    /* Make the terminal not be the controlling terminal */
    if ((tty_fd = open("/dev/tty", O_RDWR)) >= 0) {
        ioctl(tty_fd, TIOCNOTTY, (char *) 0);
    }

    /* Ignore terminal I/O signals */
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    /* Catch SIGCHLD to avoid zombie processes */
    signal(SIGCHLD, sigchld_handler);
}
