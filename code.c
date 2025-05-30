#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#define MAX 10

struct mesg_buffer{
long mesg_type;
char mesg_text[100];
}message;

int main()
{
	key_t key;
	int msgid;
	//ftok to generate unique key
	key = ftok("progfile",65);
	//msgget create a message queue
	//and returns identifier
	msgid=msgget(key,0666 | IPC_CREAT);
	message.mesg_type=1;
	printf("Write Date:");
	fgets(message.mesg_text,MAX,stdin);
	
	//msgsnd to send message
	msgsnd(msgid, &message,sizeof(message),0);
	
	//display the message
	printf("Data send is: %s \n", message.mesg_text);
	return 0;
	
}


//receive

#include<stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
//structure for msg queue

struct mesg_buffer{
	long mesg_type;
	char mesg_text[100];

}message;

int main()
{
	
	key_t key;
	int msgid;
	//ftok to generate unique key
	key=ftok("progfile",65);
	//msgget create a message queue
	//and returns identifier
	msgid= msgget(key, 0666 | IPC_CREAT);
	//msgrcv to recieve message
	msgrcv(msgid, &message, sizeof(message),1,0);
	//display the message
	printf("Data recieved is: %s \n", message.mesg_text);
	
	//to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	return  0;
	
}
