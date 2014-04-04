#include <string.h>

int main(int argc, char *argv[]) 
{
    void *ptr = NULL;
    strcpy(ptr, "segfault");
    return 0;
}
