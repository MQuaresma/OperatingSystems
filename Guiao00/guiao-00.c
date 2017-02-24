#include <stdio.h>
#include <stdlib.h>
#include "guiao-00.h"


Intv reservaV1(Intv livres, int n, int *reservado){

	Intv lRun = livres, laux = NULL, save = NULL, saveAux;
	int excess = 65535, disp;
	*reservado = -1;

	while(lRun && excess != 0){
		disp = lRun->lst - lRun->fst;
		if(disp >= n && disp-n<excess){
			excess = disp-n;
			save = lRun;
			saveAux = laux;
		}
		laux = lRun;
		lRun = lRun->prox;
	}

	if(save){
		*reservado = save->lst-n+1;
		if(excess == 0){
			if(saveAux) saveAux->prox = save->prox;
			else livres = save->prox;
			free(save);
		}
		else save->lst = *reservado-1;
	}
	return livres;
}


Intv libertaV1(Intv livres, int lugar, int n){

	int sup = lugar+n;
	Intv lRun = livres, laux= NULL;

	while(lRun && sup > lRun->fst && lRun->lst != lugar){
		laux = lRun;
		lRun = lRun->prox;
	}

	if(lRun){
		if(sup == lRun->fst-1) lRun->fst = lugar;
		else if(lRun->lst == lugar) lRun->lst = sup;
		else{
			if(laux){
				laux->prox = (Intv)malloc(sizeof(struct intv)); 
				laux = laux->prox;
				laux->prox = lRun;
			}
			else{
				laux = (Intv)malloc(sizeof(struct intv)); 
				laux->prox = livres;
				livres = laux;
			}
			laux->fst = lugar;
			laux->lst = sup;
		}

	}else{
		laux->prox = (Intv)malloc(sizeof(struct intv)); 
		laux = laux->prox;
		laux->fst = lugar;
		laux->lst = sup;
		laux->prox = NULL;
	}
	return livres;
}

int reservaV2(Intv* livres, int n){

	int r = -1, excess = 65535, disp;
	Intv *laux = livres, *lR = NULL, lRAux;

	while(*laux && excess != 0){
		disp = (*laux)->lst - (*laux)->fst;
		if(disp >= n && disp-n < excess){
			excess = disp - n;
			lR = laux;
		}
		laux = &((*laux)->prox);
	}

	if(lR){
		r = (*lR)->lst - n;
		if(excess == 0){
			lRAux = *lR;
			*lR = (*lR)->prox;
			free(lRAux); 
		}else (*lR)->lst -= n;
	}
	return r;
}

void libertaV2(Intv *livres, int lugar, int n){

	int sup = lugar+n;
	Intv *laux = livres, laux2;

	while(*laux && (*laux)->fst < sup && (*laux)->lst != lugar)
		laux = &((*laux)->prox);

	if(*laux){
		if(sup == (*laux)->fst-1) (*laux)->fst = lugar;
		else if(lugar == (*laux)->lst) (*laux)->lst = sup;
		else{
			laux2 = *laux;
            laux2 = (Intv)malloc(sizeof(struct intv));
            laux2->fst = lugar;
            laux2->lst = sup;
            laux2->prox = *laux;
            if(laux == livres) *livres = laux2;
            else *laux = laux2;
		}
	}
}
