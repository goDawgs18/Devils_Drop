# Devils_Drop
Ride down Devil's Drop if you dare!!! (EEP 520 final Project)

## How to set up the game:
1. First install and run docker on your computer
2. Run the following line of code to set up your environment:
```
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:v1.6 bash
```
3. Type the following lines of code to start the game
```
esm start
make
enviro
```
4. Navigate to you machines local host on a web browser. Suggested to use Google Chrome. 

## Gameflow:
The user will play the role of a thrill seeking skiier going down Devil's Drop. The goal for the player is to avoid the trees as they descend down the hill. As the player gets further and futher down the hills trees will start appear faster. If the skiier crashes into a tree game will end and a feet decended will appear in the terminal window running the game. 

The user can always restart the game simply by click the "Go Down Devil's Drop" button.

## Controls:
- Press the button "Go Down Devil's Drop" to start skiing down the hill
- Press "a" to move the player left
- Press "s" to make the player go straight down the hill or stop horizontal motion
- Press "d" to move the player to the right

