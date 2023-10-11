#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/msg.h>

typedef struct msg {
    long int msgType;
    int num;
} Msg;

void main() {
    Msg message;
    message.msgType = 1;
    int msgID = msgget(1440, 0666 | IPC_CREAT);
    if (msgID == -1) {
        printf("Message queue creation failed\n");
        exit(1);
    }
    if (fork() == 0) { // Child Process (Sender)
        int n;
        printf("Enter number ");
        scanf("%d", &n);
        message.num = n;
        if (msgsnd(msgID, (void*)&message, sizeof(int), 0) == -1) {
            printf("Message send failure.\n");
            exit(1);
        }
    }
    else { // Parent Process (Receiver)
        if (msgrcv(msgID, (void *)&message, sizeof(int), message.msgType, 0) == -1) {
            printf("Message receive failure.\n");
            exit(1);
        }
        int rev = 0, n = message.num;
        while (n > 0) {
            rev = rev * 10 + (n % 10);
            n = n / 10;
        }
        if (rev == message.num)
            printf("Number entered is palindrome\n");
        else
            printf("Number entered is not palindrome\n");
        if (msgctl(msgID, IPC_RMID, 0) == -1) {
            printf("Message queue deletion failure.\n");
            exit(1);
        }
    }
}