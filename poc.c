/* Proof of Concept */

#include <stdio.h>

#include <windows.h>

#pragma comment(lib,"user32.lib")

int main(int nArgc, char** lppszArgv)
{
    HANDLE hProp = GetProp(GetShellWindow(), MAKEINTATOM(0x464));

    printf("Current state: %p\n", hProp);

    if(nArgc>1)
    {
        HANDLE const hNew = (HANDLE)atoi(lppszArgv[1]);

        if(SetProp(GetShellWindow(), MAKEINTATOM(0x464), hNew))
        {
            printf("New state: %p\n", hNew);
        }
        else
        {
            puts("Failed to set new state.");
        }
    }

    return 0;
}
