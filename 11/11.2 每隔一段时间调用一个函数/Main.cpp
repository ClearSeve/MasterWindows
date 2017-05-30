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
    // ����ʱ���̳߳�
    PTP_TIMER ThreadpoolTimer = CreateThreadpoolTimer(TimerCallback,NULL,NULL);
    
    // ����ʱ��
    // ����ʱ��
    SYSTEMTIME st;
    // ���汾��ʱ��,��ת��ΪUTC��ʱ��
    FILETIME ftLocal, ftUTC;
    // ����ת���ȴ���ʱ����ʱ��
    LARGE_INTEGER liUTC; 

    // ����ʱ��
    st.wYear         = 2018; // ��
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

    // ����ʱ���̳߳�
    SetThreadpoolTimer(ThreadpoolTimer,&ftUTC,10000,10);
    
    // �Ⱥ�ʱ���̳߳�
    WaitForThreadpoolTimerCallbacks(ThreadpoolTimer,TRUE);
    //system("pause");
    // �ر�ʱ���̳߳�
    CloseThreadpoolTimer(ThreadpoolTimer);
    return 0;
}
