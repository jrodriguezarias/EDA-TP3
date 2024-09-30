# EDAversi

## Integrantes del grupo y contribución al trabajo de cada integrante

* Juan Martín Rodríguez Arias: Funcionamiento del juego; alpha beta prunning
* Lisandro Llorens: Algoritmo minimax; alpha beta prunning


## Parte 1: Generación de movimientos válidos y algoritmo de jugada

Implementamos el funcionamiento del juego utilizando un arreglo de 8 vectores directores (llamados direcciones en el codigo).
Al testear el sistema, nos encontramos con el problema de que la IA tenía permitido poner piezas donde ya habia una pieza. 
Esto era causado por un bug que permitia agregar el mismo movimiento al stack de movimientos validos. Esto se solucionó utilizando un flag

## Parte 2: Implementación del motor de IA

El algoritmo minimax utilizado consiste en intentar maximizar la cantidad de piezas del jugador asumiendo que el oponente intentara minimizarlas.
Esto fue implementado mediante llamadas recursivas donde se utilizó una copia del modelo de juego para poder evaluar posiciones futuras sin modificar el modelo actual. La naturaleza recursiva de las llamadas permite que las situaciones de juego que evalua el algoritmo sean recorridas como un arbol. Este arbol es navegado en formato DFS.

## Parte 3: Poda del árbol

Debido al alto numero de posiciones del tablero futuras que puede haber, en especial al comienzo de la partida, el algoritmo debe evaluar una cantidad muy alta de situaciones. Para el tablero utilizado de 64 posiciones, puede haber un maximo de 60 movimientos entre ambos jugadores. Como cada uno de estas posiciones debe evaluar un movimiento (implicando que llama a la funcion playMove y getValidMoves), la complejidad computacional aumenta de forma factorial. 

Como consecuencia, es funcionalmente imposible evaluar el arbol entero y es necesario limitar o bien la cantidad de posiciones (o nodos) que pueden evaluarse, o bien la profundidad (es decir, la cantidad de movimientos hacia adelante) que el algoritmo explora. Debido a que utilizamos busqueda DFS, utilizamos ambos tipos de limitaciones para podar el arbol asi no se consumen todos los nodos sin poder haber recorrido el arbol de forma pareja (es decir, que no se utilicen todos los nodos permitidos en los hijos de un mismo nodo padre sino que se evaluen tambien los hijos de los nodos hermanos al nodo padre en cuestion).

 
## Documentación adicional

[Aquí.]

## Bonus points

Implementamos poda alpha-beta en nuestro algoritmo. Esta técnica consiste en utilizar la sucesion de nodos maximos y minimos para evitar evaluaciones innecesarias de nodos que no alterarian el resultado obtenido sin importar su valor. Esto se logra evaluando la expresion alpha >= beta siendo alpha el valor maximo encontrado (heredado por los hijos) y beta el valor minimo encontrado heredado tambien. Que el valor de alpha sea mayor o igual a beta significa que ya no se podra mejorar el resultado que tomará el nodo padre, haciendo innecesaria la evaluacion del resto de nodos hijos. Cuando esto ocurre con un nodo padre maximo se le dice poda alpha mientras que se le dice poda beta cuando este evento ocurre con un nodo padre minimo.
