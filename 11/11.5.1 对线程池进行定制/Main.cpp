#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

PTP_POOL g_pPool = NULL;

// �������첽
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                           PVOID Context,  
                           PTP_WORK Work)
{
    cout<<"WorkCallback"<<endl;
}
int main()
{
    // �����̳߳ض���
    g_pPool = CreateThreadpool(NULL);
    
    // �����߳���С��
    SetThreadpoolThreadMinimum(g_pPool,5);
    // �����߳������
    SetThreadpoolThreadMaximum(g_pPool,10);
    TP_CALLBACK_ENVIRON Environ;
    // ��ʼ���ص�����
    InitializeThreadpoolEnvironment(Environ);

    // ����������(����̳߳ض���)
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, InitializeThreadpoolEnvironment );
    
    // �ύ����
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    
    // �ȴ����������
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);

    // �رչ�����
    CloseThreadpoolWork(ThreadpoolWork);
    
    // �ر��̳߳ض���
    CloseThreadpool(g_pPool);
    return 0;
}
