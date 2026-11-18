/*
 * Chuong trinh bat dau chay tu ham main o file nay.
 * Trinh tu la: doc du lieu cu, hien menu, lam theo lua chon roi luu khi thoat.
 */
#include "btl.h"

/* In cac lua chon de nguoi dung biet can nhap so nao. */
void menu(void) {
    puts("\n========== QUAN LY CHAM CONG & TINH LUONG ==========");
    puts("1. Them nhan vien");
    puts("2. Hien thi danh sach nhan vien");
    puts("3. Sua thong tin nhan vien");
    puts("4. Xoa nhan vien");
    puts("5. Tim kiem nhan vien theo ma");
    puts("6. Cham cong nhan vien");
    puts("7. Tinh va in bang luong");
    puts("8. Sap xep theo luong giam dan");
    puts("9. Thong ke quy luong (de quy)");
    puts("10. Luu du lieu vao file");
    puts("11. Doc du lieu tu file");
    puts("0. Thoat va tu dong luu");
}

/* 1. Tao danh sach rong va thu doc file da luu.
 * 2. Lap menu cho den khi nguoi dung chon 0.
 * 3. Giai phong danh sach truoc khi ket thuc chuong trinh. */
int main(void) {
    Node *head = NULL;
    int chon;
    if (docFile(&head)) puts("Da tai du lieu tu file nhanvien.dat.");
    else puts("Chua co file du lieu hop le. Bat dau voi danh sach rong.");
    do {
        menu();
        chon = nhapInt("Lua chon (0-11): ", 0, 11);
        /* Moi case goi ham ung voi so vua chon. break de ket thuc case do. */
        switch (chon) {
            case 1:
                themNhanVien(&head);
                break;
            case 2:
                hienThi(head);
                break;
            case 3:
                suaNhanVien(head);
                break;
            case 4:
                xoaNhanVien(&head);
                break;
            case 5:
                timKiem(head);
                break;
            case 6:
                chamCong(head);
                break;
            case 7:
                hienThi(head);
                break;
            case 8:
                sapXepLuong(head);
                break;
            case 9:
                thongKe(head);
                break;
            case 10:
                puts(luuFile(head) ? "Luu file thanh cong." : "Luu file that bai!");
                break;
            case 11:
                puts(docFile(&head) ? "Doc file thanh cong." : "Doc file that bai; du lieu hien tai duoc giu nguyen.");
                break;
            case 0:
                puts(luuFile(head) ? "Da luu du lieu. Tam biet!" : "CANH BAO: Khong luu duoc du lieu!");
                break;
        }
    } while (chon != 0);
    /* Tra lai bo nho da xin bang malloc truoc khi thoat. */
    giaiPhong(&head);
    return 0;
}
