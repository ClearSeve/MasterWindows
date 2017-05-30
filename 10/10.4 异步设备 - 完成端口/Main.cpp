#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

// 创建线程池
HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads)
{
    return (CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,dwNumberOfConcurrentThreads));
}

// 添加设备到线程池
BOOL AssociateDeviceWithCompletionPort( HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey )
{
    HANDLE h = CreateIoCompletionPort(hDevice,hCompletionPort,dwCompletionKey,0);
    return (h == hCompletionPort);
}

int main()
{
    // 打开文件
    HANDLE hFile = CreateFile(L"10.4.4",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }
    
    // 创建线程池, 数量根据主机的CPU数量*2
    HANDLE hCompletionPort = CreateNewCompletionPort(0); 
    // 添加句柄到线程池
    AssociateDeviceWithCompletionPort(hCompletionPort,hFile,1);
    
    // 发起I/O操作
    char szBuf[MAX_PATH] = "王世钰考上理想的大学, 这个生日一定过的很美好吧, 加油,我很期待与你相遇的一天, 相遇并非偶然, 机会由我创造!";
    OVERLAPPED OverFile1={0};
    OverFile1.Offset = 0;
    WriteFile(hFile,szBuf,20,NULL,&OverFile1);
    // 等待I/O触发
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
