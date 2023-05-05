
//my function to set pin as input/output/input with pullup inabled 
//analog pins must be prefixed by 10 i.e. analog pin 1 is 101
void pinner(int pin, char i_o_p)
{
  //porta pins

if(pin == 22 || pin == 23 || pin == 24 || 
   pin == 25 || pin == 26 || pin == 27 || 
   pin == 28 || pin == 29 )
{
//define porta Register Pointers 
volatile unsigned char* port_a = (unsigned char*)0x22;
volatile unsigned char* ddr_a = (unsigned char*)0x21;
volatile unsigned char* pin_a = (unsigned char*)0x20;

if( i_o_p == 'i')
{
  *ddr_a &= ~(0x01 << (pin-22));
  *port_a &= ~(0x01 << (pin-22));
 
}
else if( i_o_p == 'p')
{
 
  *ddr_a &= ~(0x01 << (pin-22));
  *port_a |= 0x01 << (pin-22);

}
else if(i_o_p == 'o')
{
   
  *ddr_a |= 0x01 << (pin-22);
 
}
}
  //portb pins CHECKED
if(pin == 13 || pin == 12 || pin == 11 || 
   pin == 10 || pin == 50 || pin == 51 || 
   pin == 52 || pin == 53 )
{
//define portb Register Pointers 
volatile unsigned char* port_b = (unsigned char*)0x25;
volatile unsigned char* ddr_b = (unsigned char*)0x24;
volatile unsigned char* pin_b = (unsigned char*)0x23;

if( i_o_p == 'i')
{
  if(pin <= 13)
  {
  *ddr_b &= ~(0x01 << (pin-6));
  *port_b &= ~(0x01 << (pin-6));
  }
  else
  {
  *ddr_b &= ~(0x01 << ((pin-53)*-1));
  *port_b &= ~(0x01 << ((pin-53)*-1));
  }
}
else if( i_o_p == 'p')
{
  if(pin <= 13)
  {
  *ddr_b &= ~(0x01 << (pin-6));
  *port_b |= 0x01 << (pin-6);
  }
  else 
  {
  *ddr_b &= ~(0x01 << ((pin-53)*-1));
  *port_b |= 0x01 << ((pin-53)*-1);
  }
}
else if(i_o_p == 'o')
{
   if(pin <= 13)
  {
  *ddr_b |= 0x01 << (pin-6);
  }
  else
  {
  *ddr_b |= 0x01 << ((pin-53)*-1);
  }


}

//port c pins CHECKED
} //
if(pin == 30 || pin == 31 || pin == 32 || 
   pin == 33 || pin == 34 || pin == 35 ||
   pin == 36 || pin == 37 )
{
//define portc Register Pointers
volatile unsigned char* port_c = (unsigned char*)0x28;
volatile unsigned char* ddr_c = (unsigned char*)0x27;
volatile unsigned char* pin_c = (unsigned char*)0x26;
if( i_o_p == 'i')
{
  *ddr_c &= ~(0x01 << (((pin-30)*-1)+7));
  *port_c &= ~(0x01 << (((pin-30)*-1)+7));
  
}
else if( i_o_p == 'p')
{

  *ddr_c &= ~(0x01 << (((pin-30)*-1)+7));
  *port_c |= 0x01 << (((pin-30)*-1)+7);
 
}
else if(i_o_p == 'o')
{
 
  *ddr_c |= 0x01 << (((pin-30)*-1)+7);
 
}

//port d pins CHECKED
} //
if(pin == 38 || pin == 18 || pin == 19 || 
   pin == 20 || pin == 21 )
{
//define portd Register Pointers 
volatile unsigned char* port_d = (unsigned char*)0x2B;
volatile unsigned char* ddr_d = (unsigned char*)0x2A;
volatile unsigned char* pin_d = (unsigned char*)0x29;
if( i_o_p == 'i')
{
  if(pin == 38)
  {
  *ddr_d &= ~(0x01 << (7));
  *port_d &= ~(0x01 << (7));
  }
  else if (pin >= 18 )
  {
  *ddr_d  &= ~(0x01 << (((pin-18)*-1)+3));
  *port_d &= ~(0x01 << (((pin-18)*-1)+3));
  }

}
else if( i_o_p == 'p')
{
  if(pin == 38)
  {
  *ddr_d &= ~(0x01 << (7));
  *port_d |= 0x01 << (7);
  }
else if (pin >= 18 )
  {
  *ddr_d  &= ~(0x01 << (((pin-18)*-1)+3));
  *port_d |= 0x01 << (((pin-18)*-1)+3);
  }

}
else if(i_o_p == 'o')
{
   if(pin == 38)
  {
  *ddr_d |= 0x01 << (7);
  }
else if (pin >= 18 )
  {
  *ddr_d |= 0x01 << (((pin-18)*-1)+3);
  }
 
}
}
//port e pins CHECKED
if(pin == 0 || pin == 1 || pin == 2 || 
   pin == 3 || pin == 5  )
{
//define porte Register Pointers
volatile unsigned char* port_e = (unsigned char*)0x2E;
volatile unsigned char* ddr_e = (unsigned char*)0x2D;
volatile unsigned char* pin_e = (unsigned char*)0x2C;

if( i_o_p == 'i')
{
  if(pin == 5)
  {
  *ddr_e &= ~(0x01 << (3));
  *port_e &= ~(0x01 << (3));
  }
  else if(pin >= 2)
  {
  *ddr_e &= ~(0x01 << (pin+2));
  *port_e &= ~(0x01 << (pin+2));
  }
    else 
  {
  *ddr_e &= ~(0x01 << (pin));
  *port_e &= ~(0x01 << (pin));
  }
}
else if( i_o_p == 'p')
{
  if(pin == 5)
  {
  *ddr_e &= ~(0x01 << (3));
  *port_e |= (0x01 << (3));
  }
  else if(pin >= 2)
  {
  *ddr_e &= ~(0x01 << (pin+2));
  *port_e |= 0x01 << (pin+2);
  }
    else 
  {
  *ddr_e &= ~(0x01 << (pin));
  *port_e &= ~(0x01 << (pin));
  }
}
else if(i_o_p == 'o')
{
  if(pin == 5)
  {
  *ddr_e |= (0x01 << (3));
  }
  else if(pin >= 2)
  {
  *ddr_e |= (0x01 << (pin+2));
  }
    else 
  {
  *ddr_e |= (0x01 << (pin));
  }
}

}
//portf
if(pin == 100 || pin == 101 || pin == 102 || 
   pin == 103 || pin == 104 || pin == 105 || 
   pin == 106 || pin == 107 )
{
//define porta Register Pointers 
volatile unsigned char* port_f = (unsigned char*)0x31;
volatile unsigned char* ddr_f = (unsigned char*)0x30;
volatile unsigned char* pin_f = (unsigned char*)0x2F;

if( i_o_p == 'i')
{
  *ddr_f &= ~(0x01 << (pin-100));
  *port_f &= ~(0x01 << (pin-100));
 
}
else if( i_o_p == 'p')
{
 
  *ddr_f &= ~(0x01 << (pin-100));
  *port_f |= 0x01 << (pin-100);

}
else if(i_o_p == 'o')
{
   
  *ddr_f |= 0x01 << (pin-100);
 
}
}

//port h pins CHECKED
 
if(pin == 16 || pin == 17 || pin == 9 || 
   pin == 8 || pin == 7 || pin == 6 )
{
//define porth Register Pointers
volatile unsigned char* port_h = (unsigned char*)0x102;
volatile unsigned char* ddr_h = (unsigned char*)0x101;
volatile unsigned char* pin_h = (unsigned char*)0x100;
if( i_o_p == 'i')
{
  if(pin < 10)
  {
  *ddr_h &= ~(0x01 << (pin -3));
  *port_h &= ~(0x01 << (pin -3));
  }
  else if (pin > 10 )
  {
  *ddr_h  &= ~(0x01 << ((pin-17)*-1));
  *port_h &= ~(0x01 << ((pin-17)*-1));
}
else if( i_o_p == 'p')
{
  if(pin < 10)
  {
  *ddr_h &= ~(0x01 << (pin -3));
  *port_h |= 0x01 << (pin -3);
  }
else if (pin > 10 )
  {
  *ddr_h  &= ~(0x01 << ((pin-17)*-1));
  *port_h |= 0x01 << ((pin-17)*-1);
  }
  
}
else if(i_o_p == 'o')
{
   if(pin < 10 )
  {
  *ddr_h |= 0x01 << (pin -3);
  }
else if (pin > 10 )
  {
  *ddr_h |= 0x01 << ((pin-17)*-1);
  }
   

}
}
//port g
if(pin == 4 || pin == 39 || pin == 40 || 
   pin == 41 )
{
//define porth Register Pointers
volatile unsigned char* port_g = (unsigned char*)0x34;
volatile unsigned char* ddr_g = (unsigned char*)0x33;
volatile unsigned char* pin_g = (unsigned char*)0x32;
if( i_o_p == 'i')
{
  if(pin == 4)
  {
  *ddr_g &= ~(0x01 << (5));
  *port_g &= ~(0x01 << (5));
  }
  else if (pin >= 39 )
  {
  *ddr_g  &= ~(0x01 << ((pin-41)*-1));
  *port_g &= ~(0x01 << ((pin-41)*-1));
  }

  }

else if(i_o_p == 'p')
{
  if(pin == 4)
  {
  *ddr_g &= ~(0x01) << (5);
  *port_g |= 0x01 << (5);
  }
  else if (pin >= 39 )
  {
  *ddr_g &= ~(0x01 << ((pin-41)*-1));
  *port_g |= 0x01 << ((pin-41)*-1);
  }

  else if(i_o_p == 'o')
{
   if(pin == 4)
  {
  *ddr_g |= 0x01 << (5);
  }
else if (pin >= 39 )
  {
  *ddr_g |= 0x01 << ((pin-41)*-1);
  }

}
}
}
}
}//function end






  
