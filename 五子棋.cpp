// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <graphics.h>
#include <time.h>
#include <conio.h>

#define black 0            //������ɫ����
#define white 0xFFFFFF
#define red 0x0000AA
#define yellow 0x55FFFF
#define s_x 50    //��������ϵԭ��x����
#define s_y 50    //��������ϵԭ��y����
#define w_x 640   //���̿�
#define w_y 480   //���̸�
#define FIVE 8
#define TFOUR 7
#define DFOUR 6
#define TTHREE1 5
#define TTHREE2 4
#define DTHREE 3
#define TTWO1   2
#define TTWO2   1
#define ME 0
#define OTHER 1
#define List_init_size 100
#define Listadd 10
typedef int Status;
typedef int ElemType;

static int potmap[14][14] = { 0 };
struct repot		  {

	int x, y;
	int flag;
	int f;
	struct repot *next;

};   //��¼��ֵ�����

typedef struct point {
	int x;
	int y;
	int rank;
	struct point *next;
	struct point *former;
}*L_point;//����
int max_ab(int depth, int x1, int y1, int alpha, int beta, int map[14][14], int aspect);


/*��ͼ����ģ��*/
void drowline() {                      //��ʼ�����̺���
	int x, y;
	initgraph(800, 600);

	setorigin(s_x, s_y);
	settextcolor(white);
	setlinecolor(black);
	setbkcolor(yellow);
	cleardevice();
	for (x = 0;x< 14;x++)
		line(x * 30, 0, x * 30, 390);
	for (y = 0;y < 14;y++)
		line(0, y * 30, 390, y * 30);    //����14*14���̣�������ÿ���30����

	settextstyle(20, 0, _T("����"));
	settextcolor(black);
	TCHAR s1[] = _T("player 1");
	TCHAR s2[] = _T("player 2");
	outtextxy(550, 100, s1);
	outtextxy(550, 400, s2);           //��������ӡ�����Ϣ
}
void drowpot(int flag, int x, int y, int x_1, int y_1, int flag2) {   //���Ӻ���

	if (flag == -1) {
		setbkcolor(yellow);
		setfillcolor(black);
		solidcircle(x, y, 14);
		clearcircle(660, 110, 14);         //������ӣ�x��y�������������ʾ�ֵ�player2����
		setfillcolor(white);
		solidcircle(660, 410, 14);
		if (flag2 != 0) {
			setlinecolor(red);             //���������ӵ����ú��ʮ�ֱ��
			line(x - 5, y, x + 5, y);
			line(x, y - 5, x, y + 5);
			if (x_1 != 0 || y_1 != 0) {
				setbkcolor(white);
				clearcircle(x_1, y_1, 14);
			}
		}
	}
	else {
		setbkcolor(yellow);
		setfillcolor(white);
		solidcircle(x, y, 14);
		clearcircle(660, 410, 14);    //������ӣ�x��y��������ʾ�ֵ�palyer1����
		setfillcolor(black);
		solidcircle(660, 110, 14);
		if (flag2 != 0) {
			setlinecolor(red);            //���������ӵ����ú�ɫʮ�ֱ��
			line(x - 5, y, x + 5, y);
			line(x, y - 5, x, y + 5);
			if (x_1 != 0 || y_1 != 0) {
				setbkcolor(black);
				clearcircle(x_1, y_1, 14);
			}
		}
	}
}
void repotdown(struct repot *head) {  //���̺���
	struct repot *p;
	drowline();
	for (p = head;p != NULL;p = p->next) {   //���ζ�ȡrepot�����е�x��y��flag��ʵ�ָ���
		if (p->f == 1) {
			clearcircle(p->x, p->y, 14);
			setlinecolor(black);
			line((p->x) - 15, (p->y), (p->x) + 15, (p->y));
			line((p->x), (p->y) - 15, (p->x), (p->y) + 15);
			Sleep(1000);
		}
		drowpot(p->flag, p->x, p->y, NULL, NULL, 0);
		Sleep(1000);
	}
} 
int judgewin(int x, int y, int map[14][14]) {  //�ж�ʤ������
	int i, tipe, flag, num1, num2, num3, num4;  //��¼���Ӵ�Ϊԭ����ĸ������ϵ�ͬɫ������
	tipe = 30;
	flag = map[x / 30][y / 30];
	num1 = 0;                             //x�᷽�����
	for (i = 0;i < 5;i++) {
		if (map[(x + i*tipe) / 30][y / 30] == flag)
			num1 = num1 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x - i*tipe) / 30][y / 30] == flag)
			num1 = num1 + 1;
		else
			break;

	}

	num2 = 0;                            //y�᷽�����
	for (i = 0;i < 5;i++) {
		if (map[x / 30][(y + i*tipe) / 30] == flag)
			num2 = num2 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[x / 30][(y - i*tipe) / 30] == flag)
			num2 = num2 + 1;
		else
			break;

	}

	num3 = 0;                            //x��45�ȷ������
	for (i = 0;i < 5;i++) {
		if (map[(x + i*tipe) / 30][(y + i*tipe) / 30] == flag)
			num3 = num3 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x - i*tipe) / 30][(y - i*tipe) / 30] == flag)
			num3 = num3 + 1;
		else
			break;

	}


	num4 = 0;                           //y��45�ȷ������
	for (i = 0;i < 5;i++) {
		if (map[(x - i*tipe) / 30][(y + i*tipe) / 30] == flag)
			num4 = num4 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x + i*tipe) / 30][(y - i*tipe) / 30] == flag)
			num4 = num4 + 1;
		else
			break;

	}
	if (num1 >= 5 || num2 >= 5 || num3 >= 5 || num4 >= 5)
		return 1;
	else
		return 0;
}
void judgewin(int x, int y, int map[14][14], struct repot *p, struct repot *head) {  //�ж�ʤ������
	int i, tipe, flag, num1, num2, num3, num4;  //��¼���Ӵ�Ϊԭ����ĸ������ϵ�ͬɫ������
	tipe = 30;
	flag = map[x / 30][y / 30];
	num1 = 0;                             //x�᷽�����
	for (i = 0;i < 5;i++) {
		if (map[(x + i*tipe) / 30][y / 30] == flag)
			num1 = num1 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x - i*tipe) / 30][y / 30] == flag)
			num1 = num1 + 1;
		else
			break;

	}

	num2 = 0;                            //y�᷽�����
	for (i = 0;i < 5;i++) {
		if (map[x / 30][(y + i*tipe) / 30] == flag)
			num2 = num2 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[x / 30][(y - i*tipe) / 30] == flag)
			num2 = num2 + 1;
		else
			break;

	}

	num3 = 0;                            //x��45�ȷ������
	for (i = 0;i < 5;i++) {
		if (map[(x + i*tipe) / 30][(y + i*tipe) / 30] == flag)
			num3 = num3 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x - i*tipe) / 30][(y - i*tipe) / 30] == flag)
			num3 = num3 + 1;
		else
			break;

	}


	num4 = 0;                           //y��45�ȷ������
	for (i = 0;i < 5;i++) {
		if (map[(x - i*tipe) / 30][(y + i*tipe) / 30] == flag)
			num4 = num4 + 1;
		else
			break;

	}
	for (i = 1;i < 5;i++) {
		if (map[(x + i*tipe) / 30][(y - i*tipe) / 30] == flag)
			num4 = num4 + 1;
		else
			break;

	}

	if (num1 >= 5 || num2 >= 5 || num3 >= 5 || num4 >= 5) {      //ʤ�������ж�
		p->next = NULL;
		setbkcolor(yellow);
		settextstyle(30, 0, _T("����"));
		settextcolor(black);
		TCHAR s[] = _T("����ʤ! ��Ϸ����");    //�������������Ϸ���
		TCHAR s1[] = _T("����ʤ! ��Ϸ����");
		outtextxy(150, 100, (flag == -1) ? s : s1);
		HWND hwnd = GetHWnd();
		if (MessageBox(hwnd, _T("�Ƿ�����Ϸ"), _T("T_T"), MB_OKCANCEL) == IDOK) {   //����С��ѯ���Ƿ���
			repotdown(head);
		}
		else
			MessageBox(hwnd, _T("��Ϸ����"), _T("T_T"), MB_OK);
	}


}
/*----------*/


/*AI����ģ��*/
int getLine(int x,int y,int i,int j,int map[14][14]) {
	int x1, y1;
	x1 = x;
	y1 = y;
	switch (i) {
	case 1:
		x1 = x + j;//x
		break;
	case 5:
		x1 = x + j;//y��ƫ45��
		y1 = y + j;
	case 3:
		y1 = y + j;//y
		break;
	case 7:
		x1 = x - j;//x��ƫ45��
		y1 = y + j;
	case 2:
		x1 = x - j;//x
		break;
	case 6:
		x1 = x - j;//y��ƫ45��
		y1 = y - j;
		break;
	case 4:
		y1 = y - j;//y
		break;
	case 8:
		x1 = x + j;//x��ƫ45��
		y1 = y - j;
	}

	if (x1 < 0 || y1 < 0 || x1>14 || y1>14) {
		return 2;//�߽�
	}
	/*if (x1 ==0 || y1 == 0 || x1==14 || y1==14) {
		if(map[x1][y1]==0)
			return 2;//�߽�
	}*/
	
	return map[x1][y1];
};
void value(int value1, int &value) {
	if (value1 > value)
		value = value1;
}
int allowpoint_judgement(int x, int y, int map[14][14], int plyer) {
	int mark = 0;
	int one, two, three, four;
	int f_one, f_two, f_three;

	for (int i = 1; i <= 8; i++) { // 8������
		one = getLine(x, y, i, -1, map);
		two = getLine(x, y, i, -2, map);
		three = getLine(x, y, i, -3, map);
		four = getLine(x, y, i, -4, map);
		f_one = getLine(x, y, i, 1, map);
		f_two = getLine(x, y, i, 2, map);
		f_three = getLine(x, y, i, 3, map);

		// ����A 1111* *����ǰλ��  0����������λ��    ��ͬ 
		if (one == plyer && two == plyer
			&& three == plyer && four == plyer
			) {
			value(100,mark);
			continue;

		}

		// ����B 111*1
		if (one == plyer && two == plyer
			&& three == plyer && f_one == plyer) {
			value(100, mark);
			continue;

		}
		// ����C 11*11
		if (one == plyer && two == plyer
			&& f_one == plyer && f_two == plyer) {
			value(100, mark);
			continue;

		}

		if (one == plyer && two == plyer
			&& three == plyer) {
			if (f_one == 0) {
				value(60,mark);//����A 2111*0
				if (four == 0) {
					value(90, mark);//����A 0111*0        

				}

			}
			if ((f_one == -plyer || f_one == 2) && four == 0) {
				value(60, mark);//����B 0111*2

			}
			continue;

		}


		if (one == plyer && two == plyer
			&& f_one == plyer) {
			if (three == 0 && f_two == 0) {
				value(90, mark);//����B 011*10           
				continue;

			}
			if ((three == -plyer || three == 2) && (f_two == -plyer || f_two == 2)) {
				continue;

			}
			else {
				value(60, mark);//����C 211*10 011*12 
				continue;


			}
			//����D 1*101

			if (one == plyer && f_one == plyer
				&& f_two == 0 && f_three == plyer) {
				value(60, mark);
				continue;
			}

		}
		//����A   011*0      2
		if (one == plyer && two == plyer
			&& three == 0 && f_one == 0) {
			value(50, mark);
			continue;

		}
		//���� 01*10
		if (one == plyer && f_one == plyer
			&& two == 0 && f_two == 0) {
			value(50, mark);
			continue;

		}
		//����B 01*010       2
		if (one == plyer && f_one == 0 && f_two == plyer
			&& two == 0 && f_three == 0) {
			value(50, mark);
			continue;

		}

		if (one == plyer) {
			value(20, mark);
			continue;
		}
		if (one == 0 && two == plyer) {
			value(20, mark);
			continue;
		}
		

	}

	return mark;
}
void judgement2(int x, int y, int map[14][14], int plyer, int situation[18][14][5]) {//�������ɺ���
	int value = 0;
	int numoftwo = 0;
	int nub = 0;
	for (int i = 1; i <= 8; i++) { // 8������
								   
		if (i == 3 || i == 5 || i == 7) {
			situation[x][y][nub] = value;
			nub++;
			value = 0;
		}
		//���� 11111*      
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer && getLine(x, y, i, -4, map) == plyer
			&& getLine(x, y, i, -5, map) == plyer) {
			value += 8;
			continue;

		}
		// ���� 01111* *����ǰ��λ��  0����������λ��    ��ͬ 
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer && getLine(x, y, i, -4, map) == plyer
			&& getLine(x, y, i, -5, map) == 0) {
			value += 7;
			continue;

		}
		// ����A 21111*
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer && getLine(x, y, i, -4, map) == plyer
			&& (getLine(x, y, i, -5, map) == -plyer || getLine(x, y, i, -5, map) == 2)) {
			value += 6;
			continue;

		}
		// ����B 111*1
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer && getLine(x, y, i, 1, map) == plyer) {
			value += 6;
			continue;

		}
		// ����C 11*11
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, 1, map) == plyer && getLine(x, y, i, 2, map) == plyer) {
			value += 6;
			continue;

		}
		
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer) {
			if (getLine(x, y, i, 1, map) == 0) {
				value += 3;//����A 2111*0
				if (getLine(x, y, i, -4, map) == 0) {
					value += 2;//����A 0111*0        2

				}

			}
			if ((getLine(x, y, i, 1, map) == -plyer || getLine(x, y, i, 1, map) == 2) && getLine(x, y, i, -4, map) == 0) {
				value += 3;//����B 0111*2

			}
			continue;

		}
		
		
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, 1, map) == plyer) {
			if (getLine(x, y, i, -3, map) == 0 && getLine(x, y, i, 2, map) == 0) {
				value += 4;//����B 011*10           
				continue;

			}
			if ((getLine(x, y, i, -3, map) == -plyer || getLine(x, y, i, -3, map) == 2) && (getLine(x, y, i, 2, map) == -plyer || getLine(x, y, i, 2, map) == 2)) {
				continue;

			}
			else {
				value += 3;//����C 211*10 011*12 
				continue;


			}
			//����D 1*101

			if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, 1, map) == plyer
				&& getLine(x, y, i, 2, map) == 0 && getLine(x, y, i, 3, map) == plyer) {
				value += 3;
				continue;
			}

		}
		//���A   011*0      2
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == 0 && getLine(x, y, i, 1, map) == 0) {
			value += 2;
			continue;

		}
		//���� 01*10
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, 1, map) == plyer
			&& getLine(x, y, i, -2, map) == 0 && getLine(x, y, i, 2, map) == 0) {
			value += 1;
			continue;

		}
 		//���B 01*010       2
 		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, 1, map) == 0 && getLine(x, y, i, 2, map) == plyer
			&& getLine(x, y, i, -2, map) == 0 && getLine(x, y, i, 3, map) == 0) {
			value += 2;
			continue;

		}
		
		

	}
	situation[x][y][nub] = value;
	situation[x][y][4] = 1;//�Ƿ�����
}//�������ɺ���
void EdgeOfFive(int x, int y, int map[14][14], int plyer, int situation[18][14][5]) {
	int value = 0;
	int nub = 0;
	int x1, y1;
	for (int i = 1; i <= 8; i++) { // 8������
		if (i == 3 || i == 5|| i == 7) {
			x1 = x;y1 = y;
			if (x == 0)
				x1 = 14;
			if (y == 0)
				x1 = 15;
			if (x == 13)
				x1 = 16;
			if (y == 13)
				x1 = 17;
			situation[x1][y1][nub] = value;
			nub++;
			value = 0;
		}
		//���� 1111*
		if (getLine(x, y, i, -1, map) == plyer && getLine(x, y, i, -2, map) == plyer
			&& getLine(x, y, i, -3, map) == plyer && getLine(x, y, i, -4, map) == plyer
			) {
			value += 1000000;
		}
	}
	x1 = x;y1 = y;
	if (x == 0)
		x1 = 14;
	if (y == 0)
		x1 = 15;
	if (x == 13)
		x1 = 16;
	if (y == 13)
		x1 = 17;
	situation[x1][y1][nub] = value;
	situation[x][y][4] = 1;//�Ƿ�����
}//////�����������ɺ���
int Eveluate(int map[14][14], int flag) {//��������Ե�Ȩ�ط��ͷ����Ե������ṹ�ľ������ֺ���
	int i, j, z, v;
	int x, y;
	int situation[18][14][5] = { 0,0,0,0,0 };
	int situation1[18][14][5] = { 0,0,0,0,0 };
	int TypeCount[2][9] = {0};
	/*�������ͱ�*/

	for (i = 0;i < 14;i++) {
		for (j = 0;j < 14;j++) {
			if (map[i][j] != 0) {
				for (z = -1;z <= 1;z++) {
					for (v = -1;v <= 1;v++) {
						x = i + z;
						y = j + v;
						if (x >= 0 && y >= 0 && x<14 && y<14)
							if (map[x][y] == 0) {
								if(situation[x][y][4]==0)
									judgement2(x, y, map, flag, situation);//��ǰ���ӷ�
								if(situation1[x][y][4]==0)
									judgement2(x, y, map, -flag, situation1);//����
						}   
					}
				}
			}
		}
	}
	for (i = 0;i < 14;i++) //ר�����ɱ߽��������
		for (j = 0;j < 14;j++) {
			if (i == 0 || j == 0 || i == 13 || j == 13)
				if (map[i][j] != 0) {
					EdgeOfFive(i, j, map, flag, situation);
					EdgeOfFive(i, j, map, -flag, situation1);
				}
		}

	/*ͳ������*/
	for (i = 0;i < 18;i++)
		for (j = 0;j < 14;j++)
			for (z = 0;z < 4;z++)
			{
				if (situation[i][j][4] == 1) {
					switch (situation[i][j][z]) {
						case FIVE:
							TypeCount[ME][FIVE]++;
							break;
						case TFOUR:
							TypeCount[ME][TFOUR]++;
							break;
						case DFOUR:
							TypeCount[ME][DFOUR]++;
							break;
						case TTHREE1:
							TypeCount[ME][TTHREE1]++;
							break;
						case TTHREE2:
							TypeCount[ME][TTHREE2]++;
							break;
						case DTHREE:
							TypeCount[ME][DTHREE]++;
							break;
						case TTWO1:
							TypeCount[ME][TTWO1]++;
							break;
						case TTWO2:
							TypeCount[ME][TTWO2]++;
							break;
					}
				}

				if (situation1[i][j][4] == 1) {
					switch (situation1[i][j][z]) {
						case FIVE:
							TypeCount[OTHER][FIVE]++;
							break;
						case TFOUR:
							TypeCount[OTHER][TFOUR]++;
							break;
						case DFOUR:
							TypeCount[OTHER][DFOUR]++;
							break;
						case TTHREE1:
							TypeCount[OTHER][TTHREE1]++;
							break;
						case TTHREE2:
							TypeCount[OTHER][TTHREE2]++;
							break;
						case DTHREE:
							TypeCount[OTHER][DTHREE]++;
							break;
						case TTWO1:
							TypeCount[OTHER][TTWO1]++;
							break;
						case TTWO2:
							TypeCount[OTHER][TTWO2]++;
							break;
					}
				}
			}
	/*����typeCount����*/
	for (i = 0;i < 2;i++) {
		TypeCount[i][TTHREE1] = TypeCount[i][TTHREE1] / 2+TypeCount[i][TTHREE1]%2;
		TypeCount[i][TTWO1] = TypeCount[i][TTWO1] / 2;
		if (TypeCount[i][DFOUR]>1)
			TypeCount[i][TFOUR]++;
	}

	/*������*/
	int myValue = 0;
	int otherValue = 0;
	if (TypeCount[ME][FIVE])
		return 9999;//�ҷ�������win���ؼ�ֵ
	if (TypeCount[OTHER][FIVE])
		return -9998;//�з�������loser���ؼ�ֵ

	if (TypeCount[ME][TFOUR])
		return 9997;//�ҷ����ģ�win���ؼ�ֵ
	if (TypeCount[ME][DFOUR])
		return 9996;//�ҷ����ģ�win���ؼ�ֵ

	if (TypeCount[OTHER][TFOUR])
		return -9995;//�ҷ��޳��Ļ��ģ��з����ģ�loser���ؼ�ֵ

	if (TypeCount[OTHER][DFOUR] && (TypeCount[OTHER][TTHREE1] || TypeCount[OTHER][TTHREE2]))
		return -9994;//�з��г��ĺͻ���, loser���ؼ�ֵ

	if ((TypeCount[ME][TTHREE1] || TypeCount[ME][TTHREE2]) && TypeCount[OTHER][DFOUR] == 0)
		return 9993;//�ҷ��л������з�û����, win���ؼ�ֵ

	if (TypeCount[OTHER][TTHREE1] + TypeCount[OTHER][TTHREE2] > 1 && TypeCount[ME][DFOUR] == 0 && TypeCount[ME][TTHREE1] + TypeCount[ME][TTHREE2] == 0)
		return -9992;//�з���������һ��,���ҷ����ĺ���,loser���ؼ�ֵ

	if (TypeCount[ME][TTHREE1] + TypeCount[ME][TTHREE2] > 1)
		myValue += 2000;//�ҷ���������һ��,��ֵ��2000
	else if (TypeCount[ME][TTHREE1] + TypeCount[ME][TTHREE2] == 1)
		myValue += 200;//�ҷ���������ֵ��200
	if (TypeCount[OTHER][TTHREE1] + TypeCount[OTHER][TTHREE2] > 1)
		otherValue += 500;//�з���������һ��,��ֵ��500
	else if (TypeCount[OTHER][TTHREE1] + TypeCount[OTHER][TTHREE2] == 1)
		otherValue += 100;//�з���������ֵ��200

	//ÿ��������10
	if (TypeCount[ME][DTHREE])
		myValue += TypeCount[ME][DTHREE] * 10;
	//ÿ��������10
	if (TypeCount[OTHER][DTHREE])
		otherValue += TypeCount[OTHER][DTHREE] * 10;
	//ÿ�������4
	if (TypeCount[ME][TTWO1]+TypeCount[ME][TTWO2]>=1)
		myValue += (TypeCount[ME][TTWO1] + TypeCount[ME][TTWO2]) * 4;
	//ÿ�������4
	if (TypeCount[OTHER][TTWO1]+TypeCount[OTHER][TTWO2]>=1)
		otherValue += TypeCount[OTHER][TTWO1] + TypeCount[OTHER][TTWO2] * 4;
	return myValue-otherValue;
}
void orderlist(L_point &head, L_point p)
{
	L_point p_new = (struct point*) malloc(sizeof(struct point));
	L_point pre = NULL;           /* preָ����Ϊtempָ��nextǰ�ı��� */
	p_new->rank = p->rank;       /* ������ֵ���½�� */
	p_new->x = p->x;
	p_new->y = p->y;
	p_new->next = NULL;

	L_point temp = (struct point*) malloc(sizeof(struct point));
	temp = head;  /*ÿ�β���ǰ������ͷ��ʼ��λ��*/

				   /*��λ�ս�㸳��ֵ*/
	if (NULL == head)
	{
		head = p_new;
		return;
	}

	/*����data��ͷ���С��ͷ���ǰ����*/
	if (p_new->rank < temp->rank)
	{
		p_new->next = temp;
		head = p_new;
		return;
	}
	else
	{
		while (NULL != temp)
		{
			if (p_new->rank >= temp->rank)/* �½��Ե�ǰ���data�Ƚ� */
			{
				pre = temp;
				temp = temp->next;/*��ǰ�����ƣ�ֱ��5������1 2 3 5 ����4����λ��*/
				continue;
			}
			else
			{
				p_new->next = temp;/* �����½�� */
				pre->next = p_new; /* temp��ǰһ����λ�õ�nextָ���½��p_new */
				break;
			}
		}
		if (NULL == temp)/* ��temp����Ϊβ���ʱ��˵����Ԫ��data��󣬽������Ϊβ��� */
		{
			p_new->next = NULL;
			pre->next = p_new;   /* temp��ǰһ����λ�õ�nextָ���½��p_new */
		}
	}
}
void orderlist_high(L_point &head, L_point p)
{
	L_point p_new = (struct point*) malloc(sizeof(struct point));
	L_point pre = NULL;           /* preָ����Ϊtempָ��nextǰ�ı��� */
	p_new->rank = p->rank;       /* ������ֵ���½�� */
	p_new->x = p->x;
	p_new->y = p->y;
	p_new->next = NULL;

	L_point temp = (struct point*) malloc(sizeof(struct point));
	temp = head;  /*ÿ�β���ǰ������ͷ��ʼ��λ��*/

				  /*��λ�ս�㸳��ֵ*/
	if (NULL == head)
	{
		head = p_new;
		return;
	}

	/*����data��ͷ���С��ͷ���ǰ����*/
	if (p_new->rank > temp->rank)
	{
		p_new->next = temp;
		head = p_new;
		return;
	}
	else
	{
		while (NULL != temp)
		{
			if (p_new->rank <= temp->rank)/* �½��Ե�ǰ���data�Ƚ� */
			{
				pre = temp;
				temp = temp->next;/*��ǰ�����ƣ�ֱ��5������1 2 3 5 ����4����λ��*/
				continue;
			}
			else
			{
				p_new->next = temp;/* �����½�� */
				pre->next = p_new; /* temp��ǰһ����λ�õ�nextָ���½��p_new */
				break;
			}
		}
		if (NULL == temp)/* ��temp����Ϊβ���ʱ��˵����Ԫ��data��󣬽������Ϊβ��� */
		{
			p_new->next = NULL;
			pre->next = p_new;   /* temp��ǰһ����λ�õ�nextָ���½��p_new */
		}
	}
}
void allow_point(int map[14][14],L_point &head,int flag) {
	int i, j, k;
	int rank1, rank2;
	int has_nbr;
	struct point *p = NULL, *a = NULL, *c = NULL;
	p = (struct point*) malloc(sizeof(struct point));

	for (i = 0;i < 14;i++) {
		for (j = 0;j < 14;j++) {
			if (map[i][j] == 0) {
				has_nbr = 0;
				for (k = 1;k <= 8;k++)
					if ((getLine(i, j, k, -1, map) != 0 && getLine(i, j, k, -1, map) != 2)|| (getLine(i, j, k, -2, map) != 0 && getLine(i, j, k, -2, map) != 2)) {
						has_nbr = 1;
						break;//������ھ�
					}
				if (has_nbr == 1) {
					rank1 = allowpoint_judgement(i, j, map, -1);//AI -1
					rank2 = allowpoint_judgement(i, j, map, 1);//��� 1
					if (rank1 >= 10 || rank2 >= 10) {
						p->x = i;
						p->y = j;
						if (rank1 > rank2)
							p->rank = rank1;
						else
							p->rank = rank2;

						orderlist_high(head, p);
						
					}

				}
			}
		}
	}
}
int min_ab(int depth, int x1, int y1, int alpha, int beta, int map[14][14],int aspect) {
	int rank;
	int best = 65535000;
	int x, y;
	L_point  head = NULL, c = NULL;


	if (depth <= 0) {
		rank = -Eveluate(map, -aspect);
		return rank;
	}
	allow_point(map, head,1);
	for (c = head;c->next != NULL;c = c->next) {
		x = c->x;
		y = c->y;
		map[x][y] = 1;
		int tmp = max_ab(depth - 1, x, y, best < alpha ? best : alpha, beta, map,aspect);
		map[x][y] = 0;
		if (tmp < best)
			best = tmp;
		if (tmp < beta)
			return best;
	}
	return best;
}
int max_ab(int depth, int x1, int y1, int alpha, int beta, int map[14][14],int aspect) {
	int x, y;
	int rank;
	int best = -65535000;
	L_point c, head=NULL;

	if (depth <= 0) {

		rank = Eveluate(map, aspect);
		return rank;
	}
	allow_point(map, head,2);

	for (c = head;c->next != NULL;c = c->next) {
		x = c->x;
		y = c->y;
		map[x][y] = -1;
		int tmp = min_ab(depth - 1, x, y, alpha, best>beta ? best : beta, map,aspect);
		map[x][y] = 0;
		if (tmp > best)
			best = tmp;
		if (tmp > alpha)
			return best;//��֦
	}
	return best;
}
void max_min_ab(int &m_x, int &m_y, int map[14][14], int depth,int aspect) {
	int best = -65535000;
	int x1 = 0, y1 = 0;
	int max_x = 0, max_y = 0;
	L_point  c = NULL, head = NULL;
	int mark1,mark2,x,y,x0,y0,x2,y2;
	int max_mark = -9999;
	int max_mark2 = -9999;
	allow_point(map, head,2);

	for (c = head;c->next != NULL;c = c->next) {
		x = c->x;
		y = c->y;
		map[x][y] = aspect;
		mark1 = -Eveluate(map, -aspect);
		map[x][y] = 0;

		map[x][y] = -aspect;
		mark2 = -Eveluate(map, aspect);
		map[x][y] = 0;
		if (mark1 >= max_mark) {
			max_mark = mark1;
			x0 = x;
			y0 = y;
		}

		if (mark2 >= max_mark2) {
			max_mark2 = mark2;
			x2 = x;
			y2 = y;
		}
	}
	if (max_mark >= 9992) {
		m_x = x0 * 30;
		m_y = y0 * 30;
		return;
	}
	if (max_mark2 >= 9994) {
		m_x = x0 * 30;
		m_y = y0 * 30;
		return;
	}
	for (c = head;c->next != NULL;c = c->next) {
		x1 = c->x;
		y1 = c->y;
		map[x1][y1] = aspect;

		int tmp = min_ab(depth - 1, x1, y1, 65535000, -65535000, map,aspect);
		if (tmp>best) {
			max_x = x1;
			max_y = y1;
			best = tmp;
		}
		map[x1][y1] = 0;
	}
	m_x = max_x * 30;
	m_y = max_y * 30;
}
void AI(int map[14][14], int rank, int &m_x, int &m_y)    {
	
	int x, y;
	int mark;
	int max_mark = -9999;
	int x0, y0;
	int i, j, k;
	int rank1,rank2;
	int has_nbr;
	struct point *p = NULL, *head = NULL, *a = NULL, *c = NULL;
	a = p = (struct point*) malloc(sizeof(struct point));
	head = p;                      //��ʼ���������ڼ�¼����

	for (i = 0;i < 14;i++) {
		for (j = 0;j < 14;j++) {
			if (map[i][j] == 0) {
				has_nbr = 0;
				for (k = 1;k < 8;k++)
					if ((getLine(i, j, k, -1, map) == -1 )|| (getLine(i, j, k, -1, map) == 1)) {
						has_nbr = 1;
						break;//������ھ�
					}
				if (has_nbr == 1) {
					//rank1 = judgement(i*30, j*30, map, -1, 1);
					//rank2 = judgement(i*30, j*30, map, 1, 1);
					if (rank1 >= 10 || rank2 >= 10) {
						p->x = i;
						p->y = j;
						if (rank1 > rank2)
							p->rank = rank1;
						else
							p->rank = rank2;
						p = (struct point*) malloc(sizeof(struct point));//������Ϣ��¼��������
						p->next = NULL;
						a->next = p;
						a = p;
					}
					
				}
			}
		}
	}

	for (c=head;c->next!=NULL;c=c->next) {
		x = c->x;
		y = c->y;
		map[x][y] = -1;
		mark = -Eveluate(map, 1);
		map[x][y] = 0;
		if (mark >=max_mark) {
			max_mark = mark;
			x0 = x;
			y0 = y;
			}
		}
	m_x = x0 * 30;
	m_y = y0 * 30;
}
/*------------*/


/*��Ϸģ�麯��*/
void downpot() {          //���Ӻ���
	int map[14][14] = { 0 };        //14*14��λ����ģ������
	int flag = 1;      //Ĭ�Ϻ�������
	int x2 = 0, y2 = 0;
	setfillcolor(black);
	solidcircle(660, 110, 14);
	struct repot *p = NULL, *head = NULL, *a = NULL;
	a = p = (struct repot*) malloc(sizeof(struct repot));
	head = p;                       //��ʼ���������ڼ�¼����

	MOUSEMSG m;                     //����¼�������������������
	while (true) {
		int x1 = 0;
		int y1 = 0;
		m = GetMouseMsg();           //�����յ��������ת��Ϊ��������
		x1 = ((m.x - s_x) / 30) * 30;
		y1 = ((m.y - s_y) / 30) * 30;
		if ((m.x - 50) % 30>15)
			x1 = ((m.x - s_x) / 30 + 1) * 30;
		if ((m.y - 50) % 30>15)
			y1 = ((m.y - s_y) / 30 + 1) * 30;
		switch (m.uMsg) {

		case WM_LBUTTONDOWN:       //����������
		{
			if (flag == 1) {       //flag=1��ʾ�����
				if (map[x1 / 30][y1 / 30] != 0)     //�ж��������Ƿ�������,0��ʾ����
					break;
				map[x1 / 30][y1 / 30] = 1;          //2ά������1��ʾ��λ�ú���
				drowpot(1, x1, y1, x2, y2, 1);
				p->x = x1;
				p->y = y1;
				p->flag = flag;
				p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
				a->next = p;
				judgewin(x1, y1, map, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
				a = p;
				x2 = x1;y2 = y1;

			}
			else {                  //flag��=1��ʾ�����
				if (map[x1 / 30][y1 / 30] != 0)   //�ж��������Ƿ�������,0��ʾ����
					break;
				map[x1 / 30][y1 / 30] = -1;    //2ά������2��ʾ��λ�ð���
				drowpot(-1, x1, y1, x2, y2, 1);
				p->x = x1;
				p->y = y1;
				p->flag = flag;
				p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
				a->next = p;

				judgewin(x1, y1, map, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
				a = p;
				x2 = x1;y2 = y1;
			}
			flag = -flag;   //������ɻ���
			break;
		}
		case WM_RBUTTONUP: {        //����Ҽ�����
			setbkcolor(yellow);
			clearcircle(x2, y2, 14);
			setlinecolor(white);
			line(x2 - 15, y2, x2 + 15, y2);
			line(x2, y2 - 15, x2, y2 + 15);
			map[x2 / 30][y2 / 30] = 0;  //��ģ�����̸�λ�ô�����
			p->x = x2;
			p->y = y2;
			p->flag = flag;
			p->f = 1;
			p = (struct repot*) malloc(sizeof(struct repot));  //��¼������Ϣ
			a->next = p;
			a = p;
			x2 = y2 = 0;
			flag = -flag;  //flag= -(-flag)=flag,������������ִ���
			break;
		}

		}
		FlushMouseMsgBuffer();    //������껺��
	}

}
void AIpot(int rank) {      //���Ӻ���
	        //14*14��λ����ģ������
	int flag = 1;      //Ĭ�Ϻ�������
	int x2 = 0, y2 = 0;
	setfillcolor(black);
	solidcircle(660, 110, 14);
	struct repot *p = NULL, *head = NULL, *a = NULL;
	a = p = (struct repot*) malloc(sizeof(struct repot));
	head = p;                       //��ʼ���������ڼ�¼����

	MOUSEMSG m;                     //����¼�������������������
	if (rank == 1) {
		potmap[6][7] = -1;
		drowpot(-1, 180, 210, x2, y2, 1);
		p->x = 180;
		p->y = 210;
		p->flag = -1;
		p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
		a->next = p;
		a = p;
		x2 = 180;y2 = 210;
	}
	while (true) {
		int x1 = 0;
		int y1 = 0;
		int m_x = 0, m_y = 0;
		m = GetMouseMsg();           //�����յ��������ת��Ϊ��������
		x1 = ((m.x - s_x) / 30) * 30;
		y1 = ((m.y - s_y) / 30) * 30;
		if ((m.x - 50) % 30 > 15)
			x1 = ((m.x - s_x) / 30 + 1) * 30;
		if ((m.y - 50) % 30 > 15)
			y1 = ((m.y - s_y) / 30 + 1) * 30;
		switch (m.uMsg) {

		case WM_LBUTTONDOWN:       //����������
		{
			if (flag == 1) {       //flag=1��ʾ�����
				if (potmap[x1 / 30][y1 / 30] != 0)     //�ж��������Ƿ�������,0��ʾ����
					break;
				potmap[x1 / 30][y1 / 30] = 1;          //2ά������1��ʾ��λ�ú���
				drowpot(1, x1, y1, x2, y2, 1);
				p->x = x1;
				p->y = y1;
				p->flag = flag;
				p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
				a->next = p;
				judgewin(x1, y1, potmap, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
				a = p;
				x2 = x1;y2 = y1;
				//AI(potmap, 1, m_x, m_y);
				max_min_ab(m_x, m_y, potmap, 3,-1);
				potmap[m_x / 30][m_y / 30] = -1;
				drowpot(-1, m_x, m_y, x2, y2, 1);
				p->x = m_x;
				p->y = m_y;
				p->flag = -flag;
				p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
				a->next = p;
				judgewin(m_x, m_y, potmap, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
				a = p;
				x2 = m_x;y2 = m_y;
			}
		}
		}
	}
}
void AI_VS_AIpot() {
	int flag = 1;      //Ĭ�Ϻ�������
	int x2 = 0, y2 = 0;
	setfillcolor(black);
	solidcircle(660, 110, 14);
	struct repot *p = NULL, *head = NULL, *a = NULL;
	a = p = (struct repot*) malloc(sizeof(struct repot));
	head = p;                       //��ʼ���������ڼ�¼����

	potmap[6][7] = -1;
	drowpot(-1, 180, 210, x2, y2, 1);
	p->x = 180;
	p->y = 210;
	p->flag = -1;
	p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
	a->next = p;
	a = p;
	x2 = 180;y2 = 210;

	while (true) {
		int x1 = 0;
		int y1 = 0;
		int m_x = 0, m_y = 0;
		max_min_ab(x1, y1, potmap, 3, 1);
		potmap[x1/30][y1/30] = 1;          //2ά������1��ʾ��λ�ú���
		drowpot(1, x1, y1, x2, y2, 1);
		p->x = x1;
		p->y = y1;
		p->flag = flag;
		p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
		a->next = p;
		judgewin(x1, y1, potmap, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
		a = p;
		x2 = x1;y2 = y1;
		max_min_ab(m_x, m_y, potmap, 3, -1);
		potmap[m_x / 30][m_y / 30] = -1;
		drowpot(-1, m_x, m_y, x2, y2, 1);
		p->x = m_x;
		p->y = m_y;
		p->flag = -flag;
		p = (struct repot*) malloc(sizeof(struct repot));  //������Ϣ��¼��������
		a->next = p;
		judgewin(m_x, m_y, potmap, a, head);//ÿ�����Ӻ����judgewin�����ж���Ӯ
		a = p;
		x2 = m_x;y2 = m_y;
	}
}
void gamestart() {    //��ӭ����

	initgraph(640, 480);
	setorigin(0, 0);
	setbkmode(TRANSPARENT);

	HWND hwnd = GetHWnd();					// ���ô��ڱ�������
	SetWindowText(hwnd, L"������---by suger");
	loadimage(NULL, _T("0.jpg"));

	const int bblack = 10;

	LOGFONT f;
	gettextstyle(&f);												// ��ȡ������ʽ
	f.lfHeight = 40;												// ��������߶�
	_tcscpy(f.lfFaceName, _T("����Ҧ��"));								// ��������
	f.lfQuality = ANTIALIASED_QUALITY;								// �������Ч��Ϊ�����  
	settextstyle(&f);												// ����������ʽ
	RECT r1 = { 0, 0, w_x, w_y / 3 };
	settextcolor(black);
	drawtext(_T("�� �� ��"), &r1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r2 = { 0,w_x,w_x / 3,w_y / 3 };
	settextstyle(30, 0, _T("����Ҧ��"));
	setlinecolor(black);
	rectangle(18, 375, 198, 425);
	drawtext(_T("�� �� ģ ʽ"), &r2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	RECT r3 = { 800,640,w_x / 3,w_y / 3 };
	settextstyle(30, 0, _T("����Ҧ��"));
	setlinecolor(black);
	rectangle(418, 375, 598, 425);
	drawtext(_T("˫ �� ģ ʽ"), &r3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	bool _single = false, _double = false, _boot = true;   //��ʾ������Ŀ���״̬

	MOUSEMSG m;    //����¼�
	while (_boot)
	{

		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:												//������������ʱ
			if (m.x > 418 && m.x < 598 && m.y>375 && m.y < 425) {           //��������ڰ�ť��Χ�ڣ����˳���ӭ���棬�����Ӧ��Ϸ����
				_single = true;                                             //������Ϸ���濪��
				_boot = false;                                              //��ӭ����ر�
				cleardevice();
				closegraph();
				drowline();
				downpot();
				//AIpot();
			}
			else if (m.x > 18 && m.x < 198 && m.y>375 && m.y < 425) {
				_double = true;
				_boot = false;
				cleardevice();
				closegraph();
				drowline();
				AIpot(1);
			}

		}
	}
}
/*------------*/

int main()
{
	gamestart();
	return 0;
}



