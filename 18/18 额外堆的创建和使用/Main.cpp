#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    malloc(1000);
    // ������
    HANDLE hHeap = HeapCreate(HEAP_GENERATE_EXCEPTIONS,1024*1024,1024*1024*1024 /*Ϊ0�Զ���չ*/);
    
    // �����ڴ�
    char* pszBuf = (char*)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,MAX_PATH);

    // ʹ���ڴ�
    strcpy(pszBuf,"Hello World!");
    cout<<pszBuf<<endl;
    
    // �ͷ��ڴ�
    HeapFree(hHeap,0,pszBuf);
    
    // �ͷŶ�
    HeapDestroy(hHeap);

    // GetProcessHeap(); // ��ȡ����Ĭ�϶ѵľ��
    // GetProcessHeaps(); // ��ȡ�������жѵľ��
    return 0; 
}
// 2