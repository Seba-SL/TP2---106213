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


![este drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/6fe1621c-7db1-4d48-a574-fb8351692626)


Se uso el TDA lista_t para guardar pokemons disponibles 
Se uso el TDA abb_t para guardar las jugadas disponibles
Se uso el TDA hash_t para guardar los comandos y sus funciones


El usuario interactua con el juego a traves de una interfaz de usuario implementada con el TDA menu_t:

Principales operaciones del TDA menu_t
![menu_t drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/518bb1f2-f4e9-43d3-9470-10919f54e562)


Imagenes de la interfaz 

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/003c41c7-d623-438b-b1ff-8461041700a4)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/39b6df15-9346-49c4-84bf-731d6156714a)

Principales operaciones del TDA juego_t
![juego_t drawio](https://github.com/Seba-SL/TP2---106213/assets/65742172/473ffdd5-06bd-4369-ad21-f04832b46e4f)

Imagenes de la ejecucion del juego:

Carga de archivo valida y consulta de pokemon:

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/bbf08756-309e-4733-970c-4dfb761cc02b)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/c50ed4fa-2fee-4d48-8165-e318243c4093)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/03cd4011-cd88-4dc4-8055-2278c7f5580e)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/52744594-10d4-4e0b-9011-825e8d769c7f)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/aebb18de-06c2-478e-833a-55bbd5561dac)

![image](https://github.com/Seba-SL/TP2---106213/assets/65742172/ce80760b-7cb8-40eb-8f41-b04f87984bde)


Analisis de la complejidad de funciones


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
