/*
Comprobar que el formato es *.rt.

La info puede estar separada por 1 o más espacios.

Los elementos con letra mayúscula solo pueden aparecer
una vez durante el parseo.

Como hacer la iluminación del bonus si solo se permite
en el parseo una luz?

Luz ambiente: A, intensidad del 0 al 1 de la luz y color

Cámara: C, coordenadas, dirección(normalizada),
y Field Of View de x grados entre 0 y 180.

Luz: L, coordenadas, brillo(0 a 1), color(bonus)

Esfera: sp, coordenadas, diámetro, color

Plano: pl, coordenadas, vector normal del plano, color

Cilindro: cy, coordenada(centro), v_dir(del eje),
diámetro, altura, color.


Necesito un atof y atoi.

Hay coordenadas, colores, tamaños y rangos.

Las coordenadas son 3 floats separados por comas.
Los colores 3 unsigned char o int de 0 a 255.
Los tamaños son floats.
Los rangos son floats que tienen que estar en un rango.
Los vectores tienen que estar siempre normalizados y 
por tanto si su tamaño no es 1 es un Error.


Como guardo la información?
Una estructura con información común y listas de objetos.
(buscar las mejores estructuras para esto)

Funciones para parsear:
	Coordenadas
	Colores
	Rangos
	Vectores
	Una línea
	Bucle que consume líneas
*/