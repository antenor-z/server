#include "help.h"

void help() {
    puts("-p --port <porta> Número da porta do serviço");
    puts("-l --log <filename> Nome completo do arquivo de log");
    puts("-s --statistics <filename> Nome completo do arquivo de estatísticas");
    puts("-b --background O serviço deverá rodar em background (Desafio!)");
    puts("-r --root Caminho da raiz do site");
    exit(0);
}