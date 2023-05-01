#include <SoftwareSerial.h>
//#include <pinner.h>

SoftwareSerial mySerial(10, 11); // RX, TX
#define RDA 0x80
#define TBE 0x20  
volatile unsigned char *myUCSR0A = (unsigned char *)0x00C0;
volatile unsigned char *myUCSR0B = (unsigned char *)0x00C1;
volatile unsigned char *myUCSR0C = (unsigned char *)0x00C2;
volatile unsigned int  *myUBRR0  = (unsigned int *) 0x00C4;
volatile unsigned char *myUDR0   = (unsigned char *)0x00C6;
volatile unsigned int s = 1;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() { // run over and over
  while (s=1) {
  if (mySerial.available()) {
     U0putchar(mySerial.read());
  }
  if (U0kbhit()==0) {
    if (s=1){
    mySerial.write(U0getchar());
    s=0;
    }
  }
}
}
void U0init(unsigned long U0baud)
{
 unsigned long FCPU = 16000000;
 unsigned int tbaud;
 tbaud = (FCPU / 16 / U0baud - 1);
 *myUCSR0A = 0x20;
 *myUCSR0B = 0x18;
 *myUCSR0C = 0x06;
 *myUBRR0  = tbaud;
}
void U0putchar(unsigned char U0pdata)
{
while((*myUCSR0A & TBE) == 0){};
  *myUDR0 = U0pdata;
}
unsigned char U0getchar()
{
return *myUDR0;
}
unsigned char U0kbhit()
{
return *myUCSR0A & RDA;
}
