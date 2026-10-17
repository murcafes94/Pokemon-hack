# Mochila ampliada compatible con las partidas anteriores

La mejora inicial de 9.999 unidades por pila no resolvía los huecos llenos.
En la partida de prueba se encontraron llenos los 30 huecos de objetos,
los 30 de objetos clave, los 16 de Poké Balls y los 46 de bayas.

## Capacidad actual

| Bolsillo | Huecos anteriores | Huecos actuales |
| --- | ---: | ---: |
| Objetos | 30 | 254 |
| Objetos clave | 30 | 62 |
| Poké Balls | 16 | 32 |
| MT/MO | 64 | 128 |
| Bayas | 46 | 78 |

Se mantienen las pilas de 9.999. No es capacidad infinita. El menú de prueba
ahora añade 99 unidades, omite objetos que ya se poseen y deja al menos ocho
huecos libres en cada bolsillo. No reduce ni borra las cantidades que ya
estaban guardadas. Una pila de bayas o MT/MO que ya tenga 9.999 unidades
conserva el límite de pila única del motor y puede rechazar más unidades.

## Formato y compatibilidad

Los bolsillos originales de SaveBlock1 mantienen sus tamaños y offsets.
La extensión se guarda en el espacio de SaveBlock3 que ya reservaba el motor
en los catorce sectores de cada copia de la partida. SaveBlock1 sigue en
15.568 bytes y SaveBlock2 en 3.884. La mochila original ocupa 744 bytes en
el offset 1.376; flags, variables y clave de cifrado no cambian de posición.
Hay aserciones de compilación ARM que protegen estos valores.

SaveBlock3 conserva su prefijo original de cuatro bytes y crece a 1.484,
dentro de los 1.624 disponibles. No se reutilizan Hall of Fame, Torre
Entrenador ni combate grabado. Los objetos nuevos se ven en los mismos
bolsillos mediante un acceso que combina slots originales y adicionales.
Se preservan cifrado, ordenación, compactación, venta y uso de objetos.

Las partidas anteriores de Legacy tienen a cero la zona de ampliación.
Se reconocen al cargar, se inicializan huecos vacíos y no se mueven los
objetos originales. La migración se guarda al guardar normalmente dentro
del juego; no se edita externamente el archivo .sav del jugador.

El formato nuevo tiene identificador LBG1 y comprobación de integridad de
los datos adicionales. Al elegir entre las dos copias de guardado, una
extensión inválida hace rechazar esa copia y permite recuperar la otra
válida. No se confunde una cabecera desconocida con un inventario vacío.
Los guardados de enlace y sus tareas incrementales abarcan ahora los
catorce sectores para conservar todos los fragmentos de la extensión.
Las copias temporales de la mochila para enlace y tutorial de Blasco
incluyen también los huecos nuevos.

## Verificación

```bash
python3 -m unittest discover -s tools/legacy_inventory -v
python3 -m unittest discover -s tools/legacy_story -p 'test_*.py'
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py'
```

Las pruebas compilan y ejecutan las funciones C reales con flash simulada
además de AddressSanitizer y UndefinedBehaviorSanitizer. Cubren los límites
originales llenos, entrada de objetos en la extensión, capacidad total,
retirada, ordenación, cifrado, carga de formato anterior, guardado/carga,
copia dañada con recuperación de la anterior, guardados parciales de enlace,
tutorial, copias temporales y kits de prueba sin duplicados. Se reprodujo
además el inventario real desde una copia en memoria, sin modificar el .sav.

En ARM se verifican los offsets originales mediante aserciones; el marco de
pila de selección del guardado mide 1.532 bytes en la compilación aislada O2.
Las pruebas no emulan los tiempos del hardware de enlace.

## Prueba en mGBA

Guardar dentro del juego antes de reiniciar el emulador. Abrir la ROM nueva
y elegir Continuar. Los estados rápidos antiguos contienen memoria y código
de la ROM anterior y no son el mecanismo de migración.

Comprobar recogida del objeto que fallaba, navegación por más de treinta
objetos, ordenación, venta, guardado y carga de un objeto adicional. Revisar
el tutorial y el enlace en pruebas separadas. Los respaldos originales se
conservan fuera del repositorio. No guardar esta mochila ampliada con una
ROM anterior: esa ROM desconoce los huecos nuevos y puede borrarlos.
