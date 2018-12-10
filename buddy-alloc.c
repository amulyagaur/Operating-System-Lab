#include <stdio.h>
#include <stdlib.h>
int a[100000],flag;
struct mem
{
	int sz;
	int l,r,f;
	int lf;
	struct mem* left,*right;
} *root;
void alloc(int s,struct mem* ptr)
{
	//printf("%d %d %d %d\n",ptr->sz,ptr->l,ptr->r,flag);
	
	if(flag)return;
	if(ptr->f==1 || (ptr->lf && ptr->sz <s ))
	return;
	if( (ptr->sz)/2<s && ptr->lf==1 && ptr->f==0)
	{
		ptr->f=1;
		flag=1;
		for(int i=ptr->l;i<=ptr->r;i++) a[i]++;	
		return;
	}
	else
	{
		if(ptr->left==NULL)
		{
			struct mem* temp=(struct mem*) malloc(sizeof(struct mem));
			temp->sz=(ptr->sz)/2;
			temp->l=ptr->l;
			temp->r=temp->l+temp->sz-1;
			temp->lf=1;
			temp->f=0;
			temp->left=temp->right=NULL;
			ptr->left=temp;
			temp=(struct mem*) malloc(sizeof(struct mem));
			temp->sz=(ptr->sz)/2;
			temp->r=ptr->r;
			temp->l=temp->r-temp->sz+1;
			temp->lf=1;
			temp->f=0;
			temp->left=temp->right=NULL;
			ptr->right=temp;
			ptr->lf=0;
		}
		alloc(s,ptr->left);
		alloc(s,ptr->right);
	}
}

void print()
{
	for(int i=0;i<256;i++)
	{
		printf("%d -> %d\n",i,a[i]);
	}
	printf("\n");
}
int main()
{
	root=(struct mem*)malloc(sizeof(struct mem));
	root->sz=256;
	root->l=0;
	root->r=255;
	root->f=0;
	root->lf=1;
	root->left=root->right=NULL;
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int s;
		scanf("%d",&s);
		flag=0;
		alloc(s,root);
		print();
	}
		
}
