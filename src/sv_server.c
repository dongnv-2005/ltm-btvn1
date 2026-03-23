#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>
#include <winsock2.h>
#include <time.h>

typedef struct {
    char mssv[20], hoten[50], ngaysinh[20];
    float diem;
} SinhVien;

int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Su dung: %s <Port> <FileLog>\n", argv[0]); return 1; }
    WSADATA wsa; WSAStartup(MAKEWORD(2, 2), &wsa);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server, client;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    bind(s, (struct sockaddr *)&server, sizeof(server));
    listen(s, 5);

    printf("Server SV dang doi ket noi...\n");
    while (1) {
        int c = sizeof(client);
        SOCKET cs = accept(s, (struct sockaddr *)&client, &c);
        SinhVien sv;
        int n = recv(cs, (char*)&sv, sizeof(sv), 0);
        if (n > 0) {
            time_t t = time(NULL);
            struct tm *tm = localtime(&t);
            char ts[25]; strftime(ts, 25, "%Y-%m-%d %H:%M:%S", tm);

            FILE *f = fopen(argv[2], "a");
            fprintf(f, "%s %s %s %s %s %.2f\n", 
                    inet_ntoa(client.sin_addr), ts, sv.mssv, sv.hoten, sv.ngaysinh, sv.diem);
            fclose(f);
            printf("Da log sinh vien: %s\n", sv.mssv);
        }
        closesocket(cs);
    }
    return 0;
}