#include "LCD_Test.h"

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);
    if (DEV_Module_Init() != 0)
        Serial.println("GPIO Init Fail!");
    else
        Serial.println("GPIO Init successful!");
    // initialize
    LCD_1IN28_Init(HORIZONTAL);
    DEV_SET_PWM(0);
    LCD_1IN28_Clear(WHITE);
    DEV_SET_PWM(100);
    UDOUBLE Imagesize = LCD_1IN28_HEIGHT * LCD_1IN28_WIDTH * 2;
    UWORD *BlackImage;
    if ((BlackImage = (UWORD *)malloc(Imagesize)) == NULL)
    {
        Serial.println("Failed to apply for black memory...");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage((UBYTE *)BlackImage, LCD_1IN28.WIDTH, LCD_1IN28.HEIGHT, 0, WHITE);
    Paint_SetScale(65);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);
    Paint_Clear(WHITE);

    // /* GUI */
    Serial.println("drawing...\r\n");

    unsigned int tim_count = 0;
    uint16_t result;

    // initialize display
    QMI8658_init();
    CST816S_init(CST816S_Gesture_Mode);
    DEV_KEY_Config(Touch_INT_PIN);
    Serial.println("QMI8658_init\r\n");
    DEV_SET_PWM(100);
    const float conversion_factor = 3.3f / (1 << 12) * 3;
    LCD_1IN28_Display(BlackImage);
    while(true){
 
      // read hart rate
      int value = analogRead(28);
      // print out the value you read:
      Serial.println(value);
      // write values on display
      Paint_Clear(WHITE);
      Paint_DrawNum(120 ,100 , value , &Font20 , 2 ,BLACK , WHITE);
      LCD_1IN28_DisplayWindows(120, 50, 210, 200, BlackImage);
      LCD_1IN28_DisplayWindows(130, 200, 220, 220, BlackImage);
      // 20ms delay
      delay(20);
    }
}

void loop()
{

    DEV_Delay_ms(1000);
}
