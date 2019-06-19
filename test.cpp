#include <algorithm>
#include <cstdio>
using namespace std;
int can_pay[128];
int payed[128];
int idx[128];
bool cmp(int a, int b){
	return can_pay[a] > can_pay[b] || (can_pay[a] == can_pay[b] && a < b);
}
int min(int a, int b){ return a < b ? a : b; }
int main(void){
	int TC; scanf("%d", &TC);
	while(TC--){
		int n, price, sum = 0;
		scanf("%d %d", &price, &n);
		for(int i = 0; i < n; ++i){
			scanf("%d", &can_pay[i]);
			sum += can_pay[i];
			payed[i] = 0;
			idx[i] = i;
		}
		if(sum < price) puts("IMPOSSIBLE");
		else {
			sort(idx, idx + n, cmp);
			while(price > 0){
				int payers_num;
				// go to the first payer that has the least to spare
				for(payers_num = n; payers_num--; )
					if(can_pay[idx[payers_num]] > 0)
					    break;
				int rem = 0;
				int divis = can_pay[idx[payers_num]];
				int tp = divis * (++payers_num); // how much can be payed so far equally
				if(tp > price){
					divis = price / payers_num;
					rem = price % payers_num;
					tp = price;
				}
				// iterate
				for(int i = 0; i < payers_num; ++i){
					int x = idx[i];
					if(can_pay[x] > 0){
						payed[x] += divis;
						can_pay[x] -= divis;
						if(rem>0 && can_pay[x]>0) {
                            payed[x]++;
                            can_pay[x]--;
                            rem--;
						}
					}
				}
				price -= tp;
			}
			for(int i = 0; i < n; ++i){
				if(i) putc(32, stdout);
				printf("%d", payed[i]);
			}
			putc(10, stdout);
		}
	}
	return 0;
}
