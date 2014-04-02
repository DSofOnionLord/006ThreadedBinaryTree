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
	tree copied;
	int lt;
	int rt;
};

//Binary Tree�� ���ؼ� ����� Linked List�� Insert�Ѵ�.
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

//Thread Binary Tree�� ����� ���� ���� �۾����� Inorder�� ����� Linked List�� Insert�Ѵ�.
void re_insert(tree *node, tree inp)
{
	(inp)->next = (*node)->next;
	(*node)->next = (inp);
	(*node) = (inp);
}
//Thread Binary Tree�� ����� ���� ���� �۾����� Inorder������ �ϸ鼭 �� ����� Linked List�� Insert�Ѵ�.
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

//Inorder�� ������� �ִ� Linked List�� �������� Binary Tree�� Thread Binary Tree�� ��ȯ��Ų��.
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

//������ �����Ҵ� ����.
void rip(tree *tre)
{
	tree temp = *tre;
	(*tre) = (*tre)->next;
	free(temp);
}

//Inorder����
tree insucc(tree root)
{
	tree temp = (root)->rc;
	//printf("%d %d %d \n", root->val,root->rt,root->lt);
	if((root)->rt == 0)
	{
		while(temp->lt == 0)
		{
			temp = temp->lc;
		}
	}
	return temp;
}
//Inorder����
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
//Inorder������� ���鼭 �ش� ���� �ִ� NODE�� ã�´�. => return�ؼ� �� ��ġ�� �߰��Ϸ��� ���� �ִ´�. �ߺ��� ���� �ִ� ��� ���� ã����.
tree tinsearch(tree *root, int val)
{
	tree temp = *root;
	while(1)
	{
		temp = insucc(temp);
		if(temp == (*root))
		{
			return NULL;
		}
		if(temp->val == val)
		{
			return temp;
		}
		
	}

}

//tinsearch�� ã�� node�� �������� ���� �߰� �����ش�.
void tadd(tree node, int val)
{
	FILE * out = fopen("output.txt", "w");
	tree temp;
	tree s_nod;
	temp = (tree)malloc(sizeof(*temp));

	if(node->rc != NULL && node->rt == 0)
	{
		//�־��ֱ�.
		//���� node�� RCH�� ����.
		temp->val = val;
		temp->rc = node->rc;
		temp->rt = 0;
		//node�� node�� parent�� ����.
		temp->parent = node;
		node->rc = temp;
		node->rt = 0;
		
		s_nod = temp->rc;
		while(1)
		{
			if(s_nod->lt == 1)//������ ������ ���
			{
				//node�� rch�� lch������ �������� �ű��� lch�� node���� ���.
				//������� lch�� lch�� node�� ����Ŵ.
				temp->lt = s_nod->lt;
				temp->lc = s_nod->lc;
				s_nod->lc = temp;
				break;
			}
			s_nod = s_nod->lc;
		}
	}
	else
	{
		temp->val = val;
		temp->lc = node;
		temp->lt = 1;
		temp->rc = node->rc;
		temp->rt = 1;
		node->rc = temp;
		node->rt = 0;
	}

	fclose(out);

}
//tinserach�� ã���Ÿ� �������� node�� �����Ѵ�. ���õ� ���� ������ ��带 ����. �ߺ��� ��� ���� ���°� ����
//��, Child Node�� �ִ� ��� �ִ��� Child Node�� �����ϴ� ������ �Ͽ���.
void tdel(tree node)
{
	tree temp = node;
	tree tm, ltm;
	
	if(node->lt == 1 && node->rt == 1)//RCH LCH ������ parent���� ������ Link�� �ش�.
	{
		if(node == node->parent->rc)
		{
			node->parent->rc = node->rc;
			node->parent->rt = node->rt;
		}
		else if(node == node->parent->lc)
		{
			node->parent->lc = node->lc;
			node->parent->lt = node->lt;
		}
	}
	else//node�� LCH RCH������
	{
		//node�� Lch�� Rch�� �� �κб��� ����.

		ltm = node->lc;
		tm = node->rc;
		while(1)
		{
			if(ltm->rt == 1)
			{
				if(ltm->lt == 1)//�ǳ� ������ LCH������
				{
					ltm->parent->rt = 1;
				}
				else//������
				{
					ltm->parent->rc = ltm->lc; 
				}
				ltm->rc = node->rc;
				ltm->rt = node->rt;
				ltm->lc = node->lc;
				ltm->lt = node->lt;
				ltm->parent = node->parent;//�ش� node�� ��ü�Ѵ�.
				
				if(node == node->parent->rc)//parent node�� ����.
				{
					node->parent->rc = ltm;
				}
				else if(node == node->parent->lc)
				{
					node->parent->lc = ltm;
				}

				break;
			}
			ltm = ltm->rc;
		}
		while(1)//���������� �ǳ� LCH�� ������ node�� ����Ű����.
		{
			if(ltm->rt == 1)
			{
				break;
			}
			if(tm->lt == 1)
			{
				tm->lc = ltm;
				break;
			}
			tm = tm->lc;
		}
	}

}


//Thread Binary Tree�� Copy�Ѵ�.
tree copy(tree orig)
{
	tree temp;
	
	if(orig)
	{
		temp = (tree)malloc(sizeof(*temp));
		temp->val = orig->val;
		temp->lt = orig->lt;
		temp->rt = orig->rt;
		orig->copied = temp;//Thread�������� ����ų ���� ����Ͽ� ����� ���� ��ǥ�� �����Ѵ�.

		if(temp->lt == 1)///
		{
			temp->lc = orig->lc->copied;
		}
		else if(temp -> lt == 0)
		{
			temp->lc = copy(orig->lc);
		}
		if(orig->rc != orig)//root�� rc������ ���ѹݺ� ����.
		{
			if(temp->rt == 1)//Thread��
			{
				temp->rc = orig->rc->copied;//������ �ִ� ����� �ּ� Ȱ��
			}
			else if(temp -> rt == 0)//�ƴϸ� ������� ����.
			{
				temp->rc = copy(orig->rc);
			}
		}
		else//root�κп� ���� ����ó��...
		{
			temp->rc = temp;
		}
		//printf("%d %d %d %d %d\n",temp->val, temp->lt, temp->rt, temp->lc->val, temp->rc->val);
		return temp;
	}
	
	return NULL;
}

int main()
{
	FILE * fin = fopen("input.txt", "r");
	tree root;
	tree node;
	tree rear, front;
	tree copied;
	tree copy_result;

	int n, tmp;
	int i;
	int p, l, r;
	int pos,val;

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
	
	//�Ϲ� linked list�� �Է�.
	for ( i = 0 ; i < n ;  )
	{
		fscanf(fin, "%d", &tmp);
		if(tmp != 0)
		{
			i++;
		}
		insert(&root, &node, tmp);
	}
	fscanf(fin, "%c", &tmp);
	
	front = root->next;
	if(n >= 1)
	{
		root->lc = root->next;
	}
	rear = root->next;
	
	//�Ϲ� linked list�� Binary Tree�� �����.
	//f��ġ�� node�̸� r+1�� Left Child, r+2�� Right Child�����̴�.
	//front�����Ϳ� rear�����ʹ� �������� ������ front�����ʹ� �� ����� 1ĭ, rear�����ʹ� �� ����� 2ĭ �̵��Ѵ�.
	//Queue����� ����.

	//Thread Binary Tree����Ͽ�
	//Left Child�� ������ Left Thread = 1, Right Child ������ Right Thread = 1�ϴ� �۾��� �ִ�.
	while(1)
	{
		l = 0;
		r = 0;
		if(rear->next != NULL)
		{
			rear = rear->next;//rear�� �ѹ� next�� �̵�.
			if(rear->val != 0 )//rear�����Ͱ� ����Ű�� ���� 0�̸� �����ϰ� �ڷ� �̵�.
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
			front->lt = 1; //���� ���� ��� Left Thread�� Ȱ��ȭ
		}

		if(rear->next != NULL)
		{
			rear = rear->next;//rear�� �ٽ� �ѹ� next�� �̵�.
			if(rear->val != 0)//rear�����Ͱ� ����Ű�� ���� 0�̸� �����ϰ� �ڷ� �̵�.
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
			front->rt = 1;//���� ���� ��� Right Threead�� Ȱ��ȭ
		}

		p = front->val;

		front = front->next;
		if(front == NULL)
		{
			break;
		}
	}

	//inorder������ �ϸ鼭 Thread Binary Tree������ �ϵ��� �غ��Ѵ�.
	//Tree�� ����� ���� ���� Linked List�� ������ Thread BT�� ���� Linked List�� �����.
	copied = root;
	inorder((root->next), &copied);
	copied->next = NULL;

	//������� Thread BT�� �������� Inorder������� ����Ѵ�.
	copied = root;
	ttree(&root, &copied);
	//tinorder(&root);

	//��ȣ�� �Է¹ް� +�� �߰�, -�� ����
	fscanf(fin,"%c", &tmp);
	if ( tmp == '+')//�߰�
	{
		fscanf(fin, "%d %d", &pos, &val);
		tadd(tinsearch(&root, pos),val);
		
	}
	else if (tmp == '-')//���� -> 1-4���� ����.
	{
		fscanf(fin, "%d", &pos);
		//tinsearch(&root, pos);

	}

	fscanf(fin,"%c", &tmp);//���Ͱ� ó��.

	fscanf(fin,"%c", &tmp);
	if ( tmp == '+')//�߰�
	{
		fscanf(fin, "%d %d", &pos, &val);
		tadd(tinsearch(&root, pos),val);
		
	}
	else if (tmp == '-')//���� -> 1-4���� ����. ���õ� ���� ������ ��带 ����.
	{
		fscanf(fin, "%d", &pos);
		tdel(tinsearch(&root, pos));

	}

	//Thread Binary Tree�� Copy�Ѵ�.
	copy_result = copy(root);
	
	//printf("%d\n", copy_result->rc->val);
	tinorder(&copy_result);
	
	//�����Ҵ�� �͵��� �����Ѵ�.
	rip(&root);
	//free(root);
	fclose(fin);
	return 0;
}