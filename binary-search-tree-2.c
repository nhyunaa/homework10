/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { // 구조체node
	int key; // 정수형 변수 key 선언
	struct node *left; // 구조체 포인터 left선언
	struct node *right; // 구조체 포인터 right 선언
} Node;

/* for stack */
#define MAX_STACK_SIZE 20 
Node* stack[MAX_STACK_SIZE];
int top = -1; // top을 -1로 초기화

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;



int initializeBST(Node** h);
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* functions that you have to implement */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int deleteNode(Node* head, int key);  /* delete the node for the key */
Node* pop();
void push(Node* aNode);
Node* deQueue();
void enQueue(Node* aNode);

/* you may add your own defined functions if necessary */


void printStack();



int main()
{
	char command; // char형 변수command 선언
	int key; // int형 변수 key선언
	Node* head = NULL; //  구조체 포인터 head선언 및 NULL로 초기화

	do{
        printf("[----- [노현아] [2022041065] -----]");
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);// 사용자로부터 command입력받기

		switch(command) {
		case 'z': case 'Z': //command가 z 이거나 Z인경우
			initializeBST(&head); // inintalizeBST함수 호출
			break;
		case 'q': case 'Q': // command가 q이거나Q인경우
			freeBST(head); // freeBST함수 호출
			break;
		case 'i': case 'I': // command가 i이거나I인경우
			printf("Your Key = ");
			scanf("%d", &key); // key입력받기
			insert(head, key); // insert함수 호출
			break;
		case 'd': case 'D':// command가 d이거나 D인경우
			printf("Your Key = ");
			scanf("%d", &key); // key입력받기
			deleteNode(head, key); // deleteNode함수 호출
			break;

		case 'r': case 'R': // command가 r이거나 R인경우
			recursiveInorder(head->left); // recursiveInorder함수 호출
			break;
		case 't': case 'T': // command가 t 이거나 T인경우 
			iterativeInorder(head->left); // iterativeInorder함수 호출
			break;

		case 'l': case 'L': // command가 l이거나 L 인경우
			levelOrder(head->left); // levelOrder함수호출
			break;

		case 'p': case 'P':// command가 p이거나 P 인경우
			printStack(); // printStack함수 호출
			break;

		default: //위의 command를 제외
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //집중하라는 메세지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); // command가 q와Q아닌경우에 반복

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) // head
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));//포인터 변수h에 Node만큼 메모리 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; // h를 h의 right로 대입
	(*h)->key = -9999; // h의 key값을 -9999로 초기화
	top = -1; // top을 -1로 초기화

	front = rear = -1; // front 와 rear도 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr) // 중위순회
{
	if(ptr) {
		recursiveInorder(ptr->left);//재귀함수를 통해서 ptr을 왼쪽자식으로 가르킴
		printf(" [%d] ", ptr->key);//ptr의 key값을 출력
		recursiveInorder(ptr->right);//재귀함수를 통해서 ptr을 오른쪽 자식으로 가르킴
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //반복적 중위 순회
{
	for(;;) //무한루프
	{
		for(; node; node = node->left) //node가NULL이 아니면 실행 노드를 왼쪽자식으로 바꿈
			push(node); //스택에 삽입
		node = pop(); //스택에서 삭제

		if(!node) break; //공백 스택일때 멈춤
		printf(" [%d] ", node->key);

		node = node->right; //현재노드의 오른쪽자식을 가르킴 
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr)//레벨순서 순회 
{
	// int front = rear = -1;

	if(!ptr) return; /* empty tree */

	enQueue(ptr);//ptr을 큐안에 입력

	for(;;)//무한 루트
	{
		ptr = deQueue();//큐에서 빠져나온 노드가 ptr
		if(ptr) {//ptr이 NULL 이아니면
			printf(" [%d] ", ptr->key);//ptr의 key갑 출력

			if(ptr->left)//ptr의 왼쪽 자식이 있으면
				enQueue(ptr->left);//큐안에 ptr왼쪽자식 입력
			if(ptr->right)//ptr의 오른쪽 자식이 있으면
				enQueue(ptr->right);//큐안에 ptr오른쪽 자식 입력
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));//새로운 노드를 메모리를 노드만큼 할당
	newNode->key = key;//새로운노드의 key값에 입력받은 key값을 대입
	newNode->left = NULL;//새로운노드의 왼쪽자식은 NULL로 초기화
	newNode->right = NULL;//새로운노드의 오른쪽 자식은 NULL로 초기화

	if (head->left == NULL) {//헤드왼쪽자식이 NULL이면 즉 처음 노드를 입력받는 다면
		head->left = newNode;//헤드노드의 왼쪽자식이 새로운노드를 가르키게함
		return 1; // 1반환
	}

	/* head->left is the root */
	Node* ptr = head->left;//ptr은 head노드의 왼쪽 자식

	Node* parentNode = NULL;//parentNOde는 NULL로 초기화
	while(ptr != NULL) {//ptr이 NULL일??까지 반복

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;//입력받은 키값이 이미 있으면 함수종료

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; // ptr을 parentNode에 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)//입력받은 키값이 ptr의 키값보다 크면
			ptr = ptr->right;//ptr을 ptr의 right로 바꿈
		else//입력받은 키값이 ptr의 키값보다 작으면
			ptr = ptr->left;//ptr을 ptr의left로 바꿈
	}

	/* linking the new node to the parent */
	if(parentNode->key > key)//parent노드의 키값이 입력받은 키값보다 크면
		parentNode->left = newNode;//새로운노드를 parent노드의 왼쪽자식으로 가르키게함
	else
		parentNode->right = newNode;//새로운노드를 parent노드의 오른쪽자식으로 가르키게함
	return 1;
}

int deleteNode(Node* head, int key)
{
	if (head == NULL) {//initializeBST함수를 사용하지 않은경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//입력받은 노드가 없는경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* root = head->left;//root는 첫번째 입력받은 노드



	Node* parent = NULL; // parent를 NULL로 초기화
	Node* ptr = root; // ptr을 root로 초기화

	while((ptr != NULL)&&(ptr->key != key)) {//ptr이NULL이거나 ptr의key값이 입려받은 key값이랑 같을 때까지반복
		if(ptr->key != key) {//ptr의 key값이 입력받은 key값이랑 다른경우

			parent = ptr;	/* save the parent */

			if(ptr->key > key)//ptr의 key값이 입력받은 key값보다 큰경우
				ptr = ptr->left;//ptr을 ptr의left로 바까줌
			else
				ptr = ptr->right;//ptr을 ptr의 right로 바까줌
		}
	}   

/* there is no node for the key */
	if(ptr == NULL) // ptr값이 NULL일때
	{
		printf("No node for key [%d]\n ", key); // key값 출력
		return -1;
	}

	/*
	 * case 1: the node which has to be removed is a leaf node
	 */
	if(ptr->left == NULL && ptr->right == NULL)//ptr의 왼쪽자식이랑 오른쪽자식이 없는경우 즉 ptr이 leaf노드 인경우
	{
		if(parent != NULL) { /* parent exists, parent's left and right links are adjusted */
			if(parent->left == ptr)//parent왼쪽자식이 ptr인경우
				parent->left = NULL;//parnt왼쪽자식을 제거
			else
				parent->right = NULL;//parnt의 오른쪽 자식을 제거
		} else {
			/* parent is null, which means the node to be deleted is the root */
			head->left = NULL;//head의왼쪽 자식을 제거 즉 root를 제거

		}

		free(ptr);//ptr을 메모리할당 해제
		return 1;
	}

	/**
	 * case 2: if the node to be deleted has one child
	 */
	if ((ptr->left == NULL || ptr->right == NULL))//ptr의 자식이 하나 있는경우
	{
		Node* child;
		if (ptr->left != NULL)//ptr의 왼쪽 자식이 있는경우
			child = ptr->left;//child 를  ptr의 왼쪽자식으로 함
		else
			child = ptr->right;//child를 ptr의 오른 쪽 자식으로함

		if(parent != NULL)//parent노드가 NULL이 아닐경우
		{
			if(parent->left == ptr)//parent 왼쪽자식이 ptr일경우
				parent->left = child;//parent 왼쪽 자식을 child를 가르키게함
			else//parent 오른쪽 자식이 ptr일 경우
				parent->right = child;//parent오른쪽 자식을 child를 가르키게함
		} else {
			/* parent is null, which means the node to be deleted is the root
			 * and the root has one child. Therefore, the child should be the root
			 */
			root = child; // root값을 child값으로 바꿈
		}

		free(ptr);//ptr메모리할당 해제
		return 1;
	}

	/**
	 * case 3: the node (ptr) has two children
	 *
	 * we have to find either the biggest descendant node in the left subtree of the ptr
	 * or the smallest descendant in the right subtree of the ptr.
	 *
	 * we will find the smallest descendant from the right subtree of the ptr.
	 *
	 */

	Node* candidate; //구조체 포인터  candidate선언
	parent = ptr; // parent값을 ptr값으로 바꿈


	candidate = ptr->right;//candidate 를 ptr의 오른쪽 자식으로함

	/* the smallest node is left deepest node in the right subtree of the ptr */
	while(candidate->left != NULL)//candiate의 왼쪽자식이 NULL일때 까지 반복
	{
		parent = candidate;//parnt를 candidate로 바까줌
		candidate = candidate->left;//candidate를 candidate왼쪽자식으로 바까줌
	}

	/* the candidate node is the right node which has to be deleted.
	 * note that candidate's left is null
	 */
	if (parent->right == candidate)//parnet의 오른쪽자식이candiate일경우
		parent->right = candidate->right;//parent오른쪽자식은 candidate의 오른쪽자식
	else
		parent->left = candidate->right;//parent왼쪽자식은 candidate의 오른쪽자식

	/* instead of removing ptr, we just change the key of ptr
	 * with the key of candidate node and remove the candidate node
	 */

	ptr->key = candidate->key;//ptr의 키값을 candidate의 key값으로 바까줌

	free(candidate); // free함수 호출
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);//ptr의 왼쪽 노드 메모리 할당 해제
		freeNode(ptr->right);//ptr의 오른쪽 노드 메모리 할당 해제
		free(ptr);//ptr 메모리 할당 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//head의 왼쪽노드가 head라면
	{
		free(head);//head메로리 할당 해제
		return 1;
	}

	Node* p = head->left;//포인터 p변수를 head의 왼쪽 자식으로 함,즉p는 root노드

	freeNode(p);//root노드 메모리 할당해제

	free(head);//head 메모리 할당 해제
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL; // top의 값이 0보다 작으면 NULL반환
	return stack[top--];//stack의 top을 리턴해주고 top값을 -1해줌
}

void push(Node* aNode)
{
	stack[++top] = aNode;//stack의 top값에 +1을 해준 곳에 aNode 입력
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top) // i가 top보다 작거나 같을때 반복
	{
		printf("stack[%d] = %d\n", i, stack[i]->key); // i와 stack[i]의 key값출력
	}
}


Node* deQueue()
{
	if (front == rear) { // front 와 rear의 값이 동일할때
		// printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];//큐배열의 front 인덱스 번호 리턴

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) { // front와 rear값이 동일하면
		// printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;//큐의 rear에 aNode값을 대입
}



