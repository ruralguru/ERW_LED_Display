#include <ERW_PCA9685.h>
#include <ERW_LED_Display.h>

#define LED_driver_address B01000000  /* I2C address in Binary for the device with all address pins grounded. */
#define LED_driver_Enable 10          /* Sets the enable pin for controlling the toggle functon from the Arduino
                                      NOTE: If multiple devices are ran with one OE_n control the enable can be omitted from the other constructors,
                                      this will cause odd function if the command is called. */
                                      
#define LED_driver_LED_count 16       /* This is the number of LED's driven by the display. This is used to offset the on off times so that the current draw is cleaned up some. */
#define LED_driver_Max 4095           /* This is used to set LEDs to Max Brightness in the for loop */
#define LED_driver_Half 2047          /* This is used to set LEDs to Half Brightness in the for loop */
#define LED_driver_Sixteenth 255      /* This is used to set LEDs to sixteenth Brightness in the for loop */

uint16_t LED_driver_brightness[16];                                    /* This declaration makes a brightness array the length needed by the function */
uint8_t LED_driver_DriveMode = PCA9685_OUTNE_BIT | PCA9685_INVRT_BIT;  /* Doesnt Include PCA9685_OCH_BIT 
                                                                                               
NOTES: The OUTNE is is B00000011. Enabling OUTNE_BIT puts output into high Z state when OE is high.
       The OUTDRV_BIT decides totem pole or open-drain. A one corresponds to totem pole.
       The INVRT_BIT decides if the logic states are flipped. Set for when sinking current turns LED on.
       THE OCH_BIT decides if the LED changes after the message or after the ACK
       See datasheet page 29 for INVRT and OUTDRV settings.*/
float LED_driver_Frequency = 1000;
uint16_t LED_driver_state;

char test_printable[95] = " !\"\#$%&'()*+,-./0123456789:;<.>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz";
char test_lower[27] = "abcdefghijklmnopqrstuvwxyz";
char test_upper[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char test_int[27] = "0123456789";

ERW_LED_Display BL_230B(Display_18); /* This gets the Alphanumeric Translator to work. */
ERW_PCA9685 LED_driver(LED_driver_address, LED_driver_LED_count, LED_driver_Enable); /* This alows command of the PCA9685 for offloaded LED management. */

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT); //Enable Built in LED.
  digitalWrite(LED_BUILTIN, HIGH); //Turn LED on
  Wire.setClock(1000000); /*Send I2C data at 10x the rate. */
  Serial.begin(9600); /* this can be changed for faster serial communications */

  /**
  * READ================>   NOTE: If SERIAL_DEBUG is defined the Builtin LED will light.
  * READ================>   No further action is taken until the Serial Terminal is opened.
  */

  /* Set up All used LEDs at half duty cycle */
  for (int index = 0; index < LED_driver_LED_count; index++)
  {
    LED_driver_brightness[index] = LED_driver_Sixteenth;
  }
  /* setup the IC as desired using above defines */
  LED_driver.begin(LED_driver_DriveMode);
  LED_driver.PMW_freq(LED_driver_Frequency); 
  LED_driver.set_brightness(LED_driver_brightness); /* For ease of transition from off to on the brightness is stored. */
  LED_driver.toggleIC(); /* turn IC on and off with the Pin */
  for(uint8_t loopIndex = 0; loopIndex <= LED_driver_LED_count; loopIndex++ ) /* this  loop turns the LEDs on in a wave */
  {
    bitSet(LED_driver_state, loopIndex);
    LED_driver.LED_state(LED_driver_state);
    delay(100);
  }
  delay(1000);
  BL_230B.begin_alphanumeric();
}


uint8_t charHolder = 33;
uint32_t testChar_LED_holder = 0xFF;
uint8_t testCharIndex = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(!Serial)   /* Delays serial until connection made */
  {
    //LED_driver_state = (uint16_t)BL_230B.ASCII2AN(test_printable[testCharIndex]);
    //LED_driver_state = (uint16_t)BL_230B.ASCII2AN(test_upper[testCharIndex]);
    LED_driver_state = (uint16_t)BL_230B.ASCII2AN(test_lower[testCharIndex]);
    //LED_driver_state = (uint16_t)BL_230B.ASCII2AN(test_int[testCharIndex]);
    LED_driver.LED_state(LED_driver_state);  
    
    if (testCharIndex >=( ( sizeof(test_lower) / sizeof(test_lower[0]) ) -1 ) )
    {
      testCharIndex = 0;
    }
    else
    {
      testCharIndex++;
    }
      delay(500);
  }
  else
  {
    /* takes in input from the Serial port. outputs to BL-230B via PCA-230B chip */
    int charHolder = Serial.read();
    if( ( charHolder >= 32 ) && ( charHolder <= 126 ) )
    {
      LED_driver_state = (uint16_t)BL_230B.ASCII2AN(charHolder);
      Serial.print("Desired Character: ");
      Serial.write(charHolder);
      Serial.print("\tASCII: ");
      Serial.print(charHolder);
      Serial.print("\tLED Character: ");
      Serial.println(LED_driver_state);
      LED_driver.LED_state(LED_driver_state);
      delay(200);
    }
  }
}
