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

#### 1/28/2017 Saturday

Let's trigger the input, we'll probably have to connect two pins with a jumper.

Trying to print out the captured input wasn't working (only returning 0's)
adding in a prescaler helped diagnose the issue. We were counting too quickly,
slowing down to uart speeds and grabbing the actual counter value showed that
we were sucessfully resetting the counter when the pin changes. Now we need to
take a look at the status flags and see if any of the CC values are getting set.

Setting up a debug log in main really helped out. Printed out status register
and various capture values along with counter. Saw that CC2 was actually
configured. Now I can setup a test with another GPIO.

#### 1/30/2017 Monday

Cleaned up main and read datasheet and reference manual more to get a better
idea of what was going on. For the development of the input capture code we'll
most likely need to add:
* support for multiple captures
* a way to record that we didn't hit anything, perhaps insert a 0 into the list
    if we went the whole period. This will probably atleast involve adding a
    interrupt handler on the update event.

I'd like to add an automated test, combining an output pin to the trigger input
and calling the delay function and comparing expected values with actual ones.
