# EERAM Rally Mini Demo

https://user-images.githubusercontent.com/7294232/145284501-e43a5de2-cd9b-4e7f-be3a-1c69db363a6e.mp4

[Full Video](https://vimeo.com/604094518)

## ABOUT
The demo is supposed to showcase the special capabilities of this part in a game that simulates a “Black Box” recorder function. So that the race outcome can be examined after the fact any number of times. From the beginning of the race, every move by the driver, and the positions of the other cars is recorded 30 times a second into the EERAM which can hold 30 seconds of race time. If it becomes full, the program wraps back to the beginning to form a circular buffer, always marking the last sample taken.

The demo uses an SPI EERAM part, with a density of 64kbits, the  [**48L640**](https://www.microchip.com/wwwproducts/en/48L640). The EERAM is mounted onto a removable PIM board. By removing the board, it gives the customer the clear message that this memory can be disturbed or removed from power at any time, and still retain the data written to it up to that point. The EERAM family includes lower and higher density parts (upwards to 1Mbit), on I2C and SPI serial buses. Only the 64K SPI PIM and 1M Click boards are supported by this demo. By being removable, the PIM board allows for immediate communications and power disturbance, so that the data-saving features of the EERAM can be clearly demonstrated.

EERAM is a standalone SRAM memory with shadow EEPROM backup that retains the contents of the SRAM memory when system power is lost. The EERAM uses a small external capacitor (VCAP on the PIM
board) to provide the energy needed to store the contents of the SRAM onto the EEPROM whenever power is lost. Unlike NVSRAM, no external battery is needed. EERAM offers unlimited erase and write cycles to the SRAM memory and FRAM-like functionality at a fraction of the price.

## Mini Rally Game Board
The board showcases some other Microchip components. This includes the PIC18F47K40 8-bit MCU, and the MCP16252 DC/DC Boost converter. Power is supplied by two AAA batteries which are reverse
polarity protected. Power is controlled by a small slide switch on the back near the batteries. The boost converter ensures that every ounce of juice from the batteries will be available to the game.

Besides the supplied EERAM PIM board socket on the side, there is also a MikroBUS™ (Click board) interface to the back, where the 1Mbit EERAM Click demo board (in production soon) can be plugged in and used instead of the PIM. Future software versions may also support I2C PIM boards, and be able to use the larger memory array, but at this point, using the Click board can only record 64K of data, same as the PIM. The demo will only be supplied with the PIM.

The display used is a 128 x 160 pixel TFT display with LED backlight. The game operation is smooth and clear, taking advantage of the processing power of this 8-bit MCU and of the display resolution and color capabilities. Dimming is controlled by an MCU PWM channel.

Sound is produced by a rear-facing Piezo speaker. We have tried to avoid annoying continuous sounds, but some basic sounds have been added to enhance the demo board experience, such as a sound when the racer hits another car, when the PIM is unplugged or plugged in, and when the race review (instant-replay) mode is selected. Presently, there is no option to disable sound.

## Using the Demo
Power is controlled by a slide switch near the batteries (circled below). Always turn the switch to “0” when not in use to save battery life.

![Demonstration](/Docs/Media/EERAM-Rally-Mini-Demo_back.png)

On Power ON, the screen will splash the Microchip name and logo then instruct the user to hit either the “A” button, to begin a new race, or the “B” button, to review the last race. The EERAM PIM must be plugged in correctly for either of these modes to operate.

The directional buttons are used to steer the red car around the competitor cars. The user can move forward and back, but most of the time just left and right buttons are the best to use.

Just like the red wedge demo, users can continue racing until a crash (the object is not to win but rather to avoid a crash), or until power is turned off or the memory card is unplugged. Afterwards, the user can either begin a new race or review the previous one. After reviewing it once, it pauses and repeats forever, or until a new race is selected. The competitor car pattern is hard coded, so every race offers the same challenge. If you don’t crash while racing, the track pattern will repeat itself after about a minute, but there are some tight spots which are hard to complete without practice.

![Demonstration](/Docs/Media/EERAM-Rally-Mini-Demo.png)

## **Support**
To submit a support ticket request, please contact [Microchip Support](https://microchipsupport.force.com/s/)
