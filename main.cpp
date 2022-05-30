#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void voice_broadcast(void)
{
    char s[20] = "play ##:##.mp3"; // ϵͳ����
    int hour, minute;

    time_t tmpcal_ptr; 
    struct tm *tmp_ptr = NULL;
    time(&tmpcal_ptr);
    tmp_ptr = gmtime(&tmpcal_ptr);
    hour = tmp_ptr->tm_hour + 8; // ʱ������Сʱ
    minute = tmp_ptr->tm_min;
    // ��ȡ��ǰʱ�䲢����Сʱ�ͷ���

    if (hour > 12)
        hour -= 12;
    // 12h��
    
    if (hour > 10)
    {
        s[5] = '1'; // Сʱ��λ��1
        hour -= 10;
        itoa(hour, s + 6, 10); // ��hour�ĸ�λ��ʮ���Ʋ������ַ�������ʽд��s[6]��д���s[7] = '\0'
    }
    else
    {
        s[5] = '0'; // Сʱʮλ��0
        itoa(hour, s + 6, 10); 
    }
    // ��ȫϵͳ�����е�Сʱ

    s[7] = ':'; // д��Сʱ��λ����s[7]='\0'
    itoa(minute / 10, s + 8, 10);
    itoa(minute % 10, s + 9, 10);
    s[10] = '.'; // д����Ӹ�λ����s[10]='\0'
    system(s);
}

int main()
{
    voice_broadcast(); //��������
    write();
    clean();
}
        