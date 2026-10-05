#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_SIZE 100
#define SEARCH_SIZE 50
#define MAX_VAL 1000

typedef struct TreeNode {
    int key;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

long long g_bst_build_comparisons = 0;

TreeNode* create_node(int key) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    if (!node) return NULL;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* insert_bst(TreeNode* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }

    g_bst_build_comparisons++;
    if (key < root->key) {
        root->left = insert_bst(root->left, key);
    }
    else if (key > root->key) {
        root->right = insert_bst(root->right, key);
    }
    return root;
}

int sequential_search(const int arr[], int size, int target, int* comp_count) {
    *comp_count = 0;
    for (int i = 0; i < size; i++) {
        (*comp_count)++;
        if (arr[i] == target) {
            return 1; 
        }
    }
    return 0; 
}

int bst_search(TreeNode* root, int target, int* comp_count) {
    *comp_count = 0;
    TreeNode* curr = root;

    while (curr != NULL) {
        (*comp_count)++;
        if (target == curr->key) {
            return 1; 
        }
        else if (target < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return 0;
}

void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    srand((unsigned int)time(NULL));

    int data_arr[DATA_SIZE];
    int search_keys[SEARCH_SIZE];
    TreeNode* bst_root = NULL;

    int count = 0;
    while (count < DATA_SIZE) {
        int rand_val = rand() % (MAX_VAL + 1);

        int duplicate = 0;
        for (int i = 0; i < count; i++) {
            if (data_arr[i] == rand_val) {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate) {
            data_arr[count] = rand_val;
            bst_root = insert_bst(bst_root, rand_val);
            count++;
        }
    }

    for (int i = 0; i < SEARCH_SIZE; i++) {
        search_keys[i] = rand() % (MAX_VAL + 1);
    }

    printf("=====================================================\n");
    printf(" Task 05: Sequential Search vs BST Search\n");
    printf("=====================================================\n\n");

    printf("[1] Generated 100 Unique Integers:\n");
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("%4d ", data_arr[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    printf("[2] Total comparisons for BST creation: %lld\n\n", g_bst_build_comparisons);

    printf("[3] Generated 50 Search Keys:\n");
    for (int i = 0; i < SEARCH_SIZE; i++) {
        printf("%4d ", search_keys[i]);
        if ((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");

    printf("=====================================================\n");
    printf(" %-5s | %-10s | %-12s | %-12s \n", "No", "Search Key", "Sequential", "BST");
    printf("-----------------------------------------------------\n");

    int seq_total_comp = 0;
    int bst_total_comp = 0;

    for (int i = 0; i < SEARCH_SIZE; i++) {
        int key = search_keys[i];
        int seq_comp = 0, bst_comp = 0;

        int seq_res = sequential_search(data_arr, DATA_SIZE, key, &seq_comp);
        int bst_res = bst_search(bst_root, key, &bst_comp);

        seq_total_comp += seq_comp;
        bst_total_comp += bst_comp;

        printf(" [%02d]  | %-10d | %-4s (%2d comp) | %-4s (%2d comp)\n",
            i + 1, key,
            seq_res ? "Found" : "Fail", seq_comp,
            bst_res ? "Found" : "Fail", bst_comp);
    }
    printf("=====================================================\n\n");

    double seq_avg = (double)seq_total_comp / SEARCH_SIZE;
    double bst_avg = (double)bst_total_comp / SEARCH_SIZE;

    printf("=====================================================\n");
    printf(" Performance Comparison Summary (Number of searches: %d)\n", SEARCH_SIZE);
    printf("=====================================================\n");
    printf("Sequential Search\n");
    printf("   Total comparisons   : %d\n", seq_total_comp);
    printf("   Average comparisons : %.2f\n\n", seq_avg);

    printf("BST Search\n");
    printf("   Total comparisons   : %d\n", bst_total_comp);
    printf("   Average comparisons : %.2f\n\n", bst_avg);

    printf("Cost Analysis\n");
    printf("   BST Build Cost (comparisons) : %lld\n", g_bst_build_comparisons);
    printf("   Sequential Search Total Cost : %d\n", seq_total_comp);
    printf("   BST Total Cost (Build + Search) : %lld\n", g_bst_build_comparisons + bst_total_comp);
    printf("=====================================================\n");

    free_tree(bst_root);

    return 0;
}