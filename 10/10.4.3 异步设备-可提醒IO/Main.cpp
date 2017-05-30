#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"
VOID CALLBACK FileIOCompletionRoutine(
                                       DWORD dwErrorCode,
                                       DWORD dwNumberOfBytesTransfered,
                                       LPOVERLAPPED lpOverlapped)
{
    cout<<"I/O设备完成"<<endl;
}


int main()
{
    // 打开文件
    HANDLE hFile = CreateFile(L"10.4.3",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }

    
    char szBuf[MAX_PATH] = {0};
    // 异步用的结构体
    OVERLAPPED Overlapped = {0};
    // 写入文件
    WriteFileEx(hFile,szBuf,10,&Overlapped,FileIOCompletionRoutine);
    while(1)
    {
        SleepEx(1000,TRUE); // 响应APC
    }

    // 关闭文件
    CloseHandle(hFile);
    return 0;
}
