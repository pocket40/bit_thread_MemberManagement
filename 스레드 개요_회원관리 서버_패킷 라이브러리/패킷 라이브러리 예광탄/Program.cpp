#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Packet.h"

int main()
{
    char id[20] = "홍길동";
    int age=80;
    char addr[200] = "대한민국 근처 어느 섬에 있는 동굴?";
    Packet* packet = new Packet(20);
    int len = strlen(id) + 1;
    packet->Capsulate(&len, sizeof(int));
    packet->Capsulate(id, len);
    packet->Capsulate(&age, sizeof(int));
    len = strlen(addr) + 1;
    packet->Capsulate(&len, sizeof(int));
    packet->Capsulate(addr, len);

    FILE* fp = NULL;
    fopen_s(&fp, "data.txt", "w");
    packet->Write(fp);//직렬화
    fclose(fp);
    delete packet;

    //수신부
    FILE* fp2 = NULL;
    fopen_s(&fp2, "data.txt", "r");
    Packet* packet2 = new Packet(fp2);//역직렬화
    fclose(fp2);

    int len2;    
    char id2[20];
    int age2;
    char addr2[200];
    int msgid = packet2->GetMsgID();
    printf("MSG ID:%d\n", msgid);
    packet2->UnCapsulate(&len2, sizeof(int));
    packet2->UnCapsulate(id2, len2);
    packet2->UnCapsulate(&age2, sizeof(int));
    packet2->UnCapsulate(&len2, sizeof(int));
    packet2->UnCapsulate(addr2, len2);
    printf("이름:%s 나이:%d 주소:%s\n", id2, age2, addr2);
    delete packet2;

    return 0;
}