#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

VOID CALLBACK IoCompletionCallback( PTP_CALLBACK_INSTANCE Instance,
                                    PVOID Context,
                                    PVOID Overlapped,
                                    ULONG IoResult,
                                    ULONG_PTR NumberOfBytesTransferred,
                                    PTP_IO Io)
{
    cout<<"IoCompletionCallback"<<endl;
}



int main()
{
    // 打开文件
    HANDLE hFile = CreateFile(L"10.4.4",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);

    // 创建IO线程池
    PTP_IO ThreadpoolIo = CreateThreadpoolIo(hFile,IoCompletionCallback,NULL,NULL);
    
    // IO操作
    char szText[MAX_PATH] = {0};
    ZeroMemory(szText,MAX_PATH);
    DWORD dwWrite = 0;
    OVERLAPPED overapped = {0};
    WriteFile(hFile,szText,50,&dwWrite,&overapped);
    // 设置到进程池
    StartThreadpoolIo(ThreadpoolIo);
    
    system("pause");

    // 关闭IO线程池
    CancelThreadpoolIo(ThreadpoolIo);
    
    // 关闭文件
    CloseHandle(hFile);
    return 0;
}
