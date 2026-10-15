# Primer recorrido entre Hoenn y Kanto

El recorrido actual incluye ocho mapas nativos y el primer gimnasio de Kanto. No representa la región completa: las localidades son sectores iniciales y reutilizan recursos de Hoenn. Hoenn conserva sus mapas y eventos. La Medalla Roca es la novena de la aventura; las medallas 10–24 y Johto siguen pendientes.

## Viaje y recorrido

Después de superar la Liga de Hoenn (`FLAG_SYS_GAME_CLEAR`), hablar con el nuevo marinero en (5, 12) dentro del puerto de Ciudad Calagua. Confirmar el viaje conserva equipo, inventario, dinero, Pokédex y registros. Se llega al puesto costero junto a Pueblo Paleta.

El edificio de llegada usa el layout nativo del puerto, con capitán de regreso, investigador y tienda (Ultra Ball, Hiperpoción, Cura Total, Máximo Repelente y Revivir). La salida conduce a un mapa nuevo de Ruta 1, de 24 × 32 metatiles. Su conexión norte conduce al puesto de Ciudad Verde, de 24 × 24. Allí, un guía permite entrar a la estación, que usa el layout nativo del anexo.

Los dos terrenos exteriores fueron construidos con metatiles y recursos ya presentes en el repositorio. No son reconstrucciones completas de las localidades originales. Los mapas de Rojo Fuego no se habilitan indiscriminadamente: sus eventos y flags no funcionan como una campaña de Esmeralda sin adaptar.

Los mapas nuevos declaran `region: REGION_KANTO` y `legacy_game_version: emerald`. El generador permite esa inclusión explícita sin activar los demás mapas de Kanto en la ROM de Esmeralda. La prueba ejecuta el generador sobre el catálogo completo para ambos juegos: los nuevos mapas están en Esmeralda y quedan excluidos de Rojo Fuego. El grupo y los layouts se añaden al final de las listas, conservando los identificadores anteriores.

## Pokémon y combate

La Ruta 1 tiene encuentros salvajes de niveles 48–52: Pidgey, Rattata, Pidgeotto, Raticate, Pikachu, Oddish, Meowth, Growlithe y Eevee. Sus 12 slots conservan los pesos del motor. La frecuencia de encuentro terrestre es 18; no representa un porcentaje por paso.

Pidgey y Rattata visibles permiten dos observaciones opcionales e independientes. Se pueden rechazar, aceptar después y completar en cualquier orden. Se entrega el informe en la estación una sola vez y se consulta en su libro. No concede una medalla ni altera el estudio de Hoenn. Eevee permanece visible en el puesto de Ciudad Verde.

Marcos ofrece un combate opcional: Pidgeot y Raticate al 55, Raichu al 56, con cuatro movimientos explícitos por Pokémon. Utiliza el ID 855, el primero de los nueve espacios de entrenador reservados en esta base. El máximo sigue en 864 y no desplaza las flags del sistema ni cambia la estructura del guardado. Brock utiliza el ID 856. Los IDs 857–863 permiten otros siete líderes sin cambiar el máximo; añadir entrenadores de ruta y de Johto requerirá planificar capacidad adicional.

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

Las pruebas ejecutan requisitos de viaje, cancelación, las observaciones en ambos órdenes, repetición, entrega y consulta, punto de recuperación, regreso y preservación de flags. Los recorridos se calculan sobre los metatiles binarios de los mapas y del puerto de Hoenn. La nueva batalla y los encuentros también se verifican en los datos, sin emular GBA.

La comprobación visual en mGBA sigue pendiente: viaje con una partida campeona, sprites y paletas, cruces entre mapas, tiendas, combate de Marcos, captura, derrota y regreso, Teletransporte, guardado/carga y regreso a Hoenn. Las pruebas de scripts no sustituyen esa comprobación.

## Vuelo y navegación regional

En Esmeralda, Pueblo Paleta utiliza una llegada exterior en Ruta 1 (11, 29), cerca del puerto, Ciudad Verde una llegada exterior en el puesto (12, 18) y Ciudad Plateada su puesto exterior (12, 18). Son entradas nuevas añadidas al final de la tabla de ubicaciones; no desplazan los destinos de recuperación anteriores. La estación sigue siendo el punto de recuperación por derrota y Teletransporte.

El primer viaje habilita Paleta; entrar al puesto de Ciudad Verde o a su estación habilita Verde mediante `FLAG_LEGACY_KANTO_VIRIDIAN_VISITED` (0x4BE). No se concede la MO ni se omiten sus requisitos habituales. Las ciudades todavía sin adaptar permanecen bloqueadas para Vuelo. La compilación Rojo Fuego conserva sus destinos y flags originales.

Las pruebas compilan las funciones C reales de selección y destino para las dos bases, verifican permisos antes/después de visitar y comprueban el terreno de aterrizaje, sin personajes ni tiles de warp. «Legacy rápido» permite llegar al marinero de Calagua, regresar a la estación visitada y consultar el registro de Kanto.

## Trabajo pendiente para el juego completo

1. Completar las localidades de Kanto, conectar el resto de las rutas y adaptar los otros siete gimnasios.
2. Diseñar Johto con sus localidades, interiores, rutas y eventos.
3. Extender el registro de medallas de Kanto y Johto y crear su visualización de 24 medallas. La primera de Kanto ya se registra aparte de la tarjeta de Hoenn.
4. Completar español en diálogos, interfaz y fuentes generadas; seguir verificando ventanas en juego.
5. Integrar Vínculo y encuentros de legendarios en la historia. Que una especie se pueda crear desde depuración no significa que sea obtenible durante la campaña.

Los legendarios actuales conservan sus efectos, datos y encuentros originales; este bloque no añade ni elimina encuentros legendarios.


## Ruta 2, Bosque Verde y primer gimnasio

Desde el puesto de Ciudad Verde se continúa a pie hacia el norte por Ruta 2 (24 × 24), Bosque Verde (24 × 32) y el sector inicial de Ciudad Plateada (24 × 24). Las conexiones tienen retorno en los dos sentidos y no exigen completar las observaciones opcionales. En Ruta 2 hay encuentros de nivel 50–54 y en Bosque Verde de nivel 51–55, incluidos Pikachu y los insectos propios del bosque.

Ciudad Plateada tiene una enfermera, destino de Vuelo y recuperación exterior en (12, 18), activado al entrar. El gimnasio reutiliza el layout de piedra de Férrica, con Brock y sus recursos gráficos ya presentes en la base. Su edificio exterior utiliza los metatiles nativos del gimnasio. Todavía no son reproducciones completas de las ciudades de Rojo Fuego.

Brock permite cancelar, perder e intentarlo otra vez; tras vencer concede una sola vez la Medalla Roca. Su equipo Legacy es Golem (56), Omastar (57) y Onix (58). Usa el entrenador 856 dentro del máximo existente de 864. La recompensa consulta también su flag de entrenador para recuperar una medalla pendiente si el evento quedó interrumpido tras la victoria.

`FLAG_LEGACY_KANTO_PEWTER_VISITED` (0x4BF) habilita el destino; `FLAG_LEGACY_BADGE_BOULDER` (0x4C0) registra la novena medalla. Ambas posiciones estaban sin uso y se reservan en las dos bases. No se cambia la estructura del guardado ni ninguna de las ocho flags de medallas de Hoenn. El libro de Kanto y «Registro KANTO» muestran si la Medalla Roca está pendiente o conseguida; la tarjeta normal sigue mostrando las ocho medallas de Hoenn.

Pruebas: recorrer las conexiones y retornos sobre los metatiles, acceso a la puerta y a Brock, cancelación, derrota, victoria, repetición, registro de medalla, curación, destino de Vuelo y encuentros. La ejecución de combate en GBA, ventanas, sprites, transiciones, derrota y guardado/carga aún deben comprobarse en mGBA.
