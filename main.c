#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int x, q;
    char nome[50];
    FILE *ponteiro;

    // Loop principal do menu
    do {
        printf("================================\n");
        printf("Controle de Estoque\n");
        printf("================================\n");
        printf("Selecione uma opcao:\n");
        printf("1. Adicionar Item\n");
        printf("2. Remover Item\n");
        printf("3. Listar Estoque\n");
        printf("4. Sair\n");
        printf("Opcao: ");
        scanf("%d", &x);

        while (x < 1 || x > 4) {
            printf("Opcao invalida! Tente novamente.\n");
            printf("Digite um numero de 1 a 4: ");
            scanf("%d", &x);
        }

        if (x == 1) {
            printf("Digite o nome do item: ");
            scanf("%s", nome);
            printf("Digite a quantidade: ");
            scanf("%d", &q);

            ponteiro = fopen("estoque.txt", "a");
            if (ponteiro == NULL) {
                printf("Erro ao abrir o arquivo!\n");
                return 1;
            } else {
                fprintf(ponteiro, "%s\n%d\n", nome, q);
                printf("Item adicionado com sucesso!\n\n");
                fclose(ponteiro);
            }
        } else if (x == 2) {
            printf("Digite o nome do item que deseja remover/atualizar: ");
            scanf("%s", nome);
            printf("Digite a quantidade a ser removida: ");
            scanf("%d", &q);

            ponteiro = fopen("estoque.txt", "r");
            if (ponteiro == NULL) {
                printf("Erro: nao foi possivel ler o estoque. O arquivo pode nao existir.\n");
                continue; // Volta para o menu
            }

            FILE *novo = fopen("temp.txt", "w");
            if (novo == NULL) {
                printf("Erro ao criar arquivo temporario!\n");
                fclose(ponteiro);
                return 1;
            }

            char nome_lido[50];
            int quantidade_lida;
            int encontrado = 0;

            // <<-- MUDANÇA PRINCIPAL AQUI -->>
            // Vamos ler o nome e a quantidade juntos. É mais seguro.
            while (fscanf(ponteiro, "%s\n%d\n", nome_lido, &quantidade_lida) == 2) {
                // Se o nome lido for o que queremos remover...
                if (strcmp(nome_lido, nome) == 0) {
                    encontrado = 1; // Marcamos que encontramos o item

                    if (quantidade_lida > q) {
                        // Se a quantidade no estoque for maior, a gente subtrai e escreve no novo arquivo
                        fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida - q);
                        printf("Quantidade de '%s' atualizada com sucesso!\n", nome_lido);
                    } else if (quantidade_lida == q) {
                        // Se for igual, o item é totalmente removido. A gente simplesmente NÃO escreve ele no novo arquivo.
                        printf("Item '%s' removido completamente do estoque.\n", nome_lido);
                    } else { // quantidade_lida < q
                        // Se a quantidade for insuficiente, avisamos e escrevemos o valor original de volta.
                        printf("Estoque insuficiente para '%s'. Quantidade disponivel: %d\n", nome_lido, quantidade_lida);
                        fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida);
                    }
                } else {
                    // Se o nome for diferente, apenas copiamos a linha para o novo arquivo.
                    fprintf(novo, "%s\n%d\n", nome_lido, quantidade_lida);
                }
            }

            fclose(ponteiro);
            fclose(novo);

            // <<-- Lógica movida para fora do loop -->>
            // Se depois de ler o arquivo inteiro a flag "encontrado" for 0, o item não existe.
            if (!encontrado) {
                printf("Item '%s' nao encontrado no estoque.\n", nome);
            }

            remove("estoque.txt");
            rename("temp.txt", "estoque.txt");
            printf("\n");

        } else if (x == 3) {
            ponteiro = fopen("estoque.txt", "r");
            if (ponteiro == NULL) {
                printf("Estoque vazio ou nao encontrado.\n\n");
                continue;
            }

            char nome_lido[50];
            int quantidade_lida;
            int estoque_vazio = 1;

            printf("=============================\n");
            printf("Estoque Atual\n");
            printf("=============================\n");

            // Usamos a mesma lógica de leitura segura
            while (fscanf(ponteiro, "%s\n%d\n", nome_lido, &quantidade_lida) == 2) {
                printf("Nome: %s\nQuantidade: %d\n", nome_lido, quantidade_lida);
                printf("---------------------\n");
                estoque_vazio = 0;
            }

            if (estoque_vazio) {
                printf("Estoque vazio.\n\n");
            }
            fclose(ponteiro);
            printf("\n");
        }

    } while (x != 4); // O loop continua enquanto a opção não for 4

    printf("Obrigado por usar o Controle de Estoques! Ate a proxima.\n");
    return 0;
}