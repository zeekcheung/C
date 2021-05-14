#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu(); // 菜单

int main(void)
{
    menu();
}

void menu()
{
    printf("\n-------------------------------\n");
    printf("#                             #\n");
    printf("#      I: Initialization      #\n");
    printf("#      E: Encoding            #\n");
    printf("#      D: Decoding            #\n");
    printf("#      P: Printing            #\n");
    printf("#      T: Tree Printing       #\n");
    printf("#                             #");
    printf("\n-------------------------------\n");
}