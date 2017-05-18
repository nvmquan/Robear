#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>

#include "../headers/encoders.h"
#include "../headers/get_file_name.h"

char pinmuxdir[250]="/sys/devices";
char pinmuxfile[14]="bone_capemgr.";
char pinctrldir[250]="/sys/devices";
char pinctrlfile[5]="ocp.";

/**
    Function to mux an eQEP, which allows to use it by loading a device tree
*/
void eQEPMux(int number)
{
    getFileName(pinmuxdir,pinmuxfile);
    getFileName(pinctrldir,pinctrlfile);

    char chemin[250];
    strcpy(chemin,pinmuxdir);
    strcat(chemin,"/slots\0");
    char echo[11]="bone_eqep0";

    char realnumber[2];

    sprintf(realnumber,"%d",number);

    echo[9]= realnumber[0];

    int eqepmux=open(chemin,O_RDWR);
    write(eqepmux,echo,11);
    close(eqepmux);
}
