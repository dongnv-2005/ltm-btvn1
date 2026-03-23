#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Su dung: %s <IP> <Port>\n", argv[0]); return 1; }

    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(atoi(argv[2]));

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Ket noi that bai!\n"); return 1;
    }

    char buf[1024];
    int n = recv(s, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        printf("Server chao: %s\n", buf);
    }

    printf("Nhap noi dung gui den server: ");
    fflush(stdin);
    gets(buf);
    send(s, buf, strlen(buf), 0);

    closesocket(s);
    WSACleanup();
    return 0;
}