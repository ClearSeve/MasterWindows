#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

int main()
{
    // 创建Mutex
    HANDLE hMutex = CreateMutex(NULL,FALSE,FALSE);
    
    // 等待
    WaitForSingleObject(hMutex,INFINITE);
    cout<<"等待结束"<<endl;
    
    // 关闭Mutex
    CloseHandle(hMutex);

    return 0;
}
