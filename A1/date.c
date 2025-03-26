#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(){
    time_t now = time(NULL);
    char *str_now = ctime(&now);
    printf("%s\n",str_now);
    return 0;
}