#ifndef _ANASIN_H
#define _ANASIN_H
#include "analex.h"
#include "controlador_tab.h"

enum{
	BOOLEANO=0,
	CARACTER,
	DIGITO,
	ENQUANTO,
	IDPAL,
	INTCON,
	INTEIRO,
	LETRA,
	PARA,
	PRINCIPAL,
	PROTOTIPO,
	REAL,
	REALCON,
	RETORNE,
	SE,
	SEMRETORNO,
	SEMPARAM,
	SENAO
}PalavrasReservadas;

/*Assinatura de Funções*/
void erroSintatico(char erro[]);
void termo();
int fator();
void expr();
void expr_simp();
int opr_rel();
int tipo();
void tipos_param();

#endif
