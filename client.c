// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#define PORT     8081
#define MAXLINE 1024
 #define MAX 15
int sockfd;
struct sockaddr_in     servaddr;

struct Node
{
  int data[4];
  char intr;
  struct Node *next;
};
 
struct Node* head = NULL;
void push(struct Node** head_ref, int* new_data ,char k)
{
    
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data[0]  = new_data[0];
    new_node->data[1]  = new_data[1];
    new_node->data[2]  = new_data[2];
    new_node->data[3]  = new_data[3];
    new_node->intr=k;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;

}



void printList(struct Node *node)
{
	printf(" Destination IP \t \t Interface  \n");
  while (node != NULL)
  {
     printf(" %d %d %d %d  \t \t %c  \n", node->data[0],node->data[1],node->data[2],node->data[3],node->intr);
     node = node->next;
  }
}





void delete(struct Node **head_ref, long int key)
{
    
    struct Node* temp = *head_ref, *prev;
 
    
    if (temp != NULL && temp->data == key)
    {
        *head_ref = temp->next;  
        free(temp);               
        return;
    }
 
    
    while (temp != NULL && temp->data != key)
    {
        prev = temp;
        temp = temp->next;
    }
 
    
    if (temp == NULL) return;

    prev->next = temp->next; 
    free(temp); 


}

void *recvmg(void *sock)
{
	int their_sock = *((int *)sock);
	char msg[500];
	int len;
	while((recvfrom(sockfd, (char *)msg, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, 			&len)) > 0) 
	{
		msg[len] = '\0';
		//fputs(msg,stdout);
		char *str = msg, *str2;
    				int value[4] = {0};
   					 size_t index = 0;
    				str2 = str; /* save the pointer */
    				while (*str)
    				 {
				        if (isdigit((unsigned char)*str)) 
				        {
				            value[index] *= 10;
				            value[index] += *str - '0';
				        }
				         else 
				         {
				            index++;
				        }
				        str++;
				    }
				    push(&head,value,'A');
				    
		memset(msg,'\0',sizeof(msg));
	}
}

// Driver code
int main() {
    
    char buffer[MAXLINE];
    char *hello = "Hello from client";
char buf[MAX];
    pthread_t sendt,recvt;
    
 
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    memset(&servaddr, 0, sizeof(servaddr));
     
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
     
    int  len,op,s;
    
    

char inp[50];
inp[0]='I';
inp[1]='\0';

	pthread_create(&recvt,NULL,recvmg,&servaddr);
	len = sendto(sockfd, (const char *)inp, strlen(inp),
			        	MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			            	sizeof(servaddr));
					if(len < 0) {
						perror("message not sent");
						exit(1);
					}
	len = sendto(sockfd, (const char *)inp, strlen(inp),
			        	MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			            	sizeof(servaddr));
					if(len < 0) {
						perror("message not sent");
						exit(1);
					}
while(1)
{
printf("Menu:\n");
printf("1. Update\n");
printf("2. Delete\n");
printf("3. Show IP table\n");
fflush(stdin);
scanf("%d*[^\n]", &op);
//fflush(stdin)
switch(op)
	{
		case 1: fflush(stdout);
		            printf("enter the destination ip:\n");
		            
					//fgets(buffer,500,stdin);
					scanf("%s",inp);
					printf("your input:%ld",strlen(inp));

					char *str = inp, *str2;
    				int value[4] = {0};
   					 size_t index = 0;
    				str2 = str; /* save the pointer */
    				while (*str)
    				 {
				        if (isdigit((unsigned char)*str)) 
				        {
				            value[index] *= 10;
				            value[index] += *str - '0';
				        }
				         else 
				         {
				            index++;
				        }
				        str++;
				    }
				    
					printf("values in \"%s\": %d %d %d %d\n", str2, value[0], value[1], value[2], value[3]);
						
					len = sendto(sockfd, (const char *)inp, strlen(inp),
			        	MSG_CONFIRM, (const struct sockaddr *) &servaddr, 
			            	sizeof(servaddr));
					if(len < 0) {
						perror("message not sent");
						exit(1);
					}
					memset(buffer,'\0',sizeof(buffer));
					//memset(res,'\0',sizeof(res));
				push(&head,value,'A');
				break;
		case 2: printf("uwgscusduk\n");
				break;
		case 3: printList(head);
				break;
		default : 
					printf("U failed to be human, there are only three options and i am switch case :) :) :) \n");
					continue;

	}
}
pthread_join(recvt,NULL);
   

close(sockfd);
   return 0;
}
