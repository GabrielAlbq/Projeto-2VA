/*
 ============================================================================
 Name        : ProjetoIP1.c
 Authors     : Gabriel Albuquerque de Oliveira e Elthon Ferreira
 Version     : Final
 Copyright   : Livre, favor fazer mencao.
 Description : Sistema de gerenciamento de uma padaria
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<math.h>

int vetor;          //VARIAVEL PARA DEFINIR UMA QUANTIDADE INICIAL PARA PRODUTOS(CASO CHEGUE AO LIMITE, O VETOR ƒ REALOCADO)
int vetor2;         //VARIAVEL PARA DEFINIR UMA QUANTIDADE INICIAL PARA FUNCIONARIO(CASO CHEGUE AO LIMITE, O VETOR ƒ REALOCADO)
int vetor3;         //VARIAVEL PARA DEFINIR UMA QUANTIDADE INICIAL PARA RELATORIO DE VENDA(CASO CHEGUE AO LIMITE, O VETOR ƒ REALOCADO)
int qtdprod = 0;    //VARIAVEL PARA CONTAR OS PRODUTOS CADASTRADOS
int qtdfunc = 0;    //VARIAVEL PARA CONTAR OS FUNCIONARIOS CADASTRADOS
int qtdvenda = 0;   //VARIAVEL PARA INCREMENTACAO DE VENDA
int cc[200]= {0};   //CONTADOR PARA CADA PRODUTO DE UM PEDIDO, USADO EM VENDA E EM RELATORIO

typedef struct
{
    char nome[15];
    int cod;
    float preco;
    int qtd;

} Produto;

typedef struct
{
    char nome[25];
    int idade;
    float salario;
    char sexo[15];
    int cpf;

} Funcionario;

typedef struct
{
    int CodVenda[30];
    int QtdVenda[30];
    float PrecoVenda;
    int QtdFinal;
    char NomeVenda[15];

} Relatorio;

Produto *pro;
Funcionario *func;
Relatorio *rel;

void produtoscadastrados() //IMPRIME NA TELA OS PRODUTOS QUE ESTAO CADASTRADOS
{
    int c;
    printf("\nListando %d produtos cadastrados\n",qtdprod);
    for(c=0; c<qtdprod; c++)
    {
        printf("\n(%d)\n", c+1);
        printf("Nome = %s\n", pro[c].nome);
        printf("Codigo = %d\n", pro[c].cod);
        printf("Quantidade = %d\n",pro[c].qtd);
        printf("Preco = %.2f\n",pro[c].preco);
    }
}

void funcionarioscadastrados() //IMPRIME NA TELA OS FUNCIONARIOS QUE ESTAO CADASTRADOS
{
    int c;
    printf("\nListando %d funcionarios cadastrados\n",qtdfunc);
    for(c=0; c<qtdfunc; c++)
    {
        printf("\n(%d)\n", c+1);
        printf("Nome = %s\n", func[c].nome);
        printf("Idade = %d\n", func[c].idade);
        printf("Sexo = %s\n",func[c].sexo);
        printf("CPF = %d\n",func[c].cpf);
        printf("Salario = %.2f\n", func[c].salario);
    }
}
void adicionar_produto(Produto p)
{
    int vf; //VARIAVEL PARA SERVIR DE COMPARA‚ÌO SE Jç EXISTE DETERMINADO CîDIGO CADASTRADO
    if(qtdprod == vetor)
    {
        vetor *= 1.5;
        pro = realloc(pro, vetor*sizeof(Produto));
    }
    pro[qtdprod] = p;
    if(pro[qtdprod].qtd < 0)
    {
        printf("\nErro! Quantidade nao pode ser menor que 0\n");
        return;
    }
    if(pro[qtdprod].preco < 0)
    {
        printf("\nErro! Preco Invalido!\n");
        return;
    }
    for(vf=0; vf<qtdprod; vf++)
    {
        if(pro[vf].cod==pro[qtdprod].cod)
        {
            printf("Erro! Codigo ja existe!\n");
            return;
        }
    }
    qtdprod++;
}
void adicionar_funcionarios(Funcionario f)
{
    int vf; //VARIAVEL PARA SERVIR DE COMPARA‚ÌO SE Jç EXISTE DETERMINADO CPF CADASTRADO
    if(qtdfunc == vetor2)
    {
        vetor2 *= 1.5;
        func = realloc(func, vetor2*sizeof(Funcionario));
    }
    func[qtdfunc] = f;
    for(vf=0; vf<qtdfunc; vf++)
    {
        if(func[vf].cpf==func[qtdfunc].cpf)
        {
            printf("\n\t\tErro! CPF ja cadastrado!\n");
            return;
        }
    }
    qtdfunc++;
}

Produto ler_produto()
{
    Produto p;
    printf("Digite o nome do produto: ");
    fgets(p.nome, 25, stdin);
    if(p.nome != NULL && strlen(p.nome) > 0)
    {
        short tamanho = strlen(p.nome);
        if(p.nome[tamanho-1] == '\n')
        {
            p.nome[tamanho-1] = '\0';
        }
    }
    printf("Digite o codigo do produto: ");
    scanf("%d",&p.cod);
    getchar();

    printf("Digite a quantidade do produto: ");
    scanf("%d",&p.qtd);
    getchar();

    printf("Digite o preco do produto: ");
    scanf("%f",&p.preco);
    return p;
}

Funcionario ler_funcionario()
{
    Funcionario f;
    printf("Informe o nome do funcionario(a): ");
    fgets(f.nome, 25, stdin);
    if(f.nome != NULL && strlen(f.nome) > 0)
    {
        short tamanho = strlen(f.nome);
        if(f.nome[tamanho-1] == '\n')
        {
            f.nome[tamanho-1] = '\0';
        }
    }
    printf("Informe a idade do funcionario(a): ");
    scanf("%d",&f.idade);
    getchar();

    printf("Informe o sexo do funcionario(a): ");
    fgets(f.sexo, 15, stdin);
    if(f.sexo != NULL && strlen(f.sexo) > 0)
    {
        short tamanho = strlen(f.sexo);
        if(f.sexo[tamanho-1] == '\n')
        {
            f.sexo[tamanho-1] = '\0';
        }
    }
    printf("Informe o CPF: ");
    scanf("%d", &f.cpf);
    printf("Informe o salario: ");
    scanf("%f", &f.salario);
    return f;
}

void atualizarproduto()
{
    printf("Informe o codigo do produto a ser atualizado:\n");
    int codigo;
    scanf("%d",&codigo);
    getchar();
    Produto *pr = NULL;
    int cont;
    for (cont=0; cont < qtdprod; cont++)
    {
        if(pro[cont].cod == codigo)
        {
            pr = &pro[cont];
            break;
        }
    }
    if(pr != NULL)
    {
        printf("\t\tDigite os novos dados do produto\n");
        Produto pr2 = ler_produto();
        strcpy(pr->nome, pr2.nome);
        pr->cod = pr2.cod;
        pr->preco = pr2.preco;
        pr->qtd = pr2.qtd;
    }
    else
    {
        printf("Produto nao encontrado!\n");
    }
}

void atualizarfuncionario()
{
    printf("Informe o CPF do funcionario a ser atualizado:\n");
    int cpf2;
    scanf("%d", &cpf2);
    getchar();
    Funcionario *pr = NULL;
    int cont;
    for (cont=0; cont < qtdfunc; cont++)
    {
        if(func[cont].cpf == cpf2)
        {
            pr = &func[cont];
            break;
        }
    }
    if(pr != NULL)
    {
        printf("\t\tDigite os novos dados do funcionario\n");
        Funcionario pr2 = ler_funcionario();
        strcpy(pr->nome, pr2.nome);
        pr->idade = pr2.idade;
        strcpy(pr->sexo, pr2.sexo);
        pr->cpf = pr2.cpf;
        pr->salario = pr2.salario;
    }
    else
    {
        printf("Funcionario nao encontrado!\n");
    }
}

void removeProduto()
{

    printf("Digite o codigo do produto a ser removido: ");

    int codigo;
    scanf("%d",&codigo);
    getchar();
    int m;
    int produtoe = 0;
    for (m=0; m < qtdprod; m++)
    {
        if(pro[m].cod == codigo)
        {
            int j = m;
            while(j < qtdprod-1)
            {
                pro[j] = pro[j+1];
                j++;
            }
            if(qtdprod < vetor/3)
            {
                vetor = vetor*0.5;
                pro = realloc(pro, vetor*sizeof(Produto));
            }
            qtdprod--;
            produtoe = 1;
            break;
        }
    }
    if(!produtoe)
    {
        printf("Produto nao encontrado!\n");
    }
    else
    {
        printf("Produto removido com sucesso!\n");
    }
}

void removeFuncionario()
{

    printf("Informe o CPF do funcionario a ser removido: ");

    int cpf2;
    scanf("%d",&cpf2);
    getchar();

    int m;
    int produtoe = 0;
    for (m=0; m < qtdfunc; m++)
    {
        if(func[m].cpf == cpf2)
        {
            int j = m;
            while(j < qtdfunc-1)
            {
                func[j] = func[j+1];
                j++;
            }
            if(qtdfunc < vetor2/3)
            {
                vetor2 = vetor2*0.5;
                func = realloc(func, vetor2*sizeof(Funcionario));
            }
            qtdfunc--;
            produtoe = 1;
            break;
        }
    }
    if(!produtoe)
    {
        printf("Funcionario nao encontrado!\n");
    }
    else
    {
        printf("Funcionario removido com sucesso!\n");
    }
}
int procuraproduto()
{
    printf("Informe o codigo do produto a ser vendido: ");
    int encontrou =0;
    int i=1, teste = 0;
    int cod;
    while(encontrou!=i)
    {
        scanf("%d",&cod);
        getchar();
        for (i=0; i < qtdprod; i++)
        {
            if(pro[i].cod == cod)
            {
                encontrou = i;
                break;
                teste = 0;
            }
            else
            {
                teste = 1;
            }
        }
        if(teste == 1 && encontrou !=i)
        {
            printf("Codigo nao encontrado, digite um novo: ");
        }
    }
    return encontrou;
}
int procurafuncionario()
{
    int i,encontrou,cpf;
    printf("Informe o CPF do funcionario que ira registrar a venda: ");
    while(encontrou!=1)
    {
        scanf("%d",&cpf);
        getchar();
        for (i=0; i<qtdfunc; i++)
        {
            if(func[i].cpf == cpf)
            {
                encontrou = 1;
                break;
            }
            else
            {
                encontrou = -1;
            }
        }
        if(encontrou == -1)
        {
            printf("CPF nao encontrado, digite novamente:\n");
        }
    }
    return encontrou;
}

void relatoriovenda()
{
    int c,i;
    int j=0;
    for(c=0; c<qtdvenda; c++)
    {
        j=0;
        printf("\tPEDIDO #%d\n",c+1);
        printf("Produtos\tQuantidade\tPreco\tTotal\n");
        while(j<cc[c])
        {
            if(rel[c].CodVenda[j] != 0)
            {
                for(i=0; i<qtdprod; i++)
                {
                    if(pro[i].cod == rel[c].CodVenda[j])
                    {
                        printf("%s\t",pro[i].nome);
                        printf("\t\t%d",rel[c].QtdVenda[j]);
                        printf("\t%.2f",pro[i].preco);
                        printf("\t%.2f\n",rel[c].QtdVenda[j]*pro[i].preco);
                    }
                }
            }
            j++;
        }
        printf("_____________________________________________");
        printf("\nFinal:\t\t\t%d\t\t",rel[c].QtdFinal);
        printf("%.2f\n\n", rel[c].PrecoVenda);
    }
}

void gravaarquivorel()
{
    FILE *arquivorel = fopen("relatorio.bin","wb");

    if(arquivorel == NULL)
    {
        printf("Erro: nao foi possivel abrir arquivo");
        exit(1);
    }
    else
    {
        int j;
        int c;
        c = (int) fwrite(&vetor3, sizeof(int), 1, arquivorel);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }
        c = (int) fwrite(&qtdvenda, sizeof(int),1,arquivorel);
        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }
        for(j=0; j<200; j++)
        {
            c = (int) fwrite(&cc[j], sizeof(int),1,arquivorel);
        }
        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }
        c = (int) fwrite(rel, sizeof(Relatorio), vetor3, arquivorel);

        if(c < vetor3)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }

        fclose(arquivorel);
    }
}

void learquivorel()
{
    FILE *arquivorel = fopen("relatorio.bin", "rb");

    if(arquivorel == NULL)
    {
        vetor3 = 20;
        qtdvenda = 0;
        rel = malloc(vetor3*sizeof(Relatorio));
    }
    else
    {
        int c = (int)fread(&vetor3, sizeof(int), 1, arquivorel);
        int j;
        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }

        c = (int)fread(&qtdvenda, sizeof(int), 1, arquivorel); //RECUPERA QUANTIDADE DE VENDAS

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }
        rel = malloc(vetor3*sizeof(Relatorio));
        for(j=0; j<200; j++)
        {
            c = (int)fread(&cc[j], sizeof(int), 1, arquivorel); //RECUPERA A QUANTIDADE DO CONTADOR PARA CADA PRODUTO DE UM PEDIDO
        }
        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }
        c = (int)fread(rel, sizeof(Relatorio), vetor3, arquivorel);

        if(c < vetor3)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivorel);
            return;
        }

        fclose(arquivorel);

    }
}

void venda()
{
    int sair = 1;       //SERVEM PARA O WHILE DE QUALQUER MENU
    int sair2 = 0;      //SERVE PARA QUANTO ESTIVER UM WHILE EM OUTRO E Sî QUISER SAIR APENAS DE UM
    int temp[50];       //GUARDA VALOR TEMPORARIO PARA CADA PRODUTO ADICIONADO NA VENDA
    int qtdtemp[50];    //GUARDA VALOR TEMPORARIO PARA A QUANTIDADE UM PRODUTO ADICIONADO NA VENDA
    int contador = 0;   //CONTA CADA PRODUTO ADICIONADO NO PEDIDO
    int i,j;            //CONTADORES
    float valorvenda;   //RECEBE O VALOR QUE O CLIENTE PAGOU PELA COMPRA
    float soma = 0;     //VALOR TOTAL DA VENDA
    int qtd;            //RECEBE A QUANTIDADE DO PRODUTO PEDIDO
    int opcao;          //VARIAAVEL PARA A OP‚ÌO DESEJADO DO USòARIO
    int achou = -1;     //VARIAVEL PARA PODER ENTRAR NA CONDI‚ÌO WHILE SE ACHAR FUNCIONARIO E PRODUTO
    achou = procurafuncionario();
    if(achou >= 0)
    {
        achou = -1;
        achou = procuraproduto();
        sair=0;
    }
    while(sair!=1 && achou>=0)
    {
        printf("Informe a quantidade a ser vendida: ");
        scanf("%d",&qtd);
        getchar();
        if(qtd > 0 && pro[achou].qtd >= qtd)
        {
            soma += (qtd*pro[achou].preco);
            printf("\n\tProduto: %s  \n\tQtd: %d  \n\tPreco: %1.2f  \n\tSubTotal: %1.2f\n", pro[achou].nome, qtd, pro[achou].preco, (pro[achou].preco * qtd));
            fflush(stdout);
            printf("\n\nTotal parcial: %.2f\n\n",soma);
            sair2 = 0;
            while(!sair2)
            {
                printf("Deseja adicionar mais produtos?\n(1)SIM\n(2)NAO\n");
                printf("Opcao: ");
                scanf("%d",&opcao);
                getchar();
                if (opcao == 1)
                {
                    pro[achou].qtd -= qtd;
                    temp[contador] = pro[achou].cod;
                    qtdtemp[contador] = qtd;
                    contador++;
                    achou = procuraproduto();
                    fflush(stdin);
                    sair2 = 1;
                }
                else if(opcao == 2)
                {
                    pro[achou].qtd -= qtd;
                    temp[contador] = pro[achou].cod;
                    qtdtemp[contador] = qtd;
                    contador++;
                    sair = 1;
                    sair2=1;
                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
        }
        else if(pro[achou].qtd == 0)
        {
            sair2 = 0;
            while(!sair2)
            {
                printf("\nProduto se encontra zerado no estoque, deseja digitar outro produto?\n");
                printf("(1)SIM\n(2)NAO\n");
                printf("Opcao: ");
                scanf("%d",&opcao);
                fflush(stdin);
                if(opcao == 1)
                {
                    procuraproduto();
                    sair2 = 1;
                }
                else if(opcao == 2)
                {
                    sair = 1;
                    sair2 = 1;
                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
        }
        else
        {
            sair2=0;
            while(!sair2)
            {
                printf("\n\tQuantidade insuficiente! Deseja digitar uma nova quantidade?\n\n");
                printf("(1)SIM\n(2)NAO\n");
                printf("Opcao: ");
                scanf("%d",&opcao);
                fflush(stdin);
                if(opcao == 1)
                {
                    sair = 0;
                    sair2 = 1;
                }
                else if(opcao == 2)
                {
                    int aux;
                    printf("\nSelecione uma opcao\n");
                    printf("\n(1)Finalizar venda\n(2)Digitar novo produto\n");
                    printf("Opcao: ");
                    scanf("%d",&aux);
                    if(aux == 1)
                    {
                        sair = 1;
                        sair2 = 1;
                    }
                    else if(aux == 2)
                    {
                        procuraproduto();
                        sair2 = 1;
                    }

                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
        }
    }
    printf("\nTotal da venda: R$%.2f\n",soma);
    do
    {
        printf("Qual o valor recebido?\n");
        scanf("%f",&valorvenda);
        getchar();
        if(valorvenda < soma)
        {
            printf("Valor insuficiente para compra\n");
        }
    }
    while(valorvenda<soma);

    printf("\nDeseja confirmar a venda?\n(1) - SIM\n(2) - NAO\n");
    printf("Opcao: ");
    scanf("%d",&opcao);
    fflush(stdin);
    if(opcao == 1)
    {
        if(qtdvenda == vetor3)
        {
            vetor3 *= 1.5;
            rel = realloc(rel, vetor3*sizeof(Relatorio));
        }
        qtdvenda++;
        printf("\nTroco: %.2f\n",valorvenda - soma);

        for(i=0; i<qtdprod; i++)
        {
            for(j=0; j<contador; j++)
            {
                if(pro[i].cod == temp[j])
                {
                    cc[qtdvenda-1]++;
                    rel[qtdvenda-1].CodVenda[j] = temp[j];
                    rel[qtdvenda-1].QtdFinal += qtdtemp[j];
                    rel[qtdvenda-1].QtdVenda[j] = qtdtemp[j];
                    rel[qtdvenda-1].PrecoVenda = soma;
                }
            }
        }
    }
    else if(opcao == 2)
    {
        for(i=0; i<=contador; i++)
        {
            for(j=0; j<=contador; j++)
            {
                if(pro[i].cod == temp[j])
                {
                    pro[i].qtd += qtdtemp[j];
                }
            }
        }
        contador = 0;
    }
}

void gravaarquivoprod()
{
    FILE *arquivoprod = fopen("produtos.bin", "wb");

    if(arquivoprod == NULL)
    {
        printf("Erro: nao foi possivel abrir arquivo");
        exit(1);
    }
    else
    {
        int c;
        c = (int) fwrite(&vetor, sizeof(int), 1, arquivoprod);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }
        c = (int) fwrite(&qtdprod, sizeof(int), 1, arquivoprod);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }
        c = (int) fwrite(pro, sizeof(Produto), vetor, arquivoprod);

        if(c < vetor)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }

        fclose(arquivoprod);
    }
}

void learquivoprod()
{
    FILE *arquivoprod = fopen("produtos.bin", "rb");

    if(arquivoprod == NULL)
    {
        vetor = 10;
        qtdprod = 0;
        pro = malloc(vetor*sizeof(Produto));
    }
    else
    {
        int c = (int)fread(&vetor, sizeof(int), 1, arquivoprod);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }
        c = (int)fread(&qtdprod, sizeof(int), 1, arquivoprod);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }
        pro = malloc(vetor*sizeof(Produto));

        c = (int)fread(pro, sizeof(Produto), vetor, arquivoprod);

        if(c < vetor)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivoprod);
            return;
        }

        fclose(arquivoprod);
    }

}

void gravaarquivofunc()
{
    FILE *arquivofunc = fopen("funcionarios.bin", "wb");

    if(arquivofunc == NULL)
    {
        printf("Erro: nao foi possivel abrir arquivo");
        exit(1);
    }
    else
    {
        int c = (int) fwrite(&vetor2, sizeof(int), 1, arquivofunc);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivofunc);
            return;
        }
        c = (int) fwrite(&qtdfunc, sizeof(int), 1, arquivofunc);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivofunc);
            return;
        }
        c = (int) fwrite(func, sizeof(Funcionario), vetor2, arquivofunc);

        if(c < vetor2)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivofunc);
            return;
        }

        fclose(arquivofunc);
    }
}

void learquivofunc()
{
    FILE *arquivofunc = fopen("funcionarios.bin", "rb");

    if(arquivofunc == NULL)
    {
        vetor2 = 10;
        qtdfunc = 0;
        func = malloc(vetor2*sizeof(Funcionario));
    }
    else
    {
        int c = (int)fread(&vetor2, sizeof(int), 1, arquivofunc);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");;
            fclose(arquivofunc);
            return;
        }

        c = (int)fread(&qtdfunc, sizeof(int), 1, arquivofunc);

        if(c < 1)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivofunc);
            return;
        }
        func = malloc(vetor2*sizeof(Funcionario));

        c = (int)fread(func, sizeof(Funcionario), vetor2, arquivofunc);

        if(c < vetor2)
        {
            printf("Erro: nao foi possivel abrir arquivo");
            fclose(arquivofunc);
            return;
        }

        fclose(arquivofunc);
    }

}

void menu()
{
    int sair = 0; //SERVE PARA O WHILE DE QUALQUER MENU
    while(!sair)
    {
        printf("\n\n\t\t\tMENU PRINCIPAL\n\n");
        printf("\tDigite um numero para informar a opcao desejada\n\n");
        printf("(1) - Produto\n");
        printf("(2) - Funcionario\n");
        printf("(3) - Venda\n");
        printf("(4) - Sair\n\n");
        printf("Opcao: ");

        int num;
        scanf("%d", &num);
        getchar();
        system("cls");

        if (num == 1)
        {
            while(sair!=1)
            {
                printf("\n\tPRODUTOS\n");
                printf("Selecione a opcao desejada:\n\n");
                printf("(1) - Adicionar produto\n");
                printf("(2) - Listar produtos\n");
                printf("(3) - Atualizar produto\n");
                printf("(4) - Remover produto\n");
                printf("(5) - Menu Principal\n");
                printf("\nOpcao: ");
                int sub;
                scanf("%d", &sub);
                getchar();

                if(sub == 1)
                {
                    system("cls");
                    adicionar_produto(ler_produto());
                    break;
                }
                else if(sub == 2)
                {
                    system("cls");
                    produtoscadastrados();
                }
                else if(sub == 3)
                {
                    system("cls");
                    atualizarproduto();
                }
                else if(sub == 4)
                {
                    system("cls");
                    removeProduto();
                }
                else if(sub == 5)
                {
                    sair = 1;
                    system("cls");
                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
            sair = 0;
        }

        else if (num == 2)
        {
            while(sair!=1)
            {
                printf("\n\tFUNCIONARIOS\n");
                printf("Selecione a opcao desejada:\n\n");
                printf("(1) - Cadastrar funcionario\n");
                printf("(2) - Listar funcionarios\n");
                printf("(3) - Atualizar funcionario\n");
                printf("(4) - Remover funcionario\n");
                printf("(5) - Menu Principal\n");
                printf("\nOpcao: ");
                int sub;
                scanf("%d", &sub);
                getchar();

                if(sub == 1)
                {
                    system("cls");
                    adicionar_funcionarios(ler_funcionario());
                    break;
                }
                else if(sub == 2)
                {
                    system("cls");
                    funcionarioscadastrados();
                }
                else if(sub == 3)

                {
                    system("cls");
                    atualizarfuncionario();
                }
                else if(sub == 4)
                {
                    system("cls");
                    removeFuncionario();
                }
                else if(sub == 5)
                {
                    sair = 1;
                    system("cls");
                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
            sair = 0;

        }
        else if(num == 3)
        {
            while(sair!=1)
            {
                printf("\n\tVENDA\n");
                printf("Selecione a opcao desejada:\n\n");
                printf("(1) - Registrar venda\n");
                printf("(2) - Relatorio de vendas\n");
                printf("(3) - Menu Principal\n");
                printf("\nOpcao: ");
                int sub;
                scanf("%d", &sub);
                getchar();
                if(sub == 1)
                {
                    venda();
                }
                else if(sub == 2)
                {
                    system("cls");
                    relatoriovenda();
                }
                else if(sub == 3)
                {
                    system("cls");
                    break;
                }
                else
                {
                    system("cls");
                    printf("\n\n\tOpcao Invalida!\n\n\n");
                }
            }
        }
        else if (num == 4)
        {
            printf("\n\n\tObrigado por usar o nosso sistema, volte sempre!\n\n\n\n\n");
            gravaarquivoprod();
            gravaarquivofunc();
            gravaarquivorel();
            break;
        }
        else
        {
            system("cls");
            printf("\n\n\t\tOpcao invalida\n\n\n");
        }
    }

}

int main()
{
    printf("\n\n\t\tBem vindo ao sistema de Padaria 1.0\n");
    learquivofunc();
    learquivoprod();
    learquivorel();
    menu();
    return 0;
}
