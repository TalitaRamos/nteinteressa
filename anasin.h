#ifndef ANASIN_H
#define ANASIN_H



/*Assinatura de Funções*/
void termo();
token next_token();
void fator();
void expr();
void expr_simp();
int opr_rel();
int tipo();
void tipos_param();
void tipos_p_opc();

enum{
	BOOLEANO,
	CARACTER,
	DIGITO,
	ENQUANTO,
	ID,
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

//Variáveis globais
extern token tk, tknext;

#endif
