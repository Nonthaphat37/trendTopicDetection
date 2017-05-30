#ifndef segmentedLeastSquares_H
#define segmentedLeastSquares_H

class segmentedLeastSquares{

private:
	#define INF numeric_limits<double>::infinity()
	int N;

	// coordinate x, y 2d plane
	struct cord{
		double x, y;

		bool operator <(const cord& r){
			if(x != r.x) return x < r.x;
			return y < r.y;
		}
	}c;

	// store each point
	vector<cord> points;

	// accept error < C
	double C = 0.0;

	// Precompute
	vector<double> c_xy, c_x, c_y, c_x2, c_y2;
	vector<vector<double> > m, b, SSE;

	// cal DP
	vector<double> DP;
	vector<pair<int, int> > idx_segments;

	// ans : y = mx+c
	list<pair<int, int> > segments;

	double accept_C = 0.80;

public:
	void initialize(vector<double> y, double c){
		N = y.size();
		// Precompute
		c_xy.resize(N+1);
		c_x.resize(N+1);
		c_y.resize(N+1);
		c_x2.resize(N+1);
		c_y2.resize(N+1);

		// DP
		DP.resize(N+1);
		idx_segments.resize(N+1);
		segments.clear();

		// y = mx+b
		m.resize(N+1);
		b.resize(N+1);

		// sum square Error
		SSE.resize(N+1);
		for(int i=0;i<=N;i++) m[i].resize(N+1), b[i].resize(N+1), SSE[i].resize(N+1);

		C = c;
	}

	vector<pair<pair<double, double>, pair<int, int> > > run(vector<double> y, double c, bool type){
		srand (time(NULL));
		initialize(y, c);
		points.push_back({0, 0});
		for(int i=0;i<N;i++){
			points.push_back({(double)i, y[i]});
		}

		sort(points.begin()+1, points.end());

		for(int i=1;i<=N;i++){
			c_x[i] = c_x[i-1] + points[i].x;
			c_y[i] = c_y[i-1] + points[i].y;
			c_xy[i] = c_xy[i-1] + points[i].x*points[i].y;
			c_x2[i] = c_x2[i-1] + points[i].x*points[i].x;
			c_y2[i] = c_y2[i-1] + points[i].y*points[i].y;

			double minn = INF;
			int idx = 0;

			for(int j=1;j<=i;j++){
				int itv = i-j+1;

				double x_itv = c_x[i]-c_x[j-1];
				double y_itv = c_y[i]-c_y[j-1];
				double xy_itv = c_xy[i]-c_xy[j-1];
				double x2_itv = c_x2[i]-c_x2[j-1];
				double y2_itv = c_y2[i]-c_y2[j-1];

				if(itv*x2_itv - x_itv*x_itv == 0) m[j][i] = INF;
				else m[j][i] = (itv*xy_itv - x_itv*y_itv)/(itv*x2_itv - x_itv*x_itv);

				b[j][i] = (y_itv - m[j][i]*x_itv)/itv;

				SSE[j][i] = y2_itv - ( (2*m[j][i]*xy_itv) + (2*b[j][i]*y_itv) ) + m[j][i]*m[j][i]*x2_itv + 2*m[j][i]*b[j][i]*x_itv + itv*b[j][i]*b[j][i];

				double val = SSE[j][i] + C + DP[j-1];
				if(val < minn){
					minn = val;
					idx = j;
				}
			}
			DP[i] = minn;
			idx_segments[i] = make_pair(idx, i);
		}

		int r = N;
		int l = idx_segments[r].first;
		// cout << "3" << endl;

		vector<pair<pair<double, double>, pair<int, int> > > res;
		while(r > 0){
			segments.push_front(make_pair(l, r));
			r = l-1;
			l = idx_segments[r].first;
			// cout << "x" << " " << r << " " << l << endl;
		}

		for(auto its:segments){
			res.push_back(make_pair(make_pair(m[its.first][its.second], b[its.first][its.second]), make_pair(its.first, its.second)));
		}

		// return neg class random interval
		// if(type == 0){
		// 	int ritv = rand()%res.size();
		// 	cout << "index random : " << ritv  << " " << res.size() << " " << endl;
		// 	return make_pair(res[ritv].second.first-1, res[ritv].second.second-1);
		// }

		// sort(res.begin(), res.end());

		int pidx = res.size()-1;
		double maxx = res[res.size()-1].first.first;
		// for(int i=res.size()-2;i>=0;i--){
		// 	if(res[i].first.first - maxx*0.9 >= 0 && (res[i].second.second-res[i].first.first+1 >  res[pidx].second.second-res[pidx].first.first+1)) pidx = i;
		// 	else break;
		// }

		// return pos class random interval
		return res;
		// return make_pair(res[pidx].second.first-1, res[pidx].second.second-1);
	}
};

#endif