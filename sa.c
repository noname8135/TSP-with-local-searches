#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define DEBUG 1

int city[442][2]; //city[id][0] = x of city id, city[id][1] = y of city id, 
int city_count;
float SCALE;
float T = 50;	//current temperature
int reheat_cd = 5;

float accept_prob(float delta_e){
	if(delta_e==0)
		return 0;
	const float e = 2.718281;
	if(DEBUG)
		printf("scaled delta_e=%f un=%f\n",delta_e*SCALE, delta_e);
	delta_e *= SCALE;	// normalized the scale

	return pow(e,(float)delta_e/T);
}

void cool(){
	T = T*0.99;
	return ;
}

void reheat(){
	 T+=reheat_cd*1.5;
	 return ;
}

bool if_pass_prob(float p){
	int num = (int)(p*1000000);
	if(rand()%1000000<=num)
		return 1;
	return 0;
}

float distance(int a, int b){
	int x_dis = city[a][0]-city[b][0];
	int y_dis = city[a][1]-city[b][1];
	return sqrt(x_dis*x_dis+y_dis*y_dis);
}

int route_distance(int* a){
	int i;
	float tot_dis = 0;
	for(i=0;i<city_count-1;i++)
		tot_dis += distance(a[i],a[i+1]);
	tot_dis += distance(a[0],a[city_count-1]);
	return tot_dis;
}

int* gen_neighbor(int* a,int i, int j){	//swap ith ,jth city of a and return
	int tmp;
	int* neighbor=(int*)malloc(sizeof(int)*city_count);
	for(tmp=0;tmp<city_count;tmp++){
		if(tmp==i)
			neighbor[tmp]=a[j];
		else if(tmp==j)
			neighbor[tmp]=a[i];
		else
			neighbor[tmp]=a[tmp];
	}
	return neighbor;
}

int line_dis_between_city(int* a,int pos){
	int left,right;
	left = pos-1 >=0 ? pos-1 : city_count-1;
	right = pos+1 < city_count ? pos+1 : 0;
	return distance(a[pos],a[left])+distance(a[pos],a[right]);
}

float neighbor_dis(int* a,int p1,int p2){
	int left,right;
	float ans;
	left = p1-1 >=0 ? p1-1 : city_count-1;
	if(p1>p2){
		left = p1; p1=p2; p2=left;
	}
	if(p1+1==p2)
		right=p1;
	else
		right = p1+1 < city_count ? p1+1 : 0;
	int tmp[3];
	tmp[0]=a[left];  tmp[1]=a[p2]; tmp[2]=a[right];
	ans = line_dis_between_city(tmp,1);
	if(p1+1==p2)
		left = p2;
	else
		left = p2-1 >=0 ? p2-1 : city_count-1;
	right = p2+1 < city_count ? p2+1 : 0;
	tmp[0] = a[left]; tmp[1] = a[p1]; tmp[2] = a[right];
	return ans + line_dis_between_city(tmp,1);
}

bool if_good_neighbor(int* ori,int c1_pos,int c2_pos){	
	//compare distance of original path and the path after exchanging city1 and city2
	int ori_path,new_path;
	int* neighbor=gen_neighbor(ori,c1_pos,c2_pos);
	ori_path = line_dis_between_city(ori,c1_pos)+line_dis_between_city(ori,c2_pos);
	new_path = line_dis_between_city(neighbor,c1_pos)+line_dis_between_city(neighbor,c2_pos);
	if(DEBUG)
		printf("if_good_neighbor ori_path:%d new_path:%d\n", ori_path,new_path);
	return (new_path<ori_path?1:0);
}

int* get_neighbor(int* a){
	int* neighbor; 
	int m=rand()%city_count, n=rand()%city_count,i,j;
	float prob,ori_base,ori_path,new_path;
	if(m>n){
		i=m; m=n; n=i;
	}
	if(DEBUG)
		printf("m=%d n=%d\n", m,n);
	for(i=m;i<city_count-1;i++){
		ori_base = line_dis_between_city(a,i);
		for(j=(i<n?n:i+1);j<city_count;j++){
			if(DEBUG)
				printf("T=%f ori=%f neighbor_dis=%f good:%d i=%d j=%d ai=%d aj=%d\n",T,ori_base+line_dis_between_city(a,j),neighbor_dis(a,i,j),if_good_neighbor(a,i,j),i,j,a[i],a[j]);
			ori_path = ori_base+line_dis_between_city(a,j);
			new_path= neighbor_dis(a,i,j);
			if(ori_path>new_path)
				return gen_neighbor(a,i,j);
			prob = accept_prob(ori_path-new_path);
			if(DEBUG)
				printf("prob=%f\n",prob);
			if(if_pass_prob(prob)){
				if(DEBUG)
					printf("AAACCCCEEEEPPPTTT=================\n");
				return gen_neighbor(a,i,j);
			}
		}
	}

	for(i=m;i<n;i++){
		ori_base = line_dis_between_city(a,i);
		for(j=n;j>i;j--){
			if(DEBUG)
				printf("T=%f ori=%f neighbor_dis=%f good:%d i=%d j=%d ai=%d aj=%d\n",T,ori_base+line_dis_between_city(a,j),neighbor_dis(a,i,j),if_good_neighbor(a,i,j),i,j,a[i],a[j]);
			ori_path = ori_base+line_dis_between_city(a,j);
			new_path= neighbor_dis(a,i,j);
			if(ori_path>new_path)
				return gen_neighbor(a,i,j);
			prob = accept_prob(ori_path-new_path);
			if(DEBUG)
				printf("prob=%f  ",prob);
			if(if_pass_prob(prob)){
				if(DEBUG)
					printf("AAACCCCEEEEPPPTTT=================\n");
				return gen_neighbor(a,i,j);
			}
		}
	}

	for(i=m-1;i>=0;i--){
		ori_base = line_dis_between_city(a,i);
		for(j=n;j>i;j--){
			if(DEBUG)
				printf("T=%f ori=%f neighbor_dis=%f good:%d i=%d j=%d ai=%d aj=%d\n",T,ori_base+line_dis_between_city(a,j),neighbor_dis(a,i,j),if_good_neighbor(a,i,j),i,j,a[i],a[j]);
			ori_path = ori_base+line_dis_between_city(a,j);
			new_path= neighbor_dis(a,i,j);
			if(ori_path>new_path)
				return gen_neighbor(a,i,j);
			prob = accept_prob(ori_path-new_path);
			if(DEBUG)
				printf("prob=%f\n",prob);
			if(if_pass_prob(prob)){
				if(DEBUG)
					printf("AAACCCCEEEEPPPTTT=================\n");
				return gen_neighbor(a,i,j);
			}
		}
	}
	if(DEBUG)
		printf("GET N success\n");
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

void hill(){
	int i,j,ans,count=0;
	int* now_state = get_start_state();
	while(1){
		count++;
		if(T<reheat_cd/2 && reheat_cd){
			reheat();
			reheat_cd--;
		}
		if(DEBUG)
			printf("route_distance:%d\n",route_distance(now_state));
		ans=route_distance(now_state);
		if((now_state = get_neighbor(now_state)) == NULL)
			break;
		cool();
	}
	printf("Final distance:%d %d, ",ans,count);
	return;
}

int main(int argc,char** argv){
	clock_t start=clock(), stop;
	srand(time(NULL));
	char line[70];
	int max_x,max_y,min_x,min_y;
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
		SCALE = 100.0 / (float)((max_x-min_x) + (max_y-min_y));
	}

	if(argc>2 && !strcmp(argv[2],"test")){
		T=1;
		printf("%f %f\n",accept_prob(-30),accept_prob(-10));
		T=10;
		printf("%f %f\n",accept_prob(-30),accept_prob(-10));
		T=20;
		printf("%f %f\n",accept_prob(-30),accept_prob(-10));
		T=30;
		printf("%f %f\n",accept_prob(-30),accept_prob(-10));
		return 0;
		int a[51] = {28, 20, 15, 49, 33, 29, 8 ,48 ,9 ,38 ,32 ,44, 14, 43, 41, 18, 39, 40, 12, 24, 13, 23, 42, 6 ,22 ,47 ,5,26, 50, 45, 11, 46, 17, 3 ,16 ,36 ,4, 37, 10, 31, 0 ,21 ,7 ,25 ,30, 27, 2 ,35 ,34,19,1};
		printf("%d\n",route_distance(a));
		return 0;
	}
	hill();
	if(DEBUG)
		printf("main end!\n");
	stop=clock();
	printf("total execution time: %f\n",(double)(stop-start)/(double)CLOCKS_PER_SEC);
	return 0;
}