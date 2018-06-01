/*
			ҽԺѡַ����
1.��������
	n����ׯ֮��Ľ�ͨͼ����������������ʾ��ͼ�б�<vi,vj>�ϵ�Ȩֵ��ʾ�Ӵ�ׯi����ׯj
�ĵ�·���ȡ�����Ҫ����n����ׯ��ѡ��һ����ׯ��һ��ҽԺ��������ҽԺӦ�����ĸ���ׯ��
����ʹ���еĴ�ׯ��ҽԺ���ȽϽ���
2.���˼��
	ҽԺѡַ����ʵ������������ͼ�����ĵ㡣���ȶ��嶥���ƫ�Ķȡ�
	��ͼG=��V��E��������һ����k����E(k) = max{dist<i,k>}(i@V(@������),dist<i,k>Ϊ����
i������k�Ĵ���)Ϊ����k��ƫ�Ķȡ���Ȼ��ƫ�Ķ���С�Ķ��㼴ΪͼG�����ĵ㡣 
*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using namespace std;

const int MaxSize = 10;

template <class T>
class MGraph{
	public:
		MGraph(T a[], int n, string fpath);	//���캯��������һ��n�������ͼ 
		~MGraph(){}						//��������Ϊ�� 
		void Floyd(int dist[][MaxSize],int n); 
		T CenterVertex();
	private:
		T vertex[MaxSize];				//ͼ�Ķ������� 
		int arc[MaxSize][MaxSize];		//�ڽӾ��� 
		int vertexNum;					//������ 
		int arcNum;						//���� 
};

template <class T>
MGraph<T>::MGraph(T a[], int n, string fpath)
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
	ifstream fgraph(fpath,ifstream::in);
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
void MGraph<T>::Floyd(int dist[][MaxSize], int n)
{
	//��ʼ�� 
	for(int i = 0; i < vertexNum; ++i)
		for(int j = 0; j < vertexNum; ++j)
		{
			dist[i][j] = arc[i][j];
		}
	//����dist�� 
	for(int k = 0; k < vertexNum; ++k)
		for(int i = 0; i < vertexNum; ++i)
			for(int j = 0; j < vertexNum; ++j){
				if(dist[i][j] != 0 && dist[i][k] != 0 && dist[k][j] != 0){
					if(dist[i][j] == -1){
						if(dist[i][k] != -1 && dist[k][j] != -1){
							dist[i][j] = dist[i][k] + dist[k][j];
						}
					}
					else{
						if(dist[i][k] != -1 && dist[k][j] != -1){
							if(dist[i][j] > dist[i][k] + dist[k][j]){
								dist[i][j] = dist[i][k] + dist[k][j];
							}
						}
					}
				}
			}
}

template <class T>
T MGraph<T>::CenterVertex()
{
	int Ecc[MaxSize];
	int dist[MaxSize][MaxSize];
	Floyd(dist,vertexNum);
	
	for(int j = 0; j < vertexNum; ++j){
		int max = -1;
		for(int i = 0; i < vertexNum; ++i){
			if(dist[i][j] != 0 && dist[i][j] != -1){
				if(max == -1)
					max = dist[i][j];
				else{
					if(max < dist[i][j])
						max = dist[i][j];
				}
			}
		}
		Ecc[j] = max;
	}
	
	int r = -1;
	int min;
	for(int i = 0; i < vertexNum; ++i){
		if(Ecc[i] != -1){
			if(r == -1){
				min = Ecc[i];
				r = i;
			}
			else{
				if(min > Ecc[i]){
					min = Ecc[i];
					r = i;
				}
			}
		}
	}
	
	return vertex[r];
}

int main()
{
	string fpath = "F:\\c++ project\\VillagesNetGraph.txt";
	char ch[] = {'a','b','c','d','e'};
	MGraph<char> g(ch,5,fpath);
	cout << "ҽԺӦ���ڣ�";
	cout << g.CenterVertex() << "��ׯ" << endl;	
	return 0;
}


