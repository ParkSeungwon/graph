#pragma once
#include"bintree.h"
class ParseTree : public Tree<char>
{
public:
	ParseTree(std::string expression) {
		int type = 0;
		if(is_operator(expression.front())) type = -1;
		else if(is_operator(expression.back())) type = 1;
		for(auto& a : expression) expr.push_back(a);
		switch(type) {
			case -1: Graph<char>::root = finsert(); break;
			case 0: Graph<char>::root = insert(expression); break;
			case 1: Graph<char>::root = binsert();
		}
		connect(Graph<char>::root);
		Vertex<char>* p = Graph<char>::root;
		for(int i=1; i<vts.size(); i++) {
			p->vertex = vts[i];
			p = p->vertex;
		}
	}
	ParseTree(int n) : ParseTree(compose(n)) {}
	int calc() {
		return calc(Graph<char>::root);
	}
	void forward() {
		forward(Graph<char>::root);
	}
	void middle() {
		middle(Graph<char>::root);
	}
	void back() {
		back(Graph<char>::root);
	}

private:
	std::deque<char> expr;
	std::vector<Vertex<char>*> vts;
	std::string compose(int n) {
		if(n < 0) compose(-n) + "12-*";
		else {
			if(n < 10) return std::to_string(n);
			int share = n / 9;
			int rest = n % 9;
			char r = '0' + rest;
			return compose(share) + "9*" + r + '+';
		}
	}
	int calc(Vertex<char>* p) {
		switch(p->data) {
			case '+': return calc(p->edge->vertex) + calc(p->edge->edge->vertex);
			case '-': return calc(p->edge->vertex) - calc(p->edge->edge->vertex);
			case '*': return calc(p->edge->vertex) * calc(p->edge->edge->vertex);
			case '/': return calc(p->edge->vertex) / calc(p->edge->edge->vertex);
			default: return p->data - '0';
		}
	}			
	void forward(Vertex<char>* p) {
		std::cout << p->data;
		if(p->edge) {
			forward(p->edge->vertex);
			forward(p->edge->edge->vertex);
		}
	}
	void middle(Vertex<char>* p) {
		if(p->edge) middle(p->edge->vertex);
		std::cout << p->data;
		if(p->edge) middle(p->edge->edge->vertex);
	}
	void back(Vertex<char>* p) {
		if(p->edge) {
			back(p->edge->vertex);
			back(p->edge->edge->vertex);
		}
		std::cout << p->data;
	}
	void connect(Vertex<char>* p) {//connect vertexes for graph compatibility
		vts.push_back(p);
		if(p->edge) {
			connect(p->edge->vertex);
			connect(p->edge->edge->vertex);
		}
	}
	Vertex<char>* insert(std::string s) {
		int token = div_point(s);
		Vertex<char>* p = new Vertex<char>;
		p->data = s[token];
		if(token) {
			std::string rhs = s.substr(token + 1);
			s.erase(token);
			p->edge = Graph<char>::insert(p->edge, insert(s), 0);//crash
			p->edge = Graph<char>::insert(p->edge, insert(rhs), 0);
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
	Vertex<char>* finsert() {
		Vertex<char>* p = new Vertex<char>;
		p->data = expr.front();
		expr.pop_front();
		if(is_operator(p->data)) {
			p->edge = Graph<char>::insert(p->edge, finsert(), 0);
			p->edge = Graph<char>::insert(p->edge, finsert(), 0);
		}
		return p;
	}
	Vertex<char>* binsert() {
		std::stack<Vertex<char>*> st;
		while(!expr.empty()) {
			do {
				Vertex<char>* vt = new Vertex<char>;
				vt->data = expr.front(); expr.pop_front();
				st.push(vt); 
			} while(!is_operator(st.top()->data)); 
			Vertex<char>* p1 = st.top(); st.pop();
			Vertex<char>* p3 = st.top(); st.pop();
			Vertex<char>* p2 = st.top(); st.pop();
			p1->edge = Graph<char>::insert(p1->edge, p2, 0);
			p1->edge = Graph<char>::insert(p1->edge, p3, 0);
			st.push(p1);
		}
		return st.top();
	}
};



