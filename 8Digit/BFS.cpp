//author:strewen
//Create On:2018/06/09
//describe:
//八数码问题广度优先搜索求解
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
	StateNode(int h,string s,int b,string e){state=h;state=s;blank=b;extendWay=e;}
    ~StateNode(){}
};

static queue<StateNode*> opened;  //未被拓展的节点
static bitset<362880> closed={0}; //已创建的节点
static string init_state;       
static int fac[]={1,1,2,6,24,120,720,5040,40320}; //用于康托展开
static string direction[4]={"U","D","L","R"};   //拓展规则
static int dir_x[4]={0,0,-1,1};
static int dir_y[4]={-1,1,0,0};
static int create_node,expand_node;  //创建节点数，拓展节点数

//康托展开
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

//end_state:
//1 2 3
//8 0 4
//7 6 5
static int end_state=cantorExpansion("123804765");

//初始化函数
static int getInitState(string init)
{
    create_node=0;
    expand_node=0;
    closed={0};
    while(!opened.empty()){
        StateNode *old=opened.front();
        opened.pop();
        delete old;
    }
	init_state=init;
	int blank_pos=init_state.find('0',0);
	int hash_code=cantorExpansion(init_state);
	create_node++;
	if(hash_code==end_state)
		return 0;
	StateNode* new_node=new StateNode(hash_code,init_state,blank_pos,"");
	opened.push(new_node);
	closed[hash_code]=1;
	return 1;
}

string BFS(string init,int& c_n,int& e_n)
{
	if(!getInitState(init))
	{
        c_n=create_node;
        e_n=expand_node;
		return "Input Is Answer!";
	}
	//拓展节点
	while(!opened.empty()){
		StateNode* node=opened.front();
		opened.pop();
        if(expand_node!=0)
            expand_node--;
		int row=floor(node->blank/3),col=node->blank%3,hash_code;
		for(int i=0;i<4;i++){
			string stat=node->state;
			int extend_row=row+dir_y[i],extend_col=col+dir_x[i],pos=extend_row*3+extend_col;
			if(extend_row<0||extend_row>2||extend_col<0||extend_col>2)
				continue;
			swap(stat[node->blank],stat[pos]);
			hash_code=cantorExpansion(stat);
			//节点已被创建
			if(closed[hash_code]==1)
				continue;
			create_node++;
			expand_node++;
			//拓展的节点是终止状态
			if(hash_code==end_state)
			{
                c_n=create_node;
                e_n=expand_node;
				return node->extendWay+direction[i];
			}
			closed[hash_code]=1;
			StateNode* new_node=new StateNode(hash_code,stat,pos,node->extendWay+direction[i]);
			opened.push(new_node);
		}
        delete node;
	}
    c_n=create_node;
    e_n=expand_node;
	return "No Answer!";
}
