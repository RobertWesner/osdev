void shell_help(const char* args) {
    printf(" ____            _         _____ _          _ _ \n|  _ \\          (_)       / ____| |        | | |\n| |_) | __ _ ___ _  ___  | (___ | |__   ___| | |\n|  _ < / _` / __| |/ __|  \\___ \\| '_ \\ / _ \\ | |\n| |_) | (_| \\__ \\ | (__   ____) | | | |  __/ | |\n|____/ \\__,_|___/_|\\___| |_____/|_| |_|\\___|_|_|\n", args);
    printf("\nAvailable commands:\n");
    printf("    help        | show this\n");
    printf("    test        | test passing of arguments\n");
}
