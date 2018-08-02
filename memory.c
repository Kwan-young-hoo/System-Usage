#include <stdio.h>

int main(void){
    char memtotal[9] = {0};
    char memfree[9] = {0};
    char garv[3] = {0};
    int total;
    int free;
    int used;

    FILE  *fp = fopen("/proc/meminfo", "r");

    fscanf(fp, "%s %d %s %s %d", memtotal, &total, garv, memfree, &free);
    used = total - free;
    printf("%s %d\n%s %d\nMemUsed: %d\n", memtotal, total, memfree, free, used);

    fclose(fp);
    return total, free, used;
}




