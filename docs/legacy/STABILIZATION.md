# Estado de estabilización de Pokémon Legacy

## Base recuperada

La rama `recovery/legacy-restored-af8022787`, inicialmente en `5821389c5fca77f6d00ce2cd3e2547f370f23409`, conserva los fuentes recuperados del commit raíz `af8022787` y los cinco documentos/herramientas guardados por Fabri. El árbol de la raíz, comprobado en la laptop, es `45290062e1ed79a38326906d350300fb536aad30`. Ese identificador corresponde a un árbol Git, no a un commit.

`develop` remoto todavía conserva la copia anterior. No se debe fusionar esa copia como si fuese la base correcta. Antes de cambiar la referencia remota, preservar su punta actual y comprobar que la rama recuperada contiene los fuentes y todas las modificaciones deseadas.

## Compilación local confirmada el 12 de octubre de 2026

Fabri ejecutó `make -j2` en Linux Mint; terminó con código 0 y generó `pokeemerald.gba`.

| Región de memoria | Uso | Porcentaje |
| --- | ---: | ---: |
| EWRAM | 226 420 B | 86,37 % |
| IWRAM | 28 376 B | 86,60 % |
| ROM | 26 748 816 B | 79,72 % |

Este resultado confirma la compilación local informada; no sustituye las pruebas en emulador ni confirma una compilación limpia en otro entorno.

## Localización

La introducción de `data/text/birch_speech.inc` contiene texto propio de Legacy en español. Debe conservarse al comparar con Base Hispana. Los menús y mensajes de `src/strings.c` y muchos textos del resto del árbol siguen en inglés.

El CSV guardado anteriormente tiene 1 691 entradas de cinco archivos y es una captura histórica incompleta. Se conserva para no perder trabajo; no usarlo como inventario de cobertura actual.

El extractor actualizado incluye cadenas C concatenadas, bloques `.string` y nombres de entrenadores desde los archivos editables `.party`. Excluye comentarios y archivos generados ignorados por Git. Exporta UTF-8 con finales LF, en orden estable. No traduce ni modifica fuentes del juego.

Generar un inventario nuevo sin reemplazar la captura histórica:

```bash
python3 tools/legacy_localization/inventory.py --output /tmp/legacy-inventario-actual.csv
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py' -v
```

En el árbol recuperado se encontraron 28 892 entradas en 807 archivos. Este número cuenta entradas/bloques detectados, no textos únicos, porcentaje traducido ni cobertura total: los textos gráficos y formatos distintos requieren revisión adicional.

El workflow `legacy-build.yml` genera un inventario actualizado como artefacto en cada ejecución y compila Emerald con dependencias ARM. Se activa en `develop`, en la rama recuperada, por PR y manualmente. El workflow original se conserva.

## Mecánicas y dirección del proyecto

- Hoenn: medallas 1–8; Kanto: 9–16; Johto: 17–24.
- Conservar protagonista, equipo, inventario, Pokédex, dinero y Vínculo entre regiones.
- Proyecto Génesis: postgame en las tres regiones; Mewtwo no es el antagonista. Vínculo y decisiones influyen parcialmente en el desenlace.
- El código actual define ocho medallas. El soporte de Pokémon acompañante existe en el motor, con `OW_FOLLOWERS_ENABLED` desactivado; activarlo requiere verificar eventos y movimientos.
- La revisión no confirmó un sistema propio de Vínculo, crafting, campaña de Johto ni Proyecto Génesis implementados. Las coincidencias del movimiento Genesis Supernova no representan el argumento de Génesis.
- Remaster gráfico después de estabilizar la localización: guía visual común, zona piloto y revisión de paletas, mapas, interfaces y sprites para las tres regiones. Probar también en Redmi Pad 2.

## Próximos pasos

1. Confirmar el resultado del nuevo workflow desde un checkout limpio.
2. Sincronizar `develop` con la rama recuperada con puntos de recuperación y comprobación del estado remoto.
3. Fijar una revisión de Base Hispana, comprobar compatibilidad del motor y proteger los textos exclusivos de Legacy.
4. Traducir y validar por bloques: símbolos, variables, controles, acentos, anchos y escenas en emulador.
5. Revisar presupuesto de memoria y compatibilidad del guardado antes de ampliar medallas y Vínculo.
