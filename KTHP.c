#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Câu 1
int nhapSoNguyen() {
    int n;
    char c;
    do {
        printf("Nhap so nguyen 1 byte n trong khoang [1,10]: ");
        if (scanf("%d%c", &n, &c) != 2 || c != '\n' || n < 1 || n > 10) {
            printf("Ban da nhap sai yeu cau. Vui long nhap lai!\n");
            while ((c = getchar()) != '\n' && c != EOF);
        }
    } while (n < 1 || n > 10);
    return n;
}

//Câu 3
struct staff {
    char staffID[4];
    char staffName[129];
    float salary;
    struct staff* next;
};

void nhap_danhsach(struct staff* head, int n) {
    struct staff* current = head;
    for (int i = 0; i < n; ++i) {
        printf("Nhap thong tin nhan vien thu %d:\n", i + 1);
        
        // Nhập staffID (4 ký tự)
        do {
            printf("Nhap staffID (4 ky tu): ");
            scanf("%s", current->staffID);
            if (strlen(current->staffID) != 4) {
                printf("Ban da nhap sai! Vui long nhap lai.\n");
            }
        } while (strlen(current->staffID) != 4);

        // Nhập staffName (129 ký tự)
        printf("Nhap staffName: ");
        scanf("%129s", current->staffName);

        // Nhập salary
        do {
            printf("Nhap salary: ");
            if (scanf("%f", &current->salary) != 1 || current->salary < 0) {
                printf("Ban da nhap sai! Vui long nhap lai.\n");
                while (getchar() != '\n');
            }
        } while (current->salary < 0);

        // Tạo một nút mới cho danh sách liên kết
        if (i < n - 1) {
            current->next = (struct staff*)malloc(sizeof(struct staff));
            current = current->next;
        } else {
            current->next = NULL;
        }
    }
}

//Câu 5
void ghiFile(struct staff* head, int n, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file de ghi.\n");
        return;
    }

    struct staff* current = head;
    while(current != NULL) {
        fprintf(file, "-----Thong tin nhan vien-----\n");
        fprintf(file, "\tMa nhan vien: %.4s\n", current->staffID);
        fprintf(file, "\tHo ten nhan vien: %s\n", current->staffName);
        fprintf(file, "\tLuong cua nhan vien: %.0f\n", current->salary);
        current = current->next;
    }

    fclose(file);
}

// Hàm giải phóng vùng nhớ của danh sách liên kết
void freeLinkedList(struct staff* head) {
    struct staff* current = head;
    while (current != NULL) {
        struct staff* next = current->next;
        free(current);
        current = next;
    } 
}


int main() {

    //Câu 1
    int n = nhapSoNguyen();
    char st[8+1];
    itoa(n + 200, st, 2);
    printf("1. n + 200 duoi dang nhi phan: %s\n", st);

    //Câu 2
    int highest_3Bits = ((n + 200) >> 5) & 0b111;
    printf("2. 3 bit cao nhat cua n + 200 la: %d\n", highest_3Bits);

    //Câu 4 
    struct staff* head = (struct staff*)malloc(sizeof(struct staff));
    nhap_danhsach(head, n);

    // Hiển thị các nhân viên có salary cao hơn 10.000.000 đồng
    printf("----Cac nhan vien co salary cao hon 10.000.000 dong:---- \n");
    struct staff* current = head;
    while (current != NULL) {
        if (current->salary > 10000000) {
            printf("\tMa nhan vien: %.4s\n", current->staffID);
            printf("\tHo ten nhan vien: %s\n", current->staffName);
            printf("\tLuong cua nhan vien: %.0f\n", current->salary);
            printf("\n");
        }
        current = current->next;
    }

    //Câu 5
    ghiFile(head, n, "danhsach_cautruc.txt");
    printf("Da ghi danh sach thong tin staff vao file danhsach_cautruc.txt\n");

    // Giải phóng vùng nhớ và gán địa chỉ head về giá trị phù hợp
    freeLinkedList(head);

    return 0;
}