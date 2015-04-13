#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "uthash.h"


int city_count;
int city_dis[442][442]; //distance between city, city_dis[id1][id2] = distance(id1,id2)
int** city; //city[id][0] = x of city id, city[id][1] = y of city id

struct tabu {
    short* city_route;                    /* key */
    int tabu_cd;
    UT_hash_handle hh;         /* makes this structure hashable */
};

struct tabu *route_in_tabu = NULL;

struct tabu *find_route(short* a) {
    struct tabu *s=NULL;
    HASH_FIND( hh, route_in_tabu, a, sizeof(short)*city_count, s );  /* s: output pointer */
    return s;
}

void add_tabu_route(short* new_route) {
    struct tabu *s = (struct tabu*)malloc(sizeof(struct tabu));
    int i;
	  s->city_route = new_route;
      s->tabu_cd = city_count/5;
      HASH_ADD_KEYPTR( hh,route_in_tabu,s->city_route, sizeof(short)*city_count, s );  /* id: name of key field */
    return;
}

void delete_route(struct tabu *a) {
    HASH_DEL( route_in_tabu, a);  /* user: pointer to delete */
    free(a->city_route);
    free(a);
}

void delete_all() {
  struct tabu *current_user, *tmp;
  HASH_ITER(hh, route_in_tabu, current_user, tmp) {
  	free(current_user->city_route);
    HASH_DEL(route_in_tabu,current_user);  /* delete it (users advances to next) */
    free(current_user);            /* free it */
  }
}

int distance(int a, int b){
	int x_dis = city[a][0]-city[b][0];
	int y_dis = city[a][1]-city[b][1];
	return round(sqrt(x_dis*x_dis+y_dis*y_dis));
}

int route_distance(short* a){
	int i,tot_dis = 0;
	for(i=0;i<city_count-1;i++)
		tot_dis += city_dis[a[i]][a[i+1]];
	tot_dis += city_dis[a[0]][a[city_count-1]];
	return tot_dis;
}

short* gen_neighbor(short* a,int i, int j){	//swap the order of ith~jth city of array a and return
	int tmp,k;
	short* neighbor=(short*)malloc(sizeof(short)*city_count);
	for(tmp=0;tmp<i;tmp++)
		neighbor[tmp]=a[tmp];
	for(tmp=j+1;tmp<city_count;tmp++)
		neighbor[tmp]=a[tmp];
	for(k=0;k<=j-i;k++)
		neighbor[i+k]=a[j-k];
	return neighbor;
}

int neighbor_dis(short* a,int p1,int p2, int ori_part){
	int p1_left,p2_right,tmp,ans;
	if(p1>p2){
		tmp=p1; p1=p2; p2=tmp;
	}
	p1_left = (p1==0?city_count-1:p1-1);
	p2_right = (p2==city_count-1?0:p2+1);
	return city_dis[a[p1_left]][a[p2]]+city_dis[a[p2_right]][a[p1]] - ori_part;
}

short* get_neighbor(short* a){
	int i,j,j_right,min_route_dis = 999999,tmp_dis;
	float ori_base;
	struct tabu *s=NULL;
	short* neighbor,*best;
	for(i=0;i<city_count-1;i++){
		ori_base = i==0?city_dis[a[i]][a[city_count-1]]:city_dis[a[i]][a[i-1]];
		for(j=i+1;j<city_count;j++){
			if (j-i>=city_count-2)
				continue;
			j_right = (j==city_count-1?0:j+1);
			tmp_dis = neighbor_dis(a,i,j,ori_base+city_dis[a[j]][a[j_right]]);
			if(tmp_dis && tmp_dis < min_route_dis){
				neighbor = gen_neighbor(a,i,j);
				s = find_route(neighbor);
				if(s){
					free(neighbor);
					if(--s->tabu_cd==0)
						delete_route(s);
				}
				else{
					best = neighbor;
					min_route_dis = tmp_dis;
				}
			}	
		}
	}
	add_tabu_route(a);
	if(best)
		return best;
	return a;
}

short* get_start_state(){
	short* start_state = (short*)malloc(sizeof(short)*city_count);
	bool* gened = (bool*)malloc(sizeof(bool)*city_count);
	memset(gened,0,sizeof(bool)*city_count);
	int gen_count = 0,gen_id;
	while(gen_count<city_count){
		gen_id = rand()%city_count;
		while(gened[gen_id]){
			if(++gen_id==city_count)
				gen_id = 0;
		}
		gened[gen_id] = 1;
		start_state[gen_count++] = gen_id;
	}
	return start_state;
}

int hill(){
	int i,j,ans,best=999999,loop_count=35000000;
	short* now_state = get_start_state();
	while(--loop_count){
		if(loop_count%1000000==0)
			HASH_CLEAR(hh,route_in_tabu);
		ans=route_distance(now_state);
		if(ans<best){
			best=ans;
			printf("%d\n",best);
		}
		if((now_state = get_neighbor(now_state)) == NULL)
			break;
	}
	return best;
}

int main(int argc,char** argv){
	clock_t start=clock(), stop;
	srand(time(NULL));
	char line[70];
	int jmp_counter = 6, i,j;
	float x,y;
	
	city = (int**) malloc(sizeof(int*)*442);
	for(i=0;i<442;i++)
		city[i] = (int*) malloc(sizeof(int)*2);
	FILE *f;
	if(argc<2){
		printf("format: ./hill filename\nfiles => eil51.tsp, lin105.tsp, pcb442.tsp\n");
		exit(0);
	}
	f = fopen(argv[1],"r");
	city_count = 0;
	while(fgets(line,70,f)!=NULL){
		if(strstr(line,"EOF")||line[0]=='\n')
			break;
		else if(jmp_counter){
			jmp_counter --;
			continue;
		}
		sscanf(line,"%*d %E %E",&x,&y);
		city[city_count][0] = (int)x, city[city_count++][1] = (int)y;
		for(i=0;i<city_count-1;i++)
			city_dis[city_count-1][i] = city_dis[i][city_count-1] = distance(i,city_count-1);
	}
	int counter=20,tmp;
	tmp=hill();
	printf("Final distance: %d\n",tmp);
	stop=clock();
	printf("total execution time: %f\n",(double)(stop-start)/(double)CLOCKS_PER_SEC);
	return 0;
}