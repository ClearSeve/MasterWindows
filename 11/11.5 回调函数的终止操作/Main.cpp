#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

CRITICAL_SECTION g_section = {0};

// �������첽
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                           PVOID Context,  
                           PTP_WORK Work)
{
    // ���ý���
    EnterCriticalSection(&g_section);

    cout<<"WorkCallback"<<endl;

    // ����
    LeaveCriticalSectionWhenCallbackReturns(Instance,&g_section);
}

int main()
{
    // ����������
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, NULL );

    // ��ʼ�� �ٽ���
    
    InitializeCriticalSection( &g_section );

    // �ύ����
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

    // �ȴ����������
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);
    
    // �ͷ��ٽ���
    DeleteCriticalSection(&g_section);

    // �رչ�����
    CloseThreadpoolWork(ThreadpoolWork);
    
    return 0;
}
