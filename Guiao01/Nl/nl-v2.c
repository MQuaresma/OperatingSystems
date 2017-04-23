#ifndef NLV2H
#define NLV2H
#include "nl-v2.h"
#endif

struct elem{

	char *st;
	struct elem *next;

    
};


struct buffer_t{

	Elem start;
	Elem in;
	Elem out;
	    
    
};


/* reads until a new line char is found or until block is reached */
ssize_t readln(int fildes, struct buffer_t *b, void **buf){

	ssize_t res = -1;

	if(b->out){
		*buf = b->out->st;
		b->out = b->out->next;
		res = strlen(*buf);
	}
	else{
		if((res=create_buffer(fildes, b, BLOCKSIZE)) > 0){
			*buf = b->out->st;
			b->out = b->out->next;
			res = strlen(*buf);
		}            
	}

	return res;
}


int create_buffer(int fildes, struct buffer_t *b, size_t nbyte){


	int len, i;
	ssize_t res;
	char *buf = (char*)malloc(sizeof(char)*nbyte);
	destroy_buffer(b);

	if(!buf) fprintf(stderr, "Not enough space to meet request\n");

	res = read(fildes, buf, nbyte);

	if(res <= 0){ 
		free(buf);
		return -1;
	}


	for(i = 0, len = 0; i < res; i ++, len = 0){

		if(b->in){
			b->in->next = (Elem)malloc(sizeof(struct elem));
			b->in = b->in->next;
		}else{
			b->in = (Elem)malloc(sizeof(struct elem));
			b->out = b->in;
			b->start = b->in;
		}

		while(i < res && buf[i] != '\n'){ 
			len ++;
			i ++;
		}

		b->in->st = strndup(&(buf[i-len]), len+1);
		b->in->next = NULL;

	}

	free(buf);

	return 1;

}

int destroy_buffer(struct buffer_t *b){

	Elem aux;

	if(b){
		while(b->start){
			aux = b->start->next;
			free(b->start->st);
			free(b->start);
			b->start = aux;
		}
		b->start = b->in = b-> out = NULL;
	}
}   
    
    
    
void reverse(char p[], int size){

	char c;
	int j=0;

	while(j < --size){
		c = p[size];  
		p[size] = p[j];
		p[j++] = c;
	}

}

void itoa(int in, char p[]){
    
	int i=0;

	do{
		p[i++] = (in%10) + '0';
	}while(in/=10);

	p[i] = '\0';

	reverse(p, i);
}

struct buffer_t *bufferInit(void){

	struct buffer_t *b = (struct buffer_t *)malloc(sizeof(struct buffer_t));
	b->in=b->out=b->start=NULL;

	return b;
}
