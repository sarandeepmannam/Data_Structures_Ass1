#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100 /*Max no of songs can be added in library */
#define LENGTH 20 /*max name size of each song */

//  linked list node (song)
struct Node
{
  char *song_name;
  struct Node *next;
};
 typedef struct Node node;
//function to add a node to linked list at head i.e the added node becomes new head 
void push(struct Node** head_ref, char* arr)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->song_name  = arr;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}
 
// function to add a node after a particular node
void insertAfter(struct Node* prev_node, char*new_data)
{
    
    if (prev_node == NULL)
    {
      printf("the given previous node cannot be NULL");
      return;
    }
    struct Node* new_node =(struct Node*) malloc(sizeof(struct Node)); 
    new_node->song_name  = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
}
 //function to add a node at end of the list
void append(struct Node** head_ref, char* new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
 
    struct Node *last = *head_ref;  
    new_node->song_name  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
    return;
}
 
// This function prints contents of linked list starting from head
void printList(struct Node *node)
{
  while (node != NULL)
  {
     printf("%s\n", node->song_name);
     node = node->next;
  }
}
 //To find length of linked list
int getCount(struct Node* head)
{
    int count = 0;  
    struct Node* current = head;  
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}
struct Queue {
    int front, rear, size;
    
    char arr[SIZE][LENGTH];//char arr[100][20];
};
 typedef struct Queue queue;

struct Queue* createQueue()
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->front = queue->size = 0;
    queue->rear = SIZE-1;
    return queue;
}
 
// Queue is full when its size = SIZE

int isFull(struct Queue* queue)
{
    return (queue->size == SIZE);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, char item[LENGTH])
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % SIZE;
    strcpy((queue->arr[queue->rear]),item);
    queue->size = queue->size + 1;
    //printf("%s enqueued to queue\n", item);
}
 //Function to take out the front item from queue
 //It changes front and size
char* dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return "No elements to dequeue";
    int k= queue->front;
    queue->front = (queue->front + 1)
                   % SIZE;
    queue->size = queue->size - 1;
    return queue->arr[k];
}
 
// Function to get front of queue
char* front(struct Queue* queue)
{
    if (isEmpty(queue))
        return "Queue is empty!";
    return queue->arr[queue->front];
}
 
// Function to get rear of queue 
char* rear(struct Queue* queue)
{
    if (isEmpty(queue))
        return "Queue is empty!";
    return queue->arr[queue->rear];
}
struct Stack {
    int top;
    unsigned capacity;
    char k[SIZE][LENGTH];
};
 typedef struct Stack stack;
// function to create a stack of given capacity.
struct Stack* createStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = SIZE;
    stack->top = -1;
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull1(struct Stack* stack)
{
    return stack->top == stack->capacity - 1;
}
 
// Stack is empty when top is equal to -1
int isEmpty1(struct Stack* stack)
{
    return stack->top == -1;
}
 
// Function to add a song to stack.  It increases top by 1
void push1(struct Stack* stack, char item[])
{
    if (isFull1(stack))
    return;
    else{
    strcpy(stack->k[++stack->top],item);
    printf("%s pushed to recent songs stack\n", item);}
}
 
// Function to remove a song from stack.  It decreases top by 1
char* pop(struct Stack* stack)
{
    if (isEmpty1(stack))
        return "\nthere weren't that many songs";
    return stack->k[stack->top--];
}
 
// Function to return the top from stack without removing it
char* peek(struct Stack* stack)
{
    if (isEmpty1(stack))
        return "stack is empty";
    return stack->k[stack->top];
}
//Function for creating a playlist
void create_playlist(queue*q,char a[SIZE][LENGTH],int n)
{
   char arr[100][20];
  int k=0;
 for(int i=0;i<100;i++)
 {
   printf("enter the song to be added in the playlist,end with -1\n");
   scanf("%s",arr[i]);
   if(strcmp(arr[i],"-1")==0 && q->size==0)
   {
     printf("no songs entered in playlist\n");
     break;
   }
   else if(strcmp(arr[i],"-1")==0 && q->size!=0)
   {
     printf("playlist is ready\n");break;
   }
   else 
   {
     for(int j=0;j<n;j++){
     if(strcmp(arr[i],a[j])==0)
     {
       enqueue(q,a[j]);
       k=1;
     }
     }
     if(k==1)
     {
       printf("found,enqueued!\n");
       k=0;
     }
     else{printf("song not found\n");}
   }
   
 }
}
//function to play next song
void play_next(queue *q,stack *s)
{
  if(isEmpty(q))
  {
  printf("no more songs in playlist\n");
  return;
  }
  else
  {
    printf("playing %s\n",dequeue(q));
    push1(s,q->arr[(q->front)-1]);
  }
}
//Function to play previous songs
void play_previous(stack* s,int n)
{
  int count=0;
  queue *q=NULL;
  q=createQueue();
  while(s->top!=-1&&count< n)
  {
    enqueue(q,peek(s));
   printf("playing %s\n",pop(s));
   
   count=count+1;
  }
  if(count<n)
  {
    printf("there weren't %d previous songs\n",n);
  }
  while(q->size>0)
  {
    push1(s,dequeue(q));
  }
}
//Function to play songs
void play(stack *s,queue* q)
{
  char a[10];
  printf("enter 'n' for play next\n");
  printf("enter 'p' for play previous\n");
  scanf("%s",a);
  if(strcmp(a,"n")==0)
  {
   play_next(q,s);
   play(s,q);
  }
  else if(strcmp(a,"p")==0)
  {
    int i;
    printf("enter no of previous songs to be played\n");
    scanf("%d",&i);
    play_previous(s,i);
    play(s,q);
  }
  else
  {
    printf("Thank you,Bye!");
  }
  
}

int main()
{
  
  node* Songs_head=NULL;
  printf("Enter the name of the songs to be added in the library,end with -1\n");
  char a[SIZE][LENGTH];
  for(int i=0;i<SIZE;i++)
  {
    
    scanf("%s",a[i]);
    if(strcmp(a[i],"-1")==0&& Songs_head==NULL)
    {
      printf("No songs entered\n");
      break;
    }
     if(strcmp(a[i],"-1")==0&& Songs_head!=NULL )
    {
      printf("All songs entered\n");
      break;
    }
    else {
      append(&Songs_head,a[i]);
    }
  }
  if(Songs_head!=NULL)
  {
  printf("\nCreated library of songs is: \n");
  printList(Songs_head);}
  int n=getCount(Songs_head);
  printf("\nTotal no of songs in the the library is:%d\n",n);

  queue* q=NULL;
  q=createQueue();
 
 create_playlist(q,a,n);
 
stack *s=NULL;
 s=createStack();
 
 play(s,q);

  return 0;
};