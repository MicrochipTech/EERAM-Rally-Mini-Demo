# EERAM-Rally-Mini
The demo is supposed to showcase the special capabilities of this part in a game that simulates a “Black Box” recorder function. So that the race outcome can be examined after the fact any number of times. From the beginning of the race, every move by the driver, and the positions of the other cars is recorded 30 times a second into the EERAM which can hold 30 seconds of race time. If it becomes full, the program wraps back to the beginning to form a circular buffer, always marking the last sample taken.
