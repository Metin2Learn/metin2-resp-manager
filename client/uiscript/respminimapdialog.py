import uiScriptLocale

ROOT_PATH = "d:/ymir work/ui/game/resp/"
HEADER_FONT_COLOR = 0xffccc79d
HEADER_FONT_NAME = "Tahoma:12"

SLOT_FONT_NAME = "Tahoma:12"

window = {
    "name": "RespMiniMapDialog",

    "x": SCREEN_WIDTH - 136,
    "y": 200,

    "width": 121,
    "height": 89,

    "children":
        (
            {
                "name": "resp_info_slot",
                "type": "image",

                "x": 0,
                "y": 0,

                "image": ROOT_PATH + "minimap_info_slot.sub",

                "children":
                    (
                        {
                            "name": "boss_count_text_slot",
                            "type": "window",

                            "x": 0,
                            "y": 4,

                            "horizontal_align": "center",

                            "width": 83,
                            "height": 16,

                            "children":
                                (
                                    {
                                        "name": "boss_count_text",
                                        "type": "text",

                                        "all_align": "center",

                                        "x": 0,
                                        "y": 0,

                                        "color": HEADER_FONT_COLOR,
                                        "fontname": HEADER_FONT_NAME,

                                        "text": uiScriptLocale.RESP_MINIMAP_BOSS,
                                    },
                                ),
                        },
                        {
                            "name": "boss_count_slot",
                            "type": "window",

                            "x": 0,
                            "y": 24,

                            "horizontal_align": "center",

                            "width": 83,
                            "height": 16,

                            "children":
                                (
                                    {
                                        "name": "boss_count_value",
                                        "type": "text",

                                        "all_align": "center",

                                        "x": 0,
                                        "y": 0,

                                        "text": "-",
                                        "fontname": SLOT_FONT_NAME,
                                    },
                                ),
                        },
                        {
                            "name": "metin_count_text_slot",
                            "type": "window",

                            "x": 0,
                            "y": 44,

                            "horizontal_align": "center",

                            "width": 83,
                            "height": 16,

                            "children":
                                (
                                    {
                                        "name": "metin_count_text",
                                        "type": "text",

                                        "all_align": "center",

                                        "x": 0,
                                        "y": 0,

                                        "color": HEADER_FONT_COLOR,
                                        "fontname": HEADER_FONT_NAME,

                                        "text": uiScriptLocale.RESP_MINIMAP_METIN,
                                    },
                                ),
                        },
                        {
                            "name": "metin_count_slot",
                            "type": "window",

                            "x": 0,
                            "y": 64,

                            "horizontal_align": "center",

                            "width": 83,
                            "height": 16,

                            "children":
                                (
                                    {
                                        "name": "metin_count_value",
                                        "type": "text",

                                        "all_align": "center",

                                        "x": 0,
                                        "y": 0,

                                        "text": "-",
                                        "fontname": SLOT_FONT_NAME,
                                    },
                                ),
                        },
                    ),
            },
        ),
}
