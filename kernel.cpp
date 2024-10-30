#include <cstdio>

int main()
{
    char c = 'x';

//    printf("Hello World!\nI am printf()!\naaa\n%%\nThis should print F9A12058: %X\n%x\n---", 0xF9A12058, 0xA1998);
    // printf("%d\n%i\n%u", 123456, -1337, 1984);
    printf("%p : %c\n%o", &c, c, 123123);
}
