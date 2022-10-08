# THIS PROGRAM ONLY WORKS WITH LINUX MACHINES WITH THE BASH KERNEL 

# Termpaint
Alright, so I made this application because I really like terminal/kernel text editors and instead of making just another text editor, I decided to make a painting editor!  Compile with ```g++ -std=c++20```.  It's your job to move this file to ```/usr/bin```, not mine.  Also, you can access saved files by typing in the filepath of termpaint as well as the filepath of the paint file. Example: ```termpaint  /home/user/Desktop/paint.sdpiff```

## Usage:
### Colors:
Space bar  :  Reset square <br/>
1 key  :  Paint white<br/>
2 key  :  Paint red<br/>
3 key  :  Paint orange<br/>
4 key  :  Paint yellow<br/>
5 key  :  Paint green<br/>
6 key  :  Paint cyan<br/>
7 key  :  Paint blue<br/>
8 key  :  paint purple<br/>
Pressing shift and a color at the same same will paint a lighter version of that color except for orange and yellow
### Other Stuff
W key  :  Change Y position on canvas up by one<br/>
A key  :  Change X position on canvas left by one<br/>
S key  :  Change Y position on canvas down by one<br/>
D key  :  Change X position on canvas right by one<br/>
0 key  :  Save file<br/>
; key  :  Resize canvas<br/>
### Have a good day/night
PS: If the colors don't work, that means your software does not support ANSI codes
