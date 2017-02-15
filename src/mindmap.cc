#include<map>
#include<dirent.h>
#include<iostream>
#include<memory>
#include"mindmap.h"
using namespace std;

Graph<Node> graph;
struct Node;

MindMap::MindMap(string directory)
{
	init(directory);
}

Node MindMap::init(string dir)
{
	Node n;
	n.name = dir;
	auto fs = getdir(dir);
	for(auto& a : fs) if(a.second == Node::File) n.files.insert(a.first);
	insert_vertex(n);

	for(auto& a : fs)
		if(a.second == Node::Dir) 
			insert_edge(n, init(dir + '/' + a.first), 0);//recursive
	return n;
}

bool Node::operator==(const Node& r) 
{
	return name == r.name;
}

ostream& operator<<(ostream& o, const Node& node)
{
	o << node.name;
	//for(auto& a : node.files) o << a << ' ';
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
