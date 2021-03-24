#include "Packet.h"
#include <string.h>
Packet::Packet(FILE* fp)
{
    fread(base, sizeof(MsgHead), 1, fp);
    MsgHead* mh = (MsgHead*)base;
    fread(base + sizeof(MsgHead), sizeof(char), mh->bdlen, fp);
    ptr = base + sizeof(MsgHead);
}
Packet::Packet(int msgid)
{
    MsgHead* mh = (MsgHead*)base;
    mh->msgid = msgid;
    mh->bdlen = 0;
}
void Packet::Capsulate(void* src, size_t size)
{
    MsgHead* mh = (MsgHead*)base;
    char* pos = base + sizeof(MsgHead) + mh->bdlen;
    memcpy(pos, src, size);
    mh->bdlen += size;
}
int Packet::Write(FILE* fp)
{
    MsgHead* mh = (MsgHead*)base;
    return fwrite(base, sizeof(char), sizeof(MsgHead) + mh->bdlen, fp);
}
int Packet::GetMsgID()
{
    MsgHead* mh = (MsgHead*)base;
    return mh->msgid;
}
int Packet::UnCapsulate(void* target, size_t size)
{
    char* optr = base + sizeof(MsgHead);
    MsgHead* mh = (MsgHead*)base;

    if ((ptr - optr) + size <= (unsigned)mh->bdlen)
    {
        memcpy(target, ptr, size);
        ptr += size;
        return 1;
    }
    return 0;
}




