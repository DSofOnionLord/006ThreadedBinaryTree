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

//�Է� �޴´�.
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
	//root����
	root = (tree)malloc(sizeof(*root));

	root->next = NULL;
	root->parent = NULL;
	root->rc = root;
	root->lc = root;
	root->lt = 1;
	root->rt = 0;
	node = root;
	
	//0�� ������ n���� �Է¹޾� Insert
	for ( i = 0 ; i < n ; )
	{
		fscanf(fin, "%d", &tmp);
		if(tmp != 0)
		{
			i++;
		}
		insert(&root, &node, tmp);
	}

	//�Ϲ� linked list�� Binary Tree�� �����.
	//f��ġ�� node�̸� r+1�� Left Child, r+2�� Right Child�����̴�.
	//front�����Ϳ� rear�����ʹ� �������� ������ front�����ʹ� �� ����� 1ĭ, rear�����ʹ� �� ����� 2ĭ �̵��Ѵ�.
	//Queue����� ����.
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