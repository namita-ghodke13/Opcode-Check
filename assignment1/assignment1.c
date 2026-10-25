#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void readFile(char path[], FILE *out)
{
    FILE *fp=fopen(path, "r");
    char c, next, text[5000], word[100];
    char *p;
    int i;
// if file is null then it will not open
    if (fp==NULL)
        return;
// reads charcter by character
    while ((c=fgetc(fp))!=EOF)
    {
//check if there is Block comment
        if (c == '/' && (next = fgetc(fp)) == '*')
        {
            i = 0;
//store if anthing is in comments
            while ((c=fgetc(fp)) != EOF)
            {   
            // stops  at */ 
                if (c=='*' && (next = fgetc(fp)) == '/')
                    break;

                if (i < 4999)
                    text[i++] = c;
            }

            text[i] = '\0';
            p = text;

            while (*p)
            {
                while (*p == ' ' || *p == '\t' ||
                       *p == '\n' || *p == '\r' ||
                       *p == '*')
                    p++;

                i = 0;

                while (*p && *p != ' ' && *p != '\t' &&
                       *p != '\n' && *p != '\r' && *p != '*')
                {
                    word[i++] = *p++;
                }

                word[i] = '\0';
// if word is source file name it takes it as description
                if (strstr(word, ".c") ||
                    strstr(word, ".h") ||
                    strstr(word, ".asm") ||
                    strstr(word, ".inc"))
                {
                    fprintf(out, "Filename: %s\n\n", word);
                    fprintf(out, "Description:\n%s\n", text);
                    fprintf(out, "----------------------------------------\n\n");
                    break;
                }
            }
        }
    }

    fclose(fp);
}


void searchFolder(char folder[], FILE *out)
{
    DIR *dir = opendir(folder);
    struct dirent *item;
    struct stat info;
    char path[1000];

    if (dir == NULL)
        return;

    while ((item = readdir(dir)) != NULL)
    {
        if (!strcmp(item->d_name, ".") ||
            !strcmp(item->d_name, ".."))
            continue;

        sprintf(path, "%s/%s", folder, item->d_name);

        stat(path, &info);

        if (S_ISDIR(info.st_mode))
        {
            searchFolder(path, out);
        }
        else if (strstr(item->d_name, ".c") ||
                 strstr(item->d_name, ".h"))
        {
            printf("Reading: %s\n", path);
            readFile(path, out);
        }
    }

    closedir(dir);
}


int main()
{
    char folder[1000];
    FILE *out;
// takes the input
    printf("enter nasm folder path: ");
    fgets(folder, sizeof(folder), stdin);
// here new line is removed
    folder[strcspn(folder, "\n")] = '\0';

    out = fopen("result.txt", "w");

    if (out == NULL)
    {
        printf("result does not created\n");
        return 1;
    }
//searches the input folder
    searchFolder(folder, out);

    fclose(out);

    printf("\nDone!\n");
    printf("Result is in result.txt\n");

    return 0;
}
