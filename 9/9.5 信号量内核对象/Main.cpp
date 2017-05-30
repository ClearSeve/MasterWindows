#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
    HANDLE hSemaphore = CreateSemaphore(NULL,5,10,NULL);
    
    for ( int i=0; i<10; ++i)
    {
        ReleaseSemaphore(hSemaphore,-1,NULL);
        WaitForSingleObject(hSemaphore,INFINITE);
    }
    

    CloseHandle(hSemaphore);
    return 0;
}