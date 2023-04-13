# RayTracingGiVD 2020-21

This repository contains the code developed as a part of the subject of Computer Graphics in Universitat de Barcelona.


## Equip: C02
- Angel Morales Carrasco         NIUB 20150546
- Eric Duque Martin              NIUB 20150443
- Oriol Saguillo Gonzalez        NIUB 20150502
- Maria Isabel Gonzalez Sanchez  NIUB 20221913


### Features
- Fase 1
    - [x] Background amb degradat: todos
   
    - Creació de nous objectes i interseccions (VIRTUALWORLD) 
        - [x] 4.1.a. Mapping de mons virtuals: todos
        - [x] 4.1.b. Hit Triangle: Eric, Oriol
        - [x] 4.1.c. Hit Boundary Object: Eric
        - [x] 4.1.d. Hit Cilindre: Oriol, Maria Isabel, Eric
    - Creació de REAL DATA
        - [x] 4.2.a. Transformacions Translació i Escalat amb gizmos esferes: Eric, Maria Isabel
        - [x] 4.2.b. Pla de terra: Eric, Maria Isabel
        - [x] 4.2.c. Gizmo de Triangle: Eric, Maria Isabel 
        - [x] 4.2.d. Gizmo de Cilindre: Eric, Maria Isabel
        - [x] Noves dades: Eric, Maria Isabel 
       

- Fase 2
    - [x] Antialiasing: Angel
    - [x] Gamma Correction: Angel
    - [x] Blin-Phong: Angel, Oriol
    - [x] Ombres amb objectes opacs: Angel
    - [x] Reflexions: Maria Isabel, Oriol
    - [x] Transparències: Maria Isabel, Angel
    - [x] Visualització amb dades reals: Eric, Maria Isabel
    
    
- Fase 3
    - [x] Texture mapping en el pla: Eric, Angel
    - [x] MaterialTextura: Eric
    - [x] Nova escena de dades: todos
   
- Parts opcionals
    - [x] Nous objectes paramètrics: todos 
    - [ ] Penombres 
    - [ ] Diferents tipus de llums 
    - [x] Multiple-scattering: Oriol 
    - [ ] Escena CSG 
    - [/] Ambient occlusion: Oriol (está intentado)
    - [x] Defocus blur: Oriol
    - [x] Més d'una propietat en les dades reals: Eric
    - [ ] Animacions amb dades temporals
    - [x] Ombres atenuades segons objectes transparents : Angel
    - [x] Colors d'ombra segons els colors dels objectes transparents: Angel
    - [ ] Mapeig de les dades reals en una esfera
    - [x] Ús de diferents paletes: Maria Isabel
    
### Explicació de la pràctica    
    
En aquesta pràctica hem implementat el RayTracing utilitzant c++ i la llibreria glm. Hem implementat totes les fases satisfactòriament, i hem pogut generar diverses imatges amb RayTracing.

A comentar, hem triat els anteriors opcionals i en l'últim, hem entès que les noves paletes eren de materials (hem creat la goma, el plàstic i el latón). A més, s'ha intentat "l'ambient occlusion", però per falta de temps no ho hem pogut solucionar. Llavors, sortirà comentat al codi.

Creiem que ens hem repartit prou bé la feina, a pesar que no a tots se'ns dóna bé la geometria o les matemàtiques.Per això, estem molt satisfets d'haver-nos organitzat de tal manera que cadascun realitzi una part on pugui desenvolupar-se millor.
    
### Screenshots més rellevants
#### Imatge amb dos plans i esfera base metàl·lica
![image](https://user-images.githubusercontent.com/52278195/114320679-548cd180-9b17-11eb-8898-1558170bf54b.png)
#### Efecto mariposa
![image](https://user-images.githubusercontent.com/52278195/114320705-7dad6200-9b17-11eb-822a-974947cb7b57.png)
#### Tres esferes: una metàl·lica, una transparent(però opaca en el canal vermell) i una transparent amb índex = 1.5
![image](https://user-images.githubusercontent.com/52278195/114320724-974ea980-9b17-11eb-82c9-eeb345f033b4.png)
#### Motion Blur
![image](https://user-images.githubusercontent.com/52278195/114320731-a46b9880-9b17-11eb-9109-d748630ee033.png)
### Data Barcelona
![image](https://user-images.githubusercontent.com/52278195/114321183-bbab8580-9b19-11eb-9ba1-437e2f4152f3.png)


       
### Informació addicional o observacions
El símbol / als opcionals significa que l'hem intentat però té errades.

Si ens centrem en la imatge pujada al Padlet, hem intentat fer un efecte papallona: d'unes components bàsiques (plans metàl·lics i esferes transparents), generar una escena psicodèlica a partir de si mateixa. 

Per tant, si observem una de les imatges inicials, comencem amb plans de colors primaris. D'aquí, aconseguim tot l'espectre de colors. Al final, hem decidit establir un pla prioritari de color verd, tal que són les esferes les que reflecteixen els colors. Amb tot això i les reflexions i refraccions, es genera a poc a poc aquest efecte.
