typedef struct intv{

	int fst, lst;
	struct intv *prox;

}*Intv;

Intv reservaV1(Intv livres, int n, int* reservado);
Intv libertaV1(Intv livres, int lugar, int n);
int reservaV2(Intv* livres, int n);
void libertaV2(Intv* livres, int lugar, int n);
