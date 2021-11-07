Import("env")

board_config = env.BoardConfig()
# should be array of VID:PID pairs
board_config.update("build.hwids", [
  ["0x6969", "0x0002"],  # 1st pair
  ["0x6969", "0x0002"]  # 2nd pair, etc.
])
board_config.update("build.usb_product", "Pedals")