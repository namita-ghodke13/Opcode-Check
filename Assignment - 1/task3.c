#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

#define MAX_PATH 1024
#define MAX_DESC 512

void trim(char *str)
{
    int len = strlen(str);

    while (len > 0 &&
          (str[len-1] == '\n' ||
           str[len-1] == '\r' ||
           str[len-1] == ' '  ||
           str[len-1] == '\t'))
    {
        str[--len] = '\0';
    }
}

void getDescription(const char *filepath, char *description)
{
    FILE *fp = fopen(filepath, "r");

    if (fp == NULL)
    {
        strcpy(description, "Description not found");
        return;
    }

    char line[1024];
    int inComment = 0;

    strcpy(description, "Description not found");

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "SPDX-License-Identifier"))
            continue;

        if (strstr(line, "Copyright"))
            continue;

        if (strstr(line, "/*"))
        {
            inComment = 1;
            continue;
        }

        if (!inComment)
            continue;

        if (strstr(line, "*/"))
            break;

        char *p = line;

        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '*')
            p++;

        while (*p == ' ' || *p == '\t')
            p++;

        if (*p == '\0' || *p == '\n')
            continue;

        char *ext = strstr(p, ".c");

        if (ext)
        {
            ext += 2;

            while (*ext == ' ' ||
                   *ext == '\t' ||
                   *ext == '-' ||
                   *ext == ':')
                ext++;

            if (*ext != '\0')
            {
                strcpy(description, ext);
                trim(description);
                fclose(fp);
                return;
            }
        }

        if (strncmp(p, "The ", 4) == 0 ||
            strncmp(p, "NASM", 4) == 0)
        {
            strcpy(description, p);
            trim(description);
            fclose(fp);
            return;
        }

        if (strlen(p) > 10)
        {
            strcpy(description, p);
            trim(description);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

void scanDirectory(const char *dir)
{
    DIR *dp = opendir(dir);

    if (!dp)
        return;

    struct dirent *entry;
    char path[MAX_PATH];

    while ((entry = readdir(dp)) != NULL)
    {
        if (!strcmp(entry->d_name, ".") ||
            !strcmp(entry->d_name, ".."))
            continue;

        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);

        struct stat st;

        if (stat(path, &st) != 0)
            continue;

        if (S_ISDIR(st.st_mode))
        {
            scanDirectory(path);
        }
        else
        {
            char *ext = strrchr(entry->d_name, '.');

            if (ext && strcmp(ext, ".c") == 0)
            {
                char desc[MAX_DESC];

                getDescription(path, desc);

                printf("| %-30s | %-60s |\n",
                       entry->d_name,
                       desc);
            }
        }
    }

    closedir(dp);
}

int main()
{
    char directory[MAX_PATH];

    printf("Enter NASM source directory: ");
    scanf("%1023s", directory);

    printf("\n");

    printf("----------------------------------------------------------------------------------------------------------\n");
    printf("| %-30s | %-60s |\n", "Filename", "Description");
    printf("----------------------------------------------------------------------------------------------------------\n");

    scanDirectory(directory);

    printf("----------------------------------------------------------------------------------------------------------\n");

    return 0;
}
