#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

struct TreeNode {
    char key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char k) : key(k), left(nullptr), right(nullptr) {}
};

class BinaryTree {
private:
    TreeNode* root;

    void clear(TreeNode*& node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
            node = nullptr;
        }
    }

    int getHeight(TreeNode* node) const {
        if (!node) return 0;
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    int getWidth(TreeNode* node) const {
        if (!node) return 0;
        queue<TreeNode*> q;
        q.push(node);
        int maxWidth = 0;
        while (!q.empty()) {
            int count = q.size();
            maxWidth = max(maxWidth, count);
            for (int i = 0; i < count; ++i) {
                TreeNode* temp = q.front();
                q.pop();
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            }
        }
        return maxWidth;
    }

    int getNodeCount(TreeNode* node) const {
        if (!node) return 0;
        return 1 + getNodeCount(node->left) + getNodeCount(node->right);
    }

    int getLeafCount(TreeNode* node) const {
        if (!node) return 0;
        if (!node->left && !node->right) return 1;
        return getLeafCount(node->left) + getLeafCount(node->right);
    }

    void preorderTraversal(TreeNode* node) const {
        if (node) {
            cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void inorderTraversal(TreeNode* node) const {
        if (node) {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void postorderTraversal(TreeNode* node) const {
        if (node) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            cout << node->key << " ";
        }
    }

    TreeNode* buildFromPreIn(string& preorder, string& inorder) {
        if (preorder.empty() || inorder.empty()) return nullptr;
        char rootKey = preorder[0];
        auto rootIndex = inorder.find(rootKey);
        if (rootIndex == string::npos) return nullptr;
        TreeNode* newNode = new TreeNode(rootKey);
        string leftIn = inorder.substr(0, rootIndex);
        string rightIn = inorder.substr(rootIndex + 1);
        preorder = preorder.substr(1);
        newNode->left = buildFromPreIn(preorder, leftIn);
        newNode->right = buildFromPreIn(preorder, rightIn);
        return newNode;
    }

    void insertNode(TreeNode*& node, char key) {
        if (!node) {
            node = new TreeNode(key);
        } else {
            int leftHeight = getHeight(node->left);
            int rightHeight = getHeight(node->right);
            if (leftHeight <= rightHeight) {
                insertNode(node->left, key);
            } else {
                insertNode(node->right, key);
            }
        }
    }

    bool areMirrors(TreeNode* a, TreeNode* b) {
        if (!a && !b) return true;
        if (!a || !b || a->key != b->key) return false;
        return areMirrors(a->left, b->right) && areMirrors(a->right, b->left);
    }

    TreeNode* copyTree(TreeNode* node) {
        if (!node) return nullptr;
        TreeNode* newNode = new TreeNode(node->key);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

public:
    BinaryTree() : root(nullptr) {}

    BinaryTree(const BinaryTree& other) {
        root = copyTree(other.root);
    }

    ~BinaryTree() {
        clear(root);
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this != &other) {
            clear(root);
            root = copyTree(other.root);
        }
        return *this;
    }

    void createEmptyTree() {
        clear(root);
    }

    void createFromPreIn(string preorder, string inorder) {
        clear(root);
        root = buildFromPreIn(preorder, inorder);
    }

    void insert(char key) {
        insertNode(root, key);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void traversePreOrder() const {
        preorderTraversal(root);
        cout << endl;
    }

    void traverseInOrder() const {
        inorderTraversal(root);
        cout << endl;
    }

    void traversePostOrder() const {
        postorderTraversal(root);
        cout << endl;
    }

    void levelOrderTraversal() const {
        if (!root) {
            cout << "二叉树为空。" << endl;
            return;
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            cout << node->key << " ";
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        cout << endl;
    }

    void clearTree() {
        clear(root);
    }

    int getHeight() const {
        return getHeight(root);
    }

    int getWidth() const {
        return getWidth(root);
    }

    int getNodeCount() const {
        return getNodeCount(root);
    }

    int getLeafCount() const {
        return getLeafCount(root);
    }

    bool isMirrorOf(const BinaryTree& other) {
        return areMirrors(root, other.root);
    }
};

void displayMenu() {
    cout << "二叉树操作菜单：" << endl;
    cout << "1. 构造空二叉树" << endl;
    cout << "2. 根据前序和中序序列构建二叉树" << endl;
    cout << "3. 判别二叉树是否为空" << endl;
    cout << "4. 递归先序遍历" << endl;
    cout << "5. 递归中序遍历" << endl;
    cout << "6. 递归后序遍历" << endl;
    cout << "7. 层次遍历" << endl;
    cout << "8. 清空二叉树" << endl;
    cout << "9. 求二叉树高度" << endl;
    cout << "10. 求二叉树结点数和叶子结点数" << endl;
    cout << "11. 求二叉树宽度" << endl;
    cout << "12. 插入节点" << endl;
    cout << "13. 判断两棵树是否互为镜像" << endl;
    cout << "0. 退出" << endl;
}

int main() {
    BinaryTree tree, otherTree;
    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        if (choice == 1) {
            tree.createEmptyTree();
        } else if (choice == 2) {
            string preorder, inorder;
            cin >> preorder >> inorder;
            tree.createFromPreIn(preorder, inorder);
        } else if (choice == 3) {
            cout << (tree.isEmpty() ? "二叉树为空。" : "二叉树不为空。") << endl;
        } else if (choice == 4) {
            tree.traversePreOrder();
        } else if (choice == 5) {
            tree.traverseInOrder();
        } else if (choice == 6) {
            tree.traversePostOrder();
        } else if (choice == 7) {
            tree.levelOrderTraversal();
        } else if (choice == 8) {
            tree.clearTree();
        } else if (choice == 9) {
            cout << "高度: " << tree.getHeight() << endl;
        } else if (choice == 10) {
            cout << "节点数: " << tree.getNodeCount() << ", 叶子结点数: " << tree.getLeafCount() << endl;
        } else if (choice == 11) {
            cout << "宽度: " << tree.getWidth() << endl;
        } else if (choice == 12) {
            char key;
            cin >> key;
            tree.insert(key);
        } else if (choice == 13) {
            string preorder, inorder;
            cin >> preorder >> inorder;
            otherTree.createFromPreIn(preorder, inorder);
            cout << (tree.isMirrorOf(otherTree) ? "互为镜像" : "不互为镜像") << endl;
        } else if (choice == 0) {
            break;
        }
    }
    return 0;
}