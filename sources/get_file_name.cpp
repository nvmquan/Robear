#include <cstring>
#include <dirent.h>

#include "../headers/get_file_name.h"

/**
    Function to autocomplete a directory (equivalent of autoTab on Unix shell)
*/
char* getFileName(char *chemin, char *nom)
{
    DIR *rep = opendir(chemin);

    if(rep != NULL)
    {
        struct dirent *file = readdir(rep);
        size_t n = strlen(nom);

        while(file != NULL)
        {
            if(memcmp(file->d_name,nom,n) == 0)
            {
                strcat(chemin,"/");
                strcat(chemin,(const char *)(file->d_name));
                closedir(rep);
                return(chemin);
            }

            file = readdir(rep);
        }
        closedir(rep);
        return(NULL);
    }

    return(NULL);
}
