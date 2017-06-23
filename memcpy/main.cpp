#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <map>
#include <deque>
#include <set>
#include <vector>
#include <cstdlib>
#include <bitset>
#include <ctime>
#include <fstream>
#include <cstdint>
#include <stddef.h>
#include <emmintrin.h>

#define pb push_back
#define mp make_pair
#define ll long long
#define F first
#define S second


using namespace std;

void mcpy4bit(void* to,void const* from,size_t c){
    size_t off = 0;
    size_t operations;
    while(off<c){
        asm("movl (%0), %%eax\n"
            "movl %%eax, (%1)"
            :
            :"r"((char *)from+off),"r"((char *)to+off)
            );
            off+=4;
            //cout<<off<<endl;
    }
}
void memcpy_for_gta(void *dst, const void *src, size_t sz) {

    size_t start_block = 0;

    if(sz<32){
        mcpy4bit(dst,src,sz);
        return;
    }
    size_t offset = 0;
    for(size_t offset = 0;((size_t)dst+offset)%16!=0;offset++){
		*((char *)dst + offset) = *((char *)src + offset);
		offset++;
	}

    size_t before_block = (sz - start_block) % 16;

    __m128i reg;
    for (size_t i = start_block; i < sz - before_block; i += 16) {

        __asm__("movdqu\t" "(%1), %0\n"
                "movntdq\t" "%0,(%2)"
        	:"=x"(reg)
        	:"r"((char *) src + i),"r"((char *) dst + i)
            :"memory");
    }


    for (int i = (sz - before_block) ; i < sz ; i++)  {
        *((char *)dst + i) = *((char *)src + i);
    }
    _mm_sfence();

}
char a[1111111],b[1111111],c;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n = 1111111;
    for(int i=0;i<n;i++){
        a[i] = 'a'+i;
    }
    std::clock_t begin = std::clock();
    memcpy_for_gta(&b, &a, sizeof(a));
    return 0;
}
