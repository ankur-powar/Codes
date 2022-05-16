#include <bits/stdc++.h>
using namespace std;
#define N 3
 
// state space tree nodes
struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

Node* newNode(int mat[N][N], int x, int y, int newX,
              int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
 
    return node;
}

int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

int calculateCost(int initial[N][N], int final[N][N])
{

    int count = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (initial[i][j] && initial[i][j] != final[i][j])
           count++;
    return count;
}
 
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
vector<vector<pair<int,int> >>ans;int t=0;
void printPath(Node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    if(t<ans.size())
    {
        cout<<"Heuristic Cost Value  for shift value 0 to :"<<endl;

        for(int i=0;i<ans[t].size();i++)
            cout<<ans[t][i].second<<"->"<<ans[t][i].first<<"  ";
        cout<<"\n\n";
        t++;
    }
}
 
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

void solve(int initial[N][N], int x, int y,int final[N][N])
{
            priority_queue<Node*, std::vector<Node*>, comp> pq;
            Node* root = newNode(initial, x, y, x, y, 0, NULL);
            root->cost = calculateCost(initial, final);
            pq.push(root);
         
            while (!pq.empty())
            {
                    Node* min = pq.top();
             
                    pq.pop();
                    if (min->cost == 0)
                    {
                        printPath(min);
                        return;
                    }
                    vector<pair<int,int>>v;
                    for (int i = 0; i < 4; i++)
                    {
                        if (isSafe(min->x + row[i], min->y + col[i]))
                        {
                            Node* child = newNode(min->mat, min->x,
                                          min->y, min->x + row[i],
                                          min->y + col[i],
                                          min->level + 1, min);
                            child->cost = calculateCost(child->mat, final);

                            v.push_back({child->cost,min->mat[min->x + row[i]][min->y + col[i]]});
                            //cout<<min->mat[min->x + row[i]][min->y + col[i]]<<" ";

                            pq.push(child);

                        }
                    }
                    ans.push_back(v);
            }
}
 
int main()
{
    int initial[N][N] =
    {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };
 
    int final[N][N] =
    {
        {1, 2, 3},
        {5, 8, 6},
        {0, 7, 4}
    };

    int x = 1, y = 2;
    cout<<"Blank space is marked with 0 "<<endl;
    cout<<"we can swap the blank space with the up,down,right,left values"<<endl<<endl;
    cout<<"INITIAL STATE"<<endl;
    solve(initial, x, y, final);
    cout<<"FINAL STATE"<<endl;
 
    return 0;
}
