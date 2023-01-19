# Project_SDL_VF

This is a game in C++ using SDL library
    

<img src="/images/background.png">


## Build
Create a build directory and run cmake and make from there
```bash
    mkdir build
    cd build
    cmake ..
    make
```
## Run
```bash
    ./SDL_project <nb_sheeps> <nb_wolves> <game time (s)>  
```  
You have to set the number of sheeps and wolves you want to play with.  

## Gameplay
* The wolves are controlled by the computer and will try to eat the sheeps. 
<img src="/images/wolf.png" >

* The sheeps are controlled by the computer also and will try to escape the wolves.   
    <img src="/images/sheep.png" >   

* You can control the shepherd with the q, d, z, s keys.  
<img src="/images/shepherd.png" >  
    

* The shepherd dogs move circles around the shepherd, you can control them by __left__ clicking on the screen to select one of them and __right__ clicking in the screen to move them to the selected position.  
<img src="/images/dog.bmp" >  
    
  
The game ends when keep 1 sheeps alives or when the wolves are all dead.  

## Contributors

- [Agustin Bouchon](https://github.com/Joadza)
- [Sabir Mohamed Ben Ali](https://github.com/icare-sh)
- [Anthony Becuwe](https://github.com/Super-huit)
- [Remi Tang](https://github.com/remitang)
