#ifndef CONTROLADOR_TAB_H
#define CONTROLADOR_TAB_H
#define TAM_LEXEMA 1000
#define TAM_TABSIMB 1000
#define VERDADEIRO 1
#define FALSO 0

/*Estrutura da Tabela*/
typedef struct linhaTabSimb{
    int i; //N�mero da linha da tabela
    char lexema[TAM_LEXEMA];
    int tipo; //INT, FLOAT, CHAR, ETC...
    int escopo; //Global ou Local
    int categoria; //Fun��o, Parametro, Variavel
    int zumbi; //Flag
}Linha_TabSimb;

/*Enum para deixar o c�digo claro */
enum{EMPILHAR = -2, IGNORE = -3, DESEMPILHAR = -4, CONSULTAR = -5} operations;
enum{LOCAL = -6, GLOBAL = -7}escopo;
enum{SIM_ZUMBI = 1, NAO_ZUMBI = 0}zumbi;
enum{FUNC = -10, PARAM = -11, VAR = -12}categoria;

/*Declara��es Globais*/
Linha_TabSimb tabela[TAM_TABSIMB];
int topo;

/*Assinatura das Fun��es*/
int controlador_TabSimb(int operation, char lexema[], int tipo, int escopo, int categoria, int zumbi);
void empilhar(char lexema[], int tipo, int escopo, int categoria, int zumbi);
void desempilhar();
int consultar(char lexema[], int escopo);
void imprimirTabela();

#endif
