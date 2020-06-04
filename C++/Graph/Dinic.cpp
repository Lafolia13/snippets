#include <vector>
#include <queue>
#include <algorithm>

struct dinic {
  struct edge {
    long long to;
    long long cap;
    long long rev;

    edge(long long to, long long cap, long long rev) :
      to(to),
      cap(cap),
      rev(rev)
    {}
  };

  std::vector<std::vector<edge> > edges;
  std::vector<long long> level;
  std::vector<long long> iter;

  dinic() {}
  dinic(int N) :
    edges(N+1),
    level(N+1),
    iter(N+1)
  {}

  void add_edge(long long from, long long to, long long cap) {
    edges[from].push_back(edge(to, cap, edges[to].size()));
    edges[to].push_back(edge(from, 0, edges[from].size()-1));
  }

  void bfs(long long s) {
    fill_n(level.begin(), level.size(), -1);
    level[s] = 0;
    std::queue<long long> q;
    q.push(s);
    while (q.size()) {
      long long now = q.front();
      q.pop();
      for (int i = 0; i < edges[now].size(); i++) {
        edge next = edges[now][i];
        if (next.cap > 0 && level[next.to] == -1)
          level[next.to] = level[now] + 1, q.push(next.to);
      }
    }
  }

  long long dfs(long long s, long long t, long long flow) {
    if(s == t) return flow;

    while(iter[s] < edges[s].size()) {
      edge &next = edges[s][iter[s]];
      if (next.cap > 0 && level[next.to] > level[s]) {
        long long d = dfs(next.to, t, std::min(flow, next.cap));
        if (d > 0) {
          next.cap -= d;
          edges[next.to][next.rev].cap += d;
          return d;
        }
      }

      iter[s]++;
    }

    return 0;
  }

  long long max_flow(long long s, long long t) {
    long long inf = 1e9;
    long long ret = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return ret;
      fill_n(iter.begin(), iter.size(), 0);
      long long f;
      while (f = dfs(s, t, inf), f > 0) ret += f;
    }
  }
};
