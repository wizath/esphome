from esphome import pins
import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_CHANNELS, CONF_ID

CODEOWNERS = ["@wizath"]
DEPENDENCIES = ["spi"]

hc138_ns = cg.esphome_ns.namespace("hc138")
HC138Component = hc138_ns.class_("HC138Component", cg.Component, spi.SPIDevice)
HC138Channel = hc138_ns.class_("HC138Channel", spi.SPIComponent)

MULTI_CONF = True

CONF_BUS_ID = "bus_id"
CONF_SPI_ID = "spi_id"
CONF_A0 = "a0"
CONF_A1 = "a1"
CONF_A2 = "a2"

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(HC138Component),
            cv.Required(CONF_A0): pins.gpio_output_pin_schema,
            cv.Required(CONF_A1): pins.gpio_output_pin_schema,
            cv.Required(CONF_A2): pins.gpio_output_pin_schema,
            cv.Optional(CONF_CHANNELS, default=[]): cv.ensure_list(
                {
                    cv.Required(CONF_BUS_ID): cv.declare_id(HC138Channel),
                    cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=7),
                }
            ),
        }
    )
    .extend(spi.spi_device_schema(cs_pin_required=False))
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    # Setup address pins
    a0 = await cg.gpio_pin_expression(config[CONF_A0])
    a1 = await cg.gpio_pin_expression(config[CONF_A1])
    a2 = await cg.gpio_pin_expression(config[CONF_A2])
    cg.add(var.set_a0(a0))
    cg.add(var.set_a1(a1))
    cg.add(var.set_a2(a2))

    # Setup channels
    for conf in config[CONF_CHANNELS]:
        chan = cg.new_Pvariable(conf[CONF_BUS_ID])
        await cg.register_component(chan, config)
        cg.add(chan.set_parent(var))
        cg.add(chan.set_channel(conf[CONF_CHANNEL]))
