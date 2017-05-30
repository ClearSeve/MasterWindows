#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // 创建文件
    HANDLE hFile = CreateFile(_T("e:\\Demo.DATA"),GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    // 创建文件映射
    HANDLE hFileMap = CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,1024*1024,NULL);
    
    // 映射地址
    char* pszBuf =(char*) MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,1024*1024);
    
    strcpy(pszBuf,"Hello World!");
    printf(pszBuf);

    // 卸载地址
    UnmapViewOfFile(pszBuf);

    // 关闭文件映射
    CloseHandle(hFileMap);
    // 关闭文件
    CloseHandle(hFile);
    return 0;
}
