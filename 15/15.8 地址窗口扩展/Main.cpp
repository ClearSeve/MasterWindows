#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // Ԥ���ڴ�
    char* pszBuf = (char*)VirtualAlloc(NULL,1024*1024,MEM_RESERVE|MEM_PHYSICAL,PAGE_READWRITE);

    // �����ڴ�
    int nValue[100] = {0};
    AllocateUserPhysicalPages(GetCurrentProcess(),1,nValue);
    // �ͷŷ���

    // �ͷ�Ԥ��
    VirtualFree(pszBuf,0,MEM_RESET);

    return 0;
}
