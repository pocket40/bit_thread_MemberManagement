#pragma once
#include <stdlib.h>
#include <stdio.h>
#define MAX_BUF_SIZE    4096

class Packet
{
    char base[MAX_BUF_SIZE];
    char* ptr;
    struct MsgHead
    {
        int msgid;
        int bdlen;
    };
public:
    Packet(FILE* fp);
    Packet(int msgid);
    void Capsulate(void* src, size_t size);
    int Write(FILE* fp);
    int GetMsgID();
    int UnCapsulate(void* target, size_t size);
};

