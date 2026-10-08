# Pokémon Legacy: recuperación y localización

## Estado comprobado el 8 de octubre de 2026 (UTC)

- Repositorio: `murcafes94/Pokemon-hack`; rama de trabajo: `develop`.
- Punto inicial: `932856499097a4b0e009aa6fb56399a91f16b967` (`Initialize Pokemon Legacy`).
- `main` y `develop` tienen el mismo contenido y el mismo único commit.
- El clon inicial estaba limpio, con 35 614 archivos versionados.
- No había flujos en `.github/workflows`; la API de Actions devolvió cero ejecuciones, tanto globalmente como para `develop`.
- No hay archivos `.c` ni recursos originales `.png`. Solo hay 19 cabeceras `.h`, principalmente tablas generadas. Faltan `Makefile`, `charmap.txt`, fuentes del motor, scripts de diálogo y fuentes de las herramientas.
- `make -n` falla: `No targets specified and no makefile found`.
- Hay objetos, dependencias, datos convertidos, herramientas ejecutables y una ROM previa. Su existencia no prueba que esta copia se pueda recompilar.
- Los `.d` hacen referencia a 25 850 rutas de dependencias; 24 357 no existen en esta copia. Este recuento incluye recursos originales y rutas generadas, no es una lista exacta de fuentes a recuperar.

## Recuperación creada

La rama remota `recovery/develop-93285649` conserva exactamente el commit inicial. No se borraron ni reemplazaron archivos originales. No ejecutar `make clean`, `git clean`, `git reset --hard` ni sustituir el árbol con otra base.

Huellas originales SHA-256:

```text
pokeemerald.gba 47e2dcd10d29224b96a1974eceaa273c6a358bfa181af16cc4c1bb4f06048b4c
pokeemerald.sav b5a41c3758763bbec72769fab4a2533bf2db0b6312d93d25a695f9e4b9e02260
```

Se añadió una comprobación de disponibilidad de fuentes. El workflow fallará con un diagnóstico explícito mientras falten fuentes; no compila ni modifica la ROM. Cuando se recupere el proyecto habrá que configurar y probar la compilación real desde un checkout aislado.

## Obtener la copia original desde Linux Mint

La carpeta local `~/PokemonLegacy` no está disponible en este entorno. Crear un archivo nuevo con los fuentes y el historial, sin tocar la carpeta de trabajo. El archivo temporal usa un nombre único:

```bash
set -e
cd "$HOME/PokemonLegacy"
git status --short --branch
git log -5 --oneline
test -f Makefile
test -f src/main.c
LEGACY_EXPORT=$(mktemp "$HOME/PokemonLegacy-fuentes-XXXXXX.tar.gz")
tar --exclude='./build' --exclude='./pokeemerald.gba' \
    --exclude='./pokeemerald.elf' --exclude='./pokeemerald.map' \
    --exclude='./pokeemerald.sav' \
    -czf "$LEGACY_EXPORT" .
printf 'Archivo para adjuntar: %s\n' "$LEGACY_EXPORT"
```

El archivo incluye `.git`, fuentes y modificaciones sin commit. Revisarlo antes de compartir por si contiene credenciales u otros datos personales. Adjuntar también `~/PokemonLegacy_WIP` si sigue conteniendo documentos o herramientas no reintegrados. No subir únicamente ROMs o archivos ignorados por Git.

## Referencia técnica consultada

`https://github.com/ivaantxo/Pokeemerald-Base-Hispana`

Commit consultado: `74c8121ffd01a27b349975693e18537dade38b34`. Su README identifica la base como RHH pokeemerald-expansion 1.15.0. Esta referencia no confirma qué versión usa Legacy. No se importó ningún archivo ni se asumió compatibilidad de estructuras.

## Integración segura pendiente de recuperar los fuentes

1. Revisar el archivo original, su Git, cambios locales, ramas anteriores y respaldos; crear recuperación antes de integrarlo.
2. Comparar por ruta y contenido con el snapshot actual. Preservar los archivos exclusivos y revisar cada conflicto; recuperar primero lo que falta.
3. Identificar versión y commit real del motor; compilar en una copia aislada sin reutilizar objetos antiguos. Registrar toolchain y SHA-256 del resultado.
4. Inventariar los textos de Legacy y protegerlos de reemplazos automáticos. Comparar Base Hispana a una revisión fija y usar traducciones solo para textos equivalentes. Revisar manualmente textos propios.
5. Validar variables, etiquetas, controles, terminadores, caracteres acentuados, fuentes gráficas y ancho de ventanas. Revisar menús, combate, objetos, Pokédex, diálogos, tutoriales y textos gráficos.
6. Compilar y comprobar en emulador introducción, partida nueva, guardado/carga y escenas propias. No declarar localización completa hasta revisar cobertura y presentación.

Después de estabilizar esta base: Hoenn → Kanto → Johto, 24 medallas, Vínculo/Pokémon acompañante, crafting y Proyecto Génesis. Este diagnóstico no confirma la implementación de esas funciones.
