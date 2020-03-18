Purpose:  
The purpose of this project is to learn how to use ENVIRO from https://github.com/klavinslab/enviro. This is a multiplayer
game where each player can try to drive their car "block" around the track while collecting buffs and debuffs.

Challenges:  
The hardest challenge was deciding what I wanted to do with the game. At first I had created a maze searching robot which worked pretty well but ultimately I threw all that out to tryout some of the recent updates to ENVIRO. I wanted to try multiplayer so I used the examples given in ENVIRO to create my game. The other challenge I encountered was having the view be zoomed onto each player for separate connected clients but I wasn't able to do it.

How to Play:  
First pull this repo and save it to your computer.  
Next run a Docker container with v1.6 (possibly later as well!) of ENVIRO.  
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash  
This should setup the ports and provide easy access to ENVIRO  
Next type the following command into the terminal: "make"  
This will compile the project.  
Next type the following command into the terminal: "esm start"  
This will start the browser connection to the server.  
Then type the following command into the terminal: "enviro"  
Next navigate using a webbrowser to localhost, you should see a screen with the game connected.  
Finally get another friend to join...maybe...I'm not actually certain if it only works as two instances in the same browser
or two different computers.

Sources used:  
Special thanks to Eric Klavins for providing the base upon which this rests. Much of the code of the project comes from examples provided in ENVIRO
https://github.com/klavinslab/enviro  
Additional thanks to the TAs of the class:  
Victor Cannestro  
Rajendra Surendra Hathwar   
