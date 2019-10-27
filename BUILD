cc_binary(
  name="sourbuddy",
  srcs=glob(["*.cpp", "*.h"]),
  includes=["/usr/local/include", "/opt/X11/include"],
  copts=["-Wall -Werror --std=c++11", "-L/usr/local/lib", "-I/opt/X11/lib"],
  linkopts=["-framework OpenGL -lglfw -lglew"],
)