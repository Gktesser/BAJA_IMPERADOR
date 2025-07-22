#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#ifdef _WIN32
#else
#include <unistd.h>
#endif

void pausar(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
    #else
        sleep(segundos);
    #endif
}

// Códigos ANSI para cores no terminal
#define ANSI_RESET         "\x1b[0m"
#define ANSI_RED           "\x1b[31m"
#define ANSI_YELLOW        "\x1b[33m"
#define ANSI_GREEN         "\x1b[32m"
#define ANSI_CYAN          "\x1b[36m"
#define ANSI_WHITE         "\x1b[37m"
#define ANSI_BOLD          "\x1b[1m"

void simular_enduro_baja() {
    float suspensao = 100.0f;
    float combustivel = 100.0f;
    float motor_temp = 80.0f;
    int total_voltas = 100;
    int falha_critica = 0;

    printf(ANSI_CYAN ANSI_BOLD "--- INICIO DA SIMULACAO DE ENDURO DO BAJA ---\n" ANSI_RESET);
    printf("Status inicial: Suspensao: %.1f%%, Combustivel: %.1f%%, Motor: %.1f°C\n\n",
           suspensao, combustivel, motor_temp);
    pausar(2);

    for (int volta = 1; volta <= total_voltas; volta++) {
        printf(ANSI_WHITE "--- Volta %d ---\n" ANSI_RESET, volta);

        suspensao -= 2.0f;
        combustivel -= 1.5f;
        motor_temp += 1.0f;

        if (volta % 10 == 0) {
            printf(ANSI_YELLOW "\nPenalidade aplicada! (-3%% suspensao, +5°C motor)\n\n" ANSI_RESET);
            suspensao -= 3.0f;
            motor_temp += 5.0f;
        }

        if (suspensao <= 0 || combustivel <= 0) {
            printf(ANSI_RED ANSI_BOLD "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("!!! FALHA CRITICA NA VOLTA %d !!!!!!!!!!\n", volta);
            if (suspensao <= 0)
                printf("!!! Motivo: A suspensao chegou a %.1f%%.!!\n", fmaxf(0.0f, suspensao));
            else
                printf("!!! Motivo: O combustivel chegou a %.1f%%.!!\n", fmaxf(0.0f, combustivel));
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" ANSI_RESET);
            falha_critica = 1;
            break;
        }

        if (suspensao < 20.0f)
            printf(ANSI_YELLOW "ALERTA: Suspensao em nivel critico!\n" ANSI_RESET);
        if (motor_temp > 115.0f)
            printf(ANSI_RED "ALERTA: Motor superaquecendo!\n" ANSI_RESET);

        printf("Status -> Suspensao: %.1f%% | Combustivel: %.1f%% | Motor: %.1f°C\n",
               fmaxf(0.0f, suspensao),
               fmaxf(0.0f, combustivel),
               motor_temp);

        if (volta % 20 == 0) {
            printf("\n" ANSI_CYAN "========================================\n");
            printf("| RELATORIO DE CHECKPOINT - VOLTA %-3d   |\n", volta);
            printf("========================================\n\n" ANSI_RESET);
            pausar(1);
        }

        pausar(1);
        printf("\n");
    }

    if (falha_critica) {
        printf(ANSI_RED "\n--- CORRIDA ENCERRADA PREMATURAMENTE ---\n" ANSI_RESET);
    } else {
        printf(ANSI_GREEN "\n\n--- FIM DA CORRIDA --- \n" ANSI_RESET);
    }
}

int main() {
    simular_enduro_baja();

    printf("\nSimulacao finalizada. Pressione Enter para sair.\n");
    getchar();
    return 0;
}
