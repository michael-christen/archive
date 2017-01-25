## Timing input signals

#### 1/22/2017 Sunday

Input capture mode from timers in section 15 of the reference manual gives us
most of the information we need.

We'll have to configure interrupts, which might be too complex for the first
section. Let's do it though and figure out the ordering of the book later.

Had to improve uart so we could send the info we needed.

Also implemented stdutils `itoa` functionality; I probably could have just
imported it??

This leads to a good example of a need for software tests. Haven't implemented
yet, but I should set them up soon (after timer)?? I am manually testing
everything, which took awhile and obviously won't be very robust over time.

Future plans: for POC. Setup for loop to count down, then trigger fake update
event and check values, printing out on usart. (Can't trigger fake update event,
only fake interrupt. So we'll have to either connect GPIO pins to it or manually
trip it. Note: setting up `delay(ms)` function would come in hand.


### Instance requirements

We'll be timing 2 different metrics, engine speed and wheel speed. The
requirements for these are a little different:

#### Wheel speed

velocity = circumference / period; v = c / T
v_max = 200 mph = 3520 in / s
v_min = 1 mph = 17.6 in / s
c < pi * 24 in. (being generous)
T = v / c

T_min = 0.02142 s = 21.42 ms
T_max = 4,284 ms or inf.


#### Engine speed

f = 1/T; T = 1/f
f_max = 10,000 RPM or 10/60 KHZ
f_min = 100 RPM or 100/60 Hz
T_min = 6ms
T_max = 600ms


#### 1/24/2017 Tuesday

To test out input capture we're going to need a reliable delay function. Let's
borrow the implementation from the main demo whose architecture follows:
* Get RCC HCLK_Frequency
* Configure systick as that frequency / 1000
* Delay function sets global variable then waits for it to reach 0
* In SysTick_Handler call function that decrements that global variable


We can test it out by setting up a script to wait for serial transmissions and
printing out the time difference. To be precise we'd setup an oscope on GPIO
pins, but this should suffice.

HCLK_Frequency begins at 48MHz, doesn't matter (duh!), just divide by 1000 and
we'll be at ms.

The actual spread recorded using our script doesn't look great, but in the right
ballpark. I've recorded the results in a spreadsheet. To improve this in the
future we could use GPIO instead of UART. To improve the actual spread, getting
the actual clock value and using an external oscillator would probably do the
job.
