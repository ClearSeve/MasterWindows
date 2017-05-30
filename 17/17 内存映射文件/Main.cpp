#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // �����ļ�
    HANDLE hFile = CreateFile(_T("e:\\Demo.DATA"),GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    // �����ļ�ӳ��
    HANDLE hFileMap = CreateFileMapping(hFile,NULL,PAGE_READWRITE,0,1024*1024,NULL);
    
    // ӳ���ַ
    char* pszBuf =(char*) MapViewOfFile(hFileMap,FILE_MAP_ALL_ACCESS,0,0,1024*1024);
    
    strcpy(pszBuf,"Hello World!");
    printf(pszBuf);

    // ж�ص�ַ
    UnmapViewOfFile(pszBuf);

    // �ر��ļ�ӳ��
    CloseHandle(hFileMap);
    // �ر��ļ�
    CloseHandle(hFile);
    return 0;
}
