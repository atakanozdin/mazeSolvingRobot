
# Author by Atakan ÖZDİN
# www.robotikteknik.com

include <16F873A.h>
device adc=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS      // speed Osc (> 4mhz for PCM/PCH) (>10mhz for PCD)
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected

#use delay(clock=20MHz)
#bit buzzer=0x07.6
#bit led  =0x07.5
#bit buton =0x05.5 
int16 value;
void motor (int1 m1,int16 duty1, int1 m2, int16 duty2);

int16 fire (int kanal);

void main()
{
set_tris_a(0xff);
set_tris_b(0xff);
set_tris_c(0x80);

setup_adc_ports(AN0_AN1_AN3  );
setup_adc(ADC_CLOCK_INTERNAL);

setup_spi(SPI_SS_DISABLED);

setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DIV_BY_4,249,1);
setup_ccp1(CCP_PWM);
setup_ccp2(CCP_PWM);    
enable_interrupts(GLOBAL);
buzzer=0;
motor(0,0,0,0);

while (buton==1) {led=~led; delay_ms(200);}
while(true)
{
if (fire(2)<800) motor(1,800,0,800);
else if (fire(0)<500) motor(0,500,0,800);
else if (fire(1)>500) motor(0,800,0,500);
else motor(0,0,0,0);
}
}

void motor (int1 m1,int16 duty1, int1 m2, int16 duty2)
{
output_bit( PIN_C0, m2);
output_bit( PIN_C3, m1);

if (m1 ==1) { duty1=999-duty1;}
if (m2 ==1) { duty2=999-duty2;}
 
  set_pwm2_duty(duty2);
  set_pwm1_duty(duty1);
return;
}
int16 fire(int kanal)
{
set_adc_channel (kanal);
delay_us(100);
value=read_adc();
return(value);
}