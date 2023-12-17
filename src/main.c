/*
 * Title:		%LONGPROJNAME%
 * Author:		%AUTHOR%
 * Created:		%DATE%
 *
 */
 
#include <stdio.h>

// Parameters:
// - argc: Argument count
// - argv: Pointer to the argument string - zero terminated, parameters separated by spaces
//

#include <agon/vdp_vdu.h>
#include <agon/vdp_key.h>
#include <stdio.h>
#include <mos_api.h>

#define SC_MODE 8
#define SC_WIDTH 320
#define SC_HEIGHT 240


static volatile SYSVAR *sv;

int main(int argc, char * argv[])
//int main(void)
{
	
	sv = vdp_vdu_init();
        if ( vdp_key_init() == -1 ) return 1;

        vdp_mode( SC_MODE );
        vdp_clear_screen();
        vdp_logical_scr_dims( false );
        vdp_cursor_enable( false );
	
	printf("Hello World!\n\r");

	printf("Arguments:\n\r");
	printf("- argc: %d\n\r", argc);
	
	for(int i = 0; i < argc; i++)
	{
		printf("- argv[%d]: %s\n\r", i, argv[i]);
	}

	while (1) {}

	return 0;
}
