```markdown
Laboratorio #5 - Sistemas Operativos  
Universidad del Valle de Guatemala
Curso: Sistemas Operativos - Semestre I, 2025  
````
---
## 🧪 Descripción
Este laboratorio implementa sincronización de hilos (threads) utilizando:
- Semáforos (`sem_t`)
- Monitores (simulados con `pthread_mutex_t` y `pthread_cond_t`)

El objetivo es gestionar el consumo de un recurso digital mediante múltiples hilos concurrentes.  
Cada hilo consume y devuelve recursos en ciclos con tiempos aleatorios.

---
## 📁 Estructura de Archivos



Laboratorio5-Threads/
###### ├── semaforoMain.c          # Primer programa con semáforos
###### ├── bitacoraS.txt           # Bitácora de ejecución del programa con semáforos
###### ├── monitorMain.c           # Segundo programa con monitor
###### ├── monitor.h               # Header con funciones monitorizadas
###### ├── bitacoraM.txt           # Bitácora del programa con monitor
###### ├── Makefile                # Compilación automática
###### └── README.md               # Este archivo



---

## ⚙️ Compilación

Desde la terminal (con GCC y Make instalados), ejecuta:

```bash
make
````

Esto generará dos ejecutables:

* `semaforo` → ejecuta el programa con semáforos.
* `monitor` → ejecuta el programa con monitor.

---

## ▶️ Ejecución

```bash
./semaforo
./monitor
```

Se generarán automáticamente los archivos de bitácora:

* `bitacoraS.txt` para semáforos
* `bitacoraM.txt` para monitor

---

## 🔍 Detalles Técnicos

### `semaforoMain.c`

* Crea `NUM_THREADS` hilos.
* Cada hilo ejecuta `NUM_ITERATIONS` veces:

  * Consume 1 recurso (semáforo).
  * Espera un tiempo aleatorio.
  * Libera el recurso.
* Todo sincronizado sin race conditions.

### `monitorMain.c`

* Similar, pero los hilos pueden consumir múltiples recursos (`1-3` aleatorios).
* Funciones:

  * `decrease_count(int count)`
  * `increase_count(int count)`
* Implementadas como **monitor** usando `mutex` y `condición`.

---

## 📝 Bitácoras

Las bitácoras muestran:

* Qué hilo accede a recursos.
* Cuántos recursos quedan.
* Si el hilo tuvo que esperar.

Ejemplo de línea en `bitacoraM.txt`:

```
Esperando recursos: solicitados=3, disponibles=2
```

---

## 🧠 Aprendizajes

Este laboratorio permitió aplicar conceptos fundamentales de sincronización de hilos y coordinación segura del acceso a recursos compartidos, utilizando herramientas reales del sistema como Pthreads en C.

---

## 🛠️ Requisitos

* Compilador GCC
* Sistema con Glibc (Linux o WSL en Windows)
* Make (opcional pero recomendado)

---

## 📌 Autor

**Ruth de León** 2025