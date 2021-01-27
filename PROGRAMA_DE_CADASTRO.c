//SISTEMA PARA CADASTRO DE PACIENTES

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>  //bibliotecas importadas
#include <time.h>




typedef struct data DATA; //estrutura de nascimento separadas
struct data{
      int days;
      int month;
      int year;   //variaveis

      int data_diag;
      int data_nost;
      int data_ico;

};

typedef struct contato CONTATO; //estrutura para cadastro
struct contato{
     char nome_paciente[50]; //variaveis
     int cpf;
     int telefone;
     char email[50];

     char comorbidade[50];

     char rua[50];
     int numero;
     char bairro[50];
     char cidade[50];
     char estado[50];
     int cep;

     DATA aniv; //Chamo a estrutura DATA na estrutura CONTATO com uma variavel(aniv)
};

void cabecalho();  //variaveis
void inputData();
void listar();


main(){
    int opcao;
    char usuario[50]= "abcd";  //usuario de acesso
    char *usuario1[50];
    char senha[50]= "1234";    //senha de acesso
    char *senha1[50];


  printf("____________Solicitacao de login______________\n\nDigite o usuario:");  //printf escreve na tela
  scanf("%s", &usuario1);    //scanf faz a leitura do que foi escrito e armazena na String "usuario1"
  printf("Digite a senha:");
  scanf("%s", &senha1);
  if(strcmp(usuario,usuario1) ==0) //função strcmp que compara duas String.
  if(strcmp(senha,senha1) ==0){
  printf("\nSeja bem vindo!\n");// caso a solicitação de senha seja igual a registrada no sistema, o usuario terá acesso a todo o programa
  getchar();

    do{
            cabecalho();
        printf("1 - Cadastrar\n");
        printf("2 - Listar Pacientes\n"); //menu interativo
        printf("3 - Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);


        switch(opcao){ //função para chamar as funções
          case 1:
                inputData();
            break;

          case 2:
                listar();
            break;

          case 3:
              printf("Saindo....");
            break;

          default:
              printf("Opcao invalida!"); //caso o usuario selecione algum numero fora da lista
              getch();
            break;
        }

    }while(opcao != 3); //o menu só vai sair se a opção for 3

  }else{
      printf("\n__________Acesso negado___________\n");   //acesso negado ao errar a senha, será fechado o programa
  }

}
    void cabecalho(){  //função cabecalho
    system("cls");
         printf("\n\n________________Cadastro de Paciente________________\n\n");
    }


    void inputData(){


        int isLeapYear(int year, int mon)//verifique se o ano dado é bissexto ou não
{
    int flag = 0;
    if (year % 100 == 0)
    {
            if (year % 400 == 0)
            {
                    if (mon == 2)
                    {
                            flag = 1;
                    }
            }
    }
    else if (year % 4 == 0)
    {
            if (mon == 2)
            {
                    flag = 1;
            }
    }
    return (flag);
}
         int DaysInMon[] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};
         char dob[100];
         time_t ts;
         struct tm *ct;

         FILE *Paciente_cadastro, *risco_covid; //criação de arquivo
         CONTATO ctt;


        Paciente_cadastro = fopen("cadastros_Paciente.txt", "ab");  //Arquivo gravado em binario "ab"
        risco_covid = fopen("Grupo_de_Risco.txt", "ab"); //arquivo criado no diretorio do programa

        if(Paciente_cadastro == NULL || risco_covid == NULL){
            printf("Nao foi possivel a abertura!\n");
        }
         else{
            do{
            cabecalho();

    fflush(stdin); //limpa lixos que foram deixados no caminho
    printf("\n\nNome_____________:");
    gets(ctt.nome_paciente);

    printf("\nDigite o CPF_____________:");
    scanf("%d", &ctt.cpf);

    printf("\nData do nascimento(dd mm aaaa)_____________:");
    scanf("%d %d %d", &ctt.aniv.days, &ctt.aniv.month, &ctt.aniv.year);

    //obter a data atual no sistema
    ts = time(NULL);
    ct = localtime(&ts);

    ctt.aniv.days = DaysInMon[ctt.aniv.month - 1] - ctt.aniv.days + 1;

                               //verificação de ano bissexto
    if (isLeapYear(ctt.aniv.year, ctt.aniv.month))
    {
            ctt.aniv.days = ctt.aniv.days + 1;
    }


//calculando a idade em número de dias, anos e meses
    ctt.aniv.days = ctt.aniv.days + ct->tm_mday;
    ctt.aniv.month = (12 - ctt.aniv.month) + (ct->tm_mon);
    ctt.aniv.year = (ct->tm_year + 1900) - ctt.aniv.year - 1;


//verificar ano bissexto de fevereiro - 29 dias
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1)))
    {
            if (ctt.aniv.days >= (DaysInMon[ct->tm_mon] + 1))
            {
                    ctt.aniv.days = ctt.aniv.days - (DaysInMon[ct->tm_mon] + 1);
                    ctt.aniv.month = ctt.aniv.month + 1;
            }
    }
    else if (ctt.aniv.days >= DaysInMon[ct->tm_mon])
    {
            ctt.aniv.days = ctt.aniv.days - (DaysInMon[ct->tm_mon]);
            ctt.aniv.month = ctt.aniv.month + 1;
    }

    if (ctt.aniv.month >= 12)
    {
            ctt.aniv.year = ctt.aniv.year + 1;
            ctt.aniv.month = ctt.aniv.month - 12;
    }

    // retorna a idade em ano, mes e dia.
    printf("\nEle tem %d anos %d mes e %d dias.\n", ctt.aniv.year, ctt.aniv.month, ctt.aniv.days);

    if(ctt.aniv.year >= 65 ){   //verificar se o paciente esta acima dos 65 anos ou igual.
    printf("\n\t\t_________ATENCAO_________\n_________Paciente pertence ao grupo de risco_________\n___________FOI CRIADO UM ARQUIVO SEPARADO___________\n");
}
else   //se ele não for do grupo de risco, será acionado a funcão else.
{
    printf("\t\tPaciente nao e do grupo de risco.\n"); //else retorna essa frase
}

    printf("\nTelefone para contato_____________:");
    scanf("%d", &ctt.telefone);

    fflush(stdin);
    printf("\nEmail_____________:");
    gets(ctt.email);

    fflush(stdin);
    printf("\nRua do Paciente_____________:");
    gets(ctt.rua);

    printf("\nNumero da casa_____________:");
    scanf("%d", &ctt.numero);

    fflush(stdin);
    printf("\nBairro_____________:");
    gets(ctt.bairro);

    fflush(stdin);
    printf("\nCidade_____________:");
    gets(ctt.cidade);

    fflush(stdin);
    printf("\nEstado_____________:");
    gets(ctt.estado);

    printf("\nCEP_____________:");
    scanf("%d", &ctt.cep);

    printf("\nData do diagnostico(dd mm aaaa)_____________:");
    scanf("%d %d %d", &ctt.aniv.data_diag, &ctt.aniv.data_nost, &ctt.aniv.data_ico);

    fflush(stdin);
    printf("\nPaciente possui comorbidade?_____________:");
    gets(ctt.comorbidade);

    fwrite(&ctt, sizeof(CONTATO), 1, Paciente_cadastro); //faz a gravacão do arquivo

    printf("Deseja cotinuar(s/n)?"); // laço de repetição para continuar cadastrando

        if(ctt.aniv.year >= 65){      //acima ou igual a 65 anos grava no arquivo "risco_covid"

        fprintf(risco_covid, "Idade = %d\n", ctt.aniv.year); //somente essas duas variaveis são gravadas
        fprintf(risco_covid, "CEP = %d\n\n", ctt.cep);
        }


         }while(getche() == 's'); //laço de repetição enquanto for "s"
         fclose(Paciente_cadastro); //fecha os arquivos
         fclose(risco_covid);
    }


}




void listar(){                  //função listar
        FILE* Paciente_cadastro;
        CONTATO ctt;

        Paciente_cadastro = fopen("cadastros_Paciente.txt", "rb"); //Leitura covertendo binario para numeros humanos

        if(Paciente_cadastro == NULL){
            printf("Nao foi possivel a abertura!\n"); //caso o arquivo não abra
        }
         else{
            while(fread(&ctt, sizeof(CONTATO), 1, Paciente_cadastro)==1){
                printf("Nome: %s\n", ctt.nome_paciente);
                printf("CPF: %d\n",ctt.cpf);
                printf("idade: %d\n", ctt.aniv.year);
                printf("Telefone: %d\n", ctt.telefone);
                printf("Email: %s", ctt.email);
                printf("Rua: %s - %d - %s\n", ctt.rua, ctt.numero, ctt.bairro);
                printf("Cidade e Estado: %s, %s\n", ctt.cidade, ctt.estado);
                printf("CEP: %d\n", ctt.cep);
                printf("Data do Diagnostico: %d/%d/%d\n", ctt.aniv.data_diag, ctt.aniv.data_nost, ctt.aniv.data_ico);
                printf("Comorbidade do paciente: %s\n", ctt.comorbidade);
                printf("---------------------------------------------------------\n\n");
                }

         }
          fclose(Paciente_cadastro); //fecha o arquivo
          getch(); //função para pausar e ver as informações na tela



}







