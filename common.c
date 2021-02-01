#include "common.h"



void reverse(char s[])
 {
     unsigned int i, j;
     char c;
 
     for (i = 0, j = strlen(s) - 1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
 
 
 
 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
 
 
uint16_t extract_int(char* RXs)
{
       uint16_t i, val, n;
        for(i = val =0, n = (uint16_t)strlen(RXs);i<n;i++){
                if(RXs[i] >='0' && RXs[i]<='9'){
                        val = val * 10 + RXs[i] - '0';
                }
        }
				if(val == 0){
					return 0;
				}
				return val;
}


