#include <stdlib.h>
#include <stdio.h>
int main()
{
char s[4];
scanf("%s",s);
int size=(int)s[0];
size+=1;
char* string=malloc(size*sizeof(char));
scanf("%s\n",string);
char* string2=malloc(size*sizeof(char));
size-=1;
int i2=0;
int lastdigit=9;
for (int i=0;i<size;i+=1)
{
    if(!((int)string[i]>47 && (int)string[i]<58 && (int)string[i]<lastdigit+48))
    {
        string2[i2]=string[i];
        i2+=1;
    }
}
string2[i2]='\0';
printf(string2);
}