#include <stdio.h>
#include <string.h>

#define ONE_LINE 80
#define PAST 0
#define PRESENT 1
#define JIFFIES_NUM 4

enum jiffy{USER, USER_NICE, SYSTEM, IDLE} jiffy_enum;

int main(void){
    char loadDataBuf[ONE_LINE] = {0};
    char cpuId[4] = {0};
	  
    int jiffies[2][JIFFIES_NUM] = {0}, totalJiffies;
    int diffJiffies[JIFFIES_NUM];
    int idx;
    float cpuusage;

    FILE* statFile;

    while(1){
	statFile = fopen("/proc/stat", "r");
	fscanf(statFile, "%s %d %d %d %d", 
	    cpuId, &jiffies[PRESENT][USER], &jiffies[PRESENT][USER_NICE],
	    &jiffies[PRESENT][SYSTEM], &jiffies[PRESENT][IDLE]);
			        
    for(idx = 0, totalJiffies = 0; idx < JIFFIES_NUM; ++idx){
	diffJiffies[idx] = jiffies[PRESENT][idx] - jiffies[PAST][idx];
	totalJiffies = totalJiffies + diffJiffies[idx];
    }
    cpuusage = 100.0*(1.0-(diffJiffies[IDLE] / (double)totalJiffies));				      
    printf("Cpu usage : %f%%\n",cpuusage);
//	100.0*(1.0-(diffJiffies[IDLE] / (double)totalJiffies)));
          
    memcpy(jiffies[PAST], jiffies[PRESENT], sizeof(int)*JIFFIES_NUM);
    fclose(statFile);
					          
    sleep(1);
    }
    return cpuusage; 
}
