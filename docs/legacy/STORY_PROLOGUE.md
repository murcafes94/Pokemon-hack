# Primer tramo jugable de Legacy: anexo de investigación

Base: `b64f82e761a55dc51c79b17767f17b49d43ec1bf`.
Recuperación: `recovery/develop-before-story-annex-b64f82e7`.

## Qué puede jugarse

Tras recibir la Pokédex y las Poké Balls en el laboratorio de Villa Raíz, Abedul presenta su investigación sobre señales de comportamiento y confianza. El jugador puede hablar con el guía situado en el lado derecho del laboratorio (11, 4). Si acepta, el guía lo lleva al anexo, un mapa nativo de 13 × 11 metatiles con investigador, Poochyena, registro y notas regionales.

En el anexo, el investigador permite inscribirse o rechazar el estudio y volver después. La primera observación de Poochyena ofrece dos respuestas: esperar con calma a que se sienta seguro u observar desde lejos. Ambas respetan al Pokémon y quedan diferenciadas en el registro. Repetir la interacción no cambia la decisión ni reinicia el evento. Se puede consultar el registro en el libro de la pared norte y hablar con el investigador para comentar el resultado.

El proyecto continúa con Hoenn como primera región, Kanto como segunda y Johto como tercera. Las notas mencionan futuros destinos sin habilitar viajes regionales. Mewtwo y Proyecto Génesis permanecen reservados para la trama posterior.

## Mapa y continuidad

El anexo reutiliza los gráficos del laboratorio que ya están en Legacy y tiene un plano nuevo. No se importan mapas de ROMs ni recursos de otra base. La entrada de esta versión es una transición guiada por NPC; una puerta física/corredor puede integrarse en una ampliación posterior del edificio.

Las dos salidas inferiores del anexo regresan a (11, 5) del laboratorio. Ese punto y la posición del guía son transitables en las dos variantes originales del laboratorio, incluida la variante de los iniciales de Johto. Los layouts originales no se modifican. En el laboratorio se añaden únicamente el guía y un destino de retorno; todos los objetos y warps anteriores mantienen posición y orden.

El nuevo mapa se añade al final del grupo de interiores de Villa Raíz. El nuevo layout se añade al final de la lista de layouts. Los identificadores anteriores no cambian. Se preservan las escenas iniciales, entregas de Pokémon, Pokédex, Poké Balls y eventos posteriores. La introducción de la pantalla de partida nueva conserva su hash protegido.

## Estado guardado

Se reservan cuatro bits previamente sin referencias en los fuentes de ambas bases, fuera del rango temporal 0x00–0x1F:

| Flag | Bit | Significado |
| --- | --- | --- |
| `FLAG_LEGACY_RESEARCH_REGISTERED` | 0x020 | Inscripción aceptada |
| `FLAG_LEGACY_APPROACH_PATIENTLY` | 0x021 | Esperar con calma; sin este bit tras completar significa observar a distancia |
| `FLAG_LEGACY_FIRST_OBSERVATION` | 0x022 | Observación completada |
| `FLAG_LEGACY_PROLOGUE_BRIEFED` | 0x023 | Presentación de Abedul ya mostrada |

No se amplía ni reorganiza la estructura de guardado. Las partidas existentes que ya terminaron la entrega de la Pokédex pueden comenzar hablando con el guía y recibir la presentación en el anexo. Antes de esa entrega, el guía pide terminar el encargo de Abedul. El evento no otorga objetos repetibles ni cambia amistad, estadísticas o Pokémon del equipo.

Esta es una decisión narrativa inicial. El Vínculo individual, su puntuación, el Pokémon acompañante, crafting y las 24 medallas siguen pendientes; el registro de esta escena no equivale a esos sistemas.

## Verificación y prueba de juego

```bash
python3 -m unittest discover -s tools/legacy_story -p 'test_*.py' -v
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py' -v
python3 tools/legacy_localization/check_text_layout.py
python3 tools/legacy_localization/check_protected_texts.py
make -j2 -O all
```

Nueve pruebas de historia evalúan los scripts reales mediante un intérprete limitado: acceso antes/después de la Pokédex, rechazar/aceptar inscripción, ambas decisiones, repetición y consulta del registro. Comprueban además tamaño del mapa, rutas por tiles transitables hasta salidas/interacciones, tipo de warp de las salidas, posiciones de retorno, bits permanentes y orden de mapas. Son pruebas de flujo y datos; no ejecutan el motor GBA.

El control de ancho valida ahora 683 líneas, incluidas 89 líneas del prólogo. El plano se inspeccionó mediante un render de sus metatiles y paletas reales. La revisión visual y los movimientos del personaje en mGBA aún deben verificarse.

Compilación local ARM GCC 13.2.1 aprobada: EWRAM 226 416 B (86,37 %), IWRAM 28 376 B (86,60 %), ROM 26 779 356 B (79,81 %). Los archivos propios de introducción y prólogo se excluyen del importador de referencias y se verifican por hash; cualquier ampliación intencional debe revisar y actualizar el hash del prólogo.

Para probar: obtener la Pokédex, hablar con el guía a la derecha de Abedul, aceptar el viaje, inscribirse con el investigador, hablar con Poochyena y elegir una respuesta. Revisar el libro de la pared norte, repetir la conversación, salir por abajo, guardar y cargar para confirmar el registro. Probar la otra respuesta en una partida de prueba separada. Las partidas existentes posteriores a la Pokédex pueden entrar directamente por el guía.

## Continuación prevista

El siguiente tramo llevará la investigación a una zona de campo de Hoenn con una misión propia, rutas físicas y consecuencias observables. La localización restante continúa en paralelo por bloques. La ampliación regional y el remaster gráfico se integrarán conservando esta base y sus puntos de recuperación.
