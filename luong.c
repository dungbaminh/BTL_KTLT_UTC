/*
 * File nay dung ngay cong va gio tang ca de tinh luong.
 * Cong thuc cua bai lay 26 ngay moi thang, 8 gio moi ngay, tang ca nhan 1.5.
 */
#include "btl.h"

/* Tinh tien mot ngay, tien cac ngay da lam va tien tang ca.
 * Cong hai khoan cuoi de ra luong thuc nhan. */
double tinhLuong(const NhanVien *nv) {
    double luongNgay = nv->luongCoBan / NGAY_CHUAN;
    double luongCong = luongNgay * nv->ngayCong;
    double luongTangCa = luongNgay / GIO_MOI_NGAY * HE_SO_TANG_CA * nv->gioTangCa;
    return luongCong + luongTangCa;
}

/* Tim nguoi theo ma, nhap ngay cong va gio tang ca roi tinh thu luong.
 * So moi nhap se thay so cu cua nhan vien do. */
void chamCong(Node *head) {
    char ma[20];
    Node *p;
    nhapChuoi("Nhap ma NV can cham cong: ", ma, sizeof(ma));
    p = timTheoMa(head, ma);
    if (!p) {
        puts("Khong tim thay nhan vien.");
        return;
    }
    p->data.ngayCong = nhapInt("So ngay cong trong thang (0-26): ", 0, 26);
    p->data.gioTangCa = nhapDouble("Tong gio tang ca (0-200): ", 0, 200);
    printf("Da cham cong. Luong tam tinh: %.0f VND\n", tinhLuong(&p->data));
}

/* Lay mot nguoi so voi nhung nguoi phia sau.
 * Neu nguoi phia sau co luong cao hon thi doi du lieu hai node.
 * Chi doi du lieu, cac con tro noi node van nhu cu. */
void sapXepLuong(Node *head) {
    for (Node *p = head; p; p = p->next)
        for (Node *q = p->next; q; q = q->next)
            if (tinhLuong(&p->data) < tinhLuong(&q->data)) {
                NhanVien temp = p->data;
                p->data = q->data;
                q->data = temp;
            }
    puts("Da sap xep theo luong thuc nhan giam dan.");
    hienThi(head);
}

/* Danh sach rong thi tong bang 0, day la cho dung de quy.
 * Neu con node thi lay luong nguoi dau cong tong luong cua phan con lai. */
double tongLuongDeQuy(const Node *head) {
    if (!head) return 0;
    return tinhLuong(&head->data) + tongLuongDeQuy(head->next);
}

/* Di qua moi node thi tang bien dem len 1. */
int demNhanVien(const Node *head) {
    int dem = 0;
    for (; head; head = head->next) dem++;
    return dem;
}

/* Dem so nguoi, tinh tong luong. Co it nhat mot nguoi moi tinh trung binh. */
void thongKe(Node *head) {
    int n = demNhanVien(head);
    double tong = tongLuongDeQuy(head);
    printf("So nhan vien: %d\nTong quy luong: %.0f VND\n", n, tong);
    if (n) printf("Luong trung binh: %.0f VND\n", tong / n);
}
