#include "analex.h"
#include "anasin.h"
#include "controlador_tab.h"

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

/*FunÃ§Ã£o que pega um token a frente da leitura para verificaÃ§Ã£o*/
token next_token()
{
    token tk;
    tk = Analisador_lexico();
    return tk;
}


int fator(){
    /*Se for Inteiro, Real ou Caractere*/
    if(tk.categoria == CT_I || tk.categoria == CT_R || tk.categoria == CT_C ){
        return 1;
    }

    /*Se for ID*/
    if(tk.categoria == ID){
        analex();

        //Se for abrir parentesis
        if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

            //Chama a função de expressÃ£o
            analex();
            expr();

            analex();
            //Laço para checar as ocorrencias de vÃ­rgulas e expr consecutivas
            while(1){
                //Se for vÃ­rgula, continua chamando expr
                if(tk.categoria == SN && tk.cod = VIRG){
                    //expr();
                }else{
                    break;
                }
            }//fim-while

            //If para checar se houve fechar parentesis
            if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
                //Erro faltando parentesis
            }

        }//FIM-Se for abrir parentesis
        else{
            return;
        }//FIM-ELSE

        //Se for somente ID
        return 1;

    }//Fim-Se for ID

    /* Se for somente ( expr ) */
    //Checar se houve abre parentesis
    if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

        //Chamar a funÃ§Ã£o expressÃ£o
        //expr();

        //If para checar se houve fechar parentesis
        if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
            //Erro faltando parentesis
        }
    }


    /* Se for NEGAÃ‡ÃƒO de expressÃ£o */
    if(tk.categoria == SN && tk.cod == NEGACAO){
        fator();
    }

}



/*Mexi aqui*/
void expr(){

    expr_simp();

    if(tknext.categoria == SN){
        //se o proximo token for op relacional
        if(tknext.cod == COMPARA || tknext.cod == DIFERENTE || tknext.cod == MAIOR_Q || tknext.cod == MENOR_Q || tknext.cod == MAIOR_IG || tknext.cod == MENOR_IG){
            analex();
            op_rel();
            analex();
            expr_simp();

        }//fim-se o proximo token for op relacional
        else{
            //Erro, esperando operador relacional
        }
    }
}


void expr_simp()
{
    /*Se o termo começar com + ou - */
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

                    /*ERRO DE OPERADOR essa categoria Ã© obrigatorio*/

                    break;
                }

            }//While

        }else{//else da categoria


            /*ERRO NO TIPO DE OPERADOR USADO*/


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

                 /*ERRO DE OPERADOR essa categoria Ã© obrigatorio*/

                break;
            }

        }//While

    }// else do SN

}//VOID


int opr_rel()
{
    if(tk.categoria == SN)
    {
        if(tk.cod == COMPARA || tk.cod == DIFERENTE || tk.cod == MAIOR_IG || tk.cod == MAIOR_Q || tk.cod == MENOR_IG || tk.cod == MENOR_Q)
        {
            return 1;
        }
    }

    return 0;
}


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

}

void tipos_param(){

    //Se for palavra reservada
    if(tk.categoria == PR){

        //Se a palavra reservada for semparam
        if(strcmp("semparam", PAL_RESERV[tk.cod])==0){
            return;

        }//fim-se semparam

    }
    else{
        //SE FOR TIPO
        if(tipo()>0){

            //se for id
            if(tk.categoria == ID){

                //Se nÃ£o houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, SIM_ZUMBI);

                    while(1){
                        if(tk.categoria == SN && tk.cod == VIRG){

                            if(tipo()>0){

                                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, SIM_ZUMBI);
                                }else{
                                    //Erro id jÃ¡ existente na tabela
                                }

                            }//fim-tipo
                            else{
                                //ERRO TIPO INVALIDO
                            }

                        }//Fim - se for virgula
                        else{
                            //ERRO nÃ£o tem virguls
                            break;
                        }
                    }//FIM WHILE

                }else{
                    //Erro id jÃ¡ existente na tabela
                }

            }//fim-se for id
            else{
                //Esperado id
            }

        }//fim-tipo
        else{
            //erro sintÃ¡tico TIPO INVALIDO
        }

    }//FIM-ELSE PR


}


/*SOBRE OBS*/
void tipos_p_opc (){
    //Se for palavra reservada
    if(tk.categoria == PR){

        //Se a palavra reservada for semparam
        if(strcmp("semparam", PAL_RESERV[tk.cod])==0){
            return;

        }//fim-se semparam

    }
    else{
        //SE FOR TIPO
        if(tipo()>0){

            //se for id
            if(tk.categoria == ID){

                //Se não houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, SIM_ZUMBI);

                    while(1){
                        if(tk.categoria == SN && tk.cod == VIRG){

                            if(tipo()>0){

                                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, SIM_ZUMBI);
                                }else{
                                    //Erro id já existente na tabela
                                }

                            }//fim-tipo
                            else{
                                //ERRO TIPO INVALIDO
                            }

                        }//Fim - se for virgula
                        else{
                            //ERRO não tem virguls
                            break;
                        }
                    }//FIM WHILE

                }else{
                    //Erro id já existente na tabela
                }

            }//fim-se for id

        }//fim-tipo
        else{
            if(tipo()>0){

                //Se não houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, SIM_ZUMBI);

                    while(1){
                        if(tk.categoria == SN && tk.cod == VIRG){

                            if(tipo()>0){

                            }//fim-tipo
                            else{
                                //ERRO TIPO INVALIDO
                            }

                        }//Fim - se for virgula
                        else{
                            //ERRO não tem virguls
                            break;
                        }
                    }//FIM WHILE
                }

        }//fim-tipo
    }// else
}


/*CORRIGIR ID*/
void atrib(){

    //Esperado ID
	if(tk.categoria == ID){
    //analex();

		//Esperado sinal de atribuição
		if(tk.categoria == SN && tk.cod == ATRIB){
            //analex();
            expr();

		}else{
            //Erro sintático, é esperado sinal de atribuição
		}


	}else{
        //Erro sintático, esperado ID
	}
}


void cmd(){
    if(tk.categoria == PR || tk.categoria == ID || tk.categoria == SN){

        //Se for sinal
        if(tk.categoria == SN){

            switch(tk.codigo){

                case PT_VIRG:
                    analex();
                    break;

                case CHAVES_ABRE:
                    analex();
                    while(tk.categoria != SN && tk.cod!=CHAVES_FECHA){
                        cmd();
                    }
                    analex();
                    break;
                default:
                    /*ERRO DE CATEGORIA*/

            }//fim-switch

        }//if SN

        //Se for palavra reservada
        if(tk.categoria == PR){

            switch(tk.codigo){

                case SE:
                    analex();
                    if(tk.categoria == SN && tk.cod == PARENTESIS_ABRE){
                        analec(); /*OBSERVAR AQUI*/
                        expr();
                        analex();
                        if(tk.categoria == SN && tk.cod == PARENTESIS_FECHA){
                            analex();
                            cmd();
                            /*OBSERVAÇÃO OLHAR DEPOIS A CHAMADA RECURSIVA*/

                        }//if PARENTESIS_FECHA
                        else{
                            //Erro fecha parentesis esperado
                        }

                    }//if PARENTESIS_ABRE
                else {

                    /*ERRO DE NÂO ABERTURA DE PARENTÊSE*/
                }
                    break;

                case SENAO:
                    analex();
                    cmd();
                    break;

                case ENQUANTO:
                    analex();
                    if(tk.categoria == SN && tk.cod == PARENTESIS_ABRE){
                        analex();
                        expr();
                        analex();
                        if(tk.categoria == SN && tk.cod == PARENTESIS_FECHA){
                            analex();
                            cmd();
                        }else{

                            /*ESPERADO FECHA PARENTESE*/
                        }
                    }else {

                        /*ESPERADO ABRE PARENTESE*/
                    }
                    break;

                case PARA:
                    analex();
                    if(tk.categoria == SN && tk.cod == PARENTESIS_ABRE){
                        analex();
                        if(tknext.categoria == ID){
                            analex();
                            atrib();
                            if(tknext.categoria == SN && tk.cod == PT_VIRG)
                            {
                                analex();
                                if(tknext.categoria == SN && tk.cod == PT_VIRG)
                                {
                                    analex();
                                    if(tknext.categoria == ID){
                                        analex();
                                        atrib();
                                    }else if(!(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)){

                                        /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                    }else {
                                        cmd();
                                    }// else Negacao PARENTESIS_FECHA

                                    //}// else ID OLHAR ISSO
                            }else{
                                analex();
                                expr();
                                if(tknext.categoria == SN && tk.cod == PT_VIRG)
                                {
                                    analex();
                                    if(tknext.categoria == ID){
                                        analex();
                                        atrib();
                                    }else if(!(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)){

                                        /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                    }else
                                    {
                                        cmd();
                                    }// else da negacao de FECHA_PARENTESE

                                    //}// else ID
                            } else
                                {
                                    /*ERRO POR FALTA DE PONTO VIRGULA*/

                                }// else do PT_VIRG expre

                            }// else if PT_VIRG

                            }//if PT_VIRG

                        }else {
                            /*Verifica quando não existir atrib*/
                            if(tknext.categoria == SN && tk.cod == PT_VIRG)
                            {
                                analex();
                                if(tknext.categoria == SN && tk.cod == PT_VIRG)
                                {
                                    analex();
                                    if(tknext.categoria == ID){
                                        analex();
                                        atrib();
                                    }else if(!(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)){

                                        /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                    }else {
                                        cmd();
                                    }// else Negacao PARENTESIS_FECHA

                                 }else{

                                }//else do segundo PT_VIRG
                            }else{
                                analex();
                                expr();
                                if(tknext.categoria == SN && tk.cod == PT_VIRG)
                                {
                                    analex();
                                    if(tknext.categoria == ID){
                                        analex();
                                        atrib();
                                    }else if(!(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)){

                                        /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                    }else
                                    {
                                        cmd();
                                    }// else da negacao de FECHA_PARENTESE



                        }// else ID

                    }//if PARENTESIS_ABRE


                    }else{

                        /* ERRO ESPERAVA-SE ABRE PARENTESE*/

                    }//else PARENTESIS_ABRE

                    break;

                case RETORNE:
                    analex();
                    if(!(tk.categoria == SN && tk.cod == PT_VIRG)){
                        expr();
                        analex();
                        if(tk.categoria == SN && tk.cod == PT_VIRG){

                        }else{

                            /*ERRO ESPERAVA-SE UM PONTO E VIRGULA*/

                        }
                    }

                    break;

                default:

                /*ERRO de comando não esperado*/


            }//switch


        }//if categoria


    }//If PR ou ID ou SN
}//void



























