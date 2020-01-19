#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file
{
    int length;
    char* content;
};
struct directory
{
    char name[100];
    struct directory* fils;
    struct directory* frere;
};
typedef struct file file;
typedef struct directory* directory;

//fonction juste pour debuger !!
void f() {
    printf("gg\n");
}

//read line
char* read_line() {
    printf("$ ");
    ssize_t bufsize = 1024;
    char* line = malloc(bufsize * sizeof(char));
    getline(&line, &bufsize, stdin);
    return line;
}

int main() {
    // init /home/
    directory filesystem = malloc(sizeof(directory));
    directory home = malloc(sizeof(directory));

    strcpy(home->name, "home");
    strcpy(filesystem->name, "/");

    filesystem->fils = home;
    filesystem->frere = NULL;
    home->fils = NULL;
    home->frere = NULL;

    //pointeur position vers le lieu l utilisateur
    directory position = home;
    //printf("%s\n", position->name);

    //REPL system
    char* command;
    char** args;
    int status;
    char exit[] = "exit\n";

    do
    {
        status = 1;
        command = read_line();
        if (!strcmp(command, exit))
        {
            status = 0;
        }
        
        printf("%s", command);
    } while (status == 1);
    
    //puts(command);

    return 0;
}