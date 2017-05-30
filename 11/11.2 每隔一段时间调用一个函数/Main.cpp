#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"


VOID CALLBACK TimerCallback( PTP_CALLBACK_INSTANCE Instance,
                             PVOID Context,
                             PTP_TIMER Timer)
{
    cout<<"TimerCallback"<<endl;
}


int main()
{
    // 创建时间线程池
    PTP_TIMER ThreadpoolTimer = CreateThreadpoolTimer(TimerCallback,NULL,NULL);
    
    // 构造时间
    // 保存时间
    SYSTEMTIME st;
    // 保存本地时间,和转换为UTC的时间
    FILETIME ftLocal, ftUTC;
    // 保存转给等待计时器的时间
    LARGE_INTEGER liUTC; 

    // 设置时间
    st.wYear         = 2018; // 年
    st.wMonth        = 5;    // 月
    st.wDay          = 8;    // 日
    st.wHour         = 10;   // 时
    st.wMinute       = 59;   // 分
    st.wSecond       = 40;   // 秒
    st.wMilliseconds = 0;    // 毫秒

    // 将SYSTEMTIME结构的时间转换为FILETIME结构的时间
    SystemTimeToFileTime(&st,&ftLocal);
    // 将LOCAL时区转换为UTC时区
    LocalFileTimeToFileTime(&ftLocal,&ftUTC);
    // 将FILETIME结构体数据成员,复制到LARGE_INTEGER结构体数据成员.
    liUTC.LowPart = ftUTC.dwLowDateTime;
    liUTC.HighPart = ftUTC.dwHighDateTime;

    // 设置时间线程池
    SetThreadpoolTimer(ThreadpoolTimer,&ftUTC,10000,10);
    
    // 等候时间线程池
    WaitForThreadpoolTimerCallbacks(ThreadpoolTimer,TRUE);
    //system("pause");
    // 关闭时间线程池
    CloseThreadpoolTimer(ThreadpoolTimer);
    return 0;
}
