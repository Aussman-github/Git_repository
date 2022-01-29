/*******************************************************
Name ......... : main_strings.c
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

static char *getsfunction(char *dest);

/* Two character sets: ASCII and Unicode */

// strcpy, strncpy, strcat, strncat, strlen, memcpy, memmove


int main(int argc, char *argv[]){

    char wcvar1 = 'a';
    char acStr[100] = "Here comes the sun\r\n" ;
    size_t sStrSize = sizeof(acStr);
    size_t sacStrLen = strlen(acStr) + 1; // strlen() counts code units
    char *dest = (char *)malloc(sacStrLen);
    char response[8];
    size_t sSizeResponse = sizeof(response);

    if(dbgValidAddr(dest)){
        strcpy(dest, acStr);
    }else{
        __trap();
    }

    for(int i=0; i< sacStrLen; i++) {
        printf("%c", dest[i]);
    }

    puts("Continue? [y] n: ");
    fgets(response, sSizeResponse, stdin);

    if('n' == response[0]){
        exit(EXIT_SUCCESS);
    }

    printf("%s\r\n", response);

    free(dest);
    return 0;
}


static char *getsfunction(char *dest){
    char c;
    char *p = dest;

    while((c = getchar()) != EOF && c!= '\n' ){
        *p++ = c;
    }
    *p = '\0';
    return dest;
}