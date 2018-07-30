// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT     8080
#define MAXLINE 1024


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


int clients[1024];
int n = 0;
int z;
char *hello = "Hello from server";

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 /*void sendtoall(int curr, struct sockaddr_in* cliaddr,int sockfd)
{
	int i,len;
//	pthread_mutex_lock(&mutex);
	len=sizeof(struct sockaddr_in);
	for(i = 0; i < n; i++) {
		 {
			printf("%d: port no\n",clients[i]);
			cliaddr->sin_port=htons(clients[i]);
			cliaddr->sin_family    = AF_INET; // IPv4
    			cliaddr->sin_addr.s_addr = inet_addr("127.0.0.1");
			if(sendto(sockfd, (const char *)hello, strlen(hello), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len) < 0) {
				perror("sending failure");
				continue;
			}
		}
	}
//	pthread_mutex_unlock(&mutex);
}*/
// Driver code
int main() {
    int sockfd,len; 
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;
     
    // Creating socket file descriptor
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
     
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
     
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
     
    // Bind the socket with the server address
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
            sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
  int i,p ;   
    
	while(1)
{
    z = recvfrom(sockfd, (char *)buffer, MAXLINE, 
                MSG_WAITALL, ( struct sockaddr *) &cliaddr,
                &len);
int now;
buffer[z] = '\0';
if(strlen(buffer)==1 && buffer[0]=='I')
{

        for(i=0; i<=n;i++)
            {
                printf("%d\n value of j:",n);
                if(clients[i]==cliaddr.sin_port)
                    break;
            }
        if(i>n)
            {
                clients[--i]=cliaddr.sin_port;
                n++;
            }
        for(int k =0; k<=n;k++)
            {
                printf("\n%d\n",clients[k]);
            }
            if(p=sendto(sockfd, (const char *)buffer, strlen(buffer), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len) < 0) {
                perror("sending failure");
                continue;
            }
            else
                printf("%d\n",p );
}


else{ 
    printf("Client : %s\n", buffer);
    now=cliaddr.sin_port;
	for(i = 0; i < n; i++) {
		 
			if(now!=clients[i]){
            printf("%d \t %d: port no,iteration\n",clients[i],i);
			cliaddr.sin_port=(clients[i]);
			/*cliaddr.sin_family    = AF_INET; // IPv4
    			cliaddr.sin_addr.s_addr = inet_addr("127.0.0.1");*/

			printf("\ndoomed\n");
			printf(": %s\n", inet_ntoa(cliaddr.sin_addr));
			printf(": %d\n",(cliaddr.sin_port));
			printf("%c \n",cliaddr.sin_zero);
           /* if( sendto(sockfd, (const char *)hello, strlen(hello), 
       MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
          len))
                printf("\n sent 3\n");
			*/if(p=sendto(sockfd, (const char *)buffer, strlen(buffer), 
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr,
            len) < 0) {
				perror("sending failure");
				continue;
			}
            else
                printf("%d\n",p );
	}	
	}   
 printf("message sent.\n"); 

 }
}    
    return 0;
}
