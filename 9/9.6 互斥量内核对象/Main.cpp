#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // ����Mutex
    HANDLE hMutex = CreateMutex(NULL,FALSE,FALSE);
    
    // �ȴ�
    WaitForSingleObject(hMutex,INFINITE);
    cout<<"�ȴ�����"<<endl;
    
    // �ر�Mutex
    CloseHandle(hMutex);

    return 0;
}
