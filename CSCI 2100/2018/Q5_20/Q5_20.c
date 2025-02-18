#include <stdio.h>
#include <stdlib.h>
#define HASHLOAD 0.75

typedef struct hash{
	int key;
	int freq;
	int occ;
	int nextstk;
}hash;

typedef struct stack{
	int root;
	int freq;
	struct stack *nextstk;
}stack;

typedef struct stkstack{
	struct stack *root;
}stkstack;

//stack func
stack *new_stack(stack *stk, int freq)
{
	stack *tmp = (stack*)malloc(sizeof(stack));
	tmp->freq = freq;
	tmp->nextstk = stk;
	tmp->root = -1;	//uninit
	return tmp;
}

void in_stk(int loc, hash *ht, stkstack *hp)
{
	int freq = ht[loc].freq;
	stack *tmp = hp->root;
	if(tmp->root<0 || freq>tmp->freq){
		hp->root = new_stack(hp->root, freq);
		hp->root->root = loc;`
	}
	else
	{
		while(freq<tmp)
		{
			tmp=tmp->nextstk;
		}
		ht[loc]->nextstk = tmp->root;
		tmp->root = loc;
	}
}

//hash func
void update(int loc, hash *ht, stkstack *hp)
{
	//detach in stack
	stack *tmp = hp->root;
	while(tmp->freq > ht[loc]->freq)
	{
		tmp = tmp->nextstk;
	}
	int l=tmp->root;
	if(l==loc)
	tmp->root=ht[loc]->nextstk;
	else{
		while(ht[l]->nextstk!=loc)
		{
			l = ht[l]->nextstk;
		}
		ht[l]->nextstk = ht[loc]->nextstk;
	}
	ht[loc]->freq+=1;
	in_stk(loc,ht,hp);
}

void hashing(int data,int hashkey, hash *ht, stkstack *hp) //linear probing
{
	int key = data % hashkey;
	int cap=0;
	while(cap==0)
	{
		if(ht[key]->occ==0)
		{
			ht[key]->key=data;
			ht[key]->freq=1;
			ht[key]->occ=1;
			ht[key]->nextstk=-1;
			in_stk(key,ht);
			cap=1;
		}
		else
		{
			if(ht[key]->key==data)
			{
				update(loc,ht,hp);
				cap=1;
			}
		}
		key++;
	}
}

int printstack(int ptr, int count, int lim, hash *hs)
{
	if(count>=lim)
	{
		return count;
	}
	if(count>0)
	{
		printf(" ");
	}
	printf("%d", hs[ptr]->key);
	int c=count+1;
	if(ptr<0)
	return c;
	else
	c=printstack(hs[ptr]->nextstk,c,lim,hs);
	return c;
}

void printstk(stkstack *stk,int lim,hash *hs)
{
	int count=0;
	stack *ptr = stk->root;
	while(count<lim)
	{
		count = printstack(ptr->root,count,lim,hs);
		ptr = ptr->nextstk;
	}
}

int main(void)
{
	int lp;
	stkstack cap;
	scanf("%d",&lp);
	for(int a=0;a<lp;a++)
	{
		cap.root = new_stack(NULL,1);
		int ca, nf;
		scanf("&d %d", &ca, &nf);
		int h = (int)((double)c / HASHLOAD);
		hash ht[h];
		for(int b=0;b<h;b++)
		ht[b].occ = 0;
		for(int b=0;b<ca;b++)
		{
			int tmp;
			scanf("%d", &tmp);
			hashing(tmp, h, &ht, &cap);
		}
		printstk(&cap,nf,&ht);
	}
}
