# Hoenn: primera misión de campo en la Ruta 102

Base: `484b2dbb14dd1103d625eb8a12eeb8a397a20439`.
Recuperación: `recovery/develop-before-field-mission-484b2dbb`.

## Tramo jugable

Después de observar a Poochyena y comentar el resultado con el investigador del anexo, se ofrece un encargo opcional de campo. Se puede rechazar y aceptar después. Al aceptar, el registro conserva la primera observación y añade el estado del nuevo trabajo.

El jugador camina por Hoenn hasta la Ruta 102, al oeste de Pueblo Escaso. Cerca de los árboles de bayas encontrará un investigador (28, 5) y un Zigzagoon (26, 3). El investigador recuerda cómo se respondió a Poochyena y adapta su consejo. Zigzagoon permite una segunda decisión independiente: esperar sin moverse o darle espacio para pasar. Ambas respuestas se registran sin sobrescribir la primera.

Después de observar, se vuelve caminando al anexo y se habla con el investigador. El informe adapta su respuesta a lo ocurrido, se marca como entregado una sola vez y puede consultarse en el libro de la pared norte. Las interacciones posteriores reconocen el progreso. Si se eligió esperar, al volver a cargar la Ruta 102 Zigzagoon usa el movimiento de mirar alrededor. El próximo informe sobre Bosque Petalia queda como pista de un tramo futuro, sin impedir continuar la aventura original de Hoenn.

## Mapa y continuidad

Se añaden dos objetos al final de la lista de la Ruta 102: investigador y Zigzagoon. Los nueve objetos originales conservan orden, coordenadas, gráficos, scripts y flags. Se conservan entrenadores, bayas, objeto de suelo, conexiones y encuentros salvajes. No se modifica el terreno ni sus tilesets, ni se crea un mapa o identificador de layout en esta entrega.

El nuevo callback de transición cambia únicamente la plantilla de movimiento de Zigzagoon cuando su observación y la respuesta paciente están registradas. Se utiliza `OBJ_EVENT_GFX_ZIGZAGOON_2`, el recurso existente que ya usan otros mapas de esta base.

Las pruebas de recorrido excluyen agua, saltos y tiles con colisión: se verifica el acceso a las dos nuevas interacciones desde Pueblo Escaso sin Surf, la conexión a Ciudad Petalia y que no se desconectan otros tiles transitables al añadir los dos personajes.

## Estado guardado

Se añaden cuatro flags permanentes previamente sin uso, sin cambiar el tamaño del guardado ni los bits del prólogo:

| Flag | Bit | Estado |
| --- | --- | --- |
| `FLAG_LEGACY_FIELD_ASSIGNED` | 0x024 | Encargo aceptado |
| `FLAG_LEGACY_FIELD_OBSERVED` | 0x025 | Observación de Zigzagoon completada |
| `FLAG_LEGACY_FIELD_REPORTED` | 0x026 | Informe entregado en el anexo |
| `FLAG_LEGACY_FIELD_WAITED` | 0x027 | Se eligió esperar; sin este bit tras observar significa dejarle paso |

La observación no se repite para cambiar la respuesta y el informe no concede objetos o recompensas repetibles. La amistad y el futuro Vínculo individual no se modifican: estas son decisiones narrativas guardadas. Se conservan los textos del prólogo; sus únicos cambios conectan el investigador y el registro con esta misión. El nuevo script también está protegido frente a importaciones de traducciones y verificado por hash.

## Comprobaciones

```bash
python3 -m unittest discover -s tools/legacy_story -p 'test_*.py' -v
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py' -v
python3 tools/legacy_localization/check_protected_texts.py
python3 tools/legacy_localization/check_text_layout.py
make -j2 -O all
```

Hay 19 pruebas de historia (nueve del prólogo y diez de campo) y 22 de localización: 41 en total. El intérprete de pruebas ejecuta el flujo de los scripts para comprobar acceso, rechazo/aceptación, ambos pares de decisiones, consejos, repetición, entrega, registro y transición. No emula el motor GBA. El control de ancho valida 809 líneas, incluidas 121 de la misión nueva.

Compilación local ARM GCC 13.2.1 aprobada: EWRAM 226 416 B (86,37 %), IWRAM 28 376 B (86,60 %), ROM 26 783 660 B (79,82 %).

La comprobación visual del nuevo tramo, los encuentros durante el recorrido y el guardado/carga en mGBA siguen pendientes.

## Prueba manual y actualización de la ROM

Guardar normalmente desde el menú del juego antes de actualizar. Se puede mantener mGBA abierto durante el desarrollo del código. Al recompilar la ROM en la laptop, cerrar primero la ROM cargada (o mGBA), actualizar y compilar, volver a abrir `pokeemerald.gba` y elegir Continuar. El guardado dentro del juego es el punto de continuidad para probar la nueva versión.

Con una partida que ya completó Poochyena: hablar con el investigador del anexo y aceptar el encargo. Con una partida anterior: completar primero la observación inicial. Ir a la Ruta 102 por las rutas existentes, hablar con el investigador junto a las bayas y con Zigzagoon. Volver al anexo, entregar el informe, consultar el libro, salir de la ruta y regresar para comprobar el movimiento. Guardar/cargar y comprobar que las decisiones y el informe continúan registrados. Probar la otra respuesta con una copia separada de la partida.

## Continuación implementada

Tras entregar este informe y resolver el evento original de DEVON, el guía de la zona sur de Bosque Petalia permite visitar el [claro de investigación](FOREST_CLEARING.md). Las notas y decisiones de Ruta 102 se conservan.
