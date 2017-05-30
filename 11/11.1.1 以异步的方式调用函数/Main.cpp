#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"


// 工作项异步
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                            PVOID Context,  
                            PTP_WORK Work)
{
    cout<<"WorkCallback"<<endl;
}

int main()
{
    // 创建工作项
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, NULL );
    // 提交请求
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    // 等待工作项结束
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);
    // 关闭工作项
    CloseThreadpoolWork(ThreadpoolWork);
    return 0;
}
