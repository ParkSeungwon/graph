#include<map>
#include<dirent.h>
#include<iostream>
#include"mindmap.h"
using namespace std;

map<string, int> getdir(string dir);

MindMap::MindMap(string directory)
{//populate Graph vertex and edge with subdirectories
	init(directory);
}

Node MindMap::init(string dir)
{
	Node n;
	n.name = dir;
	auto fs = getdir(dir);
	for(auto& a : fs) if(a.second == Node::File) n.files.insert(a.first);
	insert_vertex(n);//insert vertex -> insert edge. order matters

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
{//return files and directories in directory dir.
	map<string, int> files;//string is name, int is type : 4 = dir, 8 = file
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