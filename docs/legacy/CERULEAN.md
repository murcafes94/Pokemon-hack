# Ruta 4 y sector inicial de Ciudad Celeste

## Recorrido y servicios

La cámara de Monte Luna conserva su entrada anterior y añade un paso al
nordeste. Conduce a Ruta 4 y permite regresar por el mismo warp. Ruta 4
conecta a pie con el sector inicial de Ciudad Celeste. No hay saltos
obligatorios ni conexiones de un solo sentido. El sendero principal evita
la hierba alta; las zonas de captura tienen encuentros de nivel 56–59.

Celeste es por ahora un puesto exterior con plaza, servicios y el patio
de combate de Misty junto a un estanque decorativo. No representa todavía
la ciudad completa ni añade interiores de casas. El agua del estanque es
inaccesible para evitar bloquear rutas y aterrizajes del jugador.

Entrar en Celeste registra la visita y establece el punto de recuperación
exterior (14, 18). La enfermera cura el equipo y reafirma ese punto. El
vendedor reutiliza la tienda de la expedición, con Ultra Balls, Hiperpoción,
Cura Total, Repelente Máximo y Revivir. No hay entregas gratuitas repetibles.

Visitar el sector habilita su destino en el mapa regional para Vuelo; no
se concede la MO ni se alteran sus requisitos habituales. Aterrizaje y
recuperación comparten un tile seco, accesible y sin NPC ni warp. Las
funciones reales de navegación se prueban para Emerald y Rojo Fuego;
Rojo Fuego conserva su destino y flag propios.

## Misty y Medalla Cascada

Misty espera en el patio al nordeste (21, 7). Permite explorar Celeste sin
medallas nuevas, pero para disputar su desafío pide antes la Medalla Roca.
Su equipo de gimnasio es Staryu 60, Golduck 61 y Starmie 62.

Se puede cancelar, perder e intentarlo de nuevo. Ganar concede una sola
vez la Medalla Cascada. Si el combate quedó registrado antes de completarse
el diálogo, volver a hablar permite recuperar la medalla pendiente.
No modifica las ocho medallas de Hoenn. El registro regional muestra dos
medallas de Kanto y diez de las veinticuatro previstas; la tarjeta original
sigue mostrando las ocho medallas de Hoenn.

## Circuito de los Lazos

Después de la Medalla Cascada, Misty ofrece una exhibición distinta si ya
se completó la exhibición de Brock. Rechazarla o perder no altera las
medallas ni los avances anteriores. Su equipo es Politoed 64, Gyarados 65
y Starmie 66. Ganar registra únicamente ese encuentro, sin otra medalla,
objeto o premio repetible. Al repetir la conversación comenta los resultados.

La investigación compara confianza y adaptación entre los equipos de Hoenn
y Kanto. Las notas regresarán a Abedul. Ash sigue pendiente; no se anuncia
como encuentro disponible ni se bloquea la campaña por este circuito.

## Guardado

Los dos mapas y layouts se añaden al final: los IDs anteriores permanecen.
La lista de curación también se amplía al final. No se cambia el tamaño ni
la distribución del guardado.

| Dato | Espacio reservado |
| --- | --- |
| Visita a Celeste | flag 0x4C1 |
| Medalla Cascada | flag 0x4C2 |
| Misty, gimnasio | entrenador 859 |
| Misty, circuito | entrenador 860 |

Los bits 0x4C1 y 0x4C2 estaban sin usar y se reservan también en la base
Rojo Fuego para evitar colisiones futuras. El máximo existente de 864
entrenadores no se amplía. Quedan los IDs 861–863: antes de completar todos
los gimnasios restantes habrá que rediseñar o ampliar con migración el
registro de entrenadores, sin desplazar flags ya usadas.

## Validación y pendiente de emulador

Las pruebas recorren los metatiles desde la cueva hasta los servicios y
Misty, verifican ida/vuelta de warps, aterrizaje, recuperación, requisitos,
cancelación, derrota, victoria, medalla única, recuperación de la medalla
pendiente, exhibición independiente y conservación de flags anteriores.
Los diálogos propios se verifican por hash y control de ancho.

Los mapas se revisan mediante un render estático de sus tiles y paletas.
No incluye sprites ni animaciones y no sustituye mGBA.

Pendiente en una copia de la partida: salir de Monte Luna por el nordeste,
llegar a Celeste, comprar, curar, guardar/cargar, perder y ganar contra
Misty, comprobar medalla y exhibición, y probar Vuelo, Teletransporte y
Cuerda Huida desde ambas entradas de la cueva. Cargar mediante Continuar;
conservar los respaldos de la partida y de la ROM anteriores.

El siguiente tramo geográfico y los gimnasios posteriores todavía no
están disponibles. La mochila conserva pilas de 9.999; ampliar el número
de objetos diferentes requiere la migración de inventario pendiente.
