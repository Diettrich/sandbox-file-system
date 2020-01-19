#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOK_BUFSIZE 64
#define READLINE_BUFSIZE 1024

struct file
{
    int length;
    char *content;
};
struct directory
{
    char name[100];
    struct directory *fils;
    struct directory *frere;
};
typedef struct file file;
typedef struct directory *directory;

//read line
char *read_line()
{
    size_t bufsize = READLINE_BUFSIZE;
    char *line = malloc(bufsize * sizeof(char));
    getline(&line, &bufsize, stdin);
    return line;
}

//parse line
char **pasre_line(char *line)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    // bufsize est le buffer responsable du stream
    // de la commande et des arguments commançant
    // par 64 et ajouter par 64 à fur et à mesure
    char *delimiteur = " \t\r\n\a";
    char *token;
    char **tokens = malloc(bufsize * sizeof(char *));
    // tokens et la fragmentation de de la commande
    // entier envers commande principale et argumuents

    // exception ou token non defini
    if (!tokens)
    {
        fprintf(stderr, "FL-sh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    // parsing
    token = strtok(line, delimiteur);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += TOK_BUFSIZE;
            // élargisment du buffer (realloc)
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                fprintf(stderr, "FL-sh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, delimiteur);
    }
    tokens[position] = NULL;
    return tokens;
}

int main()
{
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

    //REPL system
    char *command;
    char **args;
    int status;
    char exit[] = "exit";
    int *argument_position;

    do
    {
        printf("$ ");
        command = read_line();
        args = pasre_line(command); 
        status = 1; //execution ici qui retourne status >>> test status automatiquement 1

        if (!strcmp(args[0], exit))
        {
            status = 0;
        }

        // test
        // printf("command: %s\n", command);
        for (int i = 0; i < 3; i++)
        {
            printf("%s\n", args[i]);
        }
        

        free(command);
        free(args);
    } while (status == 1);

    //puts(command);

    return 0;
}