import serial
import curses
import time

ser=serial.Serial('/dev/tty.usbmodem621')
stdscr = curses.initscr()
stdscr.keypad(1)
stdscr.nodelay(1)
stdscr.leaveok(1)
curses.noecho()
curses.cbreak()

drive = False

while 1:
    char = stdscr.getch()
    if char==ord('q'): # Quit
        break;
    elif char==curses.KEY_LEFT: # Left arrow key
        ser.write("1") # Left
    elif char==curses.KEY_RIGHT: # Right arrow key
        ser.write("2") # Right
    elif char==curses.KEY_UP: # Up arrow key
        ser.write("3") # Straight
    elif char==ord(' '): # Spacebar
        ser.write("4") if not drive else ser.write("5") # Start or Stop
        drive = not drive

    stdscr.refresh()
    time.sleep(.1)

curses.nocbreak(); stdscr.keypad(0); curses.echo()
curses.endwin()
