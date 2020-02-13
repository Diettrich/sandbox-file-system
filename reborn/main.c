#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOK_BUFSIZE 64
#define READLINE_BUFSIZE 1024

struct directory
{
    char name[128];
    char type;
    char *content;
    int contentlength;
    struct directory *fils;
    struct directory *frere;
    struct directory *previous;
};
typedef struct directory *directory;

//read line
char *read_line()
{
    size_t bufsize = READLINE_BUFSIZE;
    char *line = malloc(bufsize * sizeof(char));
    getline(&line, &bufsize, stdin);
    return line;
}

// execute command
int execute(char **args, directory *current_position, directory *__tmp_position, directory root, directory home)
{
    char *core_commande = args[0];
    char **argument_commande = &args[1];

    if (!strcmp(core_commande, "exit"))
    {
        return 0;
    }
    else if (!strcmp(core_commande, "ls"))
    {
        if (argument_commande[0] == NULL || (argument_commande[0] != NULL && argument_commande[1] == NULL))
        {
            return ls(argument_commande[0], *current_position, __tmp_position, root);
        }
        puts("on ne traite pas 2 argument ou plus.");
        return 1;
    }
    else if (!strcmp(core_commande, "cd"))
    {
        if (argument_commande[0] == NULL || (argument_commande[0] != NULL && argument_commande[1] == NULL))
        {
            return cd(argument_commande[0], current_position, __tmp_position, root, home);
        }
        puts("on ne traite pas 2 argument ou plus.");
        return 1;
    }
    else if (!strcmp(core_commande, "mkdir"))
    {
        return mkdir(argument_commande, *current_position, __tmp_position, root, home);
    }
    else if (!strcmp(core_commande, "pwd"))
    {
        return pwd(*current_position, root, 0);
    }
    else if (!strcmp(core_commande, "cp"))
    {
        if (argument_commande[0] == NULL || (argument_commande[0] != NULL && argument_commande[1] == NULL) || argument_commande[2] != NULL)
        {
            puts("cp necessite 2 arguments.");
            return 1;
        }
        
        return cp(argument_commande[0], argument_commande[1], *current_position, __tmp_position, root);
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
char **parse_line(char *line)
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
int dirExiste(const char *name, directory *_position, directory root)
{
    if (_position == NULL)
    {
        fprintf(stderr, "FL-sh: POSITION POINTER NOT FOUND\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(name, ".") == 0)
    {
        return 1;
    }
    else if (strcmp(name, "..") == 0)
    {
        if (*_position == root)
        {
            return 1;
        }

        *_position = (*_position)->previous;
        return 1;
    }

    directory var = *_position;
    if (var->fils == NULL)
    {
        return 0;
    }
    if (strcmp(var->fils->name, name) == 0)
    {
        *_position = var->fils;
        return 1;
    }
    var = var->fils;
    while (var != NULL)
    {
        if (strcmp(var->name, name) == 0)
        {
            *_position = var;
            return 1;
        }
        var = var->frere;
    }
    return 0;
}

// int createDirectory(char *name, directory parent)
// cree un repertoire de nom: name sous un repertoire parenr: parent
int createDirectory(const char *name, directory parent)
{
    directory var = malloc(sizeof(directory));
    strcpy(var->name, name);
    var->frere = NULL;
    var->fils = NULL;
    var->previous = parent;
    var->type = 'd';
    if ((parent)->fils == NULL)
    {
        (parent)->fils = var;
    }
    else
    {
        directory dernier_fils = (parent)->fils;
        while (dernier_fils->frere != NULL)
        {
            dernier_fils = dernier_fils->frere;
        }
        dernier_fils->frere = var;
    }

    return 1;
}

int addToNode(directory node, directory parent)
{
    if ((parent)->fils == NULL)
    {
        (parent)->fils = node;
    }
    else
    {
        directory dernier_fils = (parent)->fils;
        while (dernier_fils->frere != NULL)
        {
            dernier_fils = dernier_fils->frere;
        }
        dernier_fils->frere = node;
    }
    return 1;
}

// ----------------------------------------- COMMANDES -----------------------------------------

// command ls
int ls(char *url, directory _position, directory *_tmp_position, directory root)
{
    if (url != NULL)
    {
        *_tmp_position = url[0] == '/' ? root : _position;
        if (strcmp(url, "/") == 0)
        {
            poorls(*_tmp_position);
            return 1;
        }
        const char **URL_NAMES_ARRAY = (const char **)URLparser(url);
        int i = 0;
        while (URL_NAMES_ARRAY[i] != NULL)
        {
            if (dirExiste(URL_NAMES_ARRAY[i], _tmp_position, root))
            {
                i++;
            }
            else
            {
                puts("repertoire non existant");
                free(URL_NAMES_ARRAY);
                return 1;
            }
        }
        return poorls(_tmp_position);
    }
    else
    {
        return poorls(_position);
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

// command cd : change directory
int cd(char *url, directory *position, directory *_tmp_position, directory root, directory home)
{
    if (url != NULL)
    {
        if (strcmp(url, "/") == 0)
        {
            *position = root;
            return 1;
        }
        *_tmp_position = url[0] == '/' ? root : *position;
        const char **URL_NAMES_ARRAY = (const char **)URLparser(url);
        int i = 0;
        while (URL_NAMES_ARRAY[i] != NULL)
        {
            if (dirExiste(URL_NAMES_ARRAY[i], _tmp_position, root))
            {
                i++;
            }
            else
            {
                puts("repertoire non existant");
                free(URL_NAMES_ARRAY);
                return 1;
            }
        }
        *position = *_tmp_position;
        free(URL_NAMES_ARRAY);
        return 1;
    }
    else
    {
        *position = home;
        return 1;
    }
    fprintf(stderr, "FL-sh: error cd\n");
    exit(EXIT_FAILURE);
}

// command mkdir: make directory
int mkdir(char **args, directory position, directory *_tmp_position, directory root, directory home)
{
    if (args[0] == NULL)
    {
        puts("aucun repertoire saisie.");
        return 1;
    }
    int i = 0;
    while (args[i] != NULL)
    {
        const char **ARG_ARRAY = (const char **)URLparser(args[i]); // /anouar/zougrar => {anouar, zougrar}
        *_tmp_position = args[i][0] == '/' ? root : position;
        if (strcmp(args[i], "/") == 0)
        {
            puts("opération impossible.");
            return 1;
        }
        int j = 0;
        while (dirExiste(ARG_ARRAY[j], _tmp_position, root))
        {
            j++;
        }
        while (ARG_ARRAY[j] != NULL)
        {
            // createdir
            if (createDirectory(ARG_ARRAY[j], *_tmp_position))
            {
                dirExiste(ARG_ARRAY[j], _tmp_position, root);
            }
            j++;
        }
        i++;
        free(ARG_ARRAY);
    }
    return 1;
}

int pwd(directory position, directory root, int c)
{
    if (position != root)
    {
        pwd(position->previous, root, 1);
    }
    if (c == 0)
    {
        printf("/%s\n", position->name);
    }
    else
    {
        if (position != root)
        {
            printf("/%s", position->name);
        }
    }

    return 1;
}

int cp(char* path1, char* path2, directory position, directory* _tmp_position, directory root)
{
    if (strcmp(path1, "/") == 0)
    {
        puts("opération impossible.");
        return 1;
    }
    *_tmp_position = path1[0] == '/' ? root : position;
    const char **PATH1_ARRAY = (const char **)URLparser(path1);
    int i = 0;
    while (PATH1_ARRAY[i] != NULL)
    {
        if (dirExiste(PATH1_ARRAY[i], _tmp_position, root))
        {
            i++;
        }
        else
        {
            puts("repertoire non existant");
            free(PATH1_ARRAY);
            return 1;
        }
    }
    free(PATH1_ARRAY);
    directory copy = (directory)malloc(sizeof(directory));
    strcpy(copy->name, (*_tmp_position)->name);
    copy->frere = NULL;
    copy->fils = (*_tmp_position)->fils;
    copy->previous = (*_tmp_position)->previous;
    copy->type = (*_tmp_position)->type;
    //printf("%s\n", copy->name);

    //########## remake ##########
    if (strcmp(path2, "/") == 0)
    {
        addToNode(copy, root);
        return 1;
    }
    *_tmp_position = path2[0] == '/' ? root : position;
    const char **PATH2_ARRAY = (const char **)URLparser(path2);
    i = 0;
    //puts("ok");
    while (PATH2_ARRAY[i] != NULL)
    {
        if (dirExiste(PATH2_ARRAY[i], _tmp_position, root))
        {
            i++;
        }
        else if (PATH2_ARRAY[i + 1] == NULL)
        {
            strcpy(copy->name, PATH2_ARRAY[i]);
            addToNode(copy, *_tmp_position);
            free(PATH2_ARRAY);
            return 1;
        }
        else
        {
            puts("repertoire non existant");
            free(PATH2_ARRAY);
            return 1;
        }
    }
    free(PATH2_ARRAY);
    addToNode(copy, *_tmp_position);
    return 1;
}

//################################### MAIN ###################################
int main(int argc, char const *argv[])
{
    // init  /home/
    const directory root = (directory)malloc(sizeof(directory));
    const directory home = (directory)malloc(sizeof(directory));
    directory position = (directory)malloc(sizeof(directory));
    directory tmp_position = (directory)malloc(sizeof(directory));

    strcpy(root->name, "/");
    strcpy(home->name, "home");

    root->fils = home;
    root->frere = NULL;
    root->previous = root;

    home->fils = NULL;
    home->frere = NULL;
    home->previous = root;

    //pointeur position vers le lieu l utilisateur
    position = home;
    tmp_position = position;

    //REPL system (read eval print loop)
    char *command;
    char **args;
    int status;

    do
    {
        printf("%s $ ", position->name);
        command = read_line(); // READ
        args = parse_line(command);
        status = execute(args, &position, &tmp_position, root, home); //EVAL  & PRINT
        tmp_position = position;
        free(command);
        free(args);
    } while (status == 1); // LOOP

    return 0;
}
