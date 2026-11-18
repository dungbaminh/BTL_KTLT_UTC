/*
 * Du lieu duoc luu trong nhanvien.dat o dang nhi phan.
 * Dau file la so nhan vien, tiep theo la du lieu tung nguoi.
 * Cac ham o day tra ve 1 neu lam xong, tra ve 0 neu gap loi.
 */
#include "btl.h"

/* 1. Mo file de ghi nhi phan.
 * 2. Ghi so nguoi truoc, sau do ghi lan luot du lieu tung nhan vien.
 * 3. Dong file va tra ket qua ghi thanh cong hay that bai. */
int luuFile(const Node *head) {
    FILE *f = fopen(FILE_DATA, "wb");
    int n = demNhanVien(head);
    if (!f) {
        perror("Khong mo duoc file ghi");
        return 0;
    }
    if (fwrite(&n, sizeof(n), 1, f) != 1) {
        fclose(f);
        return 0;
    }
    for (const Node *p = head; p; p = p->next)
        if (fwrite(&p->data, sizeof(NhanVien), 1, f) != 1) {
            fclose(f);
            return 0;
        }
    if (fclose(f) != 0) return 0;
    return 1;
}

/* 1. Mo file va doc so nhan vien.
 * 2. Doc tung nguoi vao danh sach tam ten moi, kiem tra du lieu khi doc.
 * 3. Doc het va khong co loi thi thay danh sach cu bang danh sach tam.
 * Neu co loi o giua thi bo danh sach tam, giu lai du lieu dang dung. */
int docFile(Node **head) {
    FILE *f = fopen(FILE_DATA, "rb");
    Node *moi = NULL;
    int n;
    if (!f) return 0;
    if (fread(&n, sizeof(n), 1, f) != 1 || n < 0 || n > 100000) {
        fclose(f);
        return 0;
    }
    for (int i = 0; i < n; i++) {
        NhanVien nv;
        /* Kiem tra doc du du lieu, chuoi co ket thuc va cac so dung gioi han.
         * memchr tim ky tu ket thuc chuoi trong dung vung nho cua mang.
         * Dung || nen neu gap mot loi thi bo qua cac dieu kien phia sau. */
        if (fread(&nv, sizeof(nv), 1, f) != 1 ||
            !memchr(nv.ma, '\0', sizeof(nv.ma)) ||
            !memchr(nv.ten, '\0', sizeof(nv.ten)) ||
            !memchr(nv.chucVu, '\0', sizeof(nv.chucVu)) ||
            rong(nv.ma) || rong(nv.ten) || rong(nv.chucVu) ||
            nv.luongCoBan < 1 || nv.luongCoBan > 1000000000 ||
            nv.ngayCong < 0 || nv.ngayCong > 26 ||
            nv.gioTangCa < 0 || nv.gioTangCa > 200 ||
            timTheoMa(moi, nv.ma) || !themCuoi(&moi, nv)) {
            giaiPhong(&moi);
            fclose(f);
            return 0;
        }
    }
    /* Doc dung so nguoi roi thi file phai ket thuc, khong con du lieu thua. */
    if (fgetc(f) != EOF || ferror(f)) {
        giaiPhong(&moi);
        fclose(f);
        return 0;
    }
    if (fclose(f) != 0) {
        giaiPhong(&moi);
        return 0;
    }
    /* Chi xoa danh sach cu sau khi da doc xong danh sach moi. */
    giaiPhong(head);
    *head = moi;
    return 1;
}
