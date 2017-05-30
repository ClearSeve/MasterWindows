#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
using namespace std;

#include "../../MyFunction.h"

// 初一的你 是多么可爱
void Function1()
{

    // 分配内存
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024*1024,MEM_COMMIT,PAGE_READWRITE);

    strcpy(pszBuf,"Hello");
    cout<<pszBuf<<endl;
    getch();
    
    // 释放内存
    VirtualFree(pszBuf,1024*1024*1024,MEM_RELEASE);
}

void Function2()
{
    // 预定内存
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024*1024,MEM_RESERVE,PAGE_READWRITE);
    
    // 分配内存
    VirtualAlloc(pszBuf,1024*1024*1024,MEM_COMMIT,PAGE_READWRITE);
    strcpy(pszBuf,"Hello");
    
    // 释放内存
    VirtualFree(pszBuf,1024*1024*1024,MEM_RELEASE); 
}

// 获取虚拟内存信息
void Global() 
{
    // 获取内存信息
    MEMORYSTATUS status={0};
    status.dwLength = sizeof(status);
    GlobalMemoryStatus(&status);

    cout<<"总共物理内存:"<<status.dwTotalPhys<<endl;
    cout<<"可用物理内存:"<<status.dwAvailPhys<<endl;
    cout<<"总共内存页:"<<status.dwTotalPageFile<<endl;
    cout<<"可用内存页:"<<status.dwAvailPageFile<<endl;
    cout<<"总共虚拟内存:"<<status.dwTotalVirtual<<endl;
    cout<<"可用虚拟内存:"<<status.dwAvailVirtual<<endl;
    cout<<"使用率:"<<status.dwMemoryLoad<<"%"<<endl;
}

int main()
{
    Global();
    return 0;
}
