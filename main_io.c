/*******************************************************
Name ......... : main_io.c
Author ...... : Aussman IDDIR
Version ..... : V1.1 2022
Licence ..... : GPL
********************************************************/
#define __STDC_WANT_LIB_EXT1__ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "debug.h"




int main(int argc, char *argv[]){
    FILE *fp = fopen("text.txt", "r");

    dbgCheckValidAddr(fp);

    /*fseek sets the file position indicator to the end of the file */
    if(fseek(fp, 0, SEEK_END) != 0){
        fputs("Error, cannot find SEEK_END \r\n", stderr);
        exit(EXIT_FAILURE);
    }

    /* The ftell function returns the current value of the file position indicator for the stream as a long int */
    long int fpi = ftell(fp);

    if(-1L == fpi){
        exit(EXIT_FAILURE);
    }

    printf("File position = %ld\r\n", fpi);

    if(EOF == fclose(fp)){
        fputs("Failed to close file \r\n", stderr);
        return EXIT_FAILURE;
    }

    return 0;
}