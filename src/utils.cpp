#include "utils.h"


/*
** reverse string in place 
*/
void reverse(char *s) {
char *j;
int c;
 
  j = s + strlen(s) - 1;
  while(s < j) {
    c = *s;
    *s++ = *j;
    *j-- = c;
  }
}

char getNumber(int n){
  if(n>9) {
    return n-10+'a';
  } else {
    return n+'0';
  }
}
 void itoa(int n, char * s, int base_n)
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = getNumber(n % base_n);   /* get next digit */
     } while ((n /= base_n) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }