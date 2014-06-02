#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <string.h>

#define output(directions,pin) (directions |= pin) // set port direction for output
#define input(directions,pin) (directions &= (~pin)) // set port direction for input
#define set(port,pin) (port |= pin) // set port pin
#define clear(port,pin) (port &= (~pin)) // clear port pin
#define pin_test(pins,pin) (pins & pin) // test for port pin
#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set
#define bit_delay_time 100 // bit delay for 9600 with overhead
#define bit_delay() _delay_us(bit_delay_time) // RS232 bit delay
#define half_bit_delay() _delay_us(bit_delay_time/2) // RS232 half bit delay
#define led_delay() _delay_ms(100) // LED flash delay

#define led_port PORTA
#define led_direction DDRA
#define led_pin (1 << PA6)

#define serial_port PORTA
#define serial_direction DDRA
#define serial_pins PINA
#define serial_pin_in (1 << PA7)

int led = A6;
int mA1 = A0;
int mA2 = A1;
int mB1 = A3;
int mB2 = A4;

byte count;

int PWM=50; //This is a very important parameter



static char chr;

void get_char(volatile unsigned char *pins, unsigned char pin, char *rxbyte) {

  *rxbyte = 0;
  while (pin_test(*pins,pin));

  half_bit_delay();
  bit_delay();

  if pin_test(*pins,pin)
    *rxbyte |= (1 << 0);
  else
    *rxbyte |= (0 << 0);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 1);
  else
    *rxbyte |= (0 << 1);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 2);
  else
    *rxbyte |= (0 << 2);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 3);
  else
    *rxbyte |= (0 << 3);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 4);
  else
    *rxbyte |= (0 << 4);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 5);
  else
    *rxbyte |= (0 << 5);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 6);
  else
    *rxbyte |= (0 << 6);
  bit_delay();
  if pin_test(*pins,pin)
    *rxbyte |= (1 << 7);
  else
    *rxbyte |= (0 << 7);

  bit_delay();
  half_bit_delay();
}

void flash() {
  // LED flash delay

  clear(led_port, led_pin);
  led_delay();
  set(led_port, led_pin);
}
void setup() {    
  pinMode(mA1, OUTPUT); 
  pinMode(mA2, OUTPUT); 
  pinMode(mB1, OUTPUT); 
  pinMode(mB2, OUTPUT); 
  pinMode(led, OUTPUT); 

  // set clock divider to /1
  //
  CLKPR = (1 << CLKPCE);
  CLKPR = (0 << CLKPS3) | (0 << CLKPS2) | (0 << CLKPS1) | (0 << CLKPS0);

  set(led_port, led_pin);
  output(led_direction, led_pin);
}
void ApBp() {
  digitalWrite(mA2, LOW);   
  digitalWrite(mB2, LOW);   
  digitalWrite(mA1, HIGH);   
  digitalWrite(mB1, HIGH);   
  for (count = 0;  count < PWM; ++count) {
    digitalWrite(mA1, HIGH);   
    digitalWrite(mB1, HIGH);   
    delayOn();
    digitalWrite(mA1, LOW);   
    digitalWrite(mB1, LOW);   
    delayOff();  
  }
}

void AmBp() {
  digitalWrite(mA1, LOW);   
  digitalWrite(mB2, LOW);   
  digitalWrite(mA2, HIGH);   
  digitalWrite(mB1, HIGH);   
  for (count = 0; count < PWM; ++count) {
    digitalWrite(mA2, HIGH);   
    digitalWrite(mB1, HIGH);   
    delayOn();
    digitalWrite(mA2, LOW);   
    digitalWrite(mB1, LOW);   
    delayOff();  
  }
}

void ApBm() {
  digitalWrite(mA2, LOW);   
  digitalWrite(mB1, LOW);   
  digitalWrite(mA1, HIGH);   
  digitalWrite(mB2, HIGH);   
  for (count = 0; count < PWM; ++count) {
    digitalWrite(mA1, HIGH);   
    digitalWrite(mB2, HIGH);   
    delayOn();
    digitalWrite(mA1, LOW);   
    digitalWrite(mB2, LOW);   
    delayOff();
  }
}

void AmBm() {
  digitalWrite(mA1, LOW);   
  digitalWrite(mB1, LOW);   
  digitalWrite(mA2, HIGH);   
  digitalWrite(mB2, HIGH);
  for (count = 0; count < PWM; ++count) {
    digitalWrite(mA2, HIGH);   
    digitalWrite(mB2, HIGH);   
    delayOn();
    digitalWrite(mA2, LOW);   
    digitalWrite(mB2, LOW);   
    delayOff();
  }
}

void step_cw() {
  ApBp();
  AmBp();
  AmBm();
  ApBm();
}


void step_ccw() {
  ApBm();
  AmBm();
  AmBp();
  ApBp();
}


void delayOff(){
  delayMicroseconds(5);
  //delayMicroseconds(5);

}

void delayOn(){
  delayMicroseconds(20);
  // delayMicroseconds(25);

}
//#define stepper "A"
void loop() {

 

  get_char(&serial_pins, serial_pin_in, &chr);
  switch (chr) {
  case '5':
    step_cw();
    delay(10);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      
    break;
           
  case '6':
    step_ccw();
    delay(10);
    break; 
  }
}



// if nothing else matches, do the default
// default is optional

//flash();
//    if (chr == '5') {
//      //
//      //














