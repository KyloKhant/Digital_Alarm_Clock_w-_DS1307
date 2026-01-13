Digital Alarm Clock w/ DS1307RTC

This project demonstrates a simple and conventional digital alarm clock with snooze function. Built using Arduino, 7-segment 4 digit display, buzzer and DS1307RTC, it displays the time in 24 hour format.


Overview:

DS1307RTC - a real time clock that can output exact Date, Years, Months and Time(Hour,Minutes,Second) from the computer using its internal oscillator and DS1307 library.

7-segment 4 digit display - display the time in "Hours.Minutes" format

Buttons - 1st (closer to the display) is "STOP" button
          2nd (closer to DS1307) is "SNOOZE" button


Details:

The clock display time in 24 hr format and alarm time is determined in the code. 

Once the set-time is reached, the buzzer will be sound. 

If the stop button is pressed, the alarm terminates and reset to ring again after passing midnight.

However, if the snooze is pressed, the buzzer will stop ringing but after pre-determined snooze time (1min in video), it will ring again. 

When neither is pressed, the alarm will stop after a set-minute (1min in video) and ring again after same minute with snooze time(1min in video)

This cycle continues until STOP is pressed.

Components used:
- 7 segment 4-digit display
- DS1307RTC
- push-buttons
- Arduino
- Buzzer
