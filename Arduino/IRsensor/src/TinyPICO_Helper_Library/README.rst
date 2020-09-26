TinyPICO Arduino Helper
=======================

This library adds some helper functions and useful pin assignments to make coding with TinyPICO & Arduino easier

We will be adding this library to the Arduino IDE library manager once we get closer to shipping the TinyPICOs.

TinyPICO Hardare Pin Assingments
--------------------------------
.. code-block:: c++

    // APA102 Dotstar
    #define DOTSTAR_PWR 13
    #define DOTSTAR_DATA 2
    #define DOTSTAR_CLK 12

    // Battery
    #define BAT_CHARGE 34
    #define BAT_VOLTAGE 35
..

Helper functions
----------------
.. code-block:: c++

    // Class constructor
    TinyPICO(); 

    // Get a *rough* estimate of the current battery voltage
    // If the battery is not present, the charge IC will still report it's trying to charge at X voltage
    // so it will still show a voltage.
    float GetBatteryVoltage();

    // Return the current charge state of the battery - we need to read the value multiple times
    // to eliminate false negatives due to the charge IC not knowing the difference between no battery
    // and a full battery not charging - This is why the charge LED flashes
    bool IsChargingBattery();
        
    // Return the internal PICO-D4 temperature in Farenheit
    uint8_t Get_Internal_Temp_F();

    // Return the internal PICO-D4 temperature in Celcius
    float Get_Internal_Temp_C();

    // Power to the on-oard Dotstar is controlled by a PNP transistor, so low is ON and high is OFF
    // We also need to set the Dotstar clock and data pins to be inputs to prevent power leakage when power is off
    // The reason we have power control for the Dotstar is that it has a quiescent current of around 1mA, so we
    // need to be able to cut power to it to minimise power consumption during deep sleep or with general battery powered use
    // to minimse un-needed battery drain
    void DotStar_SetPower( bool state );

    // On-board Dotstar control
    void DotStar_Clear();
    void DotStar_SetBrightness( uint8_t );
    void DotStar_SetPixelColor( uint32_t c );
    void DotStar_SetPixelColor( uint8_t r, uint8_t g, uint8_t b );
    void DotStar_Show( void );
    void DotStar_CycleColor();
    void DotStar_CycleColor( unsigned long wait );		
    void DotStar_CycleColor();
    void DotStar_CycleColor( unsigned long wait );

    // Convert R,G,B values to uint32_t
    uint32_t Color( uint8_t r, uint8_t g, uint8_t b );
..

Example Usage
-------------
.. code-block:: c++

    #include <TinyPICO.h>

    // Interval between internal temperature reads
    unsigned long next_temp_read = 0;   // Next time step in milliseconds 
    uint8_t temp_read_interval = 1000;  // This is in milliseconds

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
..
