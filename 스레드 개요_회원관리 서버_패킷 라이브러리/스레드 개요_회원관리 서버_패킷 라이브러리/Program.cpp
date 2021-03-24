#include<Windows.h>
#include<stdio.h>
#include<thread>
DWORD WINAPI EntryOne(LPVOID param)
{
    int one = (int)(param);
    for (int i = 0; i < 100; i++)
    {
        Sleep(rand() % 1000);
        printf("Thread1:%d\n", one);
    }
    return 0;
}
DWORD WINAPI EntryTwo(LPVOID param)
{

    int one = (int)(param);
    for (int i = 0; i < 100; i++)
    {
        Sleep(rand() % 1000);
        printf("Thread2:%d\n", i);
    }
    return 0;
}

int main()
{
    DWORD id1, id2;
    int i = 1;
    HANDLE hThread = ::CreateThread(0,
        0, EntryOne, (LPVOID)i, 0, &id1);
    HANDLE hThread2 = ::CreateThread(0,
        0, EntryTwo, (LPVOID)i, 0, &id2);
    for (int i = 0; i < 100; i++)
    {
        Sleep(rand() % 1000);
        printf("main:%d\n", i);
    }
    getchar();
    CloseHandle(hThread);
    //�����尡 ����Ǵ� ���� �ƴ϶� ���̻� �����带 �ڵ鸵���� �ʰڴ�.(����x)
    CloseHandle(hThread2);
    SuspendThread(hThread);         //�����带 ������Ű�� �޼���
    ResumeThread(hThread);         //������ �����带 �ٽ� �����Ű�� �޼���
    TerminateThread(hThread, 0);      //�����带 ������ ���̴� �޼���
    TerminateThread(hThread2, 0);
    return 0;


    ///fefefe
}

