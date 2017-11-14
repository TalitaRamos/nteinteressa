#include "anasin.h"


void erroSintatico(char erro[]){

    printf("\nERRO na Linha %d: %s", linhas, erro);

    system("pause");
    exit(1);
}

/*OK*/
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

/*OK*/
void termo(){

    fator();
    printf("\nTo em termo sai de fator");

    //Se o proximo token for um sinal
    if(tknext.categoria == SN){

        //E Se esse proximo token for * / ou &&
        if(tknext.cod == MULT || tknext.cod == DIV || tknext.cod == AND){
            analex();
            while(1){
                analex();
                fator();
                if(!(tknext.cod == MULT || tknext.cod == DIV || tknext.cod == AND)){
                    break;
                }
                analex();

            }//fim-while

        }//fim-E Se esse proximo token for * / ou &&
        else{
            //erroSintatico("É esperado um operador *, / ou AND");
        }

    }//fimSe o proximo token for um sinal
}


/*OK*/
int fator(){
    /*Se for Inteiro, Real ou Caractere*/
    if(tk.categoria == CT_I || tk.categoria == CT_R || tk.categoria == CT_C  || tk.categoria == CT_LT){
        printf("\ninttcon realcon caraccon cadeiacon");
        return 1;
    }

    /*Se for ID*/
    else if(tk.categoria == ID){

        if(tknext.categoria == SN && tknext.cod != PARENTESIS_ABRE){
            //Se for somente ID
            printf("\nsomente id");
            return 1;
        }

        //Ve o proximo token
        analex();

        //Se for abrir parentesis
        if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

            //Se o próximo token for fecha parentesis
            if(tknext.categoria == SN && tknext.cod ==  PARENTESIS_FECHA){

                //Ve o proximo token e sai
                printf("\nsomente e parentesis");
                analex();
                return 1;
            }

            //Chama a função de expressÃ£o
            analex();
            expr();

            //Se o proximo token for um sinal
            if(tknext.categoria == SN){
                //E Se esse proximo token for VIRG
                if(tknext.cod == VIRG){
                    analex();
                    while(1){
                        analex();
                        expr();
                        if(!(tknext.cod == VIRG)){
                            break;
                        }
                        analex();

                    }//fim-while

                }//fim-E Se esse proximo token for VIRG
            }//fimSe o proximo token for um sinal

            analex();
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
    else if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){
        printf("\nEntrei no (expr)");
        analex();
        expr();

        analex();
        //If para checar se houve fechar parentesis
        if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
            //Erro faltando parentesis
            erroSintatico("Falta fecha parentesis");
        }

        return 1;
    }


    /* Se for negação de expressão */
    else if(tk.categoria == SN && tk.cod == NEGACAO){
        analex();
        fator();
    }
    else{
        erroSintatico("Era esperador fator");
    }

    return 0;

}


/*OK*/
void expr(){

    expr_simp();

    if(tknext.categoria == SN){
        //se o proximo token for op relacional
        if(tknext.cod == COMPARA || tknext.cod == DIFERENTE || tknext.cod == MAIOR_Q || tknext.cod == MENOR_Q || tknext.cod == MAIOR_IG || tknext.cod == MENOR_IG){
            analex();
            opr_rel();
            analex();
            expr_simp();

        }//fim-se o proximo token for op relacional
        else{
            //Erro, esperando operador relacional
            //erroSintatico("Falta operador relacional");
        }
    }
}


/*OK*/
void expr_simp()
{
    /*Se o termo começar com + ou - */
    if(tk.categoria == SN)
    {
        if(tk.cod == SOMA || tk.cod == SUB)
        {

            analex();
            termo();

            //Se o proximo token for um sinal
            if(tknext.categoria == SN){
                //E Se esse proximo token for + - ou &||
                if(tknext.cod == SOMA || tknext.cod == SUB || tknext.cod == OR){
                    analex();
                    while(1){
                        analex();
                        termo();
                        if(!(tknext.cod == SOMA || tknext.cod == SUB || tknext.cod == OR)){
                            break;
                        }
                        analex();

                    }//fim-while

                }//fim-E Se esse proximo token for + - ou &||
                else{
                    //erroSintatico("É esperando um operador +, - ou OR");
                }
            }//fim-Se o proximo token for um sinal

        }else{//else da categoria


            /*ERRO NO TIPO DE OPERADOR USADO*/
            erroSintatico("É esperado + ou -");


        }//else

    }else{

        termo();

        //Se o proximo token for um sinal
        if(tknext.categoria == SN){
            //E Se esse proximo token for + - ou &||
            if(tknext.cod == SOMA || tknext.cod == SUB || tknext.cod == OR){
                analex();
                while(1){
                    analex();
                    termo();
                    if(!(tknext.cod == SOMA || tknext.cod == SUB || tknext.cod == OR)){
                        break;
                    }
                    analex();

                }//fim-while

            }//fim-E Se esse proximo token for + - ou &||
            else{
                //erroSintatico("É esperando um operador +, - ou OR");
            }
        }//fim-Se o proximo token for um sinal

    }// else do SN

}//VOID


/*OK*/
int tipo(){

    //Se for palavra reservada
    if(tk.categoria == PR){

        if(tk.cod == CARACTER){
            return tk.cod;
        }else if(tk.cod == INTEIRO){
            return tk.cod;
        }else if(tk.cod == REAL){
            return tk.cod;
        }else if(tk.cod = BOOLEANO){
            return tk.cod;
        }else{
            return -1;
        }

        /*
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
        */

    }//FIM-se for PR
    return -1;
}

/*OK*/
void tipos_param(){

    //Se for palavra reservada
    if(tk.categoria == PR && tk.cod == SEMPARAM){
        //Se a palavra reservada for semparam
        return;
    }
    else{
        //SE FOR TIPO
        if(tipo()>0){
        printf("\n Tipos_param - É tipo!");
        analex();

            //se for id
            if(tk.categoria == ID){

                //Se nÃ£o houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);

                    //E Se esse proximo token for VIRG
                    if(tknext.categoria == SN && tknext.cod == VIRG){
                        analex();
                        while(1){
                            analex();
                            //Se for tipo
                            if(tipo()>0){
                                analex();
                                //Se for ID
                                if(tk.categoria == ID){
                                    if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                        controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);
                                    }else{
                                        erroSintatico("ID já existente");
                                    }
                                }//Fim-Se for ID
                                else{
                                    erroSintatico("ID inválido");
                                }

                            }//Fim-Se for tipo
                            else{
                                erroSintatico("Tipo inválido");
                            }


                            if(!(tknext.categoria == SN && tknext.cod == VIRG)){
                                break;
                            }
                            analex();

                        }//fim-while

                    }//fim-E Se esse proximo token for VIRG
                    else if(tknext.categoria == ID || tknext.categoria == PR){
                        erroSintatico("É esperado virgula");
                    }

                }else{
                    //Erro id jÃ¡ existente na tabela
                    erroSintatico("ID já existente na tabela");
                }

            }//fim-se for id
            else{
                //Esperado id
                erroSintatico("Era esperado ID");
            }

        }//fim-tipo
        else{
            //erro sintÃ¡tico TIPO INVALIDO
            erroSintatico("Tipo invalido");
        }

    }//FIM-ELSE PR

}


/*OK*/
void tipos_p_opc(){

    //Se for palavra reservada
    if(tk.categoria == PR && tk.cod == SEMPARAM){
        //Se a palavra reservada for semparam
        return;
    }
    else{
        //SE FOR TIPO
        if(tipo()>0){

            printf("\n Tipos_param_opc - É tipo!");

            //Se o próximo token for ID
            if(tknext.categoria == ID){
                //Pega esse token
                analex();
                //Se não já existir na tabela
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);


                }
                else{
                    //Erro id ja¡ existente na tabela
                    erroSintatico("ID já existente na tabela");
                }
            }//fim-Se o próximo token for ID

            //Se o próximo token for vírgula, tem que entrar no while
            else if(tknext.categoria == SN && tknext.cod == VIRG){
                //Ta na virgula
                analex();
                while(1){
                    analex();
                    //Se for tipo
                    if(tipo()>0){

                        //Se o próximo token for ID
                        if(tknext.categoria == ID){
                            //Pega esse token
                            analex();
                            //Se não já existir na tabela
                            if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);

                            }//fimSe não já existir na tabela
                            else{
                                //Erro id ja¡ existente na tabela
                                erroSintatico("ID já existente na tabela");
                            }
                        }//fim-Se o próximo token for ID


                    }//Fim-Se for tipo
                    else{
                        erroSintatico("Tipo inválido");
                    }

                    if(!(tknext.categoria == SN && tknext.cod == VIRG)){
                        break;
                    }
                    analex();

                }//fim-while


            }//Fim-Se o próximo token for vírgula

            //Se o próximo token não for virgula nem tipo
            else if(tipo()<0 && !(tknext.categoria == SN && tknext.cod == VIRG)){
                erroSintatico("É esperado ID ou TIPO");
            }

        }//fim-tipo
        else{
            //erro sintÃ¡tico TIPO INVALIDO
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

        analex();
        analex();

        imprimirTK(tk);
        imprimirTK(tknext);

        tipos_p_opc();


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










