#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int h, w, d;
int grid[500][500];
int Order[250000], Father[250000];
bool bio[500][500], avail[250000];

const int dx[] = { 1, 0, -1, 0 };
const int dy[] = { 0, 1, 0, -1 };

bool valid( int x, int y ) { return 0 <= x && x < h && 0 <= y && y < w; }
bool cmp( int a, int b ) { return grid[a / w][a % w] > grid[b / w][b % w]; }
int getRoot( int x ) { return Father[x] == -1 ? x : (Father[x] = getRoot( Father[x] )); }

int main( void )
{
   freopen( "in", "r", stdin );

    int nround; scanf( "%d", &nround );

    for( int round = 0; round < nround; ++round ) {
        scanf( "%d %d %d", &h, &w, &d );

        for( int i = 0; i < h; ++i )
            for( int j = 0; j < w; ++j ) {
                scanf( "%d", &grid[i][j] );
                Order[i * w + j] = i * w + j;
                Father[i * w + j] = -1;
                bio[i][j] = avail[i * w + j] = false;
            }
        sort( Order, Order + h * w, cmp );

        int j = 0, k = 0;
        int res = 0;

        for( int i = 0; i < h * w; ++i ) {
//            printf( "x = %d, y = %d\n", Order[i] / w, Order[i] % w );
            while( j < h * w && grid[Order[j] / w][Order[j] % w] > grid[Order[i] / w][Order[i] % w] - d ) {
                int x = Order[j] / w, y = Order[j] % w;
                bio[x][y] = true;
                for( int l = 0; l < 4; ++l )
                    if( valid( x + dx[l], y + dy[l] ) && bio[x + dx[l]][y + dy[l]] ) {
                        int a = getRoot( Order[j] );
                        int b = getRoot( (x + dx[l]) * w + (y + dy[l]) );
                        if( a != b ) {
                            Father[a] = b;
                            if( avail[a] ) avail[b] = true;
                        }
                    }
                ++j;
            }
            while( k < h * w && grid[Order[k] / w][Order[k] % w] > grid[Order[i] / w][Order[i] % w] ) {
                avail[getRoot( Order[k] )] = true;
                ++k;
            }
            if( !avail[getRoot( Order[i] )] ) {
				++res;
				cout << Order[i] / w << " " << Order[i] % w << " ";
				cout << grid[Order[i] / w][Order[i] % w] << endl;
			}
        }

        printf( "%d\n", res );
    }

    return 0;
}
