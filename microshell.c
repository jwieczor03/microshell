#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

//input
#define string 256
char *input;

//files
FILE* file_history;
char *line = NULL;


void hi()
{


    printf(" ~~~~~~~~~~~~~~~~~~\n");
    printf("|Witaj w mojej     |\n");
    printf("|Wersji microshella|\n");
    printf("|Milej zabawy!!    |\n");
    printf("|\t\t   |\n");
    printf("|Jakub Wieczor     |\n");
    printf(" ~~~~~~~~~~~~~~~~~~");
    printf("\n");
}

void help()
{
    printf("\t\t\t\tWitaj\n");
    printf("\t\tProgram stworzony przez Jakuba Wieczor\n");
    printf("\t\tNumer indeksu: 485704\n");
    printf("\t\tDotepne polecenia to:\n");
    printf("\t\t - move\n");
    printf("\t\t - remove\n");
    printf("\t\t - history\n");
    printf("\t\t - rename\n");
    printf("\t\t - cd\n");
    printf("\t\t - exit\n");
    printf("\t\t - cd\n");
    printf("\t\t - ck + kolor(zmiana koloru)\n");
    printf("\t\t - whoami\n");
    printf("\t\t - host\n");
    printf("\t\t - pwd\n");
}

void change_color(char *choice)
{

    int temp;
    if(strcmp(choice, "black") == 0)
        temp = 1;
    else if(strcmp(choice, "red") == 0)
        temp = 2;
    else if(strcmp(choice, "green") == 0)
        temp = 3;
    else if(strcmp(choice, "yellow") == 0)
        temp = 4;
    else if(strcmp(choice, "blue") == 0)
        temp = 5;
    else if(strcmp(choice, "magenta") == 0)
        temp = 6;
    else if(strcmp(choice, "cyan") == 0)
        temp = 7;
    else if(strcmp(choice, "white") == 0)
        temp = 8;
    else
    {
        printf("Wrong colour");
    }

    switch (temp)
    {
        case 1:
            printf("\030[1;31m");
            break;
        case 2:
            printf("\031[1;31m");
            break;
        case 3:
            printf("\032[1;31m");
            break;
        case 4:
            printf("\033[1;31m");
            break;
        case 5:
            printf("\034[1;31m");
            break;
        case 6:
            printf("\035[1;31m");
            break;
        case 7:
            printf("\036[1;31m");
            break;
        case 8:
            printf("\037[1;31m");
            break;


    }


}

void history_writing(char *input)
{

    file_history = fopen("history.txt", "a");


    if (file_history == NULL)
    {
        perror("something went wrong :(");
        printf("error: %d\n", errno);
    }
    fprintf(file_history, "%s", input);

}

void history_read()
{

    file_history = fopen("history.txt", "r");


    if (file_history == NULL) {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
    }

    line = NULL;
    ssize_t read;
    size_t len = 0;
    int i = 1;
    while ((read = getline(&line, &len, file_history)) != -1)
    {

        printf("%d. %s",i, line);
        i++;

    }
}

void cd(char *path)
{
    int code;
    code = chdir(path);
    if (code != 0)
    {
        perror("wystapil blad : ");
        printf(", o numerze %d\n", errno);

    }

}

void move(const char *stare, const char *nowe) {
    FILE *zrodlo = fopen(stare, "r");
    if (zrodlo == NULL) {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
    }

    FILE *plik_nowy = fopen(nowe, "w");
    if (plik_nowy == NULL) {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
        fclose(zrodlo);
    }

    char *line = NULL;
    ssize_t read;
    size_t len = 0;
    while ((read = getline(&line, &len, zrodlo)) != -1) {
        fprintf(plik_nowy, "%s", line);
    }

    free(line);
    fclose(zrodlo);
    fclose(plik_nowy);

    int ret = remove(stare);
    if (ret != 0) {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
    }
}
void change_name(char *old_name, char *new_name)
{
    int code;
    code = rename(old_name, new_name);
    if (code == 0) {
        printf("Nazwa zostala zmieniona\n");
    }
    else
    {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
    }
}

void remove_my(char *name)
{
    if (remove(name) == 0)
        printf("Pomyslnie usunieto plik:)");
    else
    {
        perror("Wystapil blad : ");
        printf("Numer bledu:  %d\n", errno);
    }

}

void my_exit()
{
    printf("Mam nadzieje, ze sie podobalo!\n");
    printf("Do zobaczenia!!\n");
    exit(EXIT_SUCCESS);

}

void sign_of_encouragement()
{
    char* login;
    login = getlogin();
    char hostname[3];
    gethostname(hostname, 3);
    char* cwd;
    cwd = getcwd(NULL, 0);

    printf("%s@%s:%s$ ", login, hostname, cwd);

}

void clear_terminal(void)
{
    printf("\033c");
}

int main()
{
    hi();

    while (true)
    {
        input = (char *) malloc(string);
        sign_of_encouragement();
        fgets(input, string, stdin);
        history_writing(input);
        fclose(file_history);
        int temp = 0;
        while(input[temp]!='\0')
        {
            if(input[temp]== '\n')
            {
                input[temp] = '\0';
            }
            temp++;
        }

        int i = 0;
        char *token = strtok(input, " ");
        char ** arguments = malloc(string);
        while( token != NULL )
        {
            arguments[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        if ((strcmp(arguments[0],"help") == 0) && arguments[1] == NULL)
        {
            help();
        }

        else if (strcmp(arguments[0], "move") == 0)
        {
            move(arguments[1],arguments[2]);
        }
        else if (strcmp(arguments[0], "remove") == 0)
        {
            remove_my(arguments[1]);
        }
        else if ((strcmp(arguments[0], "exit") == 0) &&  (arguments[1] == NULL))
        {
            my_exit();
        }
        else if ((strcmp(arguments[0], "clear") == 0) && (arguments[1] == NULL))
        {
            clear_terminal();
        }
        else if (strcmp(arguments[0], "rename") == 0)
        {
            change_name(arguments[1],arguments[2]);
        }
        else if (strcmp(arguments[0], "cd") == 0)
        {
            cd(arguments[1]);
        }
        else if (strcmp(arguments[0], "ck") == 0)
        {
            change_color(arguments[1]);
        }
        else if((strcmp(arguments[0], "history") == 0) && (arguments[1] == NULL))
        {
            history_read();
            fclose(file_history);
        }
        else if((strcmp(arguments[0], "whoami") == 0) && (arguments[1] == NULL))
        {
            char* login;
            login = getlogin();
            printf("%s", login);
            free(login);
        }
        else if((strcmp(arguments[0], "host") == 0) && (arguments[1] == NULL))
        {
            char hostname[3];
            gethostname(hostname, 3);
            printf("%s", hostname);
        }
        else if((strcmp(arguments[0], "pwd") == 0) && (arguments[1] == NULL))
        {
            char* pwd;
            pwd = getcwd(NULL, 0);
            printf("%s", pwd);
            free(pwd);
        }


        else
        {
            int pid = fork();
            if (pid < 0)
            {
                perror("Wystapil blad : ");
                printf("Numer bledu:  %d\n", errno);
            }
            else if (pid == 0)
            {
                if (execvp(arguments[0], arguments) != 0)
                {
                    perror("Wystapil blad : ");
                    printf("Numer bledu:  %d\n", errno);

                }
                exit(EXIT_SUCCESS);
            }
            else
                waitpid(pid, NULL, 0);
        }
        line = NULL;
        free(arguments);
        free(input);
        free(line);

    }
    return 0;
}

