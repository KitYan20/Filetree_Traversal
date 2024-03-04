#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool wildcard(const char* str, char* pattern){
    if (strstr(pattern,".") != NULL){
        //Copy the pattern string 
        char pattern_copy[strlen(pattern)+1];
        strcpy(pattern_copy,pattern);
        printf("%s ",str);
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
        //Make a copy of the pattern string
        char str_copy[strlen(str)+1];
        strcpy(str_copy,str);
        while (str_copy[i] != '\0'){
            //Checks if the current character in the string matches the first character in the pattern string
            // This will be the intial state
            if (token3 == str_copy[i]){
                //Increment the pointer to move to the next character
                i++;
                char next_state = str_copy[i];
                //If the next character is the second token and the second character is also a second token, it will be a match 
                if (next_state == token4 && str_copy[i+1] == token4){
                    printf("Pattern matched\n");
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
                            printf("Pattern matched\n");
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
        printf("No Pattern Found\n");
        return false;
    }else if (strstr(pattern,"*") != NULL) {
        printf("Wildcard with *\n");
        return true;
    }else if (strstr(pattern,"?") != NULL){
        printf("Wildcard with ?\n");
        return true;
    }else if ((strstr(pattern,"(") != NULL) && (strstr(pattern,")")) != NULL){
        
        printf("Wildcard with ()\n");
        return true;
    }else{
        printf("Unknown delimeter\n");
        
        return false;
    }
}