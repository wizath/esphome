import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_ID

CODEOWNERS = ["@agoode", "@wizath"]
DEPENDENCIES = ["spi"]
MULTI_CONF = True

mmc5983_ns = cg.esphome_ns.namespace("mmc5983")
MMC5983Component = mmc5983_ns.class_(
    "MMC5983Component", cg.PollingComponent, spi.SPIDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(MMC5983Component),
        }
    )
    .extend(cv.polling_component_schema("60s"))
    .extend(spi.spi_device_schema(cs_pin_required=True))
)


async def to_code(config):
    """Code generation for MMC5983 component."""
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)
