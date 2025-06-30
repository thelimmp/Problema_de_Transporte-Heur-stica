Este proyecto contiene una implementación en C++ de una heurística personalizada, apodada “Los Dibujitos”, para resolver el problema de transporte.

La heurística calcula penalizaciones como el promedio entre el costo mínimo y máximo de filas o columnas activas, elige la mayor penalización y asigna recursos según el menor costo dentro de esa fila o columna.

También se puede usar este repositorio como base para comparar con métodos clásicos como:

Esquina Noroeste

Costo Mínimo

Método de Vogel

El código está organizado en una clase C++ (ProblemaTransporte) y permite ingresar datos de manera interactiva, mostrar la evolución del algoritmo y calcular el costo total.