/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** brute_force.c
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int my_strlen(char const *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return (i);
}

char *read_map(char *filepath)
{
    int size = 5000000;
    char *buffer = NULL;
    int fd = open(filepath, O_RDONLY);

    buffer = malloc(sizeof(char) * (size + 1));
    read(fd, buffer, size);
    close(fd);
    if (buffer == NULL)
        return (NULL);
    return (buffer);
}

char **str_to_world_array(int *a, char *buffer)
{
    int k = 0, i = 0, r = 0;
    char **a_position = NULL, *temp = NULL;

    a_position = malloc(sizeof(char * ) * *a + 1);
    while (r < *a) {
        temp = malloc(sizeof(char) * 25 + 1);
        while (buffer[i] != '\n' && buffer[i] != '\0') {
            temp[i] = buffer[i];
            i++;
        }
        buffer = &buffer[i+1];
        a_position[k] = temp;
        i = 0;
        k++;
        r++;
    }
    a_position[k] = NULL;
    return (a_position);
}

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    for (; src[i] != '\0'; i++)
        dest[i] = src[i];
    dest[i] = '\0';
    return (dest);
}

char *my_strdup(char *str)
{
    int len = my_strlen(str) + 1;

    char *newstr = malloc(sizeof(char) * len);
    if (newstr == NULL)
        return (NULL);
    newstr = my_strcpy(newstr, str);
    newstr[len - 1] = '\0';
    return (newstr);
}

int is_same_word(char *str1, char *str2, int size)
{
    int counter = 0;

    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            if (str1[j] != '%' && str2[i] != '%' && str1[j] == str2[i]){
                str1[j] = '%';
                str2[i] = '%';
            }
        }
    }
    for (int i = 0; i < size; i++){
        if (str1[i] != '%')
            return (0);
    }
    return (1);
}

int get_size_line(char *map)
{
    int i = 0, a = 0;

    while (map[i] != '\0') {
        if (map[i] == '\n')
            a++;
        i++;
    }
    return (a);
}

int sort_word(char *line_parsed, char *name)
{
    int i = 0, a = 0;

    while (line_parsed[i+1] != '\0') {
        if (line_parsed[i] < 97)
            line_parsed[i] = line_parsed[i] + 32;
        while (line_parsed[i] != name[a]) {
            if (name[a] == '\0')
                return (1);
            if (name[a] < 97)
                name[a] = name[a] + 32;
            a++;
        }
        if (line_parsed[i] == name[a]) {
            a = 0;
            i++;
        }
    }
    a = 0;
    i = 0;
    while (name[a] != '\0') {
        while (name[a] != line_parsed[i]) {
            if (line_parsed[i] == '\0')
                return (1);
            i++;
        }
        if (line_parsed[i] == name[a]) {
            i = 0;
            a++;
        }
    }
    return (0);
}

int compare_name(char **line_parsed, char *name)
{
    int i = 0, a = 0, j = 0, size = 0;
    char *save = NULL, *save2 = NULL;
    int word_size = my_strlen(name);

    while (line_parsed[a] != NULL) {
        size = my_strlen(line_parsed[a]);
        while (i < size) {
            if (my_strlen(name) != my_strlen(line_parsed[a] + 1))
                break;
            if (sort_word(line_parsed[a], name) == 0) {
                save = my_strdup(line_parsed[a]);
                save2 = my_strdup(name);
                if (is_same_word(save, save2, word_size)) {
                    j++;
                    printf("%s\n", line_parsed[a]);
                }
                break;
            }
            else
                break;
        }
        i = 0;
        a++;
    }
    if (j == 0)
        printf("No words found..\n");
    return (0);
}

int brute_force(char *map, char *name)
{
    int i = get_size_line(map);
    char **arg_parsed = NULL;

    while (1) {
        arg_parsed = str_to_world_array(&i, map);
        if (compare_name(arg_parsed, name) == 1)
            return (0);
        break;
    }
    return (0);
}

void help()
{
    printf("    USAGE\n");
    printf("gcc find_word\n");
    printf("./a.out [DICO] [WORDS_TO_SEARCH]\n       --------------\n");
    printf("example : ./a.out liste_francais.txt rreoad");
    printf("\nname : adorer\n");
}

int main(int ac, char **argv)
{
    char *map = NULL;

    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        help();
        return (84);
    }
    if (ac != 3)
        return 84;
    map = read_map(argv[1]);
    if (map == NULL)
        return (84);
    brute_force(map, argv[2]);
}