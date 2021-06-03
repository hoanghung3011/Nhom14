#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
#include <string.h>
using namespace std;

#define M 20  // so Buckets


struct Sach// dinh nghia cau truc sach
{
	char maSach[10];
	char tenSach[20];
	char tenTG[20];
};


typedef struct Node// dinh nghia cau truc nut cua cac buckets
{
	Sach key;
	struct Node* next;
} Nodetype;


typedef Nodetype* PHNode;//dinh nghia nut con tro kieu PHNode


PHNode HashTable[M];//mang con tro Bucket gom M bucket


void initialize()//ham khoi tao bang bam
{
	for (int i = 0; i < M; i++)
	{
		HashTable[i] = NULL;
	}
}

int hashFunc(char h)//ham bam
{
	return (h % 23);
}

PHNode createNode(Sach k)//tao nut khoa k 
{
	PHNode p;
	p = (PHNode)malloc(sizeof(Nodetype));
	p->key = k;
	p->next = NULL;
	return p;
}

void  InsertList(PHNode& head, PHNode G) //them khoa k vao dslk hastable[i]
{
	PHNode  p, q;
	p = head;
	while (p != NULL)
	{
		if (strcmp(p->key.maSach, G->key.maSach) > 0) break;
		q = p;
		p = q->next;
	}
}

void themKvaobucket(int i, Sach k)// them khoa k vao bucket thu i
{
	PHNode p, t;
	p = HashTable[i];
	t = createNode(k);
	if (p == NULL)
	{
		HashTable[i] = t;
	}
	else
	{
		InsertList(HashTable[i], t);
	}
}

void themKvaobang(Sach k)//them khoa k vào hashtable
{
	int i = hashFunc(k.maSach[0]);
	themKvaobucket(i, k);
}

void TraverseBucket(int i)//duyet bucket
{
	PHNode p;
	p = HashTable[i];
	while (p != NULL)
	{
		cout << "\nMa so sach: " << p->key.maSach;
		cout << "\nTen sach: " << p->key.tenSach;
		cout << "\nTen tac gia:" << p->key.tenTG;
		p = p->next;
	}
}

void Traverse()//duyet toan bo hashtable
{
	for (int i = 0; i < M; i++)
	{
		cout << "\nVi tri " << i << " :";
		TraverseBucket(i);
		cout << "\n<-------------->" << endl;
	}
}

void timSach(char* a)//ham tim sach trong kho sach
{
	int i = hashFunc(a[0]);
	PHNode p = HashTable[i];
	while (p != NULL && strcmp(p->key.maSach, a) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "\nKhong tim thay sach co ma so " << a << " trong danh sach";
	}
	else
	{
		cout << "\nDa tim thay sach co ma so " << p->key.maSach << ": " << p->key.tenSach
			<< " cua tac gia:" << p->key.tenTG;
	}
}

void updateTenSach(char* a, char* a1)//ham cap nhat ten sach
{
	cin.ignore();
	int i = hashFunc(a[0]);
	PHNode p = HashTable[i];
	while (p != NULL && strcmp(p->key.maSach, a) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "\nKhong tim thay " << a << " trong danh sach";
	}
	else
	{
		strcpy_s(p->key.tenSach, a1);
	}
}

void Pop(PHNode& p)//lay phan tu dau xau
{
	Sach k;
	PHNode q;
	q = p;
	p = p->next;
	q->next = NULL;
	k = q->key;
	delete(q);
}

void XoaSauQ(PHNode& q)//xoa nut sau q
{
	PHNode p;
	p = q->next;
	q->next = p->next;
	p->next = NULL;
	delete(p);
}

void xoaSach(char* a)//xoa 1 quyen sach trong kho sach
{
	PHNode p, q;
	int i = hashFunc(a[0]);
	p = HashTable[i];
	while (p != NULL && strcmp(p->key.maSach, a) != 0)
	{
		q = p;
		p = p->next;
	}
	if (p == NULL)
	{
		cout << "\nKhong tim thay " << a << " trong danh sach";
	}
	if (p == HashTable[i])
	{
		Pop(HashTable[i]);
	}
	else XoaSauQ(q);
}


void menu()//menu chuc nang cua chuong trinh
{
	cout << "\n\n\t\t\t\tDANH MUC SACH TRA CUU";
	cout << "\n\nVui long chon cac chuc nang sau:";
	cout << "\n\n1.Them sach vao danh sach";
	cout << "\n\n2.Xoa sach khoi danh sach";
	cout << "\n\n3.Cap nhat ten sach";
	cout << "\n\n4.Tim sach trong kho";
	cout << "\n\n5.In danh muc sach";
	cout << "\n\n0.Thoat";
	cout << "\n\nChuc nang ban chon:";
}

int main()
{
	Sach h;
	char x[100], y[100];
	int chon;
	initialize();
	do
	{
		menu();
		cin >> chon;
		switch (chon)
		{
		case 1:
			cout << "\n\nNhap ma so sach can them:";
			cin.ignore();
			cin.getline(h.maSach, 100);
			cout << "\nNhap ten quyen sach:";
			fflush(stdin);
			cin.getline(h.tenSach, 100);
			cout << "\nNhap ten tac gia:";
			fflush(stdin);
			cin.getline(h.tenTG, 100);
			themKvaobang(h);
			break;
		case 2:
			cout << "\nNhap ma so sach can xoa: ";
			cin.ignore();
			cin.getline(x, 100);
			xoaSach(x);
			break;
		case 3:
			cout << "\nNhap ma so sach can cap nhat:";
			cin.ignore();
			cin.getline(x, 100);
			cout << "\nNhap ten sach cap nhat cua " << x << ": ";
			fflush(stdin);
			cin.getline(y, 100);
			updateTenSach(x, y);
			break;
		case 4:
			cout << "\nNhap ma so sach can tim: ";
			cin.ignore();
			cin.getline(x, 100);
			timSach(x);
			break;
		case 5:
			cout << "\n<--DANH SACH SACH TRONG KHO-->";
			Traverse();
		}
	} while (chon != 0);
	return 0;
}