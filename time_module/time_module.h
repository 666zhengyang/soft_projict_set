#include <time.h>  
#include <sys/time.h> 
#include <stdlib.h>

class Time {
public:
    time_t GetSecond(void);
    tm* GetLocal(void);
    tm* GetGmtime(void);
    void TimeSyncStart();
    void TimeSyncStop();

private:
    time_t _second;
    tm* _time_loacl;
    tm* _time_gm;
};
