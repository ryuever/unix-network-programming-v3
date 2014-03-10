#include	"unp.h"

void
sig_chld(int signo){
  pid_t	pid;
  int		stat;

  // constant WNOHANG tells waitpid not to block if there are running children that 
  // have not yet terminated.
  while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
    printf("child %d terminated\n", pid);
  return;
}
