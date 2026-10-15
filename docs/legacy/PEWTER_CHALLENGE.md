# Kanto: Ruta 2, Bosque Verde y desafío de Brock

## Recorrido

Tras superar la Liga de Hoenn, viajar desde Ciudad Calagua al puesto costero de Pueblo Paleta. Avanzar por Ruta 1 hasta Ciudad Verde. Desde allí el sendero norte conecta Ruta 2, Bosque Verde y el puesto de Ciudad Plateada; es posible volver caminando en todo momento.

Los nuevos exteriores son mapas nativos, con tiles existentes del proyecto. El puesto de Plateada incluye la fachada del gimnasio de Rustboro y su interior como recursos temporales. El trazado y los habitantes corresponden al nuevo desafío de Legacy; no es una reconstrucción completa de Ciudad Plateada ni del Bosque Verde original.

## Encuentros y servicios

Ruta 2 y Bosque Verde tienen doce entradas de encuentros cada uno, niveles 50–54. Entre las especies hay Nidoran, Abra, Pikachu, Caterpie, Weedle, Scyther y Pinsir. El Pikachu visible del bosque permite una observación ambiental; no se captura ni entrega como regalo al hablarle.

La enfermera cura el equipo. Entrar al puesto marca su punto de regreso tras una derrota. Vuelo y «Ir a PLATEADA» se habilitan únicamente después de visitarlo. La entrada del gimnasio es una puerta funcional; el guía también permite entrar mediante diálogo.

## Desafío y medalla

Brock exige superar la Liga de Hoenn y entregar el primer informe de Kanto (Pidgey y Rattata) en la estación de Ciudad Verde. Ofrece un combate opcional contra Golem nivel 58, Kabutops nivel 58 y Onix nivel 60. Cancelar permite seguir explorando. Una derrota no entrega la medalla.

Ganar registra `FLAG_LEGACY_BADGE_BOULDER` (0x4C0): primera medalla de Kanto, novena de la aventura. Se consulta hablando con el investigador del puesto o nuevamente con Brock. No se sobrescriben las ocho medallas de Hoenn. La tarjeta de entrenador todavía muestra el formato original de ocho medallas; la pantalla gráfica de 24 medallas sigue pendiente.

Se reserva también `FLAG_LEGACY_KANTO_PEWTER_VISITED` (0x4BF). Ambos bits estaban libres en las tablas base de Emerald y FireRed. Brock usa el entrenador 856 y conserva el límite de 864; no cambia el tamaño de los bloques de guardado. No altera el Brock del recorrido independiente de FireRed.

## Verificación

Las pruebas recorren conexiones en ambos sentidos, terrenos, accesos, puerta y líder del gimnasio, encuentros, restricciones del desafío, cancelación, derrota, victoria, repetición, lectura del registro y conservación de medallas de Hoenn. La prueba C de las funciones reales de Vuelo cubre Emerald y FireRed.

Pendiente: comprobar visualmente el recorrido y combate en mGBA con una copia de la partida. Guardar desde el menú del juego antes de actualizar; evitar cargar un estado rápido de otra compilación.

## Continuación pendiente

Ruta 3, Monte Moon, Ciudad Celeste y el resto de Kanto; Johto; las medallas 10–24; pantalla de 24 medallas; trama completa de Proyecto Génesis y sistema numérico de Vínculo. Esta entrega es un tramo adicional jugable, no el juego terminado.
