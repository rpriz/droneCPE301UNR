

//Drone Flight controller
//Coded By: Roger Pzybyla and Nick K
//CPE 301 Final Project

//include files
#include "pinner.h"
#include <Servo.h>
 #include "Wire.h"
 #include <MPU6050_light.h>
 #include "digitalRite.h"

 //start gyro
 MPU6050 mpu(Wire);

//masks
 //Reciever channels
#define CH1Rec 0x10  //pin 10
#define CH2Rec 0x20  //pin 11
#define CH3Rec 0x40  //pin 12
#define CH4Rec 0x80   //pin 13  

  //GPIO
#define PX0 0x01  //register 0
#define PX1 0x02  //register 1
#define PX2 0x04  //register 2
#define PX3 0x08  //register 3
#define PX4 0x10  //register 4
#define PX5 0x20  //register 5
#define PX6 0x40  //register 6
#define PX7 0x80  //register 7

 //On/Off switch Channel 6
 #define CH6swch 0x08  //pin 50 
//Global Variables


unsigned long Rest_wave = 20000;
unsigned long timer_2;
int last_channel_2 = 0;
  //global timer
  unsigned long timer_micros = 0; // timer variable to store the elapsed time in milliseconds
  unsigned long timer_overflow_count = 0;  // variable to store the number of times the timer overflows
  volatile unsigned char *myTCCR2A = (unsigned char *) 0xB0;
  volatile unsigned char *myTCCR2B = (unsigned char *) 0xB1;
  volatile unsigned char *myTCTNT2 = (unsigned char *) 0xB2;
  volatile unsigned char *myTIMSK2 = (unsigned char *) 0x70;
  volatile unsigned char *myTIFR2 = (unsigned char *) 0x37;
 unsigned long current_time;
unsigned long countmicros;
 //reciever vartiables
  //ISR for reciver address variables
  volatile unsigned char *myPCMSK0 = (unsigned char *) 0x6B;  //set register 0 to 1 to enable interupts
  volatile unsigned char *myPCICR = (unsigned char *) 0x68;      //set register 7,6,5,4 to 1 to enable interupts pins 13,12,12,10 respectively

  //gyro calibration variable
  unsigned long gyroTimeSet;
  //variables for wave calculation 
  unsigned long wave_CH_1, wave_CH_2 , wave_CH_3, wave_CH_4, wave_CH_6;
  int state_CH_1, state_CH_2, state_CH_3, state_CH_4,state_CH_6;
  int cur_state_CH_1, cur_state_CH_2, cur_state_CH_3, cur_state_CH_4,cur_state_CH_6; 
  unsigned long wtime1, wtime2, wtime3, wtime4, wtime6;

  //ESC
  unsigned long esc1, esc2 ,esc3 ,esc4;
//port B

//Port D

//Port C

//Port E pins 2 / 3
//port GPIO

volatile unsigned char* ddr_e = (unsigned char*)0x2D; //pins 2/3 use registers 4/5 respectively
volatile unsigned char* pin_e = (unsigned char*)0x2C; //pins 2/3 use registers 4/5 respectively
volatile unsigned char* port_h = (unsigned char*)0x102;  // pins 6/7 use  registers 3/4  respectively
volatile unsigned char* pin_h = (unsigned char*)0x100;
volatile unsigned char* pin_b = (unsigned char*)0x23;
volatile unsigned char* port_a = (unsigned char*)0x22;
volatile unsigned char* port_b = (unsigned char*)0x25;
volatile unsigned char* port_c = (unsigned char*)0x28;
volatile unsigned char* port_e = (unsigned char*)0x2E; //pins 2/3 use registers 4/5 respectively

//Port H

//input pins
  char rePin1 = '10';//channel 1
  char rePin2 = '11';//Channel 2
  char rePin3 = '12';//Channel 3 
  char rePin4 = '13';//Channel 4 

 char swchpin = '1'; //channel 6 from reciever
//output pins
  char moPin1 = '5'; //Motor 1 Front Left channel 4
  char moPin2 = '2'; //Motor 2 Front Right channel 3
  char moPin3 = '3'; //Motor 3 Back Left channel 2
  char moPin4 = '4'; //Motor 4 Back Right channel 1

  //int variables 
 // int timer = 0;
  int timer3 = 0;
//ESC defined
Servo ESC_FL;     // create servo object to control the ESC Front Left Motor 1 pin 5
Servo ESC_FR;     // create servo object to control the ESC Fromnt Right Motor 2 pin 2
Servo ESC_BL;     // create servo object to control the ESC Back left Motor 3 pin 3
Servo ESC_BR;     // create servo object to control the ESC Back Right  Motor 4 pin 4

#define RDA 0x80
#define TBE 0x20

//set up registers for serial communication 
volatile unsigned char *myUCSR1A = (unsigned char *)0xC8;
volatile unsigned char *myUCSR1B = (unsigned char *)0xC9;
volatile unsigned char *myUCSR1C = (unsigned char *)0xCA;
volatile unsigned int  *myUBRR1  = (unsigned int *) 0xCC;
volatile unsigned char *myUDR1   = (unsigned char *)0xCE;

volatile unsigned char* my_ADMUX = (unsigned char*) 0x7C;
volatile unsigned char* my_ADCSRB = (unsigned char*) 0x7B;
volatile unsigned char* my_ADCSRA = (unsigned char*) 0x7A;
volatile unsigned int* my_ADC_DATA = (unsigned int*) 0x78;


//GPIO variables

int fON = 28;
int fOFF = 36;
int adcPin = 107;
int adcRed =51;
int adcGreen = 53;
///////////////////////////PROGRAM SETUP/////////////////////////////////////////////////////////////
void setup() {
  //start serial for testing
  Serial. begin(9600);
  //start hardware serial on pins 18/19
  U1init(9600);
  // setup the ADC
  adc_init();


  //start gyro
   Wire.begin();
  //configure pins for input or output
  //GPIO red/green lights battery ADC and Flight COntroller on/off
    // setup the pins for ADC battery voltage lights 51 RED 53 GREEN 
  pinner(adcRed,'o');
  pinner(adcGreen,'o');
    //pins for flight controller on/off 28(PA6) GREEN 36(PC1) RED
   pinner(fON, 'o');
   pinner(fOFF, 'o');
   //analog pin 1 input for ADC
   pinner(adcPin, 'i');
  //ESC outputs
  pinner(moPin1,'o'); //Motor 1 Front Left
  pinner(moPin2,'o');//Motor 2 Front Riger
  pinner(moPin3,'o');//Motor 3 Back Left
  pinner(moPin4,'o');//Motor 4 Back Right
 //switch input pin
   pinner(swchpin,'i');//Motor 1 Front Left
  //Reciever inputs
  pinner(rePin1,'i');//Motor 1 Front Left
  pinner(rePin2,'i');//Motor 2 Front Right
  pinner(rePin3,'i');//Motor 3 Back Left
  pinner(rePin4,'i');//Motor 4 Back Right
  //clear receiver variables
 state_CH_1 = 0;
 state_CH_2 = 0;
 state_CH_3 = 0;
 state_CH_4 = 0;
  state_CH_6 = 0;
   // initialize Timer2 to trigger an interrupt every 1 millisecond
  // setup the timer control registers
   noInterrupts ();
  *myTCCR2A &= 0x00;
  *myTCCR2B |= 0X01; //set prescalar 
  *myTIMSK2 |= 0b0000001; //turn on interupts

  interrupts(); // enable interrupts

  //enable interupts for reciver input wave calculation
 *myPCICR |= 0b00000001 ; //set register 0 to 1 to enable interupts *myPCICR
 *myPCMSK0 |= 0b11111100 ;   //set register 7,6,5,4 to 1 to enable interupts pins 13,12,12,10 respectively
//gyro setup
byte status = mpu.begin();
   Serial.print(F("MPU6050 status: "));
   Serial.println(status);
   while (status != 0) { } // stop everything if could not connect to MPU6050
   gyroTimeSet = gTime();
   Serial.println(F("Calculating offsets, do not move MPU6050"));
   //while(gyroTimeSet < gTime() - 1000000){ 

  
   mpu.calcOffsets(); // gyro and accelero
//}
   Serial.println("Done!\n");
//esc setup

ESC_FL.attach(5,1000,2000); 
ESC_FR.attach(2,1000,2000); 
ESC_BL.attach(3,1000,2000); 
ESC_BR.attach(4,1000,2000); 
}


///////////////////////////////MAIN LOOP/////////////////////////////////////////////


void loop() {
  //on/off button 

  //if switch is turned off stop program
  if(wave_CH_6 <= 1500){

 
    //turn off green light turn on red
  *port_a &= ~PX6;
   *port_c |= PX1;

 
  }
  //if switch is turned on run program
  else if(wave_CH_6 > 1500)
  {
   //turn on green light turn off red
  *port_c &= ~PX1;
   *port_a |= PX6;
     gyroMPU();
 

 //end button if statement
  }
  noInterrupts();
  esc1 = wave_CH_3;
  esc2 = wave_CH_3;
  esc3 =wave_CH_3;
  esc4 = wave_CH_3;
ESC_FL.writeMicroseconds(esc1);
ESC_FR.writeMicroseconds(esc2);
ESC_BL.writeMicroseconds(wave_CH_3);
ESC_BR.writeMicroseconds(wave_CH_3);
interrupts();

  // get the reading from the ADC
  unsigned int adc_reading = adc_read(7);
  // If the ADC reading is less than 700, turn off green led turn on red
  if(adc_reading < 700)
  {
    //28(PA6) GREEN 36(PC1) RED
  *port_b &= ~PX0;
   *port_b |= PX2;
  }
  // If the ADC reading is greater than or equal to 700, turn on green led turn off red
  else
  {
  *port_b &= ~PX2;
   *port_b |= PX0;
  }

} //end main loop
//FUNCTIONS
//global timer
unsigned long gTime()
{
    // variable to store the elapsed time in microseconds
    noInterrupts (); // disable interrupts
    timer_micros = timer_overflow_count;
    countmicros = TCNT2;
    if(*myTIFR2 & 0b00000001 && countmicros < 255)
    {
      timer_micros++;
    }
    interrupts(); // enable interrupts
    return ((timer_micros << 8 ) + countmicros)* 8; // calculate elapsed time in microseconds 
}
void gyroMPU()
{
   mpu.update();
 if ((millis() - timer3) > 1000) { // print data every 10ms
    
 /*
     U1putchar("X : ");
     
     U1putchar(mpu.getAngleX());
     U1putchar("\tY : ");
     U1putchar(mpu.getAngleY());
     U1putchar("\tZ : ");
     U1putchar(mpu.getAngleZ());
     U1putchar('\n');
     timer = millis();
     Serial1.write('hi')
     */
     float xdir = mpu.getAngleX();
         Serial.write("x: ");
       Serial.print(mpu.getAngleX());
       Serial.write('\n');
     Serial.write("y: ");
       Serial.print(mpu.getAngleY());
       Serial.write('\n');
        Serial.write("z: ");
       Serial.print(mpu.getAngleZ());
       Serial.write('\n');

  int num = -1234;  // Signed integer to send
  char str[10];  // Buffer to hold converted string
  sprintf(str, "%d", num);  // Convert integer to string
  
  int len = strlen(str);  // Get length of string
  
  for (int i = 0; i < len; i++) {
    while (!(UCSR1A & (1 << UDRE1)));  // Wait for empty transmit buffer
    UDR1 = str[i];  // Send character
       
   }

 }

}
void recieverInput()
{



}

void ESC_PWM()
{
  noInterrupts (); // disable interrupts
  int timeStart = gTime();

//start wave
while(gTime() - timeStart < wave_CH_3)
{
 
*port_e |= PX4;

}
 timeStart = gTime();
while(gTime() - timeStart < Rest_wave)
{
*port_e &= PX4;
}
//wave_CH_3
interrupts (); // enables interrupts
}

///ISR FUNCTIONS
//mymillis function ISR
ISR(TIMER2_OVF_vect)
{
   // timer_millis += 1; // increment timer variable by 1
   timer_overflow_count++; // increment overflow counter
}

//Reciver interupt wave calculation
ISR(PCINT0_vect)
{
   noInterrupts (); // disable interrupts
 // unsigned long wave_CH_1, wave_CH_2 , wave_CH_3, wave_CH_4;
  
 
 current_time = gTime();
//2 ch1 CH1Rec
//3 ch2 CH2Rec
//6 ch3 CH3Rec
//7 ch4 CH4Rec

  //Channel 1  //pin 10
cur_state_CH_1 = (*pin_b & CH1Rec);
  
//if new state if higher than old state it changed from 0 to 1 start wave
if(cur_state_CH_1 > state_CH_1 )
{
 wtime1 = current_time;
  state_CH_1 = cur_state_CH_1;
}
//if new state if lower than old state it changed from 1 to 0 end wave
else if(cur_state_CH_1 < state_CH_1 )
{
  wave_CH_1 = current_time - wtime1;
  state_CH_1 = cur_state_CH_1;
}


//Channel 2   //pin 11
  cur_state_CH_2 = (*pin_b & CH2Rec);
  
//if new state if higher than old state it changed from 0 to 1 start wave
if(cur_state_CH_2 > state_CH_2 )
{
 wtime2 =current_time;
  state_CH_2 = cur_state_CH_2;
}
//if new state if lower than old state it changed from 1 to 0 end wave
else if(cur_state_CH_2 < state_CH_2 )
{
  wave_CH_2 = current_time - wtime2;
  state_CH_2 = cur_state_CH_2;
}

  //Channel 3  //pin 12
cur_state_CH_3 = (*pin_b & CH3Rec);
  
//if new state if higher than old state it changed from 0 to 1 start wave
if(cur_state_CH_3 > state_CH_3 )
{
 wtime3 = current_time;
  state_CH_3 = cur_state_CH_3;
}
//if new state if lower than old state it changed from 1 to 0 end wave
else if(cur_state_CH_3 < state_CH_3 )
{
  wave_CH_3 = current_time - wtime3;
  state_CH_3 = cur_state_CH_3;
}


//Channel 4  //pin 13
  cur_state_CH_4 = (*pin_b & CH4Rec);
  
//if new state if higher than old state it changed from 0 to 1 start wave
if(cur_state_CH_4 > state_CH_4 )
{
 wtime4 =current_time;
  state_CH_4 = cur_state_CH_4;
}
//if new state if lower than old state it changed from 1 to 0 end wave
else if(cur_state_CH_4 < state_CH_4 )
{
  wave_CH_4 = current_time - wtime4;
  state_CH_4 = cur_state_CH_4;
}
 
//Channel 6  //pin 1
  cur_state_CH_6 = (*pin_b & CH6swch);
  //cur_state_CH_6 = (digitalRead(50));
//if new state if higher than old state it changed from 0 to 1 start wave
if(cur_state_CH_6 > state_CH_6 )
{
 wtime6 = current_time;
  state_CH_6 = cur_state_CH_6;
}
//if new state if lower than old state it changed from 1 to 0 end wave
else if(cur_state_CH_6 < state_CH_6 )
{
  wave_CH_6 = current_time - wtime6;
  state_CH_6 = cur_state_CH_6;
}
 interrupts (); // disable interrupts
}

void U1init(unsigned long U1baud) {
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U1baud - 1);
  *myUCSR1A = 0x20;
  *myUCSR1B = 0x18;
  *myUCSR1C = 0x06;
  *myUBRR1  = tbaud;
}

void U1putchar(unsigned char U1pdata) {
  while((*myUCSR1A & TBE) == 0){};
  *myUDR1 = U1pdata;
}

void adc_init()
{
  // setup the A register
  *my_ADCSRA |= 0b10000000; // set bit   7 to 1 to enable the ADC
  *my_ADCSRA &= 0b11011111; // clear bit 6 to 0 to disable the ADC trigger mode
  *my_ADCSRA &= 0b11110111; // clear bit 5 to 0 to disable the ADC interrupt
  *my_ADCSRA &= 0b11111000; // clear bit 0-2 to 0 to set prescaler selection to slow reading
  // setup the B register
  *my_ADCSRB &= 0b11110111; // clear bit 3 to 0 to reset the channel and gain bits
  *my_ADCSRB &= 0b11111000; // clear bit 2-0 to 0 to set free running mode
  // setup the MUX Register
  *my_ADMUX  &= 0b01111111; // clear bit 7 to 0 for AVCC analog reference
  *my_ADMUX  |= 0b01000000; // set bit   6 to 1 for AVCC analog reference
  *my_ADMUX  &= 0b11011111; // clear bit 5 to 0 for right adjust result
  *my_ADMUX  &= 0b11100000; // clear bit 4-0 to 0 to reset the channel and gain bits
}
unsigned int adc_read(unsigned char adc_channel_num)
{
  // clear the channel selection bits (MUX 4:0)
  *my_ADMUX  &= 0b11100000;
  // clear the channel selection bits (MUX 5)
  *my_ADCSRB &= 0b11110111;
  // set the channel number
  if(adc_channel_num > 7)
  {
    // set the channel selection bits, but remove the most significant bit (bit 3)
    adc_channel_num -= 8;
    // set MUX bit 5
    *my_ADCSRB |= 0b00001000;
  }
  // set the channel selection bits
  *my_ADMUX  += adc_channel_num;
  // set bit 6 of ADCSRA to 1 to start a conversion
  *my_ADCSRA |= 0x40;
  // wait for the conversion to complete
  while((*my_ADCSRA & 0x40) != 0);
  // return the result in the ADC data register
  return *my_ADC_DATA;
}
