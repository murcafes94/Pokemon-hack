# Hoenn: claro de investigación de Bosque Petalia

Base: `6622c5f54928342a5f39ab9f66e9cd9d60c19ced`.
Recuperación: `recovery/develop-before-forest-debug-6622c5f5`.

## Acceso y recorrido

El guía del estudio está en la zona sur de Bosque Petalia, en (18, 33), junto al acceso desde la Ruta 104. Pide haber entregado el informe de Zigzagoon de la Ruta 102 y haber resuelto el encuentro original de DEVON (`VAR_PETALBURG_WOODS_STATE >= 1`). Se puede rechazar la visita y volver después.

Al aceptar, acompaña al jugador a `PetalburgWoods_LegacyClearing`, un mapa nativo nuevo de 24 × 20 metatiles. Tiene senderos abiertos, árboles, hierba, cartel, investigador y dos Pokémon visibles. La salida al sur (11/12, 18) vuelve al bosque en (18, 34), delante del guía. El acceso no concede medallas, no adelanta el evento de DEVON y no requiere Corte ni Surf.

Se anexan el mapa al final de `gMapGroup_Dungeons` y el layout al final de la lista existente. Los identificadores anteriores permanecen en su posición. El bosque original conserva su terreno, sus scripts, sus 13 objetos y sus seis warps; se añaden un guía y un punto de retorno. Se conserva la continuidad peatonal desde la entrada sur hasta el encuentro de DEVON.

## Pokémon y observaciones

Shroomish y Wurmple usan `OBJ_EVENT_GFX_SPECIES` con sus sprites y paletas de overworld existentes. No se activa el sistema global de acompañantes. Estos dos personajes son observaciones persistentes: no se capturan ni se eliminan al interactuar.

Se puede observar a las especies en cualquier orden. Shroomish permite observar desde lejos o esperar quieto; Wurmple permite esperar en silencio o dejar libre el paso. Las respuestas quedan guardadas por separado y no sustituyen las de Poochyena o Zigzagoon. Repetir la conversación reconoce la respuesta anterior.

Con ambas notas se puede entregar el informe al investigador del claro o al del anexo de Villa Raíz. Se registra una sola vez y sin recompensa repetible. El libro del anexo conserva los dos estudios anteriores y añade las observaciones del claro y la entrega del informe.

En los pequeños parches de hierba sí hay encuentros salvajes normales, de niveles 3–6:

| Especie | Peso entre encuentros terrestres |
| --- | ---: |
| Wurmple | 40 % |
| Shroomish | 30 % |
| Zigzagoon | 20 % |
| Taillow | 10 % |

La frecuencia terrestre configurada es 15. Los porcentajes son la distribución entre especies cuando se genera un encuentro; no son una probabilidad directa por paso. Las tablas originales de encuentros permanecen idénticas: se añade únicamente la del claro.

## Guardado

Se utilizan seis bits permanentes comprobados sin uso en ambas tablas base. No se cambia el tamaño ni la estructura del guardado.

| Flag | Bit |
| --- | --- |
| `FLAG_LEGACY_FOREST_ASSIGNED` | 0x4A7 |
| `FLAG_LEGACY_FOREST_SHROOMISH` | 0x4A8 |
| `FLAG_LEGACY_FOREST_WURMPLE` | 0x4A9 |
| `FLAG_LEGACY_FOREST_REPORTED` | 0x4AA |
| `FLAG_LEGACY_FOREST_DISTANCE` | 0x4AB |
| `FLAG_LEGACY_FOREST_QUIET` | 0x4AC |

Las declaraciones de flags anteriores mantienen sus valores. El nuevo diálogo de historia se protege frente al importador y por hash; los textos propios de los capítulos anteriores se conservan byte por byte.

## Validación

- 39 pruebas de historia/atajos/bicicleta y 22 de localización: 61 en total.
- 909 líneas verificadas por ancho, incluidas las nuevas conversaciones de bosque y depuración.
- Flujo real de scripts: requisitos, rechazo/aceptación, orden de observaciones, las cuatro combinaciones de respuestas, repetición, entrega desde ambas ubicaciones y registro tras conservar/cargar flags.
- Recorridos sobre el terreno binario: salidas, acceso al cartel y Pokémon, todos los parches de hierba y conexión del guía con el camino original.
- Compilación local ARM GCC 13.2.1 aprobada: EWRAM 226 416 B (86,37 %), IWRAM 28 376 B (86,60 %), ROM 26 789 596 B (79,84 %).
- Objeto ARM de scripts recompilado con `RELEASE`: excluye los nuevos atajos. La ROM normal sí contiene sus símbolos.

El intérprete de pruebas no emula GBA. La visualización de sprites, paletas, la transición de salida, combates/capturas y el guardado/carga reales de este tramo quedan pendientes de prueba en mGBA. Se revisó una representación del terreno usando los metatiles y las paletas de esta base; no equivale a una captura del juego.

## Prueba manual

1. Guardar dentro del juego, cerrar la ROM, actualizar `develop`, ejecutar `make -j2` y volver a abrir `pokeemerald.gba` con Continuar.
2. Entregar el informe de Ruta 102 y resolver el evento original de DEVON en Bosque Petalia.
3. Volver al guía cerca de la entrada sur del bosque. Rechazar y después aceptar la visita.
4. Observar a ambos Pokémon. Entregar el informe en el claro o regresar al anexo. Consultar el libro.
5. Salir por el sur, volver con el guía y comprobar que las observaciones siguen registradas. Guardar/cargar y volver a comprobarlo.
6. Probar los encuentros en la hierba y verificar que los dos Pokémon de investigación permanecen en su sitio.
7. Usar una copia de prueba de la partida para repetir otras respuestas con [Legacy rápido](TEST_SHORTCUTS.md).
