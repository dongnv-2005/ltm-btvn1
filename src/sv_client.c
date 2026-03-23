#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>

typedef struct {
    char mssv[20], hoten[50], ngaysinh[20];
    float diem;
} SinhVien;

int main(int argc, char *argv[]) {
    if (argc != 3) return 1;
    WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));
    connect(s, (struct sockaddr *)&server, sizeof(server));

    SinhVien sv;
    printf("MSSV: "); scanf("%s", sv.mssv); fflush(stdin);
    printf("Ho ten: "); gets(sv.hoten);
    printf("Ngay sinh (dd/mm/yyyy): "); scanf("%s", sv.ngaysinh);
    printf("Diem TB: "); scanf("%f", &sv.diem);

    send(s, (char*)&sv, sizeof(sv), 0);
    printf("Da gui du lieu!\n");

    closesocket(s); WSACleanup();
    return 0;
}