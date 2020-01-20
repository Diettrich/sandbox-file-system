#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOK_BUFSIZE 64
#define READLINE_BUFSIZE 1024

struct file
{
    char name[128];
    int length;
    char *content;
};
struct directory
{
    char name[128];
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

// parse string function
char **FL_sh_pareser(char *line, char *delimiteur)
{
    int bufsize = TOK_BUFSIZE, position = 0;
    // bufsize est le buffer responsable du stream
    // de la commande + arguments en cas de parse
    // de la ligne et la liste des passages d' un
    // chemin (URL) en cas de parse du lien commançant
    // par 64 et ajouter par 64 à fur et à mesure

    char *token;
    char **tokens = malloc(bufsize * sizeof(char *));
    // tokens est la fragmentation de de la ligne ou URL

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

// parse line
char **pasre_line(char *line)
{
    char *delimiteur = " \t\r\n\a";
    return FL_sh_pareser(line, delimiteur);
}

// parse URL
char **URLparser(char *line)
{
    char *delimiteur = "/";
    return FL_sh_pareser(line, delimiteur);
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
        int i = 0;
        while (args[i] != NULL)
        {
            printf("%s\n", args[i]);
            i++;
        }

        free(command);
        free(args);
    } while (status == 1);

    //puts(command);

    return 0;
}