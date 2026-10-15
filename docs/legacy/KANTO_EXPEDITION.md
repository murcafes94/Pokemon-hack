# Primer recorrido entre Hoenn y Kanto

Este bloque añade una expedición de cuatro mapas nativos, no la región completa de Kanto. Hoenn conserva sus mapas y eventos. Johto y las medallas 9–24 todavía no están implementados.

## Viaje y recorrido

Después de superar la Liga de Hoenn (`FLAG_SYS_GAME_CLEAR`), hablar con el nuevo marinero en (5, 12) dentro del puerto de Ciudad Calagua. Confirmar el viaje conserva equipo, inventario, dinero, Pokédex y registros. Se llega al puesto costero junto a Pueblo Paleta.

El edificio de llegada usa el layout nativo del puerto, con capitán de regreso, investigador y tienda (Ultra Ball, Hiperpoción, Cura Total, Máximo Repelente y Revivir). La salida conduce a un mapa nuevo de Ruta 1, de 24 × 32 metatiles. Su conexión norte conduce al puesto de Ciudad Verde, de 24 × 24. Allí, un guía permite entrar a la estación, que usa el layout nativo del anexo.

Los dos terrenos exteriores fueron construidos con metatiles y recursos ya presentes en el repositorio. No son reconstrucciones completas de las localidades originales. Los mapas de Rojo Fuego no se habilitan indiscriminadamente: sus eventos y flags no funcionan como una campaña de Esmeralda sin adaptar.

Los mapas nuevos declaran `region: REGION_KANTO` y `legacy_game_version: emerald`. El generador permite esa inclusión explícita sin activar los demás mapas de Kanto en la ROM de Esmeralda. La prueba ejecuta el generador sobre el catálogo completo para ambos juegos: los nuevos mapas están en Esmeralda y quedan excluidos de Rojo Fuego. El grupo y los layouts se añaden al final de las listas, conservando los identificadores anteriores.

## Pokémon y combate

La Ruta 1 tiene encuentros salvajes de niveles 48–52: Pidgey, Rattata, Pidgeotto, Raticate, Pikachu, Oddish, Meowth, Growlithe y Eevee. Sus 12 slots conservan los pesos del motor. La frecuencia de encuentro terrestre es 18; no representa un porcentaje por paso.

Pidgey y Rattata visibles permiten dos observaciones opcionales e independientes. Se pueden rechazar, aceptar después y completar en cualquier orden. Se entrega el informe en la estación una sola vez y se consulta en su libro. No concede una medalla ni altera el estudio de Hoenn. Eevee permanece visible en el puesto de Ciudad Verde.

Marcos ofrece un combate opcional: Pidgeot y Raticate al 55, Raichu al 56, con cuatro movimientos explícitos por Pokémon. Utiliza el ID 855, el primero de los nueve espacios de entrenador reservados en esta base. El máximo sigue en 864 y no desplaza las flags del sistema ni cambia la estructura del guardado. El resto de los gimnasios requerirá planificar más espacio de entrenadores antes de añadir sus equipos.

## Curación, regreso y guardado

Entrar a la estación establece un punto nuevo de regreso en (6, 8). La enfermera cura el equipo y establece el mismo punto. El registro de curación se añade al final de su tabla, sin cambiar los IDs existentes. El nuevo destino no usa la escena automática de Centro Pokémon, que requiere una disposición específica de enfermera y máquina: tras perder, se vuelve al punto de la estación.

El capitán del puerto permite volver a Ciudad Calagua. Al regresar, el punto de recuperación se restablece a esa ciudad para evitar volver a Kanto tras una derrota en Hoenn.

| Flag | Bit | Uso |
| --- | --- | --- |
| FLAG_LEGACY_KANTO_VISITED | 0x4AD | Viaje realizado |
| FLAG_LEGACY_KANTO_PIDGEY | 0x4AE | Primera nota |
| FLAG_LEGACY_KANTO_RATTATA | 0x4AF | Segunda nota |
| FLAG_LEGACY_KANTO_REPORTED | 0x4BD | Informe entregado |

0x4BD estaba sin uso en los scripts de ambas bases (FLAG_UNUSED_0x4BD / FLAG_0x4BD). Los bits 0x4B0–0x4BC corresponden a líderes de Rojo Fuego y no se reutilizan. La estructura del guardado y los bits de los capítulos anteriores permanecen iguales.

## Español y validación

Se traducen 207 nombres de la tabla regional por identificador, desde la referencia Base Hispana ya acreditada en LOCALIZATION_ES.md, y se corrige además «Prado de Isla Inta», que seguía en inglés en esa referencia: 208 nombres en total. Las posiciones, tamaños e IDs de las secciones permanecen iguales. Los textos de la expedición tienen control de ancho y protección por hash frente al importador.

Las pruebas ejecutan requisitos de viaje, cancelación, las observaciones en ambos órdenes, repetición, entrega y consulta, punto de recuperación, regreso y preservación de flags. Los recorridos se calculan sobre los metatiles binarios de los cuatro mapas y del puerto de Hoenn. La nueva batalla y los encuentros también se verifican en los datos, sin emular GBA.

La comprobación visual en mGBA sigue pendiente: viaje con una partida campeona, sprites y paletas, cruces entre mapas, tiendas, combate de Marcos, captura, derrota y regreso, Teletransporte, guardado/carga y regreso a Hoenn. Las pruebas de scripts no sustituyen esa comprobación.

## Vuelo y navegación regional

En Esmeralda, Pueblo Paleta utiliza una llegada exterior en Ruta 1 (11, 29), cerca del puerto, y Ciudad Verde una llegada exterior en el puesto (12, 18). Son entradas nuevas añadidas al final de la tabla de ubicaciones; no desplazan los destinos de recuperación anteriores. La estación sigue siendo el punto de recuperación por derrota y Teletransporte.

El primer viaje habilita Paleta; entrar al puesto de Ciudad Verde o a su estación habilita Verde mediante `FLAG_LEGACY_KANTO_VIRIDIAN_VISITED` (0x4BE). No se concede la MO ni se omiten sus requisitos habituales. Las ciudades todavía sin adaptar permanecen bloqueadas para Vuelo. La compilación Rojo Fuego conserva sus destinos y flags originales.

Las pruebas compilan las funciones C reales de selección y destino para las dos bases, verifican permisos antes/después de visitar y comprueban el terreno de aterrizaje, sin personajes ni tiles de warp. «Legacy rápido» permite llegar al marinero de Calagua, regresar a la estación visitada y consultar el registro de Kanto.

## Trabajo pendiente para el juego completo

1. Convertir el puesto inicial en localidades completas de Kanto, conectar sus rutas y adaptar eventos/gimnasios.
2. Diseñar Johto con sus localidades, interiores, rutas y eventos.
3. Implementar registro y visualización de 24 medallas sin desplazar el guardado existente.
4. Completar español en diálogos, interfaz y fuentes generadas; seguir verificando ventanas en juego.
5. Integrar Vínculo y encuentros de legendarios en la historia. Que una especie se pueda crear desde depuración no significa que sea obtenible durante la campaña.

Los legendarios actuales conservan sus efectos, datos y encuentros originales; este bloque no añade ni elimina encuentros legendarios.
