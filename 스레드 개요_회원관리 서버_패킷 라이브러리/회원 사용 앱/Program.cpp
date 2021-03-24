////실습할 클라이언트 코드입니다.
//#include <Windows.h>
//#include "resource.h"
//#define PNAME (TEXT("\\\\.\\pipe\\Test"))
//
//enum MsgType
//{
//    MID_REG_REQ,//가입 요청
//    MID_REG_RES,//가입 요청 결과
//    MID_UNR_REQ//탈퇴 요청
//};
//
//typedef struct MsgHead
//{
//    int msgid;
//    int bdlen;
//}MsgHead;
//
//void CancelProc(HWND hDlg)
//{
//    EndDialog(hDlg, 0);
//}
//void RegProc(HWND hDlg)
//{
//    WCHAR id[256];
//    WCHAR name[256];
//    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
//    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);
//    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
//    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));
//
//    char packet[4096];
//    MsgHead* pmh = (MsgHead*)packet;
//    pmh->msgid = MID_REG_REQ;
//    pmh->bdlen = 0;
//    int idlen_po = (lstrlen(id) + 1) * 2;
//    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, &idlen_po, sizeof(int));
//    pmh->bdlen += sizeof(int);
//    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, id, idlen_po);
//    pmh->bdlen += idlen_po;
//    int namelen_po = (lstrlen(name) + 1) * 2;
//    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, &namelen_po, sizeof(int));
//    pmh->bdlen += sizeof(int);
//    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, name, namelen_po);
//    pmh->bdlen += namelen_po;
//
//    HANDLE hPipe = CreateFile(PNAME,
//        GENERIC_READ | GENERIC_WRITE,
//        0, 0,
//        OPEN_EXISTING, 0, 0);
//    DWORD dw;
//    WriteFile(hPipe, packet, pmh->bdlen + sizeof(MsgHead), &dw, 0);
//    FlushFileBuffers(hPipe);
//
//    ReadFile(hPipe, packet, sizeof(MsgHead), &dw, 0);
//    int result = 0;
//    ReadFile(hPipe, &result, sizeof(int), &dw, 0);
//    CloseHandle(hPipe);
//    if (result)
//    {
//        MessageBox(0, TEXT("가입 성공"), TEXT("요청 결과"), MB_OK);
//    }
//    else
//    {
//        MessageBox(0, TEXT("가입 실패"), TEXT("요청 결과"), MB_OK);
//    }
//}
//void UnRegProc(HWND hDlg)
//{
//
//}
//void OnCommand(HWND hDlg, WORD cid, WORD cmsg, HWND cWnd)
//{
//    switch (cid)
//    {
//    case IDC_BUTTON_REG: RegProc(hDlg); break;
//    case IDC_BUTTON_UNREG: UnRegProc(hDlg); break;
//    case IDCANCEL: CancelProc(hDlg); break;
//    }
//}
//BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//    switch (iMessage)
//    {
//    case WM_COMMAND:
//        OnCommand(hDlg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam); return TRUE;
//    }
//    return FALSE;
//}
//INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nShow)
//{
//    DialogBox(hIns, MAKEINTRESOURCE(IDD_DIALOG1), 0, MyDlgProc);
//    return 0;
//}

// Client

#include <Windows.h>
#include <string>
#include "resource.h"
#define PNAME (TEXT("\\\\.\\pipe\\Text"))

using namespace std;

enum MsgType
{
    MID_REG_REQ, // 가입 요청
    MID_REG_RES, // 가입 요청 결과
    MID_UNR_REQ, // 탈퇴 요청
};
typedef struct MsgHead
{
    int msgid;
    int bdlen;
}MsgHead;
void CancelProc(HWND hDlg)
{
    EndDialog(hDlg, 0);
}
void RegProc(HWND hDlg)
{
    WCHAR id[256];
    WCHAR name[256];
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);
    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));

    //if (id[0] == L'\0')
    if ((wstring)id == TEXT(""))
    {
        return;
    }

    char packet[4096];
    MsgHead* pmh = (MsgHead*)packet;
    pmh->msgid = MID_REG_REQ;
    pmh->bdlen = 0;
    int idlen_po = (lstrlen(id) + 1) * 2;   // wide character 이므로 *2
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, &idlen_po, sizeof(int));
    pmh->bdlen += sizeof(int);
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, id, idlen_po);
    pmh->bdlen += idlen_po;
    int namelen_po = (lstrlen(name) + 1) * 2;   // wide character 이므로 *2
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, &namelen_po, sizeof(int));
    pmh->bdlen += sizeof(int);
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, name, namelen_po);
    pmh->bdlen += namelen_po;
    HANDLE hPipe = CreateFile(PNAME, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

    DWORD dw;
    WriteFile(hPipe, packet, pmh->bdlen + sizeof(MsgHead), &dw, 0);
    FlushFileBuffers(hPipe);

    ReadFile(hPipe, packet, sizeof(MsgHead), &dw, 0);   // header receive
    int result = 0;
    ReadFile(hPipe, &result, sizeof(int), &dw, 0);      // body receive
    CloseHandle(hPipe);
    if (result)
    {
        MessageBox(hDlg, TEXT("회원가입 성공"), TEXT("가입 성공"), MB_OK);
    }
    else
    {
        MessageBox(hDlg, TEXT("회원가입 실패"), TEXT("가입 실패"), MB_OK);
    }
}
void UnRegProc(HWND hDlg)
{
    WCHAR id[256];
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));

    if (id[0] == L'\0')
    {
        return;
    }

    char packet[4096];
    MsgHead* pmh = (MsgHead*)packet;
    pmh->msgid = MID_UNR_REQ;
    pmh->bdlen = 0;
    int idlen_po = (lstrlen(id) + 1) * 2;   // wide character 이므로 *2
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, &idlen_po, sizeof(int));
    pmh->bdlen += sizeof(int);
    memcpy(packet + sizeof(MsgHead) + pmh->bdlen, id, idlen_po);
    pmh->bdlen += idlen_po;
    HANDLE hPipe = CreateFile(PNAME, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0, 0);

    DWORD dw;
    WriteFile(hPipe, packet, pmh->bdlen + sizeof(MsgHead), &dw, 0);
    FlushFileBuffers(hPipe);
}
void OnCommand(HWND hDlg, WORD cid, WORD cmsg, HWND cWnd)
{
    switch (cid)
    {
    case IDC_BUTTON_REG: RegProc(hDlg); break;
    case IDC_BUTTON_UNREG: UnRegProc(hDlg); break;
    case IDCANCEL:CancelProc(hDlg); break;
    }
}
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_COMMAND: OnCommand(hDlg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam); return TRUE;
    }
    return FALSE;
}

INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nSHow)
{
    DialogBox(hIns, MAKEINTRESOURCE(IDD_DIALOG1), 0, MyDlgProc);
    return 0;
}