#include <ctime>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include<algorithm>
#define CARD_COUNT 52

#define pb push_back

using namespace std;

typedef struct cards {
	int num; //��ǰ�ƶ����Ƶ����� 
	bool vis[CARD_COUNT];//��Ϸ���е�״̬ 
	int chu,qi; //����/���ƴ��� 
	int score; //��ǰ���� 
	int target; //Ŀ����� 
	int* choose;//�Ƶ���źͻ�ɫ 
}CARDS;

int new_card(CARDS* cur);
char* calc_card(int id);
void display_menu(CARDS* cur);
void dfs(int* cur,CARDS* bur);

int main() {
	srand(time(NULL));
	CARDS* now=(CARDS*)malloc(sizeof(CARDS));
	now->choose=(int*)malloc(sizeof(int)*64);
	for(int i=0;i<CARD_COUNT;i++) {
		now->vis[i]=0;
	}
	now->num=CARD_COUNT;
	now->chu=now->qi=3;
	now->score=0;
	now->target=300;
	now->choose[0]=0;
	for(int i=0;i<8;i++) {
		now->choose[++now->choose[0]]=new_card(now);
	}
	while(true) {
		display_menu(now);
		char ch=' ';
		int opt=0; //0���� 1���� 
		int* use=(int*)malloc(sizeof(int)*64);
		use[0]=0;
		while(ch!='\n') {
			ch=getchar();
			if(isdigit(ch)) {
				use[++use[0]]=(int)(ch-'0');
			} else if(ch=='-') {
				opt=1;
			}
		}
		if(opt==1) {
			printf("�����Ч������: ");
			for(int i=1;i<=use[0];i++) {
				printf("%d ",-use[i]);
			}
			printf("\n");
			if(now->qi==0) {
				printf("�Ѿ�û�����ƴ�����\n");
				continue;
			}
			printf("����������Щ��: ");
			for(int i=1;i<=use[0];i++) {
				printf("%s ",calc_card(now->choose[use[i]]));
			}
			printf("\n");
			for(int i=1;i<=use[0];i++) {
				now->choose[use[i]]=new_card(now);
			}
			now->qi--;
		} else {
			printf("�����Ч������: ");
			for(int i=1;i<=use[0];i++) {
				printf("%d ",use[i]);
			}
			printf("\n");
			int* pai=(int*)malloc(sizeof(int)*64);
			pai[0]=use[0];
			for(int i=1;i<=use[0];i++) {
				pai[i]=now->choose[use[i]];
			}
			sort(pai+1,pai+pai[0]+1);
			dfs(pai,now);
			for(int i=1;i<=use[0];i++) {
				now->choose[use[i]]=new_card(now);
			}
			now->chu--;
		}
		if(now->chu==0&&now->score<now->target) {
			printf("ʧ�����Ƿ����¿�ʼy/n: ");
			char ch=' ';
			while(!islower(ch)) ch=getchar();
//			getchar();
			if(ch=='y') {
				for(int i=0;i<CARD_COUNT;i++) {
					now->vis[i]=0;
				}
				now->num=CARD_COUNT;
				now->chu=now->qi=3;
				now->score=0;
				now->target=300;
				now->choose[0]=0;
				for(int i=0;i<8;i++) {
					now->choose[++now->choose[0]]=new_card(now);
				}
			} else {
				break;
			}
		} else if(now->score>=now->target) {
			printf("��ǰ�غϻ�ʤ��\n");
			printf("�Ƿ������һ�غ�y/n: ");
			char ch=' ';
			while(!islower(ch)) ch=getchar();
//			getchar();
			if(ch=='y') {
				for(int i=0;i<CARD_COUNT;i++) {
					now->vis[i]=0;
				}
				now->num=CARD_COUNT;
				now->chu=now->qi=3;
				now->score=0;
				now->target=300;
				now->choose[0]=0;
				for(int i=0;i<8;i++) {
					now->choose[++now->choose[0]]=new_card(now);
				}
			} else {
				break;
			}
		}
		getchar();
		system("cls");
	}
	return 0;
}

int new_card(CARDS* cur) {
	int oo=rand()%cur->num;
	for(int i=0;i<CARD_COUNT;i++) {
		if(cur->vis[i]==1) {
			continue;
		} else {
			if(oo==0) {
				cur->vis[i]=1;
				cur->num--;
				return i;
			}
			oo--;
		}
	}
	return 0;
}

char* calc_card(int id) {
	char* buff=(char*)malloc(sizeof(char)*64);
	switch(id/13) {
		case 0:
			strcpy(buff,"����");
			break;
		case 1:
			strcpy(buff,"����");
			break;
		case 2:
			strcpy(buff,"����");
			break;
		case 3:
			strcpy(buff,"÷��");
			break; 
	}
	switch(id%13) {
		case 0:
			buff=strcat(buff,"A");
			break;
		case 1:
			buff=strcat(buff,"2");
			break;
		case 2:
			buff=strcat(buff,"3");
			break;
		case 3:
			buff=strcat(buff,"4");
			break;
		case 4:
			buff=strcat(buff,"5");
			break;
		case 5:
			buff=strcat(buff,"6");
			break;
		case 6:
			buff=strcat(buff,"7");
			break;
		case 7:
			buff=strcat(buff,"8");
			break;
		case 8:
			buff=strcat(buff,"9");
			break;
		case 9:
			buff=strcat(buff,"10");
			break;
		case 10:
			buff=strcat(buff,"J");
			break;
		case 11:
			buff=strcat(buff,"Q");
			break;
		case 12:
			buff=strcat(buff,"K");
			break;
	}
	return buff;
}

void display_menu(CARDS* cur) {
	printf("===================================\n");
	printf("Ŀǰӵ�е�С����: ��\n");
	printf("ʣ����ƴ���:%d          ʣ�����ƴ���:%d\n",cur->chu,cur->qi);
	printf("��ǰ����:%d       Ŀ�����:%d\n",cur->score,cur->target);
	printf("��ǰ�е�����:");
	for(int i=1;i<=8;i++) {
		printf("%s  ",calc_card(cur->choose[i]));
	}
	printf("\n");
	printf("���:          1      2      3      4      5      6      7      8\n");
	return;
}

int calc_Q(int tmp) {
	if(tmp%13==0) return 11;
	if(tmp%13>=10) return 10;
	return tmp%13+1;
}

bool cmp1(int pp,int qq) {
	return pp%13<qq%13;
}

void dfs(int* cur,CARDS* bur) {
	for(int i=1;i<=cur[0];i++) {
		cout<<cur[i]<<" "<<calc_card(cur[i])<<endl;
	}
	//ͬ��˳
	TONGHUASHUN:;
	if(cur[0]==5) {
		for(int i=2;i<=cur[0];i++) {
			if(cur[i]/13!=cur[1]/13) {
				goto SITIAO;
			}
		}
		if(cur[5]-cur[1]==4) {
			int sum=100;
			for(int i=1;i<=cur[0];i++) {
				sum+=calc_Q(cur[i]);
			}
			printf("������ͬ��˳    ");
			printf("��Ч����: ");
			for(int i=1;i<=cur[0];i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 8 = %d\n",sum,sum*8);
			bur->score+=sum*8;
			return;
		}
	}
	//���� 
	SITIAO:;
//	sort(cur+1,cur+cur[0]+1,[](int pp,int qq) {
//		return pp%13<qq%13;	
//	});
	sort(cur+1,cur+cur[0]+1);
	int* cnt=(int*)malloc(sizeof(int)*13);
	for(int i=0;i<13;i++) cnt[i]=0;
	for(int i=1;i<=cur[0];i++) cnt[cur[i]%13]++;
	if(cur[0]>=4) {
		if(cnt[cur[1]%13]==4) {
			int sum=60;
			sum+=calc_Q(cur[1])*4;
			printf("����������    ");
			printf("��Ч����: ");
			for(int i=1;i<=4;i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 7 = %d\n",sum,sum*7);
			bur->score+=sum*7;
			return;
		} else if(cnt[cur[2]%13]==4) {
			int sum=60;
			sum+=calc_Q(cur[1])*4;
			printf("����������    ");
			printf("��Ч����: ");
			for(int i=2;i<=5;i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 7 = %d\n",sum,sum*7);
			bur->score+=sum*7;
			return;
		}
	}
	//��«
	HULU:;
	if(cur[0]==5) {
		if(cnt[cur[1]%13]==3&&cnt[cur[4]%13]==2
			||cnt[cur[1]%13]==2&&cnt[cur[3]%13]==3) {
			int sum=40;
			for(int i=1;i<=cur[0];i++) {
				sum+=calc_Q(cur[i]);
			}
			printf("�����˺�«    ");
			printf("��Ч����: ");
			for(int i=1;i<=cur[0];i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 4 = %d\n",sum,sum*4);
			bur->score+=sum*4;
			return;
		}
	}
	//ͬ��
	TONGHUA:;
	if(cur[0]==5) {
		for(int i=2;i<=cur[0];i++) {
			if(cur[i]/13!=cur[1]/13) {
				goto SHUNZI;
			}
		}
		int sum=35;
		for(int i=1;i<=cur[0];i++) {
			sum+=calc_Q(cur[i]);
		}
		printf("������ͬ��    ");
		printf("��Ч����: ");
		for(int i=1;i<=cur[0];i++) {
			printf("%s ",calc_card(cur[i]));
		}
		printf("\n");
		printf("�˴ε÷���: %d * 4 = %d\n",sum,sum*4);
		bur->score+=sum*4;
		return;
	}
	//˳��
	SHUNZI:;
	if(cur[0]==5) {
		if(cur[5]%13-4!=cur[1]%13) {
			goto SANTIAO;
		}
		int sum=30;
		for(int i=1;i<=cur[0];i++) {
			sum+=calc_Q(cur[i]);
		}
		printf("������˳��    ");
		printf("��Ч����: ");
		for(int i=1;i<=cur[0];i++) {
			printf("%s ",calc_card(cur[i]));
		}
		printf("\n");
		printf("�˴ε÷���: %d * 4 = %d\n",sum,sum*4);
		bur->score+=sum*4;
		return;
	}
	//����
	SANTIAO:;
	if(cur[0]>=3) {
		int p1=-1,p2=-1;
		for(int i=1;i<=cur[0]-2;i++) {
			if(cnt[cur[i]%13]==3) {
				p1=i; p2=i+2; break;
			}
		}
		if(p1!=-1) {
			int sum=30;
			for(int i=p1;i<=p2;i++) {
				sum+=calc_Q(cur[i]);
			}
			printf("����������    ");
			printf("��Ч����: ");
			for(int i=p1;i<=p2;i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 3 = %d\n",sum,sum*3);
			bur->score+=sum*3;
			return;
		}
	}
	//����
	DUIZI:;
	if(cur[0]>=2) {
		int p1=-1,p2=-1;
		for(int i=1;i<=cur[0]-1;i++) {
			if(cnt[cur[i]%13]==2) {
				p1=i; p2=i+1; break;
			}
		}
		if(p1!=-1) {
			int sum=20;
			for(int i=p1;i<=p2;i++) {
				sum+=calc_Q(cur[i]);
			}
			printf("�����˶���    ");
			printf("��Ч����: ");
			for(int i=p1;i<=p2;i++) {
				printf("%s ",calc_card(cur[i]));
			}
			printf("\n");
			printf("�˴ε÷���: %d * 2 = %d\n",sum,sum*2);
			bur->score+=sum*2;
			return;
		}
	}
	//����
	GAOPAI:;
	if(1) {
		int p1=-1;
		if(cur[1]%13==0) {
			p1=1;
		} else p1=cur[0];
		int sum=5;
		sum+=calc_Q(cur[p1]);
		printf("�����˸���    ");
		printf("��Ч����: ");
		printf("%s ",calc_card(cur[p1]));
		printf("\n");
		printf("�˴ε÷���: %d * 1 = %d\n",sum,sum*1);
		bur->score+=sum*1;
		return;
	}
}
//һ���������Ŀ�ͺ��²�֪���Ӻο�ʼ���֣��Լ���ȥѧ��һ���㷨�����ݽṹ������Ŀǰдc�Ĵ���д�ıȽϺã����Ծ���c��д�ˣ�Ŀǰֻʵ���˵�һ�׶Σ������С���ƻ���˼����ôʵ�� 
