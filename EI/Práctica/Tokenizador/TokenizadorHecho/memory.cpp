///////////////////////////////////////////////////////
//                    memory.cpp                     //
// Por Ginés G.M., basado en el código de la función //
// SafeExec, por Jose Paulo Leal.        25/1/2008   //
//---------------------------------------------------//
// Este programa hace una estimación (aproximada) de //
// la máxima cantidad de memoria usada por otro pro- //
// grama cualquiera. Esto se consigue haciendo un    //
// muestreo del uso de memoria unas 16 veces por se- //
// gundo, quedándose con el máximo.                  //
// Compilar con: g++ memory.cpp -o memory            //
///////////////////////////////////////////////////////



#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


#define SIZE          8192  /* tamaño de buffer para leer /proc/<pid>/status */
#define INTERVAL        61  /* muestrear unas 16 veces por segundo */


pid_t pid;
int max_data= 0;
int max_stack= 0;

void error (char *pt)
{
  if (pt)
    fprintf(stderr, pt);
  abort();
}

int max (int a, int b)
{
  return (a > b ? a : b);
}

/* Kill the child process, noting that the child
   can already be a zombie (on  this case  errno
   will be ESRCH)
*/

void terminate (pid_t pid)
{
  int v;
  v = kill (-1, SIGKILL);
  if (v < 0)
    if (errno != ESRCH)
      error("error en terminate\n");
}

/* high resolution (microsecond) sleep */
void msleep (int ms)
{
  struct timeval tv;
  int v;
  do
    {
      tv.tv_sec = ms / 1000;
      tv.tv_usec = (ms % 1000) * 1000;
      v = select (0, NULL, NULL, NULL, &tv);
      /* The value of the timeout is undefined after the select returns */
    }
  while ((v < 0) && (errno == EINTR));
  if (v < 0)
    error("error en msleep\n");
}

int memusage (pid_t pid)
{
  char a[SIZE], *p, *q;
  int data, stack;
  int n, v, fd;

  p = a;
  sprintf (p, "/proc/%d/status", pid);
  fd = open (p, O_RDONLY);
  if (fd < 0)
    error ("error despues de fd = open\n");
  do
    n = read (fd, p, SIZE);
  while ((n < 0) && (errno == EINTR));
  if (n < 0)
    error ("error despues de n = read\n");
  do
    v = close (fd);
  while ((v < 0) && (errno == EINTR));
  if (v < 0)
    error ("error despues de v = close\n");

  data = stack = 0;
  q = strstr (p, "VmData:");
  if (q != NULL)
    {
      sscanf (q, "%*s %d", &data);
      q = strstr (q, "VmStk:");
      if (q != NULL)
    sscanf (q, "%*s %d\n", &stack);
    }
  max_data= max(data, max_data);
  max_stack= max(stack, max_stack);
  return (data + stack);
}

void printusage (char **p)
{
  fprintf (stderr, "Uso: %s <comando>\n", *p);
  fprintf (stderr, "\t<comando>         Programa ejecutable y parametros, en su caso.\n");
}

int main (int argc, char **argv, char **envp)
{
  int status, mem;
  int v;

  if (argc <= 1 || (argc==2 && !strcmp(argv[1], "--help"))) {
    printusage (argv);
    return (EXIT_FAILURE);
  }
  else {
    pid = fork ();
    if (pid < 0)
       error ("error despues del fork\n");
    if (pid == 0) {
      if (execve (argv[1], argv+1, envp) < 0) {
        kill (getpid (), SIGPIPE);
        error ("error despues de execve\n");
      }
    }
    else {
      mem= 16;
      do {
        msleep(INTERVAL);
        mem= max(mem, memusage(pid));
        do
          v= waitpid (pid, NULL, WNOHANG | WUNTRACED);
        while ((v < 0) && (errno != EINTR));
        if (v < 0)
          error("error despues de waitpid\n");
      } while (v == 0);
      fprintf(stderr, "\nMemoria total usada: %d Kbytes\n", mem);
      fprintf(stderr, "  \"   de datos: %d Kbytes\n", max_data);
      fprintf(stderr, "  \"    de pila: %d Kbytes\n", max_stack);
    }
  }
  return (EXIT_SUCCESS);
}
