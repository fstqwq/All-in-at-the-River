LD angle (cp u, cp v) {
	return 2 * asin(dis(u.unit(), v.unit()) / 2); }
LD area(cp s, cp t, LD r) { // 2 * area
	LD theta = angle(s, t); cp Z{0, 0};
	LD dis = point_to_segment(Z, {s, t});
	if (dis >= r) return theta * r * r;
	auto [u, v] = line_circle_inter({s, t}, {Z, r});
	point lo = sgn(det(s, u)) >= 0 ? u : s;
	point hi = sgn(det(v, t)) >= 0 ? v : t;
	return det(lo, hi) + (theta - angle(lo, hi)) * r * r; }
LD solve(vector<point> &p, cc c) {
	LD ret = 0;
	for (int i = 0; i < (int) p.size (); ++i) {
		auto u = p[i] - c.c;
		auto v = p[(i + 1) % p.size()] - c.c;
		int s = sgn(det(u, v));
		if (s > 0)      ret += area (u, v, c.r);
		else if (s < 0) ret -= area (v, u, c.r);
	} return abs (ret) / 2; } //ret在p逆时针时为正