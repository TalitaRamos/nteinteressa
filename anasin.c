#include "analex.h"
#include "anasin.h"
#include "controlador_tab.h"

void termo()
{
    fator();
    while(1)
    {
        if(tk.categoria == SN)
        {
            if(tk.cod == MULT || tk.cod == DIV || tk.cod == AND)
            {
                fator();
            } else {
                break;
            }
        }
    }
}

/*Fun��o que pega um token a frente da leitura para verifica��o*/
Token next_token()
{
    Token tk;
    tk = Analisador_lexico();
    return tk;
}


void fator(){
    /*Se for Inteiro, Real ou Caractere*/
    if(tk.Categoria == CT_I || tk.categoria == CT_R || tk.categoria == CT_C ){
        return;
    }

    /*Se for ID*/
    if(tk.categoria == ID){

        //Se for abrir parentesis
        if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

            //Chama a fun��o de express�o
            //expr();

            //La�o para checar as ocorrencias de v�rgulas e expr consecutivas
            while(1){
                //Se for v�rgula, continua chamando expr
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


    }//Fim-Se for ID

    /* Se for somente ( expr ) */
    //Checar se houve abre parentesis
    if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

        //Chamar a fun��o express�o
        //expr();

        //If para checar se houve fechar parentesis
        if(!(tk.categoria == SN && tk.cod == PARENTESIS_FECHA)){
            //Erro faltando parentesis
        }
    }


    /* Se for NEGA��O de express�o */
    if(tk.categoria == SN && tk.cod == NEGACAO){
        fator();
    }

}



/*Mexi aqui*/
void expr()
{
    Token next_tk;

    expr_simp();
    next_tk = next_token();/*pega um token na frente para olhar se � um op_rel ou fim da exp_simp*/
    if(next_tk.categoria == SN)/*Se for um sinal eu verifico se � um op_rel, se n�o ele sai por vazio*/
    {
        op_rel();
        expr_simp();
    } else return; /*Sai por vazio*/
}


void expr_simp()
{
    /*Se o termo come�ar com + ou - */
    if(tk.categoria == SN)
    {
        if(tk.cod == SOMA || tk.cod == SUB)
        {
            termo();
            /*While se houver mais e 1 termo*/
            while(1)
            {
                if(tk.cod == SOMA || tk.cod == SUB || tk.cod == OR)
                {
                    termo();
                }else{

                    /*ERRO DE OPERADOR essa categoria � obrigatorio*/

                    break;
                }

            }//While

        }else{//else da categoria


            /*ERRO NO TIPO DE OPERADOR USADO*/


        }//else

    }else{

        termo();
        /*While se houver mais e 1 termo*/
        while(1)
        {
            if(tk.cod == SOMA || tk.cod == SUB || tk.cod == OR)
            {
                termo();
            }else{

                 /*ERRO DE OPERADOR essa categoria � obrigatorio*/

                break;
            }

        }//While

    }// else do SN

}//VOID


int opr_rel()
{
    if(tk.categoria == SN)
    {
        if(tk.categoria == COMPARA || tk.categoria == DIFERENTE || tk.categoria == MAIOR_IG || tk.categoria == MAIOR_Q || tk.categoria == MENOR_IG || tk.categoria == MENOR_Q)
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

                //Se n�o houver o ID na tabela, ele insere
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, NAO_ZUMBI);

                    while(1){
                        if(tk.categoria == SN && tk.cod == VIRG){

                            if(tipo()>0){

                                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                    controlador_TabSimb(EMPILHAR, tk.lexema, LOCAL, PARAM, NAO_ZUMBI);
                                }else{
                                    //Erro id j� existente na tabela
                                }

                            }

                        }else{
                            //ERRO n�o tem virguls
                            break;
                        }
                    }



                }else{
                    //Erro id j� existente na tabela
                }

            }//fim-se for id

        }//fim-tipo
        else{
            //erro sint�tico
        }

    }//FIM-ELSE PR


}

