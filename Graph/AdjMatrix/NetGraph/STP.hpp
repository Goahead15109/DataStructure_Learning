#ifndef STP_HPP
#define STP_HPP

#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n);	//���캯��������һ��n�������ͼ 
		~MGraph(){}						//��������Ϊ�� 
		void Dijkstra(int v);
		void Floyd(int dist[][MaxSize],string Path[][MaxSize],int n); 
	private:
		T vertex[MaxSize];				//ͼ�Ķ������� 
		int arc[MaxSize][MaxSize];		//�ڽӾ��� 
		int vertexNum;					//������ 
		int arcNum;						//���� 
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
	ifstream fgraph("F:\\c++ project\\DirNetGraph.txt",ifstream::in);
	string line;
	while(getline(fgraph,line)){
		stringstream liness(line);
		int i,j,w;
		liness >> i >> j >> w;
		arc[i][j] = w;
		++e;
	}		
	arcNum = e;
} 

template <class T>
void MGraph<T>::Dijkstra(int v)
{
	//�������� 
	int dist[MaxSize];
	string Path[MaxSize];
	bool visited[MaxSize] = {0};
	//���������ʼ�� 
	for(int i = 0; i < vertexNum; ++i){
		dist[i] = arc[v][i];
		if(dist[i] != -1){
			Path[i] = vertex[v] + "-" + vertex[i];
		}
		else{
			Path[i] = "";
		}
	}
	visited[v] = 1;
	
	for(int n = 1; n < vertexNum; ++n){
		//�����С����� k 
		int k = -1;
		for(int i = 0; i < vertexNum; ++i){
			if(dist[i] != 0 && dist[i] != -1 && visited[i] == 0){
				if(k == -1){
					k = i;
				}
				else{
					if(dist[k] > dist[i]){
						k = i;
					}
				}
			}
		}
		if(k == -1) 
			break;
		//
		visited[k] = 1;
		//����dist�� 
		for(int i = 0; i < vertexNum; ++i){
			if(dist[i] != 0 && visited[i] == 0){
				if(dist[i] == -1){
					if(arc[k][i] != -1){ 
						dist[i] = dist[k] + arc[k][i];
						Path[i] = Path[k] + "-" + vertex[i]; 
					} 
				}
				else{
					if (arc[k][i] != -1) {
						if (dist[i] > dist[k] + arc[k][i]) {
							dist[i] = dist[k] + arc[k][i];
							Path[i] = Path[k] + "-" + vertex[i];
						}
					}
				}
			}
		}
	} 
	//������ 
	for(int i = 0; i < vertexNum; ++i){
		if(i == v)
			continue;
		cout << vertex[v] << "->" << vertex[i] << " : " << "���ȣ�" << dist[i] << " ·����" << Path[i] << endl; 
	}
}

template <class T>
void MGraph<T>::Floyd(int dist[][MaxSize],string Path[][MaxSize],int n)
{
	//��ʼ�� 
	for(int i = 0; i < vertexNum; ++i)
		for(int j = 0; j < vertexNum; ++j)
		{
			dist[i][j] = arc[i][j];
			if(dist[i][j] != -1){
				Path[i][j] = vertex[i] + vertex[j];
			}
			else{
				Path[i][j] = "";
			}
		}
	//����dist��Path�� 
	for(int k = 0; k < vertexNum; ++k)
		for(int i = 0; i < vertexNum; ++i)
			for(int j = 0; j < vertexNum; ++j){
				if(dist[i][j] != 0 && dist[i][k] != 0 && dist[k][j] != 0){
					if(dist[i][j] == -1){
						if(dist[i][k] != -1 && dist[k][j] != -1){
							dist[i][j] = dist[i][k] + dist[k][j];
							Path[i][j] = Path[i][k] + Path[k][j].substr(2);
						}
					}
					else{
						if(dist[i][k] != -1 && dist[k][j] != -1){
							if(dist[i][j] > dist[i][k] + dist[k][j]){
								dist[i][j] = dist[i][k] + dist[k][j];
								Path[i][j] = Path[i][k] + Path[k][j].substr(2);								
							}
						}
					}
				}
			}
}

#endif
