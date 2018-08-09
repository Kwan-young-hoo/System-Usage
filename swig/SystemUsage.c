#include <stdio.h>
#include <string.h>

#define ONE_LINE 80
#define PAST 0
#define PRESENT 1
#define JIFFIES_NUM 4

int cpu_usage(void);
int memory_info(void);

void main(){
    memory_info();
    cpu_usage();

}

enum jiffy{USER, USER_NICE, SYSTEM, IDLE} jiffy_enum;

int cpu_usage(void){
    char loadDataBuf[ONE_LINE] = {0};
    char cpu_ID[4] = {0};

    int jiffies[2][JIFFIES_NUM] = {0}, totalJiffies;
    int diff_Jiffies[JIFFIES_NUM];
    int idx;
    double cpu_usage_data;

   // FILE* statFile; // = fopen("/proc/stat", "r");

    while(1){
	FILE* statFile = fopen("/proc/stat", "r");
	fscanf(statFile, "%s %d %d %d %d",
	    cpu_ID, &jiffies[PRESENT][USER], &jiffies[PRESENT][USER_NICE], &jiffies[PRESENT][SYSTEM], &jiffies[PRESENT][IDLE]);

    for(idx = 0, totalJiffies = 0; idx < JIFFIES_NUM; ++idx){
    diff_Jiffies[idx] = jiffies[PRESENT][idx] - jiffies[PAST][idx];
    totalJiffies = totalJiffies + diff_Jiffies[idx];
    }
    cpu_usage_data = 100.0*(1.0-(diff_Jiffies[IDLE] / (double)totalJiffies));
    printf("Cpu usage : %f%%\n",cpu_usage_data);

    memcpy(jiffies[PAST], jiffies[PRESENT], sizeof(int)*JIFFIES_NUM);
    fclose(statFile);

    sleep(1);
    }
    return cpu_usage_data;
}

int memory_info(void){
    char memory_total_name[9] = {0};
    char memory_free_name[9] = {0};
    char garv[3] = {0};
    int memory_total;
    int memory_free;
    int memory_used;

    FILE* memory_file = fopen("/proc/meminfo", "r");
//    memFile = fopen("/proc/meminfo", "r");

    fscanf(memory_file, "%s %d %s %s %d", memory_total_name, &memory_total, garv, memory_free_name, &memory_free);
    memory_used = memory_total - memory_free;

    printf("%s %d kB\n",memory_total_name, memory_total);
    printf("%s %d kB\n",memory_free_name, memory_free);
    printf("MemUsed: %d kB\n",memory_used);
//  printf("%s %d\n%s %d\nMemUsed: %d\n", memtotal, total, memfree, free, used);

    fclose(memory_file);
    return memory_total, memory_free, memory_used;
}