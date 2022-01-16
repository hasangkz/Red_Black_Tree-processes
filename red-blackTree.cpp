#include <iostream>
#include <ctime>

struct Node
 {
	int data; 
	Node *parent; 
	Node *sol; 
	Node *sag; 
	int renk; 
};

typedef Node *NodePtr;

class RBTree 
{
private:
	NodePtr root;
	NodePtr TNULL;

	void initializeNULLNode(NodePtr node, NodePtr parent) 
    {
		node->data = 0;
		node->parent = parent;
		node->sol = nullptr;
		node->sag = nullptr;
		node->renk = 0;
	}

	void preOrderyardimci(NodePtr node) 
    {
		if (node != TNULL) 
        {
			std::cout<<node->data<<" ";
			preOrderyardimci(node->sol);
			preOrderyardimci(node->sag);
		} 
	}

	void inOrderyardimci(NodePtr node) 
    {
		if (node != TNULL) 
        {
			inOrderyardimci(node->sol);
			std::cout<<node->data<<" ";
			inOrderyardimci(node->sag);
		} 
	}

	void postOrderyardimci(NodePtr node) 
    {
		if (node != TNULL)
         {
			postOrderyardimci(node->sol);
			postOrderyardimci(node->sag);
			std::cout<<node->data<<" ";
		} 
	}

	void fixsilme(NodePtr x) 
    {
		NodePtr s;
		while (x != root && x->renk == 0) 
        {
			if (x == x->parent->sol) 
            {
				s = x->parent->sag;
				if (s->renk == 1) 
                {
					
					s->renk = 0;
					x->parent->renk = 1;
					solRotate(x->parent);
					s = x->parent->sag;
				}

				if (s->sol->renk == 0 && s->sag->renk == 0) 
                {
					s->renk = 1;
					x = x->parent;
				} 
                else 
                {
					if (s->sag->renk == 0) 
                    {
						
						s->sol->renk = 0;
						s->renk = 1;
						sagRotate(s);
						s = x->parent->sag;
					} 
					s->renk = x->parent->renk;
					x->parent->renk = 0;
					s->sag->renk = 0;
					solRotate(x->parent);
					x = root;
				}
			}
            else
              {
				s = x->parent->sol;
				if (s->renk == 1) 
                {
					
					s->renk = 0;
					x->parent->renk = 1;
					sagRotate(x->parent);
					s = x->parent->sol;
				}
				if (s->sag->renk == 0 && s->sag->renk == 0) 
                {
					
					s->renk = 1;
					x = x->parent;
				} 
                else 
                {
					if (s->sol->renk == 0) 
                    {
						
						s->sag->renk = 0;
						s->renk = 1;
						solRotate(s);
						s = x->parent->sol;
					}

					s->renk = x->parent->renk;
					x->parent->renk = 0;
					s->sol->renk = 0;
					sagRotate(x->parent);
					x = root;
				}
			} 
		}
		x->renk = 0;
	}


	void rbTransplant(NodePtr u, NodePtr v)
    {
		if (u->parent == nullptr) 
        {
		    root = v;
		} 
        else if (u == u->parent->sol)
        {
			u->parent->sol = v;
		} 
        else 
        {
			u->parent->sag = v;
		}
		v->parent = u->parent;
	}

	void silmeNodeyardimci(NodePtr node, int key) 
    {
		
		NodePtr z = TNULL;
		NodePtr x, y;
		while (node != TNULL)
        {
			if (node->data == key) 
            {
				z = node;
			}

			if (node->data <= key) 
            {
				node = node->sag;
			} 
            else 
            {
				node = node->sol;
			}
		}

		if (z == TNULL) 
        {
			std::cout << "Deger bulunamadi" << std::endl;
			return;
		} 

		y = z;
		int y_original_renk = y->renk;
		if (z->sol == TNULL) 
        {
			x = z->sag;
			rbTransplant(z, z->sag);
		} 
        else if (z->sag == TNULL) 
        {
			x = z->sol;
			rbTransplant(z, z->sol);
		} else 
        {
			y = minimum(z->sag);
			y_original_renk = y->renk;
			x = y->sag;
			if (y->parent == z) {
				x->parent = y;
			} else 
            {
				rbTransplant(y, y->sag);
				y->sag = z->sag;
				y->sag->parent = y;
			}

			rbTransplant(z, y);
			y->sol = z->sol;
			y->sol->parent = y;
			y->renk = z->renk;
		}
		delete z;
		if (y_original_renk == 0){
			fixsilme(x);
		}
	}

	void fixekleme(NodePtr k)
    {
		NodePtr u;
		while (k->parent->renk == 1) 
        {
			if (k->parent == k->parent->parent->sag) 
            {
				u = k->parent->parent->sol; 
				if (u->renk == 1)
                {
					u->renk = 0;
					k->parent->renk = 0;
					k->parent->parent->renk = 1;
					k = k->parent->parent;
				} 
                else 
                {
					if (k == k->parent->sol) 
                    {
						k = k->parent;
						sagRotate(k);
					}
					k->parent->renk = 0;
					k->parent->parent->renk = 1;
					solRotate(k->parent->parent);
				}
			} 
            else 
            {
				u = k->parent->parent->sag; 
				if (u->renk == 1) 
                {
					u->renk = 0;
					k->parent->renk = 0;
					k->parent->parent->renk = 1;
					k = k->parent->parent;	
				} 
                else 
                {
					if (k == k->parent->sag) 
                    {
						k = k->parent;
						solRotate(k);
					}
					k->parent->renk = 0;
					k->parent->parent->renk = 1;
					sagRotate(k->parent->parent);
				}
			}
			if (k == root) 
            {
				break;
			}
		}
		root->renk = 0;
	}

	void printyardimci(NodePtr root, std::string indent, bool last) 
    {
		
	   	if (root != TNULL) 
           {
		   std::cout << indent;
		   if (last) 
           {
		      std::cout<<"R----";
		      indent += "     ";
		   } 
           else 
           {
		      std::cout<<"L----";
		      indent += "|    ";
		   }
            
           std::string srenk = root->renk?"RED":"BLACK";
		   std::cout<<root->data<<"("<<srenk<<")"<<std::endl;
		   printyardimci(root->sol, indent, false);
		   printyardimci(root->sag, indent, true);
		}
	}

public:
	RBTree() 
    {
		TNULL = new Node;
		TNULL->renk = 0;
		TNULL->sol = nullptr;
		TNULL->sag = nullptr;
		root = TNULL;
	}
	void preorder() 
    {
		preOrderyardimci(this->root);
	}

	void inorder() 
    {
		inOrderyardimci(this->root);
	}
	void postorder() 
    {
		postOrderyardimci(this->root);
	}

	NodePtr minimum(NodePtr node) 
    {
		while (node->sol != TNULL) 
        {
			node = node->sol;
		}
		return node;
	}
	NodePtr maximum(NodePtr node) 
    {
		while (node->sag != TNULL) 
        {
			node = node->sag;
		}
		return node;
	}
	NodePtr successor(NodePtr x) 
    {

		if (x->sag != TNULL) 
        {
			return minimum(x->sag);
		}
		NodePtr y = x->parent;
		while (y != TNULL && x == y->sag) 
        {
			x = y;
			y = y->parent;
		}
		return y;
	}
	NodePtr predecessor(NodePtr x) 
    {

		if (x->sol != TNULL) 
        {
			return maximum(x->sol);
		}

		NodePtr y = x->parent;
		while (y != TNULL && x == y->sol) 
        {
			x = y;
			y = y->parent;
		}

		return y;
	}
	void solRotate(NodePtr x) 
    {
		NodePtr y = x->sag;
		x->sag = y->sol;
		if (y->sol != TNULL) 
        {
			y->sol->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
        {
			this->root = y;
		} 
        else if (x == x->parent->sol) 
        {
			x->parent->sol = y;
		} 
        else 
        {
			x->parent->sag = y;
		}
		y->sol = x;
		x->parent = y;
	}
	void sagRotate(NodePtr x) 
    {
		NodePtr y = x->sol;
		x->sol = y->sag;
		if (y->sag != TNULL) 
        {
			y->sag->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) 
        {
			this->root = y;
		} else if (x == x->parent->sag) 
        {
			x->parent->sag = y;
		} else 
        {
			x->parent->sol = y;
		}
		y->sag = x;
		x->parent = y;
	}

	void ekleme(int key) 
    {
		NodePtr node = new Node;
		node->parent = nullptr;
		node->data = key;
		node->sol = TNULL;
		node->sag = TNULL;
		node->renk = 1; 

		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != TNULL) 
        {
			y = x;
			if (node->data < x->data) 
            {
				x = x->sol;
			} 
            else 
            {
				x = x->sag;
			}
		}
		node->parent = y;
		if (y == nullptr) 
        {
			root = node;
		} 
        else if (node->data < y->data) 
        {
			y->sol = node;
		}
        else 
        {
			y->sag = node;
		}
		if (node->parent == nullptr)
        {
			node->renk = 0;
			return;
		}
		if (node->parent->parent == nullptr)
         {
			return;
		}
		fixekleme(node);
	}

	NodePtr getRoot()
    {
		return this->root;
	}
	void silmeNode(int data) 
    {
		silmeNodeyardimci(this->root, data);
	}
	void prettyPrint() 
    {
	    if (root) 
        {
    		printyardimci(this->root, "", true);
	    }
	}

    void arama(int deger)
    {
        Node *temp = root;
        bool found = false;
        while(temp != NULL)
        {
            if(deger == temp->data)
            {
                found = true;
                break;
            }
            else
            {
                if(deger < temp->data)
                    temp = temp->sol;
                else
                    temp = temp->sag;

            }
        }
            if(found)
            {
                std::cout << deger <<  " bulundu" << std::endl;
            }
            else
            {
                std::cout << deger << " bulunamadi" << std::endl;
            }
    }
};

void printArray(int array[30])
{
    for(int i = 0; i < 30; i++)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
}

int main() 
{
    srand(time(NULL));

    int array[30];
    RBTree bst;

    for(auto& iter:array)
    {
        iter = rand() + 1;
    }
    printArray(array);

    for(int i = 0; i < 30; i++)
    {
        bst.ekleme(array[i]);
    }

	bst.silmeNode(array[3]);
    bst.arama(array[2]);
    bst.arama(array[3]);
    bst.prettyPrint();
   
	return 0;
}