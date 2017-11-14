#include "anasin.h"


void erroSintatico(char erro[]){

    printf("\nERRO na Linha %d: %s", linhas, erro);

    system("pause");
    exit(1);
}

int opr_rel()
{
    if(tk.categoria == SN)
    {
        if(tk.cod == COMPARA || tk.cod == DIFERENTE || tk.cod == MAIOR_IG || tk.cod == MAIOR_Q || tk.cod == MENOR_IG || tk.cod == MENOR_Q)
        {
            return 1;
        }else{
            erroSintatico("Esperado operador relacional");
        }
    }else{
        erroSintatico("Esperado sinal");
    }

    return 0;
}

void termo(){
    fator();

    while(1){
        if(tk.categoria == SN)
        {
            if(tk.cod == MULT || tk.cod == DIV || tk.cod == AND)
            {
                analex();
                fator();
            } else {
                break;
            }
        }
    }
}

int fator(){
    /*Se for Inteiro, Real ou Caractere*/
    if(tk.categoria == CT_I || tk.categoria == CT_R || tk.categoria == CT_C ){
        return 1;
    }

    /*Se for ID*/
    if(tk.categoria == ID){

        if(tknext.cod != PARENTESIS_ABRE){
            //Se for somente ID
            return 1;
        }

        //Ve o proximo token
        analex();

        //Se for abrir parentesis
        if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

            //Se o prÛximo token for fecha parentesis
            if(tknext.categoria == SN && tknext.cod ==  PARENTESIS_FECHA){

                //Ve o proximo token e sai
                analex();
                return 1;
            }

            //Chama a funÁ„o de express√£o
            analex();
            expr();

            analex();

            //LaÁo para checar as ocorrencias de v√≠rgulas e expr consecutivas
            while(1){
                //Se for vÌrgula, continua chamando expr
                if(tk.categoria == SN && tk.cod == VIRG){
                    analex();
                    expr();
                    analex();
                }else{
                    break;
                }
            }//fim-while

            //If para checar se houve fechar parentesis
            if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
                //Erro faltando parentesis
                erroSintatico("Falta fecha parentesis");
            }

            return 1;

        }//FIM-Se for abrir parentesis
        else{
            //ERRO FALTANDO FECHAR PARENTESIS
            erroSintatico("Falta fecha parentesis");
        }//FIM-ELSE

    }//Fim-Se for ID

    /* Se for somente ( expr ) */
    //Checar se houve abre parentesis
    if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

        analex();
        expr();

        //If para checar se houve fechar parentesis
        if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
            //Erro faltando parentesis
            erroSintatico("Falta fecha parentesis");
        }

        return 1;
    }


    /* Se for negaÁ„o de express„o */
    if(tk.categoria == SN && tk.cod == NEGACAO){
        analex();
        fator();
    }

    return 0;

}


/*Mexi aqui*/
void expr(){

    expr_simp();

    if(tknext.categoria == SN){
        //se o proximo token for op relacional
        if(tknext.cod == COMPARA || tknext.cod == DIFERENTE || tknext.cod == MAIOR_Q || tknext.cod == MENOR_Q || tknext.cod == MAIOR_IG || tknext.cod == MENOR_IG){
            analex();
            analex();
            expr_simp();

        }//fim-se o proximo token for op relacional
        else{
            //Erro, esperando operador relacional
            erroSintatico("Falta operador relacional");
        }
    }
}


void expr_simp()
{
    /*Se o termo comeÁar com + ou - */
    if(tk.categoria == SN)
    {

        if(tk.cod == SOMA || tk.cod == SUB)
        {
            analex();
            termo();
            /*While se houver mais e 1 termo*/
            while(1)
            {
                if(tk.cod == SOMA || tk.cod == SUB || tk.cod == OR)
                {
                    analex();
                    termo();
                }else{

                    /*ERRO DE OPERADOR essa categoria √© obrigatorio*/
                    erroSintatico("Falta operador");

                    break;
                }

            }//While

        }else{//else da categoria


            /*ERRO NO TIPO DE OPERADOR USADO*/
            erroSintatico("Tipo de operador incorreto");


        }//else

    }else{

        analex();
        termo();
        /*While se houver mais e 1 termo*/
        while(1)
        {
            if(tk.cod == SOMA || tk.cod == SUB || tk.cod == OR)
            {
                analex();
                termo();
            }else{

                 /*ERRO DE OPERADOR essa categoria √© obrigatorio*/
                 erroSintatico("Falta operador");

                break;
            }

        }//While

    }// else do SN

}//VOID



int tipo(){

    //Se for palavra reservada
    if(tk.categoria == PR){

        if(strcmp("caracter", PAL_RESERV[tk.cod])==0){
            return tk.cod;
        }else if(strcmp("inteiro", PAL_RESERV[tk.cod])==0){
            return tk.cod;
        }else if(strcmp("real", PAL_RESERV[tk.cod])==0){
            return tk.cod;
        }else if(strcmp("booleano", PAL_RESERV[tk.cod])==0){
            return tk.cod;
        }else{
            return -1;
        }

    }//FIM-se for PR
    return -1;
}

void tipos_param(){

    //Se for palavra reservada
    if(tk.categoria == PR){

        //Se a palavra reservada for semparam
        if(tk.cod == SEMPARAM){
            return;

        }//fim-se semparam

    }
    else{
        //SE FOR TIPO
        if(tipo()>0){
        analex();

            //se for id
            if(tk.categoria == ID){

                //Se n√£o houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);

                    analex();

                    while(1){
                        if(tk.categoria == SN && tk.cod == VIRG){

                            analex();

                            if(tipo()>0){

                                analex();

                                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                    controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);
                                }else{
                                    //Erro id j√° existente na tabela
                                    erroSintatico("ID j· existente na tabela");
                                }

                            }//fim-tipo
                            else{
                                //ERRO TIPO INVALIDO
                                erroSintatico("Tipo invalido");
                            }

                        }//Fim - se for virgula
                        else{
                            //ERRO n√£o tem virguls
                            erroSintatico("Esperado virgula");
                            break;
                        }
                    }//FIM WHILE

                }else{
                    //Erro id j√° existente na tabela
                    erroSintatico("ID j· existente na tabela");
                }

            }//fim-se for id
            else{
                //Esperado id
                erroSintatico("Era esperado ID");
            }

        }//fim-tipo
        else{
            //erro sint√°tico TIPO INVALIDO
            erroSintatico("Tipo invalido");
        }

    }//FIM-ELSE PR


}

int main(){

    char nomeArquivo[1000];

    printf("\n\tDigite o nome do arquivo de teste: "); scanf("%s", nomeArquivo);

    //ABRE O ARQUIVO
	if ( (arquivo = fopen(nomeArquivo,"r")) != NULL ){
        printf("\n\tArquivo aberto com sucesso!\n");

        //chamar o analisador sintatico

        analex();
        analex();

        imprimirTK2(tk);
        imprimirTK2(tknext);

        //tk = analisadorLexico();
        //tknext = analisadorLexico();

        //imprimirTK(tk);
        //imprimirTK(tknext);


        /*while(1){
            tk = analisadorLexico();
            imprimirTK(tk);
            tknext = analisadorLexico();
            imprimirTK(tknext);

            tk=tknext;
            imprimirTK(tk);

        }*/

        //opr_rel();



        fclose(arquivo);
    }
    else{
        printf("\n\tN„o foi possÌvel abrir o arquivo %s\n", nomeArquivo);
        system("pause");
        exit(1);
    }
    //FIM-ABRE O ARQUIVO

    system("pause");
    return 0;
}










