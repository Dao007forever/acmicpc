#include <cstdio>
#include <cstring>
using namespace std;

typedef long long llint;

llint gcd(llint a, llint b) {
	while (b) {
		llint tmp = b;
		b = a % b;
		a = tmp;
	}
	return a;
}

struct Num {
	llint a, b;
	
	Num(llint a, llint b) : a(a), b(b) {};
	Num() {};
	
	void simplify() {
		if (a == 0) {
			b = 1;
			return;
		}
		
		llint g = gcd(a, b);
		
		if (g < 0) g = -g;
		if (b < 0) {
			a = -a; b = -b;
		}
		a /= g; b /= g;
	}
};

Num operator*(Num a, Num b) {
	return Num(a.a * b.a, a.b * b.b);
}

Num operator/(Num a, Num b) {
	return Num(a.a * b.b, a.b * b.a);
}

Num operator-(Num a, Num b) {
	return Num(a.a * b.b - b.a * a.b, a.b * b.b);
}

Num operator+(Num a, Num b) {
	return Num(a.a * b.b + b.a * a.b, a.b * b.b);
}



char str[50]; int N;
int startpos[50];
bool hasx[50];

void process0(int p) {
	if (str[p] == 'X' || str[p] >= '0' && str[p] <= '9') {
		startpos[p] = p;
		hasx[p] = str[p] == 'X';
	} else {
		process0(p - 1);
		process0(startpos[p - 1] - 1);
		startpos[p] = startpos[startpos[p - 1] - 1];
		hasx[p] = hasx[p - 1] || hasx[startpos[p - 1] - 1];
	}
}

Num calc(int p, Num x = Num(0, 0)) {
	if (str[p] == 'X') return x;
	else if (str[p] >= '0' && str[p] <= '9') return Num(str[p] - '0', 1);
	else {
		Num a = calc(startpos[p - 1] - 1, x);
		Num b = calc(p - 1, x);
		if (str[p] == '+') return a + b;
		else if (str[p] == '-') return a - b;
		else if (str[p] == '*') return a * b;
		else return a / b;
	}
}

Num ans;
int solve(int p, Num b) {
	if (!hasx[p]) return (calc(p) - b).a == 0;
	
	if (str[p] == 'X') {
		ans = b;
		return 2;
	}
	
	int posa = startpos[p - 1] - 1;
	int posb = p - 1;
	
	if (str[p] == '+') {
		if (hasx[posa]) return solve(posa, b - calc(posb));
		else return solve(posb, b - calc(posa));
	} else if (str[p] == '-') {
		if (hasx[posa]) return solve(posa, b + calc(posb));
		else return solve(posb, calc(posa) - b);
	} else if (str[p] == '*') {
		if (hasx[posa]) {
			if (calc(posb).a == 0) return b.a == 0;
			else return solve(posa, b / calc(posb));
		} else {
			if (calc(posa).a == 0) return b.a == 0;
			else return solve(posb, b / calc(posa));
		}
	} else {
		if (hasx[posa]) {
			return solve(posa, b * calc(posb));
		} else {
			if (b.a == 0) return calc(posa).a == 0;
			
			int ans0 = solve(posb, calc(posa) / b);
			if (ans0 == 2 && calc(posb, ans).a == 0) ans0 = 0;
			return ans0;
		}
	}
}

void solve() {
	process0(N - 1);
	int ans0 = solve(N - 1, Num(0, 1));
	if (ans0 == 0) printf("NONE\n");
	else if (ans0 == 1) printf("MULTIPLE\n");
	else {
		ans.simplify();
		printf("X = %I64d/%I64d\n", ans.a, ans.b);
	}
}

int main() {
//	freopen("equation.in", "r", stdin);
//	freopen("equation.out", "w", stdout);

	freopen("in", "r", stdin);
	char str2[100];
	while (gets(str2)) {
		int str2l = strlen(str2);
		N = 0;
		for (int i = 0; i < str2l; i += 2)
			str[N++] = str2[i];
		solve();
	}
	
	return 0;
}

