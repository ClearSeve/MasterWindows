#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"

// �¼������յ�����Ϣ
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
    // �����ں˶��󴥷��̳߳�
    PTP_WAIT ThreadpoolWait = CreateThreadpoolWait(WaitCallback,NULL,NULL);

    // ����ʱ��
    HANDLE hEvent = CreateEvent(NULL,FALSE,TRUE,L"");

    // ���ں˶���
    SetThreadpoolWait(ThreadpoolWait,hEvent,NULL);

    WaitForThreadpoolWaitCallbacks(ThreadpoolWait,FALSE);

    system("pause");
    // �ر��ں˶��󴥷��̳߳�
    CloseThreadpoolWait(ThreadpoolWait);
    return 0;
}

