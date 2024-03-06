#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
bool wildcard(const char* str, char* pattern){
    
    char ch = *pattern;
    char pattern_copy[strlen(pattern)+1];
    strcpy(pattern_copy,pattern);
    //Make a copy of the pattern string
    char str_copy[strlen(str)+1];
    strcpy(str_copy,str);
    if (strstr(pattern,".") != NULL){
        //Copy the pattern string 
        //printf("%s ",str);
        //Separate the pattern string into tokens by the "."
        char* token = strtok(pattern_copy,".");
        //Get the token from the left side
        char* token1 = token;
        //Get the token from the right side
        char *token2;
        //Standard function to get the token
        while (token != NULL) {
            token2 = token;
            token = strtok(NULL, ".");
        }
        //Dereference the first and second token into chars because 'C' 
        char token3 = *token1;
        char token4 = *token2;
        int i = 0;
        while (str_copy[i] != '\0'){
            //Checks if the current character in the string matches the first character in the pattern string
            // This will be the intial state
            if (token3 == str_copy[i]){
                //Increment the pointer to move to the next character
                i++;
                char next_state = str_copy[i];
                //If the next character is the second token and the second character is also a second token, it will be a match 
                if (next_state == token4 && str_copy[i+1] == token4){
                    //printf("Pattern matched\n");
                    return true;
                    break;
                //Else case will be if the next character isn't the second token
                //Will have to increment to the next character given the "."
                //Requirement to have any other character between the second token and after the first token
                }else if(next_state == token4){
                    i++;
                }else{
                    //Have a nested while loop to continue iterating the string
                    while(str_copy[i] != '\0'){
                        //When it finally finds a match of the second token, it will break out of the loop
                        if (str_copy[i] == token4){
                            //printf("Pattern matched\n");
                            return true;
                            break;
                            
                        }else{
                        //Continue to next character
                        //Eventually, this loop will exit out and will also exit out the outer while loop
                        //Since we have iterated throught the entire string already
                            i++;
                        }
                    }
                }
            }
            //Move on to the next character in the string
            else{
                i++;
            }
        }
        //Return false if no pattern is found
        //printf("No Pattern Found\n");
        return false;
    }else if (strstr(pattern,"*") != NULL) {
        //Separate the pattern string into tokens by the "."
        char* token = strtok(pattern_copy,"*");
        //Get the token from the left side
        char* token1 = token;
        //Get the token from the right side
        char *token2;
        //Standard function to get the token
        while (token != NULL) {
            token2 = token;
            token = strtok(NULL, "*");
        }
        //Get the last n-1 characters
        char str1[256];
        char str2[2];
        str2[0] = token1[strlen(token1)-1];
        str2[1] = '\0';
        if (strlen(token1) > 1){
            strncpy(str1,token1, strlen(token1)-1);
            str1[strlen(token1) - 1] = '\0';
            
        }else{
            strcpy(str1,token1);
            str1[strlen(str1)] = '\0';
        }
        //printf("%s %s %s\n",str1,str2,token2);
        int i = 0;

        int len_token1 = strlen(str1);
        int len_token2 = strlen(token2);
        //Edge case to account for just the character b in a string
        //IF the wildcard pattern previous and next character is length 1, just need to check if the character b exist in the string
        if (strlen(token1) == 1 && strlen(token2) == 1 && strstr(str_copy,token2) != NULL){
            printf("Pattern Matched\n");
            return true;
        }
        else if(strstr(str_copy,str1) != NULL || strstr(str_copy,token2) != NULL){
            while(str_copy[i] != '\0'){
                char *temp = (char*)malloc(len_token1+1);
                int j = i;
                int k = 0;
                if (temp == NULL){
                    //printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                while(str_copy[j] != '\0' && k < len_token1){
                    temp[k] = str_copy[j];
                    j++;
                    k++;
                }
                temp[k] = '\0';
                // printf("Temp %s\n",temp);
                if (strlen(temp) < len_token1){
                    // printf("Temp %s\n",temp);
                    printf("No pattern found\n");
                    return false;
                }
                j = i;
                int l = 0;
                if (strcmp(str1,temp) == 0){
                    char *next_char = (char*)malloc(strlen(str2)+1);
                    if (next_char == NULL){
                        //printf("Memory Allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    while(l < len_token2){
                            next_char[l] = str_copy[j+len_token1];
                            j++;
                            l++;
                    }
                    next_char[l] = '\0';
                    //printf("hi %s %s",next_char,temp);
                    if (strcmp(token2,next_char) == 0){
                            // printf("%s\n",next_char);
                            printf("Pattern Matched\n");
                            free(temp);
                            free(next_char);
                            return true;
                    }else if (strcmp(str2,next_char) == 0){
                        char *next_char2 = (char*)malloc(strlen(str2)+1);
                        next_char2[0] = str_copy[j+strlen(str1)];
                        next_char2[1] = '\0';
                        //printf("hi %s %s",next_char2,temp);
                        if (strcmp(token2,next_char2) == 0){
                                printf("Pattern Matched\n");
                                free(temp);
                                free(next_char);
                                free(next_char2);
                                return true;
                        }else{
                            
                            while(strcmp(str2,next_char2) == 0){
                                next_char2[0] = str_copy[j+strlen(str1)];
                                next_char2[1] = '\0';
                                // printf("%s",next_char2);
                                if (strcmp(token2,next_char2) == 0){
                                    printf("Pattern Matched\n");
                                    free(temp);
                                    free(next_char);
                                    free(next_char2);
                                    return true;
                                }else{
                                    j++;
                                }
                            }

                        }
                        
                    }
                    else{
                        free(next_char);
                    }              
                }
                free(temp);
                i++;
            }
              
        }else{
            printf("No Pattern found\n");
            return false;
        }
        // //strncmp
        // //strstr
        printf("No pattern found\n");
        return false;
        
    }else if (strstr(pattern,"?") != NULL){
        //Separate the pattern string into tokens by the "."
        char* token = strtok(pattern_copy,"?");
        //Get the token from the left side aka leftside of the wildcard
        char* token1 = token;
        //Get the token from the right side aka rightside of the wildcard
        char *token2;
        //Standard function to get the token
        while (token != NULL) {
            token2 = token;
            token = strtok(NULL, "?");
        }
        int len_token1 = strlen(token1);
        int len_token2 = strlen(token2);
        int i = 0;
        //printf("%s %d %s %d %s\n",token1,len_token1,token2,len_token2, str_copy);
        
        /*Accounts for the case of the wildcard pattern have only one character before the wildcard and after the wildcard "?"
         *Looking at the "?" wildcard, as long as there's a instance of the character after the "?" in the string
         *And the preceding the character is only of length one, you just need to check if the character after the "?"
         *Exist in the string
        */
        if (strlen(token1) == 1 && strlen(token2) == 1 && strstr(str_copy,token2) != NULL){
            printf("Pattern Matched\n");
            return true;
        }//Check if both the preceding string and string before and after the wildcard exist in the string
        //Does not check if its in order of the pattern
        else if(strstr(str_copy,token1) != NULL && strstr(str_copy,token2) != NULL){
            while(str_copy[i] != '\0'){
                char *temp = (char*)malloc(len_token1+1);
                if (temp == NULL){
                    //printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                int j = i;
                int k = 0;
                while(str_copy[j] != '\0' && k < len_token1){
                    temp[k] = str_copy[j];
                    j++;
                    k++;
                }
                temp[k] = '\0';
                if (strlen(temp) < len_token1){
                    //printf("No pattern found");
                    return false;
                    
                }
                char *next_char =  (char*)malloc(len_token2+1);
                if (next_char == NULL){
                    //printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                //Reassign j to be the previous character before adding length of n substring
                j = i;
                int l = 0;
                while(l < len_token2){
                    next_char[l] = str_copy[j+strlen(token1)];
                    j++;
                    l++;
                }
                next_char[l] = '\0';
                //printf("%s %s\n",temp,next_char);
                if (strcmp(token1,temp) == 0 && strcmp(token2,next_char) == 0){
                    printf("Pattern Found %s %s with string %s\n",temp,next_char,str_copy);
                    return true;    
                }
                free(next_char);
                free(temp);
                i++;
           
            }
        }
        printf("No Pattern Found with %s\n",str_copy);
        return false;

    }else if ((strstr(pattern,"(") != NULL) && (strstr(pattern,")")) != NULL){
        
        printf("Wildcard with ()\n");
        return true;
    }else if (isalnum(ch)){
        if(strstr(str,pattern) != NULL){
            return true;
        }   

    }else{
        printf("Unknown delimeter\n");
        
        return false;
    }
}