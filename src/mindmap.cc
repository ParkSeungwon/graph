#include<map>
#include<dirent.h>
#include<iostream>
#include<memory>
#include"mindmap.h"
using namespace std;

Graph<shared_ptr<Node>> graph;
struct Node;

shared_ptr<Node> MindMap::init(string dir)
{
	auto p = new Node;
	p->name = dir;
	auto r = shared_ptr<Node>(p);
	insert_vertex(r);

	auto fs = getdir(dir);
	for(auto& a : fs) {
		if(a.second == Node::Dir) {
			insert_edge(r, init(dir + '/' + a.first), 0);//recursive
		} else p->files.insert(a.first);
	}
	return r;
}

ostream& operator<<(ostream& o, const shared_ptr<Node>& node)
{
	o << node->name;
	//for(auto& a : node->files) cout << a << ' ';
	return o;
}

map<string, int> getdir(string dir)
{
	map<string, int> files;
    DIR *dp;
    struct dirent *dirp;
	int errno;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        throw errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.insert({string(dirp->d_name), dirp->d_type});
    }
    closedir(dp);
	for(auto& a : files) if(a.first[0] == '.') files.erase(a.first);
    return files;//error
}

MindMap::MindMap(string s)
{
	init(s);
}
