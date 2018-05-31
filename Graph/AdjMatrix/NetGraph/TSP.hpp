#ifndef TSP_HPP
#define TSP_HPP

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>


using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n);			//���캯��������һ��n�������ͼ 
		~MGraph(){}						//��������Ϊ�� 
		void GreedyAlg(int v);			//̰���㷨 
	private:
		T vertex[MaxSize];				//ͼ�Ķ������� 
		int arc[MaxSize][MaxSize];		//�ڽӾ��� 
		int vertexNum;					//������ 
		int arcNum;						//���� 
		void DFS(int v, bool (&visited)[MaxSize]);
};

template <class T>
MGraph<T>::MGraph(T a[], int n)
{
	vertexNum = n;
	for(int i = 0; i < n; ++i)
		vertex[i] = a[i];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j){
			if(i == j)
				arc[i][j] = 0;
			else
			    arc[i][j] = -1;			//-1���ɴ����Զ�� 
		}
	
	int e = 0;
	ifstream fgraph("CityNetGraph.txt",ifstream::in);
	string line;
	while(getline(fgraph,line)){
		stringstream liness(line);
		int i,j,w;
		liness >> i >> j >> w;
		arc[i][j] = w;
		++e;
	}		
	arcNum = e/2;
} 

template <class T>
void MGraph<T>::DFS(int v, bool (&visited)[MaxSize])
{
	cout << vertex[v] << "->";
	visited[v] = 1;
	int r = -1;
	int d;
	for(int j = 0; j < vertexNum; ++j){
		if(arc[v][j] != 0 && arc[v][j] != -1 && visited[j] == 0){
			if(r == -1)
			{
				r = j;
				d = arc[v][j]; 
			}
			else{
				if(d > arc[v][j]){
					r = j;
					d = arc[v][j];
				}
			}
		}
	}
	if(r >= 0){
		DFS(r,visited);
	}
}

template <class T>
void MGraph<T>::GreedyAlg(int v)
{
	bool visited[MaxSize] = {0};
	
	DFS(v,visited);
	cout << vertex[v] << endl;
}

#endif
