struct data {
	llong place;
	llong cost;
	llong before;

	data() {};
	data(llong place, llong cost, llong before) :
		place(place),
		cost(cost),
		before(before)
	{}

	bool operator<(const data &ri) const {
		return cost < ri.cost;
	}
	bool operator<=(const data &ri) const {
		return cost <= ri.cost;
	}
	bool operator>(const data &ri) const {
		return cost > ri.cost;
	}
};

vector<vector<data> > edges;

vector<data> dijkstra(int start) {
	priority_queue<data, vector<data>, greater<data> > que;
	vector<data> dis(edges.size(), data(-1, inf<llong>, -1));
	dis[start] = data(start, 0, -1);

	que.push(dis[start]);
	while (que.size()) {
		data now = que.top();
		que.pop();
		if (dis[now.place] < now) continue;
		now = dis[now.place];

		for (auto &edge: edges[now.place]) {
			data next(edge.place, now.cost + edge.cost, now.place);
			if(dis[next.place] <= next) continue;
			dis[next.place] = next;
			que.push(next);
		}
	}

	return dis;
}
