#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/unistd.h>     /* chamadas ao sistema: defs e declaraçoes essenciais */
#include <sys/fcntl.h>      /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#define BLOCKSIZE 1024
#define SIZE 10

struct elem;
typedef struct elem *Elem;
struct buffer_t;

ssize_t readln(int, struct buffer_t *, void **);
int create_buffer(int, struct buffer_t *, size_t);
int destroy_buffer(struct buffer_t *);
void itoa(int, char*);
void reverse(char p[], int );
struct buffer_t *bufferInit(void);
