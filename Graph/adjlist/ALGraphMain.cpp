#include"ALGraph.hpp"

int main()
{
	string fpath = "F:\\c++ project\\Graph.txt";
	char ch[] = {'A','B','C','D','E'};
	ALGraph<char> g(ch,5,fpath);
	cout << "������ȱ��������ݹ飩" ;
	g.DFSTraverse(0);
	cout << endl;
	cout << "������ȱ�����";
	g.BFSTraverse(0);
	cout << endl;
	cout << "������ȱ��������ǵݹ飩"; 
	g.DFSTNorecursion(0); 
	cout << endl;
	cout << endl;
	cout << "ָ��A�Ķ��㣺" << endl; 
	g.InVertex(0);
	cout << endl;
	cout << "����������ȱ����㷨��" << endl; 
	cout << "B��D" << (g.DFSTBePath(1,3)?"����":"������") << "·��" << endl; 
	cout << "A��D" << (g.DFSTBePath(0,3)?"����":"������") << "·��" << endl; 
	cout << "���ڹ�����ȱ����㷨��" << endl; 
	cout << "B��D" << (g.BFSTBePath(1,3)?"����":"������") << "·��" << endl; 
	cout << "A��D" << (g.BFSTBePath(0,3)?"����":"������") << "·��" << endl; 
	cout << endl;

	fpath = "F:\\c++ project\\DirGraph1.txt";
	string str[] = {"v1","v2","v3","v4"};
	ALGraph<string> g1(str,4,fpath);
	g1.Kosaraju();
	return 0;
}
