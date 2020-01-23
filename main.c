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

//read line // read
char *read_line()
{
    size_t bufsize = READLINE_BUFSIZE;
    char *line = malloc(bufsize * sizeof(char));
    getline(&line, &bufsize, stdin);
    return line;
}

// execute function // eval && print
int execute(char **args, directory *current_position, directory root, directory home)
{
    char *core_commande = args[0];
    char **argument_commande = &args[1];
    //directory *tmp_position;

    if (!strcmp(core_commande, "exit"))
    {
        return 0;
    }
    else if (!strcmp(core_commande, "ls"))
    {
        //return poorls(current_position);
        return ls(argument_commande[0], *current_position, root);
    }
    else if (!strcmp(core_commande, "cd"))
    {
        return cd(argument_commande, current_position, root);
    }
    else
    {
        puts("command non existante");
        return 1;
    }
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

// parse URL (lien)
char **URLparser(char *line)
{
    char *delimiteur = "/";
    return FL_sh_pareser(line, delimiteur);
}

// ----------------------------------------- COMMANDES UTILITIES -------------------------------

// dirExist function(char *name, directory *position_temporere) return 1 si existe 0 sinon
// et qui change la position tmp dans la fonction appelante vers nouvel position
int dirExiste(char *name, directory *position)
{
    directory var = *position;
    if (var->fils == NULL)
    {
        return 0;
    }

    if (strcmp(var->fils->name, name) == 0)
    {
        *position = var->fils;
        return 1;
    }
    var = var->fils;
    while (var != NULL)
    {
        if (strcmp(var->name, name) == 0)
        {
            *position = var;
            printf("%s\n", (*position)->name);
            return 1;
        }
        var = var->frere;
    }
    return 0;
}

// cherche fils
// directory searchFils(char *name, directory position)
directory searchFils(char *name, directory position)
{
    if (position->fils == NULL)
    {
        return NULL;
    }
    if (strcmp(name, position->fils) == 0)
    {
        return position->fils;
    }
    position = position->fils;
    while (position != NULL && strcmp(name, position->frere) != 0)
    {
        position = position->frere;
    }
    return position == NULL ? NULL : position;
}

// directory changeDirectory(char *name, directory position)
directory changeDirectory(char *name, directory *position)
{
    *position = searchFils(name, *position);
    return *position;
}

// directory createDirectory(char *name, directory parent)
// cree un repertoire de nom: name sous un repertoire parenr: parent
directory createDirectory(char *name, directory parent)
{
    directory var = malloc(sizeof(directory));
    directory precedent = malloc(sizeof(directory));
    strcpy(var->name, name);
    strcpy(precedent->name, "..");
    if (parent->fils == NULL)
    {
        parent->fils = var;
    }
    else
    {
        directory dernier_fils = parent->fils;
        while (dernier_fils->frere != NULL)
        {
            dernier_fils = dernier_fils->frere;
        }
        dernier_fils->frere = var;
    }
    var->frere = NULL;
    var->fils = precedent;
    precedent->fils = parent->fils;

    return var;
}

// ----------------------------------------- COMMANDES -----------------------------------------

// command ls
int ls(char *url, directory position, directory root)
{
    // later bitchs
    directory tmp_position;
    if (url != NULL)
    {
        tmp_position = url[0] == '/' ? root : position;
        if (strcmp(url, "/") == 0)
        {
            poorls(tmp_position);
            free(tmp_position);
            return 1;
        }
        char **url_names_array = URLparser(url);
        int i = 0;
        while (url_names_array[i] != NULL)
        {
            //printf("<<  %s   %s  >>\n", url_names_array[i], tmp_position->name);
            if (dirExiste(url_names_array[i], &tmp_position))
            {
                //printf("<<  %s   %s  >>\n", url_names_array[i], tmp_position->name);
                i++;
            }
            else
            {
                puts("repertoire non existant");
                return 1;
            }
        }
        poorls(tmp_position);
        free(tmp_position);
        return 1;
    }
    else
    {
        poorls(position);
        return 1;
    }
    fprintf(stderr, "FL-sh: error ls\n");
    exit(EXIT_FAILURE);
}

int poorls(directory position)
{
    directory var = position->fils;
    while (var != NULL)
    {
        puts(var->name);
        var = var->frere;
    }
    return 1;
}

// command mkdir: make directory
int mkdir(char *line, directory position, directory root)
{
    directory tmp_posistion;
    char **arg = URLparser(line);
    int isRelative = line[0] == '/' ? 0 : 1;
    int profondeur = 0;
    int profondeur_max = 0;
    while (arg[profondeur_max] != NULL)
    {
        profondeur_max++;
    }

    if (isRelative)
        tmp_posistion = position;
    else
        tmp_posistion = root;
    while (dirExiste(arg[profondeur], &tmp_posistion))
        profondeur++;
    for (int i = profondeur; i < profondeur_max; i++)
    {
        createDirectory(arg[i], tmp_posistion);
        changeDirectory(arg[i], &tmp_posistion);
    }

    return 1;
}

// command cd
int cd(char *commande_arg, directory *position, directory root)
{
    char **arg = URLparser(commande_arg);
    directory initial_position = *position;
    if (arg[0] == NULL)
    {
        *position = changeDirectory("home", &root);
    }
    int isRelative = commande_arg[0] == '/' ? 0 : 1;
    if (isRelative)
    {
        int i = 0;
        while (arg[i] != NULL)
        {
            if (!dirExiste(arg[i], position))
            {
                *position = initial_position;
                puts("repertoire introuvable");
            }
            i++;
        }
    }
    else
    {
        /* code */
    }
}

int main()
{
    // init /home/
    directory root = malloc(sizeof(directory));
    directory home = malloc(sizeof(directory));
    directory home_to_root = malloc(sizeof(directory)); // precedent

    strcpy(root->name, "/");
    strcpy(home->name, "home");
    strcpy(home_to_root->name, "..");

    root->fils = home;
    root->frere = NULL;
    home->fils = home_to_root;
    home->frere = NULL;
    home_to_root->fils = root->fils;

    //pointeur position vers le lieu l utilisateur
    directory position = home;

    //REPL system (read eval print loop)
    char *command;
    char **args;
    int status;

    do
    {
        printf("$ ");
        command = read_line();
        args = pasre_line(command);
        status = execute(args, &position, root, home);
        free(command);
        free(args);
    } while (status == 1);

    return 0;
}
