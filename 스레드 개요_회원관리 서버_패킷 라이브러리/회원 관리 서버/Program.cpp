////�ǽ��� ���� �ڵ��Դϴ�.
//#include <Windows.h>
//#include "resource.h"
//#include<map>
//#include <string>
//using namespace std;
//map<wstring, wstring> mem_map;
//void CancelProc(HWND hDlg)
//{
//    EndDialog(hDlg, 0);
//}
//
//bool RegProcedure(wstring id, wstring name)
//{
//    if (mem_map[id] == TEXT(""))
//    {
//        mem_map[id] = name;
//        return true;
//    }
//    return true;
//}
//void RegProc(HWND hDlg) // ����ó��
//{
//    WCHAR id[256];
//    WCHAR name[256];
//    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
//    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);
//    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
//    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));
//    if (mem_map[id] == TEXT(""))
//    {
//        SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_ADDSTRING, 0, (LPARAM)id);
//        mem_map[id] = name;
//    }
//}
//void RemoveProc(HWND hDlg)
//{
//    WCHAR id[256];
//    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
//    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
//    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));
//    if (mem_map[id] != TEXT(""))
//    {
//        SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_DELETESTRING, 0, (LPARAM)id);
//        mem_map[id] = TEXT("");
//    }
//}
//void MemberListSelectChanged(HWND hDlg)
//{
//    int index = SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETCURSEL, 0, 0);
//    if (index == -1) { return; }
//    WCHAR id[256] = TEXT("");
//    SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETTEXT, index, (LPARAM)id);
//    SetDlgItemText(hDlg, IDC_EDIT_ID, id);
//    SetDlgItemText(hDlg, IDC_EDIT_NAME, mem_map[id].c_str());
//}
//void MemberProc(HWND hDlg, WORD cmsg)
//{
//    switch (cmsg)
//    {
//    case LBN_SELCHANGE: MemberListSelectChanged(hDlg); break;
//    }
//}
//void OnCommand(HWND hDlg, WORD cid, WORD cmsg, HWND cWnd)
//{
//    switch (cid)
//    {
//    case IDC_BUTTON_REG: RegProc(hDlg); break;
//    case IDC_BUTTON_REMOVE: RemoveProc(hDlg); break;
//    case IDC_LIST_MEMBER: MemberProc(hDlg, cmsg); break;
//    case IDCANCEL: CancelProc(hDlg); break;
//    }
//}
//void RegReqProc(HANDLE hPipe, const char* packet)
//{
//    int usize = 0;
//    int ideln_po;
//    memcpy(&idlen_po, packet + usize, sizeof(int));
//    usize += sizeof(int);
//    WCHAR id[256];
//    memcpy(id, packet+usize,ideln)
//}
//
//DWORD APIENTRY DoIt(LPVOID param)
//{
//    HANDLE hPipe = (HANDLE)param;
//    //to do
//    DisconnectNamedPipe(hPipe);
//    CloseHandle(hPipe);
//    DWORD dw;
//    ReadFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
//    char packet[4096];
//    ReadFile(hPipe, packet, mh, bdlen, &dw, 0);
//    switch (mh.msgid)
//    {
//    case MID_REG_REQ:RegReqProc
//    }
//    return 0;
//}
//DWORD APIENTRY ServerStart(LPVOID param)
//{
//    HANDLE hPipe;
//    while (true)
//    {
//        hPipe = CreateNamedPipe(TEXT("\\\\.\\pipe\\Test"),
//            PIPE_ACCESS_DUPLEX,//����/���� ����
//            PIPE_TYPE_BYTE,//���� ���
//            5,//���� ó���� �� �ִ� Ŭ���̾�Ʈ ��
//            4096, 4096, //�۽� �� ���� ���� ũ��
//            0, 0);
//        BOOL check = ConnectNamedPipe(hPipe, 0);
//        if ((check == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
//        {
//            check = true;
//        }
//        if (check)
//        {
//            CloseHandle(CreateThread(0, 0, DoIt, (LPVOID)hPipe, 0, 0));
//        }
//    }
//}
//
//void OnInitDialog(HWND hDlg)
//{
//
//    CloseHandle(CreateThread(0, 0, ServerStart, 0, 0, 0));
//}
//BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//    switch (iMessage)
//    {
//    case WM_INITDIALOG: OnInitDialog(hDlg); return TRUE;
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

// Server

#include <Windows.h>
#include "resource.h"
#include <map>
#include <string>
#define PNAME (TEXT("\\\\.\\pipe\\Text"))
using namespace std;

map<wstring, wstring> mem_map;

enum MsgType
{
    MID_REG_REQ, // ���� ��û
    MID_REG_RES, // ���� ��û ���
    MID_UNR_REQ, // Ż�� ��û
};
typedef struct MsgHead
{
    int msgid;
    int bdlen;
}MsgHead;
typedef struct HANDLES
{
    HWND hDlg;
    HANDLE hPipe;
}HANDLES;
void CancelProc(HWND hDlg)
{
    EndDialog(hDlg, 0);
}
int Reg(HWND hDlg, WCHAR* id, WCHAR* name)
{
    if ((wstring)name == TEXT(""))
        return 0;
    if (mem_map[id] == TEXT(""))
    {
        SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_ADDSTRING, 0, (LPARAM)id);
        mem_map[id] = name;
        return 1;
    }
    else
    {
        MessageBox(hDlg, TEXT("�����ϴ� ID �Դϴ�"), TEXT("ID ��� ����"), MB_OK);
        return 0;
    }
}
void RegProc(HWND hDlg, HANDLE hPipe, int bdlen)
{
    char base[4096];
    int usize = 0;
    DWORD dw;

    WCHAR id[256];
    int id_size = 0;
    WCHAR name[256];
    int name_size = 0;

    ReadFile(hPipe, base, bdlen, &dw, 0);
    memcpy(&id_size, base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(id, base + usize, id_size);
    usize += id_size;
    memcpy(&name_size, base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(name, base + usize, name_size);
    usize += name_size;

    //MessageBox(hDlg, id, name, MB_OK);
    int flag = 0;
    if (Reg(hDlg, id, name))
    {
        flag = 1;
    }

    MsgHead* pmh = (MsgHead*)base;
    pmh->msgid = MID_REG_RES;
    pmh->bdlen = 0;
    memcpy(base + pmh->bdlen + sizeof(MsgHead), &flag, sizeof(int));
    pmh->bdlen += sizeof(int);
    WriteFile(hPipe, base, pmh->bdlen + sizeof(MsgHead), &dw, 0);
    FlushFileBuffers(hPipe);
}
void RegProc(HWND hDlg)
{
    WCHAR id[256];
    WCHAR name[256];
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    GetDlgItemText(hDlg, IDC_EDIT_NAME, name, 256);
    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));

    if ((wstring)id == TEXT(""))
        //if (id[0] == L'\0')
    {
        return;
    }

    Reg(hDlg, id, name);
}
void Remove(HWND hDlg, WCHAR* id)
{
    int cnt = 0;
    int index = 0;
    WCHAR temp[256] = { 0 };
    if (mem_map[id] != TEXT(""))
    {
        index = SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_FINDSTRINGEXACT, 0, (LPARAM)id);
        SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_DELETESTRING, index, 0);
        mem_map[id] = TEXT("");
    }
}
void RemoveProc(HWND hDlg, HANDLE hPipe, int bdlen)
{
    char base[4096];
    int usize = 0;
    DWORD dw;

    WCHAR id[256];
    int id_size = 0;

    ReadFile(hPipe, base, bdlen, &dw, 0);
    memcpy(&id_size, base + usize, sizeof(int));
    usize += sizeof(int);
    memcpy(id, base + usize, id_size);
    usize += id_size;

    Remove(hDlg, id);
}
void RemoveProc(HWND hDlg)
{
    WCHAR id[256] = { 0 };
    GetDlgItemText(hDlg, IDC_EDIT_ID, id, 256);
    SetDlgItemText(hDlg, IDC_EDIT_ID, TEXT(""));
    SetDlgItemText(hDlg, IDC_EDIT_NAME, TEXT(""));

    Remove(hDlg, id);
}
void MemberListSelectChanged(HWND hDlg)
{
    int index = SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETCURSEL, 0, 0);
    if (index == -1) { return; }
    WCHAR id[256];
    SendDlgItemMessage(hDlg, IDC_LIST_MEMBER, LB_GETTEXT, index, (LPARAM)id);
    SetDlgItemText(hDlg, IDC_EDIT_ID, id);
    SetDlgItemText(hDlg, IDC_EDIT_NAME, mem_map[id].c_str());
}
void MemberProc(HWND hDlg, WORD cmsg)
{
    switch (cmsg)
    {
    case LBN_SELCHANGE: MemberListSelectChanged(hDlg); break;
    }
}
void OnCommand(HWND hDlg, WORD cid, WORD cmsg, HWND cWnd)
{
    switch (cid)
    {
    case IDC_BUTTON_REG: RegProc(hDlg); break;
    case IDC_BUTTON_REMOVE: RemoveProc(hDlg); break;
    case IDC_LIST_MEMBER: MemberProc(hDlg, cmsg); break;
    case IDCANCEL:CancelProc(hDlg); break;
    }
}
DWORD APIENTRY DoIt(LPVOID param)
{
    HANDLES* hHandle = (HANDLES*)param;
    HWND hDlg = hHandle->hDlg;
    HANDLE hPipe = hHandle->hPipe;
    delete hHandle;

    MsgHead mh;
    DWORD dw;
    ReadFile(hPipe, &mh, sizeof(MsgHead), &dw, 0);
    switch (mh.msgid)
    {
    case MID_REG_REQ: RegProc(hDlg, hPipe, mh.bdlen); break;
    case MID_UNR_REQ: RemoveProc(hDlg, hPipe, mh.bdlen); break;
    }

    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    return 0;
}
DWORD APIENTRY ServerStart(LPVOID param)
{
    HWND hDlg = (HWND)param;
    HANDLE hPipe;
    while (true)
    {
        hPipe = CreateNamedPipe(PNAME,
            PIPE_ACCESS_DUPLEX,//����/���� ����
            PIPE_TYPE_BYTE,//���� ���
            5,//���� ó���� �� �ִ� Ŭ���̾�Ʈ ��
            4096, 4096, //�۽� �� ���� ���� ũ��
            0, 0);
        BOOL check = ConnectNamedPipe(hPipe, 0);
        if ((check == FALSE) && (GetLastError() == ERROR_PIPE_CONNECTED))
        {
            check = true;
        }
        if (check)
        {
            HANDLES* pHandles = new HANDLES;
            pHandles->hDlg = hDlg;
            pHandles->hPipe = hPipe;
            CloseHandle(CreateThread(0, 0, DoIt, (LPVOID)pHandles, 0, 0));
        }
    }
}
void OnInitDialog(HWND hDlg)
{
    CloseHandle(CreateThread(0, 0, ServerStart, hDlg, 0, 0));
}
BOOL CALLBACK MyDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG: OnInitDialog(hDlg); return TRUE;
        // ��� ��Ʈ��   ��� ����   ��� �������ڵ�
    case WM_COMMAND: OnCommand(hDlg, LOWORD(wParam), HIWORD(wParam), (HWND)lParam); return TRUE;
    }
    return FALSE;
}

INT APIENTRY WinMain(HINSTANCE hIns, HINSTANCE hPrev, LPSTR cmd, INT nSHow)
{
    DialogBox(hIns, MAKEINTRESOURCE(IDD_DIALOG1), 0, MyDlgProc);
    return 0;
}