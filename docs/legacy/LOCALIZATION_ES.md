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
