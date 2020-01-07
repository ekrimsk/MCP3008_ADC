



void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200); 
  Serial.println("Running adc test:"); 

  adc_init();
  delay(100); 

}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t reading_adc = analogRead(0); 
  uint16_t reading_spi = adc_read(0x03); 

  Serial.print("Reading SPI: " );
  Serial.print(5.06 * reading_spi/1023); 
  Serial.print(" Reading ADC: "); 
  Serial.println(5.00*reading_adc/1023); 
  delay(500); 
}
