#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define BUFF_SIZE 80

GtkBuilder *builder;
GtkWidget *beginWindow;

GtkWidget *LoginWindow;
GtkWidget *usernameLoginEntry;
GtkWidget *passwordLoginEntry;
GtkWidget *errorLoginLabel;
GtkWidget *errorRegisLabel;

GtkWidget *RegisterWindow;
GtkWidget *usernameRegEntry;
GtkWidget *passwordRegEntry;
GtkWidget *passwordAgainRegEntry;

char buff[80];
int rcvBytes;
int sock_app;

void trim(char s[])
{
    int i = strlen(s);
    while (s[0] == ' ')
    {
        for (int j = 0; j < i; j++)
            s[j] = s[j + 1];
        i--;
    }
    while (s[i - 1] == ' ' || s[i - 1] == '\n')
        i--;
    s[i] = '\0';
}

int checkSpace(char s[])
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == ' ')
            return 1;
    }
    return 0;
}

int app(int argc, char **argv, int sockfd)
{
    gtk_init(&argc, &argv);
    sock_app = sockfd;

    builder = gtk_builder_new_from_file("login.glade");
    beginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "beginWindow"));
    gtk_window_set_title(GTK_WINDOW(beginWindow), "Uno");

    LoginWindow = GTK_WIDGET(gtk_builder_get_object(builder, "LoginWindow"));
    gtk_window_set_title(GTK_WINDOW(LoginWindow), "Đăng nhập");
    usernameLoginEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameLoginEntry"));
    passwordLoginEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordLoginEntry"));
    errorLoginLabel = GTK_WIDGET(gtk_builder_get_object(builder, "errorLoginLabel"));

    RegisterWindow = GTK_WIDGET(gtk_builder_get_object(builder, "RegisterWindow"));
    gtk_window_set_title(GTK_WINDOW(RegisterWindow), "Đăng ký");
    usernameRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "usernameRegEntry"));
    passwordRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordRegEntry"));
    passwordAgainRegEntry = GTK_WIDGET(gtk_builder_get_object(builder, "passwordAgainRegEntry"));
    errorRegisLabel = GTK_WIDGET(gtk_builder_get_object(builder, "errorRegisLabel"));

    g_signal_connect(beginWindow, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    // fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    gtk_widget_show(beginWindow);

    gtk_main();

    return EXIT_SUCCESS;
}

void on_loginBtn_clicked()
{
    gtk_widget_show(LoginWindow);
    gtk_widget_hide(beginWindow);
    strcpy(buff, "1");
    send(sock_app, buff, strlen(buff), 0);
    rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
    buff[rcvBytes] = '\0';
}

void on_LoginWindow_destroy()
{
    gtk_widget_show(beginWindow);
    gtk_widget_hide(LoginWindow);
    gtk_editable_delete_text(GTK_EDITABLE(usernameLoginEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordLoginEntry), 0, -1);
}

void on_loginSubmitBtn_clicked()
{

    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(usernameLoginEntry)));
    trim(tmp);
    if (checkSpace(tmp) == 1)
    {
        //loi
        gtk_label_set_text(GTK_LABEL(errorLoginLabel), "username khong co dau cach!");
    }
    else
    {

        printf("-%s-\n", tmp);
        strcpy(buff, tmp);
        sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordLoginEntry)));
        printf("-%s-\n", tmp);
        trim(tmp);
        if (checkSpace(tmp) == 1)
        {
            //loi
            gtk_label_set_text(GTK_LABEL(errorLoginLabel), "password khong co dau cach!");
        }
        else
        {
            strcat(buff, " ");
            strcat(buff, tmp);
            send(sock_app, buff, strlen(buff), 0);
            rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
            if (rcvBytes < 0)
            {
                perror("Error: ");
                return;
            }
            buff[rcvBytes] = '\0';
            if (strcmp(buff, "OK") == 0)
            {
                printf("\n-------------Let's play-------------\n");
                on_LoginWindow_destroy();
                //break;
            }
            else
            {
                gtk_label_set_text(GTK_LABEL(errorLoginLabel), buff);
                //continue;
            }
        }
    }
}

void on_registerBtn_clicked()
{
    gtk_widget_show(RegisterWindow);
    gtk_widget_hide(beginWindow);
    strcpy(buff, "2");
    send(sock_app, buff, strlen(buff), 0);
    rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
    buff[rcvBytes] = '\0';
}

void on_RegisterWindow_destroy()
{
    gtk_widget_show(beginWindow);
    gtk_widget_hide(RegisterWindow);
    gtk_editable_delete_text(GTK_EDITABLE(usernameRegEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordRegEntry), 0, -1);
    gtk_editable_delete_text(GTK_EDITABLE(passwordAgainRegEntry), 0, -1);
}

void on_registerSubmitBtn_clicked()
{
    char tmp[128];
    sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(usernameRegEntry)));
    trim(tmp);
    printf("-%s-\n", tmp);
    if (checkSpace(tmp) == 1)
    {
        //loi
        gtk_label_set_text(GTK_LABEL(errorRegisLabel), "username khong co dau cach!");
    }
    else
    {

        strcpy(buff, tmp);
        strcat(buff, " ");
        sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordRegEntry)));
        if (checkSpace(tmp) == 1)
        {
            //loi
            gtk_label_set_text(GTK_LABEL(errorRegisLabel), "password khong co dau cach!");
        }
        else
        {

            printf("-%s-\n", tmp);
            strcat(buff, tmp);
            strcat(buff, " ");
            sprintf(tmp, "%s", gtk_entry_get_text(GTK_ENTRY(passwordAgainRegEntry)));
            if (checkSpace(tmp) == 1)
            {
                //loi
                gtk_label_set_text(GTK_LABEL(errorRegisLabel), "password khong co dau cach!");
            }
            else
            {

                printf("-%s-\n", tmp);
                strcat(buff, tmp);
                printf("-%s-\n", buff);
                send(sock_app, buff, strlen(buff), 0);
                rcvBytes = recv(sock_app, buff, BUFF_SIZE, 0);
                if (rcvBytes < 0)
                {
                    perror("Error: ");
                    return;
                }
                buff[rcvBytes] = '\0';
                if (strcmp(buff, "OK") == 0)
                {
                    printf("\nĐăng ký tài khoản thành công\n");
                    on_RegisterWindow_destroy();
                }
                gtk_label_set_text(GTK_LABEL(errorRegisLabel), buff);
            }
        }
    }
}
