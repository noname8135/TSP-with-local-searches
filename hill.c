#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

#define DEBUG 0

int city[442][2]; //city[id][0] = x of city id, city[id][1] = y of city id, 
int city_count;

int distance(int a, int b){
	int x_dis = city[a][0]-city[b][0];
	int y_dis = city[a][1]-city[b][1];
	return sqrt(x_dis*x_dis+y_dis*y_dis);
}

int route_distance(int* a){
	int i,tot_dis = 0;
	for(i=0;i<city_count-1;i++)
		tot_dis += distance(a[i],a[i+1]);
	tot_dis += distance(a[0],a[city_count-1]);
	return tot_dis;
}
/*
int get_nearest(int a,int city_num){	//get nearest neighbor of city a
	int i,nearest_id,min_dis=999999999;
	float dis;
	bool visited[442] = {0};
	for(i=0;i<city_num;i++){
		if(!visited[i] && (dis=distance(a,i)) < min_dis){
			min_dis = dis, nearest_id = i;
		}
	}
	return nearest_id;
}
*/
int* gen_neighbor(int* a,int i, int j){	//swap ith ,jth city of a and return
	if(DEBUG)
		printf("gen_start\n");
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
	if(DEBUG)
		printf("gen_end\n");
	return neighbor;
}
int line_dis_between_city(int* a,int pos){
	int left,right;
	left = pos-1 >=0 ? pos-1 : city_count-1;
	right = pos+1 < city_count ? pos+1 : 0;
	return distance(a[pos],a[left])+distance(a[pos],a[right]);
}
bool if_good_neighbor(int* ori,int c1_pos,int c2_pos){	
	//compare distance of original path and the path after exchanging city1 and city2
	int ori_path,new_path;
	int* neighbor=gen_neighbor(ori,c1_pos,c2_pos);
	ori_path = line_dis_between_city(ori,c1_pos)+line_dis_between_city(ori,c2_pos);
	new_path = line_dis_between_city(neighbor,c1_pos)+line_dis_between_city(neighbor,c2_pos);
	if(DEBUG)
		printf("ori_path:%d new_path:%d GOOD:%d\n", ori_path,new_path,new_path<ori_path?1:0);
	return (new_path<ori_path?1:0);
}

int* get_neighbor(int* a){
	int* neighbor; 
	int m=rand()%city_count, n=rand()%city_count,i,j;
	if(m>n){
		i=m; m=n; n=i;
	}
	if(DEBUG)
		printf("m=%d n=%d\n", m,n);
	for(i=m;i<n;i++){
		for(j=n;j<city_count;j++){
			if(if_good_neighbor(a,i,j)){
				neighbor = gen_neighbor(a,i,j);
				return neighbor;
			}
			else if(DEBUG)
				printf("1ori:%d nei:%d i=%d j=%d\n",route_distance(a),route_distance(neighbor),i,j);
		}
	}
	for(i=n;i<city_count-1;i++){
		for(j=i+1;j<city_count;j++){
			if(if_good_neighbor(a,i,j)){
				neighbor = gen_neighbor(a,i,j);
				return neighbor;
			}
			else if(DEBUG)
				printf("1ori:%d nei:%d i=%d j=%d\n",route_distance(a),route_distance(neighbor),i,j);
		}
	}

	for(i=m;i<n;i++){
		for(j=n;j>i;j--){
			if(if_good_neighbor(a,i,j)){
				neighbor = gen_neighbor(a,i,j);
				return neighbor;
			}
			else if(DEBUG)
				printf("2ori:%d nei:%d i=%d j=%d\n",route_distance(a),route_distance(neighbor),i,j);	
		}
	}

	for(i=m-1;i>=0;i--){
		for(j=n;j>i;j--){
			if(if_good_neighbor(a,i,j)){
				neighbor = gen_neighbor(a,i,j);
				return neighbor;
			}
			else if(DEBUG)
				printf("3ori:%d nei:%d i=%d j=%d\n",route_distance(a),route_distance(neighbor),i,j);
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
	int i,j,ans;
	/*
	int nearest,ans[443],ans_count=1,walker = rand()%100+1; //random start
	visited[walker] = 1;
	while(ans_count++ < visited_count){
		nearest = get_nearest(walker,visited_count);
	}*/
	
	int* now_state = get_start_state();
	while(1){
		if(DEBUG)
			printf("route_distance:%d\n",route_distance(now_state));
		ans=route_distance(now_state);
		if((now_state = get_neighbor(now_state)) == NULL)
			break;
	}
	printf("Final distance:%d\n",ans);
	/*
	printf("%d\n",route_distance(now_state));
	for(i=0;i<city_count;i++)
		printf("%d ",now_state[i]);
	printf("\n");*/
	return;
}

int main(int argc,char** argv){
	srand(time(NULL));
	char line[70];
	int jmp_counter = 6;
	float x,y;
	FILE *f;
	if(argc<2){
		printf("format: ./hill filename\nfiles => eil51.tsp, lin105.tsp, pcb442.tsp\n");
		exit(0);
	}
	f = fopen(argv[1],"r");
	printf("hill climbing => %s\n---------------------\n",argv[1]);
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
	}

	hill();
	if(DEBUG)
		printf("main end!\n");
	return 0;
}