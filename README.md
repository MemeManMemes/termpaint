# THIS PROGRAM ONLY WORKS WITH LINUX MACHINES WITH THE BASH SHELL 

# Termpaint
Alright, so I made this application because I really like terminal/kernel text editors and instead of making just another text editor, I decided to make a painting editor!  Compile with ```g++ termpaint.cpp -std=c++20 -o termpaint```.  It's your job to move this file to ```/usr/bin```, not mine.  Also, you can access saved files by typing in the filepath of termpaint as well as the filepath of the paint file. Example: ```termpaint  /home/user/Desktop/paint.sdpiff```<br/>video: https://www.youtube.com/watch?v=7HlXqYoEGGI&t<br/>
Thanks to r2boyo25 for the ability to move around the canvas with the arrow keys

## Most recent updates
**!!NEWEST!! - Bug fixed where saving with colored text would render a file unreadable<br/>**
Colored text - You can now place text down then color it by switching to color mode<br/>
Code readability and format as well as ability to switch between paint/command and text mode<br/>
Ability to move around canvas with arrow keys<br/>
Better file saving<br/>

## Future update ideas
Colored text ☑<br/>
User-made rectangles/squares ☐<br/>
Windows version ☐<br/>

## Usage:
### Colors:
Backspace Key  :  Reset sector <br/>
1 key  :  Paint white<br/>
2 key  :  Paint red<br/>
3 key  :  Paint orange<br/>
4 key  :  Paint yellow<br/>
5 key  :  Paint green<br/>
6 key  :  Paint cyan<br/>
7 key  :  Paint blue<br/>
8 key  :  paint purple<br/>
Pressing shift and a color at the same same will paint a lighter version of that color except for orange and yellow
### Commands
R Key  :  Reset  canvas
Up arrow key  :  Change Y position on canvas up by one<br/>
Left arrow key  :  Change X position on canvas left by one<br/>
Down arrow key  :  Change Y position on canvas down by one<br/>
Right arrow key  :  Change X position on canvas right by one<br/>
0 key  :  Save file<br/>
; key  :  Resize canvas<br/>
~ key  :  Switch between paint/command mode and typing mode<br/>
### Accepted characters in typing mode
A-Z, a-z, 0-9
### Have a good day/night
PS: If the colors don't work, that means your software does not support ANSI codes
