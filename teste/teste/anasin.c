#include "anasin.h"


void erroSintatico(char erro[]){

    printf("\nERRO SINT�TICO na Linha %d: %s", linhas, erro);

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
            //erroSintatico("� esperado um operador *, / ou AND");
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

        if(!(tknext.categoria == SN && tknext.cod == PARENTESIS_ABRE)){
            //Se for somente ID
            printf("\nsomente id");
            return 1;
        }

        //Ve o proximo token
        analex();

        //Se for abrir parentesis
        if(tk.categoria == SN && tk.cod ==  PARENTESIS_ABRE){

            //Se o pr�ximo token for fecha parentesis
            if(tknext.categoria == SN && tknext.cod ==  PARENTESIS_FECHA){

                //Ve o proximo token e sai
                printf("\nsomente e parentesis");
                analex();
                return 1;
            }

            //Chama a fun��o de expressão
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


    /* Se for nega��o de express�o */
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
    /*Se o termo come�ar com + ou - */
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
                    //erroSintatico("� esperando um operador +, - ou OR");
                }
            }//fim-Se o proximo token for um sinal

        }else{//else da categoria


            /*ERRO NO TIPO DE OPERADOR USADO*/
            erroSintatico("� esperado + ou -");


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
                //erroSintatico("� esperando um operador +, - ou OR");
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
        printf("\n Tipos_param - � tipo!");
        analex();

            //se for id
            if(tk.categoria == ID){

                //Se não houver o ID na tabela, ele insere
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
                                        erroSintatico("ID j� existente");
                                    }
                                }//Fim-Se for ID
                                else{
                                    erroSintatico("ID inv�lido");
                                }

                            }//Fim-Se for tipo
                            else{
                                erroSintatico("Tipo inv�lido");
                            }


                            if(!(tknext.categoria == SN && tknext.cod == VIRG)){
                                break;
                            }
                            analex();

                        }//fim-while

                    }//fim-E Se esse proximo token for VIRG
                    else if(tknext.categoria == ID || tknext.categoria == PR){
                        erroSintatico("� esperado virgula");
                    }

                }else{
                    //Erro id já existente na tabela
                    erroSintatico("ID j� existente na tabela");
                }

            }//fim-se for id
            else{
                //Esperado id
                erroSintatico("Era esperado ID");
            }

        }//fim-tipo
        else{
            //erro sintático TIPO INVALIDO
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

            printf("\n Tipos_param_opc - � tipo!");

            //Se o pr�ximo token for ID
            if(tknext.categoria == ID){
                //Pega esse token
                analex();
                //Se n�o j� existir na tabela
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);


                }
                else{
                    //Erro id ja� existente na tabela
                    erroSintatico("ID j� existente na tabela");
                }
            }//fim-Se o pr�ximo token for ID

            //Se o pr�ximo token for v�rgula, tem que entrar no while
            else if(tknext.categoria == SN && tknext.cod == VIRG){
                //Ta na virgula
                analex();
                while(1){
                    analex();
                    //Se for tipo
                    if(tipo()>0){

                        //Se o pr�ximo token for ID
                        if(tknext.categoria == ID){
                            //Pega esse token
                            analex();
                            //Se n�o j� existir na tabela
                            if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                                controlador_TabSimb(EMPILHAR, tk.lexema, tk.cod, LOCAL, PARAM, SIM_ZUMBI);

                            }//fimSe n�o j� existir na tabela
                            else{
                                //Erro id ja� existente na tabela
                                erroSintatico("ID j� existente na tabela");
                            }
                        }//fim-Se o pr�ximo token for ID


                    }//Fim-Se for tipo
                    else{
                        erroSintatico("Tipo inv�lido");
                    }

                    if(!(tknext.categoria == SN && tknext.cod == VIRG)){
                        break;
                    }
                    analex();

                }//fim-while


            }//Fim-Se o pr�ximo token for v�rgula

            //Se o pr�ximo token n�o for virgula nem tipo
            else if(tipo()<0 && !(tknext.categoria == SN && tknext.cod == VIRG)){
                erroSintatico("� esperado ID ou TIPO");
            }

        }//fim-tipo
        else{
            //erro sintático TIPO INVALIDO
            erroSintatico("Tipo invalido");
        }

    }//FIM-ELSE PR

}


/*EM TESTES*/
void atrib(){

    //Se  for ID
    if(tk.categoria == ID){
        //N�o sei se precisa consultar a tabela
        analex();

        //Se for um sinal de atribui��o
        if(tk.categoria == SN && tk.cod == ATRIB){

            analex();
            expr();

        }//fim-Se for um sinal de atribui��o
        else{
            erroSintatico("� esperado um sinal de atribui��o");
        }

    }//fim- se for id
    else{
        erroSintatico("� esperado um ID");
    }

}

/*EM TESTES (pt_virg e {cmd} ok)*/
void cmd(){
    if(tk.categoria == PR || tk.categoria == ID || tk.categoria == SN){

        //Se for sinal
        if(tk.categoria == SN){

            switch(tk.cod){

                case PT_VIRG:
                    break;

                case CHAVES_ABRE:
                    while(1){
                        if((tknext.categoria == SN && tknext.cod==CHAVES_FECHA)){
                            analex();
                            break;
                        }
                        analex();
                        cmd();
                    }
                    break;

                default:
                    /*ERRO DE CATEGORIA*/
                    erroSintatico("Sinal inv�lido! � esperado { ou ;");

            }//fim-switch

        }//if SN

        //Se for palavra reservada
        if(tk.categoria == PR){

            switch(tk.cod){

                case SE:
                    analex();
                    if(tk.categoria == SN && tk.cod == PARENTESIS_ABRE){
                        analex(); /*OBSERVAR AQUI*/
                        expr();
                        analex();
                        if(tk.categoria == SN && tk.cod == PARENTESIS_FECHA){
                            analex();
                            cmd();

                            //Saiu de CMD
                            //Se o pr�ximo token for SENAO
                            if(tknext.categoria == PR && tknext.cod == SENAO){
                                analex(); //vai estar em senao
                                analex();
                                cmd();
                            }

                        }//if PARENTESIS_FECHA
                        else{
                            //Erro fecha parentesis esperado
                            erroSintatico("Esperado )");
                        }

                    }//if PARENTESIS_ABRE
                    else {
                        /*ERRO DE N�O ABERTURA DE PARENT�SE*/
                        erroSintatico("Esperado (");
                    }
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
                            erroSintatico("Esperado )");
                        }
                    }else {

                        /*ESPERADO ABRE PARENTESE*/
                        erroSintatico("Esperado (");
                    }
                    break;

                case PARA:
                    analex();
                    if(tk.categoria == SN && tk.cod == PARENTESIS_ABRE)// if 1
                    {
                        analex();
                        if(tknext.categoria == ID) //if 2
                        {
                            analex();
                            atrib();
                            if(!(tknext.categoria == SN && tk.cod == PT_VIRG))//if 7
                            {
                                /*ERRO POR FALTA DE PONTO VIRGULA*/

                            }else{

                                /*SE L� VIRGULA*/
                                analex();
                                if(tknext.categoria == SN && tk.cod == PT_VIRG)//if 8
                                {
                                            analex();
                                            if(tknext.categoria == ID) //if 5
                                            {
                                                analex();
                                                atrib();
                                            }else if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 9
                                            {
                                                analex();// Vai para o )
                                                analex();//Vai para o cmd
                                                cmd();
                                            }else {

                                                /*ERRO POR FALTA DE FECHA PARENTESE*/

                                             }// else 9
                               // }else {


                               // } else{


                                }else{// abre else do if 8

                                           analex();
                                           expr();
                                           if(tknext.categoria == SN && tk.cod == PT_VIRG)//if 11
                                            {
                                                    analex();
                                                    if(tknext.categoria == ID)
                                                    {
                                                        analex();
                                                        atrib();
                                                        if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 12
                                                        {
                                                            cmd();
                                                        }else{

                                                             /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                                        }//fecha else do if 12
                                                    }else if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 14
                                                        {
                                                            cmd();
                                                        }else
                                                        {

                                                            /*ERRO*/

                                                        }// else fecha do else if 14

                                            }else
                                            {
                                                    /*ERRO POR FALAT DE VIRGULA*/

                                            }//fecha else do if 11

                                }// fecha else do if 8

                            }//else do if 7

                        }else if(tknext.categoria == SN && tk.cod == PT_VIRG){// else if do if 2
                            analex();
                            if(tknext.categoria == SN && tk.cod == PT_VIRG)//if 3
                            {
                                                analex();
                                                if(tknext.categoria == ID)
                                                    {
                                                        analex();
                                                        atrib();
                                                        if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 16
                                                        {
                                                            analex();
                                                            cmd();
                                                        }else{

                                                             /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                                        }//fecha else do if 16
                                                    }else if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 18
                                                        {
                                                            analex();
                                                            cmd();
                                                        }else
                                                        {

                                                            /*ERRO*/

                                                        }// else fecha do else if 18




                            }else{
                                           analex();
                                           expr();
                                           if(tknext.categoria == SN && tk.cod == PT_VIRG)//if 11
                                            {
                                                    analex();
                                                    if(tknext.categoria == ID)
                                                    {
                                                        analex();
                                                        atrib();
                                                        if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 12
                                                        {
                                                            analex();
                                                            cmd();
                                                        }else{

                                                             /*ERRO ESPERAVA-SE FECHA PARENTESE*/

                                                        }//fecha else do if 12
                                                    }else if(tknext.categoria == SN && tk.cod == PARENTESIS_FECHA)// if 14
                                                        {
                                                            analex();
                                                            cmd();
                                                        }else
                                                        {

                                                            /*ERRO*/

                                                        }// else fecha do else if 14

                                            }else
                                            {
                                                    /*ERRO POR FALAT DE VIRGULA*/

                                            }//fecha else do if 11





                            }//fecha else do if 3

                        }else
                        {
                            /*ERRO DE TIPO DESCONHECDO*/

                        }// else if 2
                    }else{

                    /* ERRO ESPERAVA-SE ABRE PARENTESE*/

                    }//else if 1


                    break;

                case RETORNE:
                    if(tknext.categoria == SN && tknext.cod == PT_VIRG){
                        analex();
                        break;
                    }

                    //Se n�o entrou no if do pt e virg
                    analex();
                    expr();
                    analex();
                    if(tk.categoria == SN && tk.cod == PT_VIRG){
                        break;
                    }else{
                        erroSintatico("Falta PT_VIRG ;");
                    }
                    break;

                default:
                    /*ERRO de comando n�o esperado*/
                    erroSintatico("Cmd invalido");


            }//switch


        }//if PR

        //SE FOR ID
        if(tk.categoria == ID){


        }//fim- if id


    }//If PR ou ID ou SN
}//void

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

        cmd();


        fclose(arquivo);
    }
    else{
        printf("\n\tN�o foi poss�vel abrir o arquivo %s\n", nomeArquivo);
        system("pause");
        exit(1);
    }
    //FIM-ABRE O ARQUIVO

    printf("\n");
    system("pause");
    return 0;
}










