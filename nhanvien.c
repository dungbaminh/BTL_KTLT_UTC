/*
 * File nay co phan nhap du lieu va cac thao tac voi danh sach nhan vien.
 * head tro den node dau. Neu head bang NULL thi danh sach chua co ai.
 * Moi node giu mot nhan vien va con tro next de di den nguoi tiep theo.
 */
#include "btl.h"

/* Doc mot dong bang fgets. Bo ky tu xuong dong o cuoi.
 * Neu nhap qua dai thi doc bo phan du de lan nhap sau khong bi anh huong. */
void docDong(char *s, size_t n) {
    size_t len;
    int c;
    if (!fgets(s, (int)n, stdin)) {
        puts("Loi nhap du lieu.");
        exit(1);
    }
    len = strlen(s);
    if (len && s[len - 1] == '\n') s[len - 1] = '\0';
    else while ((c = getchar()) != '\n' && c != EOF) {}
}

/* Di qua tung ky tu. Gap ky tu khong phai khoang trang thi chuoi khong rong. */
int rong(const char *s) {
    while (*s) {
        if (!isspace((unsigned char)*s)) return 0;
        s++;
    }
    return 1;
}

/* Hien loi nhac roi doc chuoi. Neu bo trong thi yeu cau nhap lai. */
void nhapChuoi(const char *nhac, char *s, size_t n) {
    do {
        printf("%s", nhac);
        docDong(s, n);
        if (rong(s)) puts("Khong duoc de trong!");
    } while (rong(s));
}

/* Doc du lieu vao chuoi truoc, sau do dung sscanf de lay so nguyen.
 * Chi nhan khi dung kieu so va nam trong khoang min den max. */
int nhapInt(const char *nhac, int min, int max) {
    /* extra giup phat hien ky tu thua, vi du nhap 12abc. */
    char buf[128], extra;
    int x;
    for (;;) {
        printf("%s", nhac);
        docDong(buf, sizeof(buf));
        if (sscanf(buf, " %d %c", &x, &extra) == 1 && x >= min && x <= max) return x;
        printf("Vui long nhap so nguyen tu %d den %d.\n", min, max);
    }
}

/* Lam tuong tu nhapInt, nhung doc so thuc bang %lf. */
double nhapDouble(const char *nhac, double min, double max) {
    /* extra giup phat hien ky tu thua, vi du nhap 12abc. */
    char buf[128], extra;
    double x;
    for (;;) {
        printf("%s", nhac);
        docDong(buf, sizeof(buf));
        if (sscanf(buf, " %lf %c", &x, &extra) == 1 && x >= min && x <= max) return x;
        puts("Gia tri khong hop le, vui long nhap lai (dung dau cham cho so thap phan).");
    }
}

/* Xin bo nho cho mot node. Co bo nho roi moi chep du lieu nhan vien vao. */
Node *taoNode(NhanVien nv) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (!p) {
        puts("Khong du bo nho!");
        return NULL;
    }
    p->data = nv;
    p->next = NULL;
    return p;
}

/* Tim tu dau danh sach. strcmp tra ve 0 nghia la hai ma giong nhau. */
Node *timTheoMa(Node *head, const char *ma) {
    for (Node *p = head; p != NULL; p = p->next)
        if (strcmp(p->data.ma, ma) == 0) return p;
    return NULL;
}

/* 1. Tao node moi.
 * 2. Neu danh sach rong thi cho head tro vao node do.
 * 3. Neu da co nguoi thi di toi cuoi danh sach roi noi node moi vao. */
int themCuoi(Node **head, NhanVien nv) {
    Node *p = taoNode(nv);
    Node *q;
    if (!p) return 0;
    if (!*head) {
        *head = p;
        return 1;
    }
    q = *head;
    while (q->next) q = q->next;
    q->next = p;
    return 1;
}

/* Lay node dau ra, chuyen head sang node ke tiep roi free node cu.
 * Lap lai cho den khi head bang NULL. */
void giaiPhong(Node **head) {
    Node *p;
    while (*head) {
        p = *head;
        *head = p->next;
        free(p);
    }
}

/* In ten cac cot cua bang. Do rong trong printf giup cac cot thang nhau. */
void inTieuDe(void) {
    printf("%-12s %-24s %-16s %13s %9s %9s %16s\n",
           "Ma NV", "Ho ten", "Chuc vu", "Luong CB", "Ngay cong", "Tang ca", "Thuc nhan");
    puts("-------------------------------------------------------------------------------------------------------------");
}

/* In thong tin mot nguoi va goi tinhLuong de lay so tien thuc nhan. */
void inMotNV(const NhanVien *nv) {
    printf("%-12.12s %-24.24s %-16.16s %13.0f %9d %9.1f %16.0f\n",
           nv->ma, nv->ten, nv->chucVu, nv->luongCoBan,
           nv->ngayCong, nv->gioTangCa, tinhLuong(nv));
}

/* Kiem tra danh sach rong truoc. Neu co nguoi thi in lan luot tung node. */
void hienThi(Node *head) {
    if (!head) {
        puts("Danh sach rong.");
        return;
    }
    inTieuDe();
    for (Node *p = head; p; p = p->next) inMotNV(&p->data);
}

/* 1. Nhap ma va kiem tra ma da co chua.
 * 2. Nhap ten, chuc vu va luong co ban.
 * 3. Dat ngay cong, tang ca bang 0 roi them nguoi do vao cuoi danh sach. */
void themNhanVien(Node **head) {
    NhanVien nv;
    nhapChuoi("Ma nhan vien: ", nv.ma, sizeof(nv.ma));
    if (timTheoMa(*head, nv.ma)) {
        puts("Ma nhan vien da ton tai!");
        return;
    }
    nhapChuoi("Ho ten: ", nv.ten, sizeof(nv.ten));
    nhapChuoi("Chuc vu: ", nv.chucVu, sizeof(nv.chucVu));
    nv.luongCoBan = nhapDouble("Luong co ban (VND): ", 1, 1000000000);
    nv.ngayCong = 0;
    nv.gioTangCa = 0;
    /* Dau ? : chon thong bao theo ket qua them: 1 la duoc, 0 la loi. */
    puts(themCuoi(head, nv) ? "Them thanh cong." : "Them that bai.");
}

/* Tim nhan vien theo ma truoc. Tim thay moi nhap thong tin thay the.
 * Phan nay sua ten, chuc vu va luong co ban, con ngay cong van giu nguyen. */
void suaNhanVien(Node *head) {
    char ma[20];
    Node *p;
    nhapChuoi("Nhap ma NV can sua: ", ma, sizeof(ma));
    p = timTheoMa(head, ma);
    if (!p) {
        puts("Khong tim thay nhan vien.");
        return;
    }
    nhapChuoi("Ho ten moi: ", p->data.ten, sizeof(p->data.ten));
    nhapChuoi("Chuc vu moi: ", p->data.chucVu, sizeof(p->data.chucVu));
    p->data.luongCoBan = nhapDouble("Luong co ban moi: ", 1, 1000000000);
    puts("Cap nhat thanh cong.");
}

/* 1. Tim node can xoa, dong thoi nho node dung truoc no.
 * 2. Noi lai danh sach de bo qua node can xoa.
 * 3. Giai phong node vua bo ra. */
void xoaNhanVien(Node **head) {
    char ma[20];
    Node *p = *head, *truoc = NULL;
    nhapChuoi("Nhap ma NV can xoa: ", ma, sizeof(ma));
    while (p && strcmp(p->data.ma, ma) != 0) {
        truoc = p;
        p = p->next;
    }
    if (!p) {
        puts("Khong tim thay nhan vien.");
        return;
    }
    /* Co node dung truoc thi noi no voi node dung sau p. */
    if (truoc) truoc->next = p->next;
    /* Neu p o dau danh sach thi phai doi head. */
    else *head = p->next;
    free(p);
    puts("Xoa thanh cong.");
}

/* Nhap ma can tim. Co nhan vien do thi in thong tin, khong co thi bao lai. */
void timKiem(Node *head) {
    char ma[20];
    Node *p;
    nhapChuoi("Nhap ma NV can tim: ", ma, sizeof(ma));
    p = timTheoMa(head, ma);
    if (!p) {
        puts("Khong tim thay nhan vien.");
        return;
    }
    inTieuDe();
    inMotNV(&p->data);
}
