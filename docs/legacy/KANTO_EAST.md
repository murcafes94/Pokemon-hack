# Kanto oriental: Ruta 3 y primera cámara de Monte Luna

## Recorrido implementado

Ciudad Plateada tiene una salida al este, alineada con el sendero de Ruta 3.
La conexión permite ir y volver a pie, sin medallas, objetos ni participación
en el circuito como requisitos adicionales. El viaje inicial desde Hoenn
conserva sus requisitos existentes.

Ruta 3 es un mapa nativo de 40 × 24 metatiles, con una colina al norte,
sendero con curvas, hierba al sur y un puesto de investigación frente a
la entrada de Monte Luna. El paso principal evita la hierba alta; los
encuentros son opcionales y están entre los niveles 54 y 57.

Se reutilizan las músicas de Ruta 3 y Monte Luna ya presentes en el motor.

La cámara de Monte Luna es un mapa nativo de 24 × 20 con dos pequeños
obstáculos de roca y una plataforma de observación. No exige Destello.
Tiene regreso por la entrada anterior y un paso al nordeste hacia Ruta 4.
Permite Cuerda Huida/Excavar mediante
el mecanismo de salida de cuevas del motor. No hay caída ni salida de
un solo sentido. Los encuentros están entre los niveles 55 y 58: Zubat,
Geodude, Golbat, Graveler, Paras, Parasect y Clefairy. El Clefairy del equipo
de campo es un NPC de observación; los Clefairy capturables son salvajes.

La recuperación por derrota sigue en Ciudad Plateada. El puesto no cura:
el investigador indica dónde volver para hacerlo. El paso del nordeste continúa por
[Ruta 4 hasta el puesto de Ciudad Celeste](CERULEAN.md).

## Historia y combate

Elías ofrece un combate amistoso con Sandslash 58 y Golbat 59. Puede
rechazarse, perderse y reintentarse. La victoria se registra con su flag
de entrenador; al volver conversa sobre el terreno y no fuerza otro combate.
No concede un objeto ni una medalla adicional.

El investigador del puesto reconoce la Medalla Roca y explica que esperan
compartir sus notas con Misty cuando se abra el camino a Ciudad Celeste.
En la cámara se comparan las observaciones de Hoenn con las reacciones
al eco de Monte Luna. El diálogo reconoce la exhibición con Brock si ya
fue completada; no la marca como realizada ni bloquea la exploración.

Estas escenas preparan la conexión narrativa con Misty sin anunciar un
encuentro jugable que aún no existe. Proyecto Génesis queda reservado para
el postgame y Mewtwo conserva su papel previsto.

## Compatibilidad y revisión

Los mapas y layouts se añaden al final de sus listas: conservan los IDs
anteriores. Ciudad Plateada conserva tamaño, gimnasio, servicios, objetos
y warps; únicamente se abre la salida oriental. Elías ocupa el entrenador
858, dentro del máximo existente de 864. No se amplía el guardado ni se
reservan nuevas flags o variables de historia.

Se mantiene la partida y el archivo de cheats fuera de los commits. La ROM
anterior y las partidas cuentan con respaldos externos al repositorio.

Las pruebas de scripts verifican cancelación, derrota, victoria, repetición
y conservación de los avances anteriores. Las pruebas de mapa recorren
los metatiles reales, comprueban conexión en ambos sentidos, acceso a NPC,
warps recíprocos, encuentros y registro de mapas solo para Emerald.
Los mapas se revisan con un render estático de sus tiles y paletas nativos:

```bash
python3 tools/legacy_maps/render.py LegacyKanto_Route3 /tmp/ruta3.png
python3 tools/legacy_maps/render.py LegacyKanto_MoonChamber /tmp/monte-luna.png
```

El render no incluye sprites ni animaciones y no sustituye mGBA.
Pendiente en emulador: cruzar el borde oriental de Plateada, entrar y salir
de la cueva, encuentros, combate de Elías, derrota y recuperación, Cuerda
Huida/Excavar, diálogos y guardado/carga. Usar una copia de la partida y
cargar con Continuar, conservando el respaldo original.

## Siguiente tramo

La [continuación hasta Celeste](CERULEAN.md) ya incorpora servicios, desafío
de Misty, Medalla Cascada y su exhibición en el Circuito de los Lazos. La [mochila ampliada](BAG_EXTENSION.md) ya añade huecos sin mover los
objetos de las partidas anteriores; sus pilas actuales son de 9.999.
