import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch

light_switch_actuator_ns = cg.esphome_ns.namespace("light_switch_actuator")
LightSwitchActuator = light_switch_actuator_ns.class_("LightSwitchActuator", switch.Switch, cg.Component)

CONFIG_SCHEMA = switch.switch_schema(LightSwitchActuator).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = await switch.new_switch(config)
    await cg.register_component(var, config)