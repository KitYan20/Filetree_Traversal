#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool wildcard(const char* str, char* pattern){
    char ch = *pattern;
    char pattern_copy[strlen(pattern)+1]; //Make a copy of the pattern string;
    strcpy(pattern_copy,pattern);
    char str_copy[strlen(str)+1]; //Make a copy of the string itself
    strcpy(str_copy,str);
    if (strstr(pattern,".") != NULL){ //Check if the "." wildcard is in the string
        //printf("%s ",str);
        char* token = strtok(pattern_copy,".");//Separate the pattern string into tokens by the "."
        char* token1 = token; //Get the token from the left side
        char *token2; //Get the token from the right side
        while (token != NULL) {  //Standard function to get the token
            token2 = token;
            token = strtok(NULL, ".");
        }
        //Dereference the first and second token into chars because 'C' 
        char token3 = *token1;
        char token4 = *token2;
        int i = 0;
        while (str_copy[i] != '\0'){//Checks if the current character in the string matches the first character in the pattern string
            // This will be the intial state
            if (token3 == str_copy[i]){
                i++; //Increment the pointer to move to the next character
                char next_state = str_copy[i]; //If the next character is the second token and the second character is also a second token, it will be a match 
                if (next_state == token4 && str_copy[i+1] == token4){
                    //printf("Pattern matched\n");
                    return true;
                    break;
                //Will have to increment to the next character given the "."
                //Requirement to have any other character between the second token and after the first token
                }else if(next_state == token4){//Else case will be if the next character isn't the second token
                    i++;
                }else{
                    while(str_copy[i] != '\0'){//Have a nested while loop to continue iterating the string
                        if (str_copy[i] == token4){//When it finally finds a match of the second token, it will break out of the loop
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
            else{ //Move on to the next character in the string
                i++;
            }
        }
        //printf("No Pattern Found\n");
        return false;//Return false if no pattern is found
    }
    //Checks for parenthesis in the wilcard string
    else if ((strstr(pattern,"(") != NULL) && (strstr(pattern,")")) != NULL){ //Parentheses
        //printf("%s\n",pattern);
        int count = 0;
        //Condition to check for parentheis opened before it has been closed
        for (int i = 0; i < strlen(pattern); i++){
            // printf("%c\n",pattern_copy[i]);
            if (pattern_copy[i] == '('){
                count++;
            }
            else if (pattern_copy[i] == ')' && count == 1){
                count = 0;
                //printf("closing parenthesis found\n");
            }else if (pattern_copy[i] == ')' && count > 1){
                //printf("Invalid parenthesis\n");
                return false;
            }
        }
        //Checks for the wildcard pattern "?" in the string
        if (strstr(pattern,"?") != NULL){
            char literal_start[256]; //Initialize string to hold fixed characters if any in our wildcard before the group substring
            char literal_end[256]; //Initialize string to hold fixed characters after the wildcard
            char substring[256]; //Initialize string to hold fixed characters if any in our wildcard for the group substring
            // printf("Wildcard with () and ?\n");
            int i = 0;
            //Process to extract characters before parenthesis
            while(pattern_copy[i] != '(' && pattern_copy[i] != '\0'){
                literal_start[i] = pattern_copy[i];
                i++;
            }
            literal_start[i] = '\0'; //End it with a Null character
            int len_literal_start = i;//Store the length of the start literal string
            int j = 0; //Extracting substrings within ()
            if (pattern_copy[i] == '('){
                i++; 
                while(pattern_copy[i] != ')' && pattern_copy[i] != '\0'){
                    substring[j] = pattern_copy[i];
                    i++;
                    j++;
                }
            }
            substring[j] = '\0'; //End it with a Null character
            int k = 0; //Extract characters after the parenthesis 
            if (pattern_copy[i] == ')'){
                i++;
                if (pattern_copy[i] == '?'){//Skip the wildcard
                    i++;
                }
                while(pattern_copy[i] != '\0'){//Extract the rest of the characters
                    literal_end[k] = pattern_copy[i];
                    i++;
                    k++;
                }
            }
            literal_end[k] = '\0'; //End it with a Null character
            int len_substring = j; //Get the length of the substring
            int len_literal_end = k; //get the length of the end of pattern string 
            i = 0; //reset i,j,k to 0 to be used for later
            j = 0;
            k = 0;
            // printf("%s %s %s %s %d %d %d\n",str_copy,literal_start ,substring,literal_end,i,j,k);
            // printf("%d %d %d\n",len_literal_start,len_substring,len_literal_end);
            for (i = 0; i < strlen(str_copy); i++){ //iterate through the string
                char current_char[len_literal_start+1]; //Get the substring based on the length of the fixed start string
                memset(current_char,0,sizeof(current_char));//use memset to reset the current character string 
                for (j = 0; j < len_literal_start; j++){//Basically filling out the current substring up until the length of the string before parenthesis
                        current_char[j] = str_copy[i+j];//add i + j because we will be going through the string sequentially sliding window
                }
                current_char[j] = '\0';//End it with a Null character
                // printf("%s\n",current_char);
                if (len_literal_start == 0){ //a if condition to check if the start literal string of the wild card has a length of 0 or more
                    j = i; //set j to i if there is no start substring and go back to the current position of the string iterated
                }else{
                    j = j; //set it back to j to get the next character in the string
                }
                if (strcmp(literal_start,current_char) == 0 || len_literal_start == 0){//Checks if the start string exist in the current iteration or the length is 0
                    char group_char[len_substring];//Initialize another string to store our group substring to check for the substring within the parenthesis
                    memset(group_char,0,sizeof(group_char));//Use memset to reset after each iteration
                    for (k = 0; k < strlen(substring); k++){
                        group_char[k] = str_copy[j+k];//Filling in the substring                
                    }
                    group_char[k] = '\0';//End it with a Null character
                    // printf("%s\n",group_char);
                    //Checks if the group substring exist in the string and no fixed characters before parenthesis and after the wildcard
                    if (strcmp(substring,group_char) == 0 && len_literal_start == 0 && len_literal_end == 0){
                        //printf("Pattern found\n");
                        return true;
                    //Checks if the group substring exist and the previous characters are followed by the substring afterward
                    //No fixed characters in the after the wildcard
                    }else if ((strcmp(substring,group_char) == 0 || strcmp(substring,group_char) != 0 ) && strcmp(literal_start,current_char) == 0 && len_literal_end == 0){
                        //printf("Pattern found\n");
                        return true;
                    //Checks if the group substring exist and the previous characters comes before the substring also exist afterward
                    //and then check if the next substring matches with the fixed string after the wildcard
                    }else if ((strcmp(substring,group_char) == 0 || strcmp(substring,group_char) != 0 ) && strcmp(literal_start,current_char) == 0 && len_literal_end != 0){
                        k++; //Move to the next character after matching with the substring
                        j = k; //set j to k to be use for iterating through the string
                        k = 0; //reset k to 0 to be used later
                        char next_char[len_literal_end]; //Initialize the next_char string to store the substring after the wildcard
                        memset(next_char,0,sizeof(next_char));
                        for (k = 0; k < len_literal_end; k++){
                            next_char[k] = str_copy[j+k];//Filling in the substring 
                        }
                        next_char[k] = '\0';//End it with a Null character
                        //printf("%s\n",next_char);
                        if (strcmp(literal_end,next_char) == 0){//Checks the next group of substring does indeed match with the string at the end of the wildcard
                            //printf("Pattern  matched\n");
                            return true;
                        }else{
                            continue;
                        }
                    }else{
                        continue;
                    }
                }else{
                    continue;
                }     
    
            }
            //printf("No pattern found\n");
            return false;

        }else if (strstr(pattern,"*") != NULL){//Checks for the wildcard pattern "*" in the string
            //Mostly same process with ?
            char literal_start[256];
            char literal_end[256];
            char substring[256];
            //printf("Wildcard with () and *\n");
            int i = 0;
            //Extracting characters before (
            while(pattern_copy[i] != '(' && pattern_copy[i] != '\0'){
                literal_start[i] = pattern_copy[i];
                i++;
            }
            literal_start[i] = '\0';
            
            //Extracting substrings within ()
            int j = 0;
            if (pattern_copy[i] == '('){
                i++;
                while(pattern_copy[i] != ')' && pattern_copy[i] != '\0'){
                    substring[j] = pattern_copy[i];
                    i++;
                    j++;
                }
            }
            substring[j] = '\0';
            int k = 0;
            if (pattern_copy[i] == ')'){
                i++;
                if (pattern_copy[i] == '*'){
                    i++;
                }
                while(pattern_copy[i] != '\0'){
                    literal_end[k] = pattern_copy[i];
                    i++;
                    k++;
                }
            }
            literal_end[k] = '\0';
            i = 0;
            j = 0;
            k = 0;
            // printf("%s %s %s %d %d %d\n",literal_start ,substring,literal_end,i,j,k);
            while(str_copy[i] != '\0'){
                char current_char[2];
                memset(current_char,0,sizeof(current_char));
                current_char[0] = str_copy[i];
                current_char[1] = '\0'; //End it with a Null character
                //Checks if the current character matches with the start character before parenthesis
                if (strcmp(literal_start,current_char) == 0 || strcmp(" ",literal_start)){
                    j = i;
                    j++;
                    //Move on to the next process of grouping the substring given the size of the string within the wildcard parenthesis
                    char group_char[sizeof(substring)];
                    memset(group_char,0,sizeof(group_char));
                    while(k < strlen(substring)){ //Filling in the substring to check with
                        group_char[k] = str_copy[j];
                        k++;
                        j++;
                    }
                    group_char[k] = '\0'; //End it with a Null character
                    k = 0; //Reset k to 0
                    //printf("%s",group_char);
                    if (strcmp(substring,group_char) == 0){//Checks if the current group of substring matches with the pattern inside
                        if (strcmp(" ",literal_end) == 0){//Checks if theres no substring after the wildcard
                            //There would be match
                            //printf("Pattern found\n");
                            return true;
                        }else {//If not, just repeat the process to check if the next character matches with the string literal at the end of the wildcard
                            char next_char[sizeof(literal_end)];
                            memset(next_char,0,sizeof(next_char));
                            while(k < strlen(literal_end)){ //Filling in the substring to check with
                                next_char[k] = str_copy[j];
                                k++;
                                j++;
                            }
                            next_char[k] = '\0';//End it with a Null character
                            k = 0;//Reset k to 0
                            if (strcmp(literal_end,next_char) == 0){//Checks if theres a match with a string literal at the end of the wildcard
                                //printf("Pattern found\n for %s %s", group_char,next_char);
                                return true;
                            }else{
                                i++;
                            }
                        }
                    }else{
                        i++;
                    }
                    
                }else{
                    i++;
                }    
            } 
        }else{
            //printf("Unknown delimeter\n");
            exit(EXIT_FAILURE);
        }
        //printf("No Pattern Found\n");
        return false;
    }
    else if (strstr(pattern,"*") != NULL) {//Checks for the "*" wildcard
        char* token = strtok(pattern_copy,"*");//Separate the pattern string into tokens by the "*"
        char* token1 = token; //Get the token from the left side of the wildcard
        char *token2;//Get the token from the right side of the card
        while (token != NULL) {   //Standard function to get the tokens from each side
            token2 = token;
            token = strtok(NULL, "*");
        }
        //Get the last n-1 characters
        //str1 will get the substring of character excluding the previous 
        //character of the wildcard -> eg aba*b 
        //                                / \
        //                               ab  a
        char str1[256];
        char str2[2]; //str2 will get the character of the single character before the wildcard
        str2[0] = token1[strlen(token1)-1];
        str2[1] = '\0';
        if (strlen(token1) > 1){//if the string on the right side has only more than one character, separate n - 1 characters from the right substring
            strncpy(str1,token1, strlen(token1)-1); //Make a copy of the string
            str1[strlen(token1) - 1] = '\0';//End it with a Null character
        }else{//However if its only one character on the left, store str1 with that one character
            strcpy(str1,token1); //Make a copy of the string
            str1[strlen(str1)] = '\0'; //End it with a Null character
        }
        //printf("%s %s %s\n",str1,str2,token2);
        int i = 0;
        int len_token1 = strlen(str1); //get the length of each substring from each side of the wildcard excluding the last character in the left substring
        int len_token2 = strlen(token2);
        //Case 1 to account for just the character on in a string
        //If the wildcard pattern previous and next character is length 1, just need to check if the character b exist in the string
        if (strlen(token1) == 1 && strlen(token2) == 1 && strstr(str_copy,token2) != NULL){ 
            //printf("Pattern Matched\n");
            return true;
        //A case to handle if just a previous character is in the wildcard
        }else if (strstr(str_copy,str1) != NULL && strstr(str_copy,str2) != NULL && strstr(str_copy,token2) != NULL){
            //printf("Pattern Matched\n");
            return true;
        }
        else if(strstr(str_copy,str1) != NULL || strstr(str_copy,token2) != NULL){//Case 2 to account if str1 (left side of the wildcard) or token2 (right side of the wildcard) exist in the string but need to still iterate through it to see if its in sequence for pattern matching
            //Iterate through the string character by character
            while(str_copy[i] != '\0'){
                char *temp = (char*)malloc(len_token1+1); //use malloc to allocate string storage for the length of left side substring
                int j = i; //Initialize a nested pointer to be used for later when we iterate through the string multiple times
                int k = 0;//Intialize another counter to store our left side substring up til the length of the left substring in the wildcard
                if (temp == NULL){//Cases to exit the program if memory allocation failed
                    printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                while(str_copy[j] != '\0' && k < len_token1){//This is where we essentially do sliding window to get a substring of k characters from the main string
                    temp[k] = str_copy[j];
                    j++;
                    k++;
                }
                temp[k] = '\0';//End it with a Null character
                // printf("Temp %s\n",temp);
                //This essentially checks the whole string and see if the length of the temporary string is less than the left side of the wildcard
                //This usually happens when it reaches to a state where it's at the end of the string and still hasn't found a match
                if (strlen(temp) < len_token1){
                    // printf("Temp %s\n",temp);
                    //printf("No pattern found\n");
                    return false;
                }
                j = i; //Reset j back to wherever i was pointing to in the string
                int l = 0; //Initialize a new variable to iterate through the string
                //If the temporary string finds a match with the left side substring we now check to see if there are occurences of the next character and if it does find it, then its a match
                if (strcmp(str1,temp) == 0){
                    char *next_char = (char*)malloc(strlen(str2)+1); //Allocate enough memory for one character string
                    if (next_char == NULL){
                        //printf("Memory Allocation failed\n");
                        exit(EXIT_FAILURE);
                    }
                    while(l < len_token2){//Fill in the next character string up until length of the righ side substring of the wildcard
                            next_char[l] = str_copy[j+len_token1];
                            j++;
                            l++;
                    }
                    next_char[l] = '\0';//End it with a Null character
                    //If the next character does indeed match with the rightside, then we can stop iterating through as it found a pattern
                    if (strcmp(token2,next_char) == 0){
                            //printf("Pattern Matched\n");
                            free(temp);//Make sure to free up memory from the heap
                            free(next_char); //Make sure to free up memory from the heap
                            return true;
                    //Otherwise, we check to see if the next character matches with the same instance of the single character before the wildcard
                    }else if (strcmp(str2,next_char) == 0){
                        char *next_char2 = (char*)malloc(strlen(str2)+1); //Allocte enough memory for the next char
                        next_char2[0] = str_copy[j+strlen(str1)];//Fill in the character string with the next characters
                        next_char2[1] = '\0';
                        //Now we check again to see if it matches with the rightside of the wildcard
                        if (strcmp(token2,next_char2) == 0){//If it does, make sure to free up memory from the heap and return a match
                                // printf("Pattern Matched\n");
                                free(temp);
                                free(next_char);
                                free(next_char2);
                                return true;
                        }else{
                        //If that is not the case, we need to keep iterating through the string and check continuosly to see if the next character matches the previous character
                        //Essentially checking the final state here as well 
                            while(strcmp(str2,next_char2) == 0){
                                next_char2[0] = str_copy[j+strlen(str1)];
                                next_char2[1] = '\0';
                                //printf("%s",next_char2);
                                if (strcmp(token2,next_char2) == 0){
                                    //printf("Pattern Matched\n");
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
                free(temp); //make sure to free memory from the heap
                i++;//Else case is we just reset the string back to where i was in the string and increment by one
            }
        }else{ //If it satisfies none of the cases, we just return false meaning no pattern was found
            //printf("No Pattern found\n");
            return false;
        }
        //printf("No pattern found\n");
        return false; //Main case of not finding other cases that wasn't accounted for
        
    }else if (strstr(pattern,"?") != NULL){ //Checks for the "?" wildcard
        char* token = strtok(pattern_copy,"?");//Separate the pattern string into tokens by the "?"
        char* token1 = token;//Get the token from the left side aka leftside of the wildcard
        char *token2;//Get the token from the right side aka rightside of the wildcard
        while (token != NULL) {//Standard function to get the token
            token2 = token;
            token = strtok(NULL, "?");
        }
        int len_token1 = strlen(token1);//Get the length of both side of the wildcard string
        int len_token2 = strlen(token2);
        int i = 0;
        //printf("%s %d %s %d %s\n",token1,len_token1,token2,len_token2, str_copy);
        
        /*Accounts for the case of the wildcard pattern have only one character before the wildcard and after the wildcard "?"
         *Looking at the "?" wildcard, if there's a instance of the character after the "?" in the string
         *And the preceding the character is only of length one, you just need to check if the character after the "?"
         *Exist in the string
        */
        if (strlen(token1) == 1 && strlen(token2) == 1 && strstr(str_copy,token2) != NULL){
            //printf("Pattern Matched\n");
            return true;
        }//Check if both the preceding string and string before and after the wildcard exist in the string but does not check if its in order of the pattern
        //Cases where the length of the leftside string of the wildcard is greater than 1
        else if(strstr(str_copy,token1) != NULL && strstr(str_copy,token2) != NULL){
            while(str_copy[i] != '\0'){//Iterate through the whole string character by character
                char *temp = (char*)malloc(len_token1+1); //Allocate enough memory on the heap for one character string
                if (temp == NULL){
                    //printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                //Initialize a pointer j to be a nested pointer when iterating through the string too perform other conditional checks
                int j = i;
                int k = 0;
                //Fill in the temporary substring of the string until its the same length of the left side substring this will change throughout iterations of the string
                while(str_copy[j] != '\0' && k < len_token1){
                    temp[k] = str_copy[j];
                    j++;
                    k++;
                }
                temp[k] = '\0'; //End the temporary substring with a null terminated character
                //Same reason from *
                if (strlen(temp) < len_token1){
                    //printf("No pattern found");
                    return false;
                    
                }
                char *next_char =  (char*)malloc(len_token2+1);
                if (next_char == NULL){
                    //printf("Memory Allocation failed\n");
                    exit(EXIT_FAILURE);
                }
                j = i;
                int l = 0;//Reassign j to be the previous character before adding length of right side of the wildcard substring               
                while(l < len_token2){//Getting the next character in the string
                    next_char[l] = str_copy[j+strlen(token1)];
                    j++;
                    l++;
                }
                next_char[l] = '\0';//End the string with a null terminated character
                //printf("%s %s\n",temp,next_char);
                if (strcmp(token1,temp) == 0 && strcmp(token2,next_char) == 0){//Check to see if the leftside substring and next character both match the pattern of the wildcard string
                    //printf("Pattern Found %s %s with string %s\n",temp,next_char,str_copy);
                    free(next_char);//Make sure to free the memory before exiting the program
                    free(temp);
                    return true;    
                }
                free(next_char);
                free(temp);//Continue iterating the string and free the memory for both the strings
                i++;
            }
        }
        //No pattern found if the whole string has been iterated and none of the conditions are satisfied
        //printf("No Pattern Found with %s\n",str_copy);
        return false;

    }else {//Checks for cases where it's just alphanumerical characters 
        if(strstr(str,pattern) != NULL){
            return true;
        }   
    }
}