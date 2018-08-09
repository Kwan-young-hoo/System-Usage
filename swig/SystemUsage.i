%module SystemUsage
%{
extern int cpu_usage(void);
extern int memory_info(void);
extern void main();
extern char loadDataBuf[80];
extern char cpu_ID[4];
extern int jiffies[2][4];
extern int totalJiffies;
extern int diff_Jiffies[4];
extern int idx;
extern double cpu_usage_data;
extern char memory_total_name[9];
extern char memory_free_name[9];
extern char garv[3];
extern int memory_total;
extern int memory_free;
extern int memory_used;
%}
extern int cpu_usage(void);
extern int memory_info(void);
extern void main();
extern char loadDataBuf[80];
extern char cpu_ID[4];
extern int jiffies[2][4];
extern int totalJiffies;
extern int diff_Jiffies[4];
extern int idx;
extern double cpu_usage_data;
extern char memory_total_name[9];
extern char memory_free_name[9];
extern char garv[3];
extern int memory_total;
extern int memory_free;
extern int memory_used;

#define ONE_LINE 80
#define PAST 0
#define PRESENT 1
#define JIFFIES_NUM 4
