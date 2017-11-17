void progteste(){
    int guardarTipo;

    //Espera pelo abre chaves
    if(tknext.categoria == SN && tknext.cod == CHAVES_ABRE){
        analex(); //ta no abre chaves

        //Se depois vier um fecha chaves, retorna
        if(tknext.categoria == SN && tknext.cod == CHAVES_FECHA){
            analex();
             printf("\n{}");
            return;
        }
        //Enquanto tnext for tipo
        while(tknext.categoria == PR && (tknext.cod == CARACTER || tknext.cod == INTEIRO || tknext.cod == REAL ||tknext.cod == BOOLEANO)){
            printf("\nEntrei no while");
            analex();//ta no tipo
            guardarTipo = tipo();
            printf("\nTo no tipo");
            //Se o próximo token for ID
            if(tknext.categoria == ID){
                analex();//tá no id

                //Insere ID na tabela
                if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                    controlador_TabSimb(EMPILHAR, tk.lexema, guardarTipo, LOCAL, VAR, NAO_ZUMBI);
                }else{
                    erroSintatico("ID já existente");
                }

                printf("\nTo no id");

                //Enquanto TNEXT for vírgula
                while(tknext.categoria == SN && tknext.cod == VIRG){
                    printf("\nEntrei no while2");
                    analex();//Pra pegar a virgula
                    if(tknext.categoria != ID){
                        erroSintatico("Eh esperado ID após virgula");
                    }
                    analex();//pra pegar o ID

                    //Insere ID na tabela
                    if(!controlador_TabSimb(CONSULTAR, tk.lexema, 0, LOCAL, 0, 0)){
                        controlador_TabSimb(EMPILHAR, tk.lexema, guardarTipo, LOCAL, VAR, NAO_ZUMBI);
                    }else{
                        erroSintatico("ID já existente");
                    }

                    if(!(tknext.categoria == SN && tknext.cod == VIRG) && !(tknext.categoria == SN && tknext.cod == PT_VIRG)){
                        erroSintatico("Eh esperado virgula ou PT_VIRG apos id");
                    }
                }

                if(!(tknext.categoria == SN && tknext.cod == PT_VIRG)){
                    erroAnalisadorLexico("É esperado PT_VIRG");
                }
                analex(); //pergou pt e virgula
                printf("\nPeguei o ponto e virgula");

            }//Fim-se tknext for id
            else{
                erroAnalisadorLexico("Após tipo é esperado ID");
            }


        }//fim-Enquanto tnext for tipo

        //chamar CMD
        printf("\nTalvez ocorra cmd");
        while(!(tknext.categoria == SN && tknext.cod == CHAVES_FECHA)){
            analex();
            printf("\nvai ocorrer cmd");
            cmd();
        }

        //Apos encontrar o fecha chaves, desempilha a tabela de sinais
        desempilhar();

    }

}
