#include "chassis_port.h"

using namespace joyrobot;

int main()
{
    int baud_rate = 115200;
    const char* dev =  "/dev/ttyUSB0";
    printf("hello joylifrobot\n");
    ChassisPort* chassisPortIns = new ChassisPort(dev, baud_rate);
    if (NULL == chassisPortIns) {
        printf("chassisPortIns create failed");
        return -1;
    }

    printf("chassisPortIns create success, and the ptr is %p\n", &chassisPortIns);

    int i = 3;
    printf("i++ is: %d\n", i++);
    if(1) {
        chassisPortIns->Upstation_Initialized();
        chassisPortIns->Feed_Plate_Watchdog();
        // chassisPortIns->Set_Plate_Sleep();
        // chassisPortIns->Set_Plate_Wake();
        // chassisPortIns->Set_Plate_Run_VA(45,45);
       // chassisPortIns->start(chassisPortIns);
       // chassisPortIns->stop();
    }
    // chassisPortIns->Set_Plate_Mode(1);
    // delete destData;
    delete chassisPortIns;
    return 0;
}