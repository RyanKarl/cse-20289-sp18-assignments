/* library.c: string utilities library */

#include "str.h"

#include <ctype.h>
#include <string.h>

/**
 * Convert all characters in string to lowercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	str_lower(char *s) {
    char *x = s;
    while(*x){
        *x=(tolower(*x));
        x++;
    }

    return s;
}

/**
 * Convert all characters in string to uppercase.
 * @param   s       String to convert
 * @return          Pointer to beginning of modified string
 **/
char *	str_upper(char *s) {
    char *x = s;
    while(*x){
        *x=(toupper(*x));
        x++;
    }        
 
    return s;
}

/**
 * Returns whether or not the 's' string starts with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' starts with 't'
 **/
bool	str_startswith(const char *s, const char *t) {
    
    const char *x = s;
    const char *y = t;
    if (strlen(t) > strlen(s)){
        return false;
    }

    while(*y){
        if(*y != *x) {
            return false;
        }
    
        x++;
        y++;
    }

    return true;
}

/**
 * Returns whether or not the 's' string ends with given 't' string.
 * @param   s       String to search within
 * @param   t       String to check for
 * @return          Whether or not 's' ends with 't'
 **/
bool	str_endswith(const char *s, const char *t) {
 
     const char *x = s;
     const char *y = t;
     int j = strlen(s) - strlen(t);
     for(int i = 0; i < j; i++){
         x++;
     }  

     if (strlen(t) > strlen(s)){
            return false;
     }

        while(*y){
            if(*y != *x) {
                return false;                        
                 }
     
            x++;
            y++;           
        }

    return true;
}

/**
 * Removes trailing newline (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	str_chomp(char *s) {
   
    char *x = s;
    int j = strlen(s) - 1;
    for(int i = 0; i < j; i++){
        x++;
    }

    if(*x == '\n'){
        *x = '\0';
    }

    return s;
}

/**
 * Removes whitespace from front and back of string (if present).
 * @param   s       String to modify
 * @return          Pointer to beginning of modified string
 **/
char *	str_strip(char *s) {
 
    char *x = s;
    while(isspace(*s)){
        s++;
    }
   
    int j = strlen(x);
    x = x + j - 1;
    while(isspace(*x)){
        *x = '\0';
        x--;
    }

    return s;
}

/**
 * Reverses a string.
 * @param   s       String to reverse
 * @return          Pointer to beginning of modified string
 **/
char *	str_reverse(char *s) {
   
    char *x = s;
    char *y = s + strlen(s) - 1;

    if (!strlen(s)){
        return s;
    }

    int j = strlen(s) / 2;
    for(int i = 0; i < j; i++){
        char temp = *x;
        *x = *y;
        *y = temp;
        x++;
        y--;
    }
    
    return s;
}

/**
 * Replaces all instances of 'from' in 's' with corresponding values in 'to'.
 * @param   s       String to translate
 * @param   from    String with letter to replace
 * @param   to      String with corresponding replacment values
 * @return          Pointer to beginning of modified string
 **/
char *	str_translate(char *s, char *from, char *to) {
   
    if(!from || !to){
        return s;
    }

    int table[256];
    char *str = s;
    char *first = from;
    char *new = to;
    for(int i = 0; i < 256; i++){
        table[i] = -1;
    }
    
    for(; *from && *new; first++, new++){
        table[(int) *first] = *new;
    }

    for (str = s; *str; str++){
        if(table[(int) *str] != -1)
            *str = (char) table[(int) *str];
    }

    return s;
}

/**
 * Converts given string into an integer.
 * @param   s       String to convert
 * @param   base    Integer base
 * @return          Converted integer value
 **/
int	str_to_int(const char *s, int base) {
    
    int sum = 0;
    int var = 1;
    int length = strlen(s);
    const char* c = s + strlen(s) -1;
    
    for (int i = 0; i < length; i++, --c, var*=base){
        char uppercase = toupper(*c);
        if(uppercase - 55 >= 10){
            sum += (uppercase - 55) * var;
        }
        
        else{
            sum += (uppercase - 48) * var;
        }
    }
    
    return sum;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
