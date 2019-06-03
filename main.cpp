#include<windows.h>
#include<conio.h>
#include<cstdlib>
#include<time.h>
#include<iostream>
using namespace std;

void Pos(short x,short y)//���ù��λ�ú���
{
    COORD pos;
    pos.X=x;
    pos.Y=y;
    HANDLE hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput,pos);
}

void CreateMap()//��ӡ��ͼ
{
    for(int i=0;i<57;i+=2)//��ӡ���±߿�,����ÿ������2����Ϊ����̨��һ�к�һ�еĿ�Ȳ�ͬ����ǡ����������ϵ��
    {
        Pos(i,0);
        printf("��");
        Pos(i,24);
        printf("��");
    }
    for(int i=1;i<24;i++)//��ӡ���ұ߿�
    {
        Pos(0,i);
        printf("��");            
        Pos(56,i);
        printf("��");    
    }
    return;
}

//����������ṹ��Ӷ���������
struct Body//��������ṹ��
{
    short x,y;//�����������
    Body *next;//ָ����һ������ָ��
};

int Food=0; //1������ʳ�0����ûʳ��
short food_x,food_y;//ʳ������
void CreateFood()//������ʳ��
{
    if(Food==0)
    {       
        srand((int)time(0));
        food_x=2+rand()%53;//x��ȡֵ��Χ[2,54]
        if(food_x%2==1)
            food_x--;
        food_y=1+rand()%23;//y��ȡֵ��Χ[1,23]
        Food=1;
    }
}
Body *body001;//��ͷָ��
void Init()//��Ϸ��ʼ��
{
    CreateMap();
    struct Body *body002,*body003,*body004;//�����ĸ�ָ�������ָ��
    body001=new Body;//����4������ṹ��
    body002=new Body;
    body003=new Body;
    body004=new Body;
    body001->next=body002;//�����������������γ�����
    body002->next=body003;
    body003->next=body004;
    body004->next=NULL;
    Pos(body001->x=12,body001->y=8);printf("��");//�趨����ӡ����ĳ�ʼλ��
    Pos(body002->x=10,body002->y=8);printf("��");
    Pos(body003->x=8,body003->y=8);printf("��");
    Pos(body004->x=6,body004->y=8);printf("��");
    CreateFood();//��ӡʳ��
}


void PrintSnake()//��ӡ��
{
    Body *p=body001;
    while(p!=NULL)//�ж��Ƿ�ָ����β
    {
        Pos(p->x,p->y);
        printf("��");
        p=p->next;
    }//����ͷ��ӡ����β
    return ;
}
int dir=4;//��ͷ����1-up,2-down,3-left,4-right
int sleeptime=220;//ÿ���ƶ�֮���ͣ��ʱ��
int score;//��ҵ÷�
void SnakeMove()//�����ƶ���ˢ�������ʳ�Ｐ������
{
    Body *p_food;//��һ����ʳ��
    Body *p_forward;//��һ��ûʳ��
    Body *q;//�����ƶ�һ��ʱ����ʱָ��
    p_forward=new Body;   
    if(1==dir)//�����ƶ�
    {
        if(body001->x==food_x && body001->y-1==food_y)//��һ����ʳ��
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("����:%d",score);
            Food=0;
            CreateFood();
        }
        else//��һ��û��ʳ��
        {
            p_forward->x=body001->x;//�����겻��
            p_forward->y=body001->y-1;//������-1
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//ʹqָ�����ڶ������
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//�ƶ���굽��β
            printf(" ");//ɾ����β
            free(q->next); //�ͷ���β
            q->next=NULL;//ʹ�����ڶ�������Ϊ�µ���β
        }//else
    }


    if(2==dir)//�����ƶ�
    {

        if(body001->x==food_x && body001->y+1==food_y)//��һ����ʳ��
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("����:%d",score);
            Food=0;
            CreateFood();
        }
        else//��һ��û��ʳ��
        {
            p_forward->x=body001->x;//�����겻��
            p_forward->y=body001->y+1;//������+1
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//ʹqָ�����ڶ������
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//�ƶ���굽��β
            printf(" ");//ɾ����β
            free(q->next); //�ͷ���β
            q->next=NULL;//ʹ�����ڶ�������Ϊ�µ���β
        }//else
    }


    if(3==dir)//�����ƶ�
    {
        if(body001->x-2==food_x && body001->y==food_y)//��һ����ʳ��
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Pos(62,3);printf("����:%d",score);
            Food=0;
            CreateFood();
        }
        else//��һ��û��ʳ��
        {
            p_forward->x=body001->x-2;//������-2
            p_forward->y=body001->y;//�����겻��
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//ʹqָ�����ڶ������
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//�ƶ���굽��β
            printf(" ");//ɾ����β
            free(q->next); //�ͷ���β
            q->next=NULL;//ʹ�����ڶ�������Ϊ�µ���β
        }
    }


    if(4==dir)//�����ƶ�
    {
        if(body001->x+2==food_x && body001->y==food_y)//��һ����ʳ��
        {
            p_food=new Body;
            p_food->x=food_x;
            p_food->y=food_y;
            p_food->next=body001;
            body001=p_food;
            score+=5;
            Food=0;
            Pos(62,3);printf("����:%d",score);
            CreateFood();
        }
        else//��һ��û��ʳ��
        {
            p_forward->x=body001->x+2;//������=2
            p_forward->y=body001->y;//�����겻��
            p_forward->next=body001;
            body001=p_forward;
            q=body001;
            while((q->next)->next!=NULL)//ʹqָ�����ڶ������
                q=q->next;
            Pos((q->next)->x,(q->next)->y);//�ƶ���굽��β
            printf(" ");//ɾ����β
            free(q->next); //�ͷ���β
            q->next=NULL;//ʹ�����ڶ�������Ϊ�µ���β
        }
    }
    Pos(food_x,food_y);printf("��");//��ӡʳ��
    PrintSnake();//��ӡ��
}

int TouchSelf()//�ж��Ƿ�ҧ���Լ�
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

int TouchWall()//���ɴ�ǽ
{
    if(body001->x==0 || body001->x==56 || body001->y==0 || body001->y==24)
        return 1;
    else
        return 0;
}

void GameCircle()//��Ϸѭ��
{
    while(1)
    {
        if (1== TouchWall())//���ɴ�ǽ
             break;
        if(1== TouchSelf() )//�ж����Ƿ�ҧ���Լ�
            break;//ҧ���Լ�Game Over


        //�ж��û��İ�������
        if(GetAsyncKeyState(VK_UP) && dir!=2)
            dir=1;
        else if(GetAsyncKeyState(VK_DOWN) && dir!=1)
            dir=2;
        else if(GetAsyncKeyState(VK_LEFT) && dir!=4)
            dir=3;
        else if(GetAsyncKeyState(VK_RIGHT) && dir!=3)
            dir=4;
        SnakeMove();//���ƶ�һ��
        Sleep(sleeptime);//�趨�����ƶ�֮���ʱ����
    }
}
void EndImage()
{
    system("cls");
    Pos(30,9);printf("��Ϸ��������ӭ������");
    Pos(30,11);printf("��ĵ÷֣�%d",score);
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