#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

PTP_POOL g_pPool = NULL;

// 工作项异步
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                           PVOID Context,  
                           PTP_WORK Work)
{
    cout<<"WorkCallback"<<endl;
}
int main()
{
    // 创建线程池定制
    g_pPool = CreateThreadpool(NULL);
    
    // 设置线程最小数
    SetThreadpoolThreadMinimum(g_pPool,5);
    // 设置线程最大数
    SetThreadpoolThreadMaximum(g_pPool,10);
    TP_CALLBACK_ENVIRON Environ;
    // 初始化回调环境
    InitializeThreadpoolEnvironment(Environ);

    // 创建工作项(添加线程池定制)
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, InitializeThreadpoolEnvironment );
    
    // 提交请求
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    
    // 等待工作项结束
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);

    // 关闭工作项
    CloseThreadpoolWork(ThreadpoolWork);
    
    // 关闭线程池定制
    CloseThreadpool(g_pPool);
    return 0;
}
