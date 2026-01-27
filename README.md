Prioridades:

1	Hacer que funcione con inputs básicos

2	Añadir iluminación avanzada

3	Optimizar(usar BVH solo si va lento)

Lista de objetivos:

1	Operaciones de vectores y rayos

2	Objetos y funciones de intersección

3	Generar un rayo por cada píxel de la cámara

4	Render inicial (imprimir primeros objetos)

5	Iluminación

6	Optimizar con BVH

7	Añadir materiales con propiedades distintas

8	Antialiasing, reflejos y objetos con texturas


SIGUIENTE: comprobar donde choca el rayo

Recorrer todos los objetos que haya y comprobar si un rayo choca

Imprimir el color del objeto con el que choque antes

Función que devuelva donde choca o si choca un rayo dependiendo del tipo de objeto


SIGUIENTE: iluminación

Para objetos que reflejen la luz mandar varios rayos y hacer que reboten algunos

El objetivo es conseguir una iluminación global lo más realista posible sin
hacerlo demasiado complicado y si es posible sin demasiada computación.

Iluminación ambiental"A" mínima que tienen todos los objetos + iluminación puntual"L"

1 Iluminación Phong
2 Reflexión sencilla
3 Sombras simples



###Prioridades


1 Path Tracing básico

Rebotes de luz para iluminación global.


2 Materiales PBR básicos (Principled/Metal-Rough)

Difuso Lambert para superficies no metálicas.
Microfacet GGX + Fresnel Schlick para especulares/metales.
Esto cambia drásticamente cómo “respiran” los objetos bajo la luz.


3 Sampling e Importance Sampling

Cosine-weighted hemisphere para difuso.
Importance sampling GGX para especular.
Reduce ruido y permite convergencia rápida.


4 Multiple Importance Sampling (MIS)

Combina muestreo de luz + BRDF.
Crucial si hay luces pequeñas o HDRI.


5 Area Lights / HDRI environment

Luz puntual = poco realista.
Area lights + HDRI hacen que la luz se sienta natural.


6 BVH (Bounding Volume Hierarchy)

Mejora la velocidad y permite más rays sin que la CPU muera.
Sin BVH, no podrás subir samples sin render eterno.


7 Russian Roulette (para cortar rebotes largos)

Permite limitar depth sin perder energía.
Mantiene eficiencia en CPU.


8 Tone Mapping + Gamma Correction

Convierte la iluminación física a imagen visible y natural.
Simple, rápido y da mucha mejora visual.


9 Clamp de fireflies / control de rayos muy brillantes

Evita que pocos rays arruinen la imagen.
Muy fácil de implementar, gran impacto visual.


10 Cámara básica / pinhole

No es crucial para realismo extremo, pero necesario para render correcto.

