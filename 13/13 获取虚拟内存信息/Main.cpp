#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"


void ShowSys()
{
    SYSTEM_INFO info={0};
    GetSystemInfo(&info);
    cout<<"�ڴ�ҳ�Ĵ�С:"<<info.dwPageSize<<endl;
    cout<<"������С���õ�ַ:"<<info.lpMinimumApplicationAddress<<endl;
    cout<<"���������õ�ַ:"<<info.lpMaximumApplicationAddress<<endl;
    cout<<"��������:"<<info.dwAllocationGranularity<<endl;
}

int main()
{
    ShowSys();
    
    return 0;
}

