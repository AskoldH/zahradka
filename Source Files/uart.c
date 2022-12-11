#include "uart.h"

// bude to tam??
void uart1_init(void)
{
    UART1_Init(
        9600, // rychlost
        UART1_WORDLENGTH_8D, // počet datových bitů
        UART1_STOPBITS_1, // stop bity
        UART1_PARITY_NO, // typ parity
        UART1_SYNCMODE_CLOCK_DISABLE, // synchonozační typ hodin
        UART1_MODE_TXRX_ENABLE // UART mode
    );

    UART1_Cmd(ENABLE);
}

void send_char(char c)
{
     while (!UART1_GetFlagStatus(UART1_FLAG_TXE));
        UART1_SendData8(c);
}

static uint32_t i2;
void send_str(char str[])
{
    for (i2=0; str[i2]; i2++)
        send_char(str[i2]);
}

char get_char(void)
{
    while (!UART1_GetFlagStatus(UART1_FLAG_RXNE));
    return UART1_ReceiveData8();
}


/* pokud chceme poslat cislo tak ho musime nejdriv zmenit na
str*/
const char* int_to_str(uint16_t integer)
{	

    char str_inverted[16];
    char str_final[16];

    int pocet_cifer = 0;
		int i1; /* na prochazeni for loopu, je to cely divny,
		natusim proc si nemuzu normlene tu promenou initnout v
		tom loopu*/
		
    while (integer > 0)
    {
        if (!(integer % 10))
        {	
            str_inverted[pocet_cifer] = '0';
        }
        else
        {
            str_inverted[pocet_cifer] = (integer % 10) 
						+ '0';
        }
        integer /= 10;
        ++pocet_cifer;
    }
			
    str_inverted[pocet_cifer] = '/0' ;
		
    for(i1 =0;  i1 < pocet_cifer;  i1++)
    {
        int index = (pocet_cifer -  i1) - 1;
        str_final[ i1] = str_inverted[index];
    }
		
    str_final[pocet_cifer] = '\0';

    return (str_final);
}