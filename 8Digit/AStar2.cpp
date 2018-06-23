//author:strewen
//Create On:2018/06/09
//describe:
//八数码问题广度优先搜索+启发式搜索(将牌不在位的距离和)求解
#include<iostream>
#include<queue>
#include<bitset>
#include<math.h>
#include"global.h"

using namespace std;

struct StateNode
{
    int state_hash;   //状态码，康托hash码
	string state;     //状态
	int blank;        //空格位置
    string extendWay="";  //路径
	int cost;
	StateNode(int h,string s,int b,string e,int c){state=h;state=s;blank=b;extendWay=e;cost=c;}
    ~StateNode(){}
	//比较函数
	friend bool operator <(StateNode n1,StateNode n2){
		return n1.cost>n2.cost;
	}
};

static string end_state="123804765";
static priority_queue<StateNode> opened;
static bitset<362880> closed={0};
static string init_state;
static int fac[]={1,1,2,6,24,120,720,5040,40320};
static string direction[4]={"U","D","L","R"};
static int dir_x[4]={0,0,-1,1};
static int dir_y[4]={-1,1,0,0};
static int create_node,expand_node;
static int cantorExpansion(string state)
{
	int len=state.length();
	int cantor_hash=0;
	for(int i=0;i<len;i++){
		int lt_count=0;
		for(int j=i+1;j<len;j++)
			if(state[i]>state[j])
				lt_count++;
		cantor_hash+=lt_count*fac[len-i-1];
	}
	return cantor_hash;
}

static int end_hash=cantorExpansion(end_state);

//代价函数(将牌不在位距离和)
static int getCost(string s)
{
	int cost=0;
	char number[]={'1','2','3','4','5','6','7','8'};
	for(int i=0;i<8;i++)
	{
		int s_pos=s.find(number[i]),end_pos=end_state.find(number[i]);
		int s_row=floor(s_pos/3),s_col=s_pos%3;
		int end_row=floor(end_pos/3),end_col=end_pos%3;
		cost=abs(end_row-s_row)+abs(end_col-s_col)+cost;
	}
	return cost;
}

//初始化函数
static int getInitState(string init)
{
    create_node=0;
    expand_node=0;
    closed={0};
    while(!opened.empty()){
        opened.pop();
    }
	init_state=init;
	int blank_pos=init_state.find('0',0),cost=getCost(init_state);
	int hash_code=cantorExpansion(init_state);
	create_node++;
	if(hash_code==end_hash)
		return 0;
	StateNode new_node={hash_code,init_state,blank_pos,"",cost};
	opened.push(new_node);
	closed[hash_code]=1;
	return 1;
}

string AStar2(string init,int& c_n,int& e_n)
{
	if(!getInitState(init))
	{
        c_n=create_node;
        e_n=expand_node;
		return "Input Is Answer!";
	}
	while(!opened.empty()){
		StateNode node=opened.top();
		opened.pop();
		if(expand_node!=0)
			expand_node--;
		int row=floor(node.blank/3),col=node.blank%3,hash_code;
		for(int i=0;i<4;i++){
			string stat=node.state;
			int cost=getCost(stat);
			int extend_row=row+dir_y[i],extend_col=col+dir_x[i],pos=extend_row*3+extend_col;
			if(extend_row<0||extend_row>2||extend_col<0||extend_col>2)
				continue;
			swap(stat[node.blank],stat[pos]);
			hash_code=cantorExpansion(stat);
			if(closed[hash_code]==1)
				continue;
			create_node++;
			expand_node++;
			if(hash_code==end_hash)
			{
                c_n=create_node;
                e_n=expand_node;
				return node.extendWay+direction[i];
			}
			closed[hash_code]=1;
			StateNode new_node={hash_code,stat,pos,node.extendWay+direction[i],cost};
			opened.push(new_node);
		}
	}
    c_n=create_node;
    e_n=expand_node;
	return "No Answer!";
}
