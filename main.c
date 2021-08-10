/*
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libnitrokey/NK_C_API.h>
#include <argon2.h>

#define HASHLEN 32
#define SALTLEN 16
#define SLOT_COUNT 16

int main(int argc, char *argv[])
{
	/* argon2 kdf parameters */
	uint8_t hash1[HASHLEN];
    uint8_t salt[SALTLEN];
    memset( salt, 0x00, SALTLEN );
	uint32_t t_cost = 2;            // 2-pass computation
	uint32_t m_cost = (1<<16);      // 64 mebibytes memory usage
	uint32_t parallelism = 1;       // number of threads and lanes
    uint8_t *pwd=NULL;
    uint32_t pwdlen;
	
	uint8_t* slots;
	char *slotname=NULL;
	char *slotlogin=NULL;
	char *slotpassword=NULL;
		
	if ( argc != 2 ) {
		printf("USAGE: mykey [user-pin]\n");
		exit(1);
	}
    
	char userpin[10]; 
	memset(userpin,0,10);
	strcpy(userpin,argv[1]);

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
		slots = NK_get_password_safe_slot_status();
		for (uint8_t slot = 0; slot < SLOT_COUNT; ++slot) 
		{
			if (slots[slot] == 1)
			{
				slotname=NK_get_password_safe_slot_name(slot);
				slotlogin=NK_get_password_safe_slot_login(slot);
				slotpassword=NK_get_password_safe_slot_password(slot);
				printf("[%d] Slotname: %s \n",slot,slotname);
				printf("[%d] Slot login: %s \n",slot,slotlogin);
				printf("[%d] Slot password: %s \n",slot,slotpassword);
				printf("[%d] KDF: ",slot);
				pwd = (uint8_t *)strdup(slotpassword);
				pwdlen = strlen((char *)slotpassword);
				argon2i_hash_raw(t_cost, m_cost, parallelism, pwd, pwdlen, salt, SALTLEN, hash1, HASHLEN);
				for( int i=0; i<HASHLEN; ++i ) {
					printf( "%02x", hash1[i] );
				}
				printf("\n");
			} 
			else 
			{
				printf("Slot: %d empty\n", slot);
			}
		}
	}
	NK_logout();
	return 0;
}
