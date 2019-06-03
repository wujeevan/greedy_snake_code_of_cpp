#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<time.h>
#include<iostream>
using namespace std;

void Pos(short x,short y)//设置光标位置函数
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void CreateMap()//打印地图
{
    for(int i=0;i<57;i+=2)//打印上下边框,这里每次自增2是因为控制台的一行和一列的宽度不同，且恰好有两倍关系。
    {
        Pos(i,0);
        printf("■");
        Pos(i,24);
        printf("■");
    }
    for(int i=1;i<24;i++)//打印左右边框
    {
        Pos(0,i);
        printf("■");            
        Pos(56,i);
        printf("■");    
    }
    return;
}

//接下来定义结构体从而创建链表。
struct Body//定义蛇身结构体
{
    short x,y;//蛇身结点的坐标
    Body *next;//指向下一个结点的指针
};

int Food=0; //1表明有食物，0表明没食物
short food_x,food_y;//食物坐标
void CreateFood()//创建新食物
{
    if(Food==0)
    {       
        srand((int)time(0));
        food_x=2+rand()%53;//x的取值范围[2,54]
        if(food_x%2==1)
            food_x--;
        food_y=1+rand()%23;//y的取值范围[1,23]
        Food=1;
    }
}
Body *body001;//蛇头指针
void Init()//游戏初始化
{
    CreateMap();
    struct Body *body002,*body003,*body004;//定义四个指向蛇身的指针
    body001=new Body;//创建4个蛇身结构体
    body002=new Body;
    body003=new Body;
    body004=new Body;
    body001->next=body002;//把蛇身连接起来，形成链表
    body002->next=body003;
    body003->next=body004;
    body004->next=NULL;
    Pos(body001->x=12,body001->y=8);printf("■");//设定并打印蛇身的初始位置
    Pos(body002->x=10,body002->y=8);printf("■");
    Pos(body003->x=8,body003->y=8);printf("■");
    Pos(body004->x=6,body004->y=8);printf("■");
    CreateFood();//打印食物
}


void PrintSnake()//打印蛇
{
    Body *p=body001;
    while(p!=NULL)//判断是否指向蛇尾
    {
        Pos(p->x,p->y);
        printf("■");
        p=p->next;
    }//从蛇头打印到蛇尾
    return ;
}
int dir=4;//蛇头方向1-up,2-down,3-left,4-right
int sleeptime=220;//每次移动之后的停顿时间
int score;//玩家得分
void SnakeMove()//蛇身移动、刷新蛇身和食物及其坐标
{
    Body *p_food;//下一格有食物
    Body *p_forward;//下一格没食物
    Body *q;//蛇身移动一格时的临时指针
    p_forward=new Body;   
    if(1==dir)//向上移动
    {
        if(body001->x==food_x && body001->y-1==food_y)//下一格有食物
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("分数:%d",score);
            Food=0;
            CreateFood();
        }
        else//下一格没有食物
        {
            p_forward->x=body001->x;//横坐标不变
            p_forward->y=body001->y-1;//纵坐标-1
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//使q指向倒数第二个结点
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//移动光标到蛇尾
            printf(" ");//删除蛇尾
            free(q->next); //释放蛇尾
            q->next=NULL;//使倒数第二个结点成为新的蛇尾
        }//else
    }


    if(2==dir)//向下移动
    {

        if(body001->x==food_x && body001->y+1==food_y)//下一格有食物
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("分数:%d",score);
            Food=0;
            CreateFood();
        }
        else//下一格没有食物
        {
            p_forward->x=body001->x;//横坐标不变
            p_forward->y=body001->y+1;//纵坐标+1
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//使q指向倒数第二个结点
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//移动光标到蛇尾
            printf(" ");//删除蛇尾
            free(q->next); //释放蛇尾
            q->next=NULL;//使倒数第二个结点成为新的蛇尾
        }//else
    }


    if(3==dir)//向左移动
    {
        if(body001->x-2==food_x && body001->y==food_y)//下一格有食物
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("分数:%d",score);
            Food=0;
            CreateFood();
        }
        else//下一格没有食物
        {
            p_forward->x=body001->x-2;//横坐标-2
            p_forward->y=body001->y;//纵坐标不变
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//使q指向倒数第二个结点
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//移动光标到蛇尾
            printf(" ");//删除蛇尾
            free(q->next); //释放蛇尾
            q->next=NULL;//使倒数第二个结点成为新的蛇尾
        }
    }


    if(4==dir)//向右移动
    {
        if(body001->x+2==food_x && body001->y==food_y)//下一格有食物
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Food=0;
            Pos(62,3);printf("分数:%d",score);
            CreateFood();
        }
        else//下一格没有食物
        {
            p_forward->x=body001->x+2;//横坐标=2
            p_forward->y=body001->y;//纵坐标不变
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//使q指向倒数第二个结点
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//移动光标到蛇尾
            printf(" ");//删除蛇尾
            free(q->next); //释放蛇尾
            q->next=NULL;//使倒数第二个结点成为新的蛇尾
        }
    }
    Pos(food_x,food_y);printf("■");//打印食物
    PrintSnake();//打印蛇
}

int TouchSelf()//判断是否咬到自己
{
    Body *p_tself;
    p_tself=body001;
    while(!p_tself->next==NULL)
    {
        p_tself=p_tself->next;
        if(p_tself->x==body001->x && p_tself->y==body001->y)
            return 1;
    }
    return 0;
}

int TouchWall()//不可穿墙
{
    if(body001->x==0 || body001->x==56 || body001->y==0 || body001->y==24)
        return 1;
    else
        return 0;
}

void GameCircle()//游戏循环
{
    while(1)
    {
        if (1== TouchWall())//不可穿墙
             break;
        if(1== TouchSelf() )//判断蛇是否咬到自己
            break;//咬到自己Game Over


        //判断用户的按键输入
        if(GetAsyncKeyState(VK_UP) && dir!=2)
            dir=1;
        else if(GetAsyncKeyState(VK_DOWN) && dir!=1)
            dir=2;
        else if(GetAsyncKeyState(VK_LEFT) && dir!=4)
            dir=3;
        else if(GetAsyncKeyState(VK_RIGHT) && dir!=3)
            dir=4;
        SnakeMove();//蛇移动一格
        Sleep(sleeptime);//设定两次移动之间的时间间隔
    }
}
void EndImage()
{
    system("cls");
    Pos(30,9);printf("游戏结束，欢迎再来！");
    Pos(30,11);printf("你的得分：%d",score);
    Pos(28,13);
    Sleep(5000);
}
int main()
{
    Init();
    GameCircle();
    EndImage();
    return 0;
}