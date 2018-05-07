#include<stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

bool is_anagram(const char *s1, const char *s2) {
    int max = 0;
 
    for (const char *c = s1; *c; c++) { 
	if (*c > max) max = *c; 
	}

    for (const char *c = s2; *c; c++) { if (*c > max) max = *c; }
 
    int *counts1 = calloc(max+1, sizeof(int)), *counts2 = calloc(max+1, sizeof(int));
 
    for (const char *c = s1; *c; c++) { counts1[(int)*c]++; }
    for (const char *c = s2; *c; c++) { counts2[(int)*c]++; }
 
    for (int i = 0; i <= max; i++) if (counts1[i] != counts2[i]) { 
	free(counts1); free(counts2);
	return false; }
   
	free(counts1); free(counts2);
   return true;
}

int main()
{
    const char * a = "cinema";
    const char * c = "iceman";
    bool b = is_anagram(a, c);
    printf("%d\n", b);
    return 0;
}

