#include "time_module.h"
#include "stdio.h"

/* sudo apt-get install ntp */

int main()  
{  
    tm* time_cur;
    tm* time_gm;
    Time* timeIns = new Time();
    timeIns->GetSecond();
    time_cur = timeIns->GetLocal();
    printf("time_cur is:%s",asctime(time_cur));
    time_gm = timeIns->GetGmtime();
    printf("time_gm is:%s",asctime(time_gm));
    timeIns->TimeSyncStart();
    timeIns->TimeSyncStop();
    return 0;  
}  
