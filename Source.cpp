#include<stdio.h>
#include<stdlib.h>

struct node {
	int val;
	int height;
	struct node *left;
	struct node *right;
};

int max(int a, int b) {
	return (a < b) ? b : a;
}

int getHeight(struct node *localRoot) {
	if (localRoot == NULL) return 0;
	return localRoot->height;
}

int getBalanceFactor(struct node *localRoot) {
	if (localRoot == NULL) return 0;
	return getHeight(localRoot->left) - getHeight(localRoot->right);
}

struct node *newNode(int val) {
	struct node *nodebaru = (struct node *)malloc(sizeof(struct node));

	nodebaru->val = val;
	nodebaru->left = NULL;
	nodebaru->right = NULL;
	nodebaru->height = 1;
	return nodebaru;
}

struct node *rightRotate(struct node *y) {
	struct node *x = y->left;
	struct node *B = x->right;

	// rotate
	x->right = y;
	y->left = B;

	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}

struct node *leftRotate(struct node *x) {
	struct node *y = x->right;
	struct node *B = y->left;

	// rotate
	y->left = x;
	x->right = B;


	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}


struct node *rebalance(struct node *localRoot) {
	localRoot->height = max(getHeight(localRoot->left),
		getHeight(localRoot->right)) + 1;
	int currentBalance = getBalanceFactor(localRoot);

	if (currentBalance > 1 && getBalanceFactor(localRoot->left) >= 0) {
		return rightRotate(localRoot);
	}
	if (currentBalance > 1 && getBalanceFactor(localRoot->left) < 0) {
		localRoot->left = leftRotate(localRoot->left);
		return rightRotate(localRoot);
	}
	if (currentBalance < -1 && getBalanceFactor(localRoot->right) <= 0) {
		return leftRotate(localRoot);
	}
	if (currentBalance < -1 && getBalanceFactor(localRoot->right) > 0) {
		localRoot->right = rightRotate(localRoot->right);
		return leftRotate(localRoot);
	}
	return localRoot;
}

struct node *insertValue(struct node *localRoot, int value) {
	if (localRoot == NULL) return newNode(value);
	if (localRoot->val > value) {
		localRoot->left = insertValue(localRoot->left, value);
	}
	else if (localRoot->val < value) {
		localRoot->right = insertValue(localRoot->right, value);
	}
	else { //kalo ada data yang sama
		// do nothing
		//return localRoot;

		localRoot->left = insertValue(localRoot->left, value);
	}
	return rebalance(localRoot);
}

struct node *successor(struct node *localRoot) {
	while (localRoot && localRoot->left != NULL) {
		localRoot = localRoot->left;
	}
	return localRoot;
}

struct node *deleteValue(struct node *localRoot, int value) {

	if (localRoot == NULL) return NULL;
	if (localRoot->val < value) {
		localRoot->right = deleteValue(localRoot->right, value);
	}
	else if (localRoot->val > value) {
		localRoot->left = deleteValue(localRoot->left, value);
	}
	else {
		// akhirnya ketemuuuuu

		if (localRoot->left == NULL && localRoot->right == NULL) {
			free(localRoot);
			localRoot = NULL;
		}
		else if (localRoot->left == NULL && localRoot->right != NULL) {
			struct node *tobedeleted = localRoot->right;
			*localRoot = *(localRoot->right); // kopi semua anak kanan
			free(tobedeleted);
		}
		else if (localRoot->left != NULL && localRoot->right == NULL) {
			struct node *tobedeleted = localRoot->left;
			*localRoot = *(localRoot->left); // kopi semua anak kiri
			free(tobedeleted);
		}
		else {
			struct node *suksesor = successor(localRoot->right);
			localRoot->val = suksesor->val;
			localRoot->right = deleteValue(localRoot->right, localRoot->val);
		}
	}

	if (localRoot == NULL) return NULL;
	return rebalance(localRoot);


}

struct node *freeAll(struct node *localRoot) {
	if (localRoot == NULL) return NULL;
	localRoot->left = freeAll(localRoot->left);
	localRoot->right = freeAll(localRoot->right);
	free(localRoot);
	return NULL;
}

void inorder(struct node *localRoot) {
	if (localRoot == NULL) return;
	inorder(localRoot->left);
	printf(" %d ", localRoot->val);
	inorder(localRoot->right);
}



int getMinimumValue(struct node *localRoot){
	if (localRoot->left == NULL) return localRoot->val;
	else return getMinimumValue(localRoot->left);
}

int main() {
	struct node *root = NULL;
	int n, k, newvalue;
	int smallest1, smallest2, newresult;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &newvalue);
		root = insertValue(root, newvalue);
	}
	
	int trial = 0;
	while (getMinimumValue(root) < k)
	{
		//printf("============================\n");
		//inorder(root);
		if (root == NULL || (root->left == NULL && root->right == NULL))
		{
			trial = -1;
			break;
		}
		else
		{
			//printf("\nTrial #%d:\n", trial + 1);
			smallest1 = getMinimumValue(root);
			root = deleteValue(root, smallest1);
			//printf("Smallest 1 = %d\n", smallest1);
			smallest2 = getMinimumValue(root);
			root = deleteValue(root, smallest2);
			//printf("Smallest 2 = %d\n", smallest2);
			newresult = smallest1 + 2 * smallest2;
			root = insertValue(root, newresult);
			//printf("New Result = %d\n", newresult);
			trial++;
		}
	}
	printf("%d", trial);




	
	/*root = insertValue(root, 10);
	root = insertValue(root, 13);
	root = insertValue(root, 9);
	root = insertValue(root, 14);
	root = insertValue(root, 11);
	root = insertValue(root, 7);
	root = insertValue(root, 19);
	root = insertValue(root, 21);
	root = insertValue(root, 1);
	root = insertValue(root, 18);
	root = insertValue(root, 5);
	root = insertValue(root, 24);
	root = insertValue(root, 3);
	root = insertValue(root, 100);
	root = insertValue(root, 22);

	inorder(root);
	puts("");
	printf("\n\n");
	printf("%d", getMinimumValue(root));
	*/




	getchar();
	return 0;
}
