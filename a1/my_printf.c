#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "itoa.h"
#include <string.h>

void my_printf(char *format, ...){
    //Have a variable initialized to store the number of arguments checked via % specifier
    int arg_count = 0;
    //Initialize the rbp base void pointer to check for the arguments passed on to the stack
    /*
    The first 5 arguments will be placed in registers with the
    arguments getting stored in reverse order with last arguments placed on the registers in this order
    r9 -> fifth argument 
    r8 -> fourth argument
    rcx -> third argument
    rdx -> second argument
    rsi -> first argument
    rdi -> gets the formatted string
    If more than 5 arguments are passed in, the rest of the arguments are passed onto the stack
    */
    void *rbp;
    //Initialize 5 void pointers to get the argument value in each of the register
    void *rsi, *rdx, *rcx,*r8, *r9;
    //Perform some inline assembly to get the argument value stored in the register
    asm volatile ("mov %%rsi, %0" : "=r" (rsi));
    asm volatile ("mov %%rdx, %0" : "=r" (rdx));
    asm volatile ("mov %%rcx, %0" : "=r" (rcx));
    asm volatile ("mov %%r8,  %0" : "=r" (r8));
    asm volatile ("mov %%r9,  %0" : "=r" (r9));
    asm volatile ("mov %%rbp, %0" : "=r" (rbp)); 
    //Increment the base pointer by 16 to ensure proper alignment pushed onto the stack
    rbp += 16; 
    //Initialize another void pointer to later be used for parsing through the formatted string
    //To keep track of what register to be used for the formatted string
    void *reg;
    //Check if the formatted string ends with '\0' indicating end of the formatted string
    while(*format != '\0'){
        //If the character is a %, increment the argument count and move on to the next character in the string
        //To indicate the type of data specifier
        if (*format == '%'){
            arg_count++;
            format++;
            //This switch statement will ensure what register to set to be used depending on the 
            //current number of argument it's currently being iterated through
            switch(arg_count){
                case 1:
                    reg = rsi;
                    break;              
                case 2:
                    reg = rdx;
                    break;          
                case 3:
                    reg = rcx;
                    break; 
                case 4:
                    reg = r8;
                    break;
                case 5:
                    reg = r9;
                    break;
                default:
                    break;
            }
            //Now we check for the specific format specifier to print back out
            switch(*format){
                case 'c': //The current data type is a 1 byte character data type
                    char c;
                    //Check on the stack if the number of arguments is greater than 5 <- this will be for every format specifier
                    if (arg_count > 5){
                        //convert the void* into a char* and dereference with * outside of the char*
                        //to get the char
                        c = *((char*)rbp);
                        //increment rbp by 8
                        rbp += 8;
                    }else{
                        //Type cast it into a intptr_t from void * and then dereference it to int type
                        c = (int)(intptr_t)reg;
                    }
                    //putchar will write back out one single character back to stdout
                    putchar(c);
                    break;
                
                case 's': //The current data type is a string data type 
                    char *str;
                    if (arg_count > 5){
                        //The string will be stored on a pointer holding the
                        // memory address to the string in rbp thus need to do a pointer to pointer
                        //Dereference it again
                        str = *(char**)rbp;
                        //increment rbp by 8
                        rbp += 8;
                    }else{
                        //Do type cast of void* to char* to get the string
                        //If it's in a register
                        str = (char*)reg;
                    }
                    //Print back out the string by printing one single character in the string
                    //at a time
                    while(*str != '\0'){
                        putchar(*str);
                        str++;
                    }  
                    break;
                
                case 'd'://This is a integer data type
                    char d[256];
                    int decimal;
                    if (arg_count > 5){
                        decimal = *((int*)rbp);
                        rbp += 8;
                    }else{
                        //Same format to dereference for c, d, x, and u number data types
                        decimal = (int)(intptr_t)reg;
                        
                    }
                    //Use the itoa to convert the integers back to ASCII
                    itoa(d,'d',decimal);
                    //Print back out the string by printing one single character in the string at a time
                    for (int j = 0; d[j] != '\0'; j++) {
                        putchar(d[j]); 
                    }
                    break;  
                
                case 'x':
                    char x[256];
                    int hex;
                    if (arg_count > 5){
                        hex = *((int*)rbp);
                        rbp+= 8;
                    }else{
                        hex = (int)(intptr_t)reg;
                        
                    }
                    itoa(x,'x',hex);
                    //Print back out the string by printing one single character in the string at a time
                    for (int j = 0; x[j] != '\0'; j++) {
                        putchar(x[j]); 
                    }
                    break; 
                
                case 'u':
                    char u[256];
                    unsigned int udecimal;
                    if (arg_count > 5){
                        udecimal = *((unsigned int*)rbp);
                        rbp += 8;
                    }else{
                        //Make sure to dereference the unsigned int ptr as a unsigned int p
                        udecimal = (unsigned int)(uintptr_t)reg;
                    }
                    itoa(u,'d',udecimal);
                    //Print back out the string by printing one single character in the string at a time
                    for (int j = 0; u[j] != '\0'; j++) {
                        putchar(u[j]); 
                    }
                    break; 
                
                default: 
                    //If it's not one of those case, print it back out to stdout
                    putchar(*format);
                    break;         
            }
            
        }else {
            //If there are not format '%' specifier, print it back out to stdout
            putchar(*format);           
        } 
        //Move along in the formatted string  
        format++;
        
    }  
       
}

int main(int argc, char *argv[]){
    // my_printf("%s %d\n", "hello world",8);
    // my_printf("Hello %s %c %d %u %x %s %c %d %x\n","CS410",'R', 8 , 12, 30, "CS210",'h',9,10);
    // printf("Hello %s %c %d %u %x %s %c %d\n","CS410",'R', 8 , 12, 30, "CS210",'h',9);
    // my_printf("Hello %c %c\n", 'c','c');
    // my_printf("%s %c %d %u %x %d %d\n","hello", 'c', 8 , 12345, 15,20,25);
    return 0;
    
}