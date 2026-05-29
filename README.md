# MiniKernel

Simulacion de un mini sistema operativo que implementa procesos concurrentes y planificacion de CPU mediante el algoritmo Round Robin, desarrollado en C con POSIX threads.

## Descripcion

MiniKernel funciona como un proceso en espacio de usuario que utiliza hilos para simular CPUs, generar procesos y reportar metricas de rendimiento. Los procesos son representados mediante una estructura PCB (Process Control Block).

## Componentes
- **Generador de procesos** — hilo que crea procesos con burst time y arrival time usando distribucion de Poisson
- **Cola de procesos listos** — estructura FIFO protegida con mutex y variables condicionales
- **CPUs simuladas** — 3 hilos que ejecutan procesos con Round Robin y quantum=2
- **Metricas** — hilo que calcula tiempo de respuesta y throughput

## Compilar y ejecutar

```bash
# compilar
make

# compilar y ejecutar
make run

# ejecutar tests
make test

# limpiar archivos compilados
make clean
```

## Metricas

- **Tiempo de respuesta** — tiempo desde que llega el proceso hasta que termina
- **Throughput** — numero de procesos completados por unidad de tiempo

## Repositorio

https://github.com/Dave-bee/ZambranoJ-MiniKernel
