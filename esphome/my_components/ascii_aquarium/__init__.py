import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.const import CONF_ID

# Vytvoření jmenného prostoru pro C++
ascii_aquarium_ns = cg.esphome_ns.namespace("ascii_aquarium")
AsciiAquarium = ascii_aquarium_ns.class_("AsciiAquarium", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(AsciiAquarium),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
