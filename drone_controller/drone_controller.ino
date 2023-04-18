//Drone Flight controller
//Coded By: Roger Pzybyla and Nick K
//CPE 301 Final Project

//Global Variables
  //global timer
  volatile unsigned long timer_millis = 0; // timer variable to store the elapsed time in milliseconds
  unsigned long timer_overflow_count = 0;  // variable to store the number of times the timer overflows
  volatile unsigned char *myTCCR2A = (unsigned char *) 0xB0;
  volatile unsigned char *myTCCR2B = (unsigned char *) 0xB1;
  volatile unsigned char *myTCTNT2 = (unsigned char *) 0xB2;
  volatile unsigned char *myTIMSK2 = (unsigned char *) 0x70;
 

void setup() {
  //start serial for testing
  Serial. begin(9600);

    // initialize Timer5 to trigger an interrupt every 1 millisecond
  // setup the timer control registers
   noInterrupts ();
  *myTCCR2A &= 0x00;
  *myTCCR2B |= 0X03; //set prescalar to 64
  *myTIMSK2 |= 0b0000001; //turn on interupts
  
  interrupts(); // enable interrupts


}

void loop() {
  // put your main code here, to run repeatedly:
//testing gTime
delay(1000);
Serial. println(gTime());
Serial. print("milli:");
Serial. println( millis());
//Serial. print("over");
//Serial. println( timer_overflow_count);
//Serial. print("timerr");
//Serial. println( timer_millis);
}

//FUNCTIONS
//global timer
unsigned long gTime()
{
    // variable to store the elapsed time in milliseconds
    noInterrupts (); // disable interrupts
    
    interrupts(); // enable interrupts
    return (timer_millis * 16.378); // calculate elapsed time in milliseconds
}
///ISR FUNCTIONS
//mymillis function ISR
ISR(TIMER2_OVF_vect)
{
    timer_millis += 1; // increment timer variable by 1
   timer_overflow_count++; // increment overflow counter
}