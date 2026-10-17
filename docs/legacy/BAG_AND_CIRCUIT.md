# Mochila y Circuito de los Lazos

## Mochila: primera fase compatible

Las pilas de la mochila pasan de 999 a 9.999 unidades. Se conservan los
campos, offsets, cifrado y tamaños de guardado. El PC conserva 999 unidades
por pila y la Pirámide conserva su límite propio. La interfaz usa cuatro
dígitos para las cantidades de mochila. Las ventanas de compra y venta se
ensanchan para separar cantidad y precio; los totales de venta se muestran
completos aunque superen el máximo de la cartera (que sigue en 999.999). Los totales de varias pilas se
saturan en 65.535 al consultar la API de 16 bits, sin modificar los objetos
reales ni desbordar el contador. El cálculo de compras usa 32 bits antes
de aplicar el máximo para evitar truncar el presupuesto.

Se corrige la consulta de espacio de bayas y MT/MO para respetar su pila
única: un hueco vacío no hace aceptable una entrega si su pila está llena.
Una asignación temporal fallida rechaza la entrega sin alterar el inventario.

La [ampliación de huecos](BAG_EXTENSION.md) ya añade espacio adicional sin
mover los bolsillos originales: 254 objetos, 62 objetos clave, 32 Poké Balls,
128 MT/MO y 78 bayas. Las partidas anteriores se cargan con la extensión
vacía; guardar dentro del juego conserva el formato nuevo. Los kits de
prueba añaden 99 unidades y reservan ocho huecos. Sigue siendo capacidad
finita; las pilas de bayas y MT/MO conservan su máximo de 9.999.

## Circuito opcional con historia propia

El Circuito de los Lazos reúne a entrenadores y equipos de distintas regiones
para estudiar cooperación, continuando la investigación de Abedul. Participar
no es requisito para viajar, conseguir medallas ni avanzar en la campaña.

Primer capítulo implementado en Ciudad Plateada:

- Un investigador de campo explica el circuito junto al puesto de llegada.
- Brock ofrece la exhibición al hablar de nuevo tras conseguir la Medalla Roca
  y completar la primera observación de Poochyena en el anexo de Abedul.
- Equipo: Golem 60, Crobat 60 y Steelix 61. Se puede rechazar y regresar.
- Una derrota permite otro intento; la victoria registra la exhibición con
  el flag del entrenador 857, dentro del máximo existente de 864.
- Tras ganar, Brock comenta el intercambio de notas con Abedul. No concede
  otra medalla, no consume objetos y no modifica decisiones anteriores.
- Es un encuentro único por ahora; no hay revancha repetible ni premios.

Tras ganar ambas exhibiciones, el escritorio de investigación del anexo de
Abedul ofrece revisar las notas de Brock y Misty. Es una síntesis opcional
sobre confianza y adaptación entre Hoenn y Kanto. Rechazar la revisión
continúa con la investigación de campo habitual; aceptarla permite volver
a leerla sin premios ni flags adicionales. La partida determina su acceso
mediante las dos victorias ya registradas.

Continuación del circuito:

1. Misty: su gimnasio y exhibición independiente ya están implementados en
   el [sector inicial de Celeste](CERULEAN.md). La misión de rescate acuático
   continúa como propuesta pendiente.
2. Ash: encuentro avanzado con Pikachu, accesible al cerrar varios capítulos;
   equipo y nivel pendientes de decidir. No condiciona el desenlace principal.
3. Johto: compartir los resultados y enfrentar diferencias entre amistad,
   entrenamiento y confianza. Los participantes se decidirán al crear la región.

La trama mantendrá a Mewtwo como personaje del postgame, no como antagonista.
No presentar referencias a futuras ciudades como viajes ya disponibles.

## Verificación

```bash
python3 -m unittest discover -s tools/legacy_inventory -v
python3 -m unittest discover -s tools/legacy_story -p 'test_*.py'
python3 -m unittest discover -s tools/legacy_localization -p 'test_*.py'
python3 tools/legacy_localization/check_text_layout.py
python3 tools/legacy_localization/check_protected_texts.py
make -j2 -O all
```

Las pruebas de interfaz comprueban el ancho de cuatro dígitos, la separación
de cantidad y precio, y que las ventanas ampliadas no se solapen en VRAM.
El ensayo del inventario compila las funciones C reales con un fixture del
host: pilas 999/9.999, desborde a otra pila, rechazo atómico, bayas/MT,
límite del PC y saturación de totales. No emula GBA ni el cifrado del guardado.
Las pruebas de eventos comprueban requisitos, cancelación, derrota, victoria,
repetición, conservación de flags y acceso al investigador sobre metatiles.

Pendiente en mGBA, usando una copia de la partida: revisar cantidades de
cuatro dígitos en mochila, tienda y venta; guardar/cargar objetos; visitar
al investigador; perder y ganar la exhibición y confirmar su registro tras
cargar. La partida original y su estado del emulador no se editan.
