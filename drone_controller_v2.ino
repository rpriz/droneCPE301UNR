//Drone Flight controller
//Coded By: Roger Pzybyla and Nick K
//CPE 301 Final Project

//include files
#include "pinner.h"

//masks
#define CH1Rec 0x10  //pin 10
#define CH2Rec 0x20  //pin 11
#define CH3Rec 0x40  //pin 12
#define CH4Rec 0x80   //pin 13  
//Global Variables

//masks

//test var

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

  //variables for wave calculation 
  unsigned long wave_CH_1, wave_CH_2 , wave_CH_3, wave_CH_4;
  int state_CH_1, state_CH_2, state_CH_3, state_CH_4;
  int cur_state_CH_1, cur_state_CH_2, cur_state_CH_3, cur_state_CH_4; 
  unsigned long wtime1, wtime2, wtime3, wtime4;
//port B

//Port D

//Port C

//Port E pins 2 / 3
//port e output 
volatile unsigned char* port_e = (unsigned char*)0x2E; //pins 2/3 use registers 4/5 respectively
volatile unsigned char* ddr_e = (unsigned char*)0x2D; //pins 2/3 use registers 4/5 respectively
volatile unsigned char* pin_e = (unsigned char*)0x2C; //pins 2/3 use registers 4/5 respectively
volatile unsigned char* port_h = (unsigned char*)0x102;  // pins 6/7 use  registers 3/4  respectively

volatile unsigned char* pin_b = (unsigned char*)0x23;
//Port H

//input pins
  char rePin1 = '10';//channel 1
  char rePin2 = '11';//Channel 2
  char rePin3 = '12';//Channel 3 
  char rePin4 = '13';//Channel 4 

//output pins
  char moPin1 = '13'; //Motor 1 Front Left
  char moPin2 = '12'; //Motor 2 Front Riger
  char moPin3 = '11'; //Motor 3 Back Left
  char moPin4 = '10'; //Motor 4 Back Right

void setup() {
  //start serial for testing
  Serial. begin(9600);
  //configure pins for input or output
  //ESC outputs
  pinner(moPin1,'o'); //Motor 1 Front Left
  pinner(moPin2,'o');//Motor 2 Front Riger
  pinner(moPin3,'o');//Motor 3 Back Left
  pinner(moPin4,'o');//Motor 4 Back Right

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
   // initialize Timer2 to trigger an interrupt every 1 millisecond
  // setup the timer control registers
   noInterrupts ();
  *myTCCR2A &= 0x00;
  *myTCCR2B |= 0X01; //set prescalar 
  *myTIMSK2 |= 0b0000001; //turn on interupts

  interrupts(); // enable interrupts

  //enable interupts for reciver input wave calculation
 *myPCICR |= 0b00000001 ; //set register 0 to 1 to enable interupts *myPCICR
 *myPCMSK0 |= 0b11110000 ;   //set register 7,6,5,4 to 1 to enable interupts pins 13,12,12,10 respectively



}

void loop() {
  int i = 0;
  
  if(i = 100000)
  {

i=0;
  }
else{
i++;
}

//Serial.println(*pin_b & CH2Rec);
if(wave_CH_4 >0)
{

Serial.println(wave_CH_4);


}


}
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
void recieverInput()
{



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

}












