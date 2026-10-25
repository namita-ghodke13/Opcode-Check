#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

FILE *out;     // File pointer used to write the output into output.txt */

void processDirectory(const char *path);     // Reads a .c file and extracts its description 
void processFile(const char *filepath);       // Reads a .c file and extracts its description 

int main()
{
    char path[500];

    printf("Enter directory path: ");
    scanf("%499s", path);

    out = fopen("output.txt", "w");    // Create output file 

    if(out == NULL)
    {
        printf("Error creating output.txt\n");
        return 1;
    }

    fprintf(out,"Program Name\t\tDescription\n");
    fprintf(out,"--------------------------------------------------------------------\n");

    processDirectory(path);

    // Close the output file 
    fclose(out);

    printf("\nAnalysis completed successfully.\n");
    printf("Output stored in output.txt\n");

    return 0;
}
void processDirectory(const char *path)
{
    DIR *dir;
    struct dirent *entry;
    struct stat info;
    char fullpath[1000];

    dir = opendir(path);

    if(dir == NULL)
    {
        printf("Cannot open directory: %s\n", path);
        return;
    }

    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 ||
           strcmp(entry->d_name, "..") == 0)
            continue;

        sprintf(fullpath, "%s/%s", path, entry->d_name);

        if(stat(fullpath, &info) != 0)
            continue;

        if(S_ISDIR(info.st_mode))
        {
            processDirectory(fullpath);
        }
        else
        {
            char *ext = strrchr(entry->d_name, '.');

            if(ext != NULL && strcmp(ext, ".c") == 0)
            {
                processFile(fullpath);
            }
        }
    }

    closedir(dir);
}
void processFile(const char *filepath)   
{
    FILE *fp;
    char line[1024];
    char filename[256];
    char description[768];

    fp = fopen(filepath, "r");

    if(fp == NULL)
        return;

    description[0] = '\0';

    while(fgets(line, sizeof(line), fp))
    {
        /* Look for the line containing ".c" in the comment block */

        if(line[0] == ' ' && line[1] == '*' && strstr(line, ".c"))
        {
            char *p = strstr(line, ".c");

            if(p != NULL)
            {

                int len = p - line + 2;

                strncpy(filename, line, len);
                filename[len] = '\0';


                char *start = filename;

                while(*start == ' ' || *start == '\t' || *start == '*')
                    start++;

                strcpy(filename, start);


                p += 2;

                while(*p == ' ' || *p == '\t')
                    p++;

                strcpy(description, p);


                description[strcspn(description, "\n")] = '\0';

                printf("%-20s : %s\n", filename, description);

                fprintf(out, "%-20s : %s\n", filename, description);

                break;
            }
        }
    }

    fclose(fp);
}
