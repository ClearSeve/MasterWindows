#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

// �����̳߳�
HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads)
{
    return (CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,dwNumberOfConcurrentThreads));
}

// ����豸���̳߳�
BOOL AssociateDeviceWithCompletionPort( HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey )
{
    HANDLE h = CreateIoCompletionPort(hDevice,hCompletionPort,dwCompletionKey,0);
    return (h == hCompletionPort);
}

int main()
{
    // ���ļ�
    HANDLE hFile = CreateFile(L"10.4.4",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }
    
    // �����̳߳�, ��������������CPU����*2
    HANDLE hCompletionPort = CreateNewCompletionPort(0); 
    // ��Ӿ�����̳߳�
    AssociateDeviceWithCompletionPort(hCompletionPort,hFile,1);
    
    // ����I/O����
    char szBuf[MAX_PATH] = "�����ڿ�������Ĵ�ѧ, �������һ�����ĺ����ð�, ����,�Һ��ڴ�����������һ��, ��������żȻ, �������Ҵ���!";
    OVERLAPPED OverFile1={0};
    OverFile1.Offset = 0;
    WriteFile(hFile,szBuf,20,NULL,&OverFile1);
    // �ȴ�I/O����
    while(1)
    {
        DWORD dwNumBytes;
        ULONG_PTR CompleionKey;
        OVERLAPPED* pOverlapped;

        GetQueuedCompletionStatus(hCompletionPort,&dwNumBytes,&CompleionKey,&pOverlapped,INFINITE);
        cout<<"NumBytes:"<<dwNumBytes<<"CompleionKey:"<<CompleionKey<<endl;
        SleepEx(1000,FALSE);
    }

    CloseHandle(hFile);
    return 0;
}
