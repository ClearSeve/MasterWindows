#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"
VOID CALLBACK FileIOCompletionRoutine(
                                       DWORD dwErrorCode,
                                       DWORD dwNumberOfBytesTransfered,
                                       LPOVERLAPPED lpOverlapped)
{
    cout<<"I/O�豸���"<<endl;
}


int main()
{
    // ���ļ�
    HANDLE hFile = CreateFile(L"10.4.3",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }

    
    char szBuf[MAX_PATH] = {0};
    // �첽�õĽṹ��
    OVERLAPPED Overlapped = {0};
    // д���ļ�
    WriteFileEx(hFile,szBuf,10,&Overlapped,FileIOCompletionRoutine);
    while(1)
    {
        SleepEx(1000,TRUE); // ��ӦAPC
    }

    // �ر��ļ�
    CloseHandle(hFile);
    return 0;
}
