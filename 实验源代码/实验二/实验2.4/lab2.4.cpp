#include<stdio.h>
#include<malloc.h>
#include <stdlib.h>
#include<limits.h>
const int col=8;//提前定义好的列数
const int row=9;//提前定义好的行数
const int ylen=col+2;//定义横坐标
const int xlen=row+2;
int maze[row][col]={
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 1, 1, 0, 1,
    0, 1, 1, 1, 0, 0, 1, 0,
    0, 0, 0, 1, 0, 0, 0, 0,
    0, 1, 0, 0, 0, 1, 0, 1,
    0, 1, 1, 1, 1, 0, 0, 1, 
    1, 1, 0, 0, 0, 1, 0, 1, 
    1, 1, 0, 0, 0, 0, 0, 0
};//定义好的地图
int new_maze[row+2][col+2]={0};//新地图，增加了墙
int angel[]={3,2,1,0};//定义方向优先级，右下左上
int visit[xlen][ylen]={0};//是否访问的二维数组标志位

typedef struct SElemtype{
    void* type;
}Elemtype;//自定义模板数据类型

typedef struct LNode{
    Elemtype data;
    struct LNode* next;
}LNode,*LinkStack;//自定义栈


void Init_stack(LinkStack &stack);//初始化栈
int Isempty_stack(LinkStack &stack);//判断栈是否为空
int push_stack(LinkStack &stack,SElemtype e);//入栈
SElemtype pop_stack(LinkStack &stack);//出栈
SElemtype top_stack(LinkStack &stack);//取出栈顶元素
void Get_maze();//初始化新地图
void Print_maze();//打印新地图
int Find_angel(int x,int y);//寻找移动角度
void Print_stack(LinkStack &stack);//打印栈信息
void Print_order(LinkStack &x,LinkStack &y,LinkStack &angel);//打印路线信息
void Solution_maze();//处理逻辑函数


int Find_angel(int x,int y){
    if(new_maze[x][y+1]==0&&visit[x][y+1]==0){
        return 3;
    }
    if(new_maze[x+1][y]==0&&visit[x+1][y]==0){
        return 2;
    }
    if(new_maze[x][y-1]==0&&visit[x][y-1]==0){
        return 1;
    }
    if(new_maze[x-1][y]==0&&visit[x-1][y]==0){
        return 0;
    }
    return -1;
}//寻找移动角度

void Init_stack(LinkStack &stack){
    stack=(LinkStack)malloc(sizeof(LNode));
    stack->next=NULL;
}//初始化栈

int Isempty_stack(LinkStack &stack){
    return (stack->next==NULL?1:0);
}//判断栈是否为空

int push_stack(LinkStack &stack,SElemtype e){
    LNode *temp=(LinkStack)malloc(sizeof(LNode));
    if(!temp){
        return 0;
    }
    temp->next=NULL;
    temp->data=e;
    temp->next=stack->next;
    stack->next=temp;
    return 1;
}//入栈

SElemtype pop_stack(LinkStack &stack){
    if(Isempty_stack(stack)){
        exit(-1);
    }else{
        LNode* temp=stack->next;
        SElemtype e;
        stack->next=temp->next;
        temp->next=NULL;
        e=temp->data;
        free(temp);
        return e;
    }
}//出栈

SElemtype top_stack(LinkStack &stack){
    if(Isempty_stack(stack)){
        // Elemtype e;
        // e.type=(int*)malloc(sizeof(int));
        // *(int*)e.type=-1;
        // return e;
        exit(-1);
    }
    return stack->next->data;
}//取出栈顶元素

void Get_maze(){
    for(int i=0;i<col+2;i++){
        for(int j=0;j<row+2;j++){
            if(i==0||i==col+1){
                new_maze[j][i]=1;
                continue;
            }else if(j==0||j==row+1){
                new_maze[j][i]=1;
                continue;
            }else{
                new_maze[j][i]=maze[j-1][i-1];
                continue;
            }
            

        }
    }
}//初始化新地图

void Print_maze(){
    for(int i=0;i<xlen;i++){
        for(int j=0;j<ylen;j++){
            printf("%d",new_maze[i][j]);
        }
        printf("\n");
    }
}//打印新地图

void Print_stack(LinkStack &stack){
    while(!Isempty_stack(stack)){
        printf("%d",*(int*)top_stack(stack).type);
        printf(",");
        pop_stack(stack);
    }
}//打印栈信息

void Print_order(LinkStack &x,LinkStack &y,LinkStack &angel){
    int index=1;
    while(!Isempty_stack(x)&&!Isempty_stack(y)){
        if(index==1){
            printf("(");
            printf("%d",*(int*)top_stack(x).type);
            printf(",");
            printf("%d",*(int*)top_stack(y).type);
            printf(",");
            printf("4");
            printf(")");
            pop_stack(x);
            pop_stack(y);
        }
        printf("<--");
        printf("(");
        printf("%d",*(int*)top_stack(x).type);
        printf(",");
        printf("%d",*(int*)top_stack(y).type);
        printf(",");
        printf("%d",*(int*)top_stack(angel).type);
        printf(")");
        pop_stack(x);
        pop_stack(y);
        pop_stack(angel);
        index++;
    }
}//打印寻找出口顺序

void Solution_maze(){
    LinkStack x;
    LinkStack y;
    LinkStack angel;
    Init_stack(x);
    Init_stack(y);
    Init_stack(angel);//初始化若干栈，分别表示横坐标、纵坐标、方向坐标
    Get_maze();//初始化新地图
    
    int startx=1;
    int starty=1;
    int dx=startx;//横坐标
    int dy=starty;//纵坐标
    Elemtype e1,e2;
    e1.type=(int*)malloc(sizeof(int));
    e2.type=(int*)malloc(sizeof(int));
    *(int*)e1.type=dx;
    *(int*)e2.type=dy;
    push_stack(x,e1);
    push_stack(y,e2);
    int endx=row;//定义终点的横坐标
    int endy=col;//定义终点的纵坐标
    while(*(int*)top_stack(x).type!=endx||*(int*)top_stack(y).type!=endy){//当没有达到终点时，循环寻找正确路线
        if(Find_angel(dx,dy)==3){
            dx=dx;
            dy=dy+1;
            visit[dx][dy]=1;
            Elemtype ex,ey;
            ex.type=(int*)malloc(sizeof(int));
            ey.type=(int*)malloc(sizeof(int));
            *(int*)ex.type=dx;
            *(int*)ey.type=dy;
            push_stack(x,ex);
            push_stack(y,ey);
            Elemtype eangel;
            eangel.type=(int*)malloc(sizeof(int));
            *(int*)eangel.type=3;
            push_stack(angel,eangel);
            if(*(int*)top_stack(x).type==endx&&*(int*)top_stack(y).type==endy){
                break;
            }
        }//向右走
        if(Find_angel(dx,dy)==2){
            dx=dx+1;
            dy=dy;
            visit[dx][dy]=1;
            Elemtype ex,ey;
            ex.type=(int*)malloc(sizeof(int));
            ey.type=(int*)malloc(sizeof(int));
            *(int*)ex.type=dx;
            *(int*)ey.type=dy;
            push_stack(x,ex);
            push_stack(y,ey);
            Elemtype eangel;
            eangel.type=(int*)malloc(sizeof(int));
            *(int*)eangel.type=2;
            push_stack(angel,eangel);
            if(*(int*)top_stack(x).type==endx&&*(int*)top_stack(y).type==endy){
                break;
            }
        }//向下走
        if(Find_angel(dx,dy)==1){
            dx=dx;
            dy=dy-1;
            visit[dx][dy]=1;
            Elemtype ex,ey;
            ex.type=(int*)malloc(sizeof(int));
            ey.type=(int*)malloc(sizeof(int));
            *(int*)ex.type=dx;
            *(int*)ey.type=dy;
            push_stack(x,ex);
            push_stack(y,ey);
            Elemtype eangel;
            eangel.type=(int*)malloc(sizeof(int));
            *(int*)eangel.type=1;
            push_stack(angel,eangel);
            if(*(int*)top_stack(x).type==endx&&*(int*)top_stack(y).type==endy){
                break;
            }
        }//向左走
        if(Find_angel(dx,dy)==0){
            dx=dx-1;
            dy=dy;
            visit[dx][dy]=1;
            Elemtype ex,ey;
            ex.type=(int*)malloc(sizeof(int));
            ey.type=(int*)malloc(sizeof(int));
            *(int*)ex.type=dx;
            *(int*)ey.type=dy;
            push_stack(x,ex);
            push_stack(y,ey);
            Elemtype eangel;
            eangel.type=(int*)malloc(sizeof(int));
            *(int*)eangel.type=0;
            push_stack(angel,eangel);
            if(*(int*)top_stack(x).type==endx&&*(int*)top_stack(y).type==endy){
                break;
            }
        }//向上走
        if(Find_angel(dx,dy)==-1){
            pop_stack(x);
            pop_stack(y);
            pop_stack(angel);
            dx=*(int*)top_stack(x).type;
            dy=*(int*)top_stack(y).type;
        }//走不通了，退一步

    }
    printf("The maze is according to the following:\n");
    Print_maze();
    printf("The order is according to the following:\n");
    Print_order(x,y,angel);
    printf("\n");
    printf("tips: In the output statement (x,y,angel), x represents the abscissa of the route, y represents the ordinate of the route, and angel represents the angle of travel of the route. \n Where 0 means up, 1 means left 1, 2 means down, 3 means right, and 4 means reach the end point.");
    
}

int main(){
    Solution_maze();
    system("pause");
}


// #include<stdio.h>
// #include<malloc.h>
// #include <stdlib.h>
// #include<limits.h>
// const int col=8;
// const int row=9;
// const int ylen=col+2;
// const int xlen=row+2;
// int maze[row][col]={
//     0, 0, 1, 0, 0, 0, 1, 0,
//     0, 0, 1, 0, 0, 0, 1, 0,
//     0, 0, 0, 0, 1, 1, 0, 1,
//     0, 1, 1, 1, 0, 0, 1, 0,
//     0, 0, 0, 1, 0, 0, 0, 0,
//     0, 1, 0, 0, 0, 1, 0, 1,
//     0, 1, 1, 1, 1, 0, 0, 1, 
//     1, 1, 0, 0, 0, 1, 0, 1, 
//     1, 1, 0, 0, 0, 0, 0, 0
// };
// int new_maze[row+2][col+2]={0};
// int angel[]={3,2,1,0};//定义方向优先级，右下左上
// int visit[xlen][ylen]={0};


// int Find_angel(int x,int y){
//     if(new_maze[x+1][y]==0&&visit[x+1][y]==0){
//         return 3;
//     }
//     if(new_maze[x][y+1]==0&&visit[x][y+1]==0){
//         return 2;
//     }
//     if(new_maze[x-1][y]==0&&visit[x-1][y]==0){
//         return 1;
//     }
//     if(new_maze[x][y-1]==0&&visit[x][y-1]==0){
//         return 0;
//     }
//     return -1;
// }

// typedef struct SElemtype{
//     void* type;
// }Elemtype;

// typedef struct LNode{
//     Elemtype data;
//     struct LNode* next;
// }LNode,*LinkStack;

// void Init_stack(LinkStack &stack){
//     stack=(LinkStack)malloc(sizeof(LNode));
//     stack->next=NULL;
// }

// int Isempty_stack(LinkStack &stack){
//     return (stack->next==NULL?1:0);
// }

// int push_stack(LinkStack &stack,SElemtype e){
//     LNode *temp=(LinkStack)malloc(sizeof(LNode));
//     if(!temp){
//         return 0;
//     }
//     temp->next=NULL;
//     temp->data=e;
//     temp->next=stack->next;
//     stack->next=temp;
//     return 1;

// }

// SElemtype pop_stack(LinkStack &stack){
//     if(Isempty_stack(stack)){
//         // Elemtype e;
//         // e.type=(int*)malloc(sizeof(int));
//         // *(int*)e.type=-1;
//         // return e;
//         exit(-1);
//     }else{
//         LNode* temp=stack->next;
//         SElemtype e;
//         stack->next=temp->next;
//         temp->next=NULL;
//         e=temp->data;
//         free(temp);
//         return e;


//     }
// }

// SElemtype top_stack(LinkStack &stack){
//     if(Isempty_stack(stack)){
//         // Elemtype e;
//         // e.type=(int*)malloc(sizeof(int));
//         // *(int*)e.type=-1;
//         // return e;
//         exit(-1);
//     }
//     return stack->next->data;
// }

// void Get_maze(){
//     for(int i=0;i<col+2;i++){
//         for(int j=0;j<row+2;j++){
//             if(i==0||i==col+1){
//                 new_maze[j][i]=1;
//                 continue;
//             }else if(j==0||j==row+1){
//                 new_maze[j][i]=1;
//                 continue;
//             }else{
//                 new_maze[j][i]=maze[j-1][i-1];
//                 continue;
//             }
            

//         }
//     }
// }
// void Print_maze(){
//     for(int i=0;i<xlen;i++){
//         for(int j=0;j<ylen;j++){
//             printf("%d",new_maze[i][j]);
//         }
//         printf("\n");
//     }
// }

// void Print_stack(LinkStack &stack){
//     while(!Isempty_stack(stack)){
//         printf("%d",*(int*)top_stack(stack).type);
//         printf(",");
//         pop_stack(stack);
//     }
// }

// void Solution_maze(){
//     LinkStack x;
//     LinkStack y;
//     LinkStack angel;
//     Init_stack(x);
//     Init_stack(y);
//     Init_stack(angel);
//     Get_maze();
    
//     // for(int i=0;i<xlen;i++){
//     //     for(int j=0;j<ylen;j++){
//     //         visit[i][j]=0;
//     //     }
//     // }
//     int startx=1;
//     int starty=1;
//     int dx=startx;
//     int dy=starty;
//     Elemtype e1,e2;
//     e1.type=(int*)malloc(sizeof(int));
//     e2.type=(int*)malloc(sizeof(int));
//     *(int*)e1.type=dx;
//     *(int*)e2.type=dy;
//     push_stack(x,e1);
//     push_stack(y,e2);
//     int endx=row;
//     int endy=col;
//     while(*(int*)top_stack(x).type!=endx&&*(int*)top_stack(y).type!=endy){
//         if(Find_angel(dx,dy)==3){
//             dx=dx+1;
//             dy=dy;
//             visit[dx][dy]=1;
//             Elemtype ex,ey;
//             ex.type=(int*)malloc(sizeof(int));
//             ey.type=(int*)malloc(sizeof(int));
//             *(int*)ex.type=dx;
//             *(int*)ey.type=dy;
//             push_stack(x,ex);
//             push_stack(y,ey);
//         }
//         if(Find_angel(dx,dy)==2){
//             dx=dx;
//             dy=dy+1;
//             visit[dx][dy]=1;
//             Elemtype ex,ey;
//             ex.type=(int*)malloc(sizeof(int));
//             ey.type=(int*)malloc(sizeof(int));
//             *(int*)ex.type=dx;
//             *(int*)ey.type=dy;
//             push_stack(x,ex);
//             push_stack(y,ey);
//         }
//         if(Find_angel(dx,dy)==1){
//             dx=dx-1;
//             dy=dy;
//             visit[dx][dy]=1;
//             Elemtype ex,ey;
//             ex.type=(int*)malloc(sizeof(int));
//             ey.type=(int*)malloc(sizeof(int));
//             *(int*)ex.type=dx;
//             *(int*)ey.type=dy;
//             push_stack(x,ex);
//             push_stack(y,ey);
//         }
//         if(Find_angel(dx,dy)==0){
//             dx=dx;
//             dy=dy-1;
//             visit[dx][dy]=1;
//             Elemtype ex,ey;
//             ex.type=(int*)malloc(sizeof(int));
//             ey.type=(int*)malloc(sizeof(int));
//             *(int*)ex.type=dx;
//             *(int*)ey.type=dy;
//             push_stack(x,ex);
//             push_stack(y,ey);
//         }
//         if(Find_angel(dx,dy)==-1){
//             pop_stack(x);
//             pop_stack(y);
//             dx=*(int*)top_stack(x).type;
//             dy=*(int*)top_stack(y).type;
//         }

//     }
//     // Elemtype ex,ey;
//     // ex.type=(int*)malloc(sizeof(int));
//     // ey.type=(int*)malloc(sizeof(int));
//     // *(int*)ex.type=dx;
//     // *(int*)ey.type=dy;
//     // push_stack(x,ex);
//     // push_stack(y,ey);

//     printf("x:");
//     Print_stack(x);
//     printf("\n");
//     printf("y:");
//     Print_stack(y);
// }

// int main(){
//     Solution_maze();
//     system("pause");
// }