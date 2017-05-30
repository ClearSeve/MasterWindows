#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{   
    // ���ļ�
    HANDLE hFile = CreateFile(L"10.4.1",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }

    // д���ļ�
    char szBuf[MAX_PATH] = {0};
    DWORD dwWriteNumber  =  0 ;
    OVERLAPPED overapped = {0};
    WriteFile(hFile,szBuf,100,&dwWriteNumber,&overapped);
    // �ȴ��������
    WaitForSingleObject(hFile,INFINITE);
    
    // �ر��ļ�
    CloseHandle(hFile);
 
    return 0;
}
