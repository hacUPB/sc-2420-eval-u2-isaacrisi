Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/C5iNLRra)
# Documentación del Proyecto
## Unidad 2

Estudiante:  Isaac Pineda Múnera 
Id:  000509927
---
Pagina
confusion-snapper-025.notion.site/Sistemas-Computacionales-d1806d0b626347f4aa90a17b56807004?pvs=4 

# Documentacion

Primer punto del ejercicio 1 resuelto sin problemas 
el Set up se ejecuta cada vez que se inicia el programa 
el update se ejecuta una vez dada frame 
y el render se ejecuta igual que el update. 

el punto dos se realiza igual sin problemas señ encuentra que si hay 


Altos FPS (frecuencia alta): Si los tiempos entre las llamadas a Update() y Render() son pequeños (por ejemplo, cercanos a 16 ms), el juego se verá fluido, ya que se están generando muchos cuadros por segundo.


Bajos FPS (frecuencia baja): Si los tiempos son más largos (por ejemplo, 30 ms o más), el juego puede comenzar a verse laggeado, lo que afecta negativamente la experiencia del jugador.
Importancia de la Constancia:
Mantener un tiempo de actualización constante entre las llamadas es crucial para evitar variaciones en la velocidad del juego. Si el tiempo entre las iteraciones varía demasiado, puede causar efectos no deseados, como movimientos bruscos o cambios en la velocidad del personaje.


para el punto tres se crea un ciclo while que permita crear un círculo siguiendo la ecuación r=x^2+y^2 dándole valores a "x" y a "y" con el ciclo y "r" definiéndolo desde el Código según el tamaño deseado. 
este círculo presentó un problema y es que cuando se decidió moverlo a pesar de multiplicar su velocidad por el delta time se movia con relación al frame rate y no a los píxels por segundo definidos. 


para el cuarto punto que fue mover las figuras fue simple es cambiar su posición en x o en y y multiplicar ese cambio por el delta time. 

para el punto 5 el cambio de tamaño fue fácil solo era volver la constante del tamaño de la figura una variable y amuentarla en el update. 
el cambio de orientación se planteó como intercambiar el tamaño en x y el tamaño en y pero no resultó y como no se necesitaba para el juego planteado, se descarto. 
y el cambio de color fue simple se crearon tres variables r, g y b Que representan las cantidades de luz de cada color para el drawcolor y esas mismas variables inicializarlas en valores distintos, con esas variables se cambiaban en el update aumentandolas de a una. 


para el sexto punto de plantea el rebote de las figuras como que cuando sobrepasen el tamaño de la pantalla su velocidad se vuelva negativa, pero se estaba haciendo de manera errónea y en lugar de invertir la velocidad estaba volviedo un poco hacia atrás y seguía moviéndose hacia el mismo lado, entonces se creó una variable para manejar la velocidad y así poderla hacer negativa completamente
y al hacelo así ya funcionó el rebote de las figuras, luego otro reto fueron las comisiones entre figuras que inicialmente se planteó como que cuando se igualaran las posiciones pero estaban tomando lados distintos de las figuras pero para solucionarlos se restaba a una figura el tamaño para que diera la posición del lado que debía colisionar y así si se logró que colisionaran 

para el inicio del juego se creó otro rectángulo de una tamaño muy grande a mitad de pantalla para que funcionase como un suelo en movimiento y un cuadrado dentro que cambia de color para detectar el movimiento. 

se implementó una lectura de teclado que dejase saltar al presionar la w pero no funcionó bien si leía el teclado pero a la hora de saltar no aplica bien las condiciones que se usan para saltar la primera vez que se unde la tecla sube el cubo pero no baja y al estar en el aire ys no permite tampoco saltar mas. 
