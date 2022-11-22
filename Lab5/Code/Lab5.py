# -*- coding: UTF-8 -*-
import Jetson.GPIO as GPIO
import time

#光敏電阻        #TX2腳位 mcp3008 datasheet
SPICLK = 11     #23 mcp3008 CLK
SPIMISO = 9     #21 mcp3008 Dout
SPIMOSI = 10    #19 mcp3008 Din 
SPICS = 8       #24 mcp3008 Chip Select/Shutdown input
output_pin = 7
#led腳位
LED_out1 = 17   #11
LED_out2 = 27   #13

photo_ch = 0

#init
def init():
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(SPIMOSI,GPIO.OUT)
    GPIO.setup(SPIMISO,GPIO.IN)
    GPIO.setup(SPICLK,GPIO.OUT)
    GPIO.setup(SPICS,GPIO.OUT)
    GPIO.setup(LED_out1,GPIO.OUT)
    GPIO.setup(LED_out2,GPIO.OUT)

def readadc(adcnum,clockpin,mosipin,misopin,cspin):
    if((adcnum>7) or (adcnum<0)):
        return -1
    GPIO.output(cspin, True)
    GPIO.output(clockpin, False)
    GPIO.output(cspin, False)
    
    commandout = adcnum
    commandout |= 0x18
    commandout <<= 3
    for i in range(5):
        if(commandout & 0x80):
            GPIO.output(mosipin, True)
        else:
            GPIO.output(mosipin, False)

        commandout <<= 1
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)

    # adcout = spi.xfer2([1,(8+adcnum)<<4,0])
    # adcToValue = ((adcout[1]&3)<<8) + adcout[2]
    adcout = 0
    for i in range(12):
        GPIO.output(clockpin, True)
        GPIO.output(clockpin, False)
        adcout <<= 1
        if(GPIO.input(misopin)):
            adcout |= 0x1
    
    GPIO.output(cspin, True)

    adcout >>= 1

    return adcout


def main():
    init()
    try:
        while True:
            adc_value = readadc(photo_ch,SPICLK,SPIMOSI,SPIMISO,SPICS)
            print("Photoresistor's value:{}".format(adc_value))#光敏電阻數值

            #以下code不確定要上TX2執行後在小小修改用上面那個adc_value判定
            if(adc_value <= 100):       
                GPIO.output(LED_out1,True)
                GPIO.output(LED_out2,True)
                print("LED1 is ON \t LED2 is ON")
            elif(adc_value <= 800):
                GPIO.output(LED_out1,True)
                GPIO.output(LED_out2,False)
                print("LED1 is ON \t LED2 is OFF")
            else:
                GPIO.output(LED_out1,False)
                GPIO.output(LED_out2,False)
                print("LED1 is OFF \t LED2 is OFF")
            #以上code不確定要上TX2執行後在小小修改用上面那個adc_value判定
            
            time.sleep(1)
    finally:
        GPIO.cleanup()

if __name__ == '__main__':
    main()






