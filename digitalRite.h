//digitalRite function to replace digitalWrite
//Use digitalRite(pin,output)
//output = 0 for LOW, 1 for HIGH

#ifndef DIGITALRITE_H
#define DIGITALRITE_H

// Define the memory addresses for the GPIO registers on your microcontroller
#define GPIO_BASE_ADDRESS 0x20000000
#define GPIO_PIN_OFFSET 0x04
#define GPIO_SET_OFFSET 0x1C
#define GPIO_CLR_OFFSET 0x28


void digitalRite(int pin, int value);

// Function for digitalRite
void digitalRite(int pin, int value) {
    //memory address for the GPIO register for this pin
    volatile unsigned int* gpio_pin_register = (unsigned int*)(GPIO_BASE_ADDRESS + GPIO_PIN_OFFSET + (pin / 10) * 4);
    
    //bit position for this pin within the GPIO register
    unsigned int bit_position = (pin % 10) * 3;
    
    //memory addresses for the SET and CLR registers
    volatile unsigned int* gpio_set_register = (unsigned int*)(GPIO_BASE_ADDRESS + GPIO_SET_OFFSET);
    volatile unsigned int* gpio_clr_register = (unsigned int*)(GPIO_BASE_ADDRESS + GPIO_CLR_OFFSET);
    
    // Set or clear the appropriate bit within the GPIO register, based on the desired value
    if (value) {
        *gpio_set_register = 1 << pin;
    } else {
        *gpio_clr_register = 1 << pin;
    }
}

#endif  // DIGITALRITE_H
