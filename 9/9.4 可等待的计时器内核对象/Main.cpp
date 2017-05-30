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
    // �����ɵȴ���ʱ���ں˶���
    HANDLE hWaitableTimer = CreateWaitableTimer(NULL,FALSE,NULL);

    // ����ʱ��
    SYSTEMTIME st;
    // ���汾��ʱ��,��ת��ΪUTC��ʱ��
    FILETIME ftLocal, ftUTC;
    // ����ת���ȴ���ʱ����ʱ��
    LARGE_INTEGER liUTC; 

    // ����ʱ��
    st.wYear         = 2017; // ��
    st.wMonth        = 5;    // ��
    st.wDay          = 8;    // ��
    st.wHour         = 10;   // ʱ
    st.wMinute       = 59;   // ��
    st.wSecond       = 40;   // ��
    st.wMilliseconds = 0;    // ����

    // ��SYSTEMTIME�ṹ��ʱ��ת��ΪFILETIME�ṹ��ʱ��
    SystemTimeToFileTime(&st,&ftLocal);
    // ��LOCALʱ��ת��ΪUTCʱ��
    LocalFileTimeToFileTime(&ftLocal,&ftUTC);
    // ��FILETIME�ṹ�����ݳ�Ա,���Ƶ�LARGE_INTEGER�ṹ�����ݳ�Ա.
    liUTC.LowPart = ftUTC.dwLowDateTime;
    liUTC.HighPart = ftUTC.dwHighDateTime;


    // ���ö�ʱ��
   
    
    
    
    
    while(1)
    {
        SetWaitableTimer(hWaitableTimer,&liUTC,5000,TimerAPCProc,(LPVOID)233,FALSE);
        //SetWaitableTimer(hWaitableTimer,&liUTC,5000,NULL,NULL,FALSE);
        DWORD dw = WaitForSingleObject(hWaitableTimer,INFINITE);
        SleepEx(INFINITE,TRUE);
    }
    

    // �رյȴ���ʱ���ں˶���
    CloseHandle(hWaitableTimer);

    return 0;
}
