<div align="right">
<img width="32px" src="img/algo2.svg">
</div>

# TP2

## Repositorio de Sebastian Nahuel Lazo - 106213 - slazo@fi.uba.ar

- Para compilar:

```bash
make main
```

- Para ejecutar:

```bash
./main
```

- Para ejecutar con valgrind:
```bash
make
```
---
##  Implementación de juego 

Este ultimo trabajo práctico consta de utilizar los TDA´s creados a lo largo de la cursada para la implementación de un juego que haga uso de estos para manejar datos del mismo.

Estructuras utilizadas para implementar la lógica del juego y del adversario:

![tp2-Página-2 drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/47012f60-41c7-426a-9e30-97b6c5999fec)



### Por ejemplo:

El programa funciona abriendo el archivo pasado como parámetro y leyendolo línea por línea. Por cada línea crea un registro e intenta agregarlo al vector. La función de lectura intenta leer todo el archivo o hasta encontrar el primer error. Devuelve un vector con todos los registros creados.

<div align="center">
<img width="70%" src="img/diagrama1.svg">
</div>

En el archivo `sarasa.c` la función `funcion1` utiliza `realloc` para agrandar la zona de memoria utilizada para conquistar el mundo. El resultado de `realloc` lo guardo en una variable auxiliar para no perder el puntero original en caso de error:

```c
int *vector = realloc(vector_original, (n+1)*sizeof(int));

if(vector == NULL)
    return -1;
vector_original = vector;
```


<div align="center">
<img width="70%" src="img/diagrama2.svg">
</div>

---

## Respuestas a las preguntas teóricas
Incluír acá las respuestas a las preguntas del enunciado (si aplica).
