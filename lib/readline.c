/* include readline */
#include	"unp.h"

static int	read_cnt;
static char	*read_ptr;
static char	read_buf[MAXLINE];

static ssize_t
my_read(int fd, char *ptr){
  // below if statement be executed only once. At the first time reading 
  // is successful, read_cnt will be assigned with a value of the number 
  // of read characters.
  // comparing with test/readline1.c, this is reason why the performance
  // will be improved dramatically.
  // read into buffer -- means read specified size length of characters 
  // into buffer. not just one , two, three... any lines.
  if (read_cnt <= 0) {
  again:
    if ( (read_cnt = read(fd, read_buf, sizeof(read_buf))) < 0) {
      if (errno == EINTR)
        goto again;
      return(-1);
    } else if (read_cnt == 0)
      return(0);
    read_ptr = read_buf;
  }

  read_cnt--;
  *ptr = *read_ptr++;
  return(1);
}

ssize_t readline(int fd, void *vptr, size_t maxlen) {
  ssize_t	n, rc;
  char	c, *ptr;
  
  ptr = vptr;
  for (n = 1; n < maxlen; n++) {
    if ( (rc = my_read(fd, &c)) == 1) {
      *ptr++ = c;
      if (c == '\n')
        break;	/* newline is stored, like fgets() */
    } else if (rc == 0) {
      *ptr = 0;
      return(n - 1);	/* EOF, n - 1 bytes were read */
    } else
      return(-1);		/* error, errno set by read() */
  }
  
  *ptr = 0;	/* null terminate like fgets() */
  return(n);
}

ssize_t readlinebuf(void **vptrptr){
  if (read_cnt)
    *vptrptr = read_ptr;
  return(read_cnt);
}
/* end readline */

ssize_t Readline(int fd, void *ptr, size_t maxlen){
  ssize_t n;

  if ( (n = readline(fd, ptr, maxlen)) < 0)
    err_sys("readline error");
  return(n);
}

/* int main(){ */
/*   int filedesc3 = open("test.txt",O_RDWR); */
/*   /\* my_read(filedesc3,&c3); *\/ */
/*   /\* printf("c3 is : %c", c3); *\/ */
  
/*   char str[50];   */
/*   readline(filedesc3,str,49); */
/*   printf("str is : %s",str); */
  
/*   return 0; */
/* } */
