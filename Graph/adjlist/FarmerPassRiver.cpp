/*
			ũ���������
1.��������
	һ��ũ���һֻ�ǡ�һ�Űײ˺�һֻɽ��Ҫ��һ���ӵ��ϰ�����������ũ��ÿ��ֻ��
��һ���������ӣ���������ʱ�����ũ���ڳ�ʱ����Ҫ������Ҫ�Բˣ���Ϊũ����ƹ��ӷ�����
2.����
��0��1�ֱ��ʾ���ϰ�������
������λ��������˳���ʾũ���ǣ��ײ˺����λ�ã�0000~1111��

���ӦΪ							  				  
	  						
				11 - 2   
			  /			\ 
	0 - 9 - 1 			 14 - 6 - 15 
			  \ 		/
			    13 - 4  
ע�����Ӧ�����ַ�����������ֻ�����һ�֣���ʱû�뵽���ͬʱŪ������	
*/ 

#include<iostream>
#include<queue>
#include<vector>

using namespace std;

const int Size = 16;
struct ArcNode{
	int adjvex;
	ArcNode * next;
};
struct VertexNode{
	int vertex;
	ArcNode * firstedge;
};
VertexNode adjlist[Size];
void InitAdjList();

int main()
{
	//�ڽӱ��ʼ�� 
	InitAdjList();
	//������ȱ���	
	vector<int> Path(Size,-1);//Path[i]��ֵΪ����i����һ���������� 
	bool visited[Size] = {0}; 
	queue<int> Q;
	Q.push(0);
	visited[0] = 1;
	while(!Q.empty() && Path[Size-1] == -1){
		int v = Q.front();
		Q.pop();
		ArcNode * pt = adjlist[v].firstedge;
		while(pt != NULL){
			int j = pt->adjvex;
			if(visited[j] == 0){
				Q.push(j);
				visited[j] = 1;
				Path[j] = v;
			}
			pt = pt->next; 
		}
	}
	
	if(Path[Size-1] == -1){
		cout << "û�ҵ����з�����" << endl;
		return 0;
	}
	//������� 
	vector<int> vPath;
	int i = Size -1;
	while(i != -1){
		vPath.push_back(i);
		i = Path[i];
	}
	//������ 
	for(int i = vPath.size()-1; i > 0 ; --i){
		int j = i-1;
		string str = "";
		switch(vPath[i] & 8){
			case 0:
				str += "ũ����ϰ������� ";
				break;
			case 8:
				str += "ũ��ӱ������ϰ� "; 
				break;
		}
		switch(vPath[i] ^ vPath[j]){
			case 8:
				break;
			case 9:
				str += "������";
				break;
			case 10:
				str += "���Űײ�";
				break;
			case 12:
				str += "������";
				break;
		}
		cout << str << endl;
	}
	return 0;
}

void InitAdjList()
{
	for(int i = 0; i < Size; ++i){
		adjlist[i].vertex = i;
		adjlist[i].firstedge = NULL;
		if(i == 3 || i == 5 || i == 7 || i == 8 
			|| i == 10 || i == 12)
			continue;
		for(int j = 0; j < Size; ++j){
			if(j == 3 || j == 5 || j == 7 || j == 8 
				|| j == 10 || j == 12)
				continue;
			if((i ^ 8) == j || (i ^ 9) == j || (i ^ 10) == j || (i ^ 12) == j){
				ArcNode * p = new ArcNode{j,adjlist[i].firstedge};
				adjlist[i].firstedge = p;
			}			
		}
	}
}



