//#include "anasin.h"
#include "analex.h"
int main(){

    char nomeArquivo[1000];

    printf("\n\tDigite o nome do arquivo: "); scanf("%s", nomeArquivo);

    //ABRE O ARQUIVO
	if ( (arquivo = fopen(nomeArquivo,"r")) != NULL ){
        printf("\n\tArquivo aberto com sucesso!\n");

        //chamar o analisador sintatico

        analex();

        fclose(arquivo);
    }
    else{
        printf("\n\tNão foi possível abrir o arquivo %s\n", nomeArquivo);
        system("pause");
        exit(1);
    }
    //FIM-ABRE O ARQUIVO

    system("pause");
    return 0;
}

