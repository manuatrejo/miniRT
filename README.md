POR HACER HOY:

Calcular dirección de los rayos del orígen al plano de píxeles:

1 Up predefinido y calcular right con el producto cruzado de
la dirección de la cámara y up

2 Recalcular up

3 Normalizar coordenadas del píxel
El (doble del valor del iterador / WIN_WIDTH) - 1

4 Ajustar coordenadas de píxeles por la relación entre WIDTH y HEIGHT

5 Calcular dirección del rayo
ray = (right * x) + (up * y) + cam_vector

6???? Ajustar rayos al FOV


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

