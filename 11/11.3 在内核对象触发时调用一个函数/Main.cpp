#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

// 事件触发收到的消息
VOID CALLBACK WaitCallback( PTP_CALLBACK_INSTANCE Instance,
                           PVOID Context,
                           PTP_WAIT Wait,
                           TP_WAIT_RESULT WaitResult
                           )
{
    cout<<"WaitCallback"<<endl;
}
int main()
{
    // 创建内核对象触发线程池
    PTP_WAIT ThreadpoolWait = CreateThreadpoolWait(WaitCallback,NULL,NULL);

    // 创建时间
    HANDLE hEvent = CreateEvent(NULL,FALSE,TRUE,L"");

    // 绑定内核对象
    SetThreadpoolWait(ThreadpoolWait,hEvent,NULL);

    WaitForThreadpoolWaitCallbacks(ThreadpoolWait,FALSE);

    system("pause");
    // 关闭内核对象触发线程池
    CloseThreadpoolWait(ThreadpoolWait);
    return 0;
}

