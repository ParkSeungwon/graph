#pragma once
#include"tgraph.h"
template <typename T> class Tree : public Graph<T>
{
public:
	void insert(T n) {
		Graph<T>::insert_vertex(n);
		Vertex<T>* p;
		for(p = Graph<T>::root; p->vertex; p = p->vertex);
		if(Graph<T>::root->vertex) Graph<T>::root = insert(Graph<T>::root, p);
	}
	Vertex<T>* find(T n) {
		return find(Graph<T>::root, n);
	}
		
private:
	Vertex<T>* find(Vertex<T>* p, T n) {
		if(p->data == n) return p;//all below is <else if> due to return
		if(!p->edge) return nullptr;
		if(p->data < n == p->data < p->edge->vertex->data) 
			return find(p->edge->vertex, n);
		if(!p->edge->edge) return nullptr;
		return find(p->edge->edge->vertex, n);
	}
	Vertex<T>* insert(Vertex<T>* p, Vertex<T>* n) {//insert by comparing value
		if(!p) return n;						//to make binary tree
		if(!p->edge) p->edge = Graph<T>::insert(p->edge, n, 0);//no son
		else if(!p->edge->edge) {//1 son
			if(p->data < p->edge->vertex->data == p->data < n->data)
				insert(p->edge->vertex, n);
			else p->edge = Graph<T>::insert(p->edge, n, 0);
		} else {//2son
			if(p->data < p->edge->vertex->data == p->data < n->data)
				insert(p->edge->vertex, n);
			else insert(p->edge->edge->vertex, n);
		}
		return p;
	}
};
template <typename T> class ParseTree : public Tree<T>
{
public:
	ParseTree(std::string expression) {
		int type = 0;
		if(is_operator(expression.front())) type = -1;
		else if(is_operator(expression.back())) type = 1;
		for(auto& a : expression) expr.push_back(a);
		switch(type) {
			case -1: Graph<T>::root = finsert(); break;
			case 0: Graph<T>::root = insert(expression); break;
			case 1: Graph<T>::root = binsert();
		}
		connect(Graph<T>::root);
		Vertex<T>* p = Graph<T>::root;
		for(int i=1; i<vts.size(); i++) {
			p->vertex = vts[i];
			p = p->vertex;
		}
	}
//	ParseTree(int n) {
//		if(n < 0) 
	int calc() {
		return calc(Graph<T>::root);
	}
	void forward() {
		forward(Graph<T>::root);
	}
	void middle() {
		middle(Graph<T>::root);
	}
	void back() {
		back(Graph<T>::root);
	}

private:
	std::deque<char> expr;
	std::vector<Vertex<T>*> vts;
	int calc(Vertex<T>* p) {
		switch(p->data) {
			case '+': return calc(p->edge->vertex) + calc(p->edge->edge->vertex);
			case '-': return calc(p->edge->vertex) - calc(p->edge->edge->vertex);
			case '*': return calc(p->edge->vertex) * calc(p->edge->edge->vertex);
			case '/': return calc(p->edge->vertex) / calc(p->edge->edge->vertex);
			default: return p->data - '0';
		}
	}			
	void forward(Vertex<T>* p) {
		std::cout << p->data;
		if(p->edge) {
			forward(p->edge->vertex);
			forward(p->edge->edge->vertex);
		}
	}
	void middle(Vertex<T>* p) {
		if(p->edge) middle(p->edge->vertex);
		std::cout << p->data;
		if(p->edge) middle(p->edge->edge->vertex);
	}
	void back(Vertex<T>* p) {
		if(p->edge) {
			back(p->edge->vertex);
			back(p->edge->edge->vertex);
		}
		std::cout << p->data;
	}
	void connect(Vertex<T>* p) {//connect vertexes for graph compatibility
		vts.push_back(p);
		if(p->edge) {
			connect(p->edge->vertex);
			connect(p->edge->edge->vertex);
		}
	}
	Vertex<T>* insert(std::string s) {
		int token = div_point(s);
		Vertex<T>* p = new Vertex<T>;
		p->data = s[token];
		if(token) {
			std::string rhs = s.substr(token + 1);
			s.erase(token);
			p->edge = Graph<T>::insert(p->edge, insert(s), 0);//crash
			p->edge = Graph<T>::insert(p->edge, insert(rhs), 0);
		}
		return p;
	}
	
	int div_point(std::string s) {
		std::stack<char> parenthesis;
		int token = 0;
		for(int i=0; i<s.size(); i++) {
			if(s[i] == '(') parenthesis.push('(');
			else if(s[i] == ')') parenthesis.pop();
			else if(parenthesis.empty()) {
				if(s[i] == '+' || s[i] == '-') {
					token = i;
					break;
				} else if(s[i] == '*' || s[i] == '/') if(!token) token = i;
			}
		}
		return token;
	}
	bool is_operator(char c) {
		for(auto& a : {'+', '-', '*', '/'}) if(c == a) return true;
		return false;
	}
	Vertex<T>* finsert() {
		Vertex<T>* p = new Vertex<T>;
		p->data = expr.front();
		expr.pop_front();
		if(is_operator(p->data)) {
			p->edge = Graph<T>::insert(p->edge, finsert(), 0);
			p->edge = Graph<T>::insert(p->edge, finsert(), 0);
		}
		return p;
	}
	Vertex<T>* binsert() {
		std::stack<Vertex<T>*> st;
		while(!expr.empty()) {
			do {
				Vertex<T>* vt = new Vertex<T>;
				vt->data = expr.front(); expr.pop_front();
				st.push(vt); 
			} while(!is_operator(st.top()->data)); 
			Vertex<T>* p1 = st.top(); st.pop();
			Vertex<T>* p3 = st.top(); st.pop();
			Vertex<T>* p2 = st.top(); st.pop();
			p1->edge = Graph<T>::insert(p1->edge, p2, 0);
			p1->edge = Graph<T>::insert(p1->edge, p3, 0);
			st.push(p1);
		}
		return st.top();
	}
};



