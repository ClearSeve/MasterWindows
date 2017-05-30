#include <Windows.h>

#include <iostream>
using namespace std;

#include "../../MyFunction.h"


// �������첽
VOID CALLBACK WorkCallback( PTP_CALLBACK_INSTANCE Instance,  
                            PVOID Context,  
                            PTP_WORK Work)
{
    cout<<"WorkCallback"<<endl;
}

int main()
{
    // ����������
    PTP_WORK ThreadpoolWork = CreateThreadpoolWork( WorkCallback, NULL, NULL );
    // �ύ����
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    SubmitThreadpoolWork(ThreadpoolWork);
    // �ȴ����������
    WaitForThreadpoolWorkCallbacks(ThreadpoolWork,FALSE);
    // �رչ�����
    CloseThreadpoolWork(ThreadpoolWork);
    return 0;
}
