#pragma warning (disable:4996)
#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXNUM 50
//�ɻ��Ķ���
typedef struct Planes {
	float x;//����
	float y;//γ��
	float z;//�߶�
	char id;//���
}Planes;
//�������ݵ�����
typedef struct Array {
	Planes p;
	bool flag = 0;//�������ʹ�����Ϊ1��û�����ʹ�����Ϊ0
} Friends[MAXNUM], Enemies[MAXNUM];

//���������㣬������������
float Distance(Planes p1, Planes p2) {
	return sqrt(fabs(p1.x - p2.x) * fabs(p1.x - p2.x) + fabs(p1.y - p2.y) * fabs(p1.y - p2.y) + fabs(p1.z - p2.z) * fabs(p1.z - p2.z));
}

//����һ��ƥ������ƥ��ķɻ��Ž�������
typedef struct Match {
	Planes f;//����ҷ��ɻ�����
	Planes e;//��ŵз��ɻ�����
	float distance;//�ҷ��з��ɻ���ľ���
	struct Match* next;//ָ��ƥ�������е���һ���ڵ�
}MNode;
//��ʼ��ƥ������
MNode* InitList() {
	MNode* head;
	head = (MNode*)malloc(sizeof(MNode));
	head->next = NULL;
	return head;
}
//��ƥ���������������
MNode* InsertList(MNode* head, Planes f, Planes e) {
	MNode* p1 = (MNode*)malloc(sizeof(MNode));
	p1->e = e;
	p1->f = f;
	p1->distance = Distance(f, e);
	p1->next = head->next;
	head->next = p1;
	return head;
}

//�Ⱥ���еĶ��нڵ�
typedef struct QNode {
	Planes f;//����ҷ��ɻ�
	QNode* next;//ָ����һ�����нڵ�
}QNode;
//���еĶ���
typedef struct Queue {
	QNode* head;//����ͷ
	QNode* tail;//����β
}Queue;
//��ʼ���ȴ��ض���
Queue InitQueue() {
	Queue Q;
	QNode* p1 = (QNode*)malloc(sizeof(QNode));
	p1->next = NULL;
	Q.head = Q.tail = p1;
	return Q;
}
//��ȴ��ض������������
Queue InsertQueue(Queue Q, Planes p) {
	QNode* p1 = (QNode*)malloc(sizeof(QNode));
	p1->f = p;
	p1->next = NULL;

	Q.tail->next = p1;
	Q.tail = p1;

	return Q;
}
//�ж��Ƿ�Ϊ�ն���
//�ǿն��з���false
//���ǿն��з���true
bool JudgeEmpty(Queue Q) {
	if (Q.head->next == NULL) {
		return false;
	}
	else return true;
}
//Ԫ�س����У�ɾ����ͬʱ����ɾ����Ԫ��
//ʹ��ǰӦ�ж϶����Ƿ�Ϊ��
Planes PopQueue(Queue& Q) {
	QNode* p1 = Q.head->next;
	Q.head->next = p1->next;
	if (Q.tail == p1) {
		Q.tail = Q.head;
	}
	Planes temp = p1->f;
	free(p1);
	return temp;
}


//ͼ�λ�����
void printArrow(int y) {
	settextcolor(WHITE);
	outtextxy(820, y, '-');
	outtextxy(825, y, '-');
	outtextxy(830, y, '-');
	outtextxy(835, y, '>');
}
void printMatch(MNode* head) {
	MNode* p = head;
	for (int y = 10; p; p = p->next, y += 20) {
		line((400 + 70 * p->f.x), (400 - 70 * p->f.y), (400 + 70 * p->e.x), (400 - 70 * p->e.y));
		setfillcolor(LIGHTBLUE);
		fillcircle((400 + 70 * p->f.x), (400 - 70 * p->f.y), 5); 
		outtextxy((400 + 70 * p->f.x + 10), (400 - 70 * p->f.y + 10), p->f.id);
		setfillcolor(RED);
		fillcircle((400 + 70 * p->e.x), (400 - 70 * p->e.y), 5);
		outtextxy((400 + 70 * p->e.x + 10), (400 - 70 * p->e.y + 10), p->e.id);
		settextcolor(LIGHTBLUE);
		outtextxy(810, y, p->f.id);
		printArrow(y);
		settextcolor(RED);
		outtextxy(845, y, p->e.id);
	}
}
void showXY() {
	line(0, 0, 800, 0);
	line(0, 0, 0, 800);
	line(800, 0, 800, 800);
	line(0, 800, 800, 800);
	line(400, 0, 400, 800);
	line(0, 400, 800, 400);
	outtextxy(405, 3, 'y');
	outtextxy(790, 380, 'x');
	char str[6] = { '0','1','2','3','4','5' };
	for (int i = 0, j = 380; i < 6; i++, j -= 70) {
		outtextxy(410, j, str[i]);
	}
	for (int i = 1, j = 480; i < 6; i++, j += 70) {
		outtextxy(j, 380, str[i]);
	}
	char arr[5] = { '1','2','3','4','5' };
	for (int i = 0, j = 340; i < 5; i++, j -= 70) {
		outtextxy(j - 6, 380, '-');
		outtextxy(j, 380, arr[i]);
	}
	for (int i = 0, j = 460; i < 5; i++, j += 70) {
		outtextxy(410, j - 5, '-');
		outtextxy(416, j - 5, arr[i]);
	}
	for (int i = 50; i < 800; i += 70) {
		line(400, i, 410, i);
		line(i, 400, i, 390);
	}
	circle(400, 400, 70);
	circle(400, 400, 210);
	circle(400, 400, 350);

}

int main() {
	//��ʼ����������
	Friends F;
	Enemies E;
	int num_F, num_E;
	//�����Ѿ���о���Ϣ
	printf("�������Ѿ���о��ɻ�����\n");
	scanf("%d %d", &num_F, &num_E);
	getchar();
	printf("�������Ѿ��ɻ��ı���Լ�����\n");
	for (int i = 0; i < num_F; i++) {
		scanf("%c %f,%f,%f", &F[i].p.id, &F[i].p.x, &F[i].p.y, &F[i].p.z);
		getchar();
	}
	printf("������о��ɻ��ı���Լ�����\n");
	for (int i = 0; i < num_E; i++) {
		scanf("%c %f,%f,%f", &E[i].p.id, &E[i].p.x, &E[i].p.y, &E[i].p.z);
		getchar();
	}

	//temp_f��Ŀǰ�����жϵ��ѷ��ɻ�
	//E��tag���ǵ�һ���������ҵ�����temp_f��������ĵз��ɻ�
	//F��loop���ǵڶ��δ��ҵ����ҵ�����E��tag������������ѷ��ɻ�
	//��F��loop��==temp_f��˵��temp_f������E��tag�����
	//����temp_f�Ž�һ���ȴ�����

	MNode* MatchList = InitList();
	Queue WaitList = InitQueue();

	int MatchNum = 0;
	int waitNum = 0;
	for (int i = 0; i < num_F; i++) {
		if (F[i].flag == 1) { //����ǰ�ѷ��ɻ��Ѿ�����ˣ��������÷ɻ�
			continue;
		}

		Planes temp_f = F[i].p;//��ǰ��F��i�����з���
		//��E��i������һ����֮���������
		float min1 = 100000;//��С����
		int tag = 0;//��С�����Ӧ���±�
		for (int j = 0; j < num_E; j++) {
			if (Distance(temp_f, E[j].p) < min1 && E[j].flag == 0) {
				min1 = Distance(temp_f, E[j].p);
				tag = j;
			}
		}

		//�����������С�ĵ��˽��з�������F��������������������ģ������ǲ���temp_f
		float min2 = 100000;
		int loop = 0;
		for (int k = 0; k < num_F; k++) {
			if (Distance(E[tag].p, F[k].p) < min2 && F[k].flag == 0) {
				min2 = Distance(E[tag].p, F[k].p);
				loop = k;
			}
		}

		//��F��loop��==temp_f��˵��temp_f������E��tag�����
		if (temp_f.id == F[loop].p.id) {
			MatchList = InsertList(MatchList, temp_f, E[tag].p);
			MatchNum++;
			//�ı�flagֵ
			E[tag].flag = true;
			for (int j = 0; j < num_F; j++) {
				if (temp_f.id == F[j].p.id) {
					F[j].flag = 1;
					break;
				}
			}
		}
		else {
			WaitList = InsertQueue(WaitList, temp_f);
			waitNum++;
		}
	}

	while (JudgeEmpty(WaitList)) {
		Planes temp_f = PopQueue(WaitList);
		//��E��i������һ����֮���������
		float min1 = 100000;//��С����
		int tag = 0;//��С�����Ӧ���±�
		for (int j = 0; j < num_E; j++) {
			if (Distance(temp_f, E[j].p) < min1 && E[j].flag == 0) {
				min1 = Distance(temp_f, E[j].p);
				tag = j;
			}
		}

		//�����������С�ĵ��˽��з�������F��������������������ģ������ǲ���temp_f
		float min2 = 100000;
		int loop = 0;
		for (int k = 0; k < num_F; k++) {
			if (Distance(E[tag].p, F[k].p) < min2 && F[k].flag == 0) {
				min2 = Distance(E[tag].p, F[k].p);
				loop = k;
			}
		}

		//��F��loop��==temp_f��˵��temp_f������E��tag�����
		if (temp_f.id == F[loop].p.id) {
			MatchList = InsertList(MatchList, temp_f, E[tag].p);
			MatchNum++;
			//�ı�flagֵ
			E[tag].flag = true;
			for (int j = 0; j < num_F; j++) {
				if (temp_f.id == F[j].p.id) {
					F[j].flag = 1;
					break;
				}
			}
		}
		else {
			WaitList = InsertQueue(WaitList, temp_f);
		}
	}



	MNode* p = MatchList->next;
	float TotalDistance = 0;
	while (p) {
		TotalDistance += p->distance;
		printf("%c--->%c", p->f.id, p->e.id);
		printf("�Ѿ��ɻ���ţ�%c ���꣺���ȣ�%.2f γ�ȣ��߶ȣ�%.2f \n", p->f.id, p->f.x, p->f.y, p->f.z);
		printf("����ƥ��ĵо��ɻ���ţ�%c ���꣺���ȣ�%.2f γ�ȣ��߶ȣ�%.2f \n\n", p->e.id, p->e.x, p->e.y, p->e.z);
		p = p->next;
	}
	printf("�ܾ���Ϊ��%.2f\n", TotalDistance);
	printf("���س�������������\n");
	char c = getchar();
	p = MatchList->next;
	initgraph(1000, 800);
	showXY();
	printMatch(p);
	_getch();
	system("pause");
	return 0;
}
/*
��������
A-L�Ѿ���M-Z�о�
12 12
A 1.31,-1.69,3.39
B -0.92,1.24,-0.4
C 2.47,1.22,1
D -2.49,-1.47,-0.59
E -1.99,3.6,0.47
F 4.22,-2.34,0
G 2.43,2.96,0
H -0.4,-2.59,-2
I 0.54,-0.44,-0.7
J 1.14,-2.47,-1.36
K -1.67,0.78,1.45
L 3.17,-1.56,-1
M 1.37,1.14,-1
N 1.53,-3.46,0.69
O -3.38,1.08,-2.0
P -2.94,2.18,-0.42
Q 0.7,3.03,1.43
R -4.26,-1.04,0
S 4.9,1.73,2.15
T 3.5,-3.95,2.42
U 1.8,4.56,-0.47
V -2.15,-3.49,1.24
W -1,-1,0.77
Z 0.46,1.61,1.17

8 8
A -0.38,-0.33,-0.66
B 3.76,-1.68,-1.21
C 1.07,0.84,0.69
D -2,2.82,-0.73
E -2.24,-1.84,0.37
F 1.08,-0.75,1.29
G 1.44,2.96,0.71
H -0.75,1.62,-0.61
I 2.41,0.33,-0.43
J -2.59,1.05,1.17
K 2.87,1.67,-0.21
L -0.17,-2.06,-1
M -2,-1,-0.51
N 0.25,0.24,2.31
O -1.43,2.79,-1.51
P 2.45,-3.03,-0.74
*/