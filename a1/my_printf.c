#include <stdio.h>
#include <stdlib.h>
#include "itoa_h"
#include <string.h>


void my_printf(char *format, ...){
    int count = 0;
    int i = 0;
    void *rbp;
    void *rsi, *rdx, *rcx,*r8, *r9;
    asm volatile ("mov %%rsi, %0" : "=r" (rsi));
    asm volatile ("mov %%rdx, %0" : "=r" (rdx));
    asm volatile ("mov %%rcx, %0" : "=r" (rcx));
    asm volatile ("mov %%r8,  %0" : "=r" (r8));
    asm volatile ("mov %%r9,  %0" : "=r" (r9));
    asm volatile ("mov %%rbp, %0" : "=r" (rbp));  
    void *sp = rbp + 16;  
     // Store all the registers and it's values in a array
    void *register_values[] = {rsi, rdx, rcx, r8, r9};
    while(*format != '\0'){
        if (*format == '%'){
            count++;
            ++format;
            switch(*format){
                case 'c':{
                    char c;
                    if (count > 5){
                        c = *((char*)sp);
                        sp += 8;
                    }else{
                        c = register_values[i];
                        i++;
                    }
                    putchar(c);
                    break;
                }
                case 's':{
                    char *str;
                    if (count > 5){
                        str = *(char**)sp;
                        sp += 8;
                    }else{

                        str = register_values[i];
                        i++;
                    }
                    while(*str != '\0'){
                        putchar(*str);
                        str++;
                    }  
                    break;
                }
                case 'd':{
                    char d[256];
                    int decimal;
                    if (count > 5){
                        decimal = *((int*)sp);
                        sp += 8;
                    }else{
                        decimal = register_values[i];
                        i++;
                    }
                    itoa(d,'d',decimal);
                    for (int j = 0; d[j] != '\0'; j++) {
                        putchar(d[j]); // Print each character of the string using putchar
                    }
                    break;  
                }
                case 'x':{
                    char x[256];
                    int hex;
                    if (count > 5){
                        hex = *((int*)sp);
                        sp+= 8;
                    }else{
                        hex = register_values[i];
                        i++;
                    }
                    itoa(x,'x',hex);
                    for (int j = 0; x[j] != '\0'; j++) {
                        putchar(x[j]); // Print each character of the string using putchar
                    }
                    break; 
                }
                case 'u':{
                    char u[256];
                    unsigned int udecimal;
                    if (count > 5){
                        udecimal = *((unsigned int*)sp);
                        sp += 8;
                    }else{
                        udecimal = register_values[i];
                        i++;
                    }
                    itoa(u,'u',udecimal);
                    for (int j = 0; u[j] != '\0'; j++) {
                        putchar(u[j]); // Print each character of the string using putchar
                    }
                    break; 
                }
                default: 
                    putchar(*format);
                    break;
            }
            format++;
        }else{
            putchar(*format); 
            format++;
        }   
    }       
}

int main(int argc, char *argv[]){
    //my_printf("%s %d\n", "hello",8);
    my_printf("Hell %s %c %d %u %x %s %c %d\n","hello",'H', 8 , 12, -2, "world",'h',9);
    printf("Hell %s %c %d %u %x %s %c %d\n","hello",'H', 8 , 12, -2, "world",'h',9);
    my_printf("Hello %c %c\n", 'c','c');
    //my_printf("%s %c %d %u %x %d %d\n","hello", 'c', 8 , 12345, 15,20,25);
    
}