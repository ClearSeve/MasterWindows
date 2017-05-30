#include <Windows.h>
#include <tchar.h>
#include <iostream>
using namespace std;

#include "../../MyFunction.h"

LPVOID pVoid1 = NULL;
LPVOID pVoid2 = NULL;
VOID CALLBACK FiberProc1( PVOID lpParameter )
{
    while(1)
    {
        cout<<"FiberProc1"<<endl;
        SwitchToFiber(pVoid2);
        Sleep(500);
        
    }
      
    
    
}VOID CALLBACK FiberProc2( PVOID lpParameter )
{
    while (1)
    {
        cout<<"FiberProc2"<<endl;
        SwitchToFiber(pVoid1);
        Sleep(500);
        
    }
        
    

}



int main()
{
    // ������ת��Ϊ���˳�
//    ConvertThreadToFiber((LPVOID)123);
    LPVOID pMainFiber =  ConvertThreadToFiberEx((LPVOID)123,FIBER_FLAG_FLOAT_SWITCH); // ����FPU
    // ��ȡ�˳̵�����
    int data = (int)GetFiberData();

    // ���������˳�
    pVoid1 = CreateFiber(0,FiberProc1,NULL);
    //SwitchToFiber(pVoid1);

    pVoid2 = CreateFiber(0,FiberProc2,NULL);
    SwitchToFiber(pVoid2);
    
    SleepEx(INFINITE,FALSE);

    // �����˳�ת��Ϊ�߳�
    ConvertFiberToThread();
    return 0;
}
