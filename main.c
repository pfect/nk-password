#include <stdio.h>
#include <stdlib.h>
#include <libnitrokey/NK_C_API.h>

int main(void)
{
		char userpin[]=""; // Set user pin here
	
        if (NK_login_auto() != 1) {
                fprintf(stderr, "No Nitrokey found.\n");
                return 1;
        }
        enum NK_device_model model = NK_get_device_model();
        printf("Connected to ");
        switch (model) {
        case NK_PRO:
                printf("a Nitrokey Pro");
                break;
        case NK_STORAGE:
                printf("a Nitrokey Storage");
                break;
        case NK_LIBREM:
                printf("a Librem Key");
                break;
        default:
                printf("an unsupported Nitrokey");
                break;
        }
        char* serial_number = NK_device_serial_number();
        if (serial_number)
            printf(" with serial number %s\n", serial_number);
        else
            printf(" -- could not query serial number!\n");
        free(serial_number);
        
        if ( NK_user_authenticate(userpin, "temppw") == 0 ) 
        {
			printf("Auth ok!\n");
		}
        if ( NK_enable_password_safe(userpin) == 0 )
        {
			printf("Password safe enabled\n");
			char *slotname=NULL;
			slotname=NK_get_password_safe_slot_name(1);
			printf("Slotname: %s \n",slotname);
			char *slotlogin=NULL;
			slotlogin=NK_get_password_safe_slot_login(1);
			printf("Slot login: %s \n",slotlogin);
			char *slotpassword=NULL;
			slotpassword=NK_get_password_safe_slot_password(1);
			printf("Slot password: %s \n",slotpassword);
		}
        
        NK_logout();
        return 0;
}
