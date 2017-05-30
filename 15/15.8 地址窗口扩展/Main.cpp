#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // 预定内存
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024,MEM_RESERVE|MEM_PHYSICAL,PAGE_READWRITE);

    // 分配内存
    int nValue[100] = {0};
    AllocateUserPhysicalPages(GetCurrentProcess(),1,nValue);
    // 释放分配

    // 释放预定
    VirtualFree(pszBuf,0,MEM_RESET);

    return 0;
}
