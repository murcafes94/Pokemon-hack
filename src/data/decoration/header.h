const struct Decoration gDecorations[] =
{
    [DECOR_NONE] =
    {
        .id = DECOR_NONE,
        .name = _("MESA PEQUEÑA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DESK,
        .price = 0,
        .description = COMPOUND_STRING(
            "Mesa pequeña para\nuna sola persona."
            ""),
        .tiles = DecorGfx_SMALL_DESK,
        .icon = {gItemIcon_QuestionMark, gItemIconPalette_QuestionMark},
    },

    [DECOR_SMALL_DESK] =
    {
        .id = DECOR_SMALL_DESK,
        .name = _("MESA PEQUEÑA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DESK,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Mesa pequeña para\nuna sola persona."
            ""),
        .tiles = DecorGfx_SMALL_DESK,
        .icon = {NULL, NULL},
    },

    [DECOR_POKEMON_DESK] =
    {
        .id = DECOR_POKEMON_DESK,
        .name = _("MESA POKéMON"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DESK,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Mesa pequeña con\nforma de POKé BALL."
            ""
            ""),
        .tiles = DecorGfx_POKEMON_DESK,
        .icon = {NULL, NULL},
    },

    [DECOR_HEAVY_DESK] =
    {
        .id = DECOR_HEAVY_DESK,
        .name = _("MESA PESADA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x2,
        .category = DECORCAT_DESK,
        .price = 6000,
        .description = COMPOUND_STRING(
            "Mesa grande de\nacero. Decórala."
            ""
            ""),
        .tiles = DecorGfx_HEAVY_DESK,
        .icon = {gDecorIcon_HeavyDesk, gDecorIconPalette_HeavyDesk},
    },

    [DECOR_RAGGED_DESK] =
    {
        .id = DECOR_RAGGED_DESK,
        .name = _("MESA RÚSTICA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x2,
        .category = DECORCAT_DESK,
        .price = 6000,
        .description = COMPOUND_STRING(
            "Mesa grande de\nmadera. Decórala."
            ""
            ""),
        .tiles = DecorGfx_RAGGED_DESK,
        .icon = {gDecorIcon_RaggedDesk, gDecorIconPalette_RaggedDesk},
    },

    [DECOR_COMFORT_DESK] =
    {
        .id = DECOR_COMFORT_DESK,
        .name = _("MESA CÓMODA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x2,
        .category = DECORCAT_DESK,
        .price = 6000,
        .description = COMPOUND_STRING(
            "Mesa grande de\nhojas. Decórala."
            ""
            ""),
        .tiles = DecorGfx_COMFORT_DESK,
        .icon = {gDecorIcon_ComfortDesk, gDecorIconPalette_ComfortDesk},
    },

    [DECOR_PRETTY_DESK] =
    {
        .id = DECOR_PRETTY_DESK,
        .name = _("MESA BONITA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_DESK,
        .price = 9000,
        .description = COMPOUND_STRING(
            "Mesa enorme de\ncristal. Decórala\ncon muchas cosas."
            ""
            ""),
        .tiles = DecorGfx_PRETTY_DESK,
        .icon = {gDecorIcon_PrettyDesk, gDecorIconPalette_PrettyDesk},
    },

    [DECOR_BRICK_DESK] =
    {
        .id = DECOR_BRICK_DESK,
        .name = _("MESA LADRILLO"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_DESK,
        .price = 9000,
        .description = COMPOUND_STRING(
            "Mesa enorme de\nladrillo. Decórala\ncon muchas cosas."
            ""
            ""),
        .tiles = DecorGfx_BRICK_DESK,
        .icon = {gDecorIcon_BrickDesk, gDecorIconPalette_BrickDesk},
    },

    [DECOR_CAMP_DESK] =
    {
        .id = DECOR_CAMP_DESK,
        .name = _("MESA DE CAMPO"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_DESK,
        .price = 9000,
        .description = COMPOUND_STRING(
            "Mesa enorme de\ntroncos. Decórala\ncon muchas cosas."
            ""
            ""),
        .tiles = DecorGfx_CAMP_DESK,
        .icon = {gDecorIcon_CampDesk, gDecorIconPalette_CampDesk},
    },

    [DECOR_HARD_DESK] =
    {
        .id = DECOR_HARD_DESK,
        .name = _("MESA FUERTE"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_DESK,
        .price = 9000,
        .description = COMPOUND_STRING(
            "Mesa enorme de\npiedra. Decórala\ncon muchas cosas."
            ""
            ""),
        .tiles = DecorGfx_HARD_DESK,
        .icon = {gDecorIcon_HardDesk, gDecorIconPalette_HardDesk},
    },

    [DECOR_SMALL_CHAIR] =
    {
        .id = DECOR_SMALL_CHAIR,
        .name = _("SILLA PEQUEÑA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña para\nuna persona."
            ""),
        .tiles = DecorGfx_SMALL_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_POKEMON_CHAIR] =
    {
        .id = DECOR_POKEMON_CHAIR,
        .name = _("SILLA POKéMON"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña con\nforma de POKé BALL."
            ""
            ""),
        .tiles = DecorGfx_POKEMON_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_HEAVY_CHAIR] =
    {
        .id = DECOR_HEAVY_CHAIR,
        .name = _("SILLA PESADA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde acero."
            ""),
        .tiles = DecorGfx_HEAVY_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_PRETTY_CHAIR] =
    {
        .id = DECOR_PRETTY_CHAIR,
        .name = _("SILLA BONITA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde cristal."
            ""),
        .tiles = DecorGfx_PRETTY_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_COMFORT_CHAIR] =
    {
        .id = DECOR_COMFORT_CHAIR,
        .name = _("SILLA CÓMODA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde hojas."
            ""),
        .tiles = DecorGfx_COMFORT_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_RAGGED_CHAIR] =
    {
        .id = DECOR_RAGGED_CHAIR,
        .name = _("SILLA RÚSTICA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde madera."
            ""),
        .tiles = DecorGfx_RAGGED_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_BRICK_CHAIR] =
    {
        .id = DECOR_BRICK_CHAIR,
        .name = _("SILLA LADRILLO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde ladrillo."
            ""),
        .tiles = DecorGfx_BRICK_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_CAMP_CHAIR] =
    {
        .id = DECOR_CAMP_CHAIR,
        .name = _("SILLA DE CAMPO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde troncos."
            ""),
        .tiles = DecorGfx_CAMP_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_HARD_CHAIR] =
    {
        .id = DECOR_HARD_CHAIR,
        .name = _("SILLA FUERTE"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CHAIR,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Silla pequeña\nde piedra."
            ""),
        .tiles = DecorGfx_HARD_CHAIR,
        .icon = {NULL, NULL},
    },

    [DECOR_RED_PLANT] =
    {
        .id = DECOR_RED_PLANT,
        .name = _("PLANTA ROJA"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_PLANT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Maceta con planta\nde color rojo vivo."
            ""),
        .tiles = DecorGfx_RED_PLANT,
        .icon = {gDecorIcon_RedPlant, gDecorIconPalette_RedPlant},
    },

    [DECOR_TROPICAL_PLANT] =
    {
        .id = DECOR_TROPICAL_PLANT,
        .name = _("PL. TROPICAL"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_PLANT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Exuberante planta\ntropical."
            ""),
        .tiles = DecorGfx_TROPICAL_PLANT,
        .icon = {gDecorIcon_TropicalPlant, gDecorIconPalette_TropicalPlant},
    },

    [DECOR_PRETTY_FLOWERS] =
    {
        .id = DECOR_PRETTY_FLOWERS,
        .name = _("FLORES BONITAS"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_PLANT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Maceta llena de\nflores muy bonitas."
            ""),
        .tiles = DecorGfx_PRETTY_FLOWERS,
        .icon = {gDecorIcon_PrettyFlowers, gDecorIconPalette_PrettyFlowers},
    },

    [DECOR_COLORFUL_PLANT] =
    {
        .id = DECOR_COLORFUL_PLANT,
        .name = _("PL. COLORIDA"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_2x2,
        .category = DECORCAT_PLANT,
        .price = 5000,
        .description = COMPOUND_STRING(
            "Macetón lleno de\nflores de colores."
            ""
            ""),
        .tiles = DecorGfx_COLORFUL_PLANT,
        .icon = {gDecorIcon_ColorfulPlant, gDecorIconPalette_ColorfulPlant},
    },

    [DECOR_BIG_PLANT] =
    {
        .id = DECOR_BIG_PLANT,
        .name = _("PLANTA GRANDE"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_2x2,
        .category = DECORCAT_PLANT,
        .price = 5000,
        .description = COMPOUND_STRING(
            "Planta grande con\nforma de sombrilla."
            ""
            ""),
        .tiles = DecorGfx_BIG_PLANT,
        .icon = {gDecorIcon_BigPlant, gDecorIconPalette_BigPlant},
    },

    [DECOR_GORGEOUS_PLANT] =
    {
        .id = DECOR_GORGEOUS_PLANT,
        .name = _("PLANTA ENORME"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_2x2,
        .category = DECORCAT_PLANT,
        .price = 5000,
        .description = COMPOUND_STRING(
            "Planta enorme\ne imponente."
            ""),
        .tiles = DecorGfx_GORGEOUS_PLANT,
        .icon = {gDecorIcon_GorgeousPlant, gDecorIconPalette_GorgeousPlant},
    },

    [DECOR_RED_BRICK] =
    {
        .id = DECOR_RED_BRICK,
        .name = _("LADRILLO ROJO"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Ladrillo de color\nrojo. Ponle cosas\nencima."
            ""
            ""),
        .tiles = DecorGfx_RED_BRICK,
        .icon = {gDecorIcon_RedBrick, gDecorIconPalette_RedBrick},
    },

    [DECOR_YELLOW_BRICK] =
    {
        .id = DECOR_YELLOW_BRICK,
        .name = _("LADR. AMARILLO"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Ladrillo de color\namarillo. Ponle\ncosas encima."
            ""
            ""),
        .tiles = DecorGfx_YELLOW_BRICK,
        .icon = {gDecorIcon_YellowBrick, gDecorIconPalette_YellowBrick},
    },

    [DECOR_BLUE_BRICK] =
    {
        .id = DECOR_BLUE_BRICK,
        .name = _("LADRILLO AZUL"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Ladrillo de color\nazul. Ponle cosas\nencima."
            ""
            ""),
        .tiles = DecorGfx_BLUE_BRICK,
        .icon = {gDecorIcon_BlueBrick, gDecorIconPalette_BlueBrick},
    },

    [DECOR_RED_BALLOON] =
    {
        .id = DECOR_RED_BALLOON,
        .name = _("GLOBO ROJO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Globo rojo de agua.\nSi lo pisas, explota."
            ""
            ""),
        .tiles = DecorGfx_RED_BALLOON,
        .icon = {NULL, NULL},
    },

    [DECOR_BLUE_BALLOON] =
    {
        .id = DECOR_BLUE_BALLOON,
        .name = _("GLOBO AZUL"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Globo azul de agua.\nSi lo pisas, explota."
            ""
            ""),
        .tiles = DecorGfx_BLUE_BALLOON,
        .icon = {NULL, NULL},
    },

    [DECOR_YELLOW_BALLOON] =
    {
        .id = DECOR_YELLOW_BALLOON,
        .name = _("GLOBO AMARILLO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Globo amarillo de\nagua. Si lo pisas,\nexplota."
            ""
            ""),
        .tiles = DecorGfx_YELLOW_BALLOON,
        .icon = {NULL, NULL},
    },

    [DECOR_RED_TENT] =
    {
        .id = DECOR_RED_TENT,
        .name = _("TIENDA ROJA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_ORNAMENT,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Tienda grande roja.\nSirve de escondite."
            ""
            ""),
        .tiles = DecorGfx_RED_TENT,
        .icon = {gDecorIcon_RedTent, gDecorIconPalette_RedTent},
    },

    [DECOR_BLUE_TENT] =
    {
        .id = DECOR_BLUE_TENT,
        .name = _("TIENDA AZUL"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_ORNAMENT,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Tienda grande azul.\nSirve de escondite."
            ""
            ""),
        .tiles = DecorGfx_BLUE_TENT,
        .icon = {gDecorIcon_BlueTent, gDecorIconPalette_BlueTent},
    },

    [DECOR_SOLID_BOARD] =
    {
        .id = DECOR_SOLID_BOARD,
        .name = _("TABLA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Colócala sobre un\nagujero y cruza  \nal otro lado."
            ""
            ""),
        .tiles = DecorGfx_SOLID_BOARD,
        .icon = {gDecorIcon_SolidBoard, gDecorIconPalette_SolidBoard},
    },

    [DECOR_SLIDE] =
    {
        .id = DECOR_SLIDE,
        .name = _("TOBOGÁN"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_2x4,
        .category = DECORCAT_ORNAMENT,
        .price = 8000,
        .description = COMPOUND_STRING(
            "Sirve para \ndeslizarse desde\nuna plataforma."
            ""),
        .tiles = DecorGfx_SLIDE,
        .icon = {gDecorIcon_Slide, gDecorIconPalette_Slide},
    },

    [DECOR_FENCE_LENGTH] =
    {
        .id = DECOR_FENCE_LENGTH,
        .name = _("VALLA LARGA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Pequeña valla que\nbloquea el paso."
            ""),
        .tiles = DecorGfx_FENCE_LENGTH,
        .icon = {NULL, NULL},
    },

    [DECOR_FENCE_WIDTH] =
    {
        .id = DECOR_FENCE_WIDTH,
        .name = _("VALLA ANCHA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Pequeña valla que\nbloquea el paso."
            ""),
        .tiles = DecorGfx_FENCE_WIDTH,
        .icon = {NULL, NULL},
    },

    [DECOR_TIRE] =
    {
        .id = DECOR_TIRE,
        .name = _("NEUMÁTICO"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_2x2,
        .category = DECORCAT_ORNAMENT,
        .price = 800,
        .description = COMPOUND_STRING(
            "Neumático viejo.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_TIRE,
        .icon = {gDecorIcon_Tire, gDecorIconPalette_Tire},
    },

    [DECOR_STAND] =
    {
        .id = DECOR_STAND,
        .name = _("PODIO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_4x2,
        .category = DECORCAT_ORNAMENT,
        .price = 7000,
        .description = COMPOUND_STRING(
            "Gran pedestal\ncon escalones."
            ""),
        .tiles = DecorGfx_STAND,
        .icon = {gDecorIcon_Stand, gDecorIconPalette_Stand},
    },

    [DECOR_MUD_BALL] =
    {
        .id = DECOR_MUD_BALL,
        .name = _("BOLA DE LODO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 200,
        .description = COMPOUND_STRING(
            "Gran bola de lodo\nque se deshace\nsi la pisas."
            ""
            ""),
        .tiles = DecorGfx_MUD_BALL,
        .icon = {NULL, NULL},
    },

    [DECOR_BREAKABLE_DOOR] =
    {
        .id = DECOR_BREAKABLE_DOOR,
        .name = _("PUERTA RARA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Es extraña, pero\npuede atravesarse\nsin problema."
            ""
            ""),
        .tiles = DecorGfx_BREAKABLE_DOOR,
        .icon = {gDecorIcon_BreakableDoor, gDecorIconPalette_BreakableDoor},
    },

    [DECOR_SAND_ORNAMENT] =
    {
        .id = DECOR_SAND_ORNAMENT,
        .name = _("ADORNO ARENA"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Adorno de arena\nque se desmorona\ncon sólo tocarlo."
            ""
            ""),
        .tiles = DecorGfx_SAND_ORNAMENT,
        .icon = {gDecorIcon_SandOrnament, gDecorIconPalette_SandOrnament},
    },

    [DECOR_SILVER_SHIELD] =
    {
        .id = DECOR_SILVER_SHIELD,
        .name = _("ESCUDO PLATA"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 0,
        .description = COMPOUND_STRING(
            "Se gana al vencer \n50 veces seguidas \nen TORRE BATALLA."
            ""
            ""),
        .tiles = DecorGfx_SILVER_SHIELD,
        .icon = {NULL, NULL},
    },

    [DECOR_GOLD_SHIELD] =
    {
        .id = DECOR_GOLD_SHIELD,
        .name = _("ESCUDO DE ORO"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 0,
        .description = COMPOUND_STRING(
            "Premio por 100 \nvictorias seguidas\nen TORRE BATALLA."
            ""
            ""),
        .tiles = DecorGfx_GOLD_SHIELD,
        .icon = {NULL, NULL},
    },

    [DECOR_GLASS_ORNAMENT] =
    {
        .id = DECOR_GLASS_ORNAMENT,
        .name = _("ADORNO CRISTAL"),
        .permission = DECORPERM_BEHIND_FLOOR,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_ORNAMENT,
        .price = 0,
        .description = COMPOUND_STRING(
            "Réplica en cristal\nde una escultura\ndel MUSEO DE ARTE."
            ""
            ""),
        .tiles = DecorGfx_GLASS_ORNAMENT,
        .icon = {gDecorIcon_GlassOrnament, gDecorIconPalette_GlassOrnament},
    },

    [DECOR_TV] =
    {
        .id = DECOR_TV,
        .name = _("TELEVISIÓN"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Tele de juguete\nde color gris."
            ""),
        .tiles = DecorGfx_TV,
        .icon = {NULL, NULL},
    },

    [DECOR_ROUND_TV] =
    {
        .id = DECOR_ROUND_TV,
        .name = _("TELE REDONDA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tele de juguete con\nforma de SEEDOT."
            ""
            ""),
        .tiles = DecorGfx_ROUND_TV,
        .icon = {NULL, NULL},
    },

    [DECOR_CUTE_TV] =
    {
        .id = DECOR_CUTE_TV,
        .name = _("TELE BONITA"),
        .permission = DECORPERM_SOLID_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_ORNAMENT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tele de juguete con\nforma de SKITTY."
            ""
            ""),
        .tiles = DecorGfx_CUTE_TV,
        .icon = {NULL, NULL},
    },

    [DECOR_GLITTER_MAT] =
    {
        .id = DECOR_GLITTER_MAT,
        .name = _("TAPETE BRILLO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Tapete viejo que\nbrilla si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_GLITTER_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_JUMP_MAT] =
    {
        .id = DECOR_JUMP_MAT,
        .name = _("TAPETE MUELLE"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Tapete mágico\nque te hace saltar\nsi lo pisas."
            ""
            ""),
        .tiles = DecorGfx_JUMP_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_SPIN_MAT] =
    {
        .id = DECOR_SPIN_MAT,
        .name = _("TAPETE GIRO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Tapete mágico\nque te hace girar\nsi lo pisas."
            ""
            ""),
        .tiles = DecorGfx_SPIN_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_C_LOW_NOTE_MAT] =
    {
        .id = DECOR_C_LOW_NOTE_MAT,
        .name = _("TAP. DO MENOR"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que suena\nen do menor,\nsi lo pisas."
            ""
            ""),
        .tiles = DecorGfx_C_LOW_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_D_NOTE_MAT] =
    {
        .id = DECOR_D_NOTE_MAT,
        .name = _("TAPETE NOTA RE"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nre, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_D_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_E_NOTE_MAT] =
    {
        .id = DECOR_E_NOTE_MAT,
        .name = _("TAPETE NOTA MI"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nmi, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_E_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_F_NOTE_MAT] =
    {
        .id = DECOR_F_NOTE_MAT,
        .name = _("TAPETE NOTA FA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nfa, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_F_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_G_NOTE_MAT] =
    {
        .id = DECOR_G_NOTE_MAT,
        .name = _("TAP. NOTA SOL"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nsol, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_G_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_A_NOTE_MAT] =
    {
        .id = DECOR_A_NOTE_MAT,
        .name = _("TAPETE NOTA LA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nla, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_A_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_B_NOTE_MAT] =
    {
        .id = DECOR_B_NOTE_MAT,
        .name = _("TAPETE NOTA SI"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que toca\nsi, si lo pisas."
            ""
            ""),
        .tiles = DecorGfx_B_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_C_HIGH_NOTE_MAT] =
    {
        .id = DECOR_C_HIGH_NOTE_MAT,
        .name = _("TAP. DO MAYOR"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_MAT,
        .price = 500,
        .description = COMPOUND_STRING(
            "Tapete que suena\nen do mayor,\nsi lo pisas."
            ""
            ""),
        .tiles = DecorGfx_C_HIGH_NOTE_MAT,
        .icon = {NULL, NULL},
    },

    [DECOR_SURF_MAT] =
    {
        .id = DECOR_SURF_MAT,
        .name = _("TAPETE SURF"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde SURF.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_SURF_MAT,
        .icon = {gDecorIcon_SurfMat, gDecorIconPalette_SurfMat},
    },

    [DECOR_THUNDER_MAT] =
    {
        .id = DECOR_THUNDER_MAT,
        .name = _("TAPETE TRUENO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde TRUENO.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_THUNDER_MAT,
        .icon = {gDecorIcon_ThunderMat, gDecorIconPalette_ThunderMat},
    },

    [DECOR_FIRE_BLAST_MAT] =
    {
        .id = DECOR_FIRE_BLAST_MAT,
        .name = _("TAP. LLAMARADA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde LLAMARADA.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_FIRE_BLAST_MAT,
        .icon = {gDecorIcon_FireBlastMat, gDecorIconPalette_FireBlastMat},
    },

    [DECOR_POWDER_SNOW_MAT] =
    {
        .id = DECOR_POWDER_SNOW_MAT,
        .name = _("T. NIEVE POLVO"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde NIEVE POLVO.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_POWDER_SNOW_MAT,
        .icon = {gDecorIcon_PowderSnowMat, gDecorIconPalette_PowderSnowMat},
    },

    [DECOR_ATTRACT_MAT] =
    {
        .id = DECOR_ATTRACT_MAT,
        .name = _("TAP. ATRACCIÓN"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde ATRACCIÓN.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_ATTRACT_MAT,
        .icon = {gDecorIcon_AttractMat, gDecorIconPalette_AttractMat},
    },

    [DECOR_FISSURE_MAT] =
    {
        .id = DECOR_FISSURE_MAT,
        .name = _("TAPETE FISURA"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde FISURA.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_FISSURE_MAT,
        .icon = {gDecorIcon_FissureMat, gDecorIconPalette_FissureMat},
    },

    [DECOR_SPIKES_MAT] =
    {
        .id = DECOR_SPIKES_MAT,
        .name = _("TAPETE PÚAS"),
        .permission = DECORPERM_PASS_FLOOR,
        .shape = DECORSHAPE_3x3,
        .category = DECORCAT_MAT,
        .price = 4000,
        .description = COMPOUND_STRING(
            "Tapete con dibujo\nde PÚAS.\nPonle cosas encima."
            ""
            ""),
        .tiles = DecorGfx_SPIKES_MAT,
        .icon = {gDecorIcon_SpikesMat, gDecorIconPalette_SpikesMat},
    },

    [DECOR_BALL_POSTER] =
    {
        .id = DECOR_BALL_POSTER,
        .name = _("P. POKé BALL"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_POSTER,
        .price = 1000,
        .description = COMPOUND_STRING(
            "Póster pequeño de\nPOKé BALL."
            ""
            ""),
        .tiles = DecorGfx_BALL_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_GREEN_POSTER] =
    {
        .id = DECOR_GREEN_POSTER,
        .name = _("PÓSTER VERDE"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_POSTER,
        .price = 1000,
        .description = COMPOUND_STRING(
            "Póster pequeño\nde TREECKO."
            ""),
        .tiles = DecorGfx_GREEN_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_RED_POSTER] =
    {
        .id = DECOR_RED_POSTER,
        .name = _("PÓSTER ROJO"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_POSTER,
        .price = 1000,
        .description = COMPOUND_STRING(
            "Póster pequeño\nde TORCHIC."
            ""),
        .tiles = DecorGfx_RED_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_BLUE_POSTER] =
    {
        .id = DECOR_BLUE_POSTER,
        .name = _("PÓSTER AZUL"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_POSTER,
        .price = 1000,
        .description = COMPOUND_STRING(
            "Póster pequeño\nde MUDKIP."
            ""),
        .tiles = DecorGfx_BLUE_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_CUTE_POSTER] =
    {
        .id = DECOR_CUTE_POSTER,
        .name = _("PÓSTER BONITO"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_POSTER,
        .price = 1000,
        .description = COMPOUND_STRING(
            "Póster pequeño\nde AZURILL."
            ""),
        .tiles = DecorGfx_CUTE_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_PIKA_POSTER] =
    {
        .id = DECOR_PIKA_POSTER,
        .name = _("PÓSTER PIKA"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_2x1,
        .category = DECORCAT_POSTER,
        .price = 1500,
        .description = COMPOUND_STRING(
            "Póster grande\nde PIKACHU\ny PICHU."
            ""
            ""),
        .tiles = DecorGfx_PIKA_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_LONG_POSTER] =
    {
        .id = DECOR_LONG_POSTER,
        .name = _("PÓSTER GRANDE"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_2x1,
        .category = DECORCAT_POSTER,
        .price = 1500,
        .description = COMPOUND_STRING(
            "Póster grande\nde SEVIPER."
            ""),
        .tiles = DecorGfx_LONG_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_SEA_POSTER] =
    {
        .id = DECOR_SEA_POSTER,
        .name = _("PÓSTER MAR"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_2x1,
        .category = DECORCAT_POSTER,
        .price = 1500,
        .description = COMPOUND_STRING(
            "Póster grande\nde RELICANTH."
            ""),
        .tiles = DecorGfx_SEA_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_SKY_POSTER] =
    {
        .id = DECOR_SKY_POSTER,
        .name = _("PÓSTER CIELO"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_2x1,
        .category = DECORCAT_POSTER,
        .price = 1500,
        .description = COMPOUND_STRING(
            "Póster grande\nde WINGULL."
            ""),
        .tiles = DecorGfx_SKY_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_KISS_POSTER] =
    {
        .id = DECOR_KISS_POSTER,
        .name = _("PÓSTER BESO"),
        .permission = DECORPERM_NA_WALL,
        .shape = DECORSHAPE_2x1,
        .category = DECORCAT_POSTER,
        .price = 1500,
        .description = COMPOUND_STRING(
            "Póster grande\nde SMOOCHUM."
            ""),
        .tiles = DecorGfx_KISS_POSTER,
        .icon = {NULL, NULL},
    },

    [DECOR_PICHU_DOLL] =
    {
        .id = DECOR_PICHU_DOLL,
        .name = _("MUÑECO PICHU"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de PICHU.\nPonlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_PICHU_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_PIKACHU_DOLL] =
    {
        .id = DECOR_PIKACHU_DOLL,
        .name = _("MUÑECO PIKACHU"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de PIKACHU.\nPonlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_PIKACHU_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_MARILL_DOLL] =
    {
        .id = DECOR_MARILL_DOLL,
        .name = _("MUÑECO MARILL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de MARILL.\nPonlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_MARILL_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_TOGEPI_DOLL] =
    {
        .id = DECOR_TOGEPI_DOLL,
        .name = _("MUÑECO TOGEPI"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de TOGEPI.\nPonlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_TOGEPI_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_CYNDAQUIL_DOLL] =
    {
        .id = DECOR_CYNDAQUIL_DOLL,
        .name = _("MUÑ. CYNDAQUIL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nCYNDAQUIL. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_CYNDAQUIL_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_CHIKORITA_DOLL] =
    {
        .id = DECOR_CHIKORITA_DOLL,
        .name = _("MUÑ. CHIKORITA"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nCHIKORITA. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_CHIKORITA_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_TOTODILE_DOLL] =
    {
        .id = DECOR_TOTODILE_DOLL,
        .name = _("MUÑ. TOTODILE"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nTOTODILE. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_TOTODILE_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_JIGGLYPUFF_DOLL] =
    {
        .id = DECOR_JIGGLYPUFF_DOLL,
        .name = _("MUÑ. JIGGLYPUFF"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de JIGGLY-\nPUFF. Ponlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_JIGGLYPUFF_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_MEOWTH_DOLL] =
    {
        .id = DECOR_MEOWTH_DOLL,
        .name = _("MUÑECO MEOWTH"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de MEOWTH.\nPonlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_MEOWTH_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_CLEFAIRY_DOLL] =
    {
        .id = DECOR_CLEFAIRY_DOLL,
        .name = _("MUÑECO CLEFAIRY"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nCLEFAIRY. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_CLEFAIRY_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_DITTO_DOLL] =
    {
        .id = DECOR_DITTO_DOLL,
        .name = _("MUÑECO DITTO"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de DITTO.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_DITTO_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_SMOOCHUM_DOLL] =
    {
        .id = DECOR_SMOOCHUM_DOLL,
        .name = _("MUÑECO SMOOCHUM"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de SMOO-\nCHUM. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_SMOOCHUM_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_TREECKO_DOLL] =
    {
        .id = DECOR_TREECKO_DOLL,
        .name = _("MUÑECO TREECKO"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nTREECKO. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_TREECKO_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_TORCHIC_DOLL] =
    {
        .id = DECOR_TORCHIC_DOLL,
        .name = _("MUÑECO TORCHIC"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de\nTORCHIC. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_TORCHIC_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_MUDKIP_DOLL] =
    {
        .id = DECOR_MUDKIP_DOLL,
        .name = _("MUÑECO MUDKIP"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de MUDKIP.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_MUDKIP_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_DUSKULL_DOLL] =
    {
        .id = DECOR_DUSKULL_DOLL,
        .name = _("MUÑECO DUSKULL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de DUSKULL.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_DUSKULL_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_WYNAUT_DOLL] =
    {
        .id = DECOR_WYNAUT_DOLL,
        .name = _("MUÑECO WYNAUT"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de WYNAUT.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_WYNAUT_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_BALTOY_DOLL] =
    {
        .id = DECOR_BALTOY_DOLL,
        .name = _("MUÑECO BALTOY"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de BALTOY.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_BALTOY_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_KECLEON_DOLL] =
    {
        .id = DECOR_KECLEON_DOLL,
        .name = _("MUÑECO KECLEON"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de KECLEON.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_KECLEON_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_AZURILL_DOLL] =
    {
        .id = DECOR_AZURILL_DOLL,
        .name = _("MUÑECO AZURILL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de AZURILL.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_AZURILL_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_SKITTY_DOLL] =
    {
        .id = DECOR_SKITTY_DOLL,
        .name = _("MUÑECO SKITTY"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de SKITTY.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_SKITTY_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_SWABLU_DOLL] =
    {
        .id = DECOR_SWABLU_DOLL,
        .name = _("MUÑECO SWABLU"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de SWABLU.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_SWABLU_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_GULPIN_DOLL] =
    {
        .id = DECOR_GULPIN_DOLL,
        .name = _("MUÑECO GULPIN"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de GULPIN.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_GULPIN_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_LOTAD_DOLL] =
    {
        .id = DECOR_LOTAD_DOLL,
        .name = _("MUÑECO LOTAD"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de LOTAD.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_LOTAD_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_SEEDOT_DOLL] =
    {
        .id = DECOR_SEEDOT_DOLL,
        .name = _("MUÑECO SEEDOT"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_DOLL,
        .price = 3000,
        .description = COMPOUND_STRING(
            "Muñeco de SEEDOT.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_SEEDOT_DOLL,
        .icon = {NULL, NULL},
    },

    [DECOR_PIKA_CUSHION] =
    {
        .id = DECOR_PIKA_CUSHION,
        .name = _("COJÍN PIKA"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de PIKACHU.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_PIKA_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_ROUND_CUSHION] =
    {
        .id = DECOR_ROUND_CUSHION,
        .name = _("COJÍN REDONDO"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de MARILL.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_ROUND_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_KISS_CUSHION] =
    {
        .id = DECOR_KISS_CUSHION,
        .name = _("COJÍN BESO"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de SMOOCHUM.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_KISS_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_ZIGZAG_CUSHION] =
    {
        .id = DECOR_ZIGZAG_CUSHION,
        .name = _("COJÍN ZIGZAGOON"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de ZIGZA-\nGOON. Ponlo en\nuna mesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_ZIGZAG_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_SPIN_CUSHION] =
    {
        .id = DECOR_SPIN_CUSHION,
        .name = _("COJÍN SPINDA"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de SPINDA.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_SPIN_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_DIAMOND_CUSHION] =
    {
        .id = DECOR_DIAMOND_CUSHION,
        .name = _("COJÍN DIAMANTE"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín de SABLEYE.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_DIAMOND_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_BALL_CUSHION] =
    {
        .id = DECOR_BALL_CUSHION,
        .name = _("COJÍN BALL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín con forma de\nBALL. Ponlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_BALL_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_GRASS_CUSHION] =
    {
        .id = DECOR_GRASS_CUSHION,
        .name = _("COJÍN PLANTA"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín estampado de\nplanta. Ponlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_GRASS_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_FIRE_CUSHION] =
    {
        .id = DECOR_FIRE_CUSHION,
        .name = _("COJÍN FUEGO"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín estampado de\nfuego. Ponlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_FIRE_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_WATER_CUSHION] =
    {
        .id = DECOR_WATER_CUSHION,
        .name = _("COJÍN AGUA"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x1,
        .category = DECORCAT_CUSHION,
        .price = 2000,
        .description = COMPOUND_STRING(
            "Cojín estampado de\nagua. Ponlo en una\nmesa o tapete."
            ""
            ""),
        .tiles = DecorGfx_WATER_CUSHION,
        .icon = {NULL, NULL},
    },

    [DECOR_SNORLAX_DOLL] =
    {
        .id = DECOR_SNORLAX_DOLL,
        .name = _("MUÑECO SNORLAX"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_SNORLAX_DOLL,
        .icon = {gDecorIcon_SnorlaxDoll, gDecorIconPalette_SnorlaxDoll},
    },

    [DECOR_RHYDON_DOLL] =
    {
        .id = DECOR_RHYDON_DOLL,
        .name = _("MUÑECO RHYDON"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_RHYDON_DOLL,
        .icon = {gDecorIcon_RhydonDoll, gDecorIconPalette_RhydonDoll},
    },

    [DECOR_LAPRAS_DOLL] =
    {
        .id = DECOR_LAPRAS_DOLL,
        .name = _("MUÑECO LAPRAS"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_LAPRAS_DOLL,
        .icon = {gDecorIcon_LaprasDoll, gDecorIconPalette_LaprasDoll},
    },

    [DECOR_VENUSAUR_DOLL] =
    {
        .id = DECOR_VENUSAUR_DOLL,
        .name = _("MUÑECO VENUSAUR"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_VENUSAUR_DOLL,
        .icon = {gDecorIcon_VenusaurDoll, gDecorIconPalette_VenusaurDoll},
    },

    [DECOR_CHARIZARD_DOLL] =
    {
        .id = DECOR_CHARIZARD_DOLL,
        .name = _("MUÑECO CHARIZAR"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_CHARIZARD_DOLL,
        .icon = {gDecorIcon_CharizardDoll, gDecorIconPalette_CharizardDoll},
    },

    [DECOR_BLASTOISE_DOLL] =
    {
        .id = DECOR_BLASTOISE_DOLL,
        .name = _("MUÑ. BLASTOISE"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_BLASTOISE_DOLL,
        .icon = {gDecorIcon_BlastoiseDoll, gDecorIconPalette_BlastoiseDoll},
    },

    [DECOR_WAILMER_DOLL] =
    {
        .id = DECOR_WAILMER_DOLL,
        .name = _("MUÑECO WAILMER"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_WAILMER_DOLL,
        .icon = {gDecorIcon_WailmerDoll, gDecorIconPalette_WailmerDoll},
    },

    [DECOR_REGIROCK_DOLL] =
    {
        .id = DECOR_REGIROCK_DOLL,
        .name = _("MUÑECO REGIROCK"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_REGIROCK_DOLL,
        .icon = {gDecorIcon_RegirockDoll, gDecorIconPalette_RegirockDoll},
    },

    [DECOR_REGICE_DOLL] =
    {
        .id = DECOR_REGICE_DOLL,
        .name = _("MUÑECO REGICE"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_REGICE_DOLL,
        .icon = {gDecorIcon_RegiceDoll, gDecorIconPalette_RegiceDoll},
    },

    [DECOR_REGISTEEL_DOLL] =
    {
        .id = DECOR_REGISTEEL_DOLL,
        .name = _("MUÑ. REGISTEEL"),
        .permission = DECORPERM_SPRITE,
        .shape = DECORSHAPE_1x2,
        .category = DECORCAT_DOLL,
        .price = 10000,
        .description = COMPOUND_STRING(
            "Muñeco grande.\nPonlo en una mesa\no tapete."
            ""
            ""),
        .tiles = DecorGfx_REGISTEEL_DOLL,
        .icon = {gDecorIcon_RegisteelDoll, gDecorIconPalette_RegisteelDoll},
    }
};
