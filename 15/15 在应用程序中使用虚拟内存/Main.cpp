#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <conio.h>
using namespace std;

#include "../../MyFunction.h"

// ��һ���� �Ƕ�ô�ɰ�
void Function1()
{

    // �����ڴ�
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024*1024,MEM_COMMIT,PAGE_READWRITE);

    strcpy(pszBuf,"Hello");
    cout<<pszBuf<<endl;
    getch();
    
    // �ͷ��ڴ�
    VirtualFree(pszBuf,1024*1024*1024,MEM_RELEASE);
}

void Function2()
{
    // Ԥ���ڴ�
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024*1024,MEM_RESERVE,PAGE_READWRITE);
    
    // �����ڴ�
    VirtualAlloc(pszBuf,1024*1024*1024,MEM_COMMIT,PAGE_READWRITE);
    strcpy(pszBuf,"Hello");
    
    // �ͷ��ڴ�
    VirtualFree(pszBuf,1024*1024*1024,MEM_RELEASE); 
}

// ��ȡ�����ڴ���Ϣ
void Global() 
{
    // ��ȡ�ڴ���Ϣ
    MEMORYSTATUS status={0};
    status.dwLength = sizeof(status);
    GlobalMemoryStatus(&status);

    cout<<"�ܹ������ڴ�:"<<status.dwTotalPhys<<endl;
    cout<<"���������ڴ�:"<<status.dwAvailPhys<<endl;
    cout<<"�ܹ��ڴ�ҳ:"<<status.dwTotalPageFile<<endl;
    cout<<"�����ڴ�ҳ:"<<status.dwAvailPageFile<<endl;
    cout<<"�ܹ������ڴ�:"<<status.dwTotalVirtual<<endl;
    cout<<"���������ڴ�:"<<status.dwAvailVirtual<<endl;
    cout<<"ʹ����:"<<status.dwMemoryLoad<<"%"<<endl;
}

int main()
{
    Global();
    return 0;
}
