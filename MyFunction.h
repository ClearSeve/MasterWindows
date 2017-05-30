void ShowErrorInfo()
{
    LPTSTR lpMsgBuf;
    DWORD nErrno = GetLastError();//获取错误信息
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        nErrno,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR)&lpMsgBuf,
        0,
        NULL
        );
    WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), lpMsgBuf, wcslen(lpMsgBuf),NULL,NULL); // 输出内容
    LocalFree(lpMsgBuf);
    system("pause");
}
