#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include "../headers/serial_com.h"
#include "../headers/get_file_name.h"

char serialmuxdir[250]="/sys/devices";
char serialmuxfile[14]="bone_capemgr.";
char serialctrldir[250]="/sys/devices";
char serialctrlfile[5]="ocp.";

/**
    Function to mux a serial communication port, which allows to use it by loading a device tree
*/
void serialMux(int number)
{
    getFileName(serialmuxdir,serialmuxfile);
    getFileName(serialctrldir,serialctrlfile);

    char chemin[250];
    strcpy(chemin,serialmuxdir);
    strcat(chemin,"/slots\0");
    char echo[16]="ttyO0_armhf.com";

    char realnumber[2];

    sprintf(realnumber,"%d",number);

    echo[4]= realnumber[0];

    int serialmux=open(chemin,O_RDWR);
    write(serialmux,echo,16);
    close(serialmux);
}
