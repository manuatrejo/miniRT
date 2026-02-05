# Prioridades actualmente

Añadir path tracing

Patrón de ajedrez

Evitar usar sqrt

Aceptar puntos de luz

En intersections precalcular la info que se reutilice y meter a una estructura

Preguntar cuales son todas las optimizaciones posibles para el código

Comprobar que los números estén bien escritos en el .rt

Buscar cosas que jodan el resultado de las intersecciones de rayos


# Path Tracing

1 Path Tracing difuso

2 BRDF sampleable

3 GGX especular

4 Mezcla difuso + especular

5 Emisores (ñe)

6 Optimización

### Código reciclable

- f, g, d (GGX) ahora se evaluan dentro de BRDF

### Código nuevo

- Path tracing loop

- PDFs y troughput

- RNG (píxel, sample y rebote)

### Código a reestructurar



## Info útil

### Normalizar BRDF cook-t

Quitar arreglos para verlo bien y mirar por qué hacen falta

### Separar cook_torrance en eval_brdf y pdf_brdf


### Implementar trace_path

Recursión

Russian roulette

Emisores(por ver)

Acumulación Monte Carlo

### Cosine-weighted hemisphere sampling

Para el ruido

### Convertir cook-t en BRDF sampleable

Samplear distribución GGX, convertir half vector(ct.h) a dirección de luz, pdf correcto para GGX

### BRDF mixta (difusa + especular)

Difuso lambert + especular cook-torrance

Muestreo por mezcla (MIS simple)

No se suma la luz, se suma BRDFS dif + spec

## Flujo general del proyecto

### 1	Operaciones de vectores y rayos *

### 2	Objetos y funciones de intersección *

### 3	Generar un rayo por cada píxel de la cámara *

### 4	Render inicial (imprimir primeros objetos) *

### 5	Iluminación (FALTA PATH TRACING) 

### 6	Optimizar con BVH(solo si va extremadamente lento)

### 7	Añadir materiales con propiedades distintas *

### 8	Antialiasing, reflejos y objetos con texturas



## Por implementar para realismo


### 1 Path Tracing básico

Rebotes de luz para iluminación global.


### 2 Materiales PBR básicos (Principled/Metal-Rough)

Difuso Lambert para superficies no metálicas.
Microfacet GGX + Fresnel Schlick para especulares/metales.
Esto cambia drásticamente cómo “respiran” los objetos bajo la luz.


### 3 Sampling e Importance Sampling

Cosine-weighted hemisphere para difuso.
Importance sampling GGX para especular.
Reduce ruido y permite convergencia rápida.


### 4 Multiple Importance Sampling (MIS)

Combina muestreo de luz + BRDF.
Crucial si hay luces pequeñas o HDRI.


### 5 Area Lights / HDRI environment

Luz puntual = poco realista.
Area lights + HDRI hacen que la luz se sienta natural.


### 6 BVH (Bounding Volume Hierarchy)

Mejora la velocidad y permite más rays sin que la CPU muera.
Sin BVH, no podrás subir samples sin render eterno.


### 7 Russian Roulette (para cortar rebotes largos)

Permite limitar depth sin perder energía.
Mantiene eficiencia en CPU.


### 8 Tone Mapping + Gamma Correction

Convierte la iluminación física a imagen visible y natural.
Simple, rápido y da mucha mejora visual.


### 9 Clamp de fireflies / control de rayos muy brillantes

Evita que pocos rays arruinen la imagen.
Muy fácil de implementar, gran impacto visual.


### 10 Cámara básica / pinhole

No es crucial para realismo extremo, pero necesario para render correcto.


