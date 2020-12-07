# Marathon Sim, written in CPP !
### Introduction
This is the first project of my second in my ingeeniring degree, this one is about recreating a marathon simulation taking some paramaters and working in real time using **C++** and **SFML**. It is indeed pretty basic yet functionnal and has tons of intersting features.<br/>You can find out how to compile this under [this file](build/Infos.md).

### Features
1. [Reading files in order to get and the runners and the marathon specs](https://github.com/TT-txt/MarthonSimCpp#reading-files-in-order-to-get-and-the-runners-and-the-marathon-specs)
2. [RNG?](#rng)
3. [Which parameters are changing the runner's speed ?]()
4. [Export of the results](https://github.com/TT-txt/MarthonSimCpp#-which-parameters-are-changing-the-runners-speed--)
5. [Side notes](https://github.com/TT-txt/MarthonSimCpp#-side-notes-)

### Reading files in order to get and the runners and the marathon specs
You can use your own data in order to make the race: all you need to do is go under [userFiles/participants.txt]("userFiles/participants.txt). In this place you are going to see a txt file constructed like this:</br>
```
{     
  name,     
  weight,     
  height,     
  shoes weight,   
  last marathon speed,    
  number of weeks of training  
}   
```
Note that the weight must be set in kilograms, between 45 and 120kg, also the height must set in meters and be between 1.30 and 1.75. The shoes weight is set in grams, between 100 and 300g, the last marathon speed is set in km/h and must be between 7 and 20km/h. Finaly, the number of weeks a float between 8 and 16.
Then you can do the same and edit this other file located under [userFiles/etapes.txt](userFiles/etapes.txt) in order to create your own marathon. The file is constructed like this:<br/>
```
{
  slope,
  range,
  direction,
  Has supply
}
```
Note that here, the slope is a float (representing the %), it is negative when going down, and positive when going up. The range **MUST BE CUMULATED**: for exemple step 1 range is 1.2km, then the distance between the second and thrid checkpoint 2km, then the range of the 2nd step is 2 + 1.2 = 3.2km; it is also set in kilometers. Then we have the direction, which is a float between 0 and 360 representing in which direction the step, check under [libs/coureur.cpp](libs/coureur.cpp) in order to understand that. Finaly `Has supply` must be set as a boolean, which indicate if the runner can drink from this place.<br/>

### RNG?
Luckely enough, you can also choose to generate a random one, and also random runners, all you have to do is to go under [src/main.cpp](src/main.cpp) and edit the line 7 and 8. If you set the line 7 to true, the programm will use the file you made under [userFiles/participants.txt](userFiles/participants.txt), else if it set to false it will generate the number of random runners, the number can be changed on line 46, it is the first arg. You can do the same for the steps: line 8 is defined the bool and to modify how many for the generation, it is on line 52, first arg in function call.

### Which parameters are changing the runner's speed ?
Those parameters are changing the runner speed: <br/>
* His shoes's weight,
* The slope of the step he is in,
* The wind speed and wind direction (of any kind),
* The number of weeks of training,
* His hydratation
Note that the hydratation is the only thing that can make a runner give up in the race, the calculation of this are made following what my teacher asked me to do, you can see those under [libs/coureur.cpp](libs/coureur.cpp)

### Export of the results 
Because we want to be able to check how went the race, we can export result if the const set on line 9 in [src/main.cpp](src/main.cpp) is set to true, results will be exported under [userFiles/resultats.txt](userFiles/resultats.txt)

### Side notes
It is possible that using the random generation, some races cannot be finished, I don't know if i will ever be able to fix that.</br>
This project require SFML and C++ std 17.<br/>
Wehenver a runner is passing a checkpoint, the rectangle representing where he is in the race is changing color. <br/>
In order to accelerate time, you can modify the / 3600 under [src/main.cpp](src/main.cpp) on line 150 and 152, putting a smaller number will make time passt faster. <br/>

