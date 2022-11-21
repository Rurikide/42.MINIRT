# 42.MINIRT
*Coding a mini Raytracer in C with [JustineBadia](https://github.com/justinebadia)*

## *OVERVIEW*

<p align="left" >
<img width="500" alt="image" src="https://user-images.githubusercontent.com/79991066/203154580-15f5fe50-de7f-457f-ae8e-4b94f2e47977.png">
</p>


<details><summary> More examples with Phong reflection </summary>


<img width="905" alt="Capture d’écran, le 2022-11-16 à 18 14 52" src="https://user-images.githubusercontent.com/79991066/202315056-e18063e5-3a15-4387-9d2b-ad1d09305e41.png">

<img width="905" alt="Capture d’écran, le 2022-11-16 à 18 23 35" src="https://user-images.githubusercontent.com/79991066/202316403-cf7046fb-16d6-461d-86f5-cbf0663b2485.png">

<img width="933" alt="Capture d’écran, le 2022-11-16 à 18 25 38" src="https://user-images.githubusercontent.com/79991066/202316654-8bb95425-33c0-4183-a46d-33f2d9f5a51f.png">
</details>


### How to ? 
Clone the repo :
```
git clone https://github.com/Rurikide/42.MINIRT.git
```

Do `make`and then run :
```
./miniRT /rt_files/file.rt
```

### Let's play!

| Key |  |
| :-------------: | :------------- |
| left click on the object | select the object |
| right click anywhere | unselect the object  |
| [L] | select the light |
|[W][S] | front/back translation of the selected object, if nothing is selected it applies to the camera|
|[A][D] | left/right translation of the selected object, if nothing is selected it applies to the camera|
|[R][T] | up/down translation of the selected object, if nothing is selected it applies to the camera|
|wheel| to change the diameter of a **cylinder or a sphere**, if selected|
|[+][-]| **only for cylinders** - to change its height|
|[X][Y][Z]| choose a rotation axis after selecting an object|
|[<][>]| move the object along the chosen axis|

