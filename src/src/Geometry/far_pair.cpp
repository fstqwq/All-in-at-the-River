LD diameter(vector <point> p) {
	p = convex_hull(p);
	int n = (int) p.size(); LD ret = 0;
	for (int i = 0, j, k = 1; i < n; i++) {
		j = (i + 1) % n;
		if (k == j) ++k %= n;
		while (k != i) {
			int kk = (k + 1) % n;
			if (sgn(det(p[j]-p[i], p[kk]-p[k])) > 0) k = kk;
			else break;
		}
		ret = max(ret, dis2(p[i], p[k])); 
		ret = max(ret, dis2(p[j], p[k]));
	} return ret; }
