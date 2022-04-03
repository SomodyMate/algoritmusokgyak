#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void elso();
void masodik();
void harmadik();

int main()
{
    //elso();
    //masodik();
    //harmadik();
}

void elso(){
    printf("Hello World!\n");
    return;
}

void masodik(){
    int a;
    double b;
    char c[100];
    printf("Adjon meg egy egeszet!\n");
    scanf("%d", &a);
    printf("Adjon meg egy valost!\n");
    scanf("%lf", &b);
    printf("Adjon meg egy stringet!\n");
    scanf("%s", c);
    printf("A megadott ertekek:\n");
    printf("%d\n", a);
    printf("%lf\n", b);
    printf("%s\n", c);
}

void harmadik(){
    int length;
    printf("Hany iteracio legyen?\n");
    scanf("%d", &length);
    for (int i = 0; i < length; i++)
    {
        printf("%d. iteracional jarunk\n", (i+1));
    }
}

void negyedik(){
    
}