#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Estrutura para representar uma carta de cidade
typedef struct {
    char codigo[4];  // Formato: A01, A02, etc. (3 chars + null terminator)
    int populacao;   // População (inteiro)
    float area;      // Área em km² (float)
    float pib;       // PIB em milhões de reais (float)
    int pontos_turisticos;  // Número de pontos turísticos (inteiro)
    float densidade; // Densidade Populacional (calculada: hab/km²)
    float pib_per_capita;  // PIB per Capita (calculada: R$/habitante)
} Carta;

// Função para cadastrar uma única carta
// Calcula densidade e PIB per capita automaticamente
// Retorna 1 se sucesso, 0 se inválido (e sai do programa para simplicidade)
int cadastrar_carta(Carta *carta) {
    printf("\n--- Cadastro de Nova Carta ---\n");
    
    // Ler código da carta
    printf("Digite o código da carta (ex: A01): ");
    scanf("%3s", carta->codigo);  // Lê até 3 chars
    getchar();  // Limpa o buffer do newline
    
    // Validação do código
    if (strlen(carta->codigo) != 3 ||
        !isalpha(carta->codigo[0]) || 
        toupper(carta->codigo[0]) < 'A' || toupper(carta->codigo[0]) > 'H' ||
        !isdigit(carta->codigo[1]) || !isdigit(carta->codigo[2]) ||
        (carta->codigo[1] != '0' || (carta->codigo[2] < '1' || carta->codigo[2] > '4'))) {
        printf("Código inválido! Deve ser como A01, B02, etc. (Estado A-H, Cidade 1-4).\n");
        return 0;  // Inválido
    }
    
    // Converter para uppercase se necessário
    for (int i = 0; i < 3; i++) {
        carta->codigo[i] = toupper(carta->codigo[i]);
    }
    
    // População
    printf("Digite a população (número inteiro > 0): ");
    if (scanf("%d", &carta->populacao) != 1 || carta->populacao <= 0) {
        printf("Entrada inválida para população! Deve ser um inteiro positivo.\n");
        return 0;
    }
    
    // Área
    printf("Digite a área em km² (pode ser decimal > 0): ");
    if (scanf("%f", &carta->area) != 1 || carta->area <= 0) {
        printf("Entrada inválida para área! Deve ser um número positivo.\n");
        return 0;
    }
    
    // PIB
    printf("Digite o PIB em milhões (pode ser decimal >= 0): ");
    if (scanf("%f", &carta->pib) != 1 || carta->pib < 0) {
        printf("Entrada inválida para PIB! Deve ser um número não negativo.\n");
        return 0;
    }
    
    // Pontos turísticos
    printf("Digite o número de pontos turísticos (inteiro >= 0): ");
    if (scanf("%d", &carta->pontos_turisticos) != 1 || carta->pontos_turisticos < 0) {
        printf("Entrada inválida para pontos turísticos! Deve ser um inteiro não negativo.\n");
        return 0;
    }
    
    // Calcular propriedades derivadas
    // Densidade Populacional: população / área (hab/km²)
    carta->densidade = (float)carta->populacao / carta->area;
    
    // PIB per Capita: (PIB em milhões * 1.000.000) / população = R$/habitante
    if (carta->populacao > 0) {  // Já validado acima
        carta->pib_per_capita = (carta->pib * 1000000.0f) / (float)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0f;
    }
    
    return 1;  // Sucesso
}

// Função para exibir todas as cartas cadastradas
void exibir_cartas(Carta *cartas, int num_cartas) {
    if (num_cartas == 0) {
        printf("\nNenhuma carta cadastrada.\n");
        return;
    }
    
    printf("\n--- Cartas Cadastradas ---\n");
    for (int i = 0; i < num_cartas; i++) {
        printf("\nCarta: %s\n", cartas[i].codigo);
        printf("População: %d\n", cartas[i].populacao);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("PIB: R$ %.2f milhões\n", cartas[i].pib);
        printf("Pontos Turísticos: %d\n", cartas[i].pontos_turisticos);
        printf("Densidade Populacional: %.2f hab/km²\n", cartas[i].densidade);
        printf("PIB per Capita: R$ %.2f / habitante\n", cartas[i].pib_per_capita);
        printf("----------------------------\n");
    }
}

int main() {
    Carta cartas[100];  // Array fixo para até 100 cartas (suficiente para nível aventureiro)
    int num_cartas = 0;
    char opcao;
    
    printf("Bem-vindo ao Sistema de Cadastro de Super Trunfo - Países (Nível Aventureiro)!\n");
    printf("Agora com cálculos automáticos de Densidade Populacional e PIB per Capita.\n");
    printf("Você pode cadastrar quantas cartas quiser. Digite 'n' para parar.\n\n");
    
    do {
        printf("Deseja cadastrar uma nova carta? (s/n): ");
        scanf(" %c", &opcao);  // Espaço antes de %c para ignorar whitespace
        getchar();  // Limpa buffer
        
        if (opcao == 'n' || opcao == 'N') {
            break;
        } else if (opcao == 's' || opcao == 'S') {
            if (num_cartas >= 100) {
                printf("Limite de 100 cartas atingido!\n");
                break;
            }
            if (cadastrar_carta(&cartas[num_cartas])) {
                printf("Carta %s cadastrada com sucesso!\n", cartas[num_cartas].codigo);
                printf("Densidade calculada: %.2f hab/km²\n", cartas[num_cartas].densidade);
                printf("PIB per Capita calculado: R$ %.2f / habitante\n", cartas[num_cartas].pib_per_capita);
                num_cartas++;
            } else {
                printf("Cadastro cancelado devido a erro.\n");
                exit(1);  // Para simplicidade, sai se inválido
            }
        } else {
            printf("Opção inválida. Digite 's' para sim ou 'n' para não.\n");
        }
    } while (1);
    
    // Exibe todas as cartas cadastradas
    exibir_cartas(cartas, num_cartas);
    
    printf("\nObrigado por usar o sistema! Fim do cadastro.\n");
    
    return 0;
}
