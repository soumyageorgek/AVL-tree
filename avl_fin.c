#include <stdio.h>
#include <stdlib.h>
struct node {
	int dat;
	struct node *left;
	struct node *right;
	int height;
};

struct node *delete(struct node *,int);

struct node *new(int dat)
{
	struct node *t;

	t = malloc(sizeof(struct node));
	t->dat = dat;
	t->left = 0;
	t->right = 0;
	t->height = 0;
	return t;
}

void inorder(struct node *l)
{
        if(l == 0) return;

        inorder(l->left);
        printf("%d %d\n",l->dat,l->height);
        inorder(l->right);
}

int h_update(struct node *n)
{
	int t;
	
	if(n->left==0 && n->right==0)
		return 0;

	if(n->left==0)
		return n->right->height + 1;

	if(n->right==0)
		return n->left->height + 1;

	t = (n->left->height > n->right->height)?n->left->height:n->right->height;
	return t + 1;
}

int check(struct node *h)
{
	int countl=0,countr=0;
	
	if(h->left!=0)
		countl = h->left->height+1;
	if(h->right!=0)
		countr = h->right->height+1;
	return countl-countr;
}

struct node *r_rotate(struct node *n)
{
	struct node *temp1, *temp2;

	temp1 = n->left->right;
	temp2 = n->left;
	n->left = 0;
	temp2->right = n;
	n->left = temp1;
	n->height = h_update(n);
	temp2->height = h_update(temp2);
	return temp2;
}

struct node *l_rotate(struct node *n)
{
	struct node *temp1, *temp2;

	temp1 = n->right->left;
	temp2 = n->right;
	n->right = 0;
	temp2->left = n;
	n->right = temp1;
	n->height = h_update(n);
	temp2->height = h_update(temp2);
	return temp2;
}

struct node *balance(struct node *h)
{
	int d,r,l;
	
	d = check(h);
	if(d < 2 && d > -2)
		return h;
	if(d == -2){
		r = check(h->right);
		if(r == 1){
			h->right = r_rotate(h->right);
			h->height = h_update(h);
		}
		h = l_rotate(h);
		return h;
	}
	if(d == 2){
		l = check(h->left);
		if(l == -1){
			h->left = l_rotate(h->left);
			h->height = h_update(h);
		}
		h = r_rotate(h);
		return h;
	}
}

struct node *insert(struct node *h, struct node *n)
{
	if(h == 0)
		return n;
	if(n->dat<h->dat)
		h->left = insert(h->left, n);
	else
		h->right = insert(h->right, n);
	h->height = h_update(h);
	h = balance(h);
	return h;
}

struct node *one_child(struct node *h)
{
        if(h->left != 0)
                return h->left;
        else
                return h->right;
}

int twochild(struct node *h)
{
        int d;
        struct node *p;

        p = h;
        h = h->left;
        while(h->right != 0){
                        p = h;
                        h = h->right;
        }
        d = h->dat;
        p = delete(p, h->dat);
        return d;
}

struct node *delete(struct node *h, int data)
{
        int d;

        if(h == 0){
                printf("no such an element\n");
                return h;
                }
                if(data == h->dat){
                        if(h->left == 0 && h->right == 0)
                                return NULL;
                        else{
                                if(h->left != 0 && h->right != 0){
                                        h->dat = twochild(h);
                                        return h;
                        }
                        else{
                                return one_child(h);
                        }
                        }
                }
                else{
                        if(data < h->dat)
                                h->left = delete(h->left, data);
                        else
                                h->right = delete(h->right, data);
                }
	h->height = h_update(h);
	h = balance(h);
        return h;
}

main()
{
	struct node *h = 0;
	int choice,y,data;

        do{
        printf("1.insert\n2.inorder\n3.delete\n");
        scanf("%d",&choice);
	switch(choice){
                case 1:scanf("%d",&data);
                       h = insert(h, new(data));
                       break;
                case 2:inorder(h);
		       printf("\n");
                       break;
		case 3:scanf("%d",&data);
		       h=delete(h, data);
		       break;
        }
	scanf("%d",&y);
        }while(y==1);

}
