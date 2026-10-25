#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ctype.h>

#define MAX_PATH 1024
#define MAX_LINE 512

void searchDirectory(const char *path, int *count);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    int count = 1;

    printf("+-----+----------------------+-----------------------------------------------+\n");
    printf("| No. | File Name            | Description                                   |\n");
    printf("+-----+----------------------+-----------------------------------------------+\n");

    searchDirectory(argv[1], &count);

    printf("+-----+----------------------+-----------------------------------------------+\n");

    return 0;
}

void searchDirectory(const char *path, int *count)
{
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char fullPath[MAX_PATH];

    dir = opendir(path);
    if (dir == NULL)
        return;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(fullPath, sizeof(fullPath), "%s/%s", path, entry->d_name);

        if (stat(fullPath, &st) != 0)
            continue;

        if (S_ISDIR(st.st_mode))
        {
            searchDirectory(fullPath, count);
        }
        else
        {
            char *ext = strrchr(entry->d_name, '.');

            if (ext && strcmp(ext, ".c") == 0)
            {
                FILE *fp = fopen(fullPath, "r");
                if (fp == NULL)
                    continue;

                char line[MAX_LINE];
                char description[256] = "";

                while (fgets(line, sizeof(line), fp))
                {
                    char *p = strstr(line, entry->d_name);

                    if (p)
                    {
                        p += strlen(entry->d_name);

                        while (*p == ' ' || *p == '\t')
                            p++;

                        strcpy(description, p);


                        description[strcspn(description, "\n")] = '\0';


                        char *end = strstr(description, "*/");
                        if (end)
                            *end = '\0';

                        int len = strlen(description);
                        while (len > 0 && isspace((unsigned char)description[len - 1]))
                        {
                            description[--len] = '\0';
                        }

                        printf("| %-3d | %-20s | %-45s |\n",
                               (*count)++,
                               entry->d_name,
                               description);

                        break;
                    }
                }

                fclose(fp);
            }
        }
    }

    closedir(dir);
}
