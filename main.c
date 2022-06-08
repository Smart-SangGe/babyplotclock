#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <font.h>

void voice_broadcast(int * h_m)
{
    char s[20] = "play ##-##.mp3"; // ϵͳ�����Ϊ�ļ������в��ܰ���":"��һ�����ַ������Ը���"-"����
    int hour, minute;

    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    hour = tmp_ptr->tm_hour + 8; // ʱ������Сʱ
    h_m[0] = hour / 10;
    h_m[1] = hour % 10; // ����ǰϵͳʱ���Сʱ��ʮλ�͸�λ���
    minute = tmp_ptr->tm_min;
    h_m[2] = minute / 10;
    h_m[3] = minute % 10; // ����ǰϵͳʱ��ķ��ӵ�ʮλ�͸�λ���
    // ��ȡ��ǰʱ�䲢����Сʱ�ͷ���

    if (hour > 12)
        hour -= 12;
    // 12h��

    if (hour > 10)
    {
        s[5] = '1'; // Сʱ��λ��1
        hour -= 10;
        s[6] = (char)hour + 48;
    }
    else
    {
        s[5] = '0'; // Сʱʮλ��0
        s[6] = (char)hour + 48;
    }
    // ��ȫϵͳ�����е�Сʱ

    s[8] = (char)(minute / 10) + 48; //��ϵͳʱ��ķ��ӵ�ʮλд��ϵͳ����
    s[9] = (char)(minute % 10) + 48; //��ϵͳʱ��ķ��ӵĸ�λд��ϵͳ����
    system(s);
}

int main()
{
    int i, h_m[4] = {0}; // h_m����ֱ��ŵ�ǰϵͳʱ��Сʱ��ʮλ����λ�Լ����ӵ�ʮλ����λ
    int flag = 0; // flag�������һ�����ֵĸ��������x����
    voice_broadcast(h_m); //��������

    for (i = 0; i < 4; i++)
    {
        while (LC_Num0[h_m[i]][flag] != 0)
        {
            readl(h_m[i], flag, i + 1); // i + 1�ֱ����1, 2, 3, 4,��Ӧ�ĸ�����
            // ִ�н�����õ�����(Tx, Ty)
            number(point.Tx, point.Ty, h_m[i], 0.9);
            flag++;
        }
    }
}
