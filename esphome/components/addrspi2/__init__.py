import esphome.codegen as cg
from esphome.components import spi
import esphome.config_validation as cv
from esphome.const import CONF_ADDRESS, CONF_DEVICES, CONF_ID

DEPENDENCIES = ["spi"]
CODEOWNERS = ["@wizath"]
MULTI_CONF = True

addrspi2_ns = cg.esphome_ns.namespace("addrspi2")
ADDRSPI2Component = addrspi2_ns.class_("ADDRSPI2Component", cg.Component, spi.SPIDevice)
ADDRSPI2Device = addrspi2_ns.class_("ADDRSPI2Device")

DEVICE_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_ID): cv.declare_id(ADDRSPI2Device),
        cv.Required(CONF_ADDRESS): cv.hex_uint8_t,
    }
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(ADDRSPI2Component),
            cv.Optional(CONF_DEVICES, default=[]): cv.ensure_list(DEVICE_SCHEMA),
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(spi.spi_device_schema(cs_pin_required=True, default_mode="MODE0"))
)

FINAL_VALIDATE_SCHEMA = spi.final_validate_device_schema(
    "addrspi2", require_miso=False, require_mosi=True
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await spi.register_spi_device(var, config)

    for device_config in config[CONF_DEVICES]:
        device = cg.new_Pvariable(device_config[CONF_ID])
        cg.add(device.set_parent(var))
        cg.add(device.set_address(device_config[CONF_ADDRESS]))
        cg.add(var.register_device(device))
