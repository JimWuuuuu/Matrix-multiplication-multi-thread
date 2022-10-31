#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<thread>
#include<ctime>

using namespace std;

// fmn = d mt * e tn
vector<vector<int> > d;
vector<vector<int> > e;
vector<vector<int> > f;

//single thread
void mulsingle()
{
	int m = d.size();
	int t = d[0].size();
	int n = e[0].size();
	// ikj is faster than ijk (memory access issues)
	for (int i = 0; i < m; ++i)
		for (int k = 0; k < t; ++k)
		{
			int s = d[i][k];
			for (int j = 0; j < n; ++j)
				f[i][j] += s * e[k][j];
		}
}

//multi thread
void mulMulti(int rowstart, int rowEnd)
{
	int m = d.size();
	int t = d[0].size();
	int n = e[0].size();
	// ikj is faster than ijk (memory access issues)
	for (int i = rowstart; i < rowEnd; ++i)
		for (int k = 0; k < t; ++k)
		{
			int s = d[i][k];
			for (int j = 0; j < n; ++j)
				f[i][j] += s * e[k][j];
		}
}
// create a matrix
	vector<vector<int> > createMatA(int m, int n){
		vector<vector<int> > ans(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++ )
			for (int j = 0; j < n; j++ )
				ans[i][j] = 6.6*i - 3.3*j ; // arbitrary value
		return ans;
}
	vector<vector<int> > createMatB(int m, int n) {
		vector<vector<int> > ans(m, vector<int>(n, 0));
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++)
				ans[i][j] = 100 + 2.2*i - 5.5*j ; // arbitrary value
		return ans;
	}

int main()
{
		clock_t startTime, endTime;
		
		// initializing matrices
		d = createMatA(50, 80);
		e = createMatB(80, 50);

		// f (m*n) = d (m*t) * e (t*n)
		int m = d.size();
		int t = d[0].size();
		int n = e[0].size();

		f.resize(m);
		for (int i = 0; i < m; ++i)
			f[i].resize(n);

		//single thread
		startTime = clock();
		mulsingle();
		endTime = clock();

		//display
		for (auto cur : f)
		{
			for (auto i : cur)
				cout << i << " ";
			cout << endl;
		}
		cout << "Single Thread Total Time : " << (double)(endTime - startTime)\
			/ CLOCKS_PER_SEC << " s" << endl;

		// initializing matrix
		f.clear();
		f.resize(m);
		for (int i = 0; i < m; ++i)
			f[i].resize(n);
		cout << endl;

		//multiple thread
		startTime = clock();
		int div = m / 5;
		std::thread threads[5];
		int cont = 0;
		for (int i = 0; i < 5; i++) {
			threads[i] = std::thread(mulMulti, cont, cont + div );
			cont = cont + div  ;
		}
		for (int i = 0; i < 5; i++) {
			threads[i].join();
		}
		endTime = clock();
		

		//dispLay
		for (auto cur : f)
		{
			for (auto i : cur)
				cout << i << " ";
			cout << endl;
		}
		cout << "Multiple Thread Total Time : " << (double)(endTime - startTime)
			/ CLOCKS_PER_SEC << " s" << endl;
		
		//this_thread: : sleep_for(chrono:: seconds(5));
		system("pause");
		return 0;
}