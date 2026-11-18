/*
 * File nay de cac file .c dung chung kieu du lieu va khai bao ham.
 * Muon hieu du lieu cua bai, doc NhanVien roi den Node o ben duoi.
 */
/* Tranh khai bao lap neu file nay duoc include nhieu lan. */
#ifndef BTL_H
#define BTL_H
#include <stdio.h>   /* Nhap xuat va lam viec voi file. */
#include <stdlib.h>  /* malloc, free va exit. */
#include <string.h>  /* Cac ham xu ly chuoi. */
#include <ctype.h>   /* isspace de kiem tra khoang trang. */

/* Cac gia tri dung chung trong bai. */
#define FILE_DATA "nhanvien.dat"
#define NGAY_CHUAN 26.0
#define GIO_MOI_NGAY 8.0
#define HE_SO_TANG_CA 1.5

/* Thong tin can luu cho mot nhan vien. */
typedef struct {
    char ma[20];
    char ten[80];
    char chucVu[50];
    double luongCoBan;
    int ngayCong;
    double gioTangCa;
} NhanVien;

/* next giu dia chi node sau. Node cuoi co next bang NULL. */
typedef struct Node {
    NhanVien data;
    struct Node *next;
} Node;

/* Khai bao truoc de cac file .c goi duoc nhung ham nay. */
/* const nghia la ham khong sua du lieu qua con tro do. */
/* Node ** dung khi ham can thay doi chinh con tro head cua ben goi. */
void docDong(char *s, size_t n);
int rong(const char *s);
void nhapChuoi(const char *nhac, char *s, size_t n);
int nhapInt(const char *nhac, int min, int max);
double nhapDouble(const char *nhac, double min, double max);
Node *taoNode(NhanVien nv);
Node *timTheoMa(Node *head, const char *ma);
int themCuoi(Node **head, NhanVien nv);
void giaiPhong(Node **head);
void inTieuDe(void);
void inMotNV(const NhanVien *nv);
void hienThi(Node *head);
void themNhanVien(Node **head);
void suaNhanVien(Node *head);
void xoaNhanVien(Node **head);
void timKiem(Node *head);
void chamCong(Node *head);
double tinhLuong(const NhanVien *nv);
void sapXepLuong(Node *head);
double tongLuongDeQuy(const Node *head);
int demNhanVien(const Node *head);
void thongKe(Node *head);
int luuFile(const Node *head);
int docFile(Node **head);
void menu(void);
#endif
