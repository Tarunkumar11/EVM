#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#include <string.h>
#define RS 0
#define EN 1
void DATA(int);
void com(char);
void ini();
void display(char s[]);
void intd(int);
int main(void)
{
	
	DDRC=0xFF;
	DDRD=0x03;
	DDRA=0x00;
	int b=0,c=0;
	ini();
	com(0x82);
	display("BJP");
	com(0x88);
	display("CONG");
	while(1)
	{
		
		if (PINA&=1<<PD0)
			{    b++;
			com(0xC5);
			display("THANK YOU");
			_delay_ms(500);
			com(0xC5);
			display("         ");
			while(PINA&=1<<PD0){};
			}
				
				if (PINA&=1<<PD1)
				{    c++;
					com(0xC5);
					display("THANK YOU");
					_delay_ms(500);
					com(0xC5);
					display("         ");
					while(PINA&=1<<PD1){};
				}
				if (PINA&=1<<PD2)
				{
					com(0xc2);
					intd(b);
					com(0xc7);
					intd(c);
					_delay_ms(1000);
					if (b>c)
					{
						com(0x01);
						com(0x85);
						display("BJP IS");
						com(0xC6);
						display("WINNER");
					}
					else if (c>b)
					{
						com(0x01);
						com(0x85);
						display("CONG IS");
						com(0xC6);
						display("WINNER");
					}
					else
					{
						com(0x01);
						com(0x85);
						display("NO CONCLUSION");
					}
					
					
					
				}
				
	}
}
void DATA(int x)
{
	PORTC=x;  //for char print
	
	PORTD|=(1<<RS);//RS=0
	PORTD|=(1<<EN);
	_delay_ms(5);
	PORTD&=~(1<<EN);
}
void com(char x)
{
	PORTC=x;
	PORTD&=~(1<<RS);
	PORTD|=(1<<EN);
	_delay_ms(5);
	PORTD&=~(1<<EN);
}
void ini()
{
	DDRC=0xFF;
	DDRD=0x03;
	
	com(0x38);//8 bit
	com(0x06);//curser l2r
	com(0x0E);//curser on display
	com(0x01);//clear screen
	com(0x80);//0th row 0th colum
}
void display(char s[])
{
	
	int i,len=0;
	len=strlen(s);
	for(i=0;i<=len;i++)
	{
		
		DATA(s[i]);
		_delay_ms(5);
	}
	
}
void intd(int x)
{	DATA((x/1000)+48);
	x=x%1000;
	DATA((x/100)+48);
	x=x%100;
	DATA((x/10)+48);
	x=x%10;
	DATA(x+48);

}