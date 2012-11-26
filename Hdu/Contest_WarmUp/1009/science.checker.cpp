#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <set>
#include <cstdlib>
#include <cctype>

using namespace std;

#define MAXN 80

int N;
bool A[MAXN][MAXN];

const char* infile;
const char* outfile;
const char* ansfile;
const char* resfile;

//judgements are "accepted", "Wrong Answer", or "Run-time Error"
void writeOutput(const char *res, const char *reason) {
  FILE *fd = fopen(resfile, "w");
  printf("writing to: %s\n", resfile);
  fprintf(fd, "<?xml version=\"1.0\"?>\n");
  fprintf(fd, "<result outcome = \"%s\"  security=\"%s\"> %s </result>\n", res, resfile, reason);
  fclose(fd);
}

void ok() {
  writeOutput("accepted", "Good");
}

void bad_read() {
  writeOutput("Wrong Answer", "Format Error");
  exit(0);
}

void excess_output() {
  writeOutput("Wrong Answer", "Excess Output");
  exit(0);
}

void bad_wa() {
  writeOutput("Wrong Answer", "Wrong Answer");
  exit(0);
}

char read_char() {
  int ch = cin.get();
  if(ch == -1) bad_read();
  return (char)ch;
}

int read_int() {
  long long x = 0;
  char ch = read_char();
  bool neg = ch == '-';
  if(neg) ch = read_char();
  if(!isdigit(ch)) bad_read();
  while(isdigit(ch)) {
    x *= 10;
    x += ch - '0';
    ch = cin.get();
    if(x > 0x80000000ll) bad_read();
  }
  if(ch != -1) cin.unget();
  if(neg) x *= -1;
  if(x < (int)0x80000000 || (int)0x7FFFFFFF < x) bad_read();
  return (int)x;
}

void read_expect(char ch) {
  if(read_char() != ch) bad_read();
}

void read_line() {
  for(int ch = cin.get(); ; ch = cin.get()) {
    if(ch == '\r') {
      ch = cin.get();
      if(ch != -1 && ch != '\n') cin.unget();
      break;
    } else if(ch == -1 || ch == '\n') {
      break;
    } else if(!isspace(ch)) {
      bad_read();
    }
  }
}

void read_str(const char* str) {
  for(; *str; str++) {
    read_expect(*str);
  }
}

void read_eof() {
  if(cin.get() != -1) excess_output();
}

int main(int argc, char** argv) {
  if(argc != 5) {
    printf("%s infile outfile ansfile resfile\n", argv[0]);
    return 1;
  }
  infile = argv[1]; // This is the input file
  outfile = argv[2]; // This is the contestant's output
  ansfile = argv[3]; // This is the answer file 
  resfile = argv[4]; // This is the filename to pass to writeOutput

  int et = 0;
  FILE* fin = fopen(ansfile, "r");
  freopen(outfile, "r", stdin);

  FILE* ifin=fopen(infile,"r");
  int ii = 0;
  int cnt = 0;
  for(fscanf(ifin, "%d", &N); N; fscanf(ifin, "%d", &N)) {
	  cnt++;
    et++;
    for(int i = 0; i < N; i++) {
      char buf[90];
      fscanf(ifin, "%80s", buf);
      for(int j = 0; j < N; j++) {
        A[i][j] = buf[j] == 'Y';
      }
    }
    int eres; fscanf(fin, "%d", &eres);

/*
    read_str("Case ");
    int t = read_int();
    if(t != et) bad_read();
    read_str(": ");
    
    if(eres == 0) {
      read_str("NO SCIENCE");
      read_line();
      continue;
    }
*/

    int res = read_int();
    read_line();

    if(res != eres) bad_wa();

    vector<vector<int> > V(eres, vector<int>(N, -1));
    for(int i = 0; i < res; i++) {
      set<int> st;
      for(int j = 0; j < N; j++) {
        if(j) read_expect(' ');
        V[i][j] = read_int();
        if(V[i][j] <= 0 || V[i][j] > N) bad_wa();
        if(!A[V[i][j] - 1][j]) {
			printf("No.%d\n", cnt);
			puts("Wrong Answer");
			bad_wa();
		}
        A[V[i][j] - 1][j] = false;
        st.insert(V[i][j]);
      }
      if(st.size() != N) bad_wa();
      read_line();
    }
  }
  read_eof();
  ok();
  return 0;
}
