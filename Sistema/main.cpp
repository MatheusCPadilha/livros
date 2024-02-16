#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <cstdlib>
#include <ctype.h>
#include <windows.h>
#include <time.h>

using namespace std;

// VARIAVEIS DO CLIENTE
typedef struct {
    int     codigo;
    char    nomecliente[100];
    char	enderecocliente[100];
    char	bairrocliente[50];
    char	cidadecliente[50];
    char	estadocliente[50];
    int		cepcliente;
    float   numerocasa;
    int		tipocliente;  
    char    dataCadastropessoa[11];
    char    ativo; // 'S'-Sim | 'N'-Nao.
    char    dataAtualizacao[11];
}CLIENTE;

// VARIAVEIS DO LIVRO
typedef struct {
    int     codigo;
    char    titulo[20];
    float   preco;
    float 	estoque;
    char    dataCadastro[11];
    char    ativo; // 'S'-Sim | 'N'-Não.
    char    dataAtualizacao[11];
    char    dataAtt2[11];
    float	att;
    float  estoqueminimo; //alt
}LIVRO;

//VARIAVEIS DA VENDA
typedef struct {
    int     codigo;
    char    titulo[100];
    float   preco;
    float 	estoque;
    char    dataVenda[11];
    char    ativo; // 'S'-Sim | 'N'-Não.
    char    dataAtualizacao[11];
    char    dataAtt2[11];
}VENDA;

char dataSistema[11]={"00/00/0000"};
//---------------------------------------------------------------------------

void mostraMenu(void)
{
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    sprintf(dataSistema,"%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n SISTEMA DE CONTROLE DE CLIENTES                 Data: %s", dataSistema);
    printf("\n---------------------------------------------------------------------------");
    printf("\n                         MENU DE OPCOES DO SISTEMA                         ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n [ 1 ] CADASTRAR LIVRO                    	                             ");
    printf("\n [ 2 ] MOSTRAR TODOS OS LIVROS CADASTRADOS                                 ");
    printf("\n [ 3 ] CADASTRAR CLIENTE                                                   ");
    printf("\n [ 4 ] MOSTRAR TODOS OS CLIENTES CADASTRADOS                               "); 
    printf("\n [ 5 ] ATUALIZAR CADASTRO DE CLIENTE                                       ");
    printf("\n [ 6 ] ATUALIZAR CADASTRO DE LIVRO                                         ");
    printf("\n\n [ 7 ] LANCAR UMA VENDA				                                     ");
    printf("\n\n [ESC] FINALIZAR SISTEMA                                                 ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n INFORME UMA OPCAO >>");
}

//---------------------------------------------------------------------------

int ultimoCodigoClientes()     // Busca o codigo da ultima pessoa cadastrada.
{
    CLIENTE clientes;
    int qtd = 0;
    FILE *pclientes;
    pclientes = fopen("CLIENTE.DAT","rb");
    if (pclientes == NULL)
    {
        qtd = 0;
    }
    else
    {
        fread(&clientes, sizeof(CLIENTE), 1, pclientes);
        while(!feof(pclientes))
        {
            fread(&clientes, sizeof(CLIENTE), 1, pclientes);
            qtd = clientes.codigo;
        }
    }
    fclose(pclientes);
    return qtd;
}

int ultimoCodigoLivro()     // Busca o código do último livro cadastrado.
{
    LIVRO livros;
    int qtd = 0;
    FILE *pLivros;
    pLivros = fopen("LIVROS.DAT","rb");
    if (pLivros == NULL)
    {
        qtd = 0;
    }
    else
    {
        fread(&livros, sizeof(LIVRO), 1, pLivros);
        while(!feof(pLivros))
        {
            fread(&livros, sizeof(LIVRO), 1, pLivros);
            qtd = livros.codigo;
        }
    }
    fclose(pLivros);
    return qtd;
}

int ultimoCodigoVenda()     // Busca o código da ultima venda lancada
{
    VENDA vendas;
    int qtd = 0;
    FILE *pvendas;
    pvendas = fopen("VENDA.DAT","rb");
    if (pvendas == NULL)
    {
        qtd = 0;
    }
    else
    {
        fread(&vendas, sizeof(LIVRO), 1, pvendas);
        while(!feof(pvendas))
        {
            fread(&vendas, sizeof(LIVRO), 1, pvendas);
            qtd = vendas.codigo;
        }
    }
    fclose(pvendas);
    return qtd;
}

//---------------------------------------------------------------------------

void cadastrarClientes()
{
    CLIENTE clientes;

    system("cls");

    printf("\n---------------------------------------------------------------------------");
    printf("\n CADASTRO DE CLIENTES                                                        ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n");

    //printf(" C�DIGO: ");
    //scanf("%d", &livros.codigo);

    clientes.codigo = ultimoCodigoClientes() + 1;
    printf(" CODIGO: [%05d]\n", clientes.codigo);

    fflush(stdin);
    printf(" NOME DO CLIENTE: ");
    gets(clientes.nomecliente);
    
    fflush(stdin);
    printf(" ENDERECO DO CLIENTE: ");
    gets(clientes.enderecocliente);
    
    fflush(stdin);
    printf(" NUMERO DA CASA: ");
    scanf("%f", &clientes.numerocasa);
    
    fflush(stdin);
    printf(" BAIRRO DO CLIENTE: ");
    gets(clientes.bairrocliente);
    
    fflush(stdin);
    printf(" CIDADE DO CLIENTE: ");
    gets(clientes.cidadecliente);
    
    fflush(stdin);
    printf(" CEP DO CLIENTE: ");
    scanf("%f", &clientes.cepcliente);
    
    fflush(stdin);
    printf(" ESTADO DO CLIENTE: ");
    gets(clientes.estadocliente);
    
    fflush(stdin);
    printf(" ESTE CLIENTE, PERTENCE A QUAL GRUPO?\n (1) NORMAL (2) ESTUDANTE\n ");
    scanf("%d", &clientes.tipocliente);

    fflush(stdin);

    strcpy(clientes.dataCadastropessoa,dataSistema);
    printf(" Data de Cadastro: ");
    printf(" [%s]\n", clientes.dataCadastropessoa);

    // Par�metros de manuten��o do registro.
    fflush(stdin);
    clientes.ativo = 'S';

    fflush(stdin);
    strcpy(clientes.dataAtualizacao,"00/00/0000");

    printf("\n\n DESEJA GRAVAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO ] ");

    char tecla = 0x00;
    while (tecla != 27)
    {
        if (kbhit())
        {
            tecla = getch();
            printf("%c", tecla);

            switch(toupper(tecla))
            {
                case 'S' :
                    FILE *pclientes;
                    pclientes = fopen("CLIENTE.DAT","ab");

                    if (pclientes == NULL)
                    {
                        system("cls");
                        printf("\n---------------------------------------------------------------------------");
                        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
                        printf("\n---------------------------------------------------------------------------");
                        getch();
                    }
                    else
                    {
                        fwrite(&clientes, sizeof(CLIENTE), 1, pclientes);
                        fflush(pclientes);
                    }
                    fclose(pclientes);

                    mostraMenu();
                    return;
                break;
                case 'N' : mostraMenu(); return; break;
                case 27  : mostraMenu(); return; break;
            }
        }
    }
}

//---------------------------------------------------------------------------

void mostrarTodosClientes()
{
    CLIENTE clientes;
    int qtd = 0;

    FILE *pclientes;
    pclientes = fopen("CLIENTE.DAT","rb");

    if (pclientes == NULL)
    {
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
        printf("\n---------------------------------------------------------------------------");
        getch();
    }
    else
    {
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n LISTAGEM DE TODOS OS CLIENTES CADASTRADOS                                 ");
        printf("\n---------------------------------------------------------------------------");

        fread(&clientes, sizeof(CLIENTE), 1, pclientes);
        while(!feof(pclientes))
        {
                printf(" \nCODIGO: %05d \t PERTENCE AO GRUPO: %02d",   clientes.codigo, clientes.tipocliente);
                printf(" \nNOME DO CLIENTE: %s",     clientes.nomecliente);
                printf(" \nENDERECO: %s N: %1.0f",     clientes.enderecocliente,clientes.numerocasa);
                printf(" \nBAIRRO: %s",     clientes.bairrocliente);
                printf(" \nCIDADE: %s",     clientes.cidadecliente);
                printf(" \tESTADO: %s",     clientes.estadocliente);
                printf(" \nDATA..: [%s]",   clientes.dataCadastropessoa);
                printf(" \tDATA ULT. ALTERACAO: [%s]", clientes.dataAtualizacao);
                printf(" \nATIVO.: %c\n",     clientes.ativo);

                qtd += 1;

            fread(&clientes, sizeof(CLIENTE), 1, pclientes);
        }
        printf("\n---------------------------------------------------------------------------");
        printf("\n QUANTIDADE DE CLIENTES CADASTRADOS: %05d", qtd);
        printf("\n---------------------------------------------------------------------------");
        getch();
    }

    fclose(pclientes);
}

void atualizarClientes()
{
    unsigned int codigo = 0;
    unsigned int PosicaoInicial = 0;
    unsigned int PosicaoAtual = 0;
    unsigned int PosicaoFinal = 0;

    CLIENTE clientes, clientesTemp;
    FILE *pclientes;

    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n ATUALIZACAO DE CLIENTES                                                     ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n");

    printf(" CODIGO DO REGISTRO A ALTERAR: ");
    scanf("%d", &codigo);

    pclientes = fopen("CLIENTE.DAT","rb+");

    if (pclientes != NULL)
    {
		// Reposiciona o ponteiro do arquivo no início do mesmo para posicionar no registro e buscar as informações.
		rewind(pclientes);
		fseek(pclientes, sizeof(CLIENTE)*(codigo - 1), SEEK_SET);
        fread(&clientes, sizeof(CLIENTE), 1, pclientes);

        // Atribui os dados do registro para alteração dentro de uma struct teporária.
        clientesTemp = clientes;

        if (clientes.codigo == codigo && clientes.ativo == 'S')
        {
            printf("\n---------------------------------------------------------------------------");
            printf("\n DADOS DO REGISTRO                                                         ");
            printf("\n---------------------------------------------------------------------------");
            printf("\n");
            printf(" \nCODIGO: %05d \t PERTENCE AO GRUPO: %02d",   clientes.codigo, clientes.tipocliente);
            printf(" \nNOME DO CLIENTE: %s",     clientes.nomecliente);
            printf(" \nENDERECO: %s N: %1.0f",     clientes.enderecocliente,clientes.numerocasa);
            printf(" \nBAIRRO: %s",     clientes.bairrocliente);
            printf(" \nCIDADE: %s",     clientes.cidadecliente);
            printf(" \tESTADO: %s",     clientes.estadocliente);
            printf(" \nATIVO.: %c\n",     clientes.ativo);
            printf("\n");
            printf("\n---------------------------------------------------------------------------");
            printf("\n NOVOS DADOS DO REGISTRO                                                   ");
            printf("\n---------------------------------------------------------------------------");
            printf("\n");
			
			fflush(stdin);  
    		printf(" NOME DO CLIENTE: ");
    		gets(clientesTemp.nomecliente);
    		fflush(stdin);
    		printf(" ENDERECO DO CLIENTE: ");
    		gets(clientesTemp.enderecocliente);
    		fflush(stdin);
    		printf(" NUMERO DA CASA: ");
    		scanf("%f", &clientesTemp.numerocasa);
    		fflush(stdin);
    		printf(" BAIRRO DO CLIENTE: ");
    		gets(clientesTemp.bairrocliente);
    		fflush(stdin);
    		printf(" CIDADE DO CLIENTE: ");
    		gets(clientesTemp.cidadecliente);
    		fflush(stdin);
    		printf(" CEP DO CLIENTE: ");
    		scanf("%f", &clientesTemp.cepcliente);
    		fflush(stdin);
    		printf(" ESTADO DO CLIENTE: ");
    		gets(clientesTemp.estadocliente);
			fflush(stdin);
    		printf(" ESTE CLIENTE, PERTENCE A QUAL GRUPO?\n (1) NORMAL (2) ESTUDANTE\n ");
    		scanf("%d", &clientesTemp.tipocliente);
    		printf(" DATA DE CADASTRO: ");
            printf(" [%s]", clientesTemp.dataCadastropessoa);
            strcpy(clientesTemp.dataAtualizacao,dataSistema);
			printf("  \nDATA ATT: [%s]", clientesTemp.dataAtualizacao);
   			
            printf("\n\n DESEJA ALTERAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO | A-APAGAR ] ");

            char tecla = 0x00;
            while (tecla != 27)
            {
                if (kbhit())
                {
                    tecla = getch();
                    printf("%c", tecla);

                    switch(toupper(tecla))
                    {
                        case 'S' :
                            rewind(pclientes);
                            fseek(pclientes, sizeof(CLIENTE)*(codigo - 1), SEEK_SET);

                            fwrite(&clientesTemp, sizeof(CLIENTE), 1, pclientes);
                            fclose(pclientes);
                            
                            strcpy(clientes.dataAtualizacao,dataSistema);

                            mostraMenu();
                            return;
                        break;
                        case 'N' : mostraMenu(); return; break;
                        case 'A' :
                        
                            rewind(pclientes);
                            fseek(pclientes, sizeof(CLIENTE)*(codigo - 1), SEEK_SET);
                            

                            // Parâmetros de manutenção do registro.
                            clientes.ativo = 'N';
                            strcpy(clientes.dataAtualizacao,"00/00/0000");

                            fwrite(&clientes, sizeof(CLIENTE), 1, pclientes);
                            fclose(pclientes);

                            mostraMenu();
                            return;
                        break;
                        case 27  : mostraMenu(); return; break;
                    }
                }
            }
        }
        else
        {
            printf("\n---------------------------------------------------------------------------");
            printf("\n                 ### REGISTRO APAGADO OU NAO ENCONTRADO ###                ");
            printf("\n---------------------------------------------------------------------------");


           printf("\n\n DESEJA RESTAURAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO ]");

            char tecla = 0x00;
            while (tecla != 27)
            {
                if (kbhit())
                {
                    tecla = getch();
                    printf("%c", tecla);

                    switch(toupper(tecla))
                    {
                        case 'S' :
                        
                            rewind(pclientes);
                            fseek(pclientes, sizeof(CLIENTE)*(codigo - 1), SEEK_SET);

                            // Parâmetros de manutenção do registro.
                            clientes.ativo = 'S';
                            strcpy(clientes.dataAtualizacao,"00/00/0000");

                            fwrite(&clientes, sizeof(CLIENTE), 1, pclientes);
                            fclose(pclientes);

                            mostraMenu();
                            return;
                        break;
                        case 'N' : mostraMenu(); return; break;
                        case 27  : mostraMenu(); return; break;
                    }
                }
            }
        }
    }
    else
    {
        if (pclientes == NULL)
        {
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }
    }

    fclose(pclientes);

    getch();

    mostraMenu();
    return;
}

// ========================================================================================================================================================================
// CADASTRAR LIVROS =======================================================================================================================================================
// ========================================================================================================================================================================

void cadastrarLivros()
{
    LIVRO livros;
    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n CADASTRO DE LIVROS                                                        ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n");

    //printf(" CÓDIGO: ");
    //scanf("%d", &livros.codigo);

    livros.codigo = ultimoCodigoLivro() + 1;
    printf(" CODIGO.: [%05d]\n", livros.codigo);

    fflush(stdin);
    printf(" TITULO.: ");
    gets(livros.titulo);
    

    fflush(stdin);
    printf(" PRECO..: ");
    scanf("%f", &livros.preco);
    
    fflush(stdin);
    printf(" ESTOQUE: ");
    scanf("%f", &livros.estoque);
    
    fflush(stdin);
    printf(" ESTOQUE MINIMO: "); //alt
    scanf("%f", &livros.estoqueminimo); //alt

    fflush(stdin);

    strcpy(livros.dataCadastro,dataSistema);
    printf(" DATA DE CADASTRO: ");
    printf(" [%s]\n", livros.dataCadastro);
    
    // Parâmetros de manutenção do registro.
    fflush(stdin);
    livros.ativo = 'S';

    fflush(stdin);
    strcpy(livros.dataAtualizacao,"00/00/0000");

    printf("\n\n DESEJA GRAVAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO ] ");

    char tecla = 0x00;
    while (tecla != 27)
    {
        if (kbhit())
        {
            tecla = getch();
            printf("%c", tecla);

            switch(toupper(tecla))
            {
                case 'S' :
                    FILE *pLivros;
                    pLivros = fopen("LIVROS.DAT","ab");

                    if (pLivros == NULL)
                    {
                        system("cls");
                        printf("\n---------------------------------------------------------------------------");
                        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
                        printf("\n---------------------------------------------------------------------------");
                        getch();
                    }
                    else
                    {
                        fwrite(&livros, sizeof(LIVRO), 1, pLivros);
                        fflush(pLivros);
                    }
                    fclose(pLivros);

                    mostraMenu();
                    return;
                break;
                case 'N' : mostraMenu(); return; break;
                case 27  : mostraMenu(); return; break;
            }
        }
    }
}


// ========================================================================================================================================================================
// ATUALIZACAO DE LIVROS ==================================================================================================================================================
// ========================================================================================================================================================================

void atualizarLivros()
{
    unsigned int codigo = 0;
    unsigned int PosicaoInicial = 0;
    unsigned int PosicaoAtual = 0;
    unsigned int PosicaoFinal = 0;

    LIVRO livros, livrosTemp;
    FILE *pLivros;

    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n ATUALIZACAO DE LIVROS                                                     ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n");

    printf(" CODIGO DO REGISTRO A ALTERAR: ");
    scanf("%d", &codigo);

    pLivros = fopen("LIVROS.DAT","rb+");

    if (pLivros != NULL)
    {
		// Reposiciona o ponteiro do arquivo no início do mesmo para posicionar no registro e buscar as informações.
		rewind(pLivros);
		fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);
        fread(&livros, sizeof(LIVRO), 1, pLivros);

        // Atribui os dados do registro para alteração dentro de uma struct teporária.
        livrosTemp = livros;

        if (livros.codigo == codigo && livros.ativo == 'S')
        {
            printf("\n---------------------------------------------------------------------------");
            printf("\n DADOS DO REGISTRO                                                         ");
            printf("\n---------------------------------------------------------------------------");
            printf("\n");
            printf(" CODIGO.: %05d\n", livros.codigo);
            printf(" TITULO.: %s\n",   livros.titulo);
            printf(" PRECO..: %.2f\n", livros.preco);
            printf(" ESTOQUE: %.0f\n", livros.estoque);
            printf(" ESTOQUE MINIMO: %.0f\n", livros.estoqueminimo); //alt
            printf(" DATA...: [%s]\n",   livros.dataCadastro);
            printf(" DATA.AT: [%s]\n", livros.dataAtualizacao);
            printf("\n");
            printf("\n---------------------------------------------------------------------------");
            printf("\n NOVOS DADOS DO REGISTRO                                                   ");
            printf("\n---------------------------------------------------------------------------");
            printf("\n");

            fflush(stdin);
            printf(" TITULO: ");
            gets(livrosTemp.titulo);

            printf(" PRECO.: ");
            scanf("%f", &livrosTemp.preco);
            
            printf(" ESTOQUE.: ");
            scanf("%f", &livrosTemp.estoque);
            
            printf(" ESTOQUE MINIMO: "); //alt
            scanf("%f", &livrosTemp.estoqueminimo); //alt

            printf(" DATA DE CADASTRO: ");
            printf(" [%s]", livrosTemp.dataCadastro);
            
            strcpy(livrosTemp.dataAtualizacao,dataSistema);
   			printf("  \nDATA ATT: [%s]", livrosTemp.dataAtualizacao);
            
            

            printf("\n\n DESEJA ALTERAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO | A-APAGAR ] ");

            char tecla = 0x00;
            while (tecla != 27)
            {
                if (kbhit())
                {
                    tecla = getch();
                    printf("%c", tecla);

                    switch(toupper(tecla))
                    {
                        case 'S' :
                            rewind(pLivros);
                            fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);

                            fwrite(&livrosTemp, sizeof(LIVRO), 1, pLivros);
                            fclose(pLivros);
                            
                            strcpy(livros.dataAtualizacao,dataSistema);

                            mostraMenu();
                            return;
                        break;
                        case 'N' : mostraMenu(); return; break;
                        case 'A' :
                        
                            rewind(pLivros);
                            fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);
                            

                            // Parâmetros de manutenção do registro.
                            livros.ativo = 'N';
                            strcpy(livros.dataAtualizacao,"00/00/0000");

                            fwrite(&livros, sizeof(LIVRO), 1, pLivros);
                            fclose(pLivros);

                            mostraMenu();
                            return;
                        break;
                        case 27  : mostraMenu(); return; break;
                    }
                }
            }
        }
        else
        {
            printf("\n---------------------------------------------------------------------------");
            printf("\n                 ### REGISTRO APAGADO OU NAO ENCONTRADO ###                ");
            printf("\n---------------------------------------------------------------------------");


           printf("\n\n DESEJA RESTAURAR O REGISTRO NO ARQUIVO? [ S-SIM | N-NAO ]");

            char tecla = 0x00;
            while (tecla != 27)
            {
                if (kbhit())
                {
                    tecla = getch();
                    printf("%c", tecla);

                    switch(toupper(tecla))
                    {
                        case 'S' :
                        
                            rewind(pLivros);
                            fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);

                            // Parâmetros de manutenção do registro.
                            livros.ativo = 'S';
                            strcpy(livros.dataAtualizacao,"00/00/0000");

                            fwrite(&livros, sizeof(LIVRO), 1, pLivros);
                            fclose(pLivros);

                            mostraMenu();
                            return;
                        break;
                        case 'N' : mostraMenu(); return; break;
                        case 27  : mostraMenu(); return; break;
                    }
                }
            }
        }
    }
    else
    {
        if (pLivros == NULL)
        {
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }
    }

    fclose(pLivros);

    getch();

    mostraMenu();
    return;
}

// ========================================================================================================================================================================
// MOSTRAR RELACAO DE LIVROS ==============================================================================================================================================
// ========================================================================================================================================================================

void mostrarTodosLivros()
{
    LIVRO livros;
    int qtd = 0;

    FILE *pLivros;
    pLivros = fopen("LIVROS.DAT","rb");

    if (pLivros == NULL)
    {
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
        printf("\n---------------------------------------------------------------------------");
        getch();
    }
    else
    {
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n LISTAGEM DE TODOS OS LIVROS CADASTRADOS                                   ");
        printf("\n---------------------------------------------------------------------------");
        printf("\n");

        fread(&livros, sizeof(LIVRO), 1, pLivros);
        while(!feof(pLivros))
        {
            if (livros.ativo == 'S')   // Mostra apenas registros ativos.
            {
            	
            	
            
            		
            	printf(" \nCODIGO: %05d",   livros.codigo);
                printf(" \nTITULO DO LIVRO: %s",     livros.titulo);
                printf(" \nPRECO DO LIVRO: %10.2f",     livros.preco);
                printf(" \nQUANTIDADE EM ESTOQUE: \t%.0f",     livros.estoque);
                float zero; //alt
			    zero = 0; //alt
			    if (livros.estoque < zero){ //alt
				printf("\t(!)Produto esta com estoque negativo"); //alt
			    } //alt
                if (livros.estoqueminimo >= livros.estoque){ //alt 
                	printf(" \nESTOQUE MINIMO: \t%.0f  \t(!)Produto entrou em estoque minimo",     livros.estoqueminimo); //alt
				}else{ //alt
					printf(" \nESTOQUE MINIMO: \t%.0f",     livros.estoqueminimo); //alt
				} //alt
                printf(" \nDATA DO CADASTRO: [%s]",   livros.dataCadastro);
                printf(" \tDATA ULT. ALTERACAO: [%s]", livros.dataAtualizacao);
                printf(" \nATIVO.: %c\n",     livros.ativo);
                qtd += 1;
            }
            fread(&livros, sizeof(LIVRO), 1, pLivros);
        }
        printf("\n---------------------------------------------------------------------------");
        printf("\n QUANTIDADE DE LIVROS CADASTRADOS: %05d", qtd);
        printf("\n---------------------------------------------------------------------------");
        getch();
    }

    fclose(pLivros);
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================// ================================================================================================================================================================================================
// ================================================================================================================================================================================================// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

void LancamentoVenda(){
	unsigned int codigo = 0;
	unsigned int codigocliente = 0;
    unsigned int PosicaoInicial = 0;
    unsigned int PosicaoAtual = 0;
    unsigned int PosicaoFinal = 0;
	float valorfinal = 0;
	int fpgto = 0;
	float atual = 0;
	float desconto = 0;
	float total = 0;
	float tipoatual = 0;
	float tipototal = 0;
	float tipodesconto = 0;
	float valorunidade = 0;
	float qtdlivros = 0;
	
	VENDA vendas;
	CLIENTE clientes, clientesTemp;
	FILE *pclientes;
    LIVRO livros, livrosTemp;
    FILE *pLivros;
    
    

    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n VENDA DE LIVROS - SELECAO DO LIVRO                                        ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n");
//-----------------------------------------------------
	//vendas.codigo = ultimoCodigoVenda() + 1;
    //printf(" CODIGO.: [%05d]\n", vendas.codigo);
//-----------------------------------------------------
	
    printf(" CODIGO DO LIVRO: ");
    scanf("%d", &codigo);

    pLivros = fopen("LIVROS.DAT","rb+");
    if (pLivros != NULL)
    {
		// Reposiciona o ponteiro do arquivo no início do mesmo para posicionar no registro e buscar as informações.
		rewind(pLivros);
		fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);
        fread(&livros, sizeof(LIVRO), 1, pLivros);
        // Atribui os dados do registro para alteração dentro de uma struct teporária.
        livrosTemp = livros;


        if (livros.codigo == codigo && livros.ativo == 'S')
        {
            printf("\n---------------------------------------------------------------------------");
            printf("\n DADOS DO REGISTRO DO LIVRO SELECIONADO                                    ");
            printf("\n---------------------------------------------------------------------------");
            printf("\n");
            printf(" CODIGO.: %05d\n", livros.codigo);
            printf(" TITULO.: %s\n",   livros.titulo);
            printf(" PRECO..: %.2f\n", livros.preco);
            printf(" ESTOQUE: %.0f", livros.estoque);
            float zero; //alt
			zero = 0; //alt
			if (livros.estoque < zero){ //alt
				printf("\t        (!)Produto esta com estoque negativo"); //alt
			} //alt
            if (livros.estoqueminimo >= livros.estoque){     //alt
                	printf("\n ESTOQUE MINIMO: %.0f  \t(!)Produto entrou em estoque minimo   ",     livros.estoqueminimo); //alt
				}else{                                                                       //alt
					printf("\n ESTOQUE MINIMO: %.0f",     livros.estoqueminimo);    //alt
				}     //alt
            printf(" DATA...: [%s]\n",   livros.dataCadastro);
            printf(" DATA.AT: [%s]\n", livros.dataAtualizacao);
            printf("\n---------------------------------------------------------------------------");
        
            printf(" \nQUANTIDADE A SER VENDIDA: ");
            scanf("%f", &livrosTemp.estoque);
            
            livros.att = livros.estoque - livrosTemp.estoque;
            livros.estoque = livros.att;
            qtdlivros = livrosTemp.estoque;
            
            valorfinal = livros.preco*livrosTemp.estoque;
            valorunidade = livros.preco;
            //printf("%d", valorfinal);
            //PARTE DO CLIENTE ====================================================================

			system("cls");
			printf("\n\nESTOQUE ATUALIZADO DO LIVRO: %.0f\n\n", livros.estoque); //alt
			if (livros.estoqueminimo >= livros.estoque){ //alt
				printf("(!)Produto entrou em estoque minimo\n"); //alt
			} //alt
			
			 //alt
			zero = 0; //alt
			if (livros.estoque < zero){ //alt
				printf("(!)Produto esta com estoque negativo\n"); //alt
			} //alt
			livrosTemp.estoque = livros.estoque;
			printf("\n---------------------------------------------------------------------------");
			printf("\nVENDA DE LIVROS - SELECAO DO CLIENTE");
			printf("\n---------------------------------------------------------------------------");
			
			printf(" \nCODIGO DO CLIENTE: ");
			scanf("\n%d", &codigo);
			
			pclientes = fopen("CLIENTE.DAT","rb+");
    		if (pclientes != NULL){
    			
			// Reposiciona o ponteiro do arquivo no início do mesmo para posicionar no registro e buscar as informações.
			rewind(pclientes);
			fseek(pclientes, sizeof(CLIENTE)*(codigo - 1), SEEK_SET);
      		fread(&clientes, sizeof(CLIENTE), 1, pclientes);

      		  // Atribui os dados do registro para alteração dentro de uma struct teporária.
        	clientesTemp = clientes;
        	}
        		if (clientes.codigo == codigo && clientes.ativo == 'S'){
            	printf("\n---------------------------------------------------------------------------");
            	printf("\nDADOS DO REGISTRO DO CLIENTE SELECIONADO                                  ");
            	printf("\n---------------------------------------------------------------------------");
		    	printf(" \nCODIGO: %05d \t PERTENCE AO GRUPO: %d",   clientes.codigo, clientes.tipocliente);
                printf(" \nNOME DO CLIENTE: %s",     clientes.nomecliente);
                printf(" \nENDERECO: %s N: %1.0f",     clientes.enderecocliente,clientes.numerocasa);
                printf(" \nBAIRRO: %s",     clientes.bairrocliente);
                printf(" \nCIDADE: %s",     clientes.cidadecliente);
                printf(" \tESTADO: %s",     clientes.estadocliente);
                printf("\n---------------------------------------------------------------------------");
			}
			printf(" \n\n\nFORMA DE PAGAMENTO? ");
			printf(" \n[1] DINHEIRO \n[2] PIX \n[3] CARTAO DE DEBITO \n[4] CARTAO DE CREDITO\n\n");
            scanf(" %d", &fpgto);
			
			if (clientes.tipocliente == 2){
				tipoatual = valorfinal;
				tipodesconto = (valorfinal/100)*15;
				tipototal = tipoatual-tipodesconto;
			system("cls");
			printf("\n---------------------------------------------------------------------------");
			printf("\nRESUMO DA VENDA");
            printf("\n---------------------------------------------------------------------------");
            printf(" \n\nTITULO DO LIVRO: %s \nQUANTIDADE: %.0f", livros.titulo,qtdlivros);
            printf(" \nPRECO UNITARIO DO LIVRO: R$ %.2f", valorunidade);
            printf(" \nSUBTOTAL: R$ %.2f", valorfinal);
            printf(" \n\nNOME DO CLIENTE: %s \nPERTENCENTE AO GRUPO: %02d", clientes.nomecliente, clientes.tipocliente);
            printf(" \n\nCLIENTE TIPO ESTUDANTE, APLICADO DESCONTO (R$ %.2f)", tipodesconto);
            printf(" \nVALOR TOTAL DA VENDA: R$ %.2f",tipototal);
            printf(" \nFORMA DE PAGAMENTO ESCOLHIDA: %d", fpgto);
            printf("\n---------------------------------------------------------------------------");
			} else {
				total = valorfinal;
			system("cls");
            printf("\n---------------------------------------------------------------------------");
			printf("\nRESUMO DA VENDA");
            printf("\n---------------------------------------------------------------------------");
            printf(" \n\nTITULO DO LIVRO: %s \nQUANTIDADE: %0.0f", livros.titulo,qtdlivros);
            printf(" \nPRECO UNITARIO DO LIVRO: R$ %.2f", valorunidade);
            printf(" \nSUBTOTAL: R$ %.2f", valorfinal);
            printf(" \n\nNOME DO CLIENTE: %s \nPERTENCENTE AO GRUPO: %02d", clientes.nomecliente, clientes.tipocliente);
            printf(" \n\nVALOR TOTAL DA VENDA: R$ %.2f",total);
            printf(" \nFORMA DE PAGAMENTO ESCOLHIDA: %d", fpgto);
            printf("\n\n---------------------------------------------------------------------------");
			}
            if (livros.estoqueminimo >= livros.estoque){ //alt
				printf("\n(!)Produto entrou em estoque minimo\n"); //alt
			} //alt
			
			 //alt
			zero = 0; //alt
			if (livros.estoque < zero){ //alt
				printf("(!)Produto esta com estoque negativo\n"); //alt
			} //alt
            printf("\n\n DESEJA EFETUAR ESSA VENDA? [ S-SIM | N-NAO | A-APAGAR ] ");
            char tecla = 0x00;
    while (tecla != 27)
    {
        if (kbhit())
        {
            tecla = getch();
            printf("%c", tecla);

            switch(toupper(tecla))
            {
                case 'S' :
                    FILE *pvendas;
                    pvendas = fopen("VENDA.DAT","ab");


                    if (pvendas == NULL)
                    {
                        system("cls");
                        printf("\n---------------------------------------------------------------------------");
                        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO VENDA.DAT -----------------");
                        printf("\n---------------------------------------------------------------------------");
                        getch();
                    }
                    else
                    {
            			fwrite(&vendas, sizeof(VENDA), 1, pvendas);
                        fflush(pvendas);
            			
						rewind(pLivros);
                        fseek(pLivros, sizeof(LIVRO)*(codigo - 1), SEEK_SET);
						fwrite(&livrosTemp, sizeof(LIVRO), 1, pLivros);
                        fclose(pLivros);
                    
                    }
                    fclose(pvendas);

                    mostraMenu();
                    return;
                break;
                case 'N' : mostraMenu(); return; break;
                case 27  : mostraMenu(); return; break;
            }
         }
    	}
            
            
           
			}
	}
   
}

// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================


// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================
// ================================================================================================================================================================================================

int main()
{
    setlocale(LC_ALL,"Portuguese");
    char tecla = 0;

    mostraMenu();

    while (tecla != 27)
    {
        if (kbhit())
        {
            tecla = getch();
            printf("%c", tecla);

            switch(tecla)
            {
                case 13 : mostraMenu(); break;
                case 27 : exit(0);      break;
                case 51 : cadastrarClientes();        mostraMenu(); break;
                case 52 : mostrarTodosClientes();     mostraMenu(); break;
                case 49 : cadastrarLivros();     mostraMenu(); break;
                case 50 : mostrarTodosLivros();     mostraMenu(); break;
                case 53 : atualizarClientes();     mostraMenu(); break;
                case 54 : atualizarLivros();     mostraMenu(); break;
                case 55 : LancamentoVenda();     mostraMenu(); break;
            }
        }
    }

    return 0;
}









