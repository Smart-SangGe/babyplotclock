#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
//�������������޸�Ϊ�Ƕȣ�
#define LIFT0 A//1350 ���д�� 
#define LIFT1 B//1250 д��ʱ̧�۶��� һ���lift0 С100����
#define LIFT2 C//1100 ��̧�ʼ�

// int servoLift = LIFT2;

//̧�ʺ����������ʵĸ߶� 0�����д�֣� 1����дʱ̧�ʣ� 2��̫�߱����ڲ���
// void lift(int lift)
// {
//     switch (lift)
//     {
//         // room to optimize !

//     case 0:

//         if (servoLift >= LIFT0)
//         {
//             while (servoLift >= LIFT0)
//             {
//                 servoLift--;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift); //�����������ݽǶ�
//             }
//         }
//         else
//         {
//             while (servoLift <= LIFT0)
//             {
//                 servoLift++;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift);
//             }
//         }

//         break;

//     case 1:

//         if (servoLift >= LIFT1)
//         {
//             while (servoLift >= LIFT1)
//             {
//                 servoLift--;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift);
//             }
//         }
//         else
//         {
//             while (servoLift <= LIFT1)
//             {
//                 servoLift++;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift);
//             }
//         }

//         break;

//     case 2:

//         if (servoLift >= LIFT2)
//         {
//             while (servoLift >= LIFT2)
//             {
//                 servoLift--;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift);
//             }
//         }
//         else
//         {
//             while (servoLift <= LIFT2)
//             {
//                 servoLift++;
//                 //servo1.writeMicroseconds(servoLift);
//                 //delayMicroseconds(LIFTSPEED);
//                 duoji(servoLift);
//             }
//         }
//         break;
//     }
// }

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
    puts(s);
}

int main()
{
    voice_broadcast(); //��������
    // write();
    // clean();
}
