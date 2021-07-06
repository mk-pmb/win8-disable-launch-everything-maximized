#include <cstdlib>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>

#include <btypes.h>
#include <bvargs.h>
#include <dlgtempl.h>
#include <memtaf.h>
#include <rc_const.h>
#include <w32shell.h>
#include <w32ui.h>
#include <w32wnd.hpp>

#include "slems.h"

#define SLEMS_TITLE _T("SLEMS")

#define SSE_PROP MAKEINTATOM(0x464)
#define SSE_UNSET 0
#define SSE_ENABLED 1
#define SSE_DISABLED 2

#define IDC_GROUPBOX (IDC_FIRST+0)
#define IDC_STATIC_DESCRIPTION (IDC_FIRST+1)
#define IDC_BUTTON_DISABLE (IDC_FIRST+2)
#define IDC_BUTTON_ENABLE (IDC_FIRST+3)
#define IDC_APPLY (IDC_FIRST+4)

static DLGTEMPLATEITEMINFO const l_DlgTemplItems[] =
{
#define DLU_SZ_DIALOG_W (DLU_SP_DIALOGBOX_MARGIN_H+DLG_SZ_GROUPBOX_W+DLU_SP_DIALOGBOX_MARGIN_H)
#define DLU_SZ_DIALOG_H (DLU_BUTTON_OKCANCELAPPLY_Y+DLU_SZ_BUTTON_H+DLU_SP_DIALOGBOX_MARGIN_V)
#define DLG_SZ_GROUPBOX_X (DLU_SP_DIALOGBOX_MARGIN_H)
#define DLG_SZ_GROUPBOX_Y (DLU_SP_DIALOGBOX_MARGIN_V)
#define DLG_SZ_GROUPBOX_W (DLU_SP_GROUPBOX_MARGIN_LEFT_H+DLU_BUTTON_ABLE_W+DLU_SP_RELATED_H+DLU_BUTTON_ABLE_W+DLU_SP_GROUPBOX_MARGIN_RIGHT_H)
#define DLG_SZ_GROUPBOX_H (DLU_SP_GROUPBOX_MARGIN_TOP_V+IDC_STATIC_DESCRIPTION_H+DLU_SP_UNRELATED_V+DLU_BUTTON_ABLE_H+DLU_SP_GROUPBOX_MARGIN_BOTTOM_V)
#define DLU_GROUPBOX_INNER_W (DLU_SZ_DIALOG_INNER_W-DLU_SP_GROUPBOX_MARGIN_LEFT_H-DLU_SP_GROUPBOX_MARGIN_RIGHT_H)
#define DLU_STATIC_DESCRIPTION_X (DLG_SZ_GROUPBOX_X+DLU_SP_GROUPBOX_MARGIN_LEFT_H)
#define DLU_STATIC_DESCRIPTION_Y (DLG_SZ_GROUPBOX_Y+DLU_SP_GROUPBOX_MARGIN_TOP_V)
#define IDC_STATIC_DESCRIPTION_H (DLU_SZ_STATIC_H+DLU_SZ_STATIC_H+DLU_SZ_STATIC_H+DLU_SZ_STATIC_H)
#define DLU_BUTTON_ENABLE_X (DLU_STATIC_DESCRIPTION_X)
#define DLU_BUTTON_DISABLE_X (DLU_BUTTON_ENABLE_X+DLU_BUTTON_ABLE_W+DLU_SP_RELATED_H)
#define DLU_BUTTON_ABLE_Y (DLU_STATIC_DESCRIPTION_Y+IDC_STATIC_DESCRIPTION_H+DLU_SP_UNRELATED_V)
#define DLU_BUTTON_ABLE_W (100)
#define DLU_BUTTON_ABLE_H (50)
#define DLU_BUTTON_HELP_X (DLU_SP_DIALOGBOX_MARGIN_H)
#define DLU_BUTTON_OK_X (DLU_BUTTON_CANCEL_X-DLU_SZ_BUTTON_W-DLU_SP_RELATED_H)
#define DLU_BUTTON_CANCEL_X (DLU_BUTTON_APPLY_X-DLU_SZ_BUTTON_W-DLU_SP_RELATED_H)
#define DLU_BUTTON_APPLY_X (DLU_SZ_DIALOG_W-DLU_SP_DIALOGBOX_MARGIN_H-DLU_SZ_BUTTON_W)
#define DLU_BUTTON_OKCANCELAPPLY_Y (DLG_SZ_GROUPBOX_Y+DLG_SZ_GROUPBOX_H+DLU_SP_UNRELATED_V)
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_GROUPBOX,                                        0, IDC_GROUPBOX,            DLG_SZ_GROUPBOX_X,          DLG_SZ_GROUPBOX_Y,          DLG_SZ_GROUPBOX_W,      DLG_SZ_GROUPBOX_H },
    { DLGTEMPLATEITEM_CLASS_STATIC, SS_LEFT|SS_NOPREFIX,                                0, IDC_STATIC_DESCRIPTION,  DLU_STATIC_DESCRIPTION_X,   DLU_STATIC_DESCRIPTION_Y,   DLU_GROUPBOX_INNER_W,   IDC_STATIC_DESCRIPTION_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_PUSHLIKE|BS_AUTORADIOBUTTON|WS_TABSTOP|WS_GROUP, 0, IDC_BUTTON_ENABLE,       DLU_BUTTON_ENABLE_X,        DLU_BUTTON_ABLE_Y,          DLU_BUTTON_ABLE_W,      DLU_BUTTON_ABLE_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_PUSHLIKE|BS_AUTORADIOBUTTON|WS_TABSTOP,          0, IDC_BUTTON_DISABLE,      DLU_BUTTON_DISABLE_X,       DLU_BUTTON_ABLE_Y,          DLU_BUTTON_ABLE_W,      DLU_BUTTON_ABLE_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_PUSHBUTTON|WS_TABSTOP|WS_GROUP,                  0, IDHELP,                  DLU_BUTTON_HELP_X,          DLU_BUTTON_OKCANCELAPPLY_Y, DLU_SZ_BUTTON_W,        DLU_SZ_BUTTON_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_DEFPUSHBUTTON|WS_TABSTOP|WS_GROUP,               0, IDOK,                    DLU_BUTTON_OK_X,            DLU_BUTTON_OKCANCELAPPLY_Y, DLU_SZ_BUTTON_W,        DLU_SZ_BUTTON_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_PUSHBUTTON|WS_TABSTOP,                           0, IDCANCEL,                DLU_BUTTON_CANCEL_X,        DLU_BUTTON_OKCANCELAPPLY_Y, DLU_SZ_BUTTON_W,        DLU_SZ_BUTTON_H },
    { DLGTEMPLATEITEM_CLASS_BUTTON, BS_PUSHBUTTON|WS_TABSTOP,                           0, IDC_APPLY,               DLU_BUTTON_APPLY_X,         DLU_BUTTON_OKCANCELAPPLY_Y, DLU_SZ_BUTTON_W,        DLU_SZ_BUTTON_H },
};

static DLGTEMPLATEINFO const l_DlgTempl =
{
    NULL,
    DS_SHELLFONT|DS_SETFONT|DS_CENTER|DS_MODALFRAME|WS_CAPTION|WS_SYSMENU,
    0,
    __ARRAYSIZE(l_DlgTemplItems),
    0,
    0, 0, DLU_SZ_DIALOG_W, DLU_SZ_DIALOG_H,
    l_DlgTemplItems
};

class CSmallScreenEnhancementSwitcherApp
    : public CDialogUI
{
private:
    typedef CSmallScreenEnhancementSwitcherApp CSelf;
    typedef CDialogUI CSuper;

protected:
    static int GetState()
    {
        return (int)DEGRADE_POINTER(GetProp(GetShellWindow(), SSE_PROP));
    }
    static BOOL SetState(int const nState)
    {
        return SetProp(GetShellWindow(), SSE_PROP, (HANDLE)UPGRADE_POINTER(nState));
    }

    static BOOL IsSupported()
    {
        return GetState()!=SSE_UNSET;
    }

    static BOOL IsEnabled()
    {
        return GetState()==SSE_ENABLED;
    }

    static int StateToButton(BOOL const nState)
    {
        return IDC_BUTTON_DISABLE+nState;
    }

    static BOOL ButtonToState(int const nState)
    {
        return !!(nState-IDC_BUTTON_DISABLE);
    }

    BOOL WndProcOnInitDialog(HWND hWnd, HWND hWndFocus, LPARAM lParam) override
    {
        HINSTANCE const hInstance = GetWindowInstance(hWnd);
    
        SetWindowText(hWnd, SLEMS_TITLE);
        SetDlgItemText(hWnd, IDC_GROUPBOX, _T("Launch all windows maximized"));
        SetDlgItemText(hWnd, IDC_STATIC_DESCRIPTION, _T("This setting controls the MaximizePolicy for ShowWindow and modifies the ShouldLaunchEverythingMaximized cache. When your Windows Explorer (desktop process) (re)starts, the setting is reset to default."));
        SetDlgItemText(hWnd, IDC_BUTTON_ENABLE, _T("Enable"));
        SetDlgItemText(hWnd, IDC_BUTTON_DISABLE, _T("Disable"));
        CheckRadioButton(hWnd, IDC_BUTTON_DISABLE, IDC_BUTTON_ENABLE, StateToButton(IsEnabled()));
        SetDlgItemText(hWnd, IDHELP, _T("Help"));
        SetDlgItemText(hWnd, IDOK, _T("OK"));
        SetDlgItemText(hWnd, IDCANCEL, _T("Cancel"));
        SetDlgItemText(hWnd, IDC_APPLY, _T("Apply"));
        EnableDlgItem(hWnd, IDC_APPLY, FALSE);

        SetWindowLargeIcon(hWnd, LoadLargeIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON)));
        SetWindowSmallIcon(hWnd, LoadSmallIcon(hInstance, MAKEINTRESOURCE(IDI_MAINICON)));

        return TRUE;
    }

    VOID WndProcOnCommand(HWND hWnd, INT nId, HWND hWndCtl, UINT uCodeNotify) override
    {
        switch(nId)
        {
        case IDHELP:
            ShellExecute2(hWnd, NULL, _T("http://nn.ai4rei.net/dev/ref/sme/"), NULL, NULL, SW_SHOWNORMAL);
            break;
        case IDC_APPLY:
        case IDOK:
            {
                int const nButton = GetCheckedRadioButton(hWnd, IDC_BUTTON_DISABLE, IDC_BUTTON_ENABLE);

                if(nButton!=0)
                {
                    if(SetEnabled(ButtonToState(nButton)))
                    {
                        EnableDlgItem(hWnd, IDC_APPLY, FALSE);
                    }
                    else
                    {
                        MessageBox(hWnd, _T("Failed to update setting."), SLEMS_TITLE, MB_E_OKONLY);
                    }
                }
                else
                {
                    MessageBox(hWnd, _T("Nothing selected."), SLEMS_TITLE, MB_I_OKONLY);
                }

                if(nId==IDC_APPLY)
                {
                    break;
                }

                Close(hWnd);
            }
            break;
        case IDCANCEL:
            Close(hWnd);
            break;
        case IDC_BUTTON_ENABLE:
        case IDC_BUTTON_DISABLE:
            EnableDlgItem(hWnd, IDC_APPLY, TRUE);
            break;
        }
    }

    VOID WndProcOnCreated(HWND hWnd, DWORD dwTime) override
    {
        if(!IsSupported())
        {
            MessageBox(hWnd, _T("This Windows version does not seem to support the functionality."), SLEMS_TITLE, MB_I_OKONLY);
        }
    }

public:
    virtual ~CSmallScreenEnhancementSwitcherApp()
    {
    }

    CSmallScreenEnhancementSwitcherApp(HINSTANCE const hInstance, LPCDLGTEMPLATE const lpDlgTempl)
        : CDialogUI(hInstance, lpDlgTempl, NULL)
    {
        InitCommonControls();
    }

    static BOOL SetEnabled(BOOL const bEnabled)
    {
        return SetState(bEnabled ? SSE_ENABLED : SSE_DISABLED);
    }
};

INT WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpszCmdLine, INT nShowCmd)
{
    LPTSTR* lppszArgv = NULL;
    ULONG ulArgc = 0;

    if(BVArgsSplit(GetCommandLine(), &ulArgc, &lppszArgv))
    {
        int nResult = EXIT_FAILURE;
        bool bQuit = false;

        for(ULONG ulIdx = 1; ulIdx<ulArgc; ulIdx++)
        {
            LPCTSTR lpszArg = lppszArgv[ulIdx];

            if(lpszArg[0]==_T('-') || lpszArg[0]=='/')
            {
                lpszArg++;

                if(_tcsicmp(lpszArg, _T("SetState"))==0)
                {
                    LPCTSTR const lpszParam = lppszArgv[++ulIdx];

                    if(lpszParam!=NULL)
                    {
                        if(CSmallScreenEnhancementSwitcherApp::SetEnabled(_ttoi(lpszParam)!=0))
                        {
                            nResult = EXIT_SUCCESS;
                            break;
                        }

                        bQuit = true;
                        break;
                    }
                }
                else
                if(_tcscmp(lpszArg, _T("?"))==0 || _tcsicmp(lpszArg, _T("Help"))==0)
                {
                    MessageBox(NULL, _T("Usage: slems [-SetState <new state>] [-Help]"), SLEMS_TITLE, MB_I_OKONLY);
                    nResult = EXIT_SUCCESS;
                    bQuit = true;
                    break;
                }
            }
        }

        MemTFree(&lppszArgv);

        if(bQuit)
        {
            return nResult;
        }
    }

    LPVOID lpDialog = NULL;

    if(DlgTemplateEx2(&l_DlgTempl, &lpDialog))
    {
        int nResult = CSmallScreenEnhancementSwitcherApp(hInstance, static_cast< LPCDLGTEMPLATE >(lpDialog));

        MemTFree(&lpDialog);

        return nResult;
    }

    return EXIT_FAILURE;
}
