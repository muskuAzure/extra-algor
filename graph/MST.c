#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

typedef struct {
    int u, v, w;
    int used;
} Edge;

typedef struct Node {
    int v, w;
    struct Node *next;
} Node;

int find(int *parent, int x) {
    return parent[x] == x ? x : (parent[x] = find(parent, parent[x]));
}

int dfs(Node **adj, int *vis, int cur, int target, int max_w) {
    if(cur == target) return max_w;
    vis[cur] = 1;
    
    for(Node *tmp = adj[cur]; tmp; tmp = tmp->next) {
        if(!vis[tmp->v]) {
            int res = dfs(adj, vis, tmp->v, target, max_w > tmp->w ? max_w : tmp->w);
            if(res != -1) return res;
        }
    }
    return -1;
}

void bubble(Edge *edges, int m) {
    int i, j;
    for(i = 0; i < m-1; i++) {
        for(j = 0; j < m-i-1; j++) {
            if(edges[j].w > edges[j+1].w) {
                Edge temp = edges[j];
                edges[j] = edges[j+1];
                edges[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, m, i, u, v, w, edge_count = 0;
    scanf("%d %d", &n, &m);
    
    Edge *edges = malloc(m * sizeof(Edge));
    int *parent = malloc((n+1) * sizeof(int));
    int *vis = malloc((n+1) * sizeof(int));
    Node **adj = calloc(n+1, sizeof(Node*));
    
    for(i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
        edges[i].used = 0;
    }
    
    for(i = 1; i <= n; i++) parent[i] = i;
    
    bubble(edges, m);
    
    long long mst_cost = 0;
    for(i = 0; i < m && edge_count < n-1; i++) {
        u = edges[i].u, v = edges[i].v, w = edges[i].w;
        int pu = find(parent, u), pv = find(parent, v);
        
        if(pu != pv) {
            parent[pv] = pu;
            mst_cost += w;
            edges[i].used = 1;
            edge_count++;
            
            Node *new_node = malloc(sizeof(Node));
            new_node->v = v; new_node->w = w; new_node->next = adj[u];
            adj[u] = new_node;
            
            new_node = malloc(sizeof(Node));
            new_node->v = u; new_node->w = w; new_node->next = adj[v];
            adj[v] = new_node;
        }
    }
    
    long long second_mst = LLONG_MAX;
    for(i = 0; i < m; i++) {
        if(!edges[i].used) {
            memset(vis, 0, (n+1) * sizeof(int));
            u = edges[i].u, v = edges[i].v, w = edges[i].w;
            
            int max_edge = dfs(adj, vis, u, v, 0);
            if(max_edge != -1) {
                long long candidate = mst_cost - max_edge + w;
                if(candidate > mst_cost && candidate < second_mst)
                    second_mst = candidate;
            }
        }
    }
    
    printf("%lld", second_mst == LLONG_MAX ? -1 : second_mst);
    
    free(edges);
    free(parent);
    free(vis);
    free(adj);
    
    return 0;
}