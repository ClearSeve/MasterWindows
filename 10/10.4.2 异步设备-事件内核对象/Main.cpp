#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // ���ļ�
    HANDLE hFile = CreateFile(L"10.4.2",GENERIC_READ|GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_FLAG_OVERLAPPED,NULL);
    if( hFile == INVALID_HANDLE_VALUE )
    {
        ShowErrorInfo();
        return(-1);
    }
    
    /*���¼�*/
    // д���豸
    char szBuf[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber; // д�������
    OVERLAPPED overlapped = {0}; // �첽�ṹ
    overlapped.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf,20,&dwWriteNumber,&overlapped);
    // 
    WaitForSingleObject(overlapped.hEvent,INFINITE);
    cout<<"I/O�������"<<endl;

    /*���¼�*/
    // д��2
    char szBuf1[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber1; // д�������
    OVERLAPPED overlapped1 = {0}; // �첽�ṹ
    overlapped1.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf1,20,&dwWriteNumber1,&overlapped1);
    // д��2
    char szBuf2[MAX_PATH]={0}; // buffer
    DWORD dwWriteNumber2; // д�������
    OVERLAPPED overlapped2 = {0}; // �첽�ṹ
    overlapped2.hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    WriteFile(hFile,szBuf2,20,&dwWriteNumber2,&overlapped2);

    // �����¼��ں˶���
    HANDLE hEvent[] = {overlapped1.hEvent,overlapped2.hEvent};
    // �ȴ�
    DWORD nWait = WaitForMultipleObjects(2,hEvent,FALSE,INFINITE);
        switch(nWait-WAIT_OBJECT_0)
    {
    case 0: // 1
        break;
    case 1: // 2
        break;
    }

    // �ر��ļ�
    CloseHandle(hFile);

    return 0;
}
