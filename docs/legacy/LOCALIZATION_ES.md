# Localización española: primera integración validada

## Base y referencia

Base Legacy: `1ec395663ed779449ae6e8f2cf997d3ef97f8769`.
Punto de recuperación remoto: `recovery/develop-before-spanish-1ec39566`.
Referencia: [Pokeemerald Base Hispana](https://github.com/ivaantxo/Pokeemerald-Base-Hispana), revisión fija `74c8121ffd01a27b349975693e18537dade38b34`.

Se importaron 17 367 entradas compatibles y se revisaron 123 destinos de traducción adicionales. Los números cuentan operaciones y destinos, no cadenas únicas ni porcentaje de cobertura.

Se cambiaron únicamente literales de texto de los fuentes originales: menús, objetos, movimientos, habilidades, Pokédex, combates y diálogos. Los identificadores, controles de juego, estadísticas, tablas de efectos, mapas, gráficos y estructura del guardado se conservaron. La introducción exclusiva de Legacy mantiene su SHA-256 aprobado y está protegida mediante una comprobación de CI.

Se mantienen por ahora el código y el idioma interno de la ROM original. Este cambio no migra idiomas de Pokémon ya guardados ni modifica la identificación de la partida.

## Reglas de integración

- Comparar símbolos, índices y campos equivalentes, sin copiar archivos de código completos de PBH.
- Resolver las descripciones compartidas de PBH como texto, sin importar sus punteros ni estructuras.
- Rechazar controles desconocidos, caracteres no soportados, terminadores distintos y variables incompatibles.
- Conservar los textos españoles previos y proteger explícitamente la introducción.
- Usar `spanish_overrides.json` para textos revisados que requieren ajustes propios: abreviaturas de tipos, menús y mensajes modernos de combate.
- La descripción de Hedor respeta el efecto de retroceso configurado en Legacy, en lugar de la descripción distinta de PBH.

Los campos de tipo tienen un máximo de ocho caracteres. Se usan `Eléctr.` y `Sinies.` sin ampliar estructuras del motor.

## Validación realizada

- Diez pruebas del extractor y del emparejamiento de referencias aprobadas.
- Hash de la introducción comprobado.
- Comparación de fuentes ignorando únicamente literales: el contenido no textual permanece igual.
- Compilación ARM GCC 13.2.1 finalizada con éxito en una copia aislada.
- EWRAM: 226 416 B, 86,37 %; IWRAM: 28 376 B, 86,60 %; ROM: 26 776 248 B, 79,80 %.

La compilación automática en GitHub verifica nuevamente el árbol publicado. Las pruebas visuales en emulador, el ancho de textos con nombres personalizados y las escenas de partida guardada requieren revisión posterior. No considerar esta entrega una localización completa.

## Pendientes identificados

El inventario posterior contiene 28 893 entradas. Un filtro de palabras inglesas detectó 3 129 candidatos en distintos archivos, incluidos contenido de Kanto/FRLG, funciones avanzadas del motor y algunos diálogos. Es un filtro heurístico: tiene falsos positivos y no detecta todo el inglés.

PBH conserva partes de los textos en inglés y su implementación difiere de Legacy en algunos símbolos. No se rellenaron esos casos con reemplazos automáticos de palabras. Los textos gráficos tampoco se sustituyeron en esta fase.

La lista de recuentos por archivo y los motivos de rechazo quedan en `tools/legacy_localization/spanish_import_summary.json`. El CSV anterior se conserva como captura histórica; el workflow exporta el inventario vigente.

## Herramientas

```bash
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py' -v
python3 tools/legacy_localization/check_protected_texts.py
python3 tools/legacy_localization/inventory.py --output /tmp/legacy-textos.csv
```

`import_reference.py` es una herramienta de comparación; por defecto no modifica fuentes. La aplicación requiere `--apply`, una copia de la revisión exacta de PBH y `--report`. Después de una importación, reaplicar las excepciones revisadas mediante `apply_overrides.py` y volver a compilar. No ejecutar importaciones sobre cambios locales sin revisar y respaldar el estado de Git.

Próximas tareas: completar los pendientes por archivo, revisar textos gráficos y probar visualmente introducción, menús, combate, mochila, Pokédex, diálogos y guardado/carga.

## Segunda revisión: PC, equipo, bayas y Cúpula Batalla

Punto de recuperación: `recovery/develop-before-spanish-followup-b747f038`.

Se añadieron 510 operaciones de importación compatibles y 212 traducciones/ajustes por texto completo. La detección ahora reconoce entradas anónimas de menús y relaciona los identificadores nuevos de bayas de Legacy con la tabla anterior de PBH, conservando la estructura y los efectos actuales.

Se corrigieron ayudas y opciones de las cajas del PC, mensajes del menú de equipo, mensajes de combate pendientes y textos de la Cúpula Batalla. Las descripciones de bayas se traducen y adaptan al espacio disponible. Se detectaron 52 líneas de bayas que excedían los 200 píxeles; se revisaron las dos líneas de 39 fichas y se comprobó su ancho usando la fuente real del juego.

`check_text_layout.py` valida 152 líneas estáticas de las fichas de bayas y del menú principal del PC. Se ejecuta en CI, junto con quince pruebas y la protección de la introducción. Este control no sustituye la revisión visual de ventanas con variables o nombres personalizados.

Compilación local de la revisión: EWRAM 226 416 B, IWRAM 28 376 B, ROM 26 776 172 B (79,80 %). Los cambios de fuentes siguen limitados a literales; no se modifican estadísticas, flags, mapas ni estructuras de guardado.

`spanish_exact.json` contiene traducciones completas revisadas para tablas sin símbolo propio y casos con símbolos locales repetidos en funciones distintas. Aplicarlas mediante `apply_exact.py` conserva variables, terminadores y comentarios; no hace sustituciones de palabras dentro de frases.

Tras cualquier importación de referencias, reaplicar ambos grupos de excepciones:

```bash
python3 tools/legacy_localization/apply_overrides.py
python3 tools/legacy_localization/apply_exact.py
python3 tools/legacy_localization/check_text_layout.py
```

El inglés restante continúa pendiente; su recuento actualizado aparece en la sección `followup` del informe de importación.

## Tercera revisión: evaluaciones de Oak

Base: `b68d4bbba1162aeba1e2d95f683d7ad13584b3d7`.
Punto de recuperación: `recovery/develop-before-oak-spanish-b68d4bbb`.

Se tradujeron los 24 bloques de evaluación de la Pokédex de Oak en `data/text/pokedex_rating.inc`, incluidos los recuentos nacional/regional y los mensajes de finalización. Se conservaron las variables, el control de fuente, los terminadores y las referencias a recompensas existentes. Las evaluaciones españolas de Abedul permanecen idénticas. Esta revisión traduce contenido existente de Kanto; no implementa su progresión regional.

`apply_exact.py` reconoce ahora bloques `.string` por etiqueta, aplica únicamente traducciones de texto completo y rechaza explícitamente la introducción protegida de Legacy. Las pruebas cubren conservación de etiquetas y comentarios, idempotencia y rechazo de variables/terminadores incompatibles. Las sustituciones idénticas ya no cuentan como cambios ni reescriben archivos.

Validación: 18 pruebas aprobadas, hash de la introducción intacto y comparación del archivo de evaluaciones con los literales eliminados sin diferencias. El control de ancho comprueba ahora 216 líneas: las 152 anteriores y 64 líneas estáticas de Oak, con un límite conservador de 208 píxeles. Las líneas con variables requieren comprobación adicional en emulador.

Compilación local ARM GCC 13.2.1 aprobada: EWRAM 226 416 B (86,37 %), IWRAM 28 376 B (86,60 %), ROM 26 776 020 B (79,80 %). Siguen pendientes otros diálogos en inglés, textos gráficos y revisión visual general.

## Cuarta revisión: objetos pendientes y laboratorio de Oak

Base: `d7320b5058010100c172f64395745584b51ba0b8`.
Punto de recuperación: `recovery/develop-before-items-pallet-es-d7320b50`.

Se revisaron 106 bloques de texto: 60 del laboratorio de Oak en Pueblo Paleta y 46 en la tabla de objetos. En objetos se tradujeron 43 descripciones pendientes en inglés, se ajustaron dos descripciones españolas largas y se tradujo el nombre del enlace de las cajas del PC. Hay 98 nuevas parejas de texto completo en `spanish_exact.json`; algunas se aplican en más de una variante de configuración. Los recuentos no son un porcentaje de localización completa.

Los diálogos cubren selección de inicial, rival, entrega del paquete, obtención de Pokédex y Poké Balls, instrucciones de captura, mensajes de los ayudantes y ampliación a Pokédex Nacional. Se traduce el contenido FRLG existente sin cambiar flags, movimientos, recompensas, elección de inicial ni acceso a Kanto. Los nombres propios originales se conservan; esta revisión no sustituye esos eventos por la futura historia de Legacy.

Las descripciones de abonos mantienen las dos ramas de configuración, incluido el aviso cuando el suelo no admite su uso. Las megapiedras conservan especie y efecto. Incienso Marino, Incienso Suave, Repartir Exp., Zidra y Buceo mantienen sus diferencias configurables. La descripción moderna de Zidra indica un cuarto de los PS máximos, conforme a `holdEffectParam = 25`; la antigua conserva 30 PS. No se importaron efectos ni código de otra base.

La comprobación de ancho se amplía a 594 líneas. `layout_targets.json` registra 34 campos de descripción de objetos (incluyendo sus variantes), limitados a 109 píxeles y tres líneas, y todos los textos del laboratorio, limitados a 208 píxeles. La ventana de mochila tiene 14 tiles (112 píxeles) y el texto comienza en x=3. El laboratorio reserva 42 píxeles por nombre de jugador/rival (siete caracteres del teclado latino actual, máximo de seis píxeles cada uno) y 72 por nombre de especie (doce caracteres). `{POKEBLOCK}` se mide mediante los cinco códigos de glifo definidos en el charmap, sin asumir el ancho de la palabra escrita. Los controles sin medida conocida hacen fallar los nuevos objetivos de comprobación.

Se añadió caché de medidas de fuente y cuatro pruebas para variables, nombres repetidos, controles desconocidos y símbolos compuestos. Validación: 22 pruebas aprobadas; introducción protegida intacta; únicamente literales modificados en ambos fuentes de juego; variables y terminadores conservados; reaplicación sin cambios. Compilación local ARM GCC 13.2.1 aprobada: EWRAM 226 416 B (86,37 %), IWRAM 28 376 B (86,60 %), ROM 26 775 832 B (79,80 %).

La revisión visual en emulador y los restantes textos ingleses siguen pendientes. Hoenn → Kanto → Johto, 24 medallas, Vínculo/acompañante, crafting y Proyecto Génesis continúan como fases posteriores a la estabilización española; no se consideran implementados por esta traducción.
