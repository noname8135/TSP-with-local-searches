#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int city[442][2]; //city[id][0] = x of city id, city[id][1] = y of city id, 
int city_count;
int city_dis[442][442]; //distance between city, city_dis[id1][id2] = distance(id1,id2)
float SCALE;
float T;	//current temperature
int reheat_cd;

float accept_prob(float delta_e){
	if(delta_e==0)
		return rand()%2?1:0;
	return exp(delta_e*SCALE /T); // normalized the scale;
}

float distance(int a, int b){
	int x_dis = city[a][0]-city[b][0];
	int y_dis = city[a][1]-city[b][1];
	return round(sqrt(x_dis*x_dis+y_dis*y_dis));
}

int route_distance(int* a){
	int i,tot_dis = 0;
	for(i=0;i<city_count-1;i++)
		tot_dis += city_dis[a[i]][a[i+1]];
	tot_dis += city_dis[a[0]][a[city_count-1]];
	return tot_dis;
}

int* gen_neighbor(int* a,int i, int j){	//swap the order of ith~jth city of array a and return
	int tmp,k;
	int* neighbor=(int*)malloc(sizeof(int)*city_count);
	if(i>j){
		tmp = i; i = j; j = tmp;
	}
	for(tmp=0;tmp<i;tmp++)
		neighbor[tmp]=a[tmp];
	for(tmp=j+1;tmp<city_count;tmp++)
		neighbor[tmp]=a[tmp];
	for(k=0;k<=j-i;k++)
		neighbor[i+k]=a[j-k];
	free(a);
	return neighbor;
}

float line_dis_between_city(int* a,int pos){
	int left,right;
	left = pos-1 >=0 ? pos-1 : city_count-1;
	right = pos+1 < city_count ? pos+1 : 0;
	return distance(a[pos],a[left])+distance(a[pos],a[right]);
}

int neighbor_dis(int* a,int p1,int p2, int ori_part){
	int p1_left,p2_right,tmp,ans;

	if(p1>p2){
		tmp=p1; p1=p2; p2=tmp;
	}
	p1_left = (p1==0?city_count-1:p1-1);
	p2_right = (p2==city_count-1?0:p2+1);
	return ori_part - city_dis[a[p1_left]][a[p2]] - city_dis[a[p2_right]][a[p1]] ;
}

int* get_neighbor(int* a){
	int m=rand()%city_count, n=rand()%city_count,i,j,j_right,tmp;
	float prob,ori_base;
	if(m>n){
		i=m; m=n; n=i;
	}
	for(i=m;i<city_count-1;i++){
		ori_base = i==0?city_dis[a[i]][a[city_count-1]]:city_dis[a[i]][a[i-1]];
		for(j=(i<n?n:i+1);j<city_count;j++){
			if (j-i>=city_count-2)
				continue;
			j_right = (j==city_count-1?0:j+1);
			if((tmp=neighbor_dis(a,i,j,ori_base+city_dis[a[j]][a[j_right]]))>0)
				return gen_neighbor(a,i,j);
			prob = accept_prob(tmp);
			if(rand()/(0.0+RAND_MAX) < prob)
				return gen_neighbor(a,i,j);
		}
	}

	for(i=m;i<n;i++){
		ori_base = i==0?city_dis[a[i]][a[city_count-1]]:city_dis[a[i]][a[i-1]];
		for(j=n;j>i;j--){
			if (j-i>=city_count-2)
				continue;
			j_right = (j==city_count-1?0:j+1);
			if((tmp=neighbor_dis(a,i,j,ori_base+city_dis[a[j]][a[j_right]]))>0)
				return gen_neighbor(a,i,j);
			prob = accept_prob(tmp);
			if(rand()/(0.0+RAND_MAX) < prob)
				return gen_neighbor(a,i,j);
		}
	}

	for(i=m-1;i>=0;i--){
		ori_base = i==0?city_dis[a[i]][a[city_count-1]]:city_dis[a[i]][a[i-1]];
		for(j=n;j>i;j--){
			if (j-i>=city_count-2)
				continue;
			j_right = (j==city_count-1?0:j+1);
			if((tmp=neighbor_dis(a,i,j,ori_base+city_dis[a[j]][a[j_right]]))>0)
				return gen_neighbor(a,i,j);
			prob = accept_prob(tmp);
			if(rand()/(0.0+RAND_MAX) < prob)
				return gen_neighbor(a,i,j);
		}
	}
	return NULL;
}

int* get_start_state(){
	int* start_state = (int*)malloc(sizeof(int)*city_count);
	bool* gened = (bool*)malloc(sizeof(bool)*city_count);
	memset(gened,0,sizeof(bool)*city_count);
	int gen_count = 0,gen_id;
	while(gen_count<city_count){
		gen_id = rand()%city_count;
		while(gened[gen_id]){
			gen_id++;
			if(gen_id==city_count)
				gen_id = 0;
		}
		gened[gen_id] = 1;
		start_state[gen_count++] = gen_id;
	}
	return start_state;
}

int hill(){
	int i,j,ans,count=0;
	int* now_state = get_start_state();
	while(1){
		count++;
		if(T<reheat_cd/2 && reheat_cd){
			T+=reheat_cd/2;	//reheat
			reheat_cd--;
		}
		ans=route_distance(now_state);
		if((now_state = get_neighbor(now_state)) == NULL)
			break;
		T = T*0.9999; //cool 
		if(T<=0.000001)
			break;
	}
	return ans;
}

int main(int argc,char** argv){
	clock_t start=clock(), stop;
	srand(time(NULL));
	char line[70];
	int max_x,max_y,min_x,min_y,i;
	int jmp_counter = 6;
	float x,y;
	FILE *f;
	if(argc<2){
		printf("format: ./sa filename\nfiles => eil51.tsp, lin105.tsp, pcb442.tsp\n");
		exit(0);
	}
	f = fopen(argv[1],"r");
	printf("\nsimulated annealing => %s\n---------------------\n",argv[1]);
	city_count = 0;
	max_x=max_y=-1, min_x=min_y=99999999;
	while(fgets(line,70,f)!=NULL){
		if(strstr(line,"EOF")||line[0]=='\n')
			break;
		else if(jmp_counter){
			jmp_counter --;
			continue;
		}
		sscanf(line,"%*d %E %E",&x,&y);
		city[city_count][0] = (int)x, city[city_count++][1] = (int)y;
		if(x>max_x){
			max_x=x;
		}
		if(x<min_x){
			min_x=x;
		}
		if(y>max_y){
			max_y=y;
		}
		if(y<min_y){
			min_y=y;
		}
		SCALE = 180.0 / (float)((max_x-min_x) + (max_y-min_y));
		for(i=0;i<city_count-1;i++)
			city_dis[city_count-1][i] = city_dis[i][city_count-1] = distance(i,city_count-1);
	}
	int counter=20, tmp, min=9999999;
	float tot=0;
	while(counter--){
		T=10.0;
		reheat_cd = 5;
		tmp=hill();
		if(tmp<min)
			min = tmp;
		tot+=(float)tmp;
		printf("Final distance: %d\n",tmp);
	}
	printf("min=%d avg=%f\n", min, tot/20);
	stop=clock();
	printf("total execution time: %f\n",(double)(stop-start)/(double)CLOCKS_PER_SEC);
	return 0;
}