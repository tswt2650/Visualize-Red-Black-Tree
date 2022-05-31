#include <bits/stdc++.h>
using namespace std;
#define NC "\e[0m"
#define RED "\e[0;31m"
#define BLACK "\e[0;30m"
#define WHITEB "\e[47m"
#define YELLOWB "\e[43m"
#define GREENB "\e[42m"

struct Node
{
	int data;
	bool color;
	Node *parent, *left, *right;
};

typedef Node* NodePtr;

class RedBlackTree
{
private:
	NodePtr TNULL, root;
	void CreateNULLNode(NodePtr node, NodePtr parent);
	void searchTreeXX(NodePtr node, int key)
	{
		if (key == node->data)
        {
            cout << "FOUND!\n"<< endl;
            PrintSearch(root, "", true, key, false, true);
            return;
        }
        else if (node == TNULL)
        {
            cout << "\nCouldn't find key in the tree\n\n";
            return;
        }
		else if (key < node->data) searchTreeXX(node->left, key);
		else searchTreeXX(node->right, key);
	}
	void rbTransplant(NodePtr u, NodePtr v)
	{
		if (u->parent == nullptr) root = v;
		else if (u == u->parent->left) u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;
	}
    void fixDelete(NodePtr x);
    void deleteNodeXX(NodePtr node, int key);
	void fixInsert(NodePtr k);
	void printXX(NodePtr root, string indent, bool last);

public:
	RedBlackTree()
	{
		TNULL = new Node;
		TNULL->color = 0;
		TNULL->left = nullptr;
		TNULL->right = nullptr;
		root = TNULL;
		cout << "\n\t\t\tTREE CREATED!!!!!\n";
		system("pause");
	}
    bool IsEmpty()
    {
        if (root != TNULL) return false;
        return true;
    }
	void PreOrder(NodePtr root)
	{
        if (root != TNULL)
        {
            cout << root->data << " ";
			PreOrder(root->left);
			PreOrder(root->right);
		}
    }
    void InOrder(NodePtr root)
    {
        if (root != TNULL)
        {
			InOrder(root->left);
			cout << root->data << " ";
			InOrder(root->right);
		}
    }
    void PostOrder(NodePtr root)
    {
        if (root != TNULL)
        {
			PostOrder(root->left);
			PostOrder(root->right);
			cout << root->data << " ";
		}
    }

	void searchTree(int k)
	{
	    searchTreeXX(this->root, k);
    }
    void PrintSearch(NodePtr root, string indent, bool last, int k, bool check, bool check2)
    {
        if (k == root->data) {check = true;}
        if (root != TNULL)
        {
            cout << indent;
            if (last)
            {
                cout<<"R ----> ";
                indent += "     ";
            }
            else
            {
                cout<<"L ----> ";
                indent += "|    ";
            }
            if (k == root->data && root->color) cout << RED << GREENB << root->data << BLACK << WHITEB << endl;
            else if (k == root->data && !root->color) cout << GREENB << root->data << BLACK << WHITEB << endl;
            else if (check2 && root->color) cout << RED << YELLOWB << root->data << BLACK << WHITEB << endl;
            else if (check2 && !(root->color)) cout << YELLOWB << root->data << WHITEB << endl;
            else if (root->color ) cout << RED << WHITEB << root->data << BLACK << WHITEB << endl;
            else cout << root->data << endl;
            if (k > root->data && !check && check2)
            {
                PrintSearch(root->left, indent, false, k, check, false);
                PrintSearch(root->right, indent, true, k, check, true);
            }
            else if (k < root->data && !check && check2)
            {
                PrintSearch(root->left, indent, false, k, check, true);
                PrintSearch(root->right, indent, true, k, check, false);
            }
            else if (check || !check2)
            {
                PrintSearch(root->left, indent, false, k, check, false);
                PrintSearch(root->right, indent, true, k, check, false);
            }
        }
    }
	// find the node with the minimum key
	NodePtr minimum(NodePtr node)
	{
		while (node->left != TNULL) node = node->left;
		return node;
	}
	// find the node with the maximum key
	NodePtr maximum(NodePtr node)
	{
		while (node->right != TNULL) node = node->right;
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x)
	{
		if (x->right != TNULL) return minimum(x->right);
		NodePtr y = x->parent;
		while (y != TNULL && x == y->right)
        {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x)
	{
		if (x->left != TNULL) return maximum(x->left);
		NodePtr y = x->parent;
		while (y != TNULL && x == y->left)
        {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void leftRotate(NodePtr x)
	{
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != TNULL) y->left->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr) this->root = y;
		else if (x == x->parent->left) x->parent->left = y;
		else x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x)
	{
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != TNULL) y->right->parent = x;
		y->parent = x->parent;
		if (x->parent == nullptr) this->root = y;
		else if (x == x->parent->right) x->parent->right = y;
		else x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	void insert(int key)
	{
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->left = TNULL;
		node->right = TNULL;
		node->color = 1;
		NodePtr y = nullptr, x = this->root;

		while (x != TNULL)
        {
			y = x;
			if (node->data < x->data) x = x->left;
			else x = x->right;
		}

		node->parent = y;
		if (y == nullptr) root = node;
		else if (node->data < y->data) y->left = node;
		else y->right = node;

		if (node->parent == nullptr)
        {
			node->color = 0;
			return;
		}
		if (node->parent->parent == nullptr) return;

		fixInsert(node);
	}

	NodePtr getRoot() {return this->root;}
	void deleteNode(int data) {deleteNodeXX(this->root, data);}
	void PrintTree()
	{
	    if (!IsEmpty()) printXX(this->root, "", true);
        else cout << "EMPTY TREE!!!\n";
    }

    void RemoveXX(NodePtr node)
	{
		if (node != TNULL)
        {
			RemoveXX(node->left);
			RemoveXX(node->right);
			deleteNodeXX(this->root, node->data);
		}
	}

    ~RedBlackTree()
    {
        do
        {
            RemoveXX(this->root);
        } while (!IsEmpty());
        cout << "\n\t\t\tTREE DELETED!!!!!\n\n";
    }
};

    void RedBlackTree :: fixDelete(NodePtr x)
	{
		NodePtr s;
		while (x != root && x->color == 0)
        {
			if (x == x->parent->left)
			{
				s = x->parent->right;
				if (s->color == 1)// case 3.1
				{
					s->color = 0;
					x->parent->color = 1;
					leftRotate(x->parent);
					s = x->parent->right;
				}
				if (s->left->color == 0 && s->right->color == 0)// case 3.2
				{
					s->color = 1;
					x = x->parent;
				}
                else
                {
                    if (s->right->color == 0)// case 3.3
                    {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->right->color = 0;
					leftRotate(x->parent);
					x = root;
				}
			}
			else
            {
				s = x->parent->left;
				if (s->color == 1) // case 3.1
				{
					s->color = 0;
					x->parent->color = 1;
					rightRotate(x->parent);
					s = x->parent->left;
				}

				if (s->right->color == 0 && s->left->color == 0) // case 3.2
                {
					s->color = 1;
					x = x->parent;
				}
				else
                {
					if (s->left->color == 0) // case 3.3
					{
						s->right->color = 0;
						s->color = 1;
						leftRotate(s);
						s = x->parent->left;
					}

					// case 3.4
					s->color = x->parent->color;
					x->parent->color = 0;
					s->left->color = 0;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = 0;
	}

    void RedBlackTree :: deleteNodeXX(NodePtr node, int key)
	{
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL)
        {
			if (node->data == key) z = node;
			if (node->data <= key) node = node->right;
			else node = node->left;
		}
		if (z == TNULL)
        {
			cout << "Couldn't find key in the tree" << endl;
			system("pause");
			return;
		}
		y = z;
		int y_original_color = y->color;
		if (z->left == TNULL)
        {
			x = z->right;
			rbTransplant(z, z->right);
		}
		else if (z->right == TNULL)
        {
			x = z->left;
			rbTransplant(z, z->left);
		}
		else
        {
			y = minimum(z->right);
			y_original_color = y->color;
			x = y->right;
			if (y->parent == z) x->parent = y;
			else
			{
				rbTransplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			rbTransplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		delete z;
		if (y_original_color == 0) fixDelete(x);
	}

	void RedBlackTree :: fixInsert(NodePtr k)
	{
		NodePtr u;
		while (k->parent->color == 1)
        {
			if (k->parent == k->parent->parent->right)
			{
				u = k->parent->parent->left;
				if (u->color == 1)
				{
					// case 3.1
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
                else
                {
					if (k == k->parent->left)
					{
						// case 3.2.2
						k = k->parent;
						rightRotate(k);
					}
					// case 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					leftRotate(k->parent->parent);
				}
			}
			else
            {
				u = k->parent->parent->right;

				if (u->color == 1) // mcase 3.1
                {
					u->color = 0;
					k->parent->color = 0;
					k->parent->parent->color = 1;
					k = k->parent->parent;
				}
				else
                {
					if (k == k->parent->right) // mcase 3.2.2
					{
						k = k->parent;
						leftRotate(k);
					}
					// mcase 3.2.1
					k->parent->color = 0;
					k->parent->parent->color = 1;
					rightRotate(k->parent->parent);
				}
			}
			if (k == root) break;
		}
		root->color = 0;
	}

	void RedBlackTree :: printXX(NodePtr root, string indent, bool last)
	{
		if (root != TNULL)
        {
            cout << indent;
            if (last)
            {
                cout<<"R ----> ";
                indent += "     ";
            }
            else
            {
                cout<<"L ----> ";
                indent += "|    ";
            }

            if (root->color) cout << RED << WHITEB << root->data << BLACK << WHITEB << endl;
            else cout << root->data << endl;
            printXX(root->left, indent, false);
            printXX(root->right, indent, true);
        }
	}

    void RedBlackTree :: CreateNULLNode(NodePtr node, NodePtr parent)
    {
		node->data = 0;
		node->parent = parent;
		node->left = nullptr;
		node->right = nullptr;
		node->color = 0;
	}

int main()
{
    system("color 70");
	cout << "RED BLACK TREE PROGRAM:\n\n";
	RedBlackTree phpt;
	char catchk;
    do
    {
        system("cls");
        cout << "RED BLACK TREE PROGRAM:\n\n";
        phpt.PrintTree();
        cout << "\n\n\tInsert new node [1]\n\tDelete node [2]\n\tSearch value [3]\n\t"
             << "Tree traversal [4]\n\tDelete Tree [5]\n\tExit [6]\n";
        cin >> catchk;
        switch (catchk)
        {
        case '1':
            {
                int value;
                cout << "Enter value: ";
                cin >> value;
                phpt.insert(value);
                cout << "Tree after insert value " << value << ":\n";
                phpt.PrintTree();
                system("pause");
                break;
            }
        case '2':
            {
                int value;
                cout << "Enter value: ";
                cin >> value;
                phpt.deleteNode(value);
                cout << "Tree after delete value " << value << ":\n";
                phpt.PrintTree();
                system("pause");
                break;
            }
        case '3':
            {
                int value;
                cout << "Enter value: ";
                cin >> value;
                phpt.searchTree(value);
                system("pause");
                break;
            }
        case '4':
            {
                char c;
                cout << "\n\tIn Order (L-n-R) [1]\n\tPre Order (n-L-R) [2]\n\tPost Order (L-R-n) [3]\n";
                cin >> c;
                switch (c)
                {
                case '1':
                    {
                        phpt.InOrder(phpt.getRoot());
                        break;
                    }
                case '2':
                    {
                        phpt.PreOrder(phpt.getRoot());
                        break;
                    }
                case '3':
                    {
                        phpt.PostOrder(phpt.getRoot());
                        break;
                    }
                default: break;
                }
                system("pause");
                break;
            }
        case '5':
            {
                phpt.~RedBlackTree();
                char c;
                do
                {
                    cout << "Do you want to recreate the tree [1] or exit program [2]?\n";
                    cin >> c;
                    switch (c)
                    {
                    case '1':
                        {
                            RedBlackTree phpt;
                            break;
                        }
                    case '2':
                        {
                            catchk = '6';
                            break;
                        }
                    default:
                        break;
                    }
                }while (c != '1' && c != '2');
                break;
            }
        default:
            break;
        }
    } while (catchk != '6');

    cout << "\n\t\tThank you.\n";
	return 0;
}
