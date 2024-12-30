#include "../includes/bshell/src/libbshell.h"

int print1() {
    printf("Print 22\n");
    return 1;
}

int clear() {
    #ifdef _WIN32
        system("cls");  // For Windows
    #else
        system("clear");  // For Linux/macOS
    #endif
    return 1;
}

int main(int argc, char** argv)
{
    ConfigStruct config_struct = bshell_config_init();
    config_struct.wellcome_message = "BIBLIOTECA";
    config_struct.help_message =  "As funcoes disponíveis são a seguir:";
    config_struct.prompt = "Digite uma função ou ajuda para saber mais\nComo usar. Use o nome seguido de dois porntos (Limpar:)\n";
    config_struct.add_extra_f("Print", &print1);
    config_struct.add_extra_f("Limpar", &clear);

    return bshell_main(config_struct);
}
