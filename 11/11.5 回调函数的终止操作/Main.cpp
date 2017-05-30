#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

CRITICAL_SECTION g_section = {0};

// 工作项异步
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                           PVOID Context,  
                           PTP_WORK Work)
{
    // 设置进入
    EnterCriticalSection(&g_section);

    cout<<"WorkCallback"<<endl;

    // 进出
    LeaveCriticalSectionWhenCallbackReturns(Instance,&g_section);
}

int main()
{
    // 创建工作项
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, NULL );

    // 初始化 临界区
    
    InitializeCriticalSection( &g_section );

    // 提交请求
    for (int i=0;i<100;++i)
    {
        SubmitThreadpoolWork(ThreadpoolWork);
    }
    
    /*
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    */

    // 等待工作项结束
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);
    
    // 释放临界区
    DeleteCriticalSection(&g_section);

    // 关闭工作项
    CloseThreadpoolWork(ThreadpoolWork);
    
    return 0;
}
