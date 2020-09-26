#include <TinyPICO.h>

// Interval between internal temperature reads
unsigned long next_temp_read = 0;   // Next time step in milliseconds 
uint32_t temp_read_interval = 1000;  // This is in milliseconds

// Initialise the TinyPICO library
TinyPICO tp = TinyPICO();

void setup()
{
  // Used for debug output only
  Serial.begin(115200);
}

void loop()
{
  // Cycle the DotStar colour every 25 miliseconds
  tp.DotStar_CycleColor(25);

  // You can set the DotStar colour directly using r,g,b values
  // tp.DotStar_SetPixelColor( 255, 128, 0 );

  // You can set the DotStar colour directly using a uint32_t value
  // tp.DotStar_SetPixelColor( 0xFFC900 );

  // You can aclear the DotStar too
  // tp.DotStar_Clear();

  // To power down the DotStar for deep sleep you call this
  // tp.DotStar_SetPower( false );

  // Print the internal temperature of the PICO-D4
  print_temp();
}

void print_temp()
{
  // We only run the contents of this function every *temp_read_interval* step
  if ( millis() > next_temp_read + temp_read_interval )
  {
    next_temp_read = millis();

    // Grab the temperature in Farenheit
    uint8_t temp_farenheit = tp.Get_Internal_Temp_F();

    // Grab the temperature in Celcius
    float temp_celsius = tp.Get_Internal_Temp_C();

    // Print the temperatures to the output console
    Serial.print("Temp In PICO-D4 ");
    Serial.print(temp_farenheit);
    Serial.print("°F ");
    Serial.print(temp_celsius);
    Serial.println("°C");
  }
}
