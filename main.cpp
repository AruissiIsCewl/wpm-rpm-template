// jus use Attach(L"Process-Name-Here.exe")

/*
    How does this work? Basically it cycles through all your processes until it finds the process you specified, this should NOT be used for kernel anticheat games as it is most definitely detected

    you can find an example below!
    

   HANDLE proc = OpenProcess(VM_ALL_ACCESS, Hook(L"ac_client.exe"), FALSE, 0)
   WriteProcessMemory(proc, (LPVOID)offset, new-value, sizeof(offset), nullptr);

*/


#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <TlHelp32.h>




DWORD Attach(const wchar_t* proc) noexcept
{
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap == INVALID_HANDLE_VALUE)
    {
        MessageBoxA(nullptr, "", "Error: UJ7259", MB_OK); // remove the messagebox if you want
        return -1;
    }
    
    /*
    Remove line 21 to 27 if you want to use this method (yes this method is safe, it literally tells you to do it in msvc docs)
    do {
      HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    } while (hSnap == INVALID_HANDLE_VALUE);

    */


    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hSnap, &pe32))
    {
        CloseHandle(hSnap);
        return -1;
    }

    do
    {
        if (wcscmp(pe32.szExeFile, proc) == 0)
        {
            CloseHandle(hSnap);
            return pe32.th32ProcessID;
        }
    } while (Process32Next(hSnap, &pe32));


    CloseHandle(hSnap);


    return 0;
}
