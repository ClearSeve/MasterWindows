#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // 打开文件
    HANDLE hFile = CreateFile(L"10.4.2",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }
    
    /*单事件*/
    // 写入设备
    char szBuf[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber; // 写入的数量
    OVERLAPPED overlapped = {0}; // 异步结构
    overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf,20,&dwWriteNumber,&overlapped);
    // 
    WaitForSingleObject(overlapped.hEvent,INFINITE);
    cout<<"I/O处理完成"<<endl;

    /*多事件*/
    // 写入2
    char szBuf1[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber1; // 写入的数量
    OVERLAPPED overlapped1 = {0}; // 异步结构
    overlapped1.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf1,20,&dwWriteNumber1,&overlapped1);
    // 写入2
    char szBuf2[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber2; // 写入的数量
    OVERLAPPED overlapped2 = {0}; // 异步结构
    overlapped2.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf2,20,&dwWriteNumber2,&overlapped2);

    // 设置事件内核对象
    HANDLE hEvent[] = {overlapped1.hEvent,overlapped2.hEvent};
    // 等待
    DWORD nWait = WaitForMultipleObjects(2,hEvent,FALSE,INFINITE);
        switch(nWait-WAIT_OBJECT_0)
    {
    case 0: // 1
        break;
    case 1: // 2
        break;
    }

    // 关闭文件
    CloseHandle(hFile);

    return 0;
}
