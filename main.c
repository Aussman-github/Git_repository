/*******************************************************
Name ......... : main.c
Author ...... : Aussman IDDIR
Version ..... : V1.1 2021
Licence ..... : GPL
********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include "debug.h"


#define MAX(a,b) (a>b)?a:b
#define MIN(a,b) (a<b)?a:b
#define ABS(x)    (x>0)? (x) : (-x)

#define TEST_WRAPAROUND (0)
#define UNIT_TEST (0)

#define BMW_ONLY (1)
#define DS5_ONLY (0)
#define DAIMLER_ONLY (0)

#if ( (BMW_ONLY + DS5_ONLY + DAIMLER_ONLY) > 1)
#error "Only one config car should be defined"
#endif

/* The one very important use case of function pointer is, interrupt routine */

/* Type qualifiers: const, volatile, restrict */

/* typedef is used to declare an alias for an existing type*/
typedef enum codes{
    enuJanuary      = 0x01,
    enuFebruary     = 0x02,
    enuMarch        = 0x03,
}codes_t;

typedef struct sigrecord{
    uint16_t signum;
    uint8_t signame[20];
    uint8_t sigdesc[100];
}sigrecord_t;

union{
    struct{
        int type;
    }n;

    struct {
        int type;
        int intnode;
    }ni;

    struct {
        int type;
        double numberdouble;
    }nf;
}u;





typedef signed char schar_t, *schar_p, (*fp)(void);

double addFunction(double a, double b);
double multiplyFunction(double a, double b);
double (*g_user_api)(double, double);
double wrapperFunction(double(*func_ptr)(double, double));
void setUserApi(double(*func_ptr)(double, double));

/* Function pointers */
double (*fptraddFunction)(double, double);
double (*fptrMultiplyFunction)(double, double);
static uint16_t counter;



int main (int argc, char *argv[]){
    _Atomic double resultAdd = 0;
    long double resultMultiply = 0;
    _Bool var1 = true;
    char char1 = 'a';
    char char2 = 'b';
    void *pu8var = NULL;
    sigrecord_t sigrecord1;
	codes_t myVar = 0x01;
    float fvar1 = -275.2;
    unsigned char uc1 = UCHAR_MAX; // 0xFF
    size_t varsize = sizeof resultMultiply;
    pu8var = &var1;

    dbgCheckValidAddr(pu8var);

    if(dbgValidAddr(pu8var)){}
    else{
        __trap();
    }
    fptraddFunction = addFunction;
    fptrMultiplyFunction = multiplyFunction;

    resultMultiply = fptrMultiplyFunction(2.5, 2);
    resultAdd = fptraddFunction(3, 4);
    printf("%x\r\n", ~uc1);
    printf("varsize number of bits = %d\r\n", varsize);
    printf("fvar1 = 0x%x\r\n", fvar1);
    printf("size of long long int = %d\r\n", sizeof(long long int));
    printf("size of long int = %d\r\n", sizeof(long int));
    printf("size of int = %d\r\n", sizeof(int));
    printf("size of short int = %d\r\n", sizeof(short int));
    printf("size of signed char = %d\r\n", sizeof(signed char));

    strcpy(sigrecord1.sigdesc, "Interrupt from Keyboard");
    strcpy(sigrecord1.signame, "SIG");
    strcat(sigrecord1.signame, "INT");
    printf("result = %f\n", resultAdd);
    printf("result = %2f\n", resultMultiply);

    resultAdd = wrapperFunction(addFunction);
    resultMultiply = wrapperFunction(multiplyFunction);

    printf("result add = %f\n", resultAdd);
    printf("result multiply = %2f\n", resultMultiply);
    printf("%c\n", char1);
	printf("test\r\n");
    // Initialize timer1
    // Disable interrupt for timer1
    // Set User API
    setUserApi(addFunction);
    // Enable timer 1 interrupt

    switch(myVar){
        case enuJanuary:
        {
			printf("January\n");

        }
        break;
        case enuFebruary:
        {

        }
        break;
        case enuMarch:
        {

        }
        break;
        default:
        break;
    }
	printf("size of int = %d\n", sizeof(int));
    printf("size of float = %d\n", sizeof (float));
    printf("size of double = %d\n", sizeof(double));
    printf("size of long double = %d\n", sizeof(long double));
    printf("sizeof char = %d\n", sizeof (char));

    printf("%s\n", sigrecord1.signame);
    printf("%s\n", sigrecord1.sigdesc);

#if ((defined TEST_WRAPAROUND) && (TEST_WRAPAROUND == 1))
    do{
        printf("%d\n", counter++);
    }while(counter !=UINT16_MAX);
#endif
    return EXIT_SUCCESS;
}


double addFunction(double a, double b){
    return a + b;
}


double multiplyFunction(double a, double b){
    return a*b;
}


double wrapperFunction(double(*func_ptr)(double, double)){
    return func_ptr(4, 3);
}

void INT_ROUTINE_TIMER1(){
    // call user API
    g_user_api(3,1);
}

void setUserApi(double(*func_ptr)(double, double)){
    g_user_api = func_ptr;
}
