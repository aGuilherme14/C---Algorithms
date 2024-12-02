/* 
    Nome: Guilherme Francisco Almeida de jesus 
    Prof: Semirames
    Materia: Linguagem de Programacao
    Curso: Analise e desenvolvimento de sitemas 
    
    Descricao: Este código é um sistema de gerenciamento de clientes e empréstimos, implementado em C, 
               que permite cadastrar clientes, listar os cadastrados, realizar empréstimos, 
               consultar empréstimos existentes e apagar dados associados a clientes. 
               Ele também inclui funcionalidades para salvar e carregar os dados de clientes e empréstimos em um arquivo, 
               garantindo persistência. 

    SENHA ADM: 1230

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CLIENTES 100
#define MAX_EMPRESTIMOS 100

#ifdef _WIN32
#define CLEAR "cls"
#else 
#define CLEAR "clear"
#endif

// Struct Cliente
typedef struct
{
    float salario; // Salário do cliente
    int idade;     // Idade do cliente
    char nome[50]; // Nome completo do cliente
    int ID;        // ID único para o cliente
} Pessoa;

// Struct Empréstimo
typedef struct
{
    int IDCliente;    // ID do cliente associado ao empréstimo
    float valor;      // Valor solicitado no empréstimo
    int periodo;      // Período do empréstimo em meses
    float juros;      // Taxa de juros mensal
    float valorFinal; // Valor final após aplicação dos juros
} Emprestimo;

Pessoa clientes[MAX_CLIENTES];
Emprestimo emprestimos[MAX_EMPRESTIMOS];
int numClientes = 0;
int numEmprestimos = 0;

// Declaração de funções
void RealizarCadastro(Pessoa *clientes, int *numClientes);
void MostrarClientes(const Pessoa *clientes, int numClientes);
Pessoa *BuscarClientePorID(Pessoa *clientes, int numClientes, int ID);
void RealizarEmprestimo(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int *numEmprestimos);
void MostrarEmprestimos(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int numEmprestimos);
void ApagarDadoPorID(Pessoa *clientes, int *numClientes, Emprestimo *emprestimos, int *numEmprestimos);
void PausarEContinuar();
void SalvarDadosEmArquivo(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int numEmprestimos);
void CarregarDadosDeArquivo(Pessoa *clientes, int *numClientes, Emprestimo *emprestimos, int *numEmprestimos);

int main()
{
    CarregarDadosDeArquivo(clientes, &numClientes, emprestimos, &numEmprestimos);

    int opcao;
    char resposta;

    do
    {
        system(CLEAR);
        printf("\n\t=========================================\n");
        printf("\t               BEM-VINDO                 \n");
        printf("\t=========================================\n");
        printf("O cliente já possui cadastro? (s/n): ");
        scanf(" %c", &resposta);
        getchar();

        if (resposta == 's' || resposta == 'S')
        {
            do
            {
                system(CLEAR);
                printf("\n\t=========================================\n");
                printf("\t             MENU PRINCIPAL              \n");
                printf("\t=========================================\n");
                printf("\t1. Realizar Emprestimo\n");
                printf("\t2. Consultar Emprestimos Realizados\n");
                printf("\t3. Exibir Clientes Cadastrados\n");
                printf("\t4. Apagar Cliente\n");
                printf("\t5. Sair\n");
                printf("\t=========================================\n");
                printf("Escolha uma opcao: ");
                scanf("%d", &opcao);
                getchar();

                switch (opcao)
                {
                case 1:
                    RealizarEmprestimo(clientes, numClientes, emprestimos, &numEmprestimos);
                    break;
                case 2:
                    MostrarEmprestimos(clientes, numClientes, emprestimos, numEmprestimos);
                    break;
                case 3:
                    MostrarClientes(clientes, numClientes);
                    break;
                case 4:
                    ApagarDadoPorID(clientes, &numClientes, emprestimos, &numEmprestimos);
                    break;
                case 5:
                    SalvarDadosEmArquivo(clientes, numClientes, emprestimos, numEmprestimos);
                    printf("Saindo do sistema...\n");
                    break;
                default:
                    printf("Opcao invalida! Tente novamente\n");
                }
                if (opcao != 5)
                    PausarEContinuar();
            } while (opcao != 5);
        }
        else if (resposta == 'n' || resposta == 'N')
        {
            RealizarCadastro(clientes, &numClientes);
        }
        else
        {
            printf("Resposta invalida! Tente novamente\n");
            PausarEContinuar();
        }
    } while (opcao != 5);

    return 0;
}

// Implementação das funções

void RealizarCadastro(Pessoa *clientes, int *numClientes)
{
    if (*numClientes >= MAX_CLIENTES)
    {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Pessoa *cliente = &clientes[*numClientes];
    static int ultimoID = 0;

    printf("\n\t=========== Cadastro de Cliente ===========\n\n");
    printf("Digite seu nome completo: ");
    fgets(cliente->nome, sizeof(cliente->nome), stdin);
    cliente->nome[strcspn(cliente->nome, "\n")] = '\0';

    printf("Digite sua idade: ");
    scanf("%d", &cliente->idade);

    if (cliente->idade < 18)
    {
        printf("\n\t================== AVISO ==========================\n");
        printf("\t= Cadastro nao permitido! Cliente menor de idade =\n");
        printf("\t===================================================\n\n");
        PausarEContinuar();
        return;
    }

    printf("Digite seu salario: ");
    scanf("%f", &cliente->salario);

    cliente->ID = ++ultimoID;

    (*numClientes)++;
    printf("\t=================== AVISO ========================\n");
    printf("\t=        Cliente cadastrado com sucesso          =\n");
    printf("\t=               ID do cliente: %d                 =\n", cliente->ID);
    printf("\t==================================================\n\n");
}

void MostrarClientes(const Pessoa *clientes, int numClientes)
{
    if (numClientes == 0)
    {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("\n\t======= Clientes Cadastrados =======\n\n");
    for (int i = 0; i < numClientes; i++)
    {
        printf("\tID: %d\n", clientes[i].ID);
        printf("\tNome: %s\n", clientes[i].nome);
        printf("\tIdade: %d\n", clientes[i].idade);
        printf("\tSalário: R$%.2f\n\n", clientes[i].salario);
        printf("\t------------------------------------------\n\n");
    }
}

// Função para buscar cliente por ID
Pessoa *BuscarClientePorID(Pessoa *clientes, int numClientes, int ID)
{
    for (int i = 0; i < numClientes; i++)
    {
        if (clientes[i].ID == ID)
        {
            return &clientes[i];
        }
    }
    return NULL;
}

// Função para realizar um empréstimo
void RealizarEmprestimo(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int *numEmprestimos)
{
    int ID, periodo;
    float valor;
    float taxaMensal = 0.0364; // Taxa de juros com base no mercado pago
    float valorFinal, valorParcela;

    printf("\n\t=========== Realizar Emprestimo ===========\n\n");
    printf("\tDigite o ID do cliente para realizar o emprestimo: ");
    scanf("%d", &ID);

    Pessoa *cliente = BuscarClientePorID(clientes, numClientes, ID);
    if (cliente == NULL)
    {
        printf("\tCliente nao encontrado\n");
        return;
    }

    printf("\tDigite o valor do emprestimo: ");
    scanf("%f", &valor);
    if (valor <= 0 || valor > 10 * cliente->salario)
    {

        printf("\t===========================AVISO============================\n");
        printf("\t=   Valor do emprestimo deve ser menor que 10x o salario   =\n");
        printf("\t============================================================\n\n");

        return;
    }

    printf("\tDigite o periodo do emprestimo (em meses) (maximo 60): ");
    scanf("%d", &periodo);
    if (periodo <= 0 || periodo > 60)
    {

        printf("\t==================AVISO======================\n");
        printf("\t=   Periodo nao pode ultrapassar 60 meses   =\n");
        printf("\t=============================================\n\n");

        return;
    }

    // Cálculo de juros compostos
    valorFinal = valor * pow(1 + taxaMensal, periodo);
    valorParcela = valorFinal / periodo;

    // Armazenando o empréstimo
    Emprestimo *emp = &emprestimos[*numEmprestimos];
    emp->IDCliente = cliente->ID;
    emp->valor = valor;
    emp->periodo = periodo;
    emp->juros = taxaMensal;
    emp->valorFinal = valorFinal;

    (*numEmprestimos)++;
    printf("\tEmpréstimo realizado com sucesso!\n");
    printf("\tValor final com juros: %.2f\n", valorFinal);
    printf("\tValor das parcelas: %.2f (em %d meses)\n", valorParcela, periodo);
}

// Função para exibir os empréstimos realizados
void MostrarEmprestimos(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int numEmprestimos)
{
    if (numEmprestimos == 0)
    {
        printf("\tNenhum emprestimo realizado.\n");
        return;
    }

    printf("\n\t======= Emprestimos Realizados =======\n\n");
    for (int i = 0; i < numEmprestimos; i++)
    {
        Pessoa *cliente = BuscarClientePorID(clientes, numClientes, emprestimos[i].IDCliente);
        if (cliente != NULL)
        {
            printf("\tID do cliente: %d\n", cliente->ID);
            printf("\tNome do cliente: %s\n", cliente->nome);
            printf("\tValor do empréstimo: %.2f\n", emprestimos[i].valor);
            printf("\tJuros: %.2f\n", emprestimos[i].juros * 100);
            printf("\tPeríodo: %d meses\n", emprestimos[i].periodo);
            printf("\tValor final com juros: %.2f\n", emprestimos[i].valorFinal);
            printf("\t======================================\n\n");
        }
    }
}

// Função para apagar um cliente e seus empréstimos
void ApagarDadoPorID(Pessoa *clientes, int *numClientes, Emprestimo *emprestimos, int *numEmprestimos)
{
    int ID;
    int senha;
    const int senhaCorreta = 1230; 

    for (int tentativas = 0; tentativas < 3; tentativas++)
    {
        printf("Sera necessario senha ADM para continuar: ");
        scanf("%d", &senha);

        if (senha == senhaCorreta)
        {
            printf("\tDigite o ID do cliente a ser apagado: ");
            scanf("%d", &ID);

            for (int i = 0; i < *numClientes; i++)
            {
                if (clientes[i].ID == ID)
                {
                    // Apagar empréstimos associados a esse cliente
                    for (int j = 0; j < *numEmprestimos; j++)
                    {
                        if (emprestimos[j].IDCliente == ID)
                        {
                            for (int k = j; k < *numEmprestimos - 1; k++)
                            {
                                emprestimos[k] = emprestimos[k + 1];
                            }
                            (*numEmprestimos)--;
                            break;
                        }
                    }
                    // Remover cliente
                    for (int k = i; k < *numClientes - 1; k++)
                    {
                        clientes[k] = clientes[k + 1];
                    }
                    (*numClientes)--;

                    printf("\t======================= AVISO =========================\n");
                    printf("\t=   Cliente e seus emprestimos apagados com sucesso   =\n");
                    printf("\t=======================================================\n\n");

                    return;
                }
            }
            printf("\tCliente não encontrado.\n");
            return;
        }
        else
        {
            printf("\t================ AVISO ==================\n");
            printf("\t=   Senha incorreta, digite novamente:  =\n");
            printf("\t=========================================\n\n");
        }
    }

    printf("\t=============== AVISO ================\n");
    printf("\t= Tentativas excedidas. Encerrando   =\n");
    printf("\t======================================\n\n");
    exit(0); // Encerra o programa após 3 tentativas
}

void CarregarDadosDeArquivo(Pessoa *clientes, int *numClientes, Emprestimo *emprestimos, int *numEmprestimos)
{
    FILE *arquivo = fopen("dados.dat", "rb");
    if (arquivo == NULL)
    {
        printf("Nenhum dado encontrado para carregar.\n");
        *numClientes = 0;
        *numEmprestimos = 0;
        return;
    }

    // Carregar número de clientes e clientes
    fread(numClientes, sizeof(int), 1, arquivo);
    fread(clientes, sizeof(Pessoa), *numClientes, arquivo);

    // Carregar número de empréstimos e empréstimos
    fread(numEmprestimos, sizeof(int), 1, arquivo);
    fread(emprestimos, sizeof(Emprestimo), *numEmprestimos, arquivo);

    fclose(arquivo);
    printf("Dados carregados com sucesso!\n");
}
void SalvarDadosEmArquivo(Pessoa *clientes, int numClientes, Emprestimo *emprestimos, int numEmprestimos)
{
    FILE *arquivo = fopen("dados.dat", "wb");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar os dados.\n");
        return;
    }

    // Salvar número de clientes e clientes
    fwrite(&numClientes, sizeof(int), 1, arquivo);
    fwrite(clientes, sizeof(Pessoa), numClientes, arquivo);

    // Salvar número de empréstimos e empréstimos
    fwrite(&numEmprestimos, sizeof(int), 1, arquivo);
    fwrite(emprestimos, sizeof(Emprestimo), numEmprestimos, arquivo);

    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}

// Função para pausar a execução
void PausarEContinuar()
{
    printf("\nPressione qualquer tecla para continuar...\n");
    getchar();
    getchar();
}
