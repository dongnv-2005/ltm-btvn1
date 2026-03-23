#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>

int main(int argc, char *argv[]) {
    if (argc != 4) { printf("Su dung: %s <Port> <FileChao> <FileLog>\n", argv[0]); return 1; }

    WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 3);
    printf("Server dang doi tai cong %s...\n", argv[1]);

    int c = sizeof(client);
    SOCKET client_sk = accept(s, (struct sockaddr *)&client, &c);

    FILE *f1 = fopen(argv[2], "r");
    char buf[1024];
    if (f1) {
        fgets(buf, sizeof(buf), f1);
        send(client_sk, buf, strlen(buf), 0);
        fclose(f1);
    }

    int n = recv(client_sk, buf, sizeof(buf) - 1, 0);
    if (n > 0) {
        buf[n] = '\0';
        FILE *f2 = fopen(argv[3], "a");
        fprintf(f2, "IP: %s - Noi dung: %s\n", inet_ntoa(client.sin_addr), buf);
        fclose(f2);
    }

    closesocket(client_sk);
    WSACleanup();
    return 0;
}