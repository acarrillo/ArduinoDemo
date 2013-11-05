import serial
import curses

ser=serial.Serial('/dev/tty.usbmodem411')
stdscr = curses.initscr()
stdscr.keypad(1)
stdscr.nodelay(1)
stdscr.leaveok(1)
curses.noecho()
curses.cbreak()

drive = False

while 1:
    if stdscr.getch()==ord('q'): # Quit
        break;
    elif stdscr.getch()==ord('OD'): # Left arrow key
        ser.write("1") # Left
    elif stdscr.getch()==ord('OC'): # Right arrow key
        ser.write("2") # Right
    elif stdscr.getch()==ord('OA'): # Up arrow key
        ser.write("3") # Straight
    elif stdscr.getch()==ord(' '): # Spacebar
        ser.write("4") if not drive else ser.write("5") # Start or Stop
        drive = not drive
    stdscr.refresh()

curses.nocbreak(); stdscr.keypad(0); curses.echo()
curses.endwin()
