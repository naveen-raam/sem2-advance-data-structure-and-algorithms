#include<iostream>
#include<limits.h>
using namespace std;
const int V = 12;
int a;


int mindistance(int dist[] , bool sptset[])
{
        int min = INT_MAX, min_index;
        for(int i=0;i<V;i++)
        {
                if(sptset[i] == false && min > dist[i])
                {
                        min_index = i;
                        min = dist[i];
                }
        }
        return min_index;
}

void findshortest(int graph[V][V],int src,int dest)
{
        int paths[V];
        int dist[V];
        bool sptset[V];
        for(int i=0; i<V; i++)
        {
                sptset[i] = 0;
                dist[i] = INT_MAX;
                paths[i] = i;
        }
        dist[dest] = 0;
        paths[dest] = dest;
        for(int i = 0; i<V-1; i++)
        {
                int u = mindistance(dist, sptset);
                sptset[u] = true;
                for(int v = 0; v<V; v++)
                {
                        if(!sptset[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                        {

                                dist[v] = dist[u] + graph[u][v];
                                paths[v] = u;
                        }
                }
        }
//rejecting the a path that has no path
        if(src == paths[src])
                return;
// going towards the goal
	int src1 = src;
	int flag;
	cout<<"If you want to have any blocks press 1 otherwise press 0 "<<endl;
   	for(int i=0; i<V && src1 != paths[src1]; i++)
    {
              
                        cout<<"going from "<<src1<<" to "<<paths[src1];
                		cin>>flag;
                        if(flag == 1)
                        {
                                int temp = graph[src1][ paths[src1] ];
                                graph[src1][paths[src1]] = 0;
                                graph[paths[src1]][src1] = 0;
                                findshortest(graph,src1,dest);
                                graph[src1][paths[src1]] = temp;
                                graph[paths[src1]][src1] = temp;
                                break;
                        }
                if(flag == 1)
                	break;
		src1 = paths[src1];
    }

}

int main()
{
        int graph[V][V] = {
                                        {0,2,0,0,0,0,0,0,0,0,0,0},
                                        {2,0,3,2,0,0,0,0,0,0,0,0},//1
                                        {0,3,0,0,0,0,1,0,0,0,0,0},
                                        {0,2,0,0,5,3,0,0,0,0,0,0},
                                        {0,0,0,5,0,2,0,0,0,0,11,0},//4
                                        {0,0,0,3,2,0,0,0,0,0,0,3},
                                        {0,0,3,0,0,0,0,1,0,0,0,0},
                                        {0,0,0,0,0,0,1,0,10,0,0,5},//7
                                        {0,0,0,0,0,0,0,10,0,8,3,0},
                                        {0,0,0,0,0,0,0,0,8,0,0,0},
                                        {0,0,0,0,0,0,0,0,3,0,0,2},//10
                                        {0,0,0,0,0,3,0,5,0,0,2,0}
                                };
        int src = 0;
        int dest = 11;
        findshortest(graph,src,dest);
        return 0;
}
