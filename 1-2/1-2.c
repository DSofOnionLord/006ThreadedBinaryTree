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

//Binary Tree를 위해서 예비로 Linked List를 Insert한다.
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

//Thread Binary Tree를 만들기 위한 예비 작업으로 Inorder된 결과를 Linked List에 Insert한다.
void re_insert(tree *node, tree inp)
{
	(inp)->next = (*node)->next;
	(*node)->next = (inp);
	(*node) = (inp);
}
//Thread Binary Tree를 만들기 위한 예비 작업으로 Inorder연산을 하면서 그 결과를 Linked List에 Insert한다.
void inorder(tree tre, tree *root)
{
	tree temp = tre;
	if(temp)
	{
		inorder(temp->lc, root);
		re_insert(root, temp);
		inorder(temp->rc, root);
	}

}

//Inorder된 결과과가 있는 Linked List를 바탕으로 Binary Tree를 Thread Binary Tree로 변환시킨다.
void ttree(tree *root, tree *node)
{
	tree temp;
	temp = (*node);
	while(1)
	{

		if(temp->rt == 1)
		{
			if(temp->next == NULL)
			{
				temp->rc = *root;
			}
			else
			{
				temp->rc = temp->next;
			}
		}
		if(temp->next == NULL)
		{
			break;
		}
		if(temp->next->lt == 1)
		{
			temp->next->lc = temp;
		}
		temp = temp->next;
	}
}

//데이터 동적할당 헤제.
void rip(tree *tre)
{
	tree temp = *tre;
	(*tre) = (*tre)->next;
	free(temp);
}

//Inorder연산
tree insucc(tree root)
{
	tree temp = (root)->rc;
	if((root)->rt == 0)
	{
		while(temp->lt == 0)
		{
			temp = temp->lc;
		}
	}
	return temp;
}
//Inorder연산
void tinorder(tree *root)
{
	FILE * out = fopen("output.txt", "w");
	tree temp = *root;
	
	while(1)
	{
		temp = insucc(temp);
		if(temp == (*root))
		{
			break;
		}
		fprintf(out,"%-5d", temp->val);
		if(temp->lt == 1)
		{
			fprintf(out,"(LTH ");
			if(temp->lc == (*root))
			{
				fprintf(out," Root)");
			}
			else
			{
				fprintf(out,"%5d)", temp->lc->val);
			}
		}
		else
		{
			fprintf(out,"(LCH %5d)", temp->lc->val);
		}
		if(temp->rt == 1)
		{
			fprintf(out,"(RTH");
			if(temp->rc == (*root))
			{
				fprintf(out," Root)");
			}
			else
			{
				fprintf(out,"%5d)", temp->rc->val);
			}
		}
		else
		{
			fprintf(out,"(RCH %5d)", temp->rc->val);
		}
		fprintf(out,"\n");
	}
	fclose(out);
}


int main()
{
	FILE * fin = fopen("input.txt", "r");
	tree root;
	tree node;
	tree rear, front;
	tree copied;
	tree tbt;

	int n, tmp;
	int i;
	int p, l, r;

	fscanf(fin, "%d", &n);

	root = (tree)malloc(sizeof(*root));

	root->next = NULL;
	root->parent = NULL;
	root->rc = root;
	root->lc = root;
	root->lt = 0;
	root->rt = 0;
	root->val = 666;
	node = root;
	
	//일반 linked list로 입력.
	for ( i = 0 ; i < n ;  )
	{
		fscanf(fin, "%d", &tmp);
		if(tmp != 0)
		{
			i++;
		}
		insert(&root, &node, tmp);
	}

	
	front = root->next;
	if(n >= 1)
	{
		root->lc = root->next;
	}
	rear = root->next;
	
	//일반 linked list를 Binary Tree로 만든다.
	//f위치가 node이면 r+1은 Left Child, r+2는 Right Child형식이다.
	//front포인터와 rear포인터는 시작점은 같지만 front포인터는 한 연산당 1칸, rear포인터는 한 연산당 2칸 이동한다.
	//Queue방식을 응용.

	//Thread Binary Tree대비하여
	//Left Child가 없을때 Left Thread = 1, Right Child 없을때 Right Thread = 1하는 작업도 있다.
	while(1)
	{
		l = 0;
		r = 0;
		if(rear->next != NULL)
		{
			rear = rear->next;//rear을 한번 next로 이동.
			if(rear->val != 0 )//rear포인터가 가리키는 값이 0이면 무시하고 뒤로 이동.
			{
				rear->parent = front;
				front->lc = rear;
			}
			else
			{
				front->lt = 1;
			}
			l = rear->val;
		}
		else
		{
			front->lt = 1; //값이 없을 경우 Left Thread를 활성화
		}

		if(rear->next != NULL)
		{
			rear = rear->next;//rear을 다시 한번 next로 이동.
			if(rear->val != 0)//rear포인터가 가리키는 값이 0이면 무시하고 뒤로 이동.
			{
				rear->parent = front;
				front->rc = rear;
			}
			else
			{
				front->rt = 1;
			}

			r = rear->val;
		}
		else
		{
			front->rt = 1;//값이 없을 경우 Right Threead를 활성화
		}

		p = front->val;

		front = front->next;
		if(front == NULL)
		{
			break;
		}
	}

	//inorder연산을 하면서 Thread Binary Tree연산을 하도록 준비한다.
	//Tree를 만들기 위한 예비 Linked List를 버리고 Thread BT를 위한 Linked List로 만든다.
	copied = root;
	inorder((root->next), &copied);
	copied->next = NULL;

	//만들어진 Thread BT를 바탕으로 Inorder방식으로 출력한다.
	copied = root;
	ttree(&root, &copied);
	tinorder(&root);
	
	//동적할당된 것들을 정리한다.
	rip(&root);
	//free(root);
	fclose(fin);
	return 0;
}