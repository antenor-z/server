#include "help.h"
/*
 * Show help when using -h or --help
 */

void help() {
    puts("-p --port <porta> Número da porta do serviço");
    puts("-l --log <filename> Nome completo do arquivo de log");
    puts("-s --statistics <filename> Nome completo do arquivo de estatísticas");
    puts("-b --background O serviço deverá rodar em background (Desafio!)");
    puts("-v --verbose As informações de debug são mostradas");
    puts("-r --root Caminho da raiz do site");
    exit(0);
}
