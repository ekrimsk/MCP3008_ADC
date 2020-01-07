
#include <SPI.h>


#define BIT0HI 0b00000001
#define BIT1HI 0b00000010
#define DIFF   0b00001000
#define ADC_SELECT 10 

void adc_init()
{
  // Establish chip select pin 
  pinMode(ADC_SELECT, OUTPUT); 
  digitalWrite(ADC_SELECT, HIGH);   // Idle high 

  SPI.begin(); 
  SPI.beginTransaction(SPISettings(500000, MSBFIRST, SPI_MODE0));
  SPI.endTransaction();   // should save settings for future use below 
}





uint16_t adc_read(uint8_t channel) // channel 0 to 7 
{
  digitalWrite(ADC_SELECT, LOW);  // to start transfer 

  uint8_t send_byte = (channel | DIFF) << 4; 

  SPI.transfer(BIT0HI);  // kick it off 
  uint16_t high_byte = SPI.transfer(send_byte);
  high_byte &= (BIT0HI | BIT1HI);  // clear 6 MSBs 
  uint8_t low_byte = SPI.transfer(0x00);   // send in anything 

  uint16_t reading = (high_byte << 8) | low_byte; 

  digitalWrite(ADC_SELECT, HIGH);   // back to idle high 
  return reading; 

}
