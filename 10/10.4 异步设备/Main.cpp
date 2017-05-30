#include <Windows.h>

#include <iostream>
using namespace std;

OVERLAPPED g_over={0};
OVERLAPPED g_over2={0};
/*
  �ȴ��첽I/O����Ӧ
    ��һ�ַ�ʽ: WaitForSingleObject
    �ڶ��ַ�ʽ: Event�ں˶���
    �����ַ�ʽ: WriteFileEx
*/

HANDLE CreateNewCompletionPort(DWORD dwNumberOfConcurrentThreads)
{
    return (CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,dwNumberOfConcurrentThreads));
}

// 
BOOL AssociateDeviceWithCompletionPort( HANDLE hCompletionPort, HANDLE hDevice, DWORD dwCompletionKey )
{
    HANDLE h = CreateIoCompletionPort(hDevice,hCompletionPort,dwCompletionKey,0);
    return (h == hCompletionPort);
}

int main()
{   
    // ���첽��ʽ���ļ�
    HANDLE hFile = CreateFile(L"NewFIle.txt",GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);
    // ȡ�������ļ�����
    //SetFileCompletionNotificationModes(hFile,FILE_SKIP_SET_EVENT_ON_HANDLE);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        LPTSTR lpMsgBuf = NULL;
        DWORD nErrno = GetLastError();//��ȡ������Ϣ
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |FORMAT_MESSAGE_FROM_SYSTEM |FORMAT_MESSAGE_IGNORE_INSERTS,NULL,nErrno,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,0,NULL);
        //HANDLE hAndle = GetStdHandle( STD_OUTPUT_HANDLE );// ��ȡ���
        WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), lpMsgBuf, wcslen(lpMsgBuf),NULL,NULL); // �������
        LocalFree(lpMsgBuf);
        
    }
    char szBuf[MAX_PATH] ={0};
    DWORD dwWrite=0;
    sprintf_s(szBuf,"Hello World %d!\r\n",0);


    // �����̳߳�, ��������������CPU����*2
    HANDLE hCompletionPort = CreateNewCompletionPort(0); 
    // ��Ӿ�����̳߳�
    BOOL b = AssociateDeviceWithCompletionPort(hCompletionPort,hFile,1);
    if(b == TRUE)
        cout<<"��ӳɹ�"<<endl;
    else
        cout<<"���ʧ��"<<endl;
    
    
    // д������
    g_over.Offset = 10;
    WriteFile(hFile,szBuf,20,NULL,&g_over);

    g_over2.Offset = 0;
    //WriteFileEx(hFile,szBuf,10,&g_over2,FileIOCompletionRoutine2);
    
    
    
    while(1)
    {
        DWORD dwNumBytes;
        ULONG_PTR CompleionKey;
        OVERLAPPED* pOverlapped;

        GetQueuedCompletionStatus(hCompletionPort,&dwNumBytes,&CompleionKey,&pOverlapped,INFINITE);
        cout<<"NumBytes:"<<dwNumBytes<<"CompleionKey:"<<CompleionKey<<endl;
        SleepEx(1000,FALSE);
    }
    CloseHandle(hFile);
    


    system("pause");
    return 0;
}
