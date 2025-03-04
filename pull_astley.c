#include <stdio.h>
#include <stdlib.h>
int* bin(char msg[])
{
    int* b=malloc(30*sizeof(int));
    for (int i=0;i<30;i+=1)
    {
        b[i]=0;
    }
    for (int i=0;i<5;i+=1)
    {
        if (msg[i]=='\0') break;
        int c=(int)msg[i]-(int)'a'+1;
        for (int n=0;n<5;n+=1)
        {
            b[5*i+n]=c%2;
            c-=c%2;
            c/=2;
        }


    }
    return b;
}
int main()
{
    char msg[5];
    scanf("%s",msg);
    int* b=bin(msg);
    for (int i=0;i<24;i+=1)
    {
        printf("%d",b[i]);
    }
    free(b);
    return 0;
}