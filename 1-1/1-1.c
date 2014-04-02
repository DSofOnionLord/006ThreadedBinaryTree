#include<stdio.h>
#include<stdlib.h>

typedef struct tr * tree;
struct tr
{
	int val;
	tree parent;
	tree lc;
	tree rc;
	tree next;
	int lt;
	int rt;
};

//입력 받는다.
void insert(tree *root, tree *node, int val)
{
	tree temp;
	temp = (tree)malloc(sizeof(*temp));
	temp->val = val;
	temp->next = (*node)->next;
	temp->lc = NULL;
	temp->rc = NULL;
	temp->lt = 0;
	temp->rt = 0;
	temp->parent = NULL;
	(*node)->next = temp;
	(*node) = temp;
}


void inorder(tree tre)
{
	tree temp = tre;
	if(temp)
	{
		inorder(temp->lc);
		printf("%d ", temp->val);
		inorder(temp->rc);
	}

}

void rip(tree *tre)
{
	tree temp = *tre;
	(*tre) = (*tre)->next;
	free(temp);
}

int main()
{
	FILE * fin = fopen("input.txt", "r");
	tree root;
	tree node;
	tree rear, front;

	int n, tmp;
	int i;
	int p, l, r;

	fscanf(fin, "%d", &n);
	//root지정
	root = (tree)malloc(sizeof(*root));

	root->next = NULL;
	root->parent = NULL;
	root->rc = root;
	root->lc = root;
	root->lt = 1;
	root->rt = 0;
	node = root;
	
	//0을 제외한 n개를 입력받아 Insert
	for ( i = 0 ; i < n ; )
	{
		fscanf(fin, "%d", &tmp);
		if(tmp != 0)
		{
			i++;
		}
		insert(&root, &node, tmp);
	}

	//일반 linked list를 Binary Tree로 만든다.
	//f위치가 node이면 r+1은 Left Child, r+2는 Right Child형식이다.
	//front포인터와 rear포인터는 시작점은 같지만 front포인터는 한 연산당 1칸, rear포인터는 한 연산당 2칸 이동한다.
	//Queue방식을 응용.
	front = root->next;
	rear = root->next;
	
	while(1)
	{
		l = 0;
		r = 0;
		if(rear->next != NULL)
		{
			rear = rear->next;
			if(rear->val != 0 )
			{
				rear->parent = front;
				front->lc = rear;
			}
			l = rear->val;
		}

		if(rear->next != NULL)
		{
			rear = rear->next;
			if(rear->val != 0)
			{
				rear->parent = front;
				front->rc = rear;
			}
			r = rear->val;
			
		}

		p = front->val;

		front = front->next;
		if(front == NULL)
		{
			break;
		}
	}
	
	//inorder((root->next));

	rip(&root);
	//free(root);
	fclose(fin);
	return 0;
}