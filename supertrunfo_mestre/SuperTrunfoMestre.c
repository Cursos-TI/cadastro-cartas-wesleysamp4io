// Estrutura inicial para o Super Trunfo Mestre
// Adicione aqui o código referente ao nível Mestre.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Estrutura para representar uma carta de cidade
typedef struct {
    char codigo[4];              // Formato: A01, A02, etc. (3 chars + null terminator)
    long long populacao;         // População (long long para grandes números)
    float area;                  // Área em km² (float)
    float pib;                   // PIB em milhões de reais (float)
    int pontos_turisticos;       // Número de pontos turísticos (int)
    float densidade;             // Densidade Populacional (calculada: hab/km²)
    double pib_per_capita;       // PIB per Capita (calculada: R$/habitante, double para precisão)
    double super_poder;          // Super Poder: soma de todas as propriedades (double para precisão)
} Carta;

// Função para encontrar o índice de uma carta pelo código
// Retorna o índice se encontrada, -1 se não
int encontrar_carta(Carta *cartas, int num_cartas, char *codigo_busca) {
    char codigo_upper[4];
    strncpy(codigo_upper, codigo_busca, 3);
    codigo_upper[3] = '\0';
    for (int i = 0; i < 3; i++) {
        codigo_upper[i] = toupper(codigo_upper[i]);
    }
    
    for (int i = 0; i < num_cartas; i++) {
        if (strcmp(cartas[i].codigo, codigo_upper) == 0) {
            return i;
        }
    }
    return -1;
}

// Função para cadastrar uma única carta
// Calcula densidade, PIB per capita e super poder automaticamente
// Retorna 1 se sucesso, 0 se inválido
int cadastrar_carta(Carta *carta) {
    printf("\n--- Cadastro de Nova Carta ---\n");
    
    // Ler código da carta
    printf("Digite o código da carta (ex: A01): ");
    scanf("%3s", carta->codigo);
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
    
    // População (long long para grandes números)
    printf("Digite a população (número inteiro > 0): ");
    if (scanf("%lld", &carta->populacao) != 1 || carta->populacao <= 0) {
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
    
    // PIB per Capita: (PIB em milhões * 1.000.000) / população = R$/habitante (double para precisão)
    if (carta->populacao > 0) {
        carta->pib_per_capita = (carta->pib * 1000000.0) / (double)carta->populacao;
    } else {
        carta->pib_per_capita = 0.0;
    }
    
    // Super Poder: soma de todas as propriedades (converter para double)
    carta->super_poder = (double)carta->populacao + 
                         (double)carta->area + 
                         (double)carta->pib + 
                         (double)carta->pontos_turisticos + 
                         (double)carta->densidade + 
                         carta->pib_per_capita;
    
    return 1;  // Sucesso
}

// Função para exibir todas as cartas cadastradas (incluindo novas propriedades)
void exibir_cartas(Carta *cartas, int num_cartas) {
    if (num_cartas == 0) {
        printf("\nNenhuma carta cadastrada.\n");
        return;
    }
    
    printf("\n--- Cartas Cadastradas ---\n");
    for (int i = 0; i < num_cartas; i++) {
        printf("\nCarta: %s\n", cartas[i].codigo);
        printf("População: %lld\n", cartas[i].populacao);
        printf("Área: %.2f km²\n", cartas[i].area);
        printf("PIB: R$ %.2f milhões\n", cartas[i].pib);
        printf("Pontos Turísticos: %d\n", cartas[i].pontos_turisticos);
        printf("Densidade Populacional: %.2f hab/km²\n", cartas[i].densidade);
        printf("PIB per Capita: R$ %.2f / habitante\n", carta[i].pib_per_capita);
        printf("Super Poder: %.2f\n", cartas[i].super_poder);
        printf("----------------------------\n");
    }
}

// Função para comparar duas cartas
// Usa operadores relacionais para determinar vencedores por propriedade
// Exibe resultados e retorna 1 se carta1 vence geral (maior super_poder), 2 se carta2, 0 se empate
int comparar_cartas(Carta *c1, Carta *c2) {
    printf("\n--- Comparação entre %s e %s ---\n", c1->codigo, c2->codigo);
    
    int vitorias_c1 = 0, vitorias_c2 = 0, empates = 0;
    
    // Comparação por População (maior vence)
    printf("\nPopulação:\n");
    printf("  %s: %lld\n", c1->codigo, c1->populacao);
    printf("  %s: %lld\n", c2->codigo, c2->populacao);
    if (c1->populacao > c2->populacao) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->populacao < c2->populacao) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por Área (maior vence)
    printf("\nÁrea:\n");
    printf("  %s: %.2f km²\n", c1->codigo, c1->area);
    printf("  %s: %.2f km²\n", c2->codigo, c2->area);
    if (c1->area > c2->area) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->area < c2->area) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por PIB (maior vence)
    printf("\nPIB:\n");
    printf("  %s: R$ %.2f milhões\n", c1->codigo, c1->pib);
    printf("  %s: R$ %.2f milhões\n", c2->codigo, c2->pib);
    if (c1->pib > c2->pib) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->pib < c2->pib) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por Pontos Turísticos (maior vence)
    printf("\nPontos Turísticos:\n");
    printf("  %s: %d\n", c1->codigo, c1->pontos_turisticos);
    printf("  %s: %d\n", c2->codigo, c2->pontos_turisticos);
    if (c1->pontos_turisticos > c2->pontos_turisticos) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->pontos_turisticos < c2->pontos_turisticos) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por Densidade Populacional (menor vence)
    printf("\nDensidade Populacional:\n");
    printf("  %s: %.2f hab/km²\n", c1->codigo, c1->densidade);
    printf("  %s: %.2f hab/km²\n", c2->codigo, c2->densidade);
    if (c1->densidade < c2->densidade) {
        printf("  Vencedor: %s (menor)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->densidade > c2->densidade) {
        printf("  Vencedor: %s (menor)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por PIB per Capita (maior vence)
    printf("\nPIB per Capita:\n");
    printf("  %s: R$ %.2f / habitante\n", c1->codigo, c1->pib_per_capita);
    printf("  %s: R$ %.2f / habitante\n", c2->codigo, c2->pib_per_capita);
    if (c1->pib_per_capita > c2->pib_per_capita) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->pib_per_capita < c2->pib_per_capita) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Comparação por Super Poder (maior vence)
    printf("\nSuper Poder:\n");
    printf("  %s: %.2f\n", c1->codigo, c1->super_poder);
    printf("  %s: %.2f\n", c2->codigo, c2->super_poder);
    if (c1->super_poder > c2->super_poder) {
        printf("  Vencedor: %s (maior)\n", c1->codigo);
        vitorias_c1++;
    } else if (c1->super_poder < c2->super_poder) {
        printf("  Vencedor: %s (maior)\n", c2->codigo);
        vitorias_c2++;
    } else {
        printf("  Empate\n");
        empates++;
    }
    
    // Resumo
    printf("\n--- Resumo da Comparação ---\n");
    printf("Vitórias %s: %d\n", c1->codigo, vitorias_c1);
    printf("Vitórias %s: %d\n", c2->codigo, vitorias_c2);
    printf("Empates: %d\n", empates);
    
    // Vencedor geral baseado em Super Poder
    if (c1->super_poder > c2->super_poder) {
        printf("\nVencedor Geral: %s (maior Super Poder)!\n", c1->codigo);
        return 1;
    } else if (c1->super_poder < c2->super_poder) {
        printf("\nVencedor Geral: %s (maior Super Poder)!\n", c2->codigo);
        return 2;
    } else {
        printf("\nEmpate Geral no Super Poder!\n");
        return 0;
    }
}

int main() {
    Carta cartas[100];  // Array fixo para até 100 cartas
    int num_cartas = 0;
    char opcao;
    char codigo1[4], codigo2[4];
    int idx1, idx2;
    
    printf("Bem-vindo ao Sistema de Cadastro de Super Trunfo - Países (Nível Mestre)!\n");
    printf("Agora com comparações entre cartas e Super Poder calculado.\n");
    printf("Você pode cadastrar quantas cartas quiser. Digite 'n' para parar o cadastro.\n\n");
    
    // Loop de cadastro
    do {
        printf("Deseja cadastrar uma nova carta? (s/n): ");
        scanf(" %c", &opcao);
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
                printf("Super Poder calculado: %.2f\n", cartas[num_cartas].super_poder);
                num_cartas++;
            } else {
                printf("Cadastro cancelado devido a erro.\n");
                exit(1);
            }
        } else {
            printf("Opção inválida. Digite 's' para sim ou 'n' para não.\n");
        }
    } while (1);
    
    // Exibe todas as cartas cadastradas
    exibir_cartas(cartas, num_cartas);
    
    // Loop de comparações
    if (num_cartas >= 2) {
        printf("\n--- Modo de Comparação ---\n");
        printf("Você pode comparar cartas cadastradas. Digite 'sair' para parar.\n");
        
        while (1) {
            printf("\nDeseja comparar duas cartas? (s/n ou 'sair'): ");
            scanf("%3s", codigo1);
            getchar();
            
            if (strcmp(codigo1, "sair") == 0 || strcmp(codigo1, "n") == 0) {
                break;
            } else if (strcmp(codigo1, "s") == 0) {
                printf("Digite o código da primeira carta: ");
                scanf("%3s", codigo1);
                getchar();
                
                printf("Digite o código da segunda carta: ");
                scanf("%3s", codigo2);
                getchar();
                
                idx1 = encontrar_carta(cartas, num_cartas, codigo1);
                idx2 = encontrar_carta(cartas, num_cartas, codigo2);
                
                if (idx1 == -1) {
                    printf("Carta %s não encontrada!\n", codigo1);
                    continue;
                }
                if (idx2 == -1) {
                    printf("Carta %s não encontrada!\n", codigo2);
                    continue;
                }
                if (idx1 == idx2) {
                    printf("Não é possível comparar a mesma carta!\n");
                    continue;
                }
                
                comparar_cartas(&cartas[idx1], &cartas[idx2]);
            } else {
                printf("Opção inválida. Digite 's' para sim, 'n' para não ou 'sair'.\n");
            }
        }
    } else {
        printf("\nCadastre pelo menos 2 cartas para usar o modo de comparação.\n");
    }
    
    printf("\nObrigado por usar o sistema! Fim da sessão.\n");
    
    return 0;
}

