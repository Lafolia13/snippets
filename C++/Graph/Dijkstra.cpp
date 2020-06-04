struct node {
  long long place;
  long long cost;
  long long before;

  node() {};
  node(long long place, long long cost, long long before) :
    place(place),
    cost(cost),
    before(before)
  {}

  bool operator<(const node &ri) const {
    return cost < ri.cost;
  }
  bool operator<=(const node &ri) const {
    return cost <= ri.cost;
  }
  bool operator>(const node &ri) const {
    return cost > ri.cost;
  }
};

std::vector<std::vector<node> > edges;

std::vector<node> dijkstra(int start) {
  long long inf = 1e9;
  std::priority_queue<node, std::vector<node>, std::greater<node> > que;
  std::vector<node> dis(edges.size(), node(-1, inf, -1));
  dis[start] = node(start, 0, -1);

  que.push(dis[start]);
  while (que.size()) {
    node now = que.top();
    que.pop();
    if (dis[now.place] < now) continue;
    now = dis[now.place];

    for (auto &edge: edges[now.place]) {
      node next(edge.place, now.cost + edge.cost, now.place);
      if(dis[next.place] <= next) continue;
      dis[next.place] = next;
      que.push(next);
    }
  }

  return dis;
}
