# OLED-Wemos-Subcounter
Erics Wemos D1 Mini displaying YouTube Subscriber Count with MAX7219 LED Matrix Displays - Now modified by SpiderMaf to add extra details on the sub miniature OLED displays.

Original Library here https://github.com/squix78/MAX7219LedMatrix but contains no function to rotate for my displays
Brian Lough's library contains rotate: https://github.com/witnessmenow/MAX7219LedMatrix
Brians doesnt work with Wemos D1 mini unless you comment out this line https://github.com/witnessmenow/MAX7219LedMatrix/blob/master/LedMatrix.cpp#L34
Done in the cpp file contained with this sketch
Eric originally followed this tutorial here for the YouTube API info etc: http://www.joeybabcock.me/blog/projects/arduino-esp8266-live-subscriber-display/
Wiring for Wemos D1 Mini:
| Pin On 7219| Pin on Wemos D1 Mini |
| ------- |----------------|
| GND     | G |
| VCC     | 3V3 |
| DIN     | D7 |
| CS      | D4 |
| CLK     | D5 |

This code was branched by SpiderMaf from MKMe’s source code so credit to him and the other original authors above.
Support MKme’s original’s project by picking up the display/board here:
Wemos D1: https://amzn.to/2ACRWRA
LED Matrix: https://amzn.to/2McsuUl

MkMe Youtube Channel  : http://www.youtube.com/mkmeorg
MkMe website   : http://www.mkme.org

SpiderMaf’s Youtube Channel : http://www.youtube.com/SpiderMaf
SpiderMafs Website : https://mattnorman.co.uk

You will need to amend the code in the .ino with your Channel ID, your YouTube API key and the SSID and PW of the Wifi you want this to connect to.

