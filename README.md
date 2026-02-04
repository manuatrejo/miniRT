# Prioridades actualmente

Añadir path tracing

Comprobar que los números estén bien escritos en el .rt

Buscar cosas que jodan el resultado de las intersecciones de rayos


## Path Tracing

Función que lanza rayos de forma recursiva y suma iluminación directa + indirecta

Lanzar varios rayos y calcular el promedio de estos (Montecarlo)

Necesito una función que genere rayos con direcciones random y que las direcciones más
probables sean las que más se generen

1 Función que genere múltiples muestras por píxel

2 Función que genera rayo "aleatorio"

3 Función que calcula rebotes del rayo


# Iluminación

## Implementar modelo Phong

### 1 Ambient, diffuse, specular

### 2 Sombras sencillas(shadow rays)

### 3 Atenuación de la luz / (distancia ^ 2)

### 4 Materiales con propiedades

### 5 Reflexiones

### 6 Refracción (ley de Snell)

### 7 Iluminación global(Ambient Oclussion, Path Tracing(Montecarlo))

### 8 Gamma correction

### 9 Antialiasing



## Flujo general del proyecto

### 1	Operaciones de vectores y rayos *

### 2	Objetos y funciones de intersección *

### 3	Generar un rayo por cada píxel de la cámara *

### 4	Render inicial (imprimir primeros objetos) *

### 5	Iluminación

### 6	Optimizar con BVH(solo si va extremadamente lento)

### 7	Añadir materiales con propiedades distintas

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


## Info que hay que buscar fuera de RT in one weekend y one week:

Direct lighting in path tracing
Shadow rays (iluminación poco realista)
Point light contribution
Direct + indirect lighting
Next Event Estimation (aunque sea versión simple)
Importance sampling for point lights
Light sampling vs BRDF sampling
Energy conservation in BRDF
Lambertian BRDF = albedo / π

