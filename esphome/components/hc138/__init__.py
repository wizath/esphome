"""HC138 SPI multiplexer component."""

from esphome import pins
import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_CHANNEL, CONF_CHANNELS, CONF_DATA_RATE, CONF_ID

# SPI Configuration constants
CONF_SPI_MODE = "spi_mode"
CONF_BIT_ORDER = "bit_order"

# SPI Mode options - use the same as spi component
SPIMode = spi.spi_ns.enum("SPIMode")
SPI_MODE_OPTIONS = {
    "MODE0": SPIMode.MODE0,
    "MODE1": SPIMode.MODE1,
    "MODE2": SPIMode.MODE2,
    "MODE3": SPIMode.MODE3,
    0: SPIMode.MODE0,
    1: SPIMode.MODE1,
    2: SPIMode.MODE2,
    3: SPIMode.MODE3,
    "0": SPIMode.MODE0,
    "1": SPIMode.MODE1,
    "2": SPIMode.MODE2,
    "3": SPIMode.MODE3,
}

# Bit order options
BitOrder = spi.spi_ns.enum("SPIBitOrder")
ORDERS = {
    "msb_first": BitOrder.BIT_ORDER_MSB_FIRST,
    "lsb_first": BitOrder.BIT_ORDER_LSB_FIRST,
}

CODEOWNERS = ["@wizath"]

DEPENDENCIES = ["spi"]

hc138_ns = cg.esphome_ns.namespace("hc138")
HC138Component = hc138_ns.class_("HC138Component", cg.Component, spi.SPIDevice)
HC138Channel = hc138_ns.class_("HC138Channel", spi.SPIComponent)

MULTI_CONF = True
CONF_AO = "a0"
CONF_A1 = "a1"
CONF_A2 = "a2"

CONF_BUS_ID = "bus_id"
CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(HC138Component),
            cv.Optional(CONF_CHANNELS): cv.ensure_list(
                {
                    cv.Required(CONF_BUS_ID): cv.declare_id(HC138Channel),
                    cv.Required(CONF_CHANNEL): cv.int_range(min=0, max=7),
                }
            ),
            cv.Required(CONF_AO): pins.gpio_output_pin_schema,
            cv.Required(CONF_A1): pins.gpio_output_pin_schema,
            cv.Required(CONF_A2): pins.gpio_output_pin_schema,
            cv.Optional(CONF_BIT_ORDER): cv.enum(ORDERS, lower=True),
            cv.Optional(CONF_SPI_MODE): cv.enum(SPI_MODE_OPTIONS, upper=True),
            cv.Optional(CONF_DATA_RATE): spi.SPI_DATA_RATE_SCHEMA,
        }
    )
    .extend(spi.spi_device_schema(cs_pin_required=False))
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    a0 = await cg.gpio_pin_expression(config[CONF_AO])
    a1 = await cg.gpio_pin_expression(config[CONF_A1])
    a2 = await cg.gpio_pin_expression(config[CONF_A2])
    cg.add(var.set_a0(a0))
    cg.add(var.set_a1(a1))
    cg.add(var.set_a2(a2))

    # Configure SPI parameters if provided
    if CONF_BIT_ORDER in config:
        cg.add(var.set_bit_order(config[CONF_BIT_ORDER]))
    if CONF_SPI_MODE in config:
        cg.add(var.set_mode(config[CONF_SPI_MODE]))
    if CONF_DATA_RATE in config:
        cg.add(var.set_data_rate(config[CONF_DATA_RATE]))

    # Create shared SPI delegate for all channels
    cg.add_define("HC138_USE_SHARED_DELEGATE")

    for conf in config[CONF_CHANNELS]:
        chan = cg.new_Pvariable(conf[CONF_BUS_ID])
        await cg.register_component(chan, config)
        cg.add(chan.set_parent(var))
        cg.add(chan.set_channel(conf[CONF_CHANNEL]))
