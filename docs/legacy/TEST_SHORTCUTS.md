# Legacy rápido: atajos de prueba

## Abrir el menú

En el mapa, mantener el botón **R de GBA** y pulsar **START**. Seleccionar la primera opción, **Legacy rápido…**. Son botones de GBA: en mGBA se utilizan las teclas que tengan asignadas, no necesariamente las letras R o S del teclado.

Está disponible con la compilación habitual `make -j2`, que ya habilitaba el menú de depuración de esta base. No hace falta `make debug` ni introducir códigos GameShark. `make release` desactiva el acceso y excluye los scripts rápidos nuevos.

## Opciones

| Opción | Resultado |
| --- | --- |
| Elegir objeto… | Generador existente: elegir ID y cantidad. Muestra nombre e icono y admite IDs de cuatro cifras. |
| Crear POKéMON… | Generador existente: elegir especie y nivel. Usa equipo o PC según las reglas normales. |
| Curar equipo | Curación mediante la función de depuración existente. |
| Kit de prueba | Tras confirmar: 20 Poké Ball, 10 Pociones, 10 Antídotos y 5 Repel. Informa si no cabe todo. |
| Ir al anexo | Viaje a la entrada del anexo, después de completar el encargo inicial de Abedul. |
| Ir a RUTA 102 | Viaje junto al investigador, después de aceptar su encargo. |
| Ir al bosque | Viaje junto al guía, después del informe de Ruta 102 y el evento original de DEVON. |
| Ir al claro | Viaje a su entrada, después de aceptar el estudio del claro y resolver DEVON. |
| Ir al puerto | Acceso al marinero de Calagua, tras superar la Liga de Hoenn. |
| Ir a estación | Acceso a la estación de Kanto, tras visitar Ciudad Verde y superar la Liga. |
| Registro KANTO | Consulta las notas de Kanto después del primer viaje, sin modificar flags. |
| Ver registro | Consulta el libro sin alterar el progreso ni viajar. |
| Repetir claro… | Tras confirmar, borra únicamente las dos observaciones del claro, sus respuestas y su informe. Conserva el encargo aceptado y los capítulos anteriores. |

En los selectores numéricos: arriba/abajo cambian el valor y izquierda/derecha el dígito; A confirma y B cancela. Al salir de los selectores de objeto o Pokémon se vuelve al submenú general Dar objetos de la base. Volver atrás permite abrir Legacy rápido otra vez.

Los generadores de objeto y Pokémon ya no reproducen éxito cuando falla la entrega por falta de capacidad: emiten el sonido de error. El kit utiliza las comprobaciones normales de la mochila. Si se llena durante el kit, conserva los objetos añadidos hasta entonces y detiene las entregas posteriores.

## Partida y pruebas

Los objetos y Pokémon generados, igual que la repetición del claro, se guardan si después se guarda la partida. Para pruebas repetidas conviene usar una copia de la partida normal. Los atajos de viaje no escriben flags para desbloquear destinos ni modifican las medallas.

El menú completo de depuración conserva sus herramientas avanzadas de flags, variables, PC y combates. La sección Legacy agrupa los accesos útiles para el desarrollo actual. No se añade una función de atravesar paredes ni se activa globalmente el acompañante.

## Actualizar sin perder la continuidad

Se puede mantener el juego abierto mientras se desarrolla el código. Antes de sustituir la ROM en la laptop, guardar desde el menú del juego y cerrar la ROM cargada o mGBA. Actualizar y compilar, volver a abrir el mismo archivo ROM y elegir Continuar desde el guardado normal.

```bash
cd ~/PokemonLegacy
# Conservar cualquier cambio local; no forzar si Git informa divergencia.
git pull --ff-only origin develop
make -j2
```

## Comprobaciones

Las pruebas ejercitan confirmación/cancelación, mochila llena, viajes bloqueados/desbloqueados, conservación de flags, consulta del registro y repetición limitada a cinco bits del claro. Dos callbacks C reales se compilan con APIs de almacenamiento simuladas para verificar el resultado ante falta de capacidad. También se compila una condición de ensamblador con TRUE/FALSE simbólicos para comprobar desarrollo y lanzamiento.

Se verificó además el objeto ARM real de scripts en modo normal y con `RELEASE`. La comprobación visual de las ventanas y botones en mGBA queda pendiente.

## Regresar saltando bordes con la Bici Acrobática

Montar la Bici Acrobática, mantener B hasta empezar a brincar en el sitio y pulsar hacia el borde. Ahora se puede saltar un desnivel de un tile en sentido contrario a su bajada habitual. La Bici de Carreras y el movimiento a pie mantienen sus reglas.

Solo se permite sobre tiles de borde direccional, con destino transitable a dos tiles y sin personajes en el borde ni en el lugar de aterrizaje. No permite cruzar paredes, árboles, agua ni salir del mapa. Usa la animación existente de salto de dos tiles. La función real se compila y ejecuta en una prueba nativa con los cuatro sentidos, destinos bloqueados, personajes y terrenos peligrosos. Falta comprobar la animación y los desniveles concretos en mGBA.

## Navegación de Kanto

Se añaden tres entradas a Legacy rápido:

- **Puerto de KANTO:** vuelve al puerto después del primer viaje en barco.
- **Estación de KANTO:** vuelve a la estación después de visitarla o curar allí.
- **Registro de KANTO:** consulta las notas de Kanto después del primer viaje.

Los atajos no activan la condición de campeón ni desbloquean destinos no visitados. La visita y la curación normales marcan el punto de Ciudad Verde para Vuelo; sus aterrizajes son exteriores. Guardar dentro del juego antes de actualizar y probar sobre una copia de la partida.

- **Ir a PLATEADA:** vuelve al puesto de Ciudad Plateada después de visitarlo. No desbloquea medallas ni informes.
