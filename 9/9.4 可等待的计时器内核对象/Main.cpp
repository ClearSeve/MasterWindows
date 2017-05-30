#include <Windows.h>
#include <iostream>
using namespace std;
VOID CALLBACK TimerAPCProc(LPVOID lpArgToCompletionRoutine,
                           DWORD dwTimerLowValue,
                           DWORD dwTimerHighValue)
{
    if( (int)lpArgToCompletionRoutine == 233)
    {
        cout<<"lpArgToCompletionRoutine"<<endl;
    }
    
}


int main( )
{
    // 创建可等待计时器内核对象
    HANDLE hWaitableTimer = CreateWaitableTimer(NULL,FALSE,NULL);

    // 保存时间
    SYSTEMTIME st;
    // 保存本地时间,和转换为UTC的时间
    FILETIME ftLocal, ftUTC;
    // 保存转给等待计时器的时间
    LARGE_INTEGER liUTC; 

    // 设置时间
    st.wYear         = 2017; // 年
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


    // 设置定时器
   
    
    
    
    
    while(1)
    {
        SetWaitableTimer(hWaitableTimer,&liUTC,5000,TimerAPCProc,(LPVOID)233,FALSE);
        //SetWaitableTimer(hWaitableTimer,&liUTC,5000,NULL,NULL,FALSE);
        DWORD dw = WaitForSingleObject(hWaitableTimer,INFINITE);
        SleepEx(INFINITE,TRUE);
    }
    

    // 关闭等待计时器内核对象
    CloseHandle(hWaitableTimer);

    return 0;
}
