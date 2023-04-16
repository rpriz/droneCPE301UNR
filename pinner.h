
//my function to set pin as input/output/input with pullup inabled 
void pinner(int pin, char i_o_p)
{
  //portb pins
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

//port c pins
} //
if(pin == 38 || pin == 18 || pin == 10 || 
   pin == 20 || pin == 21 )
{
//define portd Register Pointers
volatile unsigned char* port_c = (unsigned char*)0x28;
volatile unsigned char* ddr_c = (unsigned char*)0x27;
volatile unsigned char* pin_c = (unsigned char*)0x26;
if( i_o_p == 'i')
{
  if(pin == 38)
  {
  *ddr_c &= ~(0x01 << (7));
  *port_c &= ~(0x01 << (7));
  }
  else if (pin >= 20 )
  {
  *ddr_c  &= ~(0x01 << ((pin-21)*-1));
  *port_c &= ~(0x01 << ((pin-21)*-1));
  }
    else if (pin == 10 )
  {
  *ddr_c &= ~(0x01 << (2));
  *port_c &= ~(0x01 << (2));
  }
      else if (pin == 18 )
  {
  *ddr_c &= ~(0x01 << (3));
  *port_c &= ~(0x01 << (3));
  }
}
else if( i_o_p == 'p')
{
  if(pin == 38)
  {
  *ddr_c &= ~(0x01 << (7));
  *port_c |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_c  &= ~(0x01 << ((pin-21)*-1));
  *port_c |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_c &= ~(0x01 << (2));
  *port_c |= 0x01 << (2);
  }
      else if (pin == 18 )
  {
  *ddr_c &= ~(0x01 << (3));
  *port_c |= 0x01 << (3);
  }

}
else if(i_o_p == 'o')
{
   if(pin == 38)
  {
  *ddr_c |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_c |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_c |= 0x01 << (2);
  }
      else if (pin == 18)
  {
  *ddr_c |= 0x01 << (3);
  }
  
}

//port d pins
} //
if(pin == 38 || pin == 18 || pin == 10 || 
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
  else if (pin >= 20 )
  {
  *ddr_d  &= ~(0x01 << ((pin-21)*-1));
  *port_d &= ~(0x01 << ((pin-21)*-1));
  }
    else if (pin == 10 )
  {
  *ddr_d &= ~(0x01 << (2));
  *port_d &= ~(0x01 << (2));
  }
      else if (pin == 18 )
  {
  *ddr_d &= ~(0x01 << (3));
  *port_d &= ~(0x01 << (3));
  }
}
else if( i_o_p == 'p')
{
  if(pin == 38)
  {
  *ddr_d &= ~(0x01 << (7));
  *port_d |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_d  &= ~(0x01 << ((pin-21)*-1));
  *port_d |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_d &= ~(0x01 << (2));
  *port_d |= 0x01 << (2);
  }
      else if (pin == 18 )
  {
  *ddr_d &= ~(0x01 << (3));
  *port_d |= 0x01 << (3);
  }

}
else if(i_o_p == 'o')
{
   if(pin == 38)
  {
  *ddr_d |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_d |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_d |= 0x01 << (2);
  }
      else if (pin == 18)
  {
  *ddr_d |= 0x01 << (3);
  }
  
}
}
//port e pins
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

//port h pins
 //
if(pin == 38 || pin == 18 || pin == 10 || 
   pin == 20 || pin == 21 )
{
//define portd Register Pointers
volatile unsigned char* port_h = (unsigned char*)0x102;
volatile unsigned char* ddr_h = (unsigned char*)0x101;
volatile unsigned char* pin_h = (unsigned char*)0x100;
if( i_o_p == 'i')
{
  if(pin == 38)
  {
  *ddr_h &= ~(0x01 << (7));
  *port_h &= ~(0x01 << (7));
  }
  else if (pin >= 20 )
  {
  *ddr_h  &= ~(0x01 << ((pin-21)*-1));
  *port_h &= ~(0x01 << ((pin-21)*-1));
  }
    else if (pin == 10 )
  {
  *ddr_h &= ~(0x01 << (2));
  *port_h &= ~(0x01 << (2));
  }
      else if (pin == 18 )
  {
  *ddr_h &= ~(0x01 << (3));
  *port_h &= ~(0x01 << (3));
  }
}
else if( i_o_p == 'p')
{
  if(pin == 38)
  {
  *ddr_h &= ~(0x01 << (7));
  *port_h |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_h  &= ~(0x01 << ((pin-21)*-1));
  *port_h |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_h &= ~(0x01 << (2));
  *port_h |= 0x01 << (2);
  }
      else if (pin == 18 )
  {
  *ddr_h &= ~(0x01 << (3));
  *port_h |= 0x01 << (3);
  }

}
else if(i_o_p == 'o')
{
   if(pin == 38)
  {
  *ddr_h |= 0x01 << (7);
  }
else if (pin >= 20 )
  {
  *ddr_h |= 0x01 << ((pin-21)*-1);
  }
    else if (pin == 10 )
  {
  *ddr_h |= 0x01 << (2);
  }
      else if (pin == 18)
  {
  *ddr_h |= 0x01 << (3);
  }
  
}
}
}//function end






  
