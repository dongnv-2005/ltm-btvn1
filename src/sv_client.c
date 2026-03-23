#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

typedef struct {
    char mssv[20];
    char hoten[50];
    char ngaysinh[20];
    float diem;
} SinhVien;

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Huong dan: %s <IP_Server> <Port>\n", argv[0]);
        return 1;
    }

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Ket noi den Server that bai!\n");
        return 1;
    }

    SinhVien sv;
    memset(&sv, 0, sizeof(sv)); 

    printf("--- NHAP THONG TIN SINH VIEN ---\n");

    printf("MSSV: ");
    scanf("%19s", sv.mssv);
    clear_stdin(); 

    printf("Ho ten: ");
    fgets(sv.hoten, sizeof(sv.hoten), stdin);
    sv.hoten[strcspn(sv.hoten, "\n")] = 0; 

    printf("Ngay sinh (dd/mm/yyyy): ");
    scanf("%19s", sv.ngaysinh);
    clear_stdin(); 

    printf("Diem trung binh: ");
    scanf("%f", &sv.diem);

    send(s, (char*)&sv, sizeof(sv), 0);
    printf("\n[Thanh cong] Da gui du lieu sinh vien len Server!\n");

    closesocket(s);
    WSACleanup();
    return 0;
}