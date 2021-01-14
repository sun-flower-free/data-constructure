#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>      //用于BFS
#include "C:\Users\zhangyuhan\Desktop\Status.h"

#define MAXVEX 100
#define INFINITY 65535 //表示正无穷

typedef char VertexType;
typedef int EdgeType;

//////////////////邻接矩阵
typedef struct MGraph
{
	VertexType vexes[MAXVEX];         //顶点表
	EdgeType matrix[MAXVEX][MAXVEX];    //邻接矩阵，可以看做表
	int numVertexes,numEdges;        //图中当前的顶点数和边数
}MGraph;
void CreateMGraph(MGraph *G){
	std::cin>>G->numVertexes>>G->numEdges;
	for (int i = 0;i < G->numVertexes; ++i)        //读入顶点信息，建立矩阵
		std::cin>>G->vexes[i];                     
	for (int i = 0; i < G->numVertexes; ++i)       //邻接矩阵的初始化
		for (int j = 0; j < G->numVertexes; ++j)
			G->matrix[i][j] = INFINITY;
	for (int k = 0; k < G->numEdges; ++k){
		int i, j, w;
		std::cin>>i>>j>>w;
		G->matrix[i][j] = w;
		G->matrix[j][i] = w; //无向图，矩阵对称
	}
}
/////////////////邻接表
typedef struct EdgeNode                  //边表结点
{
	/* data */
	int adjvex;                          //邻接点域，存储该顶点对应的下标
	EdgeType weight;                     //用于存储权值
	struct EdgeNode *next;               //链域，指向下一个邻接点
}EdgeNode;
typedef struct VertexNode{               //顶点表结点
	int in;                              //顶点入度
	VertexType data;                     //顶点域，用于存储顶点信息
	EdgeNode *firstedge;                 //边表头指针
}VertexNode, AdjList[MAXVEX];
typedef struct 
{
	/* data */
	AdjList adjList;
	int numVertexes, numEdges;           //图中当前节点数和边数
}*GraphAdjList, graphAdjList;
void CreatALGraph(GraphAdjList G){
	EdgeNode *e;
	std::cin>>G->numVertexes>>G->numEdges;
	for (int i = 0; i < G->numVertexes; ++i){
		std::cin>>G->adjList[i].data;
		G->adjList[i].firstedge = nullptr;
	}
	for (int k = 0; k < G->numEdges; ++k){
		int i, j;
		std::cin>>i>>j;                //输入边（vi,vj）上的顶点序号
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e -> adjvex = j;
		e -> next = G ->adjList[i].firstedge;
		G -> adjList[i].firstedge = e;
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e -> adjvex = i;
		e -> next = G ->adjList[j].firstedge;
		G -> adjList[j].firstedge = e; //运用头插法，将元素插入邻接表中
	}
}


///////////////DFS
typedef int Boolean;
Boolean visited[MAXVEX];
//邻接矩阵DFS
void DFS(MGraph G,int i){
	visited[i] = TRUE;
	std::cout<<G.vexes[i]<<" ";
	for (int j = 0; j < G.numVertexes; ++j){
		if (G.matrix[i][j] == 1 && !visited[j])
			DFS(G, j);
	}
}
void DFSTraverse(MGraph G){
	for (int i = 0; i < G.numVertexes; ++i)
		visited[i] = FALSE;
	for (int i = 0; i < G.numVertexes; ++i)
		if (!visited[i])
			DFS(G, i);
}
//邻接表DFS
void DFS(graphAdjList GL,int i){
	EdgeNode *p;
	visited[i] = TRUE;
	std::cout<<GL.adjList[i].data<<" ";
	p = GL.adjList[i].firstedge;
	while(p){
		if(!visited[p->adjvex])
			DFS(GL, p->adjvex);
		p = p->next;
	}
}
void DFSTraverse(graphAdjList GL){
	for (int i = 0; i < GL.numVertexes; ++i)
		visited[i] = FALSE;
	for (int i = 0; i < GL.numVertexes; ++i)
		if (!visited[i])
			DFS(GL, i);
}

///////////////BFS(邻接表的BFS略)
void BFSTraverse(MGraph G){
	std::queue<int> q;
	for (int i = 0; i < G.numVertexes ;++i)
		visited[i] = FALSE;
	for (int i = 0; i < G.numVertexes; i++)
	{
		if(!visited[i]){
			visited[i] = TRUE;
			std::cout<<G.vexes[i]<<" ";
			q.push(i);
			while(!q.empty()){
				i = q.front();q.pop();
				for(int j = 0; j < G.numVertexes; ++j){
					if(G.matrix[i][j] == 1 && !visited[j]){
						visited[j] = TRUE;
						std::cout<<G.vexes[j]<<" ";
						q.push(j);
					}
				}
			}
		}
	}
}


//////////////最小生成树
//Prim算法
void MiniSpanTree_Prim(MGraph G){
	int min,i,j,k;
	int adjvex[MAXVEX];
	int lowcost[MAXVEX];
	lowcost[0] = 0,adjvex[0] = 0;
	for (i = 0;i < G.numVertexes; ++i){
		lowcost[i] = G.matrix[0][i];
		adjvex[i] = 0;
	}
	for (int i; i < G.numVertexes; ++i){
		min = INFINITY;
		j = 1,k = 0;
		while(j < G.numVertexes){
			if(lowcost[j] != 0 && lowcost[j] < min){
				min = lowcost[j];
				k = j;
			}
			j++;
		}
	}
	std::cout<<"("<<adjvex[k]<<","<<k<<")";
	lowcost[k] = 0;
	for(j = 1; j < G.numVertexes; ++j){
		if(lowcost[j] != 0 && G.matrix[k][j] < lowcost[j])
			lowcost[j] = G.matrix[k][j],
			adjvex[j] = k; 
	}
}
//Kruskal算法
//边集数组Edge结构的定义
typedef struct 
{
	int begin;
	int end;
	int weight;
}Edge;
int Find(int *parent, int f){     //查找连线顶点的尾部下标
	while(parent[f]>0)
		f = parent[f];
	return f;
}
void MiniSpanTree_Kruskal(MGraph G){
	int i, n, m;
	Edge edges[MAXVEX];
	int parent[MAXVEX];
	/*
	sort(edge),具体方式省略是weight从小到大
	*/
	for (i = 0; i < G.numVertexes; ++i)
		parent[i] = 0;
	for (i = 0; i < G.numVertexes; ++i){
		n = Find(parent, edges[i].begin);
		m = Find(parent, edges[i].end);
		if( n != m){
			parent[n] = m;
			std::cout<<"("<<edges[i].begin<<","<<edges[i].end<<") "<<edges[i].weight;
		}
	}
}


/*
Dijkstra
*/
/*
Floyd算法，求网图G中各顶点v到其余顶点w的最短路径P[v][w]及带权长度D[v][w]
*/
typedef int PathMatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];
void ShortestPath_Floyd(MGraph G,PathMatrix *P, ShortPathTable *D){
	int v,w,k;
	for (v = 0; v < G.numVertexes; ++v){
		for (w = 0; w < G.numVertexes; ++w){
			(*D)[v][w] = G.matrix[v][w];//D[v][w]值即为对应顶点之间的权值
			(*P)[v][w] = w;//初始化P
		}
	}
	for (k = 0; k < G.numVertexes; ++k){
		for (v = 0; v < G.numVertexes; ++v){
			for (w = 0;w < G.numVertexes; ++w){
				if((*D)[v][w] > (*D)[v][k] + (*D)[k][w]){
					//如果经过下表k顶点路径比原两点间的路径更短
					//将当前两点间的权值设为更小的一个
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];//设置路径下标为k的顶点
				}
			}
		}
	}
}
void print_shortest(MGraph G, PathMatrix *P, ShortPathTable *D){
	for (int v = 0; v < G.numVertexes; ++v){
		for (int w = 0; w < G.numVertexes; ++w){
			printf("v%d - v%d weight: %d",v,w,(*D)[v][w] );
			int k = (*P)[v][w];
			printf("path: %d",v );
			while(k != w){
				printf(" -> %d", k);
				k = (*P)[k][w];
			}
			printf(" -> %d\n",w );

		}
		printf("\n");
	}
}



