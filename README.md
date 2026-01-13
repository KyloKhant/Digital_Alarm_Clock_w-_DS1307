Digital Alarm Clock w/ DS1307RTC

This project implements a digital alarm clock with snooze functionality using an Arduino, DS1307 real-time clock (RTC), a 4-digit 7-segment display, push buttons, and a buzzer. The system displays the current time in 24-hour format and triggers an alarm based on predefined conditions in the code.


Overview:

DS1307RTC - maintains accurate date and time using an internal 32.768 kHz crystal oscillator and battery backup. The time is initially set during programming and continues running independently of the Arduino.

4-Digit 7-Segment Display - display the time in HH.MM format

Buttons - 1st (closer to the display) is "STOP" button
          2nd (closer to DS1307) is "SNOOZE" button


Alarm Logic:

The clock operates in 24-hour format.

When the set alarm time is reached, the buzzer is activated.

If the stop button is pressed, the alarm terminates and reset to ring again after passing midnight.

However,If SNOOZE is pressed, the alarm pauses and reactivates after a predefined snooze interval (1min in video).

If no button is pressed, the alarm automatically stops after a set duration(1min in video) and reactivates after the snooze interval.(1min in video)

This cycle continues until STOP is pressed.


Components used:
- 4-digit 7-segment display
- DS1307RTC
- push-buttons
- Arduino
- Buzzer


Limitations:

Cannot set a desired alarm time externally, only through the code. 

Neither display the Date nor indicate which is STOP or SNOOZE clearly.

Improvements:

Planning to implement OLED display and 4x4 KeyPad to display Date and allow alarm to be set externally, respectively.

Using LED to indicate when Stop is pressed. 
