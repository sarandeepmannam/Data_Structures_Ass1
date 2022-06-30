#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
/* A binary tree node has data, pointer to left child
   and a pointer to right child */
struct node {
    char data[20];
    struct node* left;
    struct node* right;
};
 
//  function to create a new node
struct node* newNode(char* data)
{
    struct node* temp
        = (struct node*)malloc(sizeof(struct node));
 
    strcpy(temp->data,data);
    temp->left = temp->right = NULL;
 
    return temp;
}
typedef struct node Node;
// A recursive function to construct Full from pre[].
// preIndex is used to keep track of index in pre[].
struct node* constructTreeUtil(char pre[][20], int* preIndex,
                               int low, int high, int size)
{
    //Base case
    if (*preIndex >= size || low > high)
        return NULL;
 
    // The first node in preorder traversal is root. So take
    // the node at preIndex from pre[] and make it root, and
    // increment preIndex
    struct node* root = newNode(pre[*preIndex]);
    *preIndex = *preIndex + 1;
 
    // If the current subarray has only one element, no need
    // to recur
    if (low == high)
        return root;
 
    // Search for the first element greater than root
    int i;
    for (i = low; i <= high; ++i)
    {
        if (strcmp(pre[i],root->data)>0)
        {
            break;}
            }
 
    // Use the index of element found in preorder to divide
    // preorder array in two parts. Left subtree and right
    // subtree
    root->left = constructTreeUtil(pre, preIndex, *preIndex, i - 1, size);
    root->right
        = constructTreeUtil(pre, preIndex, i, high, size);
 
    return root;
}
 
// The main function to construct BST from given preorder
// traversal. This function mainly uses constructTreeUtil()
struct node* constructTree(char pre[][20], int size)
{
    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, 0, size - 1, size);
}
 
// A utility function to print inorder traversal of a Binary
// Tree
void printInorder(struct node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%s ", node->data);
    printInorder(node->right);
}


 struct node* minValueNode(struct node* node)
{
    struct node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}
Node* deletenode(Node* root, char key[20])
{
    // base case
    if (root == NULL)
        return root;
 
    // If the key to be deleted
    // is smaller than the root's
    // key, then it lies in left subtree
    if (strcmp(key,root->data)<0)
        root->left = deletenode(root->left, key);
 
    // If the key to be deleted
    // is greater than the root's
    // key, then it lies in right subtree
    else if (strcmp(key,root->data)>0)
        root->right = deletenode(root->right, key);
 
    // if key is same as root's key,
    // then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
            
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;

        }
 
        // node with two children:
        // Get the inorder successor
        // (smallest in the right subtree)
        struct node* temp = minValueNode(root->right);
 
        // Copy the inorder
        // successor's content to this node
        strcpy(root->data,temp->data);
 
        // Delete the inorder successor
        root->right = deletenode(root->right, temp->data);
    }
    return root;
}
struct Node
{
    char key[20];
    struct Node *left;
    struct Node *right;
    int height;
};
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Node* newNode1(char key[20])
{
    struct Node* node = (struct Node*)
                        malloc(sizeof(struct Node));
    strcpy(node->key,key);
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key in the subtree rooted
// with node and returns the new root of the subtree.
struct Node* insert(struct Node* node, char key[20])
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode1(key));
 
    if (strcmp(key, node->key)<0)
        node->left  = insert(node->left, key);
    else if (strcmp(key, node->key)>0)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(key,node->left->key)<0)
        return rightRotate(node);
 
    // Right Right Case
   if (balance < -1 && strcmp(key,node->right->key)>0)
        return leftRotate(node);
 
    // Left Right Case
  if (balance > 1 && strcmp(key,node->left->key)>0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
   if (balance < -1 && strcmp(key,node->right->key)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal
// of the tree.
// The function also prints height of every node
void preOrder(struct Node *root)
{
    if(root != NULL)
    {
        printf("%s ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void printInorder1(struct Node* node)
{
    if (node == NULL)
        return;
    printInorder1(node->left);
    printf("%s ", node->key);
    printInorder1(node->right);
}
bool search_node(struct node* node, char key[20])
{
    if (node == NULL)
        return false;
 
    if (strcmp(node->data,key)==0)
        return true;
 
    /* then recur on left subtree */
    bool res1 = search_node(node->left, key);
    // node found, no need to look further
    if(res1) return true;
 
    /* node is not found in left,
    so recur on right subtree */
    bool res2 = search_node(node->right, key);
 
    return res2;
}
struct Node* create_playlist(struct Node* root1,struct node* root)
{
  char arr[100][20];
  int k=0;
 for(int i=0;i<100;i++)
 {
   printf("\nenter the song to be added in the playlist,end with -1\n");
   scanf("%s",arr[i]);
   if(strcmp(arr[i],"-1")==0 && root1!=NULL )
   {
     printf("playlist is ready!\n");
     break;
   }
   else if(strcmp(arr[i],"-1")==0 && root1==NULL)
   {
     printf("no songs entered in the playlist");
     break;
   }
   else
   {
     if(search_node(root,arr[i]))
     {
       root1=insert(root1,arr[i]);
       printf("song founded and added into playlist");
     }
     else
     {
       printf("Song not found in the library");
     }
   }
 }
 return root1;
}
struct Queue {
    int front, rear, size;
    
    char arr[100][20];//char arr[100][20];
};
 typedef struct Queue queue;

struct Queue* createQueue()
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->front = queue->size = 0;
    queue->rear = 100-1;
    return queue;
}
 
// Queue is full when its size = SIZE

int isFull(struct Queue* queue)
{
    return (queue->size == 100);
}
 
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
 
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, char item[20])
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % 100;
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
                   % 100;
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
    char k[100][20];
};
 typedef struct Stack stack;

struct Stack* createStack()
{
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = 100;
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
void store(queue *q,struct Node* root1)//store all the songs in playlist in a queue
{
  if (root1 == NULL)
        return;
    store(q,root1->left);
    enqueue(q,root1->key);
    store(q,root1->right);
}
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

void play(stack *s,queue* q)//function for playing songs
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
//Function for creating a playlist
struct Node * minValueNode1(struct Node* node)
{
    struct Node* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
struct Node* deleteNode(struct Node* root, char key[20])
{
    if (root == NULL)
        return root;
 
    // If the key to be deleted is smaller
    // than the root's key, then it lies
    // in left subtree
    if ( strcmp(key,root->key)<0 )
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater
    // than the root's key, then it lies
    // in right subtree
    else if( strcmp(key,root->key)>0 )
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then
    // This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) ||
            (root->right == NULL) )
        {
            struct Node *temp = root->left ?
                         root->left :
                         root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
            *root = *temp; // Copy the contents of
                           // the non-empty child
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            struct Node* temp = minValueNode1(root->right);
 
            // Copy the inorder successor's
            // data to this node
            strcpy(root->key,temp->key);
 
            // Delete the inorder successor
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }
 
    // If the tree had only one node
    // then return
    if (root == NULL)
    return root;
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + max(height(root->left),
                           height(root->right));
 
    // STEP 3: GET THE BALANCE FACTOR OF
    // THIS NODE (to check whether this
    // node became unbalanced)
    int balance = getBalance(root);
 
    // If this node becomes unbalanced,
    // then there are 4 cases
 
    // Left Left Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);
 
    // Left Right Case
    if (balance > 1 &&
        getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
 
    // Right Right Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);
 
    // Right Left Case
    if (balance < -1 &&
        getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}
    
// Driver code
int main()
{
    FILE *f;
    f=fopen("songs.txt","r");
    if(f==NULL)
    {
      printf("File opening was unsuccessful");
    }
    int k=0;
    char pre[100][20];
    while(!feof(f))
    {
       //fgets(pre[k],100,f);
       fscanf(f,"%s",pre[k]);
       k++;
    }
    fclose(f);
    printf("Given preorder traversal of bst of songs is:\n");
    for(int i=0;i<k;i++)
    {
       printf("%s ",pre[i]);
    }
    int size=k;
 
    struct node* root = constructTree(pre, size);
 
    printf("\nInorder traversal of the songs library is: \n");
    printInorder(root);
   printf("\nenter the songs you hate or you want to delete from library,end with -1\n");
   char a[100][20];
  for(int i=0;i<100;i++)
  {
    
    scanf("%s",a[i]);
    if(strcmp(a[i],"-1")==0)
    {
      break;
    }
    else {
      deletenode(root,a[i]);
    }
  }
   printf("Modified inorder traversal of library of songs is:\n");
   printInorder(root);

  struct Node *root1 = NULL;

 root1=create_playlist(root1,root);
printf("inorder traversal of playlist of songs:\n");
 printInorder1(root1);
printf("\nenter the songs you hate or you want to delete from playlist,end with -1\n");
char a1[100][20];
for(int i=0;i<100;i++)
  {
    
    scanf("%s",a1[i]);
    if(strcmp(a1[i],"-1")==0)
    {
      break;
    }
    else {
      deleteNode(root1,a1[i]);
    }
  }
  printf("Modified inorder traversal of playlist of songs is:\n");
  printInorder1(root1);
  queue* q=NULL;
  q=createQueue();
  store(q,root1);
  stack *s=NULL;
 s=createStack();
 
 play(s,q);

    return 0;
}
