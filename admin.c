#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"

int adminLogin() {
    const char *admin_username = "admin123";
    const char *admin_password = "123admin";

    char ad_username[20];
    char ad_password[20];

    printf("Enter admin ID: ");
    scanf("%s", ad_username);

    printf("Enter admin password: ");
    scanf("%s", ad_password);

    if (strcmp(ad_username, admin_username) == 0 && strcmp(ad_password, admin_password) == 0) {
        printf("Login successful\n");
        return 1;
    }
    else {
        printf("Invalid Admin ID or Password. Try again!\n");
        return 0;
    }
}
