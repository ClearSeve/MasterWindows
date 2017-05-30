#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"


void ShowSys()
{
    SYSTEM_INFO info={0};
    GetSystemInfo(&info);
    cout<<"内存页的大小:"<<info.dwPageSize<<endl;
    cout<<"可用最小可用地址:"<<info.lpMinimumApplicationAddress<<endl;
    cout<<"可用最大可用地址:"<<info.lpMaximumApplicationAddress<<endl;
    cout<<"区域力度:"<<info.dwAllocationGranularity<<endl;
}

int main()
{
    ShowSys();
    
    return 0;
}

