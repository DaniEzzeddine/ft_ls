#include <getopt.h>
#include <stdio.h>
extern int optind;


int main(int argc, char **argv)
{
    int i;
    char ch;

    ch = getopt(argc, argv, "qwe");
    i = (int)ch;
    printf("%d\n", optind);
    return (0);
}