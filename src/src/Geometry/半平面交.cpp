bool turn_left (const line &l, const point &p) {
	return turn_left (l.s, l.t, p); }
vector <point> hpi (vector <line> h) {
	typedef pair <LD, line> polar;
	vector <polar> g; // use atan2, caution precision
	for (auto &i : h) {
		point v = i.t - i.s;
		g.push_back({atan2 (v.y, v.x), i}); }
	sort (g.begin(), g.end(), [] (const polar &a, const polar &b) {
		if (!sgn (a.first - b.first))
			return sgn (det (a.second.t - a.second.s, b.second.t - a.second.s)) < 0;
		else return sgn (a.first - b.first) < 0; });
	h.resize (unique (g.begin(), g.end(),
	[] (const polar &a, const polar &b)
	{ return ! sgn (a.first - b.first); }) - g.begin());
	for (int i = 0; i < (int) h.size(); ++i)
		h[i] = g[i].second;
	int fore = 0, rear = -1;
	vector <line> ret;
	for (int i = 0; i < (int) h.size(); ++i) {
		while (fore < rear && !turn_left (h[i], line_inter (ret[rear - 1], ret[rear]))) {
			--rear; ret.pop_back(); }
		while (fore < rear && !turn_left (h[i], line_inter (ret[fore], ret[fore + 1])))
			++fore;
		++rear;
		ret.push_back (h[i]); }
	while (rear - fore > 1 && !turn_left (ret[fore], line_inter (ret[rear - 1], ret[rear]))) {
		--rear; ret.pop_back(); }
	while (rear - fore > 1 && !turn_left (ret[rear], line_inter (ret[fore], ret[fore + 1])))
		++fore;
	if (rear - fore < 2) return vector <point>();
	vector <point> ans; ans.resize (rear - fore + 1);
	for (int i = 0; i < (int) ans.size(); ++i)
		ans[i] = line_inter (ret[fore + i],
				ret[fore + (i + 1) % ans.size()]);
	return ans; }
