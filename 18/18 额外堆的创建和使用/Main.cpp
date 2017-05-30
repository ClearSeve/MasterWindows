#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    malloc(1000);
    // 创建堆
    HANDLE hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS,1024*1024,1024*1024*1024 /*为0自动扩展*/);
    
    // 申请内存
    char* pszBuf = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,MAX_PATH);

    // 使用内存
    strcpy(pszBuf,"Hello World!");
    cout<<pszBuf<<endl;
    
    // 释放内存
    HeapFree(hHeap,0,pszBuf);
    
    // 释放堆
    HeapDestroy(hHeap);

    // GetProcessHeap(); // 获取进程默认堆的句柄
    // GetProcessHeaps(); // 获取进程所有堆的句柄
    return 0; 
}
// 2