/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F15345
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/
#include <string.h>
#include <stdio.h>
#include "mcc_generated_files/mcc.h"

#define VERSION_DATE "v1.0.0 12-12-23"
#define MAX_COMMAND_LEN 30
char c;

char command[MAX_COMMAND_LEN];

//                   {red, green,  blue, aqua,  pink, sunset, purple, white, 0ff }; 
uint16_t red [] =   {1000,    0,     0,    0,   512,    512,    512,     0,   0}; 
uint16_t green [] = {   0, 1000,     0,   512,  128,    255,      0,     0,   0}; 
uint16_t blue [] =  {   0,    0,  1000,   128,  128,     64,     512,    0,   0}; 
uint16_t white [] = {   0,    0,     0,     0,    0,      0,       0,  1000,  0};

short int MAX_COLORS = 8;
bool BLUETOOTH_MODE = false;
bool  STARTUP_MODE = true;
int count = 0;
void executeCommand( char [] );
void updatePWMs(void);
void setArrayColor(short int);
void setRGBW_Color(uint16_t,uint16_t,uint16_t, uint16_t); 
/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    uint8_t index = 0;
    EUSART1_flushBuffer();

    
    //PWM3_LoadDutyValue(1023);  //white
    __delay_ms(500);
    //PWM3_LoadDutyValue(0);  //white
    
    //short int i=0;
    setRGBW_Color(0,0,1000,0);
    //count = 0;
    while(1) { // main_loop
        
        
 //       BLUETOOTH_MODE = true;

//        setRGBW_Color(0,0,0, 0);
//         __delay_ms(250);
//        setRGBW_Color(0,0,512, 0);
//        __delay_ms(150);
//        setRGBW_Color(0,0,0,0);
//        __delay_ms(150);   
//        setRGBW_Color(0,0,512, 0);
//        __delay_ms(150);
//        setRGBW_Color(0,0,0,0);
//        __delay_ms(150);
//        setRGBW_Color(0,0,512, 0);
//        __delay_ms(150);
//        setRGBW_Color(0,0,0,0);
    
        
//        while(BLUETOOTH_MODE)
//        {   

        c = getch();
        if(c != '\n' && c != '\r')
        {
            command[index++] = c;
            if(index > MAX_COMMAND_LEN)
            {
                index = 0;
            }
        }

        //if(c == '\n')
        if(c == '$')
        {
            command[index] = '\0';
            index = 0;
            printf("received: %s",command);

            executeCommand( command ) ;
        }
            //printf("finished loop\r\n");
//        }
        
//        while(STARTUP_MODE ){
//            if (i> 8 || i<0)
//                i=0;
//            //setRGBW_Color(red[i],green[i],blue[i],white[i]);
//            //setArrayColor(i);
//            count = 0;
//            while ((S1_GetValue() < 1) && (STARTUP_MODE == true ))
//            {   
//                if (count < 1){
//                    i++;
//                    if (i> 8){
//                        i=0;
//                    }
//                    setArrayColor(i);
//                    __delay_ms(250);
//                }
//                if (count > 10000)
//                {
//                    STARTUP_MODE = false;
//                    BLUETOOTH_MODE = true;
//                    return;
//                }
//                count++; 
//            }
//        }
        
        
    } // main loop
}

void setArrayColor(short int index)
{   
//    float red1, blue1, grn1;
//    red1 = ((float)red)/255*1023;
//    grn1 = ((float)green)/255*1023;
//    blue1 = ((float)blue)/255*1023;
    if (index<0)
        index= 0;
    if (index> 8)
        index=0;
    PWM6_LoadDutyValue( red[index]);  //red
    PWM5_LoadDutyValue( green[index]);  // green
    PWM4_LoadDutyValue(blue[index] );  // blue
    PWM3_LoadDutyValue(white[index]);  // white
}

void setRGBW_Color(uint16_t red,uint16_t green,uint16_t blue, uint16_t white)
{   
//    float red1, blue1, grn1;
//    red1 = ((float)red)/255*1023;
//    grn1 = ((float)green)/255*1023;
//    blue1 = ((float)blue)/255*1023;
    
    PWM6_LoadDutyValue( red);  //red
    PWM5_LoadDutyValue( green);  // green
    PWM4_LoadDutyValue(blue );  // blue
    PWM3_LoadDutyValue(white);  // white
}
void executeCommand( char cmd[] )
{
    cmd[strlen(cmd)-1] = '\0';
    
    char *s = cmd+1;
    char *pt;
    
    if (cmd[0] == 'a')
    {   
        uint16_t pwm_nums[] = {0,0,0,0};
        int count = 0;
        pt = strtok (s,",");
        while (pt != NULL) {
            int a = atoi(pt);
            if (a<0 || (a>1023))
                a=0;
            pwm_nums[count++] = (uint16_t)a;
            //printf("%d\n", a);
            pt = strtok (NULL, ",");
            
        }
        PWM6_LoadDutyValue(pwm_nums[0]);  //red
        PWM5_LoadDutyValue(pwm_nums[1]);  // green
        PWM4_LoadDutyValue(pwm_nums[2]);  // blue
        PWM3_LoadDutyValue(pwm_nums[3]);  //white
        
        //printf("received all command");
        return;
          
    }

    
    uint16_t pwm_val;
    int i = atoi(s);
    if (i<0)
        i=0;
    if (i>1023)
        i=1023;
    pwm_val = (uint16_t)i;
    //printf("pwm_val= %d",pwm_val);
    

    if ( pwm_val >1023)  //if number is not in range
        pwm_val = 0;
    
    if (cmd[0] == 'w'){
        PWM3_LoadDutyValue(pwm_val);   //WHITE
        return;
    }
    
    if (cmd[0] == 'b'){
        PWM4_LoadDutyValue(pwm_val);   //BLUE
        return;
    }
    
    if (cmd[0] == 'g'){
        PWM5_LoadDutyValue(pwm_val);   //GREEN
        return;
    }
    
    if (cmd[0] == 'r'){
        PWM6_LoadDutyValue(pwm_val);   //RED
        return;
    }
    
    if (cmd[0] == 'v'){
        printf("version = %s", VERSION_DATE );
        return;
    } 
    if (cmd[0] == 'f'){
        printf("flush buffer received\n");
        return;
    } 
//    if (cmd[0] == 'x'){
//        printf("Leaving Bluetooth Mode\n");
//        STARTUP_MODE= true;
//        BLUETOOTH_MODE = false;
//        return;
//    } 
}



/**
 End of File
*/