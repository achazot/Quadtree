#ifndef QUATREE_HPP
#define QUATREE_HPP

#include <vector>

class Node
{
public:
	Node(int size, int x, int y, int **data)
	{
		m_size = size;
		m_x = x;
		m_y = y;
		child[0] = NULL;
		child[1] = NULL;
		child[2] = NULL;
		child[3] = NULL;
		
		
		if (size == 1)
		{
			m_value = data[x][y];
		}
		else
		{

			int fval = data[x][y];
			bool change = false;

			for (int i = x; i < x+size; i++)
			for (int j = y; j < y+size; j++)
			{
				if (data[i][j] != fval)
				{
					change = true;
					break;
				}
				if (change) break;
			}
			
			if (change)
			{
				if (size == 2)
				{
					child[0] = new Node(1, x+0, y+0, data);
					child[1] = new Node(1, x+1, y+0, data);
					child[2] = new Node(1, x+0, y+1, data);
					child[3] = new Node(1, x+1, y+1, data);					
				}
				else
				{
					child[0] = new Node(size / 2, x, y, data);
					child[1] = new Node(size / 2, x + size/2, y, data);
					child[2] = new Node(size / 2, x, y + size/2, data);
					child[3] = new Node(size / 2, x + size/2, y + size/2, data);
				}
			}
			else m_value = fval;
		}
	}
	
	int x() { return m_x; }
	int y() { return m_y; }
	int value() { return m_value; }
	int size() { return m_size; }
	Node *nw() { return child[0]; }
	Node *ne() { return child[1]; }
	Node *sw() { return child[2]; }
	Node *se() { return child[3]; }
	
	
private:
	Node *child[4];
	int m_value;
	int m_size;
	int m_x; // x center
	int m_y; // y center
	
};

class Quadtree
{
public:
	Quadtree(int size, int **data)
	{
		root = new Node(size, 0, 0, data);
	}
	
	~Quadtree()
	{
		recDel(root);
	}
	
	std::vector<Node*> toList()
	{
		std::vector<Node*> base;
		listConstructor(root, base);
		return base;
		
	}

private:
	Node* root;
	
	void listConstructor(Node* cur, std::vector<Node*>& base)
	{
		if (cur->sw() == NULL)
		{
			base.push_back(cur);
		}
		else
		{
			listConstructor(cur->nw(), base);
			listConstructor(cur->ne(), base);
			listConstructor(cur->sw(), base);
			listConstructor(cur->se(), base);
		}
	}
	
	void recDel(Node *n)
	{
		if (n->sw() == NULL)
		{
			delete n;
		}
		else
		{
			recDel(n->nw());
			recDel(n->ne());
			recDel(n->sw());
			recDel(n->se());
		}
	}
};

#endif