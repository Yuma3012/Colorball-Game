# Colorball Game

Color Ball Game runs on Windows with GUI

# DEMO

"hoge"の魅力が直感的に伝えわるデモ動画や図解を載せる

# Features

"hoge"のセールスポイントや差別化などを説明する

# Requirement



* OS:Windows 11
* Visual studio

# Installation

(1) Select "Desktop Development with C++" to install and start Visual Studio.  
(2)Create a new project, and after selecting "Windows Desktop Wizard", create a folder in any location and select "Desktop Application" and "Empty Project".  
(3)Place Report.cpp in the header file and def.h and mlib.h in the source file.  
(4)Click "Local Windows Debugger" to start the game. When you exit, click the stop button on the right side of "Local Windows Debugger" instead of the x button on the tab.  

# Usage

■ Operation 
[Click <next> button]: Display new ball 
[A]: Move ball left 
[D]: Move ball right 
[S]: Drop ball 
━━━━━━━━━━━━━━━━━━━━ 
■ How to play the game ＜Evolution order of balls and score table＞ - Press <next> button to display the ball. Press <next> button to display the ball. The newly displayed balls are randomly selected from the three smallest (pink, light blue, yellow).
Score pink light blue + 3 yellow + 5 blue + 10 red + 20 black + 30 green + 40 pink + 55 light blue + 3 (...and the following loop)
The ball is moved to the left or right and dropped at the desired position. When balls of different colors collide, they reflect. When balls of the same color collide, the two balls disappear and a larger ball is created, and the score is added. When the <next> button is pressed again, another ball is displayed. The game is over and the game is reset when either ball hits the red dead line at the top of the screen after falling.

# Note

注意点などがあれば書く

# Author

作成情報を列挙する

* 作成者
* 所属
* E-mail

