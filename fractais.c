#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ITERATIONS 6

void gerarSequenciaFractal(char *axioma, char *regra, double angulo, int tipoFractal, FILE *arquivo) {
    char *nomeTipoFractal;

    switch (tipoFractal) {
        case 3:
            nomeTipoFractal = "Floco de Neve Onda Senoidal 1 de Von Koch";
            break;
        case 6:
            nomeTipoFractal = "Preenchimento de Hilbert";
            break;
        default:
            nomeTipoFractal = "Fractal Inválido";
            break;
    }

    char *sequencia = (char *)malloc(1 + strlen(axioma));
    strcpy(sequencia, axioma);

    fprintf(arquivo, "Tipo de Fractal: %s\n", nomeTipoFractal);
    fprintf(arquivo, "Ângulo dado em graus: %.1f\n", angulo);
    fprintf(arquivo, "Iteração\tQuantidade de Segmentos\tQuantidade de Símbolos\tSequência\n");
    fprintf(arquivo, "---------------------------------------------------------------------------------------------------------\n");

    int i, j;
    for (i = 0; i < MAX_ITERATIONS; i++) {
        char *proximaSequencia = (char *)malloc(strlen(sequencia) * strlen(regra) + 1);
        proximaSequencia[0] = '\0';

        int contagemSegmentos = 0;
        int contagemSimbolos = 0;

        for (j = 0; j < (int)strlen(sequencia); j++) {
            if (sequencia[j] == 'F') {
                contagemSegmentos++;
                contagemSimbolos += strlen(regra);
                strcat(proximaSequencia, regra);
            } else {
                contagemSimbolos++;
                strncat(proximaSequencia, &sequencia[j], 1);
            }
        }

        fprintf(arquivo, "%8d\t%22d\t%20d\t%s\n", i + 1, contagemSegmentos, contagemSimbolos, sequencia);
        fflush(arquivo);

        free(sequencia);
        sequencia = proximaSequencia;
    }

    fflush(arquivo);
    free(sequencia);
}

void gerarSequenciaFractalHilbert(char *axioma, double angulo, char *regra1, char *regra2, FILE *arquivo) {
    char *nomeTipoFractal = "Preenchimento de Hilbert";

    char *sequencia = (char *)malloc(strlen(axioma) + 1);
    strcpy(sequencia, axioma);

    fprintf(arquivo, "Tipo de Fractal: %s\n", nomeTipoFractal);
    fprintf(arquivo, "Ângulo dado em graus: %.1f\n", angulo);
    fprintf(arquivo, "Iteração\tQuantidade de Segmentos\tQuantidade de Símbolos\tSequência\n");
    fprintf(arquivo, "---------------------------------------------------------------------------------------------------------\n");

    int i, j;
    for (i = 0; i < MAX_ITERATIONS; i++) {
        char *proximaSequencia = (char *)malloc(strlen(sequencia) * (strlen(regra1) + strlen(regra2)) + 1);
        proximaSequencia[0] = '\0';

        int contagemSegmentos = 0;
        int contagemSimbolos = 0;

        for (j = 0; j < (int)strlen(sequencia); j++) {
            if (sequencia[j] == 'X') {
                contagemSegmentos++;
                contagemSimbolos += strlen(regra1);
                strcat(proximaSequencia, regra1);
            } else if (sequencia[j] == 'Y') {
                contagemSegmentos++;
                contagemSimbolos += strlen(regra2);
                strcat(proximaSequencia, regra2);
            } else {
                contagemSimbolos++;
                strncat(proximaSequencia, &sequencia[j], 1);
            }
        }

        fprintf(arquivo, "%8d\t%22d\t%20d\t%s\n", i + 1, contagemSegmentos, contagemSimbolos, proximaSequencia);
        fflush(arquivo);

        free(sequencia);
        sequencia = proximaSequencia;
    }

    // Remove os símbolos X e Y da sequência final
    char *sequenciaFinal = (char *)malloc(strlen(sequencia) + 1);
    int index = 0;
    int v;
    for (v = 0; v < (int)strlen(sequencia); v++) {
        if (sequencia[v] != 'X' && sequencia[v] != 'Y') {
            sequenciaFinal[index++] = sequencia[v];
        }
    }

    sequenciaFinal[index] = '\0';

    fprintf(arquivo, "\nSequência Final:\n%s\n", sequenciaFinal);
    fflush(arquivo);
    free(sequencia);
    free(sequenciaFinal);
}

int main() {
    char axioma[100];
    double angulo;
    int tipoFractal;
    char regra1[100];
    char regra2[100];

    printf("Digite o tipo de fractal (3 - Senoidal de Von Koch, 6 - Preenchimento de Hilbert): ");
    scanf("%d", &tipoFractal);
    printf("Digite o axioma: ");
    scanf("%s", axioma);
    printf("Digite o ângulo em graus: ");
    scanf("%lf", &angulo);

    if (tipoFractal == 3) {
        FILE *arquivo = fopen("senoidal_de_von_koch.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
        printf("Digite a regra de formação: ");
        scanf("%s", regra1);

        gerarSequenciaFractal(axioma, regra1, angulo, tipoFractal, arquivo);
        fclose(arquivo);
    } 
    else if (tipoFractal == 6) {
        FILE *arquivo = fopen("hilbert.txt", "w");
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

        printf("Digite a primeira regra de formação: ");
        scanf("%s", regra1);

        printf("Digite a segunda regra de formação: ");
        scanf("%s", regra2);

        gerarSequenciaFractalHilbert(axioma, angulo, regra1, regra2, arquivo);
        fclose(arquivo);
    } 

    printf("Sequência fractal gerada com sucesso. Consulte o arquivo criado na posta de origem.\n");
    return 0;
}