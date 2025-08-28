#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int x, q;
    char nome[50];
    FILE *ponteiro;
    printf("================================\nControle de Estoque\n================================\nSelecione uma opcao:\n1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\nOpcao:");
    scanf("%d", &x);

    while(x<1 || x>4){
        printf("Opcao invalida! Tente novamente.\nDigite um numero de 1 a 4: ");
        scanf("%d", &x);
    }
    if(x==4){
        printf("Obrigado por usar o Controle de Estoques! Ate a proxima.");
        return 0;
    }
    if(x==1){
        printf("Digite o nome do item:");
        scanf("%s", nome);
        printf("Digite a quantidade:");
        scanf("%d", &q);

    ponteiro= fopen("estoque.txt", "a");
    if(ponteiro == NULL){
        printf("Erro");
        return 1;
    }else{
        fprintf(ponteiro, "%s\n%d\n", nome, q);
        printf("Item adicionado com sucesso!\n");
        fclose(ponteiro);
    }
}
    if(x==2){
        printf("Digite o nome do item:");
        scanf("%s", nome);
        printf("Digite a quantidade:");
        scanf("%d", &q);


    ponteiro= fopen("estoque.txt", "r");
    if(ponteiro == NULL){
        printf("Erro");
        return 1;
    }
    FILE *novo= fopen("temp.txt", "w");
    if(novo==NULL){
        printf("Erro");
        return 1;
    }

    int encontrado = 0;  // Flag para indicar se o nome foi encontrado
    char nome_lido[50];
    int quantidade_lida;

    while (fgets(nome_lido, sizeof(nome_lido), ponteiro)!=NULL){
        nome_lido[strcspn(nome_lido, "\n")] = '\0';
        fscanf(ponteiro, "%d\n", &quantidade_lida);
        if(strcmp(nome_lido, nome)!=0){
            fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida);
        }
        if(strcmp(nome_lido, nome)==0){
            encontrado= 1;
           if(quantidade_lida < q){
            printf("Estoque insuficiente. Quantidade disponivel: %d\n", quantidade_lida);
            fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida);
           }
           else if(quantidade_lida > q){
            fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida-q);
            printf("Quantidade atualizada com sucesso!\n");
           }
           else if(quantidade_lida==q){
            printf("Item removido do estoque\n");
           }}
           if(!encontrado){
            printf("Item nao encontrado.\n");
            }
           }

 fclose(ponteiro);
 fclose(novo);
 remove("estoque.txt");
 rename("temp.txt", "estoque.txt");
 }
    if(x==3){
       ponteiro= fopen("estoque.txt", "r");
       if(ponteiro==NULL){
        printf("Erro ao abrir arquivo.\n");
        return 1;
       }
       char nome_lido[50];
       int quantidade_lida;
       printf("=============================\nEstoque Atual\n=============================\n");
        while(fgets(nome_lido, sizeof(nome_lido), ponteiro)!=NULL){
                nome_lido[strcspn(nome_lido, "\n")] = '\0';
        fscanf(ponteiro, "%d\n", &quantidade_lida);
        printf("Nome: %s\nQuantidade: %d\n---------------------\n", nome_lido, quantidade_lida);
        }
        fclose(ponteiro);
        }
 return 0;
}
